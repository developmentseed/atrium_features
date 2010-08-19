<?php

class atrium_activity_handler_field_activity_user extends atrium_activity_handler_field_activity {

  /**
   * Add uid in the query so we can test for anonymous if needed.
   */
  function init(&$view, &$data) {
    parent::init($view, $data);
    if (!empty($this->options['overwrite_anonymous']) || !empty($this->options['link_to_user'])) {
      $this->additional_fields['uid'] = 'uid';
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['overwrite_anonymous'] = array('default' => FALSE);
    $options['anonymous_text'] = array('default' => '', 'translatable' => TRUE);
    $options['link_to_user'] = array('default' => TRUE);
    return $options;
  }

  /**
   * Add the time_horizon element.
   */
  function options_form(&$form, $form_state) {
    parent::options_form($form, $form_state);
    unset($form['time_horizon']);
    
    $form['overwrite_anonymous'] = array(
      '#title' => t('Overwrite the value to display for anonymous users'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['overwrite_anonymous']),
      '#description' => t('If selected, you will see a field to enter the text to use for anonymous users.'),
    );
    $form['anonymous_text'] = array(
      '#title' => t('Text to display for anonymous users'),
      '#type' => 'textfield',
      '#default_value' => $this->options['anonymous_text'],
      '#process' => array('views_process_dependency'),
      '#dependency' => array(
        'edit-options-overwrite-anonymous' => array(1),
      ),
    );
    $form['link_to_user'] = array(
      '#title' => t('Link this field to its user'),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['link_to_user'],
    );
  } 

  /**
   * Render this field as a link to activity user
   */
  function render($value) {
    // Has comments
    if (!empty($value->{$this->field_alias})) {
      $account = user_load($value->{$this->aliases['comment_uid']});
      if (!empty($this->options['link_to_user'])) {
        return theme('username', $account);
      }
      else {
        return check_plain($account->name);
      }
    }
    // No comments
    $account = user_load($value->{$this->aliases['node_uid']});
    if (!empty($this->options['link_to_user'])) {
      return theme('username', $account);
    }
    else {
      return check_plain($account->name);
    }
  }
}