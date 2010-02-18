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
      'weight' => 0,
      'parent' => '',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
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
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-feature-blog';
  $context->description = '';
  $context->tag = 'Blog';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'atrium_blog' => 'atrium_blog',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-atrium_blog_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_blog_comments-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'blog',
  );
  $context->condition_mode = 0;

  $translatables['spaces-feature-blog'] = array(
    t('Blog'),
  );

  $export['spaces-feature-blog'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_blog_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  else if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
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
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: delete own blog content
  $permissions[] = array(
    'name' => 'delete own blog content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit own blog content
  $permissions[] = array(
    'name' => 'edit own blog content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  return $permissions;
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _atrium_blog_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_update_type_blog';
  $strongarm->value = TRUE;

  $export['atrium_update_type_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_blog';
  $strongarm->value = 2;

  $export['comment_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_blog';
  $strongarm->value = 3;

  $export['comment_controls_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_blog';
  $strongarm->value = 4;

  $export['comment_default_mode_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_blog';
  $strongarm->value = 2;

  $export['comment_default_order_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_blog';
  $strongarm->value = 200;

  $export['comment_default_per_page_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_blog';
  $strongarm->value = 1;

  $export['comment_form_location_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_blog';
  $strongarm->value = 0;

  $export['comment_preview_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_blog';
  $strongarm->value = 0;

  $export['comment_subject_field_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_upload_blog';
  $strongarm->value = TRUE;

  $export['comment_upload_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_blog';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'revision',
  );

  $export['node_options_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_blog';
  $strongarm->value = array(
    '0' => 'thread',
    '1' => 'grouptype',
    '2' => 'nodetype',
    '3' => 'author',
  );

  $export['notifications_content_type_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_blog';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_blog';
  $strongarm->value = FALSE;

  $export['show_diff_inline_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_blog';
  $strongarm->value = FALSE;

  $export['show_preview_changes_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_blog';
  $strongarm->value = TRUE;

  $export['upload_blog'] = $strongarm;
  return $export;
}
