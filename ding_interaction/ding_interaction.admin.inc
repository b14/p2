<?php

/**
 * @file
 * This file contains the api functions which developers can use to
 * influence the interaction results.
 */

/**
 * Get an overview of the current registered interaction functions and keys.
 */
function ding_interaction_admin_overview($form, &$form_state) {
  $form['ding_interaction_callbacks'] = array(
    '#type' => 'tableselect',
    '#header' => array(
      'title' => t('Title'),
      'weight' => t('Weight'),
      'settings' => t('Settings'),
    ),
    '#options' => array(),
    '#default_value' => variable_get('ding_interaction_callbacks', array()),
  );

  $weights = variable_get('ding_interaction_weights', array());
  $form['ding_interaction_callbacks']['#process'][] = 'ding_interaction_process_options';
  $info = ding_interaction_available_content(TRUE);
  foreach ($info as $key => $value) {
    $weight = isset($value['weight']) ? $value['weight'] : 1;
    $form['ding_interaction_callbacks']['#options'][$key] = array(
      'title' => $value['title'],
      'weight' => array(
        'data' => array(
          '#type' => 'select',
          '#title' => '',
          '#options' => range(0, 5),
          '#value' => (isset($weights[$key])) ? array($weights[$key]) : array($weight),
          '#description' => t('Choose a weight for this interaction function.'),
          '#name' => 'ding_interaction_weights[' . $key . ']',
        ),
      ),
      'settings' => '',
    );
    if (!empty($value['settings'])) {
      $form['ding_interaction_callbacks']['#options'][$key]['settings'] = array(
        'data' => l(
          t('Settings'),
          'admin/config/ding/interaction/key_overview/' . $value['settings'],
          array('query' => array('destination' => 'admin/config/ding/interaction/key_overview'))
        ),
      );
    }
  }
  $form['ding_interaction_weights'] = array(
    '#type' => 'value',
  );

  $form['ding_interaction_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ding interaction settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['ding_interaction_settings']['ding_interaction_page_count'] = array(
    '#type' => 'select',
    '#title' => t('Page count'),
    '#description' => t('Set the amount of page views between ding interaction displays'),
    '#options' => range(1, 20),
    '#default_value' => variable_get('ding_interaction_page_count', 5),
    '#required' => TRUE,
  );  
  
  return system_settings_form($form);
}

/**
 * Process admin form options.
 */
function ding_interaction_process_options($element) {
  if ($element['#multiple']) {
    $value = is_array($element['#value']) ? $element['#value'] : array();
  }
  else {
    // Advanced selection behavior makes no sense for radios.
    $element['#js_select'] = FALSE;
  }

  $element['#tree'] = TRUE;

  if (count($element['#options']) > 0) {
    if (!isset($element['#default_value']) || $element['#default_value'] === 0) {
      $element['#default_value'] = array();
    }

    // Create a checkbox or radio for each item in #options in such a way that
    // the value of the tableselect element behaves as if it had been of type
    // checkboxes or radios.
    foreach ($element['#options'] as $key => $choice) {
      // Do not overwrite manually created children.
      if (!isset($element[$key])) {
        if ($element['#multiple']) {
          $title = '';
          if (!empty($element['#options'][$key]['title']['data']['#title'])) {
            $title = t('Update @title', array(
                '@title' => $element['#options'][$key]['title']['data']['#title'],
              ));
          }
          $element[$key] = array(
            '#type' => 'checkbox',
            '#title' => $title,
            '#title_display' => 'invisible',
            '#return_value' => $key,
            '#default_value' => isset($value[$key]) ? $key : NULL,
            '#attributes' => $element['#attributes'],
          );
        }
        else {
          // Generate the parents as the autogenerator does, so we will have a
          // unique id for each radio button.
          $parents_for_id = array_merge($element['#parents'], array($key));
          $element[$key] = array(
            '#type' => 'radio',
            '#title' => '',
            '#return_value' => $key,
            '#default_value' => ($element['#default_value'] == $key) ? $key : NULL,
            '#attributes' => $element['#attributes'],
            '#parents' => $element['#parents'],
            '#id' => drupal_html_id('edit-' . implode('-', $parents_for_id)),
            '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
          );
        }
        if (isset($element['#options'][$key]['#weight'])) {
          $element[$key]['#weight'] = $element['#options'][$key]['#weight'];
        }
      }
    }
  }
  else {
    $element['#value'] = array();
  }
  return $element;
}

