<?php

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_dashboard_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Dashboard',
    'path' => 'dashboard',
    'weight' => '0',
    'description' => 'The dashboard lets you monitor recent activity in a group.',
  );
  $items[] = array(
    'title' => 'Home',
    'path' => 'home',
    'weight' => '0',
    'description' => 'Site homepage lets you monitor recent activity in all your groups.',
  );
  $items[] = array(
    'title' => 'Profile',
    'path' => 'profile',
    'weight' => '0',
    'description' => 'The user profile lets you monitor recent activity for a user.',
  );
  // Translatables
  array(
    t('Dashboard'),
    t('Home'),
    t('Profile'),
    t('Site homepage lets you monitor recent activity in all your groups.'),
    t('The dashboard lets you monitor recent activity in a group.'),
    t('The user profile lets you monitor recent activity for a user.'),
  );


  return $items;
}
