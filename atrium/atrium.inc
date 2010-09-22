<?php

/**
 * Form alter callback for comment form.
 */
function _atrium_form_comment_form_alter(&$form, $form_state) {
  // Hide display of the "Your name" field.
  if (isset($form['_author'])) {
    $form['_author']['#access'] = FALSE;
  }
  $form['comment_filter']['comment']['#rows'] = 8;

  // Drupal 6.14 introduced a form cache bug. Using the workaround describe on
  // http://drupal.org/node/579900#comment-2081404
  if (isset($form['preview']) && $form['preview']['#type'] == 'button') {
    $form['preview']['#type'] = 'submit';
  }
}

/**
 * Form alter callback for node form.
 */
function _atrium_form_node_form_alter(&$form, $form_state) {
  $node = $form['#node'];

  // Path alias UI adjustments.
  // Ideally this would live in PURL, but PURL is weighted too light for this
  // form_alter() which must occur after path.
  if (module_exists('path')) {
    $space = spaces_get_space();
    if ($space && $space->type === 'og' && isset($form['path']['path'])) {
      switch (variable_get('purl_method_spaces_og', 'path')) {
        case 'path':
          $form['path']['path']['#size'] = '28';
          $form['path']['path']['#field_prefix'] = "{$space->group->purl}/";
          break;
        case 'pair':
          $key = variable_get('purl_method_spaces_og_key', FALSE);
          $form['path']['path']['#size'] = '28';
          $form['path']['path']['#field_prefix'] = "{$key}/{$space->id}/";
          break;
      }
    }
  }

  // Disable node forms in archived spaces.
  $space = spaces_get_space();
  if (!atrium_archivable($node) && $space && $space->type === 'og' && !$space->group->status) {
    drupal_access_denied(); exit;
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
        ATRIUM_MEMBERS_ALL => t('Users can view all members'),
        ATRIUM_MEMBERS_GROUP => t('Users can only view members that belong to their groups')
      ),
      '#default_value' => variable_get('atrium_members', ATRIUM_MEMBERS_ALL),
    );
    $form['atrium']['atrium_notifications'] = array(
      '#title' => t('Notifications'),
      '#type' => 'select',
      '#description' => t('Choose the notifications UI for this site.'),
      '#options' => array(
        ATRIUM_NOTIFICATIONS_TEAM => t('Small team: authors subscribe others to their posts'),
        ATRIUM_NOTIFICATIONS_SUBSCRIBE => t('Community: users subscribe to posts on their own')
      ),
      '#default_value' => variable_get('atrium_notifications', ATRIUM_NOTIFICATIONS_TEAM),
    );
    $form['#submit'][] = 'atrium_form_spaces_features_form_submit';
  }
  elseif ($space->type == 'user') {
    unset($form['designkit_color']);
    unset($form['designkit_image']);
  }
}

/**
 * Implementation of hook_form_alter for system_themes_form.
 * Limit options to themes that implement atrium compatibility.
 */
function _atrium_form_system_themes_form_alter(&$form, $form_state) {
  $themes = system_theme_data();
  $hidden = FALSE;
  foreach ($themes as $key => $theme) {
    if (empty($theme->info['atrium']) && !variable_get('atrium_show_all_themes', FALSE)) {
      unset($form[$key]);
      unset($form['status']['#options'][$key]);
      unset($form['theme_default']['#options'][$key]);
    }
  }
  $form['atrium'] = array(
    '#type' => 'fieldset',
    '#description' => variable_get('atrium_show_all_themes', FALSE) ?
        t('All themes, including those incompatible with Atrium, are shown above.') :
        t('Themes that are not compatible with Atrium have been hidden.'),
  );
  $form['atrium']['toggle'] = array(
    '#type' => 'submit',
    '#value' => variable_get('atrium_show_all_themes', FALSE) ? t('Show only compatible themes') : t('Show all themes'),
    '#submit' => array('atrium_system_themes_form_submit'),
  );
}

/**
 * Implementation of hook_form_alter() for user_login.
 */
function _atrium_form_user_login_alter(&$form, $form_state) {
  // If user has no destination set or user/login (a bad one), send to homepage post login.
  // See user module login block for the use of [#action] to force a redirect.
  $dest = isset($_GET['destination']) ? $_GET['destination'] : '';
  if (!$dest || $dest == 'user/login') {
    $path = variable_get('site_frontpage', 'node');
    $form['#redirect'] = $path;
  }
}

/**
 * Form alter for views exposed forms.
 */
function _atrium_form_views_exposed_form_alter(&$form, $form_state) {
  // Quick check that this is the right view
  $view = views_get_current_view();
  if ($view && $view->name === 'search_listing' && !empty($form['created'])) {
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
 * Menu callback for archive confirmation form.
 */
function atrium_archive($form_state, $node) {
  $form = array();
  $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
  $form['#submit'] = array('atrium_archive_submit');
  return confirm_form($form, t('Are you sure you want to archive %title?', array('%title' => $node->title)), "node/{$node->nid}", '', t('Archive'), t('Cancel'));
}

/**
 * OG archive submit handler.
 * Test: AtriumTest->testArchive().
 */
function atrium_archive_submit($form, &$form_state) {
  $nid = $form_state['values']['nid'];
  $node = node_load($nid);
  $node->status = 0;
  node_save($node);
  drupal_set_message(t('The @type @title has been archived.', array('@type' => node_get_types('name', $node->type), '@title' => $node->title)));
  if (og_is_group_type($node->type)) {
    purl_goto('<front>', array('purl' => array('provider' => 'spaces_og', 'id' => $nid)));
  }
  else {
    $form_state['redirect'] = "node/$nid";
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
 * Reactivate node submit handler.
 * Test: AtriumTest->testArchive().
 */
function atrium_reactivate_submit($form, &$form_state) {
  $nid = $form_state['values']['nid'];
  $node = node_load($nid);
  $node->status = 1;
  node_save($node);
  drupal_set_message(t('The @type @title has been reactivated.', array('@type' => node_get_types('name', $node->type), '@title' => $node->title)));
  if (og_is_group_type($node->type)) {
    purl_goto('<front>', array('purl' => array('provider' => 'spaces_og', 'id' => $nid)));
  }
  else {
    $form_state['redirect'] = "node/$nid";
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
 * 403 page.
 * Test: AtriumTest->test403().
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
  else {
    // Logged in user requests path like 'user/login?destination=dashboard' which
    // is a common case if user loses session but has 46 browser tabs open and
    // refreshes one such tab.  This will redirect that request properly to
    // avoid a 403.
    if ($_REQUEST['q'] === 'user/login' && isset($_REQUEST['destination']) && $_REQUEST['destination'] !== 'user/login') {
      drupal_goto($_REQUEST['q']);
    }
  }
  return "<div class='access-denied'>". t('You are not authorized to access this page.') ."</div>";
}

/**
 * 404 page.
 */
function atrium_404() {
  return "<div class='not-found'>". t('The requested page could not be found.') ."</div>";
}
