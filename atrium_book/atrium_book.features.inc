<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_book_ctools_plugin_api() {
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
function atrium_book_node_info() {
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

/**
 * Implementation of hook_views_api().
 */
function atrium_book_views_api() {
  return array(
    'api' => '2',
  );
}
