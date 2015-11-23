<?php

/**
 * @file
 * Add user to list form pane.
 */

$plugin = array(
  'title' => t('Add user to list'),
  'description' => t('Add user to list.'),
  'single' => TRUE,
  'content_types' => array('user'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_add_user_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_add_user_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;
  
  $account = $context->data;
  
  if ($account->uid == $user->uid) {
    return FALSE;
  }
  
  $block = new stdClass();
  $block->content = array();

  $id = $account->uid;
  if (module_exists('ting_openlist')) {
    $id = ting_openlist_user_identifier($account);
  }

  $block->content = drupal_get_form('ding_list_add_element_form', 'ding_list_user', $id, 'Add to @list');

  return $block;
}
