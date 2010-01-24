<?php
// $Id$

/**
 * Provides custom access controls beyond the default spaces_feature access plugin.
 */
class atrium_plugin_access_atrium_feature extends spaces_plugin_access_spaces_feature {
  function access($account) {
    $feature = $this->options['spaces_feature'] == 0 ? $this->get_my_feature() : $this->options['spaces_feature'];
    return atrium_feature_access($feature, $this->options['perm']);
  }

  function get_access_callback() {
    $feature = $this->options['spaces_feature'] == 0 ? $this->get_my_feature() : $this->options['spaces_feature'];
    return array('atrium_feature_access', array($feature, $this->options['perm']));
  }

  function option_defaults(&$options) {
    parent::option_defaults($options);
    $options['perm'] = 'access content';
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $perms = array();
    // Get list of permissions
    foreach (module_list(FALSE, FALSE, TRUE) as $module) {
      if ($permissions = module_invoke($module, 'perm')) {
        $perms[$module] = drupal_map_assoc($permissions);
      }
    }
    $form['perm'] = array(
      '#type' => 'select',
      '#options' => $perms,
      '#title' => t('Permission'),
      '#default_value' => $this->options['perm'],
      '#description' => t('Only users with the selected permission flag will be able to access this display. Note that users with "access all views" can see any view, regardless of other permissions.'),
    );
  }
}
