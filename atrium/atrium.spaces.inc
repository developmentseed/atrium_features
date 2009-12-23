<?php

/**
 * Implementation of space_setting.
 */
class atrium_setting_sitemode implements space_setting {
  var $id;
  var $types;

  function __construct($id = NULL) {
    $this->id = 'atrium_sitemode';
    $this->types = array('site');
  }

  function form($space, $value = array()) {
    $options = array(
      ATRIUM_SITEMODE_PRIVATE => t('Private access only'),
      ATRIUM_SITEMODE_PUBLIC => t('Public access, open registration'),
      ATRIUM_SITEMODE_CONTROLLED => t('Public access, moderated registration'),
    );
    $form = array(
      '#title' => t('Site mode'),
      '#type' => 'select',
      '#description' => t('Choose the access level for the site.'),
      '#options' => $options,
      '#default_value' => !empty($value) ? $value : ATRIUM_SITEMODE_PRIVATE,
    );
    return $form;
  }

  function validate($space, $value) { }

  function submit($space, $value) {
    variable_set('user_register', $value);
    features_rebuild();
    return $value;
  }
}

/**
 * Implementation of space_setting.
 */
class atrium_setting_members implements space_setting {
  var $id;
  var $types;

  function __construct($id = NULL) {
    $this->id = 'atrium_members';
    $this->types = array('site');
  }

  function form($space, $value = array()) {
    $form = array(
      '#title' => t('Members'),
      '#type' => 'select',
      '#description' => t('Choose the access mode for the member directory and profiles. Administrators and managers will be able to see all members regardless of this setting.'),
      '#options' => array(
        ATRIUM_MEMBERS_ALL => t('Users can view all members'),
        ATRIUM_MEMBERS_GROUP => t('Users can only view members that belong to their groups')
      ),
      '#default_value' => !empty($value) ? $value : 0,
    );
    return $form;
  }

  function validate($space, $value) { }

  function submit($space, $value) {
    variable_set('atrium_members', $value);
    features_rebuild();
    return $value;
  }
}
