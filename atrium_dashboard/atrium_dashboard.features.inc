<?php

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_dashboard_menu_default_items() {
  module_load_include('inc', 'atrium_dashboard', 'atrium_dashboard.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_dashboard_menu_default_items', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_dashboard_views_default_views() {
  module_load_include('inc', 'atrium_dashboard', 'atrium_dashboard.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_dashboard_views_default_views', $args);
}
