/**
 * Drupal behaviors implementation for Atrium Shoutbox.
 */
Drupal.behaviors.atrium_shoutbox = function(context) {
  /**
   * Mark shoutboxes as "submitting" while AHAH is processing. After submission
   * clear the shoutbox (attachBehaviors is called by ahah.js).
   */
  $('form.shoutform.submitted textarea').removeClass('submitted').val('');
  $('form.shoutform:not(.atrium-shoutbox-processed)')
    .addClass('atrium-shoutbox-processed')
    .each(function() {
      var form = $(this);
      $('input.form-submit', this).mousedown(function() {
        form.addClass('submitted');
      });
    });

  /**
   * Adds a handler to the Atrium Shoutbox launcher link that sets a cookie
   * with the current pageload's server timestamp when clicked. The cookie
   * is used server-side for the non-critical task of determining how many
   * shouts have not been viewed by the current user.
   */
  if (jQuery.cookie && Drupal.settings.atrium_shoutbox.timestamp) {
    $('#atrium-shoutbox-launcher:not(.atrium-shoutbox-processed)')
      .addClass('atrium-shoutbox-processed')
      .each(function() {
        if ($(this).is('.active')) {
          $.cookie('AtriumShoutbox', Drupal.settings.atrium_shoutbox.timestamp, {expires: 14, path: '/'});
        }
        else {
          $(this).click(function() {
            if ($('span.count', this).size() > 0) {
              $('span.count', this).hide();
            }
            $.cookie('AtriumShoutbox', Drupal.settings.atrium_shoutbox.timestamp, {expires: 14, path: '/'});
          });
        }
      });
  }
};
