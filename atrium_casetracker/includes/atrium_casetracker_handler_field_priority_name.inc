<?php
/**
 * Field handler to show Selective state.
 *
 * @ingroup views_field_handlers
 */
class atrium_casetracker_handler_field_priority_name extends views_handler_field {
  function render($values) {
    return theme('atrium_casetracker_priority', $values->casetracker_case_case_priority_id);
  }
}
