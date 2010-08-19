<?php

class atrium_activity_handler_field_activity_path extends atrium_activity_handler_field_activity {

  function option_definition() {
    $options = parent::option_definition();
    $options['absolute'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Add the time_horizon element.
   */
  function options_form(&$form, $form_state) {
    parent::options_form($form, $form_state);
    unset($form['time_horizon']);
    $form['absolute'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use absolute link (begins with "http://")'),
      '#default_value' => $this->options['absolute'],
      '#description' => t('If you want to use this as in "output this field as link" in "link path", you must enable this option.'),
    );
  } 

  /**
   * Render this field as a link to group space.
   */
  function render($value) {
    // Has comments
    if (!empty($value->{$this->field_alias})) {
      return url("node/{$value->{$this->aliases['nid']}}", array(
        'absolute' => $this->options['absolute'],
        'fragment' => "comment-{$value->{$this->field_alias}}"
      ));
    } 
    // No comments
    return url("node/{$value->{$this->aliases['nid']}}", array(
      'absolute' => $this->options['absolute'],
    ));
  }
}