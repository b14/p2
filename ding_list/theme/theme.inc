<?php
/**
 * @file
 * Theme and preprocess files
 */

/**
 * Add an entity to the list.
 * TODO What is this function doing here? It does not seem theme related
 * and I cannot find anywhere it is being called.
 */
function ding_list_add_to_list($lid, $content) {
  // @todo validate input
  $list = entity_load('ding_type', array($lid));
  entity_save('ding_type', $list);
}

/**
 * Ding list message theme.
 */
function theme_ding_list_message($variables) {
  return '<div class="ding-list-message">' . $variables['message'] . '</div>';
}

/**
 * Ding list permission description theme.
 */
function theme_ding_list_permission_description($variables) {
  return '<div id="status-description">' . $variables['message'] . '</div>';
}

/**
 * Default preprocess.
 */
function template_preprocess_ding_list_list(&$variables) {
  if ($variables['toggler'] === TRUE) {
    // TODO If this is really unused then please uncomment.
    // $variables['toggler'] = array('#theme' => 'ding_list_mode_toggler');
  }

  if ($variables['sortable'] !== FALSE) {
    $variables['classes_array'][] = 'sort-enabled';
  }
}

/**
 * Add button.
 */
function template_preprocess_ding_list_add_button(&$variables) {
  // TODO: Could this be added to #attached in a render array?
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_js(drupal_get_path('module', 'ding_list') . '/js/ding-list-add-button.js');
  drupal_add_css(drupal_get_path('module', 'ding_list') . '/css/ding-list-add-button.css');

  $variables['buttons'] = array(
    '#theme' => 'links',
    '#links' => array(),
    '#attributes' => array(
      'class' => array('buttons'),
    ),
  );

  $variables['single_link'] = FALSE;

  if ($variables['options'] === FALSE) {
    $options = ding_list_get_add_to_list_data($variables['type'], $variables['value'], $variables['value_title']);
  }
  else {
    $options = $variables['options'];
  }

  if ($variables['type'] == 'ting_object') {
    $options[] = array(
      'custom' => array(
        'title' => t('Add to new list'),
        'href' => 'list/create',
        'attributes' => array(
          'class' => array(),
        ),
        'query' => array('at' => $variables['type'], 'av' => $variables['value']),
      ),
    );
  }
  foreach ($options as $option) {
    if (!isset($option['custom'])) {
      $l = array(
        'title' => $option['title'],
        'href' => 'dinglist/attach/' . $option['type'] . '/' . $option['list_id'] . '/' . $option['value'],
        'attributes' => array(
          'class' => array('use-ajax', drupal_html_class($option['type'])),
        ),
      );

      if (!empty($option['value_title'])) {
        $l['query'] = array('title' => $option['value_title']);
      }
    }
    else {
      $l = $option['custom'];
    }

    $variables['buttons']['#links'][] = $l;
    if (isset($option['#single_link'])) {
      $variables['single_link'] = TRUE;
    }
  }

  // Translating this late, enables customized titles.
  if(isset($options[0]['title'])) {
    $variables['title'] = t($variables['title'], array('@list' => $options[0]['title']));
  }
}

/**
 * Ding list followers preprocessor.
 */
function template_preprocess_ding_list_followers(&$variables) {
  $list = $variables['list'];
  $variables['count'] = ding_list_get_list_followers_count($list);
  
  $variables['note'] = ding_base_get_value('ding_type', $list, 'field_notes');
  if ($variables['note'] === FALSE) {
    $list_information = ding_list_list_operations();
    $list_type = ding_base_get_value('ding_type', $list, 'field_list_type');
    if (isset($list_information[$list_type])) {
      $list_information = $list_information[$list_type];
      if (isset($list_information['_data']['description'])) {
        $variables['note'] = $list_information['_data']['description'];
      }
    }
  }
  
  $variables['no_objects'] = empty($list->field_list_objects);
}

/**
 * Ding list followers theme.
 */
function theme_ding_list_followers($variables) {
  $out = format_plural($variables['count'], '1 user following this list', '@count users following this list');
  
  if ($variables['note'] !== FALSE) {
    $out .= '<div class="ding-list-note">' . $variables['note'] . '</div>';
  }

  // TODO Outputting the elements seem odd compared when the function is
  // dealing with followers.
  if ($variables['no_objects']) {
    $out .= '<div class="ding-list-no-elements">' . t('No elements in this list.') . '</div>';
  }
  
  return $out;
}


/**
 * Ding list lists preprocessor.
 */
function template_preprocess_ding_list_lists(&$variables) {
  // TODO: If it is intentional that this function should do nothing then at
  // least add a comment explaining why it is defined.
}

/**
 * Ding list lists theme.
 */
function theme_ding_list_lists($variables) {
  $out = '';
  
  foreach ($variables['groups'] as $group_name => $group) {
    $rows = array();

    // TODO: Why is sorting done here. It seems it might as well be done
    // directly where group is defined before passing it to the theme function.
    if (isset($group['sort']) && function_exists($group['sort'])) {
      uasort($group['lists'], $group['sort']);
    }

    foreach ($group['lists'] as $lists) {
      foreach ($lists as $list) {
        // Remove the #list reference.
        // TODO: Why?
        unset($list['#list']);
        $rows[] = $list;
      }
    }
    
    $out .= theme_item_list(array(
      'items' => $rows,
      'title' => $group['title'],
      'type' => 'ul',
      'attributes' => array(),
    ));
  }

  // Footer links.
  $out .= theme_item_list(array(
    'items' => array(
      l(t("> Mark all notifications as read"), "ding_message/purge_user_messages"),
      l(t("> Create new list"), "list/create"),
    ),
    'title' => "",
    'type' => 'ul',
    'attributes' => array('class' => array('bottom-links')),
  ));

  // TODO: Should this class be prefixed with ding?
  return '<div class="user-lists">' . $out . '</div>';
}
