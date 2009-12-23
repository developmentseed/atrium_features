<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_book_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'spaces-feature-book';
  $context->description = '';
  $context->tag = 'Book';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'book' => 'book',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'atrium_book' => 'atrium_book',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'diff-inline' => array(
          'module' => 'diff',
          'delta' => 'inline',
          'region' => 'right',
          'weight' => 0,
        ),
        'atrium-book' => array(
          'module' => 'atrium',
          'delta' => 'book',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );

  $export['spaces-feature-book'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_book_ctools_plugin_api() {
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
function _atrium_book_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Documents',
    'path' => 'documents',
    'weight' => '0',
    'description' => 'The documents feature lets you store and share information and attachments.',
  );
  // Translatables
  array(
    t('Documents'),
    t('The documents feature lets you store and share information and attachments.'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_book_user_default_permissions() {
  $permissions = array();

  // Exported permission: add content to books
  $permissions[] = array(
    'name' => 'add content to books',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: administer book outlines
  $permissions[] = array(
    'name' => 'administer book outlines',
    'roles' => array(
      '0' => 'admin',
    ),
  );

  // Exported permission: create book content
  $permissions[] = array(
    'name' => 'create book content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: create new books
  $permissions[] = array(
    'name' => 'create new books',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: delete any book content
  $permissions[] = array(
    'name' => 'delete any book content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete own book content
  $permissions[] = array(
    'name' => 'delete own book content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit any book content
  $permissions[] = array(
    'name' => 'edit any book content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
