<?php

/**
 * Migration function for Atrium installs that have used profile module
 * in the past. Loaded in .install.
 */
function _atrium_profile_profile_migration() {
  $result = db_query("SELECT DISTINCT(p.uid) FROM {profile_values} p JOIN {users} u ON p.uid = u.uid");
  while ($row = db_fetch_object($result)) {
    $uid = $row->uid;
    $account = user_load(array('uid' => $uid));

    if ($account) {
      // Gather existing profile field content
      $pfields = array();
      profile_load_profile($account);
      foreach ($account as $k => $v) {
        if (strpos($k, 'profile_') === 0) {
          $pfields[$k] = $v;
        }
      }

      // Gather available cck profile fields
      $info = _content_type_info();
      $cckfields = $info['content types']['profile']['fields'];

      // Try to get an existing profile node. If none, create a new node.
      $node = node_load(array('type' => 'profile', 'uid' => $uid));
      if (!$node) {
        $node = new StdClass();
        $node->status = 1;
        $node->type = 'profile';
        $node->uid = $uid;
      }

      // Set profile title
      if (!empty($pfields['profile_givenname']) || !empty($pfields['profile_familyname'])) {
        $node->title = trim($pfields['profile_givenname']) ." ". trim($pfields['profile_familyname']);
      }
      else {
        $node->title = $account->name;
      }

      // Set profile address
      if (!empty($pfields['profile_street']) && !empty($cckfields['field_profile_address'])) {
        $address = array();
        $address[] = $pfields['profile_street'];
        $line2 = array($pfields['profile_city'], $pfields['profile_province'], $pfields['profile_postal']);
        foreach ($line2 as $k => $v) {
          if (empty($v)) {
            unset($line2[$k]);
          }
        }
        if (!empty($line2)) {
          $address[] = implode(', ', $line2);
        }
        if (!empty($pfields['profile_country'])) {
          $address[] = $pfields['profile_country'];
        }
        $node->field_profile_address = array(
          array('value' => implode("\n", $address)),
        );
      }

      // Straight mapping for the rest
      foreach ($pfields as $k => $v) {
        if (!empty($cckfields["field_{$k}"])) {
          $fieldname = "field_{$k}";
          $node->{$fieldname} = array(
            array('value' => $v),
          );
        }
      }

      node_save($node);
      drupal_set_message(t("Migrated profile for user <strong>!username</strong>", array('!username' => $account->name)));
    }
  }
  module_disable(array('profile'));
  drupal_uninstall_module('profile');
}
