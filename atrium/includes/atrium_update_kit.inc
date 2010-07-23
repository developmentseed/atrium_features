<?php

/**
 * Update feature components for Kit compliance
 *
 * @param array $type
 *   The type of component.  Accepted types are 'views' and 'context'
 * @param array $info
 *
 *
 * Component array should look something like:
 *
 *
 * $components = array(
 *   'views' => array(
 *     'atrium_blog' => array(
 *       'atrium_blog_listing' => array(
 *         'block_1',
 *         'block_2',
 *       ),
 *     ),
 *   ),
 *   'contexts' => array(
 *     'spaces-feature-blog' => 'blog_listing',
 *   ),
 * );
 *
 */
function atrium_kit_comply_presets($info, $type = 'views') {
  $type == 'views' ? $views = $info['views'] : $views = $info['blocks'];
  foreach ($views as $old_view_name => $new_view) {
    $view = views_get_view($old_view_name);
    // Proceed if view is not overridden.
    if ($view->type != 'Overriden' || $type == 'blocks') {
      // Go block by block and update spaces_dashboards, spaces_presets, and context.
      foreach ($new_view as $new_view_name => $blocks) {
        foreach ($blocks as $block) {
          $query = db_query("SELECT * FROM {spaces_presets}");
          while ($result = db_fetch_object($query)) {
            $value = unserialize($result->value);
            foreach ($value as $key => $settings) {
              if ($key == 'context') {
                foreach ($settings as $name => $def) {
                  // Call api function to replace keys and values.
                  $value[$key][$name] = _atrium_kit_comply_rename($def, $type, $old_view_name, $new_view_name, $block);
                }
              }
            }
            $value = serialize($value);
            if ($value != $result->value) {
              db_query("UPDATE {spaces_presets} SET value = '%s' WHERE name = '%s'", $value, $result->name);
            }
          }
        }
      }
    }
  }
}

function atrium_kit_comply_overrides($info, $type = 'views') {
  $type == 'views' ? $views = $info['views'] : $views = $info['blocks'];
  foreach ($views as $old_view_name => $new_view) {
    $view = views_get_view($old_view_name);
    // Proceed if view is not overridden.
    if ($view->type != 'Overriden' || $type == 'blocks') {
      // Go block by block and update spaces_dashboards, spaces_presets, and context.
      foreach ($new_view as $new_view_name => $blocks) {
        foreach ($blocks as $block) {
          // Replace block names in spaces_dashboard
          $query = db_query("SELECT * FROM {spaces_overrides} WHERE object_type = 'context' AND object_id LIKE 'spaces_dashboard%%'");
          while ($result = db_fetch_object($query)) {
            $value = unserialize($result->value);
            $value = _atrium_kit_comply_rename($value, $type, $old_view_name, $new_view_name, $block);
            $value = serialize($value);
            if ($value != $result->value) {
              db_query("UPDATE {spaces_overrides} SET value = '%s' WHERE type = '%s' AND id = %d AND object_id = '%s'", $value, $result->type, $result->id, $result->object_id);
            }
          }
        }
      }
    }
  }
}

