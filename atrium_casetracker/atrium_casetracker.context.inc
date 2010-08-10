<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_casetracker_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'casetracker_listing';
  $context->description = '';
  $context->tag = 'Casetracker';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'casetracker_basic_case' => 'casetracker_basic_case',
        'casetracker_basic_project' => 'casetracker_basic_project',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'casetracker_cases' => 'casetracker_cases',
        'casetracker_projects' => 'casetracker_projects',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'atrium_casetracker-filters' => array(
          'module' => 'atrium_casetracker',
          'delta' => 'filters',
          'region' => 'right',
          'weight' => 2,
        ),
        'views-casetracker_cases-block_2' => array(
          'module' => 'views',
          'delta' => 'casetracker_cases-block_2',
          'region' => 'right',
          'weight' => 3,
        ),
        'views-casetracker_projects-block_1' => array(
          'module' => 'views',
          'delta' => 'casetracker_projects-block_1',
          'region' => 'page_tools',
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'casetracker',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Casetracker');

  $export['casetracker_listing'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'casetracker_project';
  $context->description = '';
  $context->tag = 'Casetracker';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'casetracker_basic_project' => 'casetracker_basic_project',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-casetracker_cases-block_1' => array(
          'module' => 'views',
          'delta' => 'casetracker_cases-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Casetracker');

  $export['casetracker_project'] = $context;
  return $export;
}
