<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_groups_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-groups-global';
  $context->description = '';
  $context->tag = 'Groups';
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
        'views-atrium_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_groups-block_1',
          'region' => 'header',
          'weight' => 0,
        ),
      ),
    ),
  );

  $export['atrium-groups-global'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-feature-groups';
  $context->description = '';
  $context->tag = 'Groups';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'atrium_groups' => 'atrium_groups',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'groups',
  );

  $export['spaces-feature-groups'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_groups_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
}

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_groups_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Groups',
    'path' => 'groups',
    'weight' => '0',
    'description' => 'Provides a group management feature',
  );
  // Translatables
  array(
    t('Groups'),
    t('Provides a group management feature'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_spaces_presets().
 */
function _atrium_groups_spaces_presets() {
  $presets = array();

  // Exported preset: atrium_og_private
  $presets['atrium_og_private'] = array(
    'name' => 'Private group',
    'description' => 'A simple private group with a blog, document library and dashboard.',
    'type' => 'og',
    'preset' => array(
      'features' => array(
        'atrium_blog' => 1,
        'atrium_book' => 1,
        'atrium_calendar' => 0,
        'atrium_dashboard' => 1,
      ),
      'settings' => array(
        'home' => 'dashboard',
      ),
      'og' => array(
        'og_selective' => 3,
        'og_directory' => 0,
        'og_register' => 1,
        'og_private' => 1,
      ),
    ),
  );

  // Exported preset: atrium_og_public
  $presets['atrium_og_public'] = array(
    'name' => 'Public group',
    'description' => 'A simple public group with a blog, document library and dashboard.',
    'type' => 'og',
    'preset' => array(
      'features' => array(
        'atrium_blog' => 2,
        'atrium_book' => 2,
        'atrium_calendar' => 0,
        'atrium_dashboard' => 2,
      ),
      'settings' => array(
        'home' => 'dashboard',
      ),
      'og' => array(
        'og_selective' => 0,
        'og_directory' => 1,
        'og_register' => 1,
        'og_private' => 0,
      ),
    ),
  );

  return $presets;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_groups_user_default_permissions() {
  $permissions = array();

  // Exported permission: create group content
  $permissions[] = array(
    'name' => 'create group content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete own group content
  $permissions[] = array(
    'name' => 'delete own group content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own group content
  $permissions[] = array(
    'name' => 'edit own group content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  return $permissions;
}
