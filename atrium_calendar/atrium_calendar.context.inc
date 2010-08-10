<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_calendar_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'calendar_calendar';
  $context->description = '';
  $context->tag = 'Calendar';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'event' => 'event',
        'feed_ical' => 'feed_ical',
        'feed_ical_item' => 'feed_ical_item',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'calendar_listing' => 'calendar_listing',
        'calendar_feed_items' => 'calendar_feed_items',
        'calendar_feeds' => 'calendar_feeds',
        'calendar_upcoming' => 'calendar_upcoming',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-calendar_upcoming-block_1' => array(
          'module' => 'views',
          'delta' => 'calendar_upcoming-block_1',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
    'menu' => 'calendar',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Calendar');

  $export['calendar_calendar'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'calendar_event';
  $context->description = '';
  $context->tag = 'Calendar';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'event' => 'event',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium_calendar-mini' => array(
          'module' => 'atrium_calendar',
          'delta' => 'mini',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Calendar');

  $export['calendar_event'] = $context;
  return $export;
}
