<?php

/**
 * @file
 * Views hooks file.
 */

/**
 * Implements hook_views_plugins().
 */
function entity_gallery_views_plugins() {
  $path = drupal_get_path('module', 'entity_gallery');

  $plugins = array(
    'module' => 'entity_gallery',
    'style' => array(
      // Style plugin.
      'entity_gallery_style' => array(
        'title' => t('Entity Gallery'),
        'help' => t('This display style simply connects to the relevant template file.'),
        'handler' => 'views_plugin_style_entity_gallery',
        'path' => $path . '/views',
        'theme' => 'views_view_entity_gallery',
        'theme file' => 'theme.inc',
        'theme path' => $path . '/theme',
        'base' => array('node', 'comment', 'users', 'taxonomy_term_data', 'file_managed'),
        'uses row plugin' => FALSE,
        'uses fields' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'uses pager' => FALSE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
/*
// Kept for reference
    'row' => array(
      'entity_gallery' => array(
        'title' => t('Entity Gallery'),
        'help' => t('Display gallery of entities with the Entity Gallery module.'),
        'handler' => 'views_plugin_entity_gallery',
        'path' => $path . '/views',
        'base' => array('node', 'comment', 'users', 'taxonomy_term_data', 'file_managed'),
        'theme' => 'entity_gallery_row_entity',
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
*/
  );
  return $plugins;
}
