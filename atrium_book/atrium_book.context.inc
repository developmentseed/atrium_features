<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_book_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'book_casetracker';
  $context->description = '';
  $context->tag = 'Casetracker';
  $context->conditions = array(
    'bookroot' => array(
      'values' => array(
        'casetracker_basic_project' => 'casetracker_basic_project',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'diff-inline' => array(
          'module' => 'diff',
          'delta' => 'inline',
          'region' => 'right',
          'weight' => 0,
        ),
        'atrium_book-book' => array(
          'module' => 'atrium_book',
          'delta' => 'book',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
    'menu' => 'casetracker',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Casetracker');

  $export['book_casetracker'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'book_listing';
  $context->description = '';
  $context->tag = 'Book';
  $context->conditions = array(
    'bookroot' => array(
      'values' => array(
        'book' => 'book',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'book_listing' => 'book_listing',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'diff-inline' => array(
          'module' => 'diff',
          'delta' => 'inline',
          'region' => 'right',
          'weight' => 0,
        ),
        'atrium_book-book_all' => array(
          'module' => 'atrium_book',
          'delta' => 'book_all',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
    'menu' => 'notebook',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Book');

  $export['book_listing'] = $context;
  return $export;
}
