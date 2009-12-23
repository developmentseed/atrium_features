<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _atrium_blog_content_default_fields() {
  $fields = array();

  // Exported field: field_referenced_book_page
  $fields[] = array(
    'field_name' => 'field_referenced_book_page',
    'type_name' => 'blog',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'book' => 'book',
      'event' => 'event',
      'imageset' => 'imageset',
      'admin_message' => 0,
      'blog' => 0,
      'casetracker_basic_case' => 0,
      'feedapi_node' => 0,
      'group' => 0,
      'page' => 0,
      'profile' => 0,
      'casetracker_basic_project' => 0,
      'shoutbox' => 0,
      'feed_ical_item' => 0,
      'feed_ical' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => NULL,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_referenced_book_page][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Referenced Page',
      'weight' => 0,
      'description' => 'Type in the title of another post to add a reference.',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Translatables
  array(
    t('Referenced Page'),
  );

  return $fields;
}

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_blog_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'blog',
    'description' => '',
    'node' => array(
      '0' => 'blog',
    ),
    'views' => array(
      '0' => 'atrium_blog',
    ),
    'spaces' => array(
      'label' => 'Blog',
      'description' => 'A blog for team communications.',
      'menu' => array(
        '0' => array(
          'title' => 'Blog',
          'href' => 'blog',
        ),
      ),
      'types' => array(
        '0' => 'og',
        '1' => 'user',
      ),
    ),
    'menu' => 'blog',
    'block' => array(
      'views_atrium_blog_comments-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_blog_comments-block_1',
        'weight' => 20,
        'region' => 'right',
        'status' => '0',
        'label' => 'atrium_blog_comments: Recent comments',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_blog_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Blog',
    'path' => 'blog',
    'weight' => '0',
    'description' => 'The blog lets you have a conversation on a topic with your team.',
  );
  // Translatables
  array(
    t('Blog'),
    t('The blog lets you have a conversation on a topic with your team.'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_blog_user_default_permissions() {
  $permissions = array();

  // Exported permission: create blog content
  $permissions[] = array(
    'name' => 'create blog content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: delete own blog content
  $permissions[] = array(
    'name' => 'delete own blog content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit own blog content
  $permissions[] = array(
    'name' => 'edit own blog content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
