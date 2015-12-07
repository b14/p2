<?php

/**
 * @file
 * Ding interaction includes
 */

/**
 * To-do: doc here.
 */
function ding_interests_all_recommended_subjects() {
  // @TODO grupperet liste over fremh�vede emneord
  // TODO: This is a single function in a generic inc file. Is this necessary?

  return '<h1>' . t('The librarys selected subjects') . '</h1>' . theme('ding_interests_tree');
}
