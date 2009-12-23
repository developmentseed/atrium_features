<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_casetracker_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'atrium',
    'attribute' => 'casetracker',
    'value' => 'project',
    'description' => '',
    'node' => array(
      '0' => 'casetracker_basic_project',
    ),
    'block' => array(
      'views_atrium_casetracker-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_casetracker-block_1',
        'weight' => 50,
        'region' => 'content',
        'status' => '0',
        'label' => 'atrium_casetracker: Project cases (newest)',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'casetracker',
    'description' => '',
    'menu' => 'casetracker',
    'node' => array(
      '0' => 'casetracker_basic_project',
      '1' => 'casetracker_basic_case',
    ),
    'views' => array(
      '0' => 'atrium_casetracker',
      '1' => 'atrium_casetracker_projects',
    ),
    'block' => array(
      'atrium_casetracker_book' => array(
        'module' => 'atrium_casetracker',
        'delta' => 'book',
        'weight' => 50,
        'region' => 'right',
        'status' => '0',
        'label' => 'Atrium: Case Tracker book',
        'type' => 'context_ui',
      ),
      'atrium_casetracker_filters' => array(
        'module' => 'atrium_casetracker',
        'delta' => 'filters',
        'weight' => 51,
        'region' => 'right',
        'status' => '0',
        'label' => 'Atrium: Case Tracker filter',
        'type' => 'context_ui',
      ),
      'views_atrium_casetracker-block_2' => array(
        'module' => 'views',
        'delta' => 'atrium_casetracker-block_2',
        'weight' => 52,
        'region' => 'right',
        'status' => '0',
        'label' => 'atrium_casetracker: My cases',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
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
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: create cases
  $permissions[] = array(
    'name' => 'create cases',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
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
      '0' => 'authenticated user',
      '1' => 'admin',
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
