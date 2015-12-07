<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

$plugin = array(
  'title' => t('Ding serendipity content'),
  'description' => t('Display serendipity content'),
  'admin info' => 'ding_serendipity_admin_info',
  'single' => TRUE,
  'required context' => array(
    new ctools_context_optional(t('Node'), 'node'),
    new ctools_context_optional(t('Search term'), 'string'),
    new ctools_context_optional(t('Taxonomy terms'), 'terms'),
  ),
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration information in panels.
 */
function ding_serendipity_admin_info($subtype, $conf, $context) {
  $output = new stdClass();
  $output->title = t('Serendipity inspiration list');
  $output->content = t('Serendipity content. View mode: @view_mode', array('@view_mode' => $conf['view_mode'])) . '<br/>';
  $output->content .= t('Sort by weight: @sort_weight', array('@sort_weight' => $conf['sort_weight'])) . '<br/>';
  $output->content .= t('Maximum items: @max', array('@max' => $conf['max'])) . '<br/>';
  $output->content .= t('Minimum items: @min', array('@min' => $conf['min'])) . '<br/>';
  $output->content .= t('Sort random: @random', array('@random' => $conf['random'])) . '<br/>';
  return $output;
}

/**
 * Implements hook_content_type_render().
 */
function ding_serendipity_serendipity_content_type_render($subtype, $conf, $panel_args, $context) {
  $context_data = array();
  if (!empty($context[0]->data)) {
    $context_data['node'] = $context[0]->data;
    $context_data['node_nid'] = $panel_args[0];
  }
  
  if (!empty($context[1]->data)) {
    $context_data['search_term'] = $context[1]->data;
  }
  
  if (!empty($context[2]->data)) {
    $context_data['taxonomy_term'] = $context[2]->data;
    $context_data['taxonomy_tid'] = $panel_args[0];
  }
  
  $context_data += array(
    'view_mode' => isset($conf['view_mode']) ? $conf['view_mode'] : 'teaser',
    'sort_weight' => isset($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => isset($conf['max']) ? $conf['max'] : 0,
    'min' => isset($conf['min']) ? $conf['min'] : 0,
    'random' => isset($conf['random']) ? $conf['random'] : FALSE,
  );
  
  if (isset($conf['selected'])) {
    foreach ($conf['selected'] as $key => $value) {
      $context_data[$key] = TRUE;
    }
  }

  $content = ding_serendipity_render($context_data);

  $output = array();
  if (!empty($content)) {
    foreach ($content as $key => $item) {
      $item['#weight'] = $key;
      $output['content'][] = $item;
    }
  }
  
  $block = new stdClass();
  // TODO Respecting override_title should not be necesary here. Panels
  // should take care of that.
  $block->title = ($conf['override_title']) ? $conf['override_title_text'] : t('Serendipity content');
  $block->content = $output;
  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_serendipity_content_type_edit_form($form, &$form_state) {
  $base = ding_serendipity_form_base($form_state);
  $form += $base;

  $info = ding_serendipity_get_info();
  $options = array();
  foreach ($info as $key => $value) {
    // TODO: keys does not seem to be a declared part of the return value in
    // ding_serendipity.api.inc. Please document it.
    foreach ($value['keys'] as $serendipity_key) {
      if (!isset($options[$serendipity_key])) {
        $options[$serendipity_key] = $serendipity_key;
      }
    }
  }

  // TODO Related to the komment above: I do not understand what keys mean here.
  // It is a very generic term. Could this be elaborated?
  $form['selected'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => array_unique($options),
    '#multiple' => TRUE,
    '#default_value' => $form_state['conf']['selected'],
    '#description' => t('Select any additional keys which apply to the serendipity display you wish to present.'),
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_serendipity_content_type_edit_form_submit($form, &$form_state) {
  // TODO How abour adding ding_serendipity_form_base_submit as a submit handler
  // for ding_serendipity_form_base()?
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['selected'] = !empty($form_state['values']['selected']) ? $form_state['values']['selected'] : FALSE;
}

/**
 * Setup a base form for serendipity ctools content types.
 * TODO: If this is a reusable form then please move it to a shared file e.g.
 * ding_serendipity.module.
 */
function ding_serendipity_form_base($form_state) {
  $form['view_mode'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => array(
      // TODO Where does this list come from? Could it be extracted through
      // code or otherwise documented?
      'full' => t('Full'),
      'teaser' => t('Teaser'),
      'big_teaser' => t('Big teaser'),
      'grid_item' => t('Grid item'),
      'list_item_short' => t('Short list item'),
    ),
    '#default_value' => (isset($form_state['conf']['view_mode'])) ? $form_state['conf']['view_mode'] : 'full',
    '#description' => t('Select the view mode which the content will display with.'),
  );
  
  $form['sort_weight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort by by weight.'),
    '#default_value' => (isset($form_state['conf']['random'])) ? $form_state['conf']['sort_weight'] : 0,
  );
  
  $form['max'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity maximum'),
    '#description' => t('The maximum number of items to display.'),
    '#default_value' => (isset($form_state['conf']['max'])) ? $form_state['conf']['max'] : 2,
    '#size' => 2,
    '#maxlength' => 2,
  );
  
  $form['min'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity minimum'),
    '#description' => t('Select the minimum amount of items displayed.'),
    '#default_value' => (isset($form_state['conf']['min'])) ? $form_state['conf']['min'] : 0,
    '#size' => 3,
    '#maxlength' => 3,
  );
  
  $form['random'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort by random order.'),
    '#default_value' => (isset($form_state['conf']['random'])) ? $form_state['conf']['random'] : 0,
  );
  
  return $form;
}

/**
 * Setup a base form submit for serendipity ctools content types.
 */
function ding_serendipity_form_base_submit(&$form_state) {
  $form_state['conf']['view_mode'] = !empty($form_state['values']['view_mode']) ? $form_state['values']['view_mode'] : 'big_teaser';
  $form_state['conf']['sort_weight'] = !empty($form_state['values']['sort_weight']) ? $form_state['values']['sort_weight'] : FALSE;
  $form_state['conf']['max'] = !empty($form_state['values']['max']) ? $form_state['values']['max'] : 0;
  $form_state['conf']['min'] = !empty($form_state['values']['min']) ? $form_state['values']['min'] : 0;
  $form_state['conf']['random'] = !empty($form_state['values']['random']) ? $form_state['values']['random'] : FALSE;
}
