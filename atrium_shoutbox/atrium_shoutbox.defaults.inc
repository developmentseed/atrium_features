<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_shoutbox_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-shoutbox-og';
  $context->description = '';
  $context->tag = 'Shoutbox';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'atrium_shoutbox_shouts:page_1' => 'atrium_shoutbox_shouts:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-468d4512633362842c0ff768ac59efad' => array(
          'module' => 'views',
          'delta' => '468d4512633362842c0ff768ac59efad',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-atrium_shoutbox_users-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_shoutbox_users-block_1',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );

  $export['spaces-shoutbox-og'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-shoutbox-user';
  $context->description = '';
  $context->tag = 'Shoutbox';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'atrium_shoutbox_shouts:page_2' => 'atrium_shoutbox_shouts:page_2',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-584a7dacb1e0f4c880cbacb19e2d0e93' => array(
          'module' => 'views',
          'delta' => '584a7dacb1e0f4c880cbacb19e2d0e93',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );

  $export['spaces-shoutbox-user'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_shoutbox_ctools_plugin_api() {
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
function _atrium_shoutbox_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Shoutbox',
    'path' => 'shoutbox',
    'weight' => '0',
    'description' => 'A simple shoutbox feature',
  );
  // Translatables
  array(
    t('A simple shoutbox feature'),
    t('Shoutbox'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_shoutbox_user_default_permissions() {
  $permissions = array();

  // Exported permission: create shoutbox
  $permissions[] = array(
    'name' => 'create shoutbox',
    'roles' => array(),
  );

  // Exported permission: post messages to shoutbox
  $permissions[] = array(
    'name' => 'post messages to shoutbox',
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
function _atrium_shoutbox_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_update_type_shoutbox';
  $strongarm->value = 0;

  $export['atrium_update_type_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_shoutbox';
  $strongarm->value = '0';

  $export['comment_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'feedapi_settings_shoutbox';
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

  $export['feedapi_settings_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_shoutbox';
  $strongarm->value = array(
    '0' => 'status',
  );

  $export['node_options_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_shoutbox';
  $strongarm->value = array();

  $export['notifications_content_type_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_shoutbox';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_shoutbox';
  $strongarm->value = 0;

  $export['show_diff_inline_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_shoutbox';
  $strongarm->value = 0;

  $export['show_preview_changes_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_shoutbox';
  $strongarm->value = FALSE;

  $export['upload_shoutbox'] = $strongarm;
  return $export;
}
