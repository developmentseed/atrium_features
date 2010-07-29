<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_calendar_user_default_permissions() {
  $permissions = array();

  // Exported permission: create event content
  $permissions['create event content'] = array(
    'name' => 'create event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: create feed_ical content
  $permissions['create feed_ical content'] = array(
    'name' => 'create feed_ical content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'manager',
    ),
  );

  // Exported permission: create feed_ical_item content
  $permissions['create feed_ical_item content'] = array(
    'name' => 'create feed_ical_item content',
    'roles' => array(),
  );

  // Exported permission: delete any feed_ical content
  $permissions['delete any feed_ical content'] = array(
    'name' => 'delete any feed_ical content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete any feed_ical_item content
  $permissions['delete any feed_ical_item content'] = array(
    'name' => 'delete any feed_ical_item content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete own event content
  $permissions['delete own event content'] = array(
    'name' => 'delete own event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit any feed_ical content
  $permissions['edit any feed_ical content'] = array(
    'name' => 'edit any feed_ical content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit any feed_ical_item content
  $permissions['edit any feed_ical_item content'] = array(
    'name' => 'edit any feed_ical_item content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own event content
  $permissions['edit own event content'] = array(
    'name' => 'edit own event content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
