<?php

class atrium_activity_handler_field_activity_timestamp extends atrium_activity_handler_field_activity {
  function __construct() {
    views_get_handler('node', 'created', 'field');
  }

  /**
   * Override of option_definition().
   */
  function option_definition() {
    if (class_exists('reldate_handler_field_date')) {
      return reldate_handler_field_date::option_definition();
    }
    elseif (class_exists('views_handler_field_date')) {
      return views_handler_field_date::option_definition();
    }
  }

  /**
   * Override of options_form().
   */
  function options_form(&$form, &$form_state) {
    if (class_exists('reldate_handler_field_date')) {
      reldate_handler_field_date::options_form($form, $form_state);
    }
    elseif (class_exists('views_handler_field_date')) {
      views_handler_field_date::options_form($form, $form_state);
    }
  }

  /**
   * Do nothing.
   */
  function query() {
  }

  /**
   * Render this field as a link to group space.
   */
  function render($values) {
    $this->field_alias = 'atrium_activity_sort';
    if (class_exists('reldate_handler_field_date')) {
      return reldate_handler_field_date::render($values);
    }
    elseif (class_exists('views_handler_field_date')) {
      return views_handler_field_date::render($values);
    }
  }
}
