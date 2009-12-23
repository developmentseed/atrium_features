<?php
class atrium_handler_filter_og_group_nid extends views_handler_filter_equality {
  // exposed filter options
  var $no_single = TRUE;

  /**
   * Provide a simple textfield for equality
   */
  function value_form(&$form, &$form_state) {
    if (!empty($form_state['exposed']) && empty($this->value)) {
      $this->value = t('All');
    }

    global $user;
    $options = array();
    if (!empty($user->og_groups)) {
      foreach ($user->og_groups as $gid => $group) {
        $options[$gid] = $group['title'];
      }
    }

    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Value'),
      '#options' => $options,
      '#default_value' => $this->value,
    );

    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];
      if (!isset($form_state['input'][$identifier])) {
        $form_state['input'][$identifier] = $this->value;
      }
    }
  }
}
