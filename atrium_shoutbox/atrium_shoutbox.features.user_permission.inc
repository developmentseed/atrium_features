<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_shoutbox_user_default_permissions() {
  $permissions = array();

  // Exported permission: create shoutbox
  $permissions['create shoutbox'] = array(
    'name' => 'create shoutbox',
    'roles' => array(),
  );

  // Exported permission: post messages to shoutbox
  $permissions['post messages to shoutbox'] = array(
    'name' => 'post messages to shoutbox',
    'roles' => array(
      '0' => 'admin',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
