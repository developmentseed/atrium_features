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
      'atrium_handler_field_group' => array(
        'parent' => 'views_handler_field',
      ),
      'atrium_handler_field_ncs_last_updated' => array(
        'parent' => 'seed_handler_field_date',
      ),
      'atrium_handler_field_og_group_nids' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function atrium_views_data() {
  $data = array();
  // Group space link
  $data['node']['atrium_group'] = array(
    'real field' => 'title',
    'title' => t('Group space'),
    'help' => t("Provide link to a group node's space."),
    'field' => array('handler' => 'atrium_handler_field_group'),
  );

  // A second entry for og_ancestry, to add an optional group display handler.
  $data['atrium_og_ancestry']['table']['group']  = t('Organic groups');
  $data['atrium_og_ancestry']['table']['join'] = array(
    'node' => array(
      'table' => 'og_ancestry',
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['atrium_og_ancestry']['group_nid'] = array(
    'title' => t('Groups (color-coded)'),
    'help' => t('The groups for a post.'),
    'field' => array(
      'handler' => 'atrium_handler_field_og_group_nids',
    ),
  );

  // A second entry for the history table, see node.views.inc for the first.
  $data['history_user2']['table']['group']  = t('Node');
  $data['history_user2']['table']['join'] = array(
     // Directly links to node table.
    'node' => array(
      'table' => 'history',
      'left_field' => 'nid',
      'field' => 'nid',
      'extra' => array(
        array('field' => 'uid', 'value' => '***CURRENT_USER***', 'numeric' => TRUE),
      ),
    ),
  );
  $data['history_user2']['timestamp'] = array(
    'title' => t('Last viewed by current user'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  return $data;
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
            case 'views_handler_field_ncs_last_updated':
              $cache[$module][$column][$property]['handler'] = 'atrium_handler_field_ncs_last_updated';
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