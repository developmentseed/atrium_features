<?php

/**
 * User list inclusion/exclusion handler. Makes it easy to exclude user 1, or
 * other users arbritrarily from a list.
 */
class atrium_handler_filter_user_list extends views_handler_filter_in_operator {
  var $value_form_type = 'textfield';

  function construct() {
    parent::construct();
    $this->value_title = t('Options');
  }

  function value_form(&$form, &$form_state) {
    $default_value = (array) $this->value;

    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];

      if (!empty($this->options['expose']['reduce'])) {
        $options = $this->reduce_value_options();

        if (empty($this->options['expose']['single']) && !empty($this->options['expose']['optional'])) {
          $default_value = array();
        }
      }

      if (!empty($this->options['expose']['single'])) {
        if (!empty($this->options['expose']['optional']) && (empty($default_value) || !empty($this->options['expose']['reduce']))) {
          $default_value = 'All';
        }
        else if (empty($default_value)) {
          $keys = array_keys($options);
          $default_value = array_shift($keys);
        }
        else {
          $copy = $default_value;
          $default_value = array_shift($copy);
        }
      }
    }

    // Turn array of values into comma-separated string
    $default_value = implode(', ', $default_value);

    $form['value'] = array(
      '#type' => $this->value_form_type,
      '#title' => $this->value_title,
      '#default_value' => $default_value,
    );

    if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier])) {
      $form_state['input'][$identifier] = $default_value;
    }

  }

  // Process comma separated list.
  function value_submit($form, &$form_state) {
    $values = explode(',', $form_state['values']['options']['value']);
    if (!empty($values)) {
      foreach ($values as $k => $v) {
        $v = trim($v);
        if (!is_numeric($v)) {
          unset($values[$k]);
        }
        else {
          $values[$k] = $v;
        }
      }
    }
    else {
      $values = array();
    }
    $form_state['values']['options']['value'] = $values;
  }

  // Admin display summary
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    if (!is_array($this->value)) {
      return;
    }

    if (count($this->value) == 1) {
      // If there is only one, show it as an =.
      $value = current($this->value);
      return (substr($this->operator, 0, 3) != 'not' ? '=' : '<>') . ' ' . $value;
    }
    $output = '';
    foreach ($this->value as $value) {
      if ($output !== '') {
        $output .= ', ';
      }
      if (strlen($output) > 8) {
        $output .= '...';
        break;
      }
      $output .= $value;
    }

    return check_plain($this->operator) . ' ' . $output;
  }
}
