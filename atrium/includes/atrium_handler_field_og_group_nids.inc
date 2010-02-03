<?php
class atrium_handler_field_og_group_nids extends views_handler_field {
  function init(&$view, $options) {
    parent::init($view, $options);
    $this->additional_fields['group_nid'] = array('table' => 'og_ancestry', 'field' => 'group_nid');

    // Omit this field if we're within a group space.
    $space = spaces_get_space();
    if ($space && $space->type === 'og') {
      $this->options['exclude'] = TRUE;
    }
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
      if (module_exists('designkit')) {
        $join = "LEFT JOIN {spaces_overrides} s ON s.id = n.nid AND s.type = 'og' AND s.object_type = 'variable' AND s.object_id = 'designkit_color'";
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
          $color = unserialize($row->color);
          if (!empty($color) && is_array($color)) {
            $row->color = array_shift($color);
          }
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
      $options = array('purl' => array('provider' => 'spaces_og', 'id' => $group->nid));
      $output .= theme('seed_crayon_swatch', $group->nid, $group->modifier, $group->title, '<front>', $options, $group->color);
    }
    return $output;
  }
}