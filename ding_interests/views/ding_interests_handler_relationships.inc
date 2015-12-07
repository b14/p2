<?php

/**
 * @file
 * Contains various relationship handlers.
 */

define('DING_INTERESTS_INTERESTS', 'interests');
define('DING_INTERESTS_NO_INTEREST', 'no interest');

/**
 * Base class for all our relationship classes.
 *
 * @ingroup views
 *
 * @todo: change class names, underscores are not allowed!
 */
abstract class Ding_interests_handler_relationship extends views_handler_relationship {

  /**
   * Every relationship has a 'flag' option.
   *
   * TODO: Why is flags mentioned here?
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['ding_interests'] = array('default' => NULL);
    $options['required'] = array('default' => 1);
    return $options;
  }

  /**
   * Make sure the flag exists.
   *
   * When importing views, or when deleting flags, inconsistent views may
   * result. This validator is called by Views before saving or previewing a
   * view.
   *
   * TODO: More references to flags...
   *
   * @todo: Visibility must be declared on method "validate".
   */
  function validate() {
    $errors = array();
    $tokens = array(
      '@relationship-name' => $this->ui_name() . ' ' . $this->admin_summary(),
      '@ding-interests-name' => $this->options['ding_interests'],
    );
    if (!$this->options['ding_interests']) {
      $errors[] = t('You must pick an interest type to use for the relationship "@relationship-name".', $tokens);
    }
    return $errors;
  }

  /**
   * To-do: doc here.
   */
  function get_ding_interests_type() {
    return isset($this->definition['list type']) ? $this->definition['list type'] : NULL;
  }

  /**
   * Returns the flag object.
   */
  function get_list() {
    // TODO: There are no flags in this module
    // Backward compatibility: There may exist old views on the system whose
    // 'flag' option isn't set. (This happens if the admin had skippped
    // clicking the 'Update' button.) When run, these views should behave as
    // if the first flag was selected.
    if (!isset($this->options['ding_interests'])) {
      $this->options['ding_interests'] = DING_INTERESTS_INTERESTS;
    }

    // Validation: Since validate() is called only when in Views's
    // administrative UI, we need to do validation at "run time" ourselves.
    if (($errors = $this->validate())) {
      foreach ($errors as $error) {
        drupal_set_message(check_plain($error), 'error');
      }
    }

    return ding_list_get_list($this->options['ding_interests']);
  }

  // @todo: It's logical that this class should also implement options_form(),
  // to show the flag selector, and query(), to filter on the flag.
}

/**
 * Specialized relationship handler associating flags and content.
 *
 * TODO Should this be lists - not flags?
 *
 * @ingroup views
 *
 * @todo: change class names, underscores are not allowed!
 */
class Ding_interests_handler_relationship_content extends ding_interests_handler_relationship {

  /**
   * To-do: doc here.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['user_scope'] = array('default' => 'current');
    return $options;
  }

  /**
   * To-do: doc here.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $content_type = $this->definition['list type'];
    // TODO Should this be selected list instead of flag?
    $form['label']['#description'] .= ' ' . t('The name of the selected flag makes a good label.');
    $form['ding_interests'] = array(
      '#type' => 'radios',
      '#title' => t('List type'),
      '#options' => array(
        DING_INTERESTS_INTERESTS => t('Interests'),
        DING_INTERESTS_NO_INTEREST => t('No interest'),
      ),
      '#default_value' => $this->options['ding_interests'],
      '#required' => TRUE,
    );

    $form['user_scope'] = array(
      '#type' => 'radios',
      '#title' => t('By'),
      '#options' => array(
        'current' => t('Current user'),
        'any' => t('Any user'),
      ),
      '#default_value' => $this->options['user_scope'],
    );

    $form['required']['#title'] = t('Include only content in list');
    $form['required']['#description'] = t('If checked, only content in the list will be included. Leave unchecked to include all content.');

    if (!$form['ding_interests']['#options']) {
      $form = array(
        'error' => array(
          '#markup' => '<p class="error form-item">' . t('No %type list exist.', array('%list' => $content_type)) . '</p>',
        ),
      );
      $form_state['no list exist'] = TRUE;
    }
  }

  /**
   * To-do: doc here.
   */
  function options_validate(&$form, &$form_state) {
    if (!empty($form_state['no list exist'])) {
      form_error($form, t('You must first select a list'));
    }
  }

  /**
   * To-do: doc here.
   */
  function admin_summary() {
    return $this->options['user_scope'] == 'current' ? t('by current user') : t('by any user');
  }

  /**
   * To-do: doc here.
   */
  function ui_name($short = FALSE) {
    // We put the bookmark name in the UI string to save space.
    return t('!group: !title', array('!group' => $this->definition['group'], '!title' => empty($this->options['ding_interests']) ? t('(Please select a list)') : $this->options['ding_interests']));
  }

  /**
   * Called to implement a relationship in a query.
   * @todo: Visibility must be declared on method "query".
   */
  function query() {
    // TODO This code seems to check for the ding_interests list 3 times
    // Is this really necessary?
    if (!($list = $this->get_list())) {
      return;
    }
    if ($this->options['user_scope'] == 'current') {
      $list = ding_list_get_list($this->options['ding_interests']);
    }
    else {
      $list = ding_list_get_list($this->options['ding_interests']);
    }
    $items = field_get_items('ding_type', $list, 'field_list_objects');
    if (empty($items)) {
      return;
    }
    $eids = array();
    foreach ($items as $key => $item) {
      $eids[] = $item['target_id'];
    }
    $this->definition['extra'][] = array(
      'field' => 'entity_id',
      'value' => $eids,
      'numeric' => TRUE,
    );
    parent::query();
  }
}

/**
 * Specialized relationship handler associating flags and users.
 *
 * @ingroup views
 *
 * @todo: change class names, underscores are not allowed!
 */
class Ding_interests_handler_relationship_user_content extends ding_interests_handler_relationship {

  /**
   * To-do: doc here.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['label']['#description'] .= ' ' . t('Including name of the selected flag helps identify this relationship.');

    // TODO This code uses the flag module and the flag module is also a
    // dependency but it seems odd that this class is the only class actually
    // using flags. Can this be right?
    $form['flag'] = flag_views_flag_config_form('radios', NULL, $this->options['flag']);
    $form['flag']['#title'] = t('Flagged');

    $form['required']['#title'] = t('Include only users who have flagged content.');
    $form['required']['#description'] = t('If checked, only users that have flagged any content with this flag will be included.');
  }

  /**
   * To-do: doc here.
   */
  function admin_summary() {
    return $this->options['flag'];
  }

  /**
   * Called to implement a relationship in a query.
   * @todo: Visibility must be declared on method "query".
   */
  function query() {
    if (!($flag = $this->get_flag())) {
      return;
    }

    $this->definition['extra'][] = array(
      'field' => 'fid',
      'value' => $flag->fid,
      'numeric' => TRUE,
    );
    parent::query();
  }
}
