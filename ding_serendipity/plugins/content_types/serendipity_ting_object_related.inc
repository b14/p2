<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

$plugin = array(
  'title' => t('Ding serendipity with TingObject Related'),
  'description' => t('Display serendipity content of type the ting object.'),
  'admin info' => 'ding_serendipity_serendipity_ting_object_related_admin_info',
  'single' => TRUE,
  'required context' => array(
    new ctools_context_optional(t('Node'), 'node'),
    new ctools_context_optional(t('Search term'), 'string'),
    new ctools_context_optional(t('Taxonomy terms'), 'terms'),
    new ctools_context_optional(t('Ting object'), 'ting_object'),
  ),
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration information in panels.
 */
function ding_serendipity_serendipity_ting_object_related_admin_info($subtype, $conf, $context) {
  $output = new stdClass();
  $output->title = t('Serendipity list with ting object');
  $output->content = t('Serendipity content. View mode: @view_mode', array('@view_mode' => $conf['view_mode'])) . '<br/>';
  $output->content .= t('Serendipity keys: @keys', array('@keys' => $conf['selected_keys'])) . '<br/>';
  $output->content .= t('Sort by weight: @sort_weight', array('@sort_weight' => $conf['sort_weight'])) . '<br/>';
  $output->content .= t('Maximum items: @max', array('@max' => $conf['max'])) . '<br/>';
  $output->content .= t('Minimum items: @min', array('@min' => $conf['min'])) . '<br/>';
  $output->content .= t('Sort random: @random', array('@random' => $conf['random'])) . '<br/>';
  return $output;
}

/**
 * Implements hook_content_type_render().
 */
function ding_serendipity_serendipity_ting_object_related_content_type_render($subtype, $conf, $panel_args, $context) {
  $context_data = array();
  if (isset($conf['selected_keys'])) {
    foreach ($conf['selected_keys'] as $key => $value) {
      $context_data[$key] = TRUE;
    }
  }
  
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
  
  if (!empty($context[3]->data)) {
    $context_data['ting_object'] = $context[2]->data;
    $context_data['ting_object_id'] = $panel_args[0];
  }
  
  $context_data += array(
    'view_mode' => isset($conf['view_mode']) ? $conf['view_mode'] : 'compact',
    'sort_weight' => isset($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => isset($conf['max']) ? $conf['max'] : 0,
    'min' => isset($conf['min']) ? $conf['min'] : 0,
    'random' => isset($conf['random']) ? $conf['random'] : FALSE,
    'bundle' => 'ting_object',
  );

  $content = ding_serendipity_render($context_data);

  $output = array();
  if (!empty($content)) {
    $path = drupal_get_path('module', 'ding_serendipity');

    drupal_add_css($path . '/css/ding_serendipity.css');
    drupal_add_library('system', 'drupal.ajax');
    
    drupal_add_js($path . '/js/ding_serendipity.js');
    drupal_add_js(array('ding_serendipity' => array('context' => $context_data)), 'setting');
    
    $tmp = array();
    foreach ($content as $key => $item) {
      $item['#weight'] = $key;
      $output['content'][] = $item;
      $tmp[] = $item;
    }
  }

  $block = new stdClass();
  $block->title = ($conf['override_title']) ? $conf['override_title_text'] : t('Serendipity materials');
  $block->content = $output;
  
  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_serendipity_ting_object_related_content_type_edit_form($form, &$form_state) {
  // Get the available serendipity keys.
  $info = ding_serendipity_get_info();
  $options = array();
  foreach ($info as $key => $value) {
    foreach ($value['keys'] as $serendipity_key) {
      if (!isset($options[$serendipity_key])) {
        $options[$serendipity_key] = $serendipity_key;
      }
    }
  }

  // Setup a select field enabling the admin to customize the filter.
  $form['selected_keys'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => array_unique($options),
    '#multiple' => TRUE,
    '#default_value' => (isset($form_state['conf']['selected_keys'])) ? $form_state['conf']['selected_keys'] : '',
    '#description' => t('Select any additional keys which apply to the serendipity display you wish to present.'),
  );
  
  // Get ting object entity info and extract the available view modes.
  $entity_info = entity_get_info('ting_object');
  $view_mode_options = array();
  foreach ($entity_info['view modes'] as $key => $view_mode) {
    $view_mode_options[$key] = $view_mode['label'];
  }
  
  $form['view_mode'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => $view_mode_options,
    '#default_value' => (isset($form_state['conf']['view_mode'])) ? $form_state['conf']['view_mode'] : 'full',
    '#description' => t('Select the view mode which the content will display with.'),
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
  
  $form['sort_weight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort by by weight.'),
    '#default_value' => (isset($form_state['conf']['random'])) ? $form_state['conf']['sort_weight'] : 0,
  );
  
  $form['random'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort by random order.'),
    '#default_value' => (isset($form_state['conf']['random'])) ? $form_state['conf']['random'] : 0,
  );
  
  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_serendipity_serendipity_ting_object_related_content_type_edit_form_validate($form, &$form_state) {
  if (!isset($form_state['values']['selected_keys']) || empty($form_state['values']['selected_keys'])) {
    form_error($form['selected_keys'], t('Please specify some keys for the serendipity filter.'));
  }
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_serendipity_ting_object_related_content_type_edit_form_submit($form, &$form_state) {
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['selected_keys'] = !empty($form_state['values']['selected_keys']) ? $form_state['values']['selected_keys'] : FALSE;
}
