<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_members_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'members',
    'menu' => 'members',
    'views' => array(
      '0' => 'atrium_members',
    ),
    'theme_section' => array(
      'title' => 'Members',
      'subtitle' => '',
      'class' => '',
    ),
    'block' => array(
      'views_-exp-atrium_members-default' => array(
        'module' => 'views',
        'delta' => '-exp-atrium_members-default',
        'region' => 'right',
        'weight' => '-10',
      ),
    ),
  );
  return $items;
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
  $presets = array();

  // Exported preset: atrium_user_simple
  $presets['atrium_user_simple'] = array(
    'name' => 'Simple profile',
    'description' => 'A simple profile with a blog, calendar and dashboard.',
    'type' => 'user',
    'preset' => array(
      'features' => array(
        'atrium_blog' => '1',
        'atrium_book' => '0',
        'atrium_calendar' => '1',
        'atrium_dashboard' => '1',
      ),
      'settings' => array(
        'home' => 'profile',
      ),
      'locked' => array(
        'features' => array(
          'atrium_blog' => 1,
          'atrium_book' => 0,
          'atrium_calendar' => 1,
          'atrium_dashboard' => 1,
        ),
        'settings' => array(
          'home' => 1,
        ),
      ),
      'user' => array(),
    ),
  );

  return $presets;
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
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: view imagecache user-s
  $permissions[] = array(
    'name' => 'view imagecache user-s',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
