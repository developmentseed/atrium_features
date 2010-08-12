<?php
// $Id$

/**
 * Filter by node types included in 'book types'.
 */
class atrium_book_handler_filter_book_types extends views_handler_filter {
  function query() {
    $types = array();
    foreach (variable_get('book_allowed_types', array('book')) as $type) {
      $types[$type] = $type;
    }

    $this->ensure_my_table();
    $placeholder = "'%s'";
    $replace = array_fill(0, sizeof($types), $placeholder);
    $in = ' (' . implode(", ", $replace) . ')';

    // We use array_values() because the checkboxes keep keys and that can cause
    // array addition problems.
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field IN {$in}", array_values($types));
  }
}