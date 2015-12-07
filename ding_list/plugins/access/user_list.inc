<?php

/**
 * @file
 * Plugin to provide access control based on user lists.
 */

$plugin = array(
  'title' => t("User: list"),
  'description' => t('Control access by to user lists.'),
  'callback' => 'ding_list_user_list_ctools_access_check',
  // TODO: Is default needed here?
  'default' => 1,
  'settings form' => 'ding_list_user_list_ctools_access_settings',
  'summary' => 'ding_list_user_list_ctools_access_summary',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
    new ctools_context_required(t('Dinglist'), 'ding_type'),
  ),
  'defaults' => array(
    'visibility_settings' => 'view',
  ),
);

/**
 * Settings form for the 'by perm' access plugin.
 */
function ding_list_user_list_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['visibility_settings'] = array(
    // TODO: Nitpicking but I think radios would be better for usability.
    '#type' => 'select',
    '#title' => t('Visibility settings for the list'),
    '#options' => array(
      // TODO This should use proper definitions of permissions for keys - e.g.
      // constants.
      'view' => t('View'),
      'edit' => t('Edit'),
      'owner' => t('Owner'),
    ),
    '#default_value' => $conf['visibility_settings'],
  );

  return $form;
}

/**
 * Check for access.
 */
function ding_list_user_list_ctools_access_check($conf, $context) {
  if (empty($context)) {
    return FALSE;
  }

  $account = $context[0]->data;
  $list = $context[1]->data;

  $result = ding_list_user_has_access($list, $conf['visibility_settings'], $account);

  return $result;
}

/**
 * Provide a summary description based upon the checked roles.
 */
function ding_list_user_list_ctools_access_summary($conf, $context) {
  // TODO Please include the list in the summary
  return t('@identifier @setting', array('@identifier' => $context[0]->identifier, '@setting' => $conf['visibility_settings']));
}
