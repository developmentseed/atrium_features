<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_casetracker_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-casetracker-project';
  $context->description = '';
  $context->tag = 'Casetracker';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'casetracker_basic_project' => 'casetracker_basic_project',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-atrium_casetracker-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_casetracker-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );

  $export['atrium-casetracker-project'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-feature-casetracker';
  $context->description = '';
  $context->tag = 'Casetracker';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'casetracker_basic_project' => 'casetracker_basic_project',
        'casetracker_basic_case' => 'casetracker_basic_case',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'atrium_casetracker' => 'atrium_casetracker',
        'atrium_casetracker_projects' => 'atrium_casetracker_projects',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium_casetracker-book' => array(
          'module' => 'atrium_casetracker',
          'delta' => 'book',
          'region' => 'right',
          'weight' => 0,
        ),
        'atrium_casetracker-filters' => array(
          'module' => 'atrium_casetracker',
          'delta' => 'filters',
          'region' => 'right',
          'weight' => 1,
        ),
        'views-atrium_casetracker-block_2' => array(
          'module' => 'views',
          'delta' => 'atrium_casetracker-block_2',
          'region' => 'right',
          'weight' => 2,
        ),
      ),
    ),
    'menu' => 'casetracker',
  );

  $export['spaces-feature-casetracker'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_casetracker_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  else if ($module == "system" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_casetracker_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Case Tracker',
    'path' => 'casetracker',
    'weight' => '0',
    'description' => 'The casetracker lets you assign tasks to yourself and others and track the progress on a project.',
  );
  // Translatables
  array(
    t('Case Tracker'),
    t('The casetracker lets you assign tasks to yourself and others and track the progress on a project.'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_casetracker_user_default_permissions() {
  $permissions = array();

  // Exported permission: access case tracker
  $permissions[] = array(
    'name' => 'access case tracker',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: create casetracker_basic_case content
  $permissions[] = array(
    'name' => 'create casetracker_basic_case content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: create casetracker_basic_project content
  $permissions[] = array(
    'name' => 'create casetracker_basic_project content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own casetracker_basic_case content
  $permissions[] = array(
    'name' => 'edit own casetracker_basic_case content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit own casetracker_basic_project content
  $permissions[] = array(
    'name' => 'edit own casetracker_basic_project content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  return $permissions;
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _atrium_casetracker_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_update_type_casetracker_basic_case';
  $strongarm->value = 1;

  $export['atrium_update_type_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_update_type_casetracker_basic_project';
  $strongarm->value = 1;

  $export['atrium_update_type_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'casetracker_view_assignee_options';
  $strongarm->value = 'atrium_ct_assignee_options';

  $export['casetracker_view_assignee_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'casetracker_view_project_options';
  $strongarm->value = 'atrium_ct_project_options';

  $export['casetracker_view_project_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_casetracker_basic_case';
  $strongarm->value = '2';

  $export['comment_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_casetracker_basic_project';
  $strongarm->value = '0';

  $export['comment_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_casetracker_basic_case';
  $strongarm->value = '3';

  $export['comment_controls_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_casetracker_basic_case';
  $strongarm->value = '4';

  $export['comment_default_mode_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_casetracker_basic_case';
  $strongarm->value = '2';

  $export['comment_default_order_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_casetracker_basic_case';
  $strongarm->value = '200';

  $export['comment_default_per_page_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_casetracker_basic_case';
  $strongarm->value = '1';

  $export['comment_form_location_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_casetracker_basic_case';
  $strongarm->value = '0';

  $export['comment_preview_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_casetracker_basic_case';
  $strongarm->value = '0';

  $export['comment_subject_field_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_upload_casetracker_basic_case';
  $strongarm->value = '1';

  $export['comment_upload_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'feedapi_settings_casetracker_basic_case';
  $strongarm->value = array(
    'enabled' => 0,
    'upload_method' => 'url',
    'refresh_on_create' => 0,
    'update_existing' => 1,
    'refresh_time' => '1800',
    'items_delete' => '0',
    'parsers' => array(
      'parser_ical' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
    ),
    'processors' => array(
      'feedapi_node' => array(
        'enabled' => 0,
        'weight' => '0',
        'content_type' => 'blog',
        'input_format' => '4',
        'node_date' => 'feed',
        'x_dedupe' => '0',
      ),
      'feedapi_inherit' => array(
        'enabled' => 0,
        'weight' => '0',
        'inherit_og' => 1,
        'inherit_taxonomy' => 1,
        'inherit_author' => 1,
      ),
    ),
  );

  $export['feedapi_settings_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'feedapi_settings_casetracker_basic_project';
  $strongarm->value = array(
    'enabled' => 0,
    'upload_method' => 'url',
    'refresh_on_create' => 0,
    'update_existing' => 1,
    'refresh_time' => '1800',
    'items_delete' => '0',
    'parsers' => array(
      'parser_ical' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
    ),
    'processors' => array(
      'feedapi_node' => array(
        'enabled' => 0,
        'weight' => '0',
        'content_type' => 'blog',
        'input_format' => '4',
        'node_date' => 'feed',
        'x_dedupe' => '0',
      ),
      'feedapi_inherit' => array(
        'enabled' => 0,
        'weight' => '0',
        'inherit_og' => 1,
        'inherit_taxonomy' => 1,
        'inherit_author' => 1,
      ),
    ),
  );

  $export['feedapi_settings_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_casetracker_basic_case';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'revision',
  );

  $export['node_options_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_casetracker_basic_project';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'revision',
  );

  $export['node_options_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_casetracker_basic_case';
  $strongarm->value = array(
    '0' => 'thread',
    '1' => 'nodetype',
    '2' => 'author',
  );

  $export['notifications_content_type_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_casetracker_basic_project';
  $strongarm->value = array(
    '0' => 'thread',
    '1' => 'nodetype',
    '2' => 'author',
  );

  $export['notifications_content_type_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_casetracker_basic_case';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_casetracker_basic_project';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_event_casetracker_basic_case';
  $strongarm->value = FALSE;

  $export['show_diff_inline_event_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_event_casetracker_basic_project';
  $strongarm->value = TRUE;

  $export['show_diff_inline_event_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_casetracker_basic_case';
  $strongarm->value = 0;

  $export['show_preview_changes_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_casetracker_basic_project';
  $strongarm->value = 0;

  $export['show_preview_changes_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_casetracker_basic_case';
  $strongarm->value = '1';

  $export['upload_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_casetracker_basic_project';
  $strongarm->value = '1';

  $export['upload_casetracker_basic_project'] = $strongarm;
  return $export;
}
