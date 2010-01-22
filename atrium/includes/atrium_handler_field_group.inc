<?php

class atrium_handler_field_group extends views_handler_field {
  /**
   * Don't allow advanced render of this field.
   */
  function allow_advanced_render() { return FALSE; }

  /**
   * Render this field as a link to group space.
   */
  function render($value) {
    return l($value->node_title, '<front>', array('purl' => array('provider' => 'spaces_og', 'id' => $value->nid)));
  }
}
