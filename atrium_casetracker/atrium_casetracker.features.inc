<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_casetracker_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function atrium_casetracker_node_info() {
  $items = array(
    'casetracker_basic_case' => array(
      'name' => t('Case'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => t('Open a new case assigned to a particular project.'),
    ),
    'casetracker_basic_project' => array(
      'name' => t('Project'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => t('Create a project for use with Case Tracker.'),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function atrium_casetracker_views_api() {
  return array(
    'api' => '2',
  );
}
