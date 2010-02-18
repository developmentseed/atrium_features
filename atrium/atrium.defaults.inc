<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-intranet-global';
  $context->description = '';
  $context->tag = 'Intranet';
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
        'atrium-account' => array(
          'module' => 'atrium',
          'delta' => 'account',
          'region' => 'header',
          'weight' => 0,
        ),
        'atrium-user_links' => array(
          'module' => 'atrium',
          'delta' => 'user_links',
          'region' => 'header',
          'weight' => 1,
        ),
        'atrium-create' => array(
          'module' => 'atrium',
          'delta' => 'create',
          'region' => 'space_tools',
          'weight' => 0,
        ),
        'atrium-admin_links' => array(
          'module' => 'atrium',
          'delta' => 'admin_links',
          'region' => 'space_tools',
          'weight' => 1,
        ),
        'atrium-search' => array(
          'module' => 'atrium',
          'delta' => 'search',
          'region' => 'space_tools',
          'weight' => 2,
        ),
        'xref-create' => array(
          'module' => 'xref',
          'delta' => 'create',
          'region' => 'page_tools',
          'weight' => 0,
        ),
        'spaces_dashboard-editor' => array(
          'module' => 'spaces_dashboard',
          'delta' => 'editor',
          'region' => 'palette',
          'weight' => 0,
        ),
        'spaces-menu_editor' => array(
          'module' => 'spaces',
          'delta' => 'menu_editor',
          'region' => 'palette',
          'weight' => 1,
        ),
        'atrium-help' => array(
          'module' => 'atrium',
          'delta' => 'help',
          'region' => 'palette',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['atrium-intranet-global'] = array(
    t('Intranet'),
  );

  $export['atrium-intranet-global'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-section-taxonomy';
  $context->description = '';
  $context->tag = 'Intranet';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'atrium_taxonomy' => 'atrium_taxonomy',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-atrium_taxonomy-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_taxonomy-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['atrium-section-taxonomy'] = array(
    t('Intranet'),
  );

  $export['atrium-section-taxonomy'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'layout_login';
  $context->description = '';
  $context->tag = 'Theme';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'login',
    ),
  );
  $context->condition_mode = 0;

  $translatables['layout_login'] = array(
    t('Theme'),
  );

  $export['layout_login'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'layout_wide';
  $context->description = '';
  $context->tag = 'Theme';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'node/add/*' => 'node/add/*',
        'node/*/edit' => 'node/*/edit',
        'admin' => 'admin',
        'admin/*' => 'admin/*',
        'user/*/edit' => 'user/*/edit',
        'user/*/edit/*' => 'user/*/edit/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(),
      'layout' => 'wide',
    ),
  );
  $context->condition_mode = 0;

  $translatables['layout_wide'] = array(
    t('Theme'),
  );

  $export['layout_wide'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces_dashboard-custom-1';
  $context->description = 'Dashboard';
  $context->tag = 'Dashboard';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium-welcome_admin' => array(
          'module' => 'atrium',
          'delta' => 'welcome_admin',
          'region' => 'content',
          'weight' => 0,
        ),
        'views-atrium_intranet-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_intranet-block_1',
          'region' => 'content',
          'weight' => 1,
        ),
        'views-atrium_groups-block_2' => array(
          'module' => 'views',
          'delta' => 'atrium_groups-block_2',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['spaces_dashboard-custom-1'] = array(
    t('Dashboard'),
  );

  $export['spaces_dashboard-custom-1'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_ctools_plugin_api() {
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
 * Helper to implementation of hook_filter_default_formats().
 */
function _atrium_filter_default_formats() {
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
function _atrium_imagecache_default_presets() {
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
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration pages
  $permissions[] = array(
    'name' => 'access administration pages',
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

  // Exported permission: post comments
  $permissions[] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: post comments without approval
  $permissions[] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
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
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: select different theme
  $permissions[] = array(
    'name' => 'select different theme',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: skip notifications
  $permissions[] = array(
    'name' => 'skip notifications',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: subscribe to author
  $permissions[] = array(
    'name' => 'subscribe to author',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: subscribe to content
  $permissions[] = array(
    'name' => 'subscribe to content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: upload files
  $permissions[] = array(
    'name' => 'upload files',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: upload files to comments
  $permissions[] = array(
    'name' => 'upload files to comments',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: use advanced search
  $permissions[] = array(
    'name' => 'use advanced search',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: view files uploaded to comments
  $permissions[] = array(
    'name' => 'view files uploaded to comments',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: view imagecache fileview
  $permissions[] = array(
    'name' => 'view imagecache fileview',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: view uploaded files
  $permissions[] = array(
    'name' => 'view uploaded files',
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
function _atrium_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_toolbar';
  $strongarm->value = array(
    'layout' => 'vertical',
    'position' => 'nw',
    'blocks' => array(
      'admin-create' => 'admin-create',
      'admin-menu' => 'admin-menu',
      'admin-devel' => 'admin-devel',
      'context_ui-editor' => 0,
      'context_ui-devel' => 0,
      'spaces_dashboard-editor' => 0,
      'spaces-menu_editor' => 0,
    ),
  );

  $export['admin_toolbar'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'allowed_html_1';
  $strongarm->value = '<div> <span> <br> <a> <em> <strong> <cite> <code> <strike> <ul> <ol> <li> <dl> <dt> <dd> <img> <blockquote> <p> <pre> <h1> <h2> <h3> <h4> <h5> <h6> <table> <caption> <thead> <th> <td> <tr> <sup> <sub>';

  $export['allowed_html_1'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'allowed_html_2';
  $strongarm->value = '<div> <span> <br> <a> <em> <strong> <cite> <code> <strike> <ul> <ol> <li> <dl> <dt> <dd> <img> <blockquote> <p> <pre> <h1> <h2> <h3> <h4> <h5> <h6> <table> <caption> <thead> <th> <td> <tr> <sup> <sub>';

  $export['allowed_html_2'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'allowed_html_3';
  $strongarm->value = '<div> <span> <br> <a> <em> <strong> <cite> <code> <strike> <ul> <ol> <li> <dl> <dt> <dd> <img> <blockquote> <p> <pre> <h1> <h2> <h3> <h4> <h5> <h6> <table> <caption> <thead> <th> <td> <tr> <sup> <sub>';

  $export['allowed_html_3'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'allowed_html_4';
  $strongarm->value = '<div> <span> <br> <a> <em> <strong> <cite> <code> <strike> <ul> <ol> <li> <dl> <dt> <dd> <img> <blockquote> <p> <pre> <h1> <h2> <h3> <h4> <h5> <h6> <table> <caption> <thead> <th> <td> <tr> <sup> <sub>';

  $export['allowed_html_4'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'allowed_html_5';
  $strongarm->value = '<div> <span> <br> <a> <em> <strong> <cite> <code> <strike> <ul> <ol> <li> <dl> <dt> <dd> <img> <blockquote> <p> <pre> <h1> <h2> <h3> <h4> <h5> <h6> <table> <caption> <thead> <th> <td> <tr> <sup> <sub>';

  $export['allowed_html_5'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'book_allowed_types';
  $strongarm->value = array(
    '0' => 'book',
    '1' => 'casetracker_basic_project',
  );

  $export['book_allowed_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'context_ui_show_empty_regions';
  $strongarm->value = 1;

  $export['context_ui_show_empty_regions'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_field_date_long';
  $strongarm->value = 'g:ia D M j, Y';

  $export['date_format_field_date_long'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_field_date_medium';
  $strongarm->value = 'g:ia M j, Y';

  $export['date_format_field_date_medium'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_field_date_short';
  $strongarm->value = 'M j, Y';

  $export['date_format_field_date_short'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_long';
  $strongarm->value = 'g:ia D M j, Y';

  $export['date_format_long'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_medium';
  $strongarm->value = 'g:ia M j, Y';

  $export['date_format_medium'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_short';
  $strongarm->value = 'M j, Y';

  $export['date_format_short'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'filter_default_format';
  $strongarm->value = '5';

  $export['filter_default_format'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imageapi_jpeg_quality';
  $strongarm->value = 90;

  $export['imageapi_jpeg_quality'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_primary_links_source';
  $strongarm->value = 'features';

  $export['menu_primary_links_source'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'messaging_default_method';
  $strongarm->value = 'mail';

  $export['messaging_default_method'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'messaging_method_mail';
  $strongarm->value = array(
    'filter' => 3,
  );

  $export['messaging_method_mail'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_per_type';
  $strongarm->value = 1;

  $export['notifications_content_per_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_team_max_options';
  $strongarm->value = 200;

  $export['notifications_team_max_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_account_options';
  $strongarm->value = array(
    'block' => 'block',
  );

  $export['notifications_ui_account_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_node';
  $strongarm->value = array(
    'block' => 'block',
  );

  $export['notifications_ui_node'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_per_type';
  $strongarm->value = 0;

  $export['notifications_ui_per_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_types';
  $strongarm->value = array(
    'grouptype' => 'grouptype',
    'thread' => 'thread',
    'nodetype' => 'nodetype',
    'author' => 'author',
  );

  $export['notifications_ui_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_user';
  $strongarm->value = array(
    'page' => 'page',
  );

  $export['notifications_ui_user'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_home_page_view';
  $strongarm->value = '0';

  $export['og_home_page_view'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_notifications_content_types';
  $strongarm->value = array(
    'blog' => 'blog',
    '0' => 'book',
    '1' => 'event',
    '2' => 'feed_ical',
    '3' => 'feed_ical_item',
    '4' => 'casetracker_basic_case',
    '5' => 'casetracker_basic_project',
  );

  $export['og_notifications_content_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'purl_method_spaces_og';
  $strongarm->value = 'path';

  $export['purl_method_spaces_og'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'purl_types';
  $strongarm->value = array(
    'path' => 'path',
  );

  $export['purl_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seed_book';
  $strongarm->value = array(
    'book_nav' => '0',
  );

  $export['seed_book'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seed_imagecache_attachment';
  $strongarm->value = 'fileview';

  $export['seed_imagecache_attachment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'dashboard';

  $export['site_frontpage'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'space_menu_items';
  $strongarm->value = array(
    'dashboard' => -20,
    'og' => -19,
    'members' => -18,
  );

  $export['space_menu_items'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_dashboard_blocks';
  $strongarm->value = array(
    'admin-create' => 0,
    'admin-devel' => 0,
    'admin-menu' => 0,
    'atrium-account' => 0,
    'atrium-admin_links' => 0,
    'atrium-book' => 0,
    'atrium-book_all' => 0,
    'atrium-create' => 0,
    'atrium-help' => 0,
    'atrium-search' => 0,
    'atrium-user_links' => 0,
    'atrium-welcome_admin' => 1,
    'atrium-welcome_member' => 1,
    'atrium_calendar-mini' => 1,
    'atrium_casetracker-filters' => 0,
    'atrium_shoutbox-shoutbox' => 0,
    'book-0' => 0,
    'casetracker-0' => 0,
    'comment-0' => 0,
    'context_ui-devel' => 0,
    'context_ui-editor' => 0,
    'devel-0' => 0,
    'devel-2' => 0,
    'diff-inline' => 0,
    'feedapi-feed_ical' => 0,
    'feedapi-feedapi_node' => 0,
    'markdown-help' => 0,
    'menu-admin' => 0,
    'menu-devel' => 0,
    'menu-features' => 0,
    'menu-primary-links' => 0,
    'menu-secondary-links' => 0,
    'menu-spaces' => 0,
    'node-0' => 0,
    'og-0' => 0,
    'og-3' => 0,
    'og_views-0' => 0,
    'og_views-1' => 0,
    'search-0' => 0,
    'spaces-menu_editor' => 0,
    'spaces_dashboard-editor' => 0,
    'system-0' => 0,
    'user-0' => 0,
    'user-1' => 0,
    'user-2' => 0,
    'user-3' => 0,
    'views--exp-atrium_members-default' => 0,
    'views--exp-atrium_members-page_1' => 0,
    'views--exp-atrium_members-page_2' => 0,
    'views--exp-atrium_members-page_3' => 0,
    'views--exp-atrium_members-page_4' => 0,
    'views--exp-messaging_shoutbox-block_1' => 0,
    'views--exp-messaging_shoutbox-block_2' => 0,
    'views--exp-messaging_shoutbox-default' => 0,
    'views-2806ea1d75b0ffa45a7eaa780e276615' => 1,
    'views-3de5a072e9754aa7bce60e3f05d1538e' => 1,
    'views-468d4512633362842c0ff768ac59efad' => 0,
    'views-707d7ca4a3396303c7ef762f32d243c8' => 0,
    'views-9659fa0bc3abbfbebd3db25567f1aa29' => 0,
    'views-atrium_blog-block_1' => 0,
    'views-atrium_blog-block_2' => 1,
    'views-atrium_blog_comments-block_1' => 1,
    'views-atrium_calendar-block_1' => 0,
    'views-atrium_casetracker-block_1' => 0,
    'views-atrium_casetracker-block_2' => 1,
    'views-atrium_casetracker-block_3' => 1,
    'views-atrium_groups-block_2' => 1,
    'views-atrium_intranet-block_1' => 1,
    'views-atrium_intranet-block_2' => 1,
    'views-atrium_profile_blocks-block_1' => 0,
    'views-atrium_profile_blocks-block_2' => 0,
    'views-atrium_shoutbox_shouts-block_1' => 1,
    'views-atrium_shoutbox_users-block_1' => 0,
    'views-atrium_taxonomy-block_1' => 0,
    'views-d6af0b83befbd3a36210064bbba489a8' => 0,
    'views-fff60b5167ffbdd19460dca794bcc787' => 0,
    'views-messaging_shoutbox-block_1' => 0,
    'views-messaging_shoutbox-block_2' => 0,
    'xref-create' => 0,
  );

  $export['spaces_dashboard_blocks'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_dashboard_layouts';
  $strongarm->value = array(
    'default' => 1,
    'columns' => 1,
    'split' => 1,
    'wide' => 0,
    'login' => 0,
  );

  $export['spaces_dashboard_layouts'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_features';
  $strongarm->value = array(
    'atrium_groups' => '1',
    'atrium_members' => '1',
    'spaces_dashboard' => '1',
  );

  $export['spaces_features'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_preset_status';
  $strongarm->value = array(
    'og_controlled' => TRUE,
    'og_private' => TRUE,
    'og_public' => TRUE,
  );

  $export['spaces_preset_status'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_extensions_default';
  $strongarm->value = 'au avi bzip2 csv doc docx flv gif graffle gz htm html iso jpeg jpg kml kmz mov mp2 mp3 mp4 odp ods odt pages patch pdf png pps ppt pptx psd rar svg swf template tif tgz txt vsd wav wmv xls xlsx zip';

  $export['upload_extensions_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_list_default';
  $strongarm->value = 1;

  $export['upload_list_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_uploadsize_default';
  $strongarm->value = 20;

  $export['upload_uploadsize_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_usersize_default';
  $strongarm->value = 200;

  $export['upload_usersize_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_dimensions';
  $strongarm->value = '500x500';

  $export['user_picture_dimensions'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_file_size';
  $strongarm->value = '500';

  $export['user_picture_file_size'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_path';
  $strongarm->value = 'pictures';

  $export['user_picture_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_pictures';
  $strongarm->value = TRUE;

  $export['user_pictures'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_register';
  $strongarm->value = '0';

  $export['user_register'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_signatures';
  $strongarm->value = FALSE;

  $export['user_signatures'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_no_hover_links';
  $strongarm->value = TRUE;

  $export['views_no_hover_links'] = $strongarm;
  return $export;
}
