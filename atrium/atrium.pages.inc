<?php

/**
 * Form alter callback for node form.
 */
function _atrium_form_node_form_alter(&$form, $form_state) {
  $node = $form['#node'];

  // Book mods
  if ($form['#id'] == 'node-form' && book_type_is_allowed($form['#node']->type)) {
    $node = $form['#node'];

    if (!empty($form['book'])) {
      // Fieldset mods
      $form['book']['#weight'] = !empty($form['body_field']['#weight']) ? $form['body_field']['#weight'] : 0;
      $form['book']['#collapsible'] =
      $form['book']['#collapsed'] = FALSE;

      if (!empty($form['book']['bid']['#options'])) {
        // Remove "none" option -- do not allow book pages to be orphaned
        unset($form['book']['bid']['#options'][0]);
        // Filter book options by current space
        if ($view = views_get_view('atrium_book_current')) {
          $view->set_display();
          $view->set_items_per_page(0);
          $view->execute();

          // Collect books in this space into an array
          $books = array();
          $books[$node->nid] = 1;
          if (is_array($view->result) && count($view->result)) {
            foreach($view->result as $row) {
              $books[$row->nid] = 1;
            }
          }

          // Use collected array to filter options
          foreach ($form['book']['bid']['#options'] as $k => $v) {
            if (is_numeric($k) && !isset($books[$k])) {
              unset($form['book']['bid']['#options'][$k]);
            }
          }
        }
      }
    }
  }

  $space = spaces_get_space();

  // Determine whether this node is archivable
  $archivable = in_array($node->type, variable_get('atrium_archivable', array()));
  $archivable = !empty($node->nid) && $archivable;

  // Only allow root books to be archived.
  if (book_type_is_allowed($node->type)) {
    $archivable = $archivable && (!empty($node->book) && $node->book['plid'] == 0);
  }

  // Add a link to archive/reactive the space
  if ($archivable) {
    // Add archive / reactivate buttons
    if ($node->status) {
      $archive_help = t('This !type is currently <strong>active</strong>. You can archive it to hide it from listings and prevent others from adding to or altering its content. You can always undo this action by reactivating the !type.', array('!type' => node_get_types('name', $node->type)));
    }
    else {
      $archive_help = t('This !type is currently <strong>archived</strong>. You can reactivate it to allow others to add and alter its content.', array('!type' => node_get_types('name', $node->type)));
    }
    $form['archive'] = array(
      '#type' => 'fieldset',
      '#description' => $archive_help,
      '#weight' => 100,
    );
    $form['archive']['button'] = array(
      '#type' => 'submit',
      '#value' => $node->status ? t('Archive this !type', array('!type' => node_get_types('name', $node->type))) : t('Reactivate'),
      '#submit' => $node->status ? array('atrium_archive_submit') : array('atrium_reactivate_submit'),
    );
  }
  // Disable other node forms in archived spaces
  else if (atrium_is_archived($space)) {
    drupal_access_denied(); exit;
  }

  // Even if you have the perms, we don't want you messing with this stuff
  $disable = array('menu', 'comment_settings');
  foreach ($disable as $key) {
    if (!empty($form[$key])) {
      $form[$key]['#access'] = FALSE;
    }
  }
}

/**
 * Implementation of hook_form_alter for spaces_features_form.
 */
function _atrium_form_spaces_features_form_alter(&$form, $form_state) {
  $space = spaces_get_space();
  if (!$space) {
    $form['atrium'] = array(
      '#type' => 'fieldset',
      '#title' => t('Site settings'),
      '#tree' => FALSE,
    );
    $form['atrium']['user_register'] = array(
      '#title' => t('Site mode'),
      '#type' => 'select',
      '#description' => t('Choose the access level for the site.'),
      '#options' => array(
        0 => t('Private access only'),
        1 => t('Public access, open registration'),
        2 => t('Public access, moderated registration'),
      ),
      '#default_value' => variable_get('user_register', 0),
    );
    $form['atrium']['atrium_members'] = array(
      '#title' => t('Members'),
      '#type' => 'select',
      '#description' => t('Choose the access mode for the member directory and profiles. Administrators and managers will be able to see all members regardless of this setting.'),
      '#options' => array(
        ATRIUM_MEMBERS_ALL=> t('Users can view all members'),
        ATRIUM_MEMBERS_GROUP => t('Users can only view members that belong to their groups')
      ),
      '#default_value' => variable_get('atrium_members', ATRIUM_MEMBERS_ALL),
    );
    $form['#submit'][] = 'atrium_form_spaces_features_form_submit';
  }
}

