<?php

/**
 * Implementation of hook_filter_default_formats().
 */
function atrium_filter_default_formats() {
  $formats = array();

  // Exported format: Full HTML
  $formats['Full HTML'] = array(
    'name' => 'Full HTML',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'manager',
    ),
    'filters' => array(
      '0' => array(
        'module' => 'codefilter',
        'delta' => '0',
        'weight' => '0',
      ),
      '1' => array(
        'module' => 'filter',
        'delta' => '2',
        'weight' => '0',
      ),
      '2' => array(
        'module' => 'filter',
        'delta' => '1',
        'weight' => '1',
      ),
      '3' => array(
        'module' => 'filter',
        'delta' => '3',
        'weight' => '10',
      ),
    ),
  );

  // Exported format: Messaging plain text
  $formats['Messaging plain text'] = array(
    'name' => 'Messaging plain text',
    'roles' => array(),
    'filters' => array(
      '0' => array(
        'module' => 'filter',
        'delta' => '1',
        'weight' => '-10',
      ),
      '1' => array(
        'module' => 'messaging',
        'delta' => '1',
        'weight' => '-9',
      ),
    ),
  );

  // Exported format: Markdown
  $formats['Markdown'] = array(
    'name' => 'Markdown',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'administrator',
      '3' => 'manager',
    ),
    'filters' => array(
      '0' => array(
        'module' => 'markdown',
        'delta' => '0',
        'weight' => '-10',
      ),
      '1' => array(
        'module' => 'filter',
        'delta' => '2',
        'weight' => '-9',
      ),
      '2' => array(
        'module' => 'filter',
        'delta' => '0',
        'weight' => '-8',
      ),
      '3' => array(
        'module' => 'codefilter',
        'delta' => '0',
        'weight' => '-7',
      ),
      '4' => array(
        'module' => 'filter',
        'delta' => '3',
        'weight' => '-6',
      ),
    ),
  );

  return $formats;
}
