<?php
/**
 * @file
 * Default output for a entity gallery entity.
*/
?>
<div id="entity-gallery">
  <div id="<?php print $settings['custom_class'] ?>-<?php print $id; ?>" class="<?php print $settings['custom_class'] ?>-content clearfix"><a name="v"></a>
    <div id="<?php print $settings['custom_class'] ?>" class="<?php print $settings['custom_class'] ?>-main"> <?php print render($default); ?> </div>
    <div id="<?php print $settings['custom_class'] ?>-list" class="<?php print $settings['custom_class'] ?>-list">
      <ul class="<?php print $settings['custom_class'] ?>-list jcarousel-skin-entity-gallery">
        <?php
        foreach($render as $item) {
  ?>
        <li id="entity-gallery-list" class="<?php print $settings['custom_class'] ?>-list-item"> <a href="<?php print $item['ajax_link'] ?>" class="use-ajax">
          <?php if(!empty($item['field_image'])): ?>
          <?php print render($item['field_image']); ?>
          <?php endif; ?>

<?php
            if(isset($item['field_video_category'])) {
              if($item['field_video_category'][0]['#markup'] != 'Interstitial' || $item['field_video_category'][0]['#markup'] != 'Other' || $item['field_video_category'][0]['#markup'] != 'Promotion') {
?>

          <div class="cove-category"><?php print render($item['field_video_category']); ?></div>
<?php
             }
            }
?>
          <h3 class="node-title"><?php print render($item['#node']->title); ?></h3>
          </a> </li>
<?php
            }
?>
      </ul>
  
  <?php
      jcarousel_add($settings['custom_class'].'-list', array('horizontal' => TRUE, 'skin' => 'entity_gallery'));
  ?>
  
    </div>
  </div>
</div>