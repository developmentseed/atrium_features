<?php

/**
 * Implementation of hook_strongarm().
 */
function atrium_members_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'spaces_preset_user';
  $strongarm->value = 'atrium_members_simple';

  $export['spaces_preset_user'] = $strongarm;
  return $export;
}
