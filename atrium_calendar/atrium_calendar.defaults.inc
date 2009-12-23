<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _atrium_calendar_content_default_fields() {
  $fields = array();

  // Exported field: field_date
  $fields[] = array(
    'field_name' => 'field_date',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'long',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'long',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'date',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
      'hour' => 'hour',
      'minute' => 'minute',
    ),
    'timezone_db' => '',
    'tz_handling' => 'none',
    'todate' => 'optional',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'long',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'm/d/Y - g:ia',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-3:+3',
      'label_position' => 'above',
      'default_value_custom' => '',
      'default_value_custom2' => '',
      'label' => 'Date',
      'weight' => '-3',
      'description' => '',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Exported field: field_date
  $fields[] = array(
    'field_name' => 'field_date',
    'type_name' => 'feed_ical_item',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'full' => array(
        'format' => 'field_date_long',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'field_date_long',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'date',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
      'hour' => 'hour',
      'minute' => 'minute',
    ),
    'timezone_db' => '',
    'tz_handling' => 'none',
    'todate' => 'optional',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'long',
    'widget' => array(
      'default_value' => 'now',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'Y-m-d H:i:s',
      'input_format_custom' => '',
      'increment' => 1,
      'text_parts' => array(),
      'year_range' => '-3:+3',
      'label_position' => 'above',
      'default_value_custom' => '',
      'default_value_custom2' => '',
      'label' => 'Date',
      'weight' => '-3',
      'description' => '',
      'type' => 'date_text',
      'module' => 'date',
    ),
  );

  // Translatables
  array(
    t('Date'),
  );

  return $fields;
}

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_calendar_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'calendar',
    'description' => '',
    'node' => array(
      '0' => 'event',
      '1' => 'feed_ical',
      '2' => 'feed_ical_item',
    ),
    'views' => array(
      '0' => 'atrium_calendar',
      '1' => 'atrium_calendar_feed_items',
      '2' => 'atrium_calendar_feeds',
      '3' => 'atrium_calendar_upcoming',
    ),
    'menu' => 'calendar',
    'block' => array(
      'atrium_calendar_mini' => array(
        'module' => 'atrium_calendar',
        'delta' => 'mini',
        'weight' => 20,
        'region' => 'right',
        'status' => '0',
        'label' => 'Atrium calendar: Mini calendar',
        'type' => 'context_ui',
      ),
      'views_atrium_calendar_upcoming-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_calendar_upcoming-block_1',
        'weight' => 21,
        'region' => 'right',
        'status' => '0',
        'label' => 'atrium_calendar_upcoming: Block',
        'type' => 'context_ui',
      ),
      'views_3d47b44f26df08825145e8a74a809061' => array(
        'module' => 'views',
        'delta' => '3d47b44f26df08825145e8a74a809061',
        'weight' => 20,
        'region' => 'content',
        'status' => '0',
        'label' => 'atrium_calendar_feed_items: Block',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_calendar_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Calendar',
    'path' => 'calendar',
    'weight' => '0',
    'description' => 'The calendar lets you share events and meetings with your team.',
  );
  // Translatables
  array(
    t('Calendar'),
    t('The calendar lets you share events and meetings with your team.'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_calendar_user_default_permissions() {
  $permissions = array();

  // Exported permission: create event content
  $permissions[] = array(
    'name' => 'create event content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: create feed_ical content
  $permissions[] = array(
    'name' => 'create feed_ical content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: create feed_ical_item content
  $permissions[] = array(
    'name' => 'create feed_ical_item content',
    'roles' => array(),
  );

  // Exported permission: delete any feed_ical content
  $permissions[] = array(
    'name' => 'delete any feed_ical content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete any feed_ical_item content
  $permissions[] = array(
    'name' => 'delete any feed_ical_item content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: delete own event content
  $permissions[] = array(
    'name' => 'delete own event content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit any feed_ical content
  $permissions[] = array(
    'name' => 'edit any feed_ical content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit any feed_ical_item content
  $permissions[] = array(
    'name' => 'edit any feed_ical_item content',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own event content
  $permissions[] = array(
    'name' => 'edit own event content',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  return $permissions;
}
