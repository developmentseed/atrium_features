<?php

/**
 * Helper to implementation of hook_views_default_views().
 */
function _atrium_dashboard_views_default_views() {
  $views = array();

  // Exported view: atrium_dashboard
  $view = new view;
  $view->name = 'atrium_dashboard';
  $view->description = 'Atrium > Dashboard';
  $view->tag = 'atrium';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'group_nid' => array(
      'label' => '',
      'exclude' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'empty' => '',
      'id' => 'group_nid',
      'table' => 'og_ancestry',
      'field' => 'group_nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'feature' => array(
      'label' => '',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'feature',
      'table' => 'spaces_node',
      'field' => 'feature',
      'relationship' => 'none',
    ),
    'last_updated' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'time',
      'custom_date_format' => 'g:i a',
      'exclude' => 0,
      'id' => 'last_updated',
      'table' => 'node_comment_statistics',
      'field' => 'last_updated',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'timestamp' => array(
      'label' => '',
      'link_to_node' => 0,
      'comments' => 0,
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'history_user',
      'field' => 'timestamp',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'last_comment_name' => array(
      'label' => '',
      'link_to_user' => TRUE,
      'exclude' => 0,
      'id' => 'last_comment_name',
      'table' => 'node_comment_statistics',
      'field' => 'last_comment_name',
      'relationship' => 'none',
    ),
    'last_updated_1' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'day',
      'custom_date_format' => 'l, M j',
      'exclude' => 1,
      'id' => 'last_updated_1',
      'table' => 'node_comment_statistics',
      'field' => 'last_updated',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'last_updated' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'last_updated',
      'table' => 'node_comment_statistics',
      'field' => 'last_updated',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'current' => array(
      'operator' => 'active',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'current',
      'table' => 'spaces',
      'field' => 'current',
      'relationship' => 'none',
    ),
    'update_type' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'update_type',
      'table' => 'node',
      'field' => 'update_type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'spaces_feature',
    'spaces_feature' => 'atrium_dashboard',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Dashboard');
  $handler->override_option('empty', 'No recent activity found.');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => 'last_updated_1',
    'override' => 0,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'group_nid' => 'group_nid',
      'last_updated' => 'last_updated',
      'feature' => 'feature',
      'title' => 'title',
      'last_comment_name' => 'last_comment_name',
      'last_updated_1' => 'last_updated_1',
      'timestamp' => 'last_comment_name',
    ),
    'info' => array(
      'group_nid' => array(
        'separator' => '',
      ),
      'last_updated' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'feature' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_comment_name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_updated_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'timestamp' => array(
        'separator' => '',
      ),
    ),
    'default' => 'last_updated_1',
  ));
  $handler = $view->new_display('page', 'All activity', 'page_1');
  $handler->override_option('path', 'dashboard/all');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'All activity',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'All activity',
    'description' => '',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'My threads', 'page_2');
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'uid_current' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'uid_current',
      'table' => 'notifications',
      'field' => 'uid_current',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'current' => array(
      'operator' => 'active',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'current',
      'table' => 'spaces',
      'field' => 'current',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'update_type' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'update_type',
      'table' => 'node',
      'field' => 'update_type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'atrium_feature',
    'spaces_feature' => 'atrium_dashboard',
    'perm' => 'subscribe to content',
  ));
  $handler->override_option('path', 'dashboard/my');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'My threads',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Home',
    'description' => '',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'Files', 'page_3');
  $handler->override_option('relationships', array(
    'upload_fid' => array(
      'label' => 'Files',
      'required' => 1,
      'id' => 'upload_fid',
      'table' => 'node',
      'field' => 'upload_fid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'group_nid' => array(
      'label' => '',
      'exclude' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'empty' => '',
      'id' => 'group_nid',
      'table' => 'og_ancestry',
      'field' => 'group_nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'filemime' => array(
      'label' => '',
      'link_to_file' => 1,
      'exclude' => 0,
      'id' => 'filemime',
      'table' => 'files',
      'field' => 'filemime',
      'relationship' => 'upload_fid',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'filename' => array(
      'label' => '',
      'link_to_file' => 1,
      'exclude' => 0,
      'id' => 'filename',
      'table' => 'files',
      'field' => 'filename',
      'relationship' => 'upload_fid',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'title' => array(
      'label' => '',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'last_updated' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'time',
      'custom_date_format' => 'g:i a',
      'exclude' => 0,
      'id' => 'last_updated',
      'table' => 'node_comment_statistics',
      'field' => 'last_updated',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'last_comment_name' => array(
      'label' => '',
      'link_to_user' => TRUE,
      'exclude' => 0,
      'id' => 'last_comment_name',
      'table' => 'node_comment_statistics',
      'field' => 'last_comment_name',
      'relationship' => 'none',
    ),
    'last_updated_1' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'day',
      'custom_date_format' => 'l, M j',
      'exclude' => 1,
      'id' => 'last_updated_1',
      'table' => 'node_comment_statistics',
      'field' => 'last_updated',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('style_options', array(
    'grouping' => 'last_updated_1',
    'override' => 0,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'group_nid' => 'group_nid',
      'filemime' => 'filemime',
      'filename' => 'filename',
      'title' => 'filename',
      'last_updated' => 'last_updated',
      'last_comment_name' => 'last_comment_name',
      'last_updated_1' => 'last_updated_1',
    ),
    'info' => array(
      'group_nid' => array(
        'separator' => '',
      ),
      'filemime' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'filename' => array(
        'sortable' => 0,
        'separator' => '<br/>',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_updated' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_comment_name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_updated_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => 'last_updated_1',
  ));
  $handler->override_option('path', 'dashboard/files');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Files',
    'description' => '',
    'weight' => '2',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'All activity (block)', 'block_1');
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'current' => array(
      'operator' => 'active',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'current',
      'table' => 'spaces',
      'field' => 'current',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'update_type' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'update_type',
      'table' => 'node',
      'field' => 'update_type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Recent activity');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 15);
  $handler->override_option('use_pager', '0');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $translatables['atrium_dashboard'] = array(
    t('Defaults'),
    t('Dashboard'),
    t('No recent activity found.'),
    t('All activity'),
    t('My threads'),
    t('Files'),
    t('All activity (block)'),
    t('Recent activity'),
  );

  $views[$view->name] = $view;

  return $views;
}
