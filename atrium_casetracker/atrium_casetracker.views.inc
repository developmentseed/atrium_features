<?php

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
    'title' => t('Show closed cases'),
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
