<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_casetracker_node_info() {
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
