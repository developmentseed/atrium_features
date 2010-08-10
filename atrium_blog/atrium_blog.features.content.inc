<?php

/**
 * Implementation of hook_content_default_fields().
 */
function atrium_blog_content_default_fields() {
  $fields = array();

  // Exported field: field_referenced_book_page
  $fields['blog-field_referenced_book_page'] = array(
    'field_name' => 'field_referenced_book_page',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => 0,
      'parent' => '',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'book' => 'book',
      'event' => 'event',
      'imageset' => 'imageset',
      'admin_message' => 0,
      'blog' => 0,
      'casetracker_basic_case' => 0,
      'feedapi_node' => 0,
      'group' => 0,
      'page' => 0,
      'profile' => 0,
      'casetracker_basic_project' => 0,
      'shoutbox' => 0,
      'feed_ical_item' => 0,
      'feed_ical' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_referenced_book_page][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'autocomplete_match' => 'contains',
      'size' => NULL,
      'label' => 'Referenced Page',
      'weight' => 0,
      'description' => 'Type in the title of another post to add a reference.',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Referenced Page');

  return $fields;
}
