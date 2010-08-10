<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_shoutbox_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'shoutbox_og';
  $context->description = '';
  $context->tag = 'Shoutbox';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'shoutbox_shouts:page_1' => 'shoutbox_shouts:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views--exp-shoutbox_shouts-page_1' => array(
          'module' => 'views',
          'delta' => '-exp-shoutbox_shouts-page_1',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-shoutbox_users-block_1' => array(
          'module' => 'views',
          'delta' => 'shoutbox_users-block_1',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Shoutbox');

  $export['shoutbox_og'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'shoutbox_sitewide';
  $context->description = '';
  $context->tag = 'Shoutbox';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium_shoutbox-shoutbox' => array(
          'module' => 'atrium_shoutbox',
          'delta' => 'shoutbox',
          'region' => 'palette',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Shoutbox');

  $export['shoutbox_sitewide'] = $context;
  return $export;
}
