<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_shoutbox_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-shoutbox';
  $context->description = '';
  $context->tag = 'Shoutbox';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        '1' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium_shoutbox-shoutbox' => array(
          'module' => 'atrium_shoutbox',
          'delta' => 'shoutbox',
          'region' => 'palette',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['atrium-shoutbox'] = array(
    t('Shoutbox'),
  );

  $export['atrium-shoutbox'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-shoutbox-og';
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
  $context->condition_mode = 0;

  $translatables['atrium-shoutbox-og'] = array(
    t('Shoutbox'),
  );

  $export['atrium-shoutbox-og'] = $context;
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
  else if ($module == "strongarm" && $api == "strongarm") {
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
  );
  // Translatables
  array(
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
