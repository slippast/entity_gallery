<?php
/**
 * @file
 * Default output for a entity gallery entity.
*/

?>
<div id="entity-gallery" class="video-grid-container <?php print $settings['custom_class'] ?>">
  <div id="<?php print $settings['custom_class'] ?>-<?php print $id; ?>" class="<?php print $settings['custom_class'] ?>-content clearfix">
    <a name="v"></a>
    <a name="v-<?php print $settings['custom_class'] ?>"></a>
    <div id="<?php print $settings['custom_class'] ?>" class="<?php print $settings['custom_class'] ?>-main"> <?php print render($default); ?> </div>
    <div id="<?php print $settings['custom_class'] ?>-list-container" class="<?php print $settings['custom_class'] ?>-list">
      <ul id="<?php print $settings['custom_class'] ?>-list" class="entity-gallery-list video-grid-list-container <?php print $settings['custom_class'] ?>-list">
        <?php foreach($render as $item) { ?>
          <li id="<?php print $settings['custom_class'] ?>-<?php print $item['eid'] ?>" class="<?php print $settings['custom_class'] ?>-list-item">
            <a href="<?php print $item['ajax_link'] ?>" class="use-ajax">
            <?php if(!empty($item['field_image'])): ?>
            <?php print render($item['field_image']); ?>
            <?php endif; ?>

            <?php if(!empty($item['field_episode_header_image'])): ?>
            <?php print render($item['field_episode_header_image']); ?>
            <?php endif; ?>
            <h3 class="node-title"><?php print render($item['#node']->title); ?></h3>
            </a>
          </li>
        <?php } ?>

      </ul> 
    </div>
  </div>
</div>
