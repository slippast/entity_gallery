<?php
/**
 * @file
 * Theming functions for the Entity Gallery module.
 */

/**
 * Template preprocess handler for 'entity_gallery' theme.
 */
function template_preprocess_entity_gallery(&$vars) {
  // Let's detect the entity type and act accordingly.
  // Only nodes and files work thus far.
  switch ($vars['settings']['entity_type']) {
    case 'node':
      $key = 'nid';
      $file_type = 'node';
      $entity_type = 'node';
      break;
    case 'comment':
      break;
    case 'users':
      break;
    case 'taxonomy_term_data':
      $key = 'tid';
      break;
    case 'file_managed':
      $key = 'fid';
      $file_type = 'file';
      $entity_type = 'file_managed';
      break;
  }
  
  $key = 'nid';
  $file_type = 'node';
  $entity_type = 'node';
  
  // Give us the theme hook to created custom displays.
  if($vars['theme_hook_original'] == 'entity_gallery') {
     $vars['settings']['entity_type'] = 'node';

    // Use the custom class to create a custom theme
    if(isset($vars['settings']['custom_class'])) {
       $vars['theme_hook_suggestions'][] = 'entity_gallery__'. preg_replace('/-/', '_', $vars['settings']['custom_class']);
    }

    // Set a default class if none exists
    // This is important.
    if(!isset($vars['settings']['custom_class'])) {
      $vars['settings']['custom_class'] = 'entity-gallery';
    }

    // This path allows the ajax load to work.
    // These are also important, otherwise the
    // ajax function doesn't know what to do.
    $ajax_root = '/gallery/ajax/'.$vars['settings']['entity_type'].'/'.$vars['settings']['main_mode'].'/'.$vars['settings']['custom_class'].'/';
    $vars['settings']['ajax_root'] = $ajax_root;
  
    // Convert items from stdclass to an array
    $items = array();
    $eid = array();
    $i=0;
    foreach($vars['items'] as $item) {
      if(is_object($item)) {
        if($entity_type == 'file_managed') {
          $items[$i] = $item->fid;
        } elseif($entity_type == 'node') {
          $items[$i] = $item->nid;
        }
        $i++;
      } else {
        $items[$i] = $item['target_id'];
        $i++;
      }
    }
    
    // First do file_managed entities
    if($entity_type == 'file_managed') {
      unset($vars['items']);
      foreach($items as $delta => $eid['target_id']) {
        // Test to see if the eid is ready to go
        if(empty($eid['target_id'])) {
          $eid['target_id'] = $eid[0];
        }
        // Sets the default item for display
        if($delta == 0) {
          $default_entity = file_load($eid['target_id']);
          $vars['default'][0] = file_view($default_entity, $vars['settings']['main_mode']);
        }
        
        // Iterate through, all loaded entites
        // Including the first one.
        $entity = file_load($eid['target_id']);
        if(is_object($entity)) {
          // Do the name. If the title exists, use it. If not show the file name
          // in the link
          if(!empty($entity->field_file_image_title_text)) {
            $title = t($entity->field_file_image_title_text);
          } else {
            $title = t($entity->filename);
          }
          $vars['items'][$delta][$entity_type][$eid['target_id']] = file_view($entity, $vars['settings']['secondary_mode']);
          $vars['items'][$delta][$entity_type][$eid['target_id']]['ajax_link'] = $ajax_root.$eid['target_id'];
  
          // Remove the links if requested
          if($vars['settings']['secondary_links'] == 0) {
            unset($vars['items'][$delta][$entity_type][$eid['target_id']]['links']);
          }
          $vars['render'][$delta] = $vars['items'][$delta][$entity_type][$eid['target_id']];
          $vars['render'][$delta]['eid'] = $eid['target_id'];
  
          // Fix the markup
          $vars['items'][$delta][$entity_type][$eid['target_id']]['title'][0]['#markup'] = '<a href="'.$ajax_root.$eid['target_id'].'" class="use-ajax">'.$title.'</a>';
      
          // Fix the #items array
          $vars['items'][$delta][$entity_type][$eid['target_id']]['title']['#items'][0]['value'] = '<a href="'.$ajax_root.$eid['target_id'].'" class="use-ajax">'.$title.'</a>';
        }
      }
    // Second do nodes
    } elseif($entity_type == 'node') {
      foreach($items as $delta => $eid['target_id']) {
        // Test to see if the eid is ready to go
        if(empty($eid['target_id'])) {
          $eid['target_id'] = $eid[0];
        }
        // Display the default entity
        if($delta == 0) {
          $default_entity = entity_load($vars['settings']['entity_type'], $eid, array(), TRUE);
          $vars['default'][0] = entity_view($vars['settings']['entity_type'], $default_entity, $vars['settings']['main_mode']);

          // Remove the links if requested
          if($vars['settings']['main_links'] == 0) {
            unset($vars['default'][0][$vars['settings']['entity_type']][$eid['target_id']]['links']);
          }
         }
  
        // Iterate through, all loaded entites
        // Including the first one.
        $entity = entity_load($vars['settings']['entity_type'], $eid, array(), TRUE);
        if(isset($entity[$eid['target_id']])) {
            
          $title = t($entity[$eid['target_id']]->title);
          $vars['items'][$delta] = entity_view($vars['settings']['entity_type'], $entity, $vars['settings']['secondary_mode']);
          $vars['items'][$delta][$vars['settings']['entity_type']][$eid['target_id']]['ajax_link'] = $ajax_root.$eid['target_id'];
      
          // Remove the links if necessary
          if($vars['settings']['secondary_links'] == 0) {
            unset($vars['items'][$delta][$vars['settings']['entity_type']][$eid['target_id']]['links']);
          }
          $vars['render'][$delta] = $vars['items'][$delta][$vars['settings']['entity_type']][$eid['target_id']];
          $vars['render'][$delta]['eid'] = $eid['target_id'];
                
          // Fix the markup
          $vars['items'][$delta][$vars['settings']['entity_type']][$eid['target_id']]['title'][0]['#markup'] = '<a href="'.$ajax_root.$eid['target_id'].'" class="use-ajax">'.$title.'</a>';
      
          // Fix the #items array
          $vars['items'][$delta][$vars['settings']['entity_type']][$eid['target_id']]['title']['#items'][0]['value'] = '<a href="'.$ajax_root.$eid['target_id'].'" class="use-ajax">'.$title.'</a>';
  
        }
      }
    }
  }
}

/**
 * Theme 'views_view_entity_gallery'.
 */
function theme_views_view_entity_gallery($vars) {
  $view = $vars['view'];
  $output = theme('entity_gallery', array(
    'items' => $vars['rows'],
    'settings' => $vars['options'],
  ));
  return $output;
}
