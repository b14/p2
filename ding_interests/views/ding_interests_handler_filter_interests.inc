<?php

/**
 * @file
 * Contains the flagged content filter handler.
 */

/**
 * Handler to filter for content that has not been flagged.
 *
 * @ingroup views
 *
 * @todo: change class names, underscores are not allowed!
 */
class Ding_interests_handler_filter_interests extends views_handler_filter_boolean_operator {

  /**
   * Provide the default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['value'] = array('default' => 1);
    return $options;
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['value']['#type'] = 'radios';
    $form['value']['#title'] = t('Status');
    $form['value']['#options'] = array(
      1 => t('In interests'),
      0 => t('Not in interests'),
      'All' => t('All')
    );
    $form['value']['#default_value'] = empty($this->options['value']) ? '1' : $this->options['value'];
    $form['value']['#description'] = '<p>' . t('This filter is only needed if the relationship used has the "Include only content in lists" option <strong>unchecked</strong>.') . '</p><p>' . t('By choosing <em>Not in list</em>, it is possible to create a list of content that has not been added to one of the interests lists.') . '</p>';
  }

  /**
   * Override query
   */
  public function query() {
    $join = new views_join();
    $join->table = 'eck_ding_type';
    $join->field = 'id';
    $join->left_table = $this->query->table_queue['field_data_field_status']['alias'];
    $join->left_field = 'entity_id';
    $join->type = 'left';
    $this->query->add_relationship('ding_interest_user', $join, 'taxonomy_term_data');
    $operator = $this->value ? 'IS NOT' : 'IS';
    $this->query->add_where($this->options['group'], 'ding_interest_user.uid', NULL, $operator . ' NULL');
  }
}
