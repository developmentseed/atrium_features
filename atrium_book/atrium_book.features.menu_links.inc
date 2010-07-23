<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function atrium_book_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: features:notebook
  $menu_links['features:notebook'] = array(
    'menu_name' => 'features',
    'link_path' => 'notebook',
    'router_path' => 'notebook',
    'link_title' => 'Notebook',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  array(
    t('Notebook'),
  );


  return $menu_links;
}
