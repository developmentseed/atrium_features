<?php
// $Id$

/**
 * Implementation of hook_views_pre_build().
 */
function atrium_views_pre_build(&$view) {
  // When OG public nodes are in play it is (very) possible to get
  // duplicate rows because of the node_access() JOIN and WHERE
  // combination. This is a rather brute force method of making
  // sure this doesn't affect our Views without going through every
  // default view and setting the distinct flag.
  global $user;
  if ($user->uid != 0 && !user_access('administer nodes') && in_array($view->base_table, array('node', 'comments'), TRUE)) {
    $view->display_handler->set_option('distinct', 1);
  }
}

/**
 * Implementation of hook_views_handlers().
 */
function atrium_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'atrium') .'/includes',
    ),
    'handlers' => array(
      'atrium_handler_filter_book_types' => array(
        'parent' => 'views_handler_filter',
      ),
      'atrium_handler_field_file' => array(
        'parent' => 'views_handler_field_file',
       ),
    ),
  );
}

/**
 * Implementation of hook_views_data_alter().
 *
 * Replaces default views date field formatters with special-sauce atrium
 * date field formatters.
 */
function atrium_views_data_alter(&$cache) {
  foreach ($cache as $module => $a) {
    foreach ($a as $column => $b) {
      foreach ($b as $property => $c) {
        if ($property == 'field' && !empty($c['handler'])) {
          switch ($c['handler']) {
            case 'views_handler_field_file':
              $cache[$module][$column][$property]['handler'] = 'atrium_handler_field_file';
              break;
          }
        }
      }
    }
  }

  // Book enabled type filter
  $cache['node']['book_type'] = array(
    'real field' => 'type',
    'title' => t('Book-enabled types'),
    'help' => t('Affects only book-enabled content types.'),
    'filter' => array(
      'handler' => 'atrium_handler_filter_book_types',
    ),
  );
}
