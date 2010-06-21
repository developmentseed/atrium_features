<?php

/**
 * Custom autocomplete callback that retrieves all users that a user has
 * access to see. Differs from user_autocomplete() only in that it pushes
 * the query through db_rewrite_sql().
 */
function atrium_members_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = "SELECT uid, name FROM {users} WHERE LOWER(name) LIKE LOWER('%s%%')";
    $query = db_rewrite_sql($query, 'users', 'uid', array($string));
    $result = db_query_range($query, $string, 0, 10);
    while ($user = db_fetch_object($result)) {
      $matches[$user->name] = check_plain($user->name);
    }
  }
  drupal_json($matches);
}

/**
 * Form for adding existing members to a group.
 */
function atrium_members_addform($form_state, $group) {
  $form = array('#theme' => 'atrium_members_addform');
  $form['messages'] = array('#type' => 'markup');

  // Provide the page View for AJAX reload action.
  if ($display = views_get_page_view()) {
    if ($display->get_option('use_ajax')) {
      $form['view'] = array(
        '#type' => 'hidden',
        '#value' => "{$display->view->name}:{$display->view->current_display}",
        '#attributes' => array('class' => 'atrium-members-addform-view'),
      );
    }
  }

  $form['group'] = array(
    '#type' => 'value',
    '#value' => $group,
  );
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => '',
    '#autocomplete_path' => 'members/add/autocomplete',
    '#description' => '',
  );
  $form['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add to group'),
    '#submit' => array('atrium_members_addform_submit'),
    '#ahah' => array(
      'path' => 'members/add/ajax',
      'wrapper' => 'atrium-members-addform-messages',
      'method' => 'replace',
      'effect' => 'none',
    ),
  );
  return $form;
}

/**
 * Theme function for atrium_members_addform().
 */
function theme_atrium_members_addform($form) {
  drupal_add_js(drupal_get_path('module', 'atrium_members') .'/atrium_members.js');
  $output = "<div id='atrium-members-addform-messages'>";
  $output .= drupal_render($form['messages']);
  $output .= "</div>";
  $output .= drupal_render($form);
  return "<div class='atrium-members-addform'>{$output}</div>";
}

/**
 * Submit handler for member addform.
 */
function atrium_members_addform_submit(&$form, &$form_state) {
  if ($uid = db_result(db_query("SELECT uid FROM {users} WHERE name = '%s'", $form_state['values']['username']))) {
    if ($account = user_load($uid)) {
      og_save_subscription($form_state['values']['group']->nid, $account->uid, array('is_active' => 1));
      drupal_set_message(t('Subscribed user %name to %group.', array('%name' => $account->name, '%group' => $form_state['values']['group']->title)));
    }
  }
}

/**
 * AJAX/AHAH callback for user addform submission.
 */
function atrium_members_addform_ajax() {
  if ($form = form_get_cache($_POST['form_build_id'], $form_state)) {
    // Build submitted values.
    $form_state = array('values' => $_POST);
    foreach (element_children($form) as $key) {
      if ($form[$key]['#type'] === 'value' && isset($form[$key]['#value'])) {
        $form_state['values'][$key] = $form[$key]['#value'];
      }
    }
    // Submit the form & retrieve messages.
    atrium_members_addform_submit($form, $form_state);
    $output = theme('status_messages');
    $output = "<div class='atrium-members-ajax'>{$output}</div>";
    drupal_json(array('status' => TRUE, 'data' => $output));
    exit();
  }
  drupal_json(array('status' => FALSE, 'data' => ''));
  exit();
}

/**
 * Page callback for og users.
 */
function atrium_members_og_users() {
  menu_set_active_item('members');
  return menu_execute_active_handler();
}

/**
 * Form callback that generates only the portion of the user profile form that is requested.
 */
function atrium_members_user_profile_tab($form_state, $account, $tab) {
  module_load_include('inc', 'user', 'user.pages');
  $form = user_profile_form($form_state, $account);
  $form['#submit'] = array('user_profile_form_submit');
  foreach (element_children($form) as $k) {
    if ($k == $tab || $form[$k]['#type'] == 'submit') {
      $form[$k]['#access'] = TRUE;
    }
    else {
      $form[$k]['#access'] = FALSE;
    }
  }
  if (isset($form['delete'])) {
    $form['delete']['#access'] = FALSE;
  }
  return $form;
}