/**
 * Implementation of hook_form_alter for system_themes_form.
 * Limit options to themes that implement atrium compatibility.
 */
function _atrium_form_system_themes_form_alter(&$form, $form_state) {
  $themes = system_theme_data();
  foreach ($themes as $key => $theme) {
    if (empty($theme->info['atrium'])) {
      unset($form[$key]);
      unset($form['status']['#options'][$key]);
      unset($form['theme_default']['#options'][$key]);
    }
  }
}

/**
 *  Implementation of hook_form_alter for node_type_form.
 */
function _atrium_form_node_type_form_alter(&$form, $form_state) {
  if (isset($form['identity']['type'])) {
    $form['atrium'] = array(
      '#type' => 'fieldset',
      '#title' => t('Atrium'),
      '#tree' => FALSE,
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['atrium']['atrium_update_type'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show in recent activity views'),
      '#description' => t('Show this content type in activity streams, update lists, etc.'),
      '#default_value' => variable_get('atrium_update_type_'. $form['#node_type']->type, TRUE),
    );
  }
}

/**
 * Form alter for views exposed forms.
 */
function _atrium_form_views_exposed_form_alter(&$form, $form_state) {
  // Quick check that this is the right view
  $view = views_get_current_view();
  if ($view && $view->name === 'atrium_search' && !empty($form['created'])) {
    $options = array(
      '-14 days' => t('2 weeks ago'),
      '-30 days' => t('1 month ago'),
      '-180 days' => t('6 month ago'),
      '' => t('Anytime'),
    );
    $form['created']['#type'] = 'select';
    $form['created']['#options'] = $options;
    unset($form['created']['#size']);
  }
}

/**
 * Menu callback for reactivation confirmation form.
 */
function atrium_reactivate($form_state, $node) {
  $form = array();
  $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
  $form['#submit'] = array('atrium_reactivate_submit');
  return confirm_form($form, t('Are you sure you want to reactivate %title?', array('%title' => $node->title)), "node/{$node->nid}", '', t('Reactivate'), t('Cancel'));
}

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
    $firstgroup = variable_get('atrium_firstgroup', FALSE);
    if (!$firstgroup) {
      if ($result = db_result(db_query("SELECT count(*) FROM {node} WHERE type = 'group'"))) {
        variable_set('atrium_firstgroup', TRUE);
        $firstgroup = TRUE;
      }
    }
    if ($firstgroup) {
      menu_set_active_item('dashboard');
      return menu_execute_active_handler();
    }
    else {
      drupal_set_title(t('Welcome to !sitename', array('!sitename' => variable_get('site_name', 'Atrium'))));

      $output = "<div class='view-empty'>";
      if (node_access('create', 'group')) {
        $output .= t('Create your first !type to get started.', array('!type' => node_get_types('name', 'group')));
        $output .= "<div class='buttons'>". l(t('Create !type', array('!type' => node_get_types('name', 'group'))), 'node/add/group', array('attributes' => array('class' => 'button'))) ."</div>";
      }
      else {
        $output .= t('The site administator has not finished setting up this site. Please be patient and try again later.');
      }
      $output .= "</div>";

      return $output;
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
 * Redirect the user to their dashboard.
 */
function atrium_dashboard_redirect() {
  global $user;
  if ($user->uid != 0) {
   drupal_goto("user/{$user->uid}/dashboard");
  }
  drupal_goto("dashboard");
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

/**
 * 403 page.
 */
function atrium_403() {
  // If we're in intranet mode, send anonymous users to a login screen.
  global $user;
  if (!$user->uid && !user_access('access content')) {
    // drupal_access_denied() sets the $_REQUEST['destination'] which will
    // prevent drupal_goto from behaving as expected. So we unset it.
    unset($_REQUEST['destination']);
    drupal_goto('user/login', 'destination='. $_REQUEST['q']);
  }
  return "<div class='access-denied'>". t('You are not authorized to access this page.') ."</div>";
}
