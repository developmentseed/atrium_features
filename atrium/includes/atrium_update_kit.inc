<?php

/**
 * Update feature components for Kit compliance
 *
 * @param array $type
 *   The type of component.  Possible values are 'views' or 'blocks.  Use 
 *   'blocks' if renaming blocks implemented by hook_block which may be stored
 *   in an override in the database using their old name.
 * @param array $info
 *   Array of component information.  Component $info array should look
 *   similar to:
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
 * In this example array, the 'views' and 'contexts' keys indicate the type of
 * component.  In the 'views' array, the next key down the array is the name of
 * an existing view, followed by an array keyed by the new name of that existing
 * view and the blocks which that view contains.  In this example, the existing 
 * view name is "atrium_blog" which will be renamed to "atrium_blog_listing" and
 * the view implements "block_1" and "block_2" blocks.  References to this view
 * name and block names will be rewritten in overridden settings stored in the
 * database.
 * 
 * In the case of 'contexts', the key of the child array 'spaces-feature-blog'
 * is the name of an existing context, which should get renamed to the value
 * 'blog_listing'.
 *
 */


/**
 * Rewrites names of views blocks and blocks stored as overrides in the
 * spaces_presets table.
 * 
 * @param $info
 *   Array of components.  See @file for detailed explanation.
 * @param $type
 *   Type of component.  See @file for detailed explanation.
 */
function atrium_kit_comply_presets($info, $type = 'views') {
  $type == 'views' ? $views = $info['views'] : $views = $info['blocks'];
  foreach ($views as $old_view_name => $new_view) {
    $view = views_get_view($old_view_name);
    // Proceed if view is not overridden.
    if ($view->type != 'Overriden' || $type == 'blocks') {
      // For each existing view, look through each of its blocks, pull up from
      // the database all the stored spaces_presets, then look in each context
      // in the stored presets and rename the references to that block so that
      // it uses the new name of the block.  In the case of views blocks, the
      // name of the block changes because it's based on the name of the view
      // that implements that block.  In the case of blocks implemented by 
      // hook_block whose names actually do change (you're using $type = 'blocks'
      // these will also get renamed.
      foreach ($new_view as $new_view_name => $blocks) {
        foreach ($blocks as $block) {
          $query = db_query("SELECT * FROM {spaces_presets}");
          while ($result = db_fetch_object($query)) {
            $value = unserialize($result->value);
            // Possible values are 'variable' or 'context'
            foreach ($value as $key => $settings) {
              if ($key == 'context') {
                // There is a context for each custom dashboard.  The key is
                // like 'spaces_dashboard-custom-1:reaction:block' and consists
                // of a 'blocks' key which is an array of blocks keyed by
                // the name of the block, with values of module, delta, region,
                // and weight, and a 'layout' key whose value is the name (string) 
                // of the layout for that dashboard.
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

/**
 * Rewrites views blocks and blocks stored as overrides in the spaces_overrides
 * table.
 * 
 * For each old view, go through the new view array which contains block names
 * that need to be overwritten.  For each of those blocks, select all of the
 * rows stored in spaces_overrides and go through each one and run the value
 * through the renaming callback (_atrium_kit_comply_rename()) and save it back
 * to the database.
 * 
 * The spaces_overrides contains a value column which has either a 'blocks', 
 * 'layout', or both of these keys.  The blocks key contains an array of arrays 
 * of blocks values.  Each blocks values array is keyed by the block name, and 
 * contains an associative array for values for module, delta, region, and 
 * weight.  The 'layout' key contains a string name of the layout for the given 
 * dashboard.
 * 
 * @param $info
 *   Array of components.  See @file for detailed explanation.
 * @param $type
 *   Type of component.  See @file for detailed explanation.
 */
function atrium_kit_comply_overrides($info, $type = 'views') {
  $type == 'views' ? $views = $info['views'] : $views = $info['blocks'];
  foreach ($views as $old_view_name => $new_view) {
    $view = views_get_view($old_view_name);
    // Proceed if view is not overridden.
    if ($view->type != 'Overriden' || $type == 'blocks') {
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

/**
 * Rewrite component names stored in overridden contexts.
 * 
 * Views names and the names of blocks provided by views or by hook_block must
 * be rewritten in contexts stored in the database.  The stored context contains
 * a 'conditions' and a 'reactions column.  In the 'conditions' column the actual
 * view name must be rewritten for affected views.  In the 'reactions' column
 * views-provided blocks and blocks provided by hook_block must be renamed.
 * 
 * In the 'conditions' column, the column holds a serialized array which is keyed
 * on the condition type.  Views are in the 'views' key which stores an
 * associative array of values where both the key and value of the array of
 * arrays are the view name.
 * 
 * The 'reactions' column stores its value as seriaized data keyed by the reaction
 * type.  The 'block' keu contains an array whose key is 'blocks' which itself
 * contains an array of arrays where the key is the block name and the values are
 * module, delta, region, and weight.  For example:
 * 
 * 'reactions' => 
 *   'block' => array(
 *     'blocks => array(
 *       'block-name' => array(
 *         'module' => 'module-name', 
 *         'delta' => 'delta-name',
 * 
 * @param $info
 *   Array of components.  See @file for detailed explanation.
 * @param $type
 *   Type of component.  See @file for detailed explanation.
 */
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

/**
 * Renames values in stored data.
 * 
 * @param $block
 *   The delta of the existing block
 * @param $source
 *   The source to operate on and manipulate.  This should be an array that
 *   contains a 'blocks' key.  The 'blocks' key should be keyed with the name
 *   of the block, and contains values like module, delta, region, and weight.
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
