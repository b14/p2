/**
 * @file
 * Ding list add button.
 */

(function ($) {
  "use strict";
  
  $(window).bind('resize', function (evt) {
    $('.dlab-breakout-button:visible').css('display', 'none');
  });
  
  Drupal.behaviors.ding_list_add_button = {
    attach: function (context, settings) {
      $('.ding-list-add-button', context).each(function (delta, dlab) {
        var $buttons = $('.buttons', dlab)
          .css({
            position: 'absolute',
            display: 'none'
          })
          .addClass('dlab-breakout-button')
          .appendTo('body');
        
        $('.trigger', dlab).bind('mouseenter', function (evt) {
          $buttons.css($(this).offset())
            .css('display', 'block');
          $(dlab).addClass('showing');
        });
          
        $buttons.bind('mouseleave', function (evt) {
          $buttons.css('display', 'none');
          $(dlab).removeClass('showing');
        });
      });
    }
  };
}(jQuery));