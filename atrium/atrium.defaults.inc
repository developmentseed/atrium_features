<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'atrium',
    'attribute' => 'section',
    'value' => 'taxonomy',
    'description' => '',
    'views' => array(
      '0' => 'atrium_taxonomy',
    ),
    'block' => array(
      'views_atrium_taxonomy-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_taxonomy-block_1',
        'weight' => 20,
        'region' => 'right',
        'status' => '0',
        'label' => 'atrium_taxonomy: Archive block',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}
