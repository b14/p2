<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  // TODO I do not understand how this plugin differs from
  // "Ding serendipity content". The title/description refers to nodes but the
  // contexts are largely the same. Only a ting_object is added.
  // Could this be made clearer through title, description and code comments?
  'title' => t('Ding serendipity content with nodes'),
  'description' => t('Display serendipity content of nodes based on the current entity.'),
  'admin info' => 'ding_serendipity_serendipity_node_admin_info',
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
function ding_serendipity_serendipity_node_admin_info($subtype, $conf, $context) {
  // TODO: This seems very similar to ding_serendipity_admin_info().
  // Could this be reused?
  $output = new stdClass();
  $output->title = t('Serendipity inspiration list');
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
function ding_serendipity_serendipity_node_content_type_render($subtype, $conf, $panel_args, $context) {
  $context_data = array();

  // Build a context that can be rendered by the serendipity plugins 

  // Transfer selected keys from panel settings
  // TODO This seems to be duplicated from
  // ding_serendipity_serendipity_content_type_render().
  if (isset($conf['selected_keys'])) {
    foreach ($conf['selected_keys'] as $key => $value) {
      $context_data[$key] = TRUE;
    }
  }

  // Transfer current node nid 
  if (!empty($context[0]->data)) {
    $context_data['node'] = $context[0]->data;
    $context_data['node_nid'] = $panel_args[0];
  }
  
  // Insert optional manual search term
  if (!empty($context[1]->data)) {
    $context_data['search_term'] = $context[1]->data;
  }
  
  // Insert term and tid
  if (!empty($context[2]->data)) {
    $context_data['taxonomy_term'] = $context[2]->data;
    $context_data['taxonomy_tid'] = $panel_args[0];
  }
  
  // Insert manually selected object ids
  if (!empty($context[3]->data)) {
    $context_data['ting_object'] = $context[2]->data;
    $context_data['ting_object_id'] = $panel_args[0];
  }

  // Complete the context array  
  $context_data += array(
    'view_mode' => isset($conf['view_mode']) ? $conf['view_mode'] : 'teaser',
    'bundle' => isset($conf['bundle']) ? $conf['bundle'] : 'teaser',
    'sort_weight' => isset($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => isset($conf['max']) ? $conf['max'] : 0,
    'min' => isset($conf['min']) ? $conf['min'] : 0,
    'random' => isset($conf['random']) ? $conf['random'] : FALSE,
  );

  // And render the array
  $content = ding_serendipity_render($context_data);

  $output = array();
  if (!empty($content)) {
    foreach ($content as $key => $item) {
      $item['#weight'] = $key;
      if (isset($item['#serendipity_info'])) {
        $item['serendipity_info'] = array(
          '#theme' => 'ding_serendipity_info',
          '#title' => t('Serendipity info') . ':',
          '#information' => $item['#serendipity_info'],
          '#weight' => 50,
        );
      }
      $output['content'][] = $item;
    }
  }

  $block = new stdClass();
  // TODO: No need to handle override_title here.
  $block->title = ($conf['override_title']) ? $conf['override_title_text'] : t('Serendipity content');
  $block->content = $output;
  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_serendipity_node_content_type_edit_form($form, &$form_state) {
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
  // TODO See comment in ding_serendipity_serendipity_content_type_edit_form
  // regarding keys.
  $form['selected_keys'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => array_unique($options),
    '#multiple' => TRUE,
    '#default_value' => (isset($form_state['conf']['selected_keys'])) ? $form_state['conf']['selected_keys'] : '',
    '#description' => t('Select any additional keys which apply to the serendipity display you wish to present.'),
  );
  
  // Get ting object entity info and extract the available view modes.
  $entity_info = entity_get_info('node');
  $view_mode_options = array();
  foreach ($entity_info['view modes'] as $key => $view_mode) {
    $view_mode_options[$key] = $view_mode['label'];
  }
  
  $form['view_mode'] = array(
    '#type' => 'select',
    '#title' => t('View mode'),
    '#options' => $view_mode_options,
    '#default_value' => (isset($form_state['conf']['view_mode'])) ? $form_state['conf']['view_mode'] : 'full',
    '#description' => t('Select the view mode which the content will display with.'),
  );
  
  $bundles = array();
  foreach ($entity_info['bundles'] as $key => $bundle) {
    $bundles[$key] = $bundle['label'];
  }
  
  $form['bundle'] = array(
    '#type' => 'select',
    '#title' => t('Bundle'),
    '#options' => $bundles,
    '#default_value' => (isset($form_state['conf']['bundle'])) ? $form_state['conf']['bundle'] : '',
    '#description' => t('Select the bundle to list serendipity content for.'),
  );

  // TODO Could the base form be refactored so we could avoid declaring
  // these fields again? The submit handler is already using
  // ding_serendipity_form_base_submit().
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
function ding_serendipity_serendipity_node_content_type_edit_form_validate($form, &$form_state) {
  // TODO Could this be handled using #required?
  if (!isset($form_state['values']['selected_keys']) || empty($form_state['values']['selected_keys'])) {
    form_error($form['selected_keys'], t('Please specify some keys for the serendipity filter.'));
  }
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_serendipity_node_content_type_edit_form_submit($form, &$form_state) {
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['selected_keys'] = !empty($form_state['values']['selected_keys']) ? $form_state['values']['selected_keys'] : FALSE;
  $form_state['conf']['view_mode'] = !empty($form_state['values']['view_mode']) ? $form_state['values']['view_mode'] : FALSE;
  $form_state['conf']['bundle'] = !empty($form_state['values']['bundle']) ? $form_state['values']['bundle'] : FALSE;
}
