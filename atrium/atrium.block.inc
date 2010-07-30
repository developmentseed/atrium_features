<?php

/**
 * Welcome block for administrators.
 */
function _atrium_block_welcome_admin() {
  if (user_access('administer site configuration')) {
    $block = array();
    $block['subject'] = t('Welcome to @title', array('@title' => variable_get('site_name', 'Drupal')));

    // Video.
    // Set "wmode" to prevent z-index issues. see http://kb2.adobe.com/cps/155/tn_15523.html
    $video = '<embed wmode="opaque" src="http://blip.tv/play/hZ4ygcbWBwA" type="application/x-shockwave-flash" width="560" height="345" allowscriptaccess="always" allowfullscreen="true"></embed>';

    // Build links.
    $links = array();
    $item = menu_get_item('node/add/group');
    if ($item['access']) {
      $links[] = array(
        'title' => "<span class='spaces-feature feature-atrium_groups'></span>". t('Add @type', array('@type' => node_get_types('name', 'group'))),
        'href' => 'node/add/group',
      );
    }
    $item = menu_get_item('members/add');
    if ($item['access']) {
      $links[] = array(
        'title' => "<span class='spaces-feature feature-atrium_members'></span>". $item['title'],
        'href' => 'members/add',
      );
    }
    $item = menu_get_item('features');
    if ($item['access']) {
      $links[] = array(
        'title' => t('Customize features'),
        'href' => 'features',
      );
    }
    $links[] = array(
      'title' => t('Documentation & support'),
      'href' => 'http://community.openatrium.com',
    );

    // Admin link.
    $admin = '';
    if (spaces_access_admin()) {
      $link = l(t('customizing the dashboard'), $_GET['q'], array('fragment' => 'block-spaces_dashboard-editor', 'attributes' => array('class' => 'palette-toggle')));
      $admin = t('You can remove this block by !customize_dashboard.', array('!customize_dashboard' => $link));
    }

    $block['content'] = theme('atrium_welcome', $video, $links, $admin);
    return $block;
  }
}

/**
 * Welcome block for members.
 */
function _atrium_block_welcome_member() {
  $space = spaces_get_space();
  if (user_access('access content') && $space && $space->type === 'og') {
    $block = array();
    $block['subject'] = t('Welcome to @title', array('@title' => $space->title()));

    // Video.
    // Set "wmode" to prevent z-index issues. see http://kb2.adobe.com/cps/155/tn_15523.html
    $video = '<embed wmode="opaque" src="http://blip.tv/play/hZ4ygcbWJgA" type="application/x-shockwave-flash" width="560" height="345" allowscriptaccess="always" allowfullscreen="true"></embed>';

    // Build links.
    $links = array();
    $feature_map = features_get_component_map('node');
    foreach (system_admin_menu_block(menu_get_item('node/add')) as $menu_item) {
      $args = explode('/', $menu_item['href']);
      $type = str_replace('-', '_', array_pop($args));
      if (!empty($feature_map[$type])) {
        $feature = reset($feature_map[$type]);
        $menu_item['title'] = t('Add @type', array('@type' => $menu_item['title']));
        $menu_item['title'] = "<span class='spaces-feature feature-{$feature}'></span>{$menu_item['title']}";
        $links[] = $menu_item;
      }
    }

    // Admin link.
    $admin = '';
    if (spaces_access_admin()) {
      $link = l(t('customizing the dashboard'), $_GET['q'], array('fragment' => 'block-spaces_dashboard-editor', 'attributes' => array('class' => 'palette-toggle')));
      $admin = t('You can remove this block by !customize_dashboard.', array('!customize_dashboard' => $link));
    }
    $block['content'] = theme('atrium_welcome', $video, $links, $admin);
    return $block;
  }
}

/**
 * User starting point block.
 */
function _atrium_block_account() {
  global $user;
  $block = array();
  if ($user->uid) {
    $block['subject'] = theme('user_picture', $user) . check_plain($user->name);
    $block['content'] = "<div class='panes clear-block'><div class='pane-left'>";
    $block['content'] .= "<h3>". t('My account') ."</h3>". theme('links', atrium_account_links());
    $block['content'] .= "</div>";

    // My groups
    if ($view = views_get_view('groups_listing')) {
      $block['content'] .= "<div class='pane-right'>";
      $block['content'] .= "<h3>". t('My groups') ."</h3>" . $view->execute_display('default');
      $block['content'] .= "</div>";
      $view->destroy();
    }
    $block['content'] .= "</div>";
    return $block;
  }
  else {
    $item = menu_get_item('user/login');
    if ($item && $item['access']) {
      return array('content' => l($item['title'], $item['href']));
    }
  }
}

/**
 * Space admin links block.
 */
function _atrium_block_admin_links() {
  if ($links = atrium_admin_links()) {
    return array('subject' => "<span class='icon'></span> ". t('Settings'), 'content' => theme('links', $links));
  }
}

/**
 * Content creation block.
 */
function _atrium_block_create() {
  $feature_map = features_get_component_map('node');
  $item = menu_get_item('node/add');
  $links = array();
  foreach (system_admin_menu_block($item) as $menu_item) {
    $args = explode('/', $menu_item['href']);
    $type = str_replace('-', '_', array_pop($args));
    if (!empty($feature_map[$type])) {
      $feature = reset($feature_map[$type]);
      $menu_item['title'] = "<span class='spaces-feature feature-{$feature}'></span>{$menu_item['title']}";
      $menu_item['html'] = TRUE;
      $links["$feature-{$type}"] = $menu_item;
    }
    else {
      $menu_item['title'] = "<span class='spaces-feature node-{$type}'></span>{$menu_item['title']}";
      $menu_item['html'] = TRUE;
      $links["{$type}"] = $menu_item;
    }
  }
  ksort($links);
  return array('subject' => "<span class='icon'></span> {$item['title']}", 'content' => theme('links', $links));
}

/**
 * Search block.
 */
function _atrium_block_search() {
  if (user_access('access content') && user_access('search content')) {
    return array('subject' => "<span class='icon'></span> ". t('Search'), 'content' => drupal_get_form('atrium_search_form'));
  }
}

/**
 * User links block.
 */
function _atrium_block_user_links() {
  if ($links = atrium_user_links()) {
    return array('subject' => t('Membership'), 'content' => theme('links', $links));
  }
}

/**
 * Help.
 */
function _atrium_block_help() {
  if ($helptext = theme('help')) {
    return array('subject' => t('Need help?'), 'content' => $helptext);
  }
}
