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
  return $export;
}
