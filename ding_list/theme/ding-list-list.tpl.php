<?php
/**
 * @file
 * Ding List list template.
 */
?>
 
<div <?php
if ($sortable !== FALSE): print 'ref="' . $sortable . '" '; endif; ?>class="<?php print $classes; ?>">
  <div class="ding-list-items">
    <?php print render($items); ?>
  </div>
</div>
