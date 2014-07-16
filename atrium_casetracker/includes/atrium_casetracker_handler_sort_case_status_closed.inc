<?php
// $Id$

/**
 * Defines a sort handler for the Atrium Casetracker inactive case status.
 */
class atrium_casetracker_handler_sort_status_closed extends views_handler_sort {
  /**
   * Override of views_handler_sort::query().
   */
  function query() {
    $pattern = '(' . db_escape_string(implode('|', atrium_casetracker_get_inactive_states())) . ')';
    global $db_type;
    switch ($db_type) {
      case 'mysql':
      case 'mysqli':
        $formula = "{$this->table}.{$this->real_field} REGEXP '$pattern'";
        break;
    }
    if (!empty($formula)) {
      $this->ensure_my_table();
      $this->query->add_orderby(NULL, $formula, $this->options['order'], $this->query->base_field . '_' . $this->field);
    }
  }
}
