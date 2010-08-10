<?php

/**
 * Implementation of hook_spaces_presets().
 */
function atrium_members_spaces_presets() {
  $export = array();
  $spaces_presets = new stdClass;
  $spaces_presets->disabled = FALSE; /* Edit this to true to make a default spaces_presets disabled initially */
  $spaces_presets->api_version = 3;
  $spaces_presets->name = 'atrium_members_simple';
  $spaces_presets->title = 'Simple profile';
  $spaces_presets->description = 'A simple profile with a blog, calendar and dashboard.';
  $spaces_presets->space_type = 'user';
  $spaces_presets->value = array(
    'variable' => array(
      'spaces_features' => array(
        'spaces_dashboard' => '1',
      ),
      'spaces_dashboard_custom' => array(
        'custom-1' => 'Dashboard',
      ),
      'spaces_setting_home' => 'profile',
      'spaces_dashboard_blocks' => array(
        'atrium-welcome_admin' => 1,
        'atrium-welcome_member' => 1,
        'atrium_calendar-mini' => 1,
        'views-calendar_upcoming-block_1' => 1,
        'views-casetracker_projects-block_1' => 1,
        'views-blog_listing-block_2' => 1,
        'views-blog_comments-block_1' => 1,
        'views-casetracker_cases-block_3' => 1,
        'views-casetracker_cases-block_4' => 1,
        'views-groups_listing-block_1' => 1,
        'views-activity_listing-block_1' => 1,
        'views-activity_listing-block_2' => 1,
      ),
    ),
    'context' => array(
      'spaces_dashboard-custom-1:reaction:block' => array(
        'blocks' => array(
          'views-activity_listing-block_1' => array(
            'module' => 'views',
            'delta' => 'activity_listing-block_1',
            'region' => 'content',
            'weight' => 0,
          ),
          'views-blog_comments-block_1' => array(
            'module' => 'views',
            'delta' => 'blog_comments-block_1',
            'region' => 'right',
            'weight' => 0,
          ),
        ),
      ),
      'spaces_dashboard-custom-2:reaction:block' => array(
        'blocks' => array(),
      ),
      'spaces_dashboard-custom-3:reaction:block' => array(
        'blocks' => array(),
      ),
      'spaces_dashboard-custom-4:reaction:block' => array(
        'blocks' => array(),
      ),
      'spaces_dashboard-custom-5:reaction:block' => array(
        'blocks' => array(),
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A simple profile with a blog, calendar and dashboard.');
  t('Simple profile');

  $export['atrium_members_simple'] = $spaces_presets;
  return $export;
}
