<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_book_node_info() {
  $items = array(
    'book' => array(
      'name' => t('Book page'),
      'module' => 'features',
      'description' => t('A <em>book page</em> is a page of content, organized into a collection of related entries collectively known as a <em>book</em>. A <em>book page</em> automatically displays links to adjacent pages, providing a simple navigation system for organizing and reviewing structured content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
