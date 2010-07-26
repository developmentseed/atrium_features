<?php

/**
 * Implementation of hook_strongarm().
 */
function atrium_casetracker_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_archivable_casetracker_basic_project';
  $strongarm->value = TRUE;

  $export['atrium_archivable_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_update_type_casetracker_basic_case';
  $strongarm->value = 1;

  $export['atrium_update_type_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'atrium_update_type_casetracker_basic_project';
  $strongarm->value = 1;

  $export['atrium_update_type_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'casetracker_default_assign_to';
  $strongarm->value = 'Anonymous';

  $export['casetracker_default_assign_to'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'casetracker_view_assignee_options';
  $strongarm->value = 'casetracker_override_assignee_options';

  $export['casetracker_view_assignee_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'casetracker_view_project_options';
  $strongarm->value = 'casetracker_override_project_options';

  $export['casetracker_view_project_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_casetracker_basic_case';
  $strongarm->value = '2';

  $export['comment_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_casetracker_basic_project';
  $strongarm->value = '0';

  $export['comment_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_casetracker_basic_case';
  $strongarm->value = '3';

  $export['comment_controls_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_casetracker_basic_case';
  $strongarm->value = '4';

  $export['comment_default_mode_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_casetracker_basic_case';
  $strongarm->value = '2';

  $export['comment_default_order_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_casetracker_basic_case';
  $strongarm->value = '200';

  $export['comment_default_per_page_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_casetracker_basic_case';
  $strongarm->value = '1';

  $export['comment_form_location_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_casetracker_basic_case';
  $strongarm->value = '0';

  $export['comment_preview_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_casetracker_basic_case';
  $strongarm->value = '0';

  $export['comment_subject_field_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_upload_casetracker_basic_case';
  $strongarm->value = '1';

  $export['comment_upload_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_casetracker_basic_case';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'revision',
  );

  $export['node_options_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_casetracker_basic_project';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'revision',
  );

  $export['node_options_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_casetracker_basic_case';
  $strongarm->value = array(
    '0' => 'thread',
    '1' => 'nodetype',
    '2' => 'author',
  );

  $export['notifications_content_type_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_casetracker_basic_project';
  $strongarm->value = array(
    '0' => 'thread',
    '1' => 'nodetype',
    '2' => 'author',
  );

  $export['notifications_content_type_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_casetracker_basic_case';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_casetracker_basic_project';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_casetracker_basic_case';
  $strongarm->value = FALSE;

  $export['show_diff_inline_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_casetracker_basic_project';
  $strongarm->value = TRUE;

  $export['show_diff_inline_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_casetracker_basic_case';
  $strongarm->value = 0;

  $export['show_preview_changes_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_casetracker_basic_project';
  $strongarm->value = 0;

  $export['show_preview_changes_casetracker_basic_project'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_casetracker_basic_case';
  $strongarm->value = '1';

  $export['upload_casetracker_basic_case'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_casetracker_basic_project';
  $strongarm->value = '1';

  $export['upload_casetracker_basic_project'] = $strongarm;
  return $export;
}
