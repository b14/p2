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
  'title' => t('Ding notifications top menu'),
  'description' => t('Displays status notifications to the user'),
  'admin info' => 'ding_notifications_admin_info',
  'single' => TRUE,
  'edit form' => 'ding_notifications_content_type_edit_form',
  'render callback' => 'ding_notifications_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration interaction in panels.
 */
function ding_notifications_admin_info($subtype, $conf, $context) {
  $output = new stdClass();
  $output->title = t('User status list');
  $output->content = t('Notifications displayed: @status', array('@status' => implode(', ', $conf['top_menu_items']))) . '<br/>';
  return $output;
}

/**
 * Implements hook_content_type_render().
 */
function ding_notifications_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;

  // TODO: Page manager already have a caching system. Why not use that?
  // If we do not use that then avoiding tying the cache name to the function
  // name would be good - especially if we need to access these cache entries
  // outside of this function.
  $cache_key = __FUNCTION__ . ':' . md5($user->uid . serialize($conf));
  $cache = cache_get($cache_key);

  // TODO What is going on here with the arg() checking?
  if (isset($cache->expire) && $cache->expire > time() && arg(0) != 'user') {
    return $cache->data;
  }

  if (!ding_user_is_provider_user($user)) {
    $output = new stdClass();
    $output->title = t('User status');
    $output->content = '';

    cache_set($cache_key, $output, 'cache', time() + (60 * 5));
    return $output;
  }
  $content = array();
  $default = array(1, 2, 3, 4);
  $defaults = (isset($conf['top_menu_items'])) ? $conf['top_menu_items'] : $default;
  $uri = entity_uri('user', $user);

  if (module_exists('ding_message')) {
    $num_notifications = ding_message_get_message_count();
    $classes = 'icon-bell notifications-lists';
    if (!$num_notifications) {
      $classes .= ' empty';
    }
    $link_text_t = sprintf('<div data-count="%d" class="notifications-count">%d</div>', $num_notifications, $num_notifications);
    $attr = array(
      'html' => TRUE,
      'attributes' => array(
        'title' => t('Notifications: @count', array('@count' => $num_notifications)),
        'class' => array($classes),
      ),
    );
    $content[] = l($link_text_t, 'user', $attr);
  }

  if (isset($defaults['ready_to_pickup'])) {
    // TODO Why not use ding_provider_invoke here?
    $ready_to_pickup = ding_provider_invoke_page('reservation', 'list', $user, DING_RESERVATION_READY);
    $ready_to_pickup_count = count($ready_to_pickup);
    // TODO Is any styling missing here? I cannot spont any declarations of
    // notifications-* classes.
    $classes = 'icon-folder-open notifications-pickup';
    if (!$ready_to_pickup_count) {
      $classes .= ' empty';
    }
    // TODO
    $ready_to_pickup_count_t = sprintf('<div data-count="%d" class="notifications-count">%d</div>', $ready_to_pickup_count, $ready_to_pickup_count);
    $attr = array(
      'html' => TRUE,
      'attributes' => array(
        'title' => t('Ready to Pickup: @count', array('@count' => $ready_to_pickup_count)),
        'class' => array($classes),
      ),
    );
    $content[] = l($ready_to_pickup_count_t, $uri['path'] . '/status/reservations', $attr);
  }

  if (isset($defaults['dept'])) {
    // TODO Why not use ding_provider_invoke here?
    $debts = ding_provider_invoke_page('debt', 'list', $user);
    $dept_count = count($debts);
    $dept_count_t = sprintf('<div data-count="%d" class="notifications-count">%d</div>', $dept_count, $dept_count);
    $classes = 'icon-legal notifications-fines';
    if (!$dept_count) {
      $classes .= ' empty';
    }
    $attr = array(
      'html' => TRUE,
      'attributes' => array(
        'title' => t('Fines: @count', array('@count' => $dept_count)),
        'class' => array($classes),
      ),
    );
    $content[] = l($dept_count_t, $uri['path'] . '/status/debts', $attr);
  }

  $output = new stdClass();
  if (!empty($content)) {
    $output->title = t('User status');
    $variables = array(
      'items' => $content,
      'title' => '',
      'type' => 'ul',
      'attributes' => array(),
    );
    $output->content = theme_item_list($variables);
  }

  cache_set($cache_key, $output, 'cache', time() + (60 * 5));
  return $output;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_notifications_content_type_edit_form($form, &$form_state) {
  // TODO The options are duplicated. We can do better than that.
  // TODO The form defines 4 options but only two seems to be implemented.
  // Why is that?
  $options = array(
    'loans' => t('Loans'),
    'ready_to_pickup' => t('Ready to pickup'),
    'reservations' => t('Reservations'),
    'dept' => t('Dept'),
  );

  $form['top_menu_items'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select which elements to display'),
    '#default_value' => (isset($form_state['conf']['top_menu_items'])) ? $form_state['conf']['top_menu_items'] : $options,
    '#options' => $options,
  );
  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_notifications_content_type_edit_form_validate($form, &$form_state) {

}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_notifications_content_type_edit_form_submit($form, &$form_state) {
  $options = array(
    'loans' => t('Loans'),
    'ready_to_pickup' => t('Ready to pickup'),
    'reservations' => t('Reservations'),
    'dept' => t('Dept'),
  );

  $form_state['conf']['top_menu_items'] = !empty($form_state['values']['top_menu_items']) ? $form_state['values']['top_menu_items'] : $options;
}
