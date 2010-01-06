<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_context_default_contexts() {
  $export = array();
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

  $export['atrium-section-taxonomy'] = $context;

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
        'atrium_account' => array(
          'module' => 'atrium',
          'delta' => 'account',
          'region' => 'header',
          'weight' => 0,
        ),
        'atrium_user_links' => array(
          'module' => 'atrium',
          'delta' => 'user_links',
          'region' => 'header',
          'weight' => 1,
        ),
        'atrium_create' => array(
          'module' => 'atrium',
          'delta' => 'create',
          'region' => 'space_tools',
          'weight' => 0,
        ),
        'atrium_admin_links' => array(
          'module' => 'atrium',
          'delta' => 'admin_links',
          'region' => 'space_tools',
          'weight' => 1,
        ),
        'atrium_search' => array(
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
      ),
    ),
  );

  $export['atrium-intranet-global'] = $context;
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

  $export['layout_wide'] = $context;

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
  else if ($module == "system" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _atrium_strongarm() {
  $export = array();
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
  $strongarm->value = FALSE;

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
  $strongarm->name = 'admin_toolbar';
  $strongarm->value = array(
    'layout' => 'vertical',
    'position' => 'nw',
    'blocks' => array(
      'spaces-menu_editor' => 'spaces-menu_editor',
      'spaces_dashboard-editor' => 'spaces_dashboard-editor',
      'admin-create' => 'admin-create',
      'admin-menu' => 'admin-menu',
      'context_ui-editor' => 0,
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
  $strongarm->name = 'feedapi_allow_html_all';
  $strongarm->value = FALSE;

  $export['feedapi_allow_html_all'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'feedapi_allowed_html_tags';
  $strongarm->value = '<div> <h1> <h2> <h3> <h4> <h5> <h6> <img> <a> <b> <br> <dd> <dl> <dt> <em> <i> <li> <ol> <p> <strong> <u> <ul> <sup> <sub>';

  $export['feedapi_allowed_html_tags'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'feedapi_cron_percentage';
  $strongarm->value = '25';

  $export['feedapi_cron_percentage'] = $strongarm;
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
  $strongarm->name = 'seed_imagecache_attachment';
  $strongarm->value = 'fileview';

  $export['seed_imagecache_attachment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'welcome';

  $export['site_frontpage'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_features';
  $strongarm->value = array(
    'atrium_calendar' => '0',
    'atrium_groups' => '1',
    'atrium_intranet' => '1',
    'atrium_members' => '1',
    'spaces_dashboard' => '1',
  );

  $export['spaces_features'] = $strongarm;
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
  $strongarm->name = 'views_no_hover_links';
  $strongarm->value = TRUE;

  $export['views_no_hover_links'] = $strongarm;
  return $export;
}
