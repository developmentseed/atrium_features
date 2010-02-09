<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_members_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-members-directory';
  $context->description = '';
  $context->tag = 'Members';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'atrium_members' => 'atrium_members',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium_members-addform' => array(
          'module' => 'atrium_members',
          'delta' => 'addform',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['atrium-members-directory'] = array(
    t('Members'),
  );

  $export['atrium-members-directory'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-feature-members';
  $context->description = '';
  $context->tag = 'Members';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'members/add' => 'members/add',
        'members/add/*' => 'members/add/*',
      ),
    ),
    'views' => array(
      'values' => array(
        'atrium_members' => 'atrium_members',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'members',
  );
  $context->condition_mode = 0;

  $translatables['spaces-feature-members'] = array(
    t('Members'),
  );

  $export['spaces-feature-members'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_members_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  else if ($module == "spaces" && $api == "spaces") {
    return array("version" => 3);
  }
  else if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_imagecache_default_presets().
 */
function _atrium_members_imagecache_default_presets() {
  $items = array(
    'user-m' => array(
      'presetname' => 'user-m',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '60',
            'height' => '60',
          ),
        ),
      ),
    ),
    'user-s' => array(
      'presetname' => 'user-s',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '30',
            'height' => '30',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_members_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Members',
    'path' => 'members',
    'weight' => '0',
    'description' => 'Provides a member directory and user management feature',
  );
  // Translatables
  array(
    t('Members'),
    t('Provides a member directory and user management feature'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_spaces_presets().
 */
function _atrium_members_spaces_presets() {
  $export = array();
  $spaces_presets = new stdClass;
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'atrium_user_simple';
  $spaces_presets->title = 'Simple profile';
  $spaces_presets->description = 'A simple profile with a blog, calendar and dashboard.';
  $spaces_presets->space_type = 'user';
  $spaces_presets->value = array(
    'variable' => array(
      'spaces_features' => array(
        'spaces_dashboard' => '1',
      ),
      'spaces_dashboard_custom' => array(
        'custom-1' => 'Dashboard',
      ),
      'spaces_setting_home' => 'profile',
    ),
    'context' => array(
      'spaces_dashboard-custom-1:reaction:block' => array(
        'blocks' => array(
          'views-atrium_intranet-block_1' => array(
            'module' => 'views',
            'delta' => 'atrium_intranet-block_1',
            'region' => 'content',
            'weight' => 0,
          ),
          'views-atrium_blog_comments-block_1' => array(
            'module' => 'views',
            'delta' => 'atrium_blog_comments-block_1',
            'region' => 'right',
            'weight' => 0,
          ),
        ),
      ),
      'spaces_dashboard-custom-2:reaction:block' => array(
        'blocks' => array(),
      ),
      'spaces_dashboard-custom-3:reaction:block' => array(
        'blocks' => array(),
      ),
      'spaces_dashboard-custom-4:reaction:block' => array(
        'blocks' => array(),
      ),
      'spaces_dashboard-custom-5:reaction:block' => array(
        'blocks' => array(),
      ),
    ),
  );

  $translatables['atrium_user_simple'] = array(
    t('A simple profile with a blog, calendar and dashboard.'),
    t('Simple profile'),
  );
  $export['atrium_user_simple'] = $spaces_presets;
  return $export;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_members_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer users
  $permissions[] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: block users
  $permissions[] = array(
    'name' => 'block users',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: change own username
  $permissions[] = array(
    'name' => 'change own username',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: create users
  $permissions[] = array(
    'name' => 'create users',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: view imagecache user-m
  $permissions[] = array(
    'name' => 'view imagecache user-m',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: view imagecache user-s
  $permissions[] = array(
    'name' => 'view imagecache user-s',
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
function _atrium_members_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seed_imagecache_user_picture';
  $strongarm->value = 'user-s';

  $export['seed_imagecache_user_picture'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_preset_user';
  $strongarm->value = 'atrium_user_simple';

  $export['spaces_preset_user'] = $strongarm;
  return $export;
}
