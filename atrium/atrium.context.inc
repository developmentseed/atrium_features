<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'global';
  $context->description = '';
  $context->tag = 'Intranet';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
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

  // Translatables
  // Included for use with string extractors like potx.
  t('Intranet');

  $export['global'] = $context;
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

  // Translatables
  // Included for use with string extractors like potx.
  t('Theme');

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

  // Translatables
  // Included for use with string extractors like potx.
  t('Theme');

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
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Dashboard');

  $export['spaces_dashboard-custom-1'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'taxonomy_listing';
  $context->description = '';
  $context->tag = 'Intranet';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'taxonomy_listing' => 'taxonomy_listing',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-taxonomy_listing-block_1' => array(
          'module' => 'views',
          'delta' => 'taxonomy_listing-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Intranet');

  $export['taxonomy_listing'] = $context;
  return $export;
}
