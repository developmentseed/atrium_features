<?php

/**
 * Implementation of hook_strongarm().
 */
function atrium_shoutbox_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_activity_update_type_shoutbox';
  $strongarm->value = 0;

  $export['atrium_activity_update_type_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_shoutbox';
  $strongarm->value = '0';

  $export['comment_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_shoutbox';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_shoutbox';
  $strongarm->value = array();

  $export['notifications_content_type_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_shoutbox';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_shoutbox';
  $strongarm->value = 0;

  $export['show_diff_inline_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_shoutbox';
  $strongarm->value = 0;

  $export['show_preview_changes_shoutbox'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_shoutbox';
  $strongarm->value = '0';

  $export['upload_shoutbox'] = $strongarm;
  return $export;
}
