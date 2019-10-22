<?php

/**
 * @file
 * Provides the Entity Gallery views entity style plugin.
 */

/**
  * Implements a style type plugin for the Views module.
  */
class views_plugin_style_entity_gallery extends views_plugin_style {

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->base_table = $view->base_table;
    $this->base_field = $this->entity_gallery_views_3_support();
  }

  // Return base_field based on base_table. Shamelessly stolen from Display Suite
 function entity_gallery_views_3_support() {
    if (strpos($this->base_table, 'eck_') === 0) {
      // Base tables of entities created by entity construction kit (eck)
      // are prefixed with 'eck_' and the base field is always 'id'.
      $this->entity_type = str_replace('eck_', '', $this->base_table);
      return 'id';
    }

    $base_table_fields = array(
      'node' => array('field' => 'nid', 'entity_type' => 'node'),
      'comment' => array('field' => 'cid', 'entity_type' => 'comment'),
      'users' => array('field' => 'uid', 'entity_type' => 'user'),
      //'apachesolr' => array('field' => 'nid', 'entity_type' => 'node'),
      'taxonomy_term_data' => array('field' => 'tid', 'entity_type' => 'taxonomy_term'),
      'file_managed' => array('field' => 'fid', 'entity_type' => 'file'),
      //'micro' => array('field' => 'mid', 'entity_type' => 'micro'),
    );
 
    $this->entity_type = isset($base_table_fields[$this->base_table]) ? $base_table_fields[$this->base_table]['entity_type'] : 'node';
    return isset($base_table_fields[$this->base_table]) ? $base_table_fields[$this->base_table]['field'] : 'nid';
  }

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

  /**
   * Query method.
   */
  function query() {
    parent::query();
    $base_table = $this->view->query->base_table;
    // I need to fix this for different entity types!!!!
    if($base_table == 'node') {
      $this->view->query->add_field('', 'node.nid', 'nid');      
    } elseif($base_table == 'file_managed') {
      $this->view->query->add_field('', 'file_managed.fid', 'fid');
    }
  }

  /**
   * Preload all entities.
   */
  function pre_render($values) {
    $ids = array();

    switch ($this->base_table) {
      case 'node':
        foreach ($values as $row) {
          $ids[] = $row->nid;
        }
        //$this->entities = node_load_multiple($ids);
        $this->options['entity_type'] = $this->base_table;
        break;

      case 'comment':
        $this->entities = comment_load_multiple($ids);
        break;
        
      case 'users':
        $this->entities = user_load_multiple($ids);
        break;
        
      case 'taxonomy_term_data':
        $this->entities = taxonomy_term_load_multiple($ids);
        if (function_exists('i18n_taxonomy_localize_terms')) {
          global $language;
          foreach($this->entities as $index => &$entity) {
            $entity = i18n_taxonomy_localize_terms($entity, $language->language);
          }
        }
        break;
      case 'file_managed':
        foreach ($values as $row) {
          $ids[] = $row->fid;
        }
        $this->options['entity_type'] = $this->base_table;
        break;
    }
  }

  /**
   * Render each $row.
   */
  function render_items($values) {
    $items = array();
    foreach ($values as $value) {
      $items[][] = $value->nid;
    }
    $output = theme('views_view_entity_gallery',
      array(
        'view' => $this->view,
        'options' => $this->options,
        'rows' => $items,
        'title' => $this->view->name,
        )
      );
    if (empty($output)) {
      return;
    }
  return $output;
  }
}
