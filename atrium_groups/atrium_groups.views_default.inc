<?php

/**
 * Implementation of hook_views_default_views().
 */
function atrium_groups_views_default_views() {
  $views = array();

  // Exported view: groups_listing
  $view = new view;
  $view->name = 'groups_listing';
  $view->description = 'Atrium > Groups';
  $view->tag = 'atrium';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'spaces' => array(
        'frontpage' => 1,
        'type' => 'spaces_og',
      ),
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type_groups_all' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_groups_all',
      'table' => 'og',
      'field' => 'type_groups_all',
      'relationship' => 'none',
    ),
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
    'uid' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'uid',
      'table' => 'og_uid',
      'field' => 'uid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'spaces_feature',
    'spaces_feature' => 'atrium_groups',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'My groups');
  $handler->override_option('empty', 'No groups found.');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('use_more', 0);
  $handler->override_option('use_more_text', 'View more');
  $handler->override_option('link_display', 'page_1');
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
  ));
  $handler = $view->new_display('block', 'Block: My groups (sidebar)', 'block_2');
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'access content',
  ));
  $handler->override_option('items_per_page', 15);
  $handler->override_option('block_description', 'My groups');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('page', 'Page: My groups', 'page_1');
  $handler->override_option('fields', array(
    'private' => array(
      'label' => '',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'private',
      'table' => 'og',
      'field' => 'private',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'spaces' => array(
        'frontpage' => 1,
        'type' => 'spaces_og',
      ),
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'description' => array(
      'id' => 'description',
      'table' => 'og',
      'field' => 'description',
    ),
    'created' => array(
      'label' => 'Created',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
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
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'member_count' => array(
      'label' => 'Members',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 1,
      ),
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'member_count',
      'table' => 'og',
      'field' => 'member_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'spaces_feature',
    'spaces_feature' => '0',
    'perm' => 'subscribe to content',
  ));
  $handler->override_option('use_ajax', FALSE);
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'private' => 'private',
      'title' => 'title',
      'description' => 'title',
      'created' => 'created',
      'member_count' => 'member_count',
    ),
    'info' => array(
      'private' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '<br />',
      ),
      'description' => array(
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'member_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('row_options', array());
  $handler->override_option('path', 'og/my');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'My groups',
    'description' => '',
    'weight' => '1',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Groups',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Page: Group directory', 'page_2');
  $handler->override_option('fields', array(
    'private' => array(
      'label' => '',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'private',
      'table' => 'og',
      'field' => 'private',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'spaces' => array(
        'frontpage' => 1,
        'type' => 'spaces_og',
      ),
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'description' => array(
      'id' => 'description',
      'table' => 'og',
      'field' => 'description',
    ),
    'created' => array(
      'label' => 'Created',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
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
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'member_count' => array(
      'label' => 'Members',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 1,
      ),
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'member_count',
      'table' => 'og',
      'field' => 'member_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'post_count' => array(
      'label' => 'Total posts',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
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
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 1,
      'id' => 'post_count',
      'table' => 'og',
      'field' => 'post_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'selective' => array(
      'label' => 'Type',
      'exclude' => 0,
      'id' => 'selective',
      'table' => 'og',
      'field' => 'selective',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type_groups_all' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_groups_all',
      'table' => 'og',
      'field' => 'type_groups_all',
      'relationship' => 'none',
    ),
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
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'group' => 'group',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Directory');
  $handler->override_option('empty', '');
  $handler->override_option('use_ajax', FALSE);
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'private' => 'private',
      'title' => 'title',
      'description' => 'title',
      'created' => 'created',
      'member_count' => 'member_count',
      'post_count' => 'post_count',
      'selective' => 'selective',
    ),
    'info' => array(
      'private' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '<br />',
      ),
      'description' => array(
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'member_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'post_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'selective' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'title' => 'title',
    ),
    'separator' => '',
  ));
  $handler->override_option('path', 'og/all');
  $handler->override_option('menu', array(
    'type' => 'default tab',
    'title' => 'Directory',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Groups',
    'description' => '',
    'weight' => '0',
    'name' => 'features',
  ));
  $handler = $view->new_display('page', 'Page: Archived groups', 'page_3');
  $handler->override_option('fields', array(
    'private' => array(
      'label' => '',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'private',
      'table' => 'og',
      'field' => 'private',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'spaces' => array(
        'frontpage' => 1,
        'type' => 'spaces_og',
      ),
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'description' => array(
      'label' => 'Group: Description',
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
      'truncate' => '0',
      'exclude' => 0,
      'id' => 'description',
      'table' => 'og',
      'field' => 'description',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Created',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
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
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'member_count' => array(
      'label' => 'Members',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 1,
      ),
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'member_count',
      'table' => 'og',
      'field' => 'member_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'selective' => array(
      'label' => 'Type',
      'exclude' => 0,
      'id' => 'selective',
      'table' => 'og',
      'field' => 'selective',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type_groups_all' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_groups_all',
      'table' => 'og',
      'field' => 'type_groups_all',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => 0,
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
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'uid' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'uid',
      'table' => 'og_uid',
      'field' => 'uid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'spaces_feature',
    'spaces_feature' => 'atrium_groups',
    'perm' => 'administer nodes',
  ));
  $handler->override_option('title', 'Archived groups');
  $handler->override_option('empty', 'No archived groups found.');
  $handler->override_option('use_ajax', FALSE);
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'private' => 'private',
      'title' => 'title',
      'description' => 'title',
      'created' => 'created',
      'member_count' => 'member_count',
      'selective' => 'selective',
    ),
    'info' => array(
      'private' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '<br />',
      ),
      'description' => array(
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'member_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'selective' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('path', 'og/archived');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Archived',
    'description' => '',
    'weight' => '2',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('block', 'Block: User groups', 'block_1');
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '%1\'s groups',
      'breadcrumb' => '',
      'default_argument_type' => 'user',
      'default_argument' => '',
      'validate_type' => 'user',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'og_uid',
      'field' => 'uid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'book' => 0,
        'event' => 0,
        'feed_ical' => 0,
        'feed_ical_item' => 0,
        'group' => 0,
        'profile' => 0,
        'shoutbox' => 0,
        'casetracker_basic_case' => 0,
        'casetracker_basic_project' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
      'validate_argument_group_node_type' => array(
        'group' => 0,
      ),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type_groups_all' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_groups_all',
      'table' => 'og',
      'field' => 'type_groups_all',
      'relationship' => 'none',
    ),
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
  ));
  $handler->override_option('block_description', 'User groups');
  $handler->override_option('block_caching', -1);
  $translatables['groups_listing'] = array(
    t('Archived groups'),
    t('Block: My groups (sidebar)'),
    t('Block: User groups'),
    t('Defaults'),
    t('Directory'),
    t('My groups'),
    t('No archived groups found.'),
    t('No groups found.'),
    t('Page: Archived groups'),
    t('Page: Group directory'),
    t('Page: My groups'),
    t('User groups'),
    t('View more'),
  );

  $views[$view->name] = $view;

  return $views;
}
