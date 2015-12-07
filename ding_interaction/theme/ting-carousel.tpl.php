// TODO Why is file included here? I cannot find any references to it in the
// module and it looks as if it belongs in the ting_carousel module.
<?php
/**
 * @file
 * Available variables:
 * - $objects: Array with each tab search.
 */
?>
<!-- The wrapper div is important because rs-carousel replaces it -->
<div id="<?php print $id; ?>" class="ting-carousel rs-carousel-wrapper">
  <div class="rs-carousel">
    <div class="rs-carousel-inner">
      <div class="rs-carousel-items">
        <ul>
         <?php print $object_items; ?>
        </ul>
      </div>
    </div>
  </div>
</div>
