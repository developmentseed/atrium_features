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
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        '0' => 'atrium_taxonomy',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-atrium_taxonomy-block_1' => array(
          'module' => 'views',
          'delta' => 'atrium_taxonomy-block_1',
          'weight' => 20,
          'region' => 'right',
          'status' => '0',
          'label' => 'atrium_taxonomy: Archive block',
          'type' => 'context_ui',
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
