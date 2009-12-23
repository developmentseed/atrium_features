<?php

/**
 * Implementation of hook_content_default_fields().
 */
function atrium_blog_content_default_fields() {
  module_load_include('inc', 'atrium_blog', 'atrium_blog.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_blog_content_default_fields', $args);
}

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_blog_context_default_contexts() {
  module_load_include('inc', 'atrium_blog', 'atrium_blog.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_blog_context_default_contexts', $args);
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_blog_menu_default_items() {
  module_load_include('inc', 'atrium_blog', 'atrium_blog.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_blog_menu_default_items', $args);
}

/**
 * Implementation of hook_node_info().
 */
function atrium_blog_node_info() {
  module_load_include('inc', 'atrium_blog', 'atrium_blog.features.node');
  $args = func_get_args();
  return call_user_func_array('_atrium_blog_node_info', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_blog_user_default_permissions() {
  module_load_include('inc', 'atrium_blog', 'atrium_blog.defaults');
  $args = func_get_args();
  return call_user_func_array('_atrium_blog_user_default_permissions', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_blog_views_default_views() {
  module_load_include('inc', 'atrium_blog', 'atrium_blog.features.views');
  $args = func_get_args();
  return call_user_func_array('_atrium_blog_views_default_views', $args);
}
