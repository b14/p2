<?php

/**
 * TODO This file needs updating.
 * - The top docblock refers to serendipity
 * - hook_ding_interaction_info supports more return values shown by e.g. ding_entity_rating_loan_history_ding_interaction_info
 * - hook_ding_interaction_view supports more return values shown by e.g. ding_user_complete_ding_interaction_view().
 *
 * @file
 * This file contains the api functions which developers can use to
 * influence the serendipity results.
 */

/**
 * Hook which defines ding interaction content.
 *
 * @return array
 *   The returned array should contain the following values.
 *   - "title": The title to display when the interaction pane is display.
 *   - "active": Status of this interaction content.
 *     TRUE if this pane should be displayed, FALSE if not.
 */
function hook_ding_interaction_info() {
  return array(
    'title' => t('Title to display'),
    'active' => TRUE,
  );
}

/**
 * Hook which provides ding interaction content.
 *
 * @return string
 *   Return content which is ready to be displayed by the interaction pane.
 */
function hook_ding_interaction_view() {
  return $output;
}
