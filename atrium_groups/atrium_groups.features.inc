<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_groups_context_default_contexts() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_context_default_contexts', $args);
}

/**
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_groups_ctools_plugin_api() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_groups_menu_default_items() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_menu_default_items', $args);
}

/**
 * Implementation of hook_node_info().
 */
function atrium_groups_node_info() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.features.node');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_node_info', $args);
}

/**
 * Implementation of hook_spaces_presets().
 */
function atrium_groups_spaces_presets() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_spaces_presets', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_groups_user_default_permissions() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_user_default_permissions', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function atrium_groups_strongarm() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_strongarm', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_groups_views_default_views() {
  module_load_include('inc', 'atrium_groups', 'atrium_groups.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_groups_views_default_views', $args);
}
