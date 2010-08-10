<?php

class atrium_activity_handler_field_activity extends views_handler_field {
  /**
   * Add the time_horizon option.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['time_horizon'] = array('default' => 30);
    return $options;
  }

  /**
   * Add the time_horizon element.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['time_horizon'] = array(
      '#type' => 'select',
      '#title' => t('Time horizon'),
      '#description' => t('Show activity that goes back to the selected period. Choosing a shorter period will result in a more optimized view.'),
      '#options' => array(
        7 => t('@num days', array('@num' => 7)),
        14 => t('@num days', array('@num' => 14)),
        30 => t('@num days', array('@num' => 30)),
        90 => t('@num days', array('@num' => 90)),
      ),
      '#default_value' => $this->options['time_horizon'],
    );
  }

  /**
   * Constructor. Add additional fields.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
    $this->additional_fields['node_title'] = array('table' => 'node', 'field' => 'title');
    $this->additional_fields['node_uid'] = array('table' => 'node_revisions', 'field' => 'uid');
    $this->additional_fields['comment_uid'] = array('table' => 'comments', 'field' => 'uid');
    $this->additional_fields['node_changed'] = array('table' => 'node', 'field' => 'changed');
    $this->additional_fields['node_created'] = array('table' => 'node', 'field' => 'created');
  }

  /**
   * Query. This relies on the hijacking of the Views execution process in
   * atrium_views_query_alter().
   */
  function query() {
    parent::query();
    if (!isset($this->view->atrium_activity)) {
      $this->view->atrium_activity = TRUE;
      $node = $this->query->ensure_table('node');
      $comments = $this->query->ensure_table('comments');
      $horizon = $this->options['time_horizon'] * 24 * 60 * 60;
      $this->query->add_orderby(NULL, "***ATRIUM_ACTIVITY_TIMESTAMP***", 'DESC', 'atrium_activity_sort');
      $this->query->add_where(NULL, "***ATRIUM_ACTIVITY_TIMESTAMP*** > (***CURRENT_TIME*** - $horizon)");
    }
  }

  /**
   * Don't allow advanced render of this field.
   */
  function allow_advanced_render() { return FALSE; }

  /**
   * Render this field as a link to group space.
   */
  function render($value) {
    // Has comments
    if (!empty($value->{$this->field_alias})) {
      $account = $this->user_load($value->{$this->aliases['comment_uid']});
      $tokens = array(
        '!user' => theme('username', $account),
        '!title' => l($value->{$this->aliases['node_title']}, "node/{$value->{$this->aliases['nid']}}", array('fragment' => "comment-{$value->{$this->field_alias}}")),
      );
      return t('!user commented on !title', $tokens);
    }
    // No comments
    $account = $this->user_load($value->{$this->aliases['node_uid']});
    $tokens = array(
      '!user' => theme('username', $account),
      '!title' => l($value->{$this->aliases['node_title']}, "node/{$value->{$this->aliases['nid']}}"),
    );
    if ($value->{$this->aliases['node_changed']} > $value->{$this->aliases['node_created']}) {
      return t('!user updated !title', $tokens);
    }
    return t('!user posted !title', $tokens);
  }

  /**
   * Static cached user load.
   */
  protected function user_load($uid, $reset = FALSE) {
    static $cache = array();
    if (!isset($cache[$uid]) || $reset) {
      $cache[$uid] = user_load($uid);
    }
    return $cache[$uid];
  }
}
