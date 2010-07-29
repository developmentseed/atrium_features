<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_profile_user_default_permissions() {
  $permissions = array();

  // Exported permission: create profile content
  $permissions['create profile content'] = array(
    'name' => 'create profile content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: delete own profile content
  $permissions['delete own profile content'] = array(
    'name' => 'delete own profile content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit own profile content
  $permissions['edit own profile content'] = array(
    'name' => 'edit own profile content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
