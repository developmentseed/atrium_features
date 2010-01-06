<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function atrium_intranet_ctools_plugin_api() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_intranet_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_filter_default_formats().
 */
function atrium_intranet_filter_default_formats() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_intranet_filter_default_formats', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function atrium_intranet_imagecache_default_presets() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_intranet_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_intranet_user_default_permissions() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_intranet_user_default_permissions', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function atrium_intranet_strongarm() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_intranet_strongarm', $args);
}
