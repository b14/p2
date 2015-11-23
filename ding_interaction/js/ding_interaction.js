/**
 * @file
 * Ding interaction widget
 */

(function ($) {
  
  $.widget("ding.interaction", {
    // default options
    options: {
      red: 255,
      green: 0,
      blue: 0
    },

    // the constructor
    _create: function() {
      this.element
        // add a class for theming
        .addClass( "ding-interaction" )
        // prevent double click to select text
        .disableSelection();

      this.closer = $('.close-btn', this.element).addClass('icon-remove-sign button');
      
      // bind click events on the changer button to the random method
      $(this.closer).on('click', this.closePane);
      this._refresh();
    },
    closePane: function(event) {
      $(this).closest(".pane-info-pane").slideUp();
    },
    // called when created, and later when changing options
    _refresh: function() {
      // trigger a callback/event
      this._trigger( "change" );
    },
    
    // events bound via _on are removed automatically
    // revert other modifications here
    _destroy: function() {
      // remove generated elements
      this.closer.remove();

      this.element
        .removeClass( "ding-interaction" )
        .enableSelection();
    },

    // _setOptions is called with a hash of all options that are changing
    // always refresh when changing options
    _setOptions: function() {
      // _super and _superApply handle keeping the right this-context
      this._superApply( arguments );
      this._refresh();
    },

    // _setOption is called for each individual option that is changing
    _setOption: function( key, value ) {
      this._super( key, value );
    }
  });
  
  Drupal.behaviors.ding_interaction = {
    attach: function (context, settings) {
      $('.ding-interaction-pane', context).interaction();
    }
  };
})(jQuery);
