<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_calendar_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'module' => 'features',
      'description' => t('A calendar event with start and optional end times.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
    ),
    'feed_ical' => array(
      'name' => t('iCal Feed'),
      'module' => 'features',
      'description' => t('A feed used to aggregate events from external iCal calendars.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => t(''),
    ),
    'feed_ical_item' => array(
      'name' => t('iCal Event'),
      'module' => 'features',
      'description' => t('An event aggregated from an external iCal feed.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
    ),
  );
  return $items;
}
