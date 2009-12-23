<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_casetracker_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-casetracker-project';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        '0' => 'casetracker_basic_project',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-atrium_casetracker-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_casetracker-block_1',
          'weight' => 50,
          'region' => 'content',
          'status' => '0',
          'label' => 'atrium_casetracker: Project cases (newest)',
          'type' => 'context_ui',
        ),
      ),
    ),
  );

  $export['atrium-casetracker-project'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-feature-casetracker';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        '0' => 'casetracker_basic_project',
        '1' => 'casetracker_basic_case',
      ),
      'options' => array(),
    ),
    'views' => array(
      'values' => array(
        '0' => 'atrium_casetracker',
        '1' => 'atrium_casetracker_projects',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'menu' => 'casetracker',
    'block' => array(
      'blocks' => array(
        'atrium_casetracker-book' => array(
          'module' => 'atrium_casetracker',
          'delta' => 'book',
          'weight' => 50,
          'region' => 'right',
          'status' => '0',
          'label' => 'Atrium: Case Tracker book',
          'type' => 'context_ui',
        ),
        'atrium_casetracker-filters' => array(
          'module' => 'atrium_casetracker',
          'delta' => 'filters',
          'weight' => 51,
          'region' => 'right',
          'status' => '0',
          'label' => 'Atrium: Case Tracker filter',
          'type' => 'context_ui',
        ),
        'views-atrium_casetracker-block_2' => array(
          'module' => 'views',
          'delta' => 'atrium_casetracker-block_2',
          'weight' => 52,
          'region' => 'right',
          'status' => '0',
          'label' => 'atrium_casetracker: My cases',
          'type' => 'context_ui',
        ),
      ),
    ),
  );

  $export['spaces-feature-casetracker'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_casetracker_ctools_plugin_api() {
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
function _atrium_casetracker_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Case Tracker',
    'path' => 'casetracker',
    'weight' => '0',
    'description' => 'The casetracker lets you assign tasks to yourself and others and track the progress on a project.',
  );
  // Translatables
  array(
    t('Case Tracker'),
    t('The casetracker lets you assign tasks to yourself and others and track the progress on a project.'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_casetracker_user_default_permissions() {
  $permissions = array();

  // Exported permission: access case tracker
  $permissions[] = array(
    'name' => 'access case tracker',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: create cases
  $permissions[] = array(
    'name' => 'create cases',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: create projects
  $permissions[] = array(
    'name' => 'create projects',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own cases
  $permissions[] = array(
    'name' => 'edit own cases',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit own projects
  $permissions[] = array(
    'name' => 'edit own projects',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  return $permissions;
}
