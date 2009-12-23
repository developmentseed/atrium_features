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
  if ($user->uid != 0 && !user_access('administer nodes') && $view->base_table == 'node') {
    $view->display_handler->set_option('distinct', 1);
  }

  switch ($view->name) {
    // Improve book contextuality
    // This alter checks the current active context and only allows
    // root books in that context's content types to be displayed/selected.
    // This is critical to siloing each book enabled content type to
    // their respective features while allowing child book pages to be
    // nested under them. See hook_nodeapi() for the companion functionality
    // which sets the active context based on the root book type.
    case 'atrium_book_current':
      if (context_get('atrium', 'book') === 'rendering') {
        $filters = $view->display_handler->get_option('filters');
        $filters['feature'] = array(
          'operator' => '=',
          'value' => '',
          'group' => '0',
          'exposed' => FALSE,
          'expose' => array(
            'operator' => FALSE,
            'label' => '',
          ),
          'id' => 'feature',
          'table' => 'node',
          'field' => 'feature',
        );
        $view->display_handler->set_option('filters', $filters);
      }
      break;
  }
}

/**
 * Implementation of hook_views_plugins().
 */
function atrium_views_plugins() {
  return array(
    'module' => 'atrium',
    'access' => array(
      'atrium_feature' => array(
        'title' => t('Atrium feature (advanced)'),
        'help' => t('Extends Spaces feature access control for additional custom access checks.'),
        'handler' => 'atrium_plugin_access_atrium_feature',
        'path' => drupal_get_path('module', 'atrium') .'/includes',
        'uses options' => TRUE,
        'parent' => 'spaces_feature',
      ),
    ),
  );
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
      'atrium_handler_filter_update_types' => array(
        'parent' => 'views_handler_filter',
      ),
      'atrium_handler_field_file' => array(
        'parent' => 'views_handler_field_file',
       ),
      'atrium_handler_field_ncs_last_updated' => array(
        'parent' => 'seed_handler_field_date',
       ),
      'atrium_handler_field_og_group_nids' => array(
        'parent' => 'views_handler_field',
       ),
      'atrium_handler_filter_og_group_nid' => array(
        'parent' => 'views_handler_filter_equality',
       ),
      'atrium_handler_field_og_post_count_new' => array(
        'parent' => 'views_handler_field_numeric',
       ),
      'atrium_handler_filter_user_list' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'atrium_handler_argument_node_created_shortdate' => array(
        'parent' => 'views_handler_argument_date',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function atrium_views_data() {
  $data = array();

  // UID
  $data['users']['uid_list'] = array(
    'real field' => 'uid',
    'title' => t('Include/exclude UIDs'),
    'help' => t('Filter the view to include or exclude by UID.'),
    'filter' => array(
      'handler' => 'atrium_handler_filter_user_list',
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

  // Search & destroy operations
  $cache['og_ancestry']['group_nid']['field']['handler'] = 'atrium_handler_field_og_group_nids';
  $cache['og_ancestry']['group_nid']['filter']['handler'] = 'atrium_handler_filter_og_group_nid';
  $cache['og']['post_count_new']['field']['handler'] = 'atrium_handler_field_og_post_count_new';
  
  // Add a sort by user access history
  $cache['history_user']['timestamp']['sort']['handler'] = 'views_handler_sort';
  $cache['history_user']['timestamp']['sort']['help'] = t('Sort items by current user\'s latest access time');

  // Alias -- copy of created_fulldate but with simpler formatting
  $cache['node']['created_shortdate'] = array(
    'title' => t('Created date (short)'),
    'help' => t('In the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'atrium_handler_argument_node_created_shortdate',
    ),
  );

  // Update type filter
  $cache['node']['update_type'] = array(
    'real field' => 'type',
    'title' => t('Atrium update types'),
    'help' => t('Affects only content types designated as update types.'),
    'filter' => array(
      'handler' => 'atrium_handler_filter_update_types',
    ),
  );
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
