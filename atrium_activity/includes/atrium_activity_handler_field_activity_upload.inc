<?php

class atrium_activity_handler_field_activity_upload extends atrium_activity_handler_field_activity {
  /**
   * Constructor. Add additional fields.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['filemime'] = array('table' => 'files', 'field' => 'filemime');
    $this->additional_fields['filename'] = array('table' => 'files', 'field' => 'filename');
    $this->additional_fields['filepath'] = array('table' => 'files', 'field' => 'filepath');
  }

  /**
   * Query. This relies on the hijacking of the Views execution process in
   * atrium_views_query_alter().
   */
  function query() {
    $this->query->ensure_table('comments');

    $join = new views_join();
    $join->construct('upload', 'node', 'vid', 'vid', array(), 'INNER');
    $this->query->ensure_table('upload');

    $join = new views_join();
    $join->construct('files', 'upload', 'fid', 'fid', array(), 'INNER');
    $this->query->ensure_table('files', NULL, $join);

    // We run the parent query method last, as the tables need to be added
    // before the additional fields can be.
    parent::query();
  }

  /**
   * Render this field as a link to group space.
   */
  function render($value) {
    $filename = truncate_utf8($value->{$this->aliases['filename']}, 25, FALSE, TRUE);
    // Has comments
    if (!empty($value->{$this->field_alias})) {
      $account = $this->user_load($value->{$this->aliases['comment_uid']});
      $tokens = array(
        '!user' => theme('username', $account),
        '!title' => l($filename, "node/{$value->{$this->aliases['nid']}}", array('fragment' => "comment-{$value->{$this->field_alias}}")),
      );
    }
    // No comments
    else {
      $account = $this->user_load($value->{$this->aliases['node_uid']});
      $tokens = array(
        '!user' => theme('username', $account),
        '!title' => l($filename, "node/{$value->{$this->aliases['nid']}}"),
      );
    }
    $download = l(t('Download'), file_create_url($value->{$this->aliases['filepath']}), array('attributes' => array('class' => 'atrium-activity-download')));
    return $download .' '. t('!user uploaded !title', $tokens);
  }
}
