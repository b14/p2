// TODO Why is file included here? I cannot find any references to it in the
// module and it looks as if it belongs in the ting_carousel module.
/**
 * @file
 * Handles the carousels loading of content and changes between tabs. There are
 * two selectors to change tabs based on breaks points (which is handle by the
 * theme).
 *
 * For large screens the normal tab list (ul -> li) is used while on small
 * screens (mobile/tables) a select dropdown is used.
 *
 */
(function ($) {
  "use strict";

  var TingCarousel = (function() {

    var cache = [];
    var carousel;

    /**
     * Private: Check is the device have support for touch events.
     */
    function _is_touch_device() {
      // First part work in most browser the last in IE 10.
      return !!('ontouchstart' in window) || !!('onmsgesturechange' in window);
    }

    /**
     * Private: Enable draggable touch support to the carousel, but only if the
     * device is touch enabled.
     */
    function _add_touch_support() {
      if (_is_touch_device()) {
        // Add support for touch displays (requires jQuery Touch Punch).
        $('.rs-carousel-runner',carousel).draggable({
          axis: "x",
          stop: function() {
            var left = $('.rs-carousel-runner',carousel).position().left;

            // Left side reached.
            if (left > 0) {
              carousel.carousel('goToPage', 0);
            }

            // Right side reached.
            if ($('.rs-carousel-mask',carousel).width() - $('.rs-carousel-runner',carousel).width() > left) {
              var lastIndex = carousel.carousel('getNoOfPages') - 1;
              carousel.carousel('goToPage', lastIndex);
            }
          }
        });

        // Hide navigation arrows.
        $('.rs-carousel-action-prev',carousel).hide();
        $('.rs-carousel-action-next',carousel).hide();
      }
    }

    /**
     * Public: Init the carousel and fetch content for the first tab.
     */
    function init(prefixer) {
      // Select the carousel element.
      carousel = $(prefixer + ' .rs-carousel-items');
      console.log(carousel);
      // Start the carousel.
      carousel.carousel({
        noOfRows: 1,
        orientation: 'horizontal',
        itemsPerTransition: 'auto'
      });
      

      // Maybe add support for touch devices (will only be applied on touch
      // enabled devices).
      // _add_touch_support();

    }

    /**
     * Expoes public functions.
     */
    return {
        name: 'ting_carousel',
        init: init
    };
  })();

  /**
   * Start the carousel when the document is ready.
   */
  $(document).ready(function() {
    for (var i in Drupal.settings.ting_carousel) {
      TingCarousel.init(Drupal.settings.ting_carousel[i]);
    }
  });
})(jQuery);
