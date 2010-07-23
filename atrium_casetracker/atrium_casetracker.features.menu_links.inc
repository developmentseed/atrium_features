<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function atrium_casetracker_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: features:casetracker
  $menu_links['features:casetracker'] = array(
    'menu_name' => 'features',
    'link_path' => 'casetracker',
    'router_path' => 'casetracker',
    'link_title' => 'Case Tracker',
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
    t('Case Tracker'),
  );


  return $menu_links;
}
