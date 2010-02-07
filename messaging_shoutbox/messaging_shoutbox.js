// $Id$

Drupal.behaviors.messaging_shoutbox = function (context) {
  /**
   * Retrieve the active page view if present and initialize AJAX parameters
   * for refreshing the view via AJAX when necessary. This is fired when
   * Drupal.attachBehaviors is called after a successful AJAX response from
   * atrium_members.
   */
  if ($('.messaging-shoutbox-ajax', context).size() > 0) {
    var form = $('.shoutform');
    if (form) {
      // Views AJAX prep. For the origin of much of this code, see
      // ajax_view.js in Views.
      if ($('input.messaging-shoutbox-shoutform-view', form).size() > 0) {
        // Retrieve current page view's settings and DOM element.
        var settings = {};
        var view = '';
        var identifier = $('input.messaging-shoutbox-shoutform-view', form).val().split(':');
        for (var i in Drupal.settings.views.ajaxViews) {
          if (
            Drupal.settings.views.ajaxViews[i].view_name == identifier[0] &&
            Drupal.settings.views.ajaxViews[i].view_display_id == identifier[1]
          ) {
            settings = Drupal.settings.views.ajaxViews[i];
            view = $('.view-dom-id-' + settings.view_dom_id);
            break;
          }
        }

        // If there are multiple views this might've ended up showing up multiple times.
        var ajax_path = Drupal.settings.views.ajax_path;
        if (ajax_path.constructor.toString().indexOf("Array") != -1) {
          ajax_path = ajax_path[0];
        }

        // Prepare viewData params.
        var viewData = settings;
        viewData.js = 1;

        // AJAX request.
        $.ajax({
          url: ajax_path,
          type: 'GET',
          data: viewData,
          success: function(response) {
            // Call all callbacks.
            if (response.__callbacks) {
              $.each(response.__callbacks, function(i, callback) { eval(callback)(view, response); });
            }
          },
          error: function(xhr) { Drupal.Views.Ajax.handleErrors(xhr, ajax_path); },
          dataType: 'json'
        });
      }
    }
  }

  /**
   * Attach to Shoutbox forms and clear form field when submitting.
   */
  $('.shoutform:not(.messaging-shoutbox-processed)')
    .addClass('messaging-shoutbox-processed')
    .each(function() {
      var form = $(this);
      // Clear out textarea value on submit.
      $('input.form-submit', this).mousedown(function() {
        $('textarea', form).val('');
      });
    });
};
