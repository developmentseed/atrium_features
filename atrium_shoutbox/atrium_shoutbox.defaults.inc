<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_shoutbox_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'shoutbox',
    'value' => 'og',
    'description' => '',
    'node' => array(
      '0' => 'shoutbox',
    ),
    'views' => array(
      '0' => 'atrium_shoutbox_shouts:page_1',
      '1' => 'atrium_shoutbox_shouts:page_3',
    ),
    'menu' => 'shoutbox',
    'block' => array(
      'views_468d4512633362842c0ff768ac59efad' => array(
        'module' => 'views',
        'delta' => '468d4512633362842c0ff768ac59efad',
        'weight' => 20,
        'region' => 'right',
        'status' => '0',
        'label' => 'Exposed form: atrium_shoutbox_shouts-page_1',
        'type' => 'context_ui',
      ),
      'views_atrium_shoutbox_users-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_shoutbox_users-block_1',
        'weight' => 21,
        'region' => 'right',
        'status' => '0',
        'label' => 'atrium_shoutbox_users: Block',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'shoutbox',
    'value' => 'user',
    'description' => '',
    'node' => array(
      '0' => 'shoutbox',
    ),
    'views' => array(
      '0' => 'atrium_shoutbox_shouts:page_2',
    ),
    'menu' => 'shoutbox',
    'block' => array(
      'views_584a7dacb1e0f4c880cbacb19e2d0e93' => array(
        'module' => 'views',
        'delta' => '584a7dacb1e0f4c880cbacb19e2d0e93',
        'weight' => 20,
        'region' => 'right',
        'status' => '0',
        'label' => 'Exposed form: atrium_shoutbox_shouts-page_2',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
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
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
