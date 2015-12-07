<?php

/**
 * @file
 * Add list form pane.
 */

$plugin = array(
  'title' => t('Add list to list'),
  'description' => t('Add list to list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),

  'category' => t('Ding!'),
  'render callback' => 'ding_list_add_list_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_add_list_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;
  $list = $context->data;

  $block = new stdClass();
  $block->content = array();
  // TODO Why is there an access check required here?
  if ($list->uid != $user->uid) {
    $block->content = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->id, '@list');
  }

  return $block;
}
