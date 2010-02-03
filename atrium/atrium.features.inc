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
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_ctools_plugin_api() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_filter_default_formats().
 */
function atrium_filter_default_formats() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_filter_default_formats', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function atrium_imagecache_default_presets() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_user_default_permissions() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  $args = func_get_args();
  module_load_include('inc', 'atrium', 'atrium');
  return atrium_user_default_permissions_extra();
}

/**
 * Implementation of hook_strongarm().
 */
function atrium_strongarm() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_strongarm', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_views_default_views() {
  module_load_include('inc', 'atrium', 'atrium.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_views_default_views', $args);
}
