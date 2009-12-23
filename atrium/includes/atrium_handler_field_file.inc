<?php

class atrium_handler_field_file extends views_handler_field_file {
  // Render a file icon/preview instead of a text mimetype
  function render_mime($data, $values) {
    if (!empty($this->options['link_to_file'])) {
      $file = new stdClass();
      $file->fid = 1;
      $file->filepath = $values->{$this->aliases['filepath']};
      $file->filemime = $data;
      return theme('seed_fileview', $file);
    }
    else {
      return $data;
    }
  }

  function render($values) {
    if ($this->field == 'filemime') {
      return $this->render_mime(check_plain($values->{$this->field_alias}), $values);
    }
    else {
      return $this->render_link(check_plain($values->{$this->field_alias}), $values);
    }
  }
}
