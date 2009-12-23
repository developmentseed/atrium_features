<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_context_default_contexts() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_context_default_contexts', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_views_default_views() {
  module_load_include('inc', 'atrium', 'atrium.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_views_default_views', $args);
}
