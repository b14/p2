<?php

/**
 * @file
 * Ding user handling module.
 */

/**
 * Implements hook_rules_action_info().
 */
function ding_user_consent_rules_action_info() {
  return array(
    'ding_user_consent_user_created_info' => array(
      'label' => t('Present User Consent info'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('New user'),
        ),
      ),
      'group' => t('Ding'),
    ),
  );
}

/**
 * Action function for the ding_user_consent_user_created_info function.
 *
 * @param object $account
 *   The newly created user to present the user consent information to.
 */
function ding_user_consent_user_created_info($account) {
  if(variable_get('user_consent_activate')) {
    $title = variable_get('loan_history_store_title_first_time', '');
    $description = variable_get('loan_history_store_description_first_time', '');
    drupal_set_message(check_plain($title));
    drupal_set_message($description['value']);
  }
}
