<?php

/**
 * @file
 * Admin related functionality.
 */

/**
 * The admin settings form.
 */
function ting_openlist_settings_form($form, &$form_state) {
  // Default settings.
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Openlist settings'),
  );
  
  $form['settings']['ting_openlist_wsdl'] = array(
    '#type' => 'textfield',
    '#title' => t('URI of the WSDL file'),
    '#description' => t("The client doesn't support non-WSDL mode, so this is required."),
    '#default_value' => variable_get('ting_openlist_wsdl', ''),
    '#required' => TRUE,
  );
  
  $form['settings']['ting_library_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Library code'),
    '#description' => '',
    '#default_value' => variable_get('ting_library_code', ''),
    '#required' => TRUE,
  );
  
  $form['settings']['ting_openlist_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Openlist prefix'),
    // TODO Please add a description here. Without any formal documentation
    // its it the best we can get.
    '#description' => '',
    '#default_value' => variable_get('ting_openlist_prefix', uniqid()),
    '#required' => TRUE,
  );

  // Caching settings.
  $form['caching'] = array(
    '#type' => 'fieldset',
    '#title' => t('Openlist WSDL caching'),
    '#description' => t('These settings only affect the SoapClients created for openlist, and will not interfere with other SoapClients on your site.'),
  );
  
  $form['caching']['ting_openlist_wsdl_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable WSDL caching'),
    '#description' => '',
    '#default_value' => variable_get('ting_openlist_wsdl_cache', FALSE),
  );
  
  $form['caching']['ting_openlist_wsdl_cache_ttl'] = array(
    '#type' => 'textfield',
    '#title' => t('WSDL time to live'),
    '#description' => t("How long should the WSDL be cached in seconds."),
    '#default_value' => variable_get('ting_openlist_wsdl_cache_ttl', ''),
  );

  // Debugging settings.
  $form['debugging'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debugging settings'),
    '#description' => t('Do not enable these settings in a production environment.<br />Even without any debugging on, openlist will log actual errors'),
  );
  
  $form['debugging']['ting_openlist_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#description' => t('Log requests send to the openlist service.'),
    '#default_value' => variable_get('ting_openlist_log', FALSE),
  );

  // TODO Why is there a need for two levels of debugging? Other similar modules
  // in this project only have one.
  $form['debugging']['ting_openlist_log_details'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable detailed logging'),
    '#description' => t('If logging, this will log more details, but the log messages can get big and confusing.'),
    '#default_value' => variable_get('ting_openlist_log_details', FALSE),
  );
  
  $form['debugging']['ting_openlist_developer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Developer'),
    '#description' => t('Send the developer cookie to the service.'),
    '#default_value' => variable_get('ting_openlist_developer', FALSE),
  );

  return system_settings_form($form);
}
