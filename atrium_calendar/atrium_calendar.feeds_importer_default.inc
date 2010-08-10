<?php

/**
 * Implementation of hook_feeds_importer_default().
 */
function atrium_calendar_feeds_importer_default() {
  $export = array();
  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'atrium_calendar_ical_feed';
  $feeds_importer->config = array(
    'name' => 'iCal feed',
    'description' => 'Importer for iCal feeds.',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'ParserIcalFeedsParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'feed_ical_item',
        'update_existing' => 1,
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'ical_date',
            'target' => 'field_date:start',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'ical_date',
            'target' => 'field_date:end',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'description',
            'target' => 'body',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'timestamp',
            'target' => 'created',
            'unique' => FALSE,
          ),
        ),
      ),
    ),
    'content_type' => 'feed_ical',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
  );

  $export['atrium_calendar_ical_feed'] = $feeds_importer;
  return $export;
}
