<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_members_context_default_contexts() {
  module_load_include('inc', 'atrium_members', 'atrium_members.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_context_default_contexts', $args);
}

/**
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_members_ctools_plugin_api() {
  module_load_include('inc', 'atrium_members', 'atrium_members.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function atrium_members_imagecache_default_presets() {
  module_load_include('inc', 'atrium_members', 'atrium_members.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_members_menu_default_items() {
  module_load_include('inc', 'atrium_members', 'atrium_members.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_menu_default_items', $args);
}

/**
 * Implementation of hook_spaces_presets().
 */
function atrium_members_spaces_presets() {
  module_load_include('inc', 'atrium_members', 'atrium_members.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_spaces_presets', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_members_user_default_permissions() {
  module_load_include('inc', 'atrium_members', 'atrium_members.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_user_default_permissions', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function atrium_members_strongarm() {
  module_load_include('inc', 'atrium_members', 'atrium_members.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_strongarm', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_members_views_default_views() {
  module_load_include('inc', 'atrium_members', 'atrium_members.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_members_views_default_views', $args);
}
