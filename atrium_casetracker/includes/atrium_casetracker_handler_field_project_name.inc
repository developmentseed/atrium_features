<?php

class atrium_casetracker_handler_field_project_name extends views_handler_field {
  /**
   * Pre_render() -- collect casetracker project names
   */
  function pre_render($values) {
    $nids = array();
    foreach ($values as $row) {
      if (!empty($row->casetracker_case_pid)) {
        $nids[] = $row->casetracker_case_pid;
      }
    }
    if (!empty($nids)) {
      $result = db_query(db_rewrite_sql("SELECT n.nid, n.title FROM {node} n WHERE n.nid IN(%s)"), implode(',', $nids));
      while ($row = db_fetch_object($result)) {
        $row->acro = $this->acronymize($row->title);
        $this->projects[$row->nid] = $row;
      }
    }
  }

  /**
   * Render() -- use crayon theming
   */
  function render($values) {
    if (!empty($this->projects[$values->casetracker_case_pid])) {
      $project = $this->projects[$values->casetracker_case_pid];
      return theme('seed_crayon_swatch', $project->nid, $project->acro, $project->title, "node/{$project->nid}");
    }
  }

  /**
   * Acronymizer function. Attempts to generate a reasonable acronym from a given string.
   */
  function acronymize($string, $reset = FALSE) {
    static $cache = array();

    if (!isset($cache[$string]) || $reset) {
      $split = preg_split('/[ .-]+/', $string, -1, PREG_SPLIT_NO_EMPTY);
      $acro = '';

      // Capital-letter based acronyms
      if (preg_match('/[0-9A-Z]+/', $string)) {

        // Eliminate small words
        foreach ($split as $k => $chunk) {
          // No caps or numbers, trash it
          if (!preg_match('/[0-9A-Z]+/', $chunk)) {
            unset($split[$k]);
          }
        }
        reset($split);

        // Multiword titles -- form acronym from key characters.
        if (count($split) > 1) {
          foreach ($split as $chunk) {
            $char = array();
            preg_match_all('/[0-9A-Z]/', $chunk, $char);
            $acro .= implode('', $char[0]);
          }
        }
        // 1 word titles
        else {
          $split = array_shift($split);
          $char = array();
          preg_match_all('/[0-9A-Z]/', $split, $char);
          // Use caps as the acronym, but if there's only 1 cap use the whole string.
          $acro = count($char[0]) > 1 ? implode('', $char[0]) : $split;
        }
      }
      // Lower case title, bail and use first word
      else {
        // Multi-word -- use first letter of each
        if (count($split) > 1) {
          foreach ($split as $chunk) {
            $acro .= drupal_substr($chunk, 0, 1);
          }
        }
        // Bail, use first word
        else {
          $acro = current($split);
        }
      }
      $cache[$string] = $acro;
    }

    return $cache[$string];
  }
}
