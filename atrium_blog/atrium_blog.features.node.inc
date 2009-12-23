<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_blog_node_info() {
  $items = array(
    'blog' => array(
      'name' => t('Blog entry'),
      'module' => 'features',
      'description' => t('A blog is a regularly updated journal or diary made up of individual posts shown in reversed chronological order. Each member of the site may create and maintain a blog.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
