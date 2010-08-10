<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_members_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'members_directory';
  $context->description = '';
  $context->tag = 'Members';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'members_listing' => 'members_listing',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium_members-addform' => array(
          'module' => 'atrium_members',
          'delta' => 'addform',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Members');

  $export['members_directory'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'members_section';
  $context->description = '';
  $context->tag = 'Members';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'members/add' => 'members/add',
        'members/add/*' => 'members/add/*',
      ),
    ),
    'views' => array(
      'values' => array(
        'members_listing' => 'members_listing',
      ),
    ),
  );
  $context->reactions = array(
    'menu' => 'members',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Members');

  $export['members_section'] = $context;
  return $export;
}
