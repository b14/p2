<?php

/**
 * @file
 * Add search to list button.
 */

$plugin = array(
  'title' => t('Add search to list'),
  'description' => t('Add search query to list.'),
  'single' => TRUE,
  // 'content_types' => array('list'),
  'content_types' => array('ting_search'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_search_query_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_search_query_content_type_render($subtype, $conf, $panel_args, $context) {
  $keywords = $context->data;

  $facets = drupal_http_build_query(drupal_get_query_parameters());

  if (!empty($facets)) {
    $keywords .= '?' . $facets;
  }

  $block = new stdClass();

  $title = $context->data;

  // TODO Why is there a need to do this processing of the facet string?
  // It seems like we are jumping through hooks to get
  // drupal_get_query_parameters() again?
  $facet_list = explode('&', $facets);
  if (!empty($facet_list)) {
    foreach ($facet_list as & $facet) {
      $facet = urldecode($facet);
      $facet = substr($facet, strpos($facet, ':') + 1);
    }

    $title .= ', ' . implode(', ', $facet_list);
  }

  $block->content = array(
    '#theme' => 'ding_list_add_button',
    '#type' => 'search_query',
    '#value' => $keywords,
    '#value_title' => $title,
  );

  return $block;
}
