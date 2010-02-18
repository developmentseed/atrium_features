<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_groups_context_default_contexts() {
  $export = array();
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
    'menu' => 'og',
  );
  $context->condition_mode = 0;

  $translatables['spaces-feature-groups'] = array(
    t('Groups'),
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
  else if ($module == "spaces" && $api == "spaces") {
    return array("version" => 3);
  }
  else if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_groups_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Groups',
    'path' => 'og',
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
  $export = array();
  $spaces_presets = new stdClass;
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'atrium_og_private';
  $spaces_presets->title = 'Private group';
  $spaces_presets->description = 'A private group is accessible only to users added to that group by one of the group\'s managers.';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'variable' => array(
      'spaces_features' => array(
        'atrium_blog' => '1',
        'atrium_book' => '1',
        'atrium_calendar' => '0',
        'atrium_casetracker' => '0',
        'atrium_members' => '1',
        'atrium_shoutbox' => '0',
        'spaces_dashboard' => '1',
      ),
      'spaces_dashboard_custom' => array(
        'custom-1' => 'Dashboard',
      ),
      'spaces_setting_home' => 'dashboard',
      'spaces_og_selective' => 3,
      'spaces_og_directory' => 0,
      'spaces_og_register' => 1,
      'spaces_og_private' => 1,
      'designkit_color' => array(
        'background' => '#3399aa',
      ),
      'site_frontpage' => 'dashboard',
      'space_menu_items' => array(
        'dashboard' => -20,
        'blog' => -19,
        'notebook' => -18,
        'casetracker' => -17,
        'shoutbox' => -16,
        'calendar' => -15,
        'members' => -14,
      ),
    ),
    'context' => array(
      'spaces_dashboard-custom-1:reaction:block' => array(
        'blocks' => array(
          'atrium-welcome_member' => array(
            'module' => 'atrium',
            'delta' => 'welcome_member',
            'region' => 'content',
            'weight' => 0,
          ),
          'views-atrium_intranet-block_1' => array(
            'module' => 'views',
            'delta' => 'atrium_intranet-block_1',
            'region' => 'content',
            'weight' => 1,
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

  $translatables['atrium_og_private'] = array(
    t('A private group is accessible only to users added to that group by one of the group\'s managers.'),
    t('Private group'),
  );

  $export['atrium_og_private'] = $spaces_presets;
  $spaces_presets = new stdClass;
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'atrium_og_public';
  $spaces_presets->title = 'Public group';
  $spaces_presets->description = 'A public group is accessible to all users on the site. Users can join and leave public groups freely.';
  $spaces_presets->space_type = 'og';
  $spaces_presets->value = array(
    'variable' => array(
      'spaces_features' => array(
        'atrium_blog' => '1',
        'atrium_book' => '1',
        'atrium_calendar' => '0',
        'atrium_casetracker' => '0',
        'atrium_members' => '1',
        'atrium_shoutbox' => '0',
        'spaces_dashboard' => '1',
      ),
      'site_frontpage' => 'dashboard',
      'spaces_dashboard_custom' => array(
        'custom-1' => 'Dashboard',
      ),
      'spaces_og_selective' => 0,
      'spaces_og_directory' => 1,
      'spaces_og_register' => 1,
      'spaces_og_private' => 0,
      'designkit_color' => array(
        'background' => '#3399aa',
      ),
      'space_menu_items' => array(
        'dashboard' => -20,
        'blog' => -19,
        'notebook' => -18,
        'casetracker' => -17,
        'shoutbox' => -16,
        'calendar' => -15,
        'members' => -14,
      ),
    ),
    'context' => array(
      'spaces_dashboard-custom-1:reaction:block' => array(
        'blocks' => array(
          'atrium-welcome_member' => array(
            'module' => 'atrium',
            'delta' => 'welcome_member',
            'region' => 'content',
            'weight' => 0,
          ),
          'views-atrium_intranet-block_1' => array(
            'module' => 'views',
            'delta' => 'atrium_intranet-block_1',
            'region' => 'content',
            'weight' => 1,
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

  $translatables['atrium_og_public'] = array(
    t('A public group is accessible to all users on the site. Users can join and leave public groups freely.'),
    t('Public group'),
  );

  $export['atrium_og_public'] = $spaces_presets;
  return $export;
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

/**
 * Helper to implementation of hook_strongarm().
 */
function _atrium_groups_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_archivable_group';
  $strongarm->value = TRUE;

  $export['atrium_archivable_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_update_type_group';
  $strongarm->value = FALSE;

  $export['atrium_update_type_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_group';
  $strongarm->value = 0;

  $export['comment_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_group';
  $strongarm->value = array(
    '0' => 'status',
  );

  $export['node_options_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_group';
  $strongarm->value = array();

  $export['notifications_content_type_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_checkboxes';
  $strongarm->value = 0;

  $export['og_audience_checkboxes'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_required';
  $strongarm->value = '1';

  $export['og_audience_required'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_group';
  $strongarm->value = 'group';

  $export['og_content_type_usage_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_member_pics';
  $strongarm->value = 0;

  $export['og_member_pics'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_notification';
  $strongarm->value = 0;

  $export['og_notification'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_private_groups';
  $strongarm->value = 3;

  $export['og_private_groups'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility';
  $strongarm->value = 2;

  $export['og_visibility'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility_directory';
  $strongarm->value = '2';

  $export['og_visibility_directory'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility_registration';
  $strongarm->value = '3';

  $export['og_visibility_registration'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_group';
  $strongarm->value = FALSE;

  $export['show_diff_inline_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_group';
  $strongarm->value = FALSE;

  $export['show_preview_changes_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_preset_og';
  $strongarm->value = 'atrium_og_private';

  $export['spaces_preset_og'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_group';
  $strongarm->value = FALSE;

  $export['upload_group'] = $strongarm;
  return $export;
}
