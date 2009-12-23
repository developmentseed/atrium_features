<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'atrium-section-taxonomy';
  $context->description = '';
  $context->tag = 'Intranet';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'atrium_taxonomy' => 'atrium_taxonomy',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-atrium_taxonomy-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_taxonomy-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );

  $export['atrium-section-taxonomy'] = $context;
  return $export;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _atrium_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
}
