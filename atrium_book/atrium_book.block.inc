<?php

/**
 * Feature-aware book block. Show only the current book.
 */
function _atrium_book_block_book() {
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
          drupal_add_js(drupal_get_path('module', 'atrium_book') .'/atrium_book.js');
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
function _atrium_book_block_book_all() {
  if (module_exists('spaces')) {
    $space = spaces_get_space();
  }
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
    drupal_add_js(drupal_get_path('module', 'atrium_book') .'/atrium_book.js');
    drupal_add_js(array('atriumBookPath' => url($_GET['q'])), 'setting');

    // Build a distinct cache ID per space & node type.
    if ($space) {
      $cid = $type ? "atrium_book:{$space->type}:{$space->id}:$type" : "atrium_book:{$space->type}:{$space->id}";
    }
    else {
      $cid = $type ? "atrium_book:$type" : "atrium_book";
    }
    if ($cache = cache_get($cid)) {
      $block = array(
        'subject' => "<span class='trail'>". t('Notebook') ."</span>",
        'content' => $cache->data,
      );
    }
    else if ($view = views_get_view('book_current')) {
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
  else if ($view = views_get_view('book_current')) {
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
  return isset($block) ? $block : NULL;
}