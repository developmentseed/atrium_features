<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_intranet_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'atrium',
    'attribute' => 'intranet',
    'value' => 'global',
    'description' => '',
    'sitewide' => '1',
    'block' => array(
      'atrium_intranet_account' => array(
        'module' => 'atrium_intranet',
        'delta' => 'account',
        'weight' => -47,
        'region' => 'header',
        'status' => '0',
        'label' => 'Atrium Intranet: User account',
        'type' => 'context_ui',
      ),
      'atrium_intranet_help' => array(
        'module' => 'atrium_intranet',
        'delta' => 'help',
        'weight' => 48,
        'region' => 'header',
        'status' => '0',
        'label' => 'Atrium Intranet: Help',
        'type' => 'context_ui',
      ),
      'atrium_intranet_spacelinks' => array(
        'module' => 'atrium_intranet',
        'delta' => 'spacelinks',
        'weight' => 47,
        'region' => 'space_tools',
        'status' => '0',
        'label' => 'Atrium Intranet: Space links',
        'type' => 'context_ui',
      ),
      'atrium_intranet_create' => array(
        'module' => 'atrium_intranet',
        'delta' => 'create',
        'weight' => 48,
        'region' => 'space_tools',
        'status' => '0',
        'label' => 'Atrium Intranet: Create content',
        'type' => 'context_ui',
      ),
      'xref_create' => array(
        'module' => 'xref',
        'delta' => 'create',
        'weight' => 47,
        'region' => 'page_tools',
        'status' => '0',
        'label' => 'Crossref: Create referrer',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'theme',
    'attribute' => 'layout',
    'value' => 'custom',
    'description' => '',
    'theme_regiontoggle' => array(
      '0' => 'right',
      '1' => 'content',
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_filter_default_formats().
 */
function _atrium_intranet_filter_default_formats() {
  $formats = array();

  // Exported format: Full HTML
  $formats[] = array(
    'name' => 'Full HTML',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
    'filters' => array(
      '0' => array(
        'module' => 'codefilter',
        'delta' => '0',
        'weight' => '0',
      ),
      '1' => array(
        'module' => 'filter',
        'delta' => '2',
        'weight' => '0',
      ),
      '2' => array(
        'module' => 'filter',
        'delta' => '1',
        'weight' => '1',
      ),
      '3' => array(
        'module' => 'filter',
        'delta' => '3',
        'weight' => '10',
      ),
    ),
  );

  // Exported format: Messaging plain text
  $formats[] = array(
    'name' => 'Messaging plain text',
    'roles' => array(),
    'filters' => array(
      '0' => array(
        'module' => 'filter',
        'delta' => '1',
        'weight' => '-10',
      ),
      '1' => array(
        'module' => 'messaging',
        'delta' => '1',
        'weight' => '-9',
      ),
    ),
  );

  // Exported format: Markdown
  $formats[] = array(
    'name' => 'Markdown',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'admin',
      '3' => 'manager',
    ),
    'filters' => array(
      '0' => array(
        'module' => 'markdown',
        'delta' => '0',
        'weight' => '-10',
      ),
      '1' => array(
        'module' => 'filter',
        'delta' => '2',
        'weight' => '-9',
      ),
      '2' => array(
        'module' => 'filter',
        'delta' => '0',
        'weight' => '-8',
      ),
      '3' => array(
        'module' => 'codefilter',
        'delta' => '0',
        'weight' => '-7',
      ),
      '4' => array(
        'module' => 'filter',
        'delta' => '3',
        'weight' => '-6',
      ),
    ),
  );

  return $formats;
}

/**
 * Helper to implementation of hook_imagecache_default_presets().
 */
function _atrium_intranet_imagecache_default_presets() {
  $items = array(
    'fileview' => array(
      'presetname' => 'fileview',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_deprecated_scale',
          'data' => array(
            'fit' => 'inside',
            'width' => '60',
            'height' => '40',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_spaces_presets().
 */
function _atrium_intranet_spaces_presets() {
  $presets = array();

  // Exported preset: atrium_intranet
  $presets['atrium_intranet'] = array(
    'name' => 'Basic intranet',
    'description' => 'A basic intranet hub setup.',
    'type' => 'site',
    'preset' => array(
      'features' => array(
        'atrium_intranet' => '1',
        'atrium_dashboard' => '1',
        'atrium_groups' => '1',
        'atrium_members' => '1',
      ),
      'settings' => array(
        'home' => 'home',
      ),
      'locked' => array(
        'features' => array(
          'atrium_intranet' => 1,
          'atrium_dashboard' => 1,
          'atrium_groups' => 1,
          'atrium_members' => 1,
        ),
        'settings' => array(
          'atrium_sitemode' => 0,
          'atrium_members' => 0,
          'home' => 0,
          'logo' => 0,
          'color' => 0,
        ),
      ),
      'weights' => array(
        'atrium_intranet' => '-10',
        'atrium_dashboard' => '-9',
        'atrium_groups' => '-8',
        'atrium_members' => '-7',
      ),
      'site' => array(),
    ),
  );

  return $presets;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_intranet_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration pages
  $permissions[] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: add list of open ids
  $permissions[] = array(
    'name' => 'add list of open ids',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: admin menu
  $permissions[] = array(
    'name' => 'admin menu',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer atrium
  $permissions[] = array(
    'name' => 'administer atrium',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer comments
  $permissions[] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: administer filters
  $permissions[] = array(
    'name' => 'administer filters',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer messaging
  $permissions[] = array(
    'name' => 'administer messaging',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer nodes
  $permissions[] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer notifications
  $permissions[] = array(
    'name' => 'administer notifications',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer permissions
  $permissions[] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer search
  $permissions[] = array(
    'name' => 'administer search',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer site configuration
  $permissions[] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer spaces
  $permissions[] = array(
    'name' => 'administer spaces',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: administer taxonomy
  $permissions[] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: configure spaces features
  $permissions[] = array(
    'name' => 'configure spaces features',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: post comments
  $permissions[] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: post comments without approval
  $permissions[] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: revert revisions
  $permissions[] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: search content
  $permissions[] = array(
    'name' => 'search content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: select different theme
  $permissions[] = array(
    'name' => 'select different theme',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: skip notifications
  $permissions[] = array(
    'name' => 'skip notifications',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: subscribe other users
  $permissions[] = array(
    'name' => 'subscribe other users',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: subscribe to author
  $permissions[] = array(
    'name' => 'subscribe to author',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: subscribe to content
  $permissions[] = array(
    'name' => 'subscribe to content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: upload files
  $permissions[] = array(
    'name' => 'upload files',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: upload files to comments
  $permissions[] = array(
    'name' => 'upload files to comments',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: use advanced search
  $permissions[] = array(
    'name' => 'use advanced search',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: view files uploaded to comments
  $permissions[] = array(
    'name' => 'view files uploaded to comments',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: view imagecache fileview
  $permissions[] = array(
    'name' => 'view imagecache fileview',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: view imagecache spaces-logo
  $permissions[] = array(
    'name' => 'view imagecache spaces-logo',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: view uploaded files
  $permissions[] = array(
    'name' => 'view uploaded files',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
