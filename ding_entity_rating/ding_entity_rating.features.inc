<?php

/**
 * @file
 * ding_interests.features.inc
 */

// TODO: As far as I can tell this module does not define any features.
// Why are these methods defined in a ding_entity_rating.features.inc file?
// They also seem to refer to a range of apis which are not used by this module
// e.g. field_groups, strongarm, views etc.
// Can the entire file be deleted?

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_entity_rating_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_entity_rating_views_api() {
  return array(
    'api' => 3,
    'path' => drupal_get_path('module', 'ding_interests/views'),
  );
}
