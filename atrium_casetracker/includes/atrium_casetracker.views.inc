<?php
// $Id$

/**
 * Implementation of hook_views_pre_build().
 */
function atrium_casetracker_views_pre_build(&$view) {
  switch ($view->name) {
    // Smarts for user space
    case 'atrium_casetracker':
    case 'atrium_casetracker_mycases':
      $space = spaces_get_space();
      if ($space && $space->type == 'user') {
        $filters = $view->display[$view->current_display]->display_options['filters'];
        // Clear out the spaces filter
        if (!empty($filters['current'])) {
          unset($filters['current']);
        }
        // Ensure that the assigned to user filter points at the current user space
        if (!empty($filters['assign_to'])) {
          $filters['assign_to']['exposed'] = FALSE;
          $filters['assign_to']['value'] = $space->sid;
        }
        $handler = $view->display[$view->current_display]->handler;
        $handler->override_option('filters', $filters);
      }
      break;
    // Project book logic
    // We will hide project books from book listing displays as casetracker
    // provides its own display.
  }
}

/**
 * Implementation of hook_views_handlers().
 */
function atrium_casetracker_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'atrium_casetracker') .'/includes',
    ),
    'handlers' => array(
      'atrium_casetracker_handler_field_project_name' => array(
         'parent' => 'views_handler_field',
      ),
      'atrium_casetracker_handler_field_priority_name' => array(
         'parent' => 'views_handler_field',
      ),
      'atrium_casetracker_handler_filter_status_closed' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function atrium_casetracker_views_data() {
  $data = array();

  // A second entry for the history table, see node.views.inc for the first.
  $data['casetracker_case2']['table']['group']  = t('Case Tracker');
  $data['casetracker_case2']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
      'table' => 'casetracker_case',
    ),
  );
  $data['casetracker_case2']['case_status_closed'] = array(
    'title' => t('Case Tracker: Show closed cases'),
    'filter' => array(
      'field' => 'case_status_id',
      'handler' => 'atrium_casetracker_handler_filter_status_closed',
      'help' => t('Filter out closed cases.'),
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 *
 * Replaces default field formatters with special-sauce field formatters.
 */
function atrium_casetracker_views_data_alter(&$cache) {
  // Search & destroy operations
  $cache['casetracker_case']['pid']['field']['handler'] = 'atrium_casetracker_handler_field_project_name';
  $cache['casetracker_case']['case_priority_id']['field']['handler'] = 'atrium_casetracker_handler_field_priority_name';
}
