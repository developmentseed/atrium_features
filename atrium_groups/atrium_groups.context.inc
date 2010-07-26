<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_groups_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'groups_listing';
  $context->description = '';
  $context->tag = 'Groups';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'groups_listing' => 'groups_listing',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'og',
  );
  $context->condition_mode = 0;

  $translatables['groups_listing'] = array(
    t('Groups'),
  );

  $export['groups_listing'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile_groups';
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
        'views-groups_listing-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_listing-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  $translatables['profile_groups'] = array(
    t('Profile'),
  );

  $export['profile_groups'] = $context;
  return $export;
}
