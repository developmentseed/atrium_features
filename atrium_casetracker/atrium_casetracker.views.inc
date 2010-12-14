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
      'atrium_casetracker_handler_field_priority_name' => array(
         'parent' => 'views_handler_field',
      ),
      'atrium_casetracker_handler_filter_status_closed' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      'atrium_casetracker_handler_sort_status_closed' => array(
        'parent' => 'views_handler_sort',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data_alter().
 * Replaces default field formatters with special-sauce field formatters.
 */
function atrium_casetracker_views_data_alter(&$data) {
  if (isset($data['casetracker_case'])) {
    $data['casetracker_case']['case_status_closed'] = array(
      'title' => t('Show closed cases'),
      'filter' => array(
        'field' => 'case_status_id',
        'handler' => 'atrium_casetracker_handler_filter_status_closed',
        'help' => t('Filter out closed cases.'),
      ),
    );
  }
  if (isset($data['casetracker_case_states'])) {
    $data['casetracker_case_states']['case_status_closed'] = array(
      'title' => t('Closed Case Status'),
      'real field' => 'csid',
      'sort' => array(
        'field' => 'csid',
        'handler' => 'atrium_casetracker_handler_sort_status_closed',
        'help' => t('Sort by Case Active/Inactive status.'),
      ),
    );
  }
  if (isset($data['casetracker_case']['case_priority_id']['field']['handler'])) {
    $data['casetracker_case']['case_priority_id']['field']['handler'] = 'atrium_casetracker_handler_field_priority_name';
  }
}
