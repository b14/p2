<?php

/**
 * @file
 * Information about list followers pane.
 */

$plugin = array(
  'title' => t('Ding list followers'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_followers_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_followers_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();
  $block->title = entity_label('ding_type', $list);
  $block->content = array('#theme' => 'ding_list_followers', '#list' => $list);

  return $block;
}
