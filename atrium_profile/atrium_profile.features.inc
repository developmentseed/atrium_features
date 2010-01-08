<?php

/**
 * Implementation of hook_content_default_fields().
 */
function atrium_profile_content_default_fields() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_profile_content_default_fields', $args);
}

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_profile_context_default_contexts() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_profile_context_default_contexts', $args);
}

/**
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_profile_ctools_plugin_api() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_profile_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_node_info().
 */
function atrium_profile_node_info() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.features.node');
  $args = func_get_args();
  return call_user_func_array('_atrium_profile_node_info', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_profile_user_default_permissions() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_profile_user_default_permissions', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function atrium_profile_strongarm() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_profile_strongarm', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_profile_views_default_views() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_profile_views_default_views', $args);
}
