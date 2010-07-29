<?php
// $Id$

/**
 * Filter by node types included in 'update types'.
 */
class atrium_activity_handler_filter_update_types extends views_handler_filter {
  function query() {
    $types = atrium_activity_update_types();

    $this->ensure_my_table();
    $placeholder = "'%s'";
    $replace = array_fill(0, sizeof($types), $placeholder);
    $in = ' (' . implode(", ", $replace) . ')';

    // We use array_values() because the checkboxes keep keys and that can cause
    // array addition problems.
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field IN {$in}", array_values($types));
  }
}
