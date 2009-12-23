<?php
class atrium_handler_field_og_group_nids extends views_handler_field {
  function init(&$view, $options) {
    parent::init($view, $options);
    $this->additional_fields['group_nid'] = array('table' => 'og_ancestry', 'field' => 'group_nid');
  }

  /**
   * Add this term to the query
   */
  function query() {
    $this->add_additional_fields();
  }

  /**
   * Collect group title, purl here.
   */
  function pre_render($values) {
    $nids = array();
    foreach ($values as $result) {
      if (!empty($result->{$this->aliases['group_nid']})) {
        $nids[] = $result->{$this->aliases['group_nid']};
      }
    }
    if ($nids) {

      // Grab spaces design color info
      $join = '';
      $fields = '';
      if (module_exists('spaces_design')) {
        $join = "LEFT JOIN {spaces_settings} s ON s.sid = n.nid AND s.type = 'og' AND s.id = 'color'";
        $fields = ", s.value AS color";
      }

      $result = db_query("
        SELECT p.value AS modifier, n.nid AS nid, n.title AS title $fields
          FROM {purl} p
          JOIN {node} n ON p.id = n.nid
          $join
          WHERE p.id IN (" . implode(', ', $nids) . ")
          AND p.provider = '%s'",
        'spaces_og');
      while ($row = db_fetch_object($result)) {
        if (!empty($row->color)) {
          $row->color = unserialize($row->color);
        }
        $this->groups[$row->nid] = $row;
      }
    }
  }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($value) {
    $output = '';
    if (!empty($this->groups[$value->{$this->aliases['group_nid']}])) {
      $group = $this->groups[$value->{$this->aliases['group_nid']}];
      $output .= theme('seed_crayon_swatch', $group->nid, $group->modifier, $group->title, "node/{$group->nid}", $group->color);
    }
    return $output;
  }
}