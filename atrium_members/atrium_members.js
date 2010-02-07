Drupal.behaviors.atrium_members = function(context) {
  /**
   * Retrieve the active page view if present and initialize AJAX parameters
   * for refreshing the view via AJAX when necessary. This is fired when
   * Drupal.attachBehaviors is called after a successful AJAX response from
   * atrium_members.
   */
  if ($('.atrium-members-ajax', context).size() > 0) {
    var form = $('.atrium-members-addform');
    if (form) {
      // Views AJAX prep. For the origin of much of this code, see
      // ajax_view.js in Views.
      if ($('input.atrium-members-addform-view', form).size() > 0) {
        // Retrieve current page view's settings and DOM element.
        var settings = {};
        var view = '';
        var identifier = $('input.atrium-members-addform-view', form).val().split(':');
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
   * Attach to Atrium members addforms and do the following:
   * - Event handler when hitting "enter" in the username field.
   * - Event handler when clicking the "Add" button.
   */
  $('.atrium-members-addform:not(.atrium-members-processed)')
    .addClass('atrium-members-processed')
    .each(function() {
      var form = $(this);

      // Detect enter key, submit.
      $('input.form-text', this).keypress(function(event) {
        if (event.keyCode == 13) {
          var selected = $('.selected', $(this).siblings('#autocomplete:has(.selected)'));
          if (selected.size() > 0) {
            $(this).val(selected.get(0).autocompleteValue);
          }
          $('input.form-submit', form).mousedown();
          return false;
        }
      });

      // Clear out textfield value on submit.
      $('input.form-submit', this).mousedown(function() {
        $('input.form-text', form).val('');
      });
    });
};
