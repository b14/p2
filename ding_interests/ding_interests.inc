<?php

/**
 * @file
 * Ding interaction includes
 */

/**
 * To-do: doc here.
 */
function ding_interests_all_recommended_subjects() {
  // @TODO grupperet liste over fremhævede emneord

  return '<h1>' . t('The librarys selected subjects') . '</h1>' . theme('ding_interests_tree');
}
