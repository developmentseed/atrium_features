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
      'atrium_handler_field_activity' => array(
        'parent' => 'views_handler_field',
      ),
      'atrium_handler_field_activity_timestamp' => array(
        'parent' => 'atrium_handler_field_activity',
      ),
      'atrium_handler_field_activity_upload' => array(
        'parent' => 'atrium_handler_field_activity',
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
  $data['comments']['atrium_activity'] = array(
    'real field' => 'cid',
    'title' => t('Activity'),
    'help' => t("Poor man's activity field."),
    'field' => array('handler' => 'atrium_handler_field_activity'),
  );
  $data['comments']['atrium_activity_timestamp'] = array(
    'real field' => 'cid',
    'title' => t('Activity timestamp'),
    'help' => t("Timestamp for poor man's activity field."),
    'field' => array('handler' => 'atrium_handler_field_activity_timestamp'),
  );
  $data['comments']['atrium_activity_upload'] = array(
    'real field' => 'cid',
    'title' => t('Activity upload'),
    'help' => t("Upload for poor man's activity field."),
    'field' => array('handler' => 'atrium_handler_field_activity_upload'),
  );

  // Group space link
  $data['node']['atrium_group'] = array(
    'real field' => 'title',
    'title' => t('Group space'),
    'help' => t("Provide link to a group node's space."),
    'field' => array('handler' => 'atrium_handler_field_group'),
  );

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

/**
 * Implementation of hook_views_query_alter().
 */
function atrium_views_query_alter(&$view, &$query) {
  if (!empty($view->atrium_activity)) {
    // Skip Views' query execution - we will do it ourselves.
    $view->executed = TRUE;

    $main = drupal_clone($query);
    $subquery = drupal_clone($query);
    $args = $query->get_where_args();

    // Subquery: Retrieves node posts & updates.
    // NULL any fields that reference the comments table and remove the join completely.
    foreach ($subquery->fields AS $key => $field) {
      if ($field['table'] === 'comments') {
        $subquery->fields[$key]['table'] = NULL;
        $subquery->fields[$key]['field'] = "NULL";
      }
    }
    if (isset($subquery->tables['node']['comments'])) {
      unset($subquery->tables['node']['comments']);
    }
    if (isset($subquery->table_queue['comments'])) {
      unset($subquery->table_queue['comments']);
    }
    $subquery = strtr($subquery->query(), array('***ATRIUM_ACTIVITY_TIMESTAMP***' => 'node.changed'));

    // Main: Retrieve "only" comments.

    // Because of the node_access change introduced in Drupal 6.14, distinct
    // has been added to most queries to prevent duplicate rows from appearing.
    // For this query, which pulls comments, we need to remove DISTINCT from
    // nid and add one to cid. But since cid has been pushed into the middle of
    // the field stack (and it is not easy to reorder fields), we use a
    // GROUP BY cid instead.
    $main->distinct = FALSE;
    if (isset($main->fields['comments_cid'])) {
      $main->add_groupby($main->fields['comments_cid']['alias']);
    }

    // Switch LEFT to INNER JOIN against comments table.
    if (isset($main->table_queue['comments']['join'])) {
      $main->table_queue['comments']['join']->type = 'INNER';
    }
    // Move node and comment to the beginning of the stack to ensure that any
    // joins we switch further on in the stack have access to comments table.
    $queue = array(
      'node' => $main->table_queue['node'],
      'comments' => $main->table_queue['comments'],
    );
    foreach ($main->table_queue as $k => $v) {
      if (($k !== 'node') && ($k !== 'comments')) {
        $queue[$k] = $v;
      }
    }
    $main->table_queue = $queue;
    // Alter join to the user table to go through comments,
    if (isset($main->table_queue['users']['join'])) {
      $main->table_queue['users']['join']->left_table = 'comments';
    }
    // Alter joins to the upload, files tables to go through comment_upload instead.
    if (isset($main->table_queue['upload']['join'])) {
      $main->table_queue['upload']['join']->left_table = 'comments';
      $main->table_queue['upload']['join']->left_field= 'cid';
      $main->table_queue['upload']['join']->field= 'cid';
      $main->table_queue['upload']['join']->table = 'comment_upload';
    }
    $main = strtr($main->query(), array('***ATRIUM_ACTIVITY_TIMESTAMP***' => 'comments.timestamp'));

    // SQL rewrite.
    $subquery = db_rewrite_sql($subquery, $view->base_table, $view->base_field, array('view' => &$view));
    $main     = db_rewrite_sql($main, $view->base_table, $view->base_field, array('view' => &$view));

    // Views query token replacements.
    $replacements = module_invoke_all('views_query_substitutions', $view);
    $subquery = str_replace(array_keys($replacements), $replacements, $subquery);
    $main     = str_replace(array_keys($replacements), $replacements, $main);
    if (is_array($args)) {
      foreach ($args as $id => $arg) {
        $args[$id] = str_replace(array_keys($replacements), $replacements, $arg);
      }
    }

    // UNION. We use UNION ALL (as opposed to the implied UNION DISTINCT)
    // since our two queries above should have no common rows.
    // See: http://www.mysqlperformanceblog.com/2007/10/05/union-vs-union-all-performance
    $main = str_replace('ORDER BY', " UNION ALL ({$subquery}) ORDER BY", $main);

    // Execute query and build result set.
    $count_query = "SELECT COUNT(*) FROM ($main) AS count";
    $result = pager_query($main, $view->pager['items_per_page'], 0, $count_query, array_merge($args, $args));
    while ($row = db_fetch_object($result)) {
      $view->result[] = $row;
    }
  }
}
