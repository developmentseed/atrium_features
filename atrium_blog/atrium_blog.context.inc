<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_blog_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'blog_listing';
  $context->description = '';
  $context->tag = 'Blog';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'blog_listing' => 'blog_listing',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-blog_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'blog_comments-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'blog',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blog');

  $export['blog_listing'] = $context;
  return $export;
}
