(function ($) {
  Drupal.behaviors.entity_gallery = {
    attach: function(context, settings) {
      var $link = $('#entity-gallery');
       
      new Drupal.ajax('#entity-gallery', $link, {

      alert(settings);

        url: $link.attr('href'),
        settings: {},
        event: 'click tap'
      });
    }
  }
})(jQuery);