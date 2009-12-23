<?php

class atrium_book_space_setting implements space_setting {
  var $id;

  function __construct($id = NULL) {
    $this->id = 'atrium_book';
  }

  function form($space, $value = array()) {
    $form = array('#tree' => TRUE);
    $options = array(0 => t('Recent updates'), t('Pages') => array());

    if ($view = views_get_view('atrium_book_current')) {
      $view->set_display();
      $view->set_items_per_page(0);
      $view->execute();

      // Collect books in this space into an array
      if (is_array($view->result) && count($view->result)) {
        foreach($view->result as $row) {
          $options[t('Pages')][$row->nid] = $row->node_title;
        }
      }
    }

    $form = array(
      '#title' => t('Overview page'),
      '#type' => 'select',
      '#description' => t('Choose the page to display when a user first views this feature.'),
      '#options' => $options,
      '#default_value' => !empty($value) ? $value : 0,
    );

    return $form;
  }

  function validate($space, $value) {
  }

  function submit($space, $value) {
    return $value;
  }
}
