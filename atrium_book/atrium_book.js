Drupal.behaviors.atrium = function(context) {
  // Add drill-down functionality to atrium book blocks.
  if (jQuery().drilldown) {
    $('div.page-region div.block-atrium_book:has(ul.menu):not(.atrium_book-processed)')
      .addClass('atrium_book-processed')
      .each(function() {
        $(this).addClass('drilldown');
        var menu = $(this);
        var trail = '#' + $(this).attr('id') + ' span.trail';
        $('ul.menu:first', this).parent().drilldown('init', {'activePath': Drupal.settings.atriumBookPath, 'trail': trail});
    });
  }
}