function atrium_kit_comply_contexts($info, $type = 'views') {
  // Update components in contexts.
  $type == 'views' ? $views = $info['views'] : $views = $info['blocks'];
  foreach ($views as $old_view_name => $new_view) {
    $view = views_get_view($old_view_name);
    // Proceed if view is not overridden.
    if ($view->type != 'Overriden' || $type == 'blocks') {
      // Go block by block and update contexts.
      foreach ($new_view as $new_view_name => $blocks) {
        foreach ($blocks as $block) {
          $query = db_query("SELECT * FROM {context}");
          while ($result = db_fetch_object($query)) {
            // Update views names in conditions.
            $conditions = unserialize($result->conditions);
            foreach ($conditions as $condition => $values) {
              if ($condition == 'views') {
                foreach ($values['values'] as $vname => $value) {
                  if ($vname == $old_view_name) {
                    $conditions[$condition]['values'][$new_view_name] = $new_view_name;
                    unset($conditions[$condition]['values'][$old_view_name]);
                  }
                }
              }
            }
            $conditions = serialize($conditions);
            // Update views/blocks names in reactions
            $reactions = unserialize($result->reactions);
            if (!empty($reactions['block']['blocks'])) {
              $reactions['block'] = _atrium_kit_comply_rename($reactions['block'], $type, $old_view_name, $new_view_name, $block);
            }
            $reactions = serialize($reactions);
            if ($reactions != $result->reactions || $conditions != $result->conditions) {
              db_query("UPDATE {context} SET conditions = '%s', reactions = '%s' WHERE name = '%s'", $conditions, $reactions, $result->name);
            }
          }
        }
      }
    }
  }
  // Update names for overridden contexts.
  foreach ($info['contexts'] as $old => $new) {
    db_query("UPDATE {context} SET name = '%s' WHERE name = '%s'", $new, $old);
  }
}

function atrium_kit_comply_spaces_presets($info, $type = 'views') {
  // Replace 'name' value in the spaces_presets table.
  // Replace 'value' value in the spaces_overrides table where object_type = 'variable'
  $presets = $info['spaces_presets'];
  foreach ($presets as $old_preset => $new_preset) {
    db_query("UPDATE {spaces_presets} SET name = '%s' WHERE name = '%s'", $new_preset, $old_preset);
    $query = db_query("SELECT * FROM {spaces_overrides} WHERE object_type = 'variable' AND value LIKE '%\%s%'", $old_preset);
    while ($result = db_fetch_object($query)) {
      db_query("UPDATE {spaces_overrides} SET value = '%s' WHERE type = '%s' AND id = %d AND object_id = '%s'", $new_preset, $result->type, $result->id, $result->object_id);
    }
    // Replace 'value' in spaces_presets in the 'variable' key
    $query = db_query("SELECT * FROM {spaces_presets}");
    while ($result = db_fetch_object($query)) {
      $value = unserialize($result->value);
      foreach ($value as $key => $settings) {
        if ($key == 'variable') {
          foreach ($settings as $name => $def) {
            if ($def == $old_preset) {
              $value[$key][$name] = $new_preset;
            }
          }
        }
      }
      $value = serialize($value);
      if ($value != $result->value) {
        db_query("UPDATE {spaces_presets} SET value = '%s' WHERE name = '%s'", $value, $result->name);
      }
    }
  }
}

/*
 * $source should always be an array to operate on, not serialized data.
 */
function _atrium_kit_comply_rename($source, $type, $old_view_name, $new_view_name, $block) {
  $block_name = $block['delta'];
  $module = $block['module'];
  $current_blocks = $source['blocks'];
  if ($type == 'views') {
    // Replace key name
    if (array_key_exists("views-$old_view_name-$block_name", $current_blocks)) {
      $current_blocks["views-$new_view_name-$block_name"] = $current_blocks["views-$old_view_name-$block_name"];
      unset($current_blocks["views-$old_view_name-$block_name"]);
    }
    // Rename values
    foreach ($current_blocks as $key => $current_block) {
      $current_block = str_replace("$old_view_name-$block_name", "$new_view_name-$block_name", $current_block);
      $current_blocks[$key] = $current_block;
    }
  }
  else {
    // Blocks provided by modules do not use "views" prefix.
    // Replace key name
    if (array_key_exists("$old_view_name-$block_name", $current_blocks)) {
      $current_blocks["$new_view_name-$block_name"] = $current_blocks["$old_view_name-$block_name"];
      $current_blocks["$new_view_name-$block_name"]['module'] = $module;
      unset($current_blocks["$old_view_name-$block_name"]);
    }
    // Rename values
    foreach ($current_blocks as $key => $current_block) {
      $current_block = str_replace("$old_view_name-$block_name", "$new_view_name-$block_name", $current_block);
      $current_blocks[$key] = $current_block;
    }
  }
  $source['blocks'] = $current_blocks;
  return $source;
}
