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
  'title' => t('Ding interaction pane'),
  'description' => t('Displays interaction to the user'),
  'admin info' => 'ding_interaction_admin_info',
  'single' => TRUE,
  'edit form' => 'ding_interaction_content_type_edit_form',
  'render callback' => 'ding_interaction_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration interaction in panels.
 */
function ding_interaction_admin_info($subtype, $conf, $context) {
  $output = new stdClass();
  $output->title = t('Serendipity inspiration list');
  $output->content = t('Serendipity content. Page view interval: @count', array('@count' => $conf['count'])) . '<br/>';
  return $output;
}

/**
 * Implements hook_content_type_render().
 */
function ding_interaction_content_type_render($subtype, $conf, $panel_args, $context) {
  // Only show on front if activated.
  // TODO Could this be handled using visibility rules? That would make the
  // content type more resuable.
  if(drupal_is_front_page() && !variable_get('ding_frontpage_serendipity') && variable_get('ding_frontpage_promoter') != 'serendipity') {
    return;
  }

  // Include the CTools tools that we need.
  ctools_include('ajax');
  // TODO Could this be added to #attached and a render array returned?
  drupal_add_js(drupal_get_path('module', 'ding_interaction') . '/js/ding_interaction.js');
  drupal_add_css(drupal_get_path('module', 'ding_interaction') . '/css/ding_interaction.css');
  $data = ding_interaction_content(NULL, $conf['count']);
  
  $output = new stdClass();
  if ($data) {
    // See previous comment about closing panes without AJAX.
    $close_btn = ctools_ajax_text_button(' ' . t('Close'), 'ding_interaction/nojs/hide', t('Close pane'), 'close-btn');

    $help_text = empty($data['more_title']) ? "" : l(
      $data['more_title'],
      $data['more_url'],
      array(
        "attributes" => array(
          "class" => "view-all-link",
        ),
      )
    );

    $output->title = '';
    $output->content = '<h2>' . $data['title'] . '</h2><div class="ding-interaction-pane">' . $data['data'] . $close_btn . $help_text . '</div>';
    $output->css_class = isset($data['css_class']) ? $data['css_class'] : "default-interaction";
  }
  return $output;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_interaction_content_type_edit_form($form, &$form_state) {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Count'),
    '#default_value' => (isset($form_state['conf']['count'])) ? $form_state['conf']['count'] : '5',
    '#description' => t('How many page views should there be between showing this pane.'),
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_interaction_content_type_edit_form_validate($form, &$form_state) {

}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_interaction_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['count'] = !empty($form_state['values']['count']) ? $form_state['values']['count'] : '5';
}
