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
