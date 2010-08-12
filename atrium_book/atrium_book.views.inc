<?php

/**
 * Implementation of hook_views_handlers().
 */
function atrium_book_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'atrium_book') .'/includes',
    ),
    'handlers' => array(
      'atrium_book_handler_filter_book_types' => array(
        'parent' => 'views_handler_filter',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data_alter().
 */
function atrium_book_views_data_alter(&$cache) {
  // Book enabled type filter
  $cache['node']['book_type'] = array(
    'real field' => 'type',
    'title' => t('Book-enabled types'),
    'help' => t('Affects only book-enabled content types.'),
    'filter' => array(
      'handler' => 'atrium_book_handler_filter_book_types',
    ),
  );
}