<?php

/**
 * Custom welcome/login page.
 */
function atrium_welcome() {
  if (!user_access('access content')) {
    menu_set_active_item('user'); // we need tabs to show up
    drupal_set_title(t('Please Login'));
    $login = drupal_get_form('user_login');
    return $login;
  }
  else {
    $install_state = variable_get('atrium_install', 0);
    switch ($install_state) {
      // Stage 0: Clear out messages & theme cache, reload.
      // We shouldn't get here anymore if the installer runs fine.
      // @todo clean up this first step.
      case 0:
        system_theme_data();  // Rebuild theme cache.
        _block_rehash();      // Rebuild block cache.
        views_invalidate_cache(); // Rebuild the views.
        menu_rebuild();       // Rebuild the menu.
        features_rebuild();   // Features rebuild scripts.
        variable_set('atrium_install', 1);
        drupal_goto('welcome');
      // Stage 1: Display welcome and ask user to create first group
      case 1:
        $firstgroup = variable_get('atrium_firstgroup', FALSE);
        if (!$firstgroup) {
          if ($result = db_result(db_query("SELECT count(*) FROM {node} WHERE type = 'group'"))) {
            variable_set('atrium_firstgroup', TRUE);
            $firstgroup = TRUE;
          }
        }
        if ($firstgroup) {
          $space = spaces_load('site', 1);
          // If a homepage setting has been chosen, go there
          if (!empty($space->settings['home'])) {
            $space->redirect('home');
          }
          // Otherwise, fallback to site dashboard feature
          return drupal_goto('home');
        }
        else {
          drupal_set_title(t('Welcome to !sitename', array('!sitename' => variable_get('site_name', 'Atrium'))));

          $output = "<div class='view-empty'>";
          if (node_access('create', 'group')) {
            $output .= t('Create your first !type to get started.', array('!type' => atrium_get_typename('group')));
            $output .= "<div class='buttons'>". l(t('Create !type', array('!type' => atrium_get_typename('group'))), 'node/add/group', array('attributes' => array('class' => 'button'))) ."</div>";
          }
          else {
            $output .= t('The site administator has not finished setting up this site. Please be patient and try again later.');
          }
          $output .= "</div>";

          return $output;
        }
        break;
    }
  }
}

/**
 * User help callback
 */
function atrium_help_page($name = null) {
  if (isset($name) && module_hook($name, 'help')) {
    $module = drupal_parse_info_file(drupal_get_path('module', $name) .'/'. $name .'.info');
    drupal_set_title($module['name']);

    $temp = module_invoke($name, 'help', "help#$name", drupal_help_arg());
    if (empty($temp)) {
      $output = t("No help is available for module %module.", array('%module' => $module['name']));
    }
    else {
      $output = $temp;
    }
  }
  else {
    $empty_arg = drupal_help_arg();
    $module_info = module_rebuild_cache();

    $modules = array();
    foreach (module_implements('help', TRUE) as $module) {
      if (module_invoke($module, 'help', "help#$module", $empty_arg)) {
        $modules[$module] = l($module_info[$module]->info['name'], 'help/'. $module);
      }
    }
    asort($modules);
    $output = theme('item_list', $modules);
  }
  return $output;
}

/**
 * Override of taxonomy/autocomplete. Uses a view query that is space-aware.
 */
function atrium_taxonomy_autocomplete($vid, $string = '') {
  // The user enters a comma-separated list of tags. We only autocomplete the last tag.
  $array = drupal_explode_tags($string);

  // Fetch last tag
  $last_string = trim(array_pop($array));
  $matches = array();
  if ($last_string != '') {
    $view = views_get_view('atrium_taxonomy_autocomplete');
    if ($view) {
      $view->init_display();

      // Override term name value.
      $filters = $view->display_handler->get_option('filters');
      $filters['name']['value'] = $last_string;
      $filters['vid']['value'] = $filters['vid']['operator'] == 'in' ? array($vid) : $vid;
      $view->display_handler->set_option('filters', $filters);

      // Execute query
      $view->execute_display();

      // Get field alias for term name
      $alias = !empty($view->field['name']) ? $view->field['name']->field_alias : '';

      // Collect query results, prepare for autocomplete output
      if ($alias) {
        $prefix = count($array) ? implode(', ', $array) .', ' : '';
        foreach ($view->result as $term) {
          $n = $term->{$alias};
          // Commas and quotes in terms are special cases, so encode 'em.
          if (strpos($term->term_data_name, ',') !== FALSE || strpos($term->term_data_name, '"') !== FALSE) {
            $n = '"'. str_replace('"', '""', $term->term_data_name) .'"';
          }
          $matches[$prefix . $n] = check_plain($term->term_data_name);
        }
      }
    }
  }
  drupal_json($matches);
}
