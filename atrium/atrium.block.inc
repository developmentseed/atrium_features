<?php

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
    if ($view = views_get_view('atrium_groups')) {
      $block['content'] .= "<div class='pane-right'>";
      $block['content'] .= "<h3>". t('My groups') ."</h3>" . $view->execute_display('default');
      $block['content'] .= "</div></div>";
      $view->destroy();
    }
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
 * Feature-aware book block.
 */
function _atrium_block_book() {
  context_set('atrium', 'book', 'rendering');

  $space = spaces_get_space();
  $block = array();
  if ($space) {
    if ($node = menu_get_object()) {
      $current_bid = empty($node->book['bid']) ? 0 : $node->book['bid'];
    }
    // Set customized title
    $features = spaces_features();
    $block['subject'] = t('Documents');

    // Generate book tree per book node in current space
    $output = '';
    if ($view = views_get_view('atrium_book_current')) {
      $view->set_display();
      $view->set_items_per_page(0);
      $view->execute();
      if (is_array($view->result) && count($view->result)) {
        foreach($view->result as $row) {
          $output .= menu_tree(book_menu_name($row->nid));
        }
      }
    }
    $block['content'] = $output;
  }

  context_set('atrium', 'book', FALSE);

  return $block;
}

/**
 * Content creation block.
 */
function _atrium_block_create() {
  $feature_map = spaces_features_map('node');
  $item = menu_get_item('node/add');
  $links = array();
  foreach (system_admin_menu_block($item) as $menu_item) {
    $args = explode('/', $menu_item['href']);
    $type = str_replace('-', '_', array_pop($args));
    if (isset($feature_map[$type])) {
      $feature = $feature_map[$type];
      $menu_item['title'] = "<span class='spaces-feature feature-{$feature}'></span>{$menu_item['title']}";
      $menu_item['html'] = TRUE;
      $links["$feature-{$type}"] = $menu_item;
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
