<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_activity_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'activity_profile';
  $context->description = '';
  $context->tag = 'Profile';
  $context->conditions = array(
    'user_page' => array(
      'values' => array(
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'all',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-activity_listing-block_3' => array(
          'module' => 'views',
          'delta' => 'activity_listing-block_3',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');

  $export['activity_profile'] = $context;
  return $export;
}
