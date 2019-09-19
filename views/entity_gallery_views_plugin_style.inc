<?php

/**
 * @file
 * Provides the Entity Gallery views entity style plugin.
 */

/**
  * Implements a style type plugin for the Views module.
  */
class entity_gallery_views_plugin_style extends views_plugin_style {
  /**
   * If this view is displaying an entity, save the entity type and info.
   */
/*  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
  }
  */
  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();
    //dpm($this);
    return $options;
  }
}