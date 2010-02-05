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
 * Feature-aware book block. Show only the current book.
 */
function _atrium_block_book() {
  $node = menu_get_object();
  if (!empty($node->book['bid'])) {
    // Only show the block if the user has view access for the top-level node.
    $title = db_result(db_query(db_rewrite_sql('SELECT n.title FROM {node} n WHERE n.nid = %d'), $node->book['bid']));
    if ($title) {
      // Dynamic block
      if (module_exists('admin')) {
        $data = array_shift(menu_tree_all_data($node->book['menu_name']));
        if ($data['below']) {
          drupal_add_css(drupal_get_path('module', 'admin') .'/includes/admin.menu.css');
          drupal_add_js(drupal_get_path('module', 'admin') .'/includes/jquery.drilldown.js');
          drupal_add_js(drupal_get_path('module', 'atrium') .'/atrium.js');
          drupal_add_js(array('atriumBookPath' => url($_GET['q'])), 'setting');
          $title = l($data['link']['title'], "node/{$node->book['bid']}", array('attributes' => array('class' => 'depth-0')));
          return array(
            'subject' => "<span class='trail'>{$title}</span>",
            'content' => menu_tree_output(array($data)),
          );
        }
      }
      // Boring old block
      else {
        $data = array_shift(menu_tree_page_data($node->book['menu_name']));
        if ($data['below']) {
          $title = l($data['link']['title'], "node/{$node->book['bid']}", array('attributes' => array('class' => 'depth-0')));
          return array(
            'subject' => "<span class='trail'>{$title}</span>",
            'content' => menu_tree_output($data['below']),
          );
        }
      }
    }
  }
}

/**
 * Feature-aware book block. Show all books that belong to the current feature.
 */
function _atrium_block_book_all() {
  if ($space = spaces_get_space()) {
    // Retrieve node type arguments from active context if necessary.
    $type = NULL;
    foreach (context_get('context') as $context) {
      if (!empty($context->conditions['bookroot']['values'])) {
        $type = current($context->conditions['bookroot']['values']);
        break;
      }
    }

    // Dynamic block.
    if (module_exists('admin')) {
      drupal_add_css(drupal_get_path('module', 'admin') .'/includes/admin.menu.css');
      drupal_add_js(drupal_get_path('module', 'admin') .'/includes/jquery.drilldown.js');
      drupal_add_js(drupal_get_path('module', 'atrium') .'/atrium.js');
      drupal_add_js(array('atriumBookPath' => url($_GET['q'])), 'setting');

      // Build a distinct cache ID per space & node type.
      $cid = $type ? "atrium_book:{$space->type}:{$space->id}:$type" : "atrium_book:{$space->type}:{$space->id}";
      if ($cache = cache_get($cid)) {
        $block = array(
          'subject' => "<span class='trail'>". t('Notebook') ."</span>",
          'content' => $cache->data,
        );
      }
      else if ($view = views_get_view('atrium_book_current')) {
        // Since the tree is *complete* and will be cached, we clear out
        // $_GET['q'] for the duration of the build to prevent stray active
        // classes from being added to links in the tree.
        $q = $_GET['q'];
        $_GET['q'] = '';

        // Generate book tree per book node in current space.
        $data = array();
        $view->execute_display('default', array($type));
        if (is_array($view->result) && count($view->result)) {
          foreach($view->result as $row) {
            $data = array_merge($data, menu_tree_all_data(book_menu_name($row->nid)));
          }
          $data = array(array('link' => array('title' => 'Notebook', 'href' => 'notebook'), 'below' => $data));
          if ($output = menu_tree_output($data)) {
            cache_set($cid, $output);
            $block = array(
              'subject' => "<span class='trail'>". t('Notebook') ."</span>",
              'content' => $output,
            );
          }
        }

        // Put path back.
        $_GET['q'] = $q;
      }
    }
    // Boring old block.
    else if ($view = views_get_view('atrium_book_current')) {
      $data = array();
      $view->execute_display('default', array($type));
      if (is_array($view->result) && count($view->result)) {
        foreach($view->result as $row) {
          $data = array_merge($data, menu_tree_page_data(book_menu_name($row->nid)));
        }
      }
      if ($output = menu_tree_output($data)) {
        $title = l(t('Notebook'), 'notebook', array('attributes' => array('class' => 'depth-0')));
        $block = array(
          'subject' => "<span class='trail'>{$title}</span>",
          'content' => $output,
        );
      }
    }
  }
  return isset($block) ? $block : NULL;
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

/**
 * Help.
 */
function _atrium_block_help() {
  if ($helptext = theme('help')) {
    return array('subject' => t('Need help?'), 'content' => $helptext);
  }
}
