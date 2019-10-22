<?php

/**
 * @file
 * Provides the Entity Gallery views entity style plugin.
 */

 /**
  * Implements a style type plugin for the Views module.
  */
class views_plugin_entity_gallery extends views_plugin_style {

  function option_definition() {
    $options = parent::option_definition();
    $options['main_mode'] = array('default' => 'full');
    $options['main_links'] = array('default' => 0);
    $options['secondary_mode'] = array('default' => 'teaser');
    $options['secondary_links'] = array('default' => 0);
    $options['replace_links'] = array('default' => 1);
    $options['custom_class'] = array('default' => FALSE);
    return $options;
   }
 
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $settings = array();

    $mode_options = array();
    $entity_type = $this->view->base_table;
    // In case we're working with users or managed files, change the entity type variable.
    if ($entity_type == 'users') $entity_type = 'user';
    if ($entity_type == 'file_managed') $entity_type = 'file';
    $entity_view_modes = ds_entity_view_modes($entity_type);
    foreach ($entity_view_modes as $key => $view_mode) {
      $mode_options[$key] = $view_mode['label'];
    }

  // Select the main mode
  $form['main_mode'] = array(
    '#type'           => 'select',
    '#title'          => t('Primary display mode'),
    '#description'    => t('Select the view mode to use for the primary item'),
    '#default_value'  => $this->options['main_mode'],
    '#options'        => $mode_options,
  );
  // Select the main links option
  $form['main_links'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Show Links?'),
    '#default_value'  => $this->options['main_links'],
  );
  // Select the secondary mode
  $form['secondary_mode'] = array(
    '#type'           => 'select',
    '#title'          => t('Thumbnail display mode'),
    '#description'    => t('Select the view mode to use for the smaller previews'),
    '#default_value'  => $settings['secondary_mode'],
    '#default_value'  => $this->options['secondary_mode'],
    '#options'        => $mode_options,
  );
  // Select the secondary links option
  $form['secondary_links'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Show Links?'),
    '#default_value'  => $this->options['secondary_links'],
  );

  // As users if we want to replace their links
  $form['replace_links'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Replace tease links?'),
    '#description'    => t('If you turn this on clicking on a tease image will load that content in the primary area.<br />If this option is turned off links will be preserved and clicking on a tease title<br /> or image will link directly to the content.'),
    '#default_value'  => $this->options['replace_links'],
  );
	// Custom CSS classes
  $form['custom_class'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Custom Class'),
    '#description'    => t('Custom class to wrap this element. Otherwise the default "entity-gallery" will be used.'),
    '#default_value'  => $this->options['custom_class'],
  );
  return $form;
  }
}

