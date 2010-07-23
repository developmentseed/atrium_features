<?php

/**
 * Implementation of hook_user_default_roles().
 */
function atrium_user_default_roles() {
  $roles = array();

  // Exported role: admin
  $roles['admin'] = array(
    'name' => 'admin',
  );

  // Exported role: anonymous user
  $roles['anonymous user'] = array(
    'name' => 'anonymous user',
  );

  // Exported role: authenticated user
  $roles['authenticated user'] = array(
    'name' => 'authenticated user',
  );

  // Exported role: manager
  $roles['manager'] = array(
    'name' => 'manager',
  );

  return $roles;
}
