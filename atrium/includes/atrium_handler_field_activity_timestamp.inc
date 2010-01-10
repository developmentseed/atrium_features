<?php

class atrium_handler_field_activity_timestamp extends atrium_handler_field_activity {
  /**
   * Activity date formatting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['time_horizon']);

    $time = time();
    $form['date_format'] = array(
      '#type' => 'select',
      '#title' => t('Date format'),
      '#options' => array(
        'small' => format_date($time, 'small'),
        'medium' => format_date($time, 'medium'),
        'large' => format_date($time, 'large'),
        'custom' => t('Custom'),
        'time ago' => t('Time ago'),
        'day' => t('Day only'),
        'time' => t('Time only'),
        'reldate' => t('Relative date'),
      ),
      '#default_value' => isset($this->options['date_format']) ? $this->options['date_format'] : 'small',
    );
    $form['custom_date_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom date format'),
      '#description' => t('If "Custom", see <a href="http://us.php.net/manual/en/function.date.php" target="_blank">the PHP docs</a> for date formats. If "Time ago" this is the the number of different units to display, which defaults to two.'),
      '#default_value' => isset($this->options['custom_date_format']) ? $this->options['custom_date_format'] : '',
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-options-date-format' => array('custom', 'time ago')),
    );
  }

  /**
   * Do nothing.
   */
  function query() {
  }

  /**
   * Render this field as a link to group space.
   */
  function render($values) {
    $value = $values->atrium_activity_sort;
    $format = $this->options['date_format'];
    if ($format == 'custom' || $format == 'time ago') {
      $custom_format = $this->options['custom_date_format'];
    }

    // @TODO: Use date_format_date if date API is available.
    switch ($format) {
      case 'reldate':
        return $value ? seed_rel_date($value) : theme('views_nodate');
      case 'day':
        $format = variable_get('date_format_day', 'l, M j');
        return $value ? format_date($value, 'custom', $format) : theme('views_nodate');
      case 'time':
        $format = variable_get('date_format_time', 'g:ia');
        return $value ? format_date($value, 'custom', $format) : theme('views_nodate');
      case 'time ago':
        return $value ? t('%time ago', array('%time' => format_interval(time() - $value, is_numeric($custom_format) ? $custom_format : 2))) : theme('views_nodate');
      case 'custom':
        return $value ? format_date($value, $format, $custom_format) : theme('views_nodate');
      default:
        return $value ? format_date($value, $format) : theme('views_nodate');
    }
  }
}
