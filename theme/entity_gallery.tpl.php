<?php
/**
 * @file
 * Default output for a entity gallery entity.
*/
?>

<?php
dpm($items);
?>

<div class="entity-gallery-content clearfix" id="entity-gallery-<?php print $id; ?>">
  <?php print render($items); ?>
</div>
