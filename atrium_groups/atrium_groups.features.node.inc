<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_groups_node_info() {
  $items = array(
    'group' => array(
      'name' => t('Group'),
      'module' => 'features',
      'description' => t('A group space for members to coordinate, collaborate and share ideas.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
