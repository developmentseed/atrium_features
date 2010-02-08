<?php

/**
 * Implementation of hook_content_default_fields().
 */
function atrium_calendar_content_default_fields() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_content_default_fields', $args);
}

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_calendar_context_default_contexts() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_context_default_contexts', $args);
}

/**
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_calendar_ctools_plugin_api() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_feeds_importer_default().
 */
function atrium_calendar_feeds_importer_default() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_feeds_importer_default', $args);
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_calendar_menu_default_items() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_menu_default_items', $args);
}

/**
 * Implementation of hook_node_info().
 */
function atrium_calendar_node_info() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.features.node');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_node_info', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_calendar_user_default_permissions() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_user_default_permissions', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function atrium_calendar_strongarm() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_strongarm', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_calendar_views_default_views() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_calendar_views_default_views', $args);
}
