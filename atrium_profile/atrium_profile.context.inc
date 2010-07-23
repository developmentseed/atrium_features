<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_profile_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile_display';
  $context->description = '';
  $context->tag = 'Profile';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'profile_display' => 'profile_display',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-profile_blocks-block_2' => array(
          'module' => 'views',
          'delta' => 'profile_blocks-block_2',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-profile_blocks-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_blocks-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['profile_display'] = array(
    t('Profile'),
  );

  $export['profile_display'] = $context;
  return $export;
}
