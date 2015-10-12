<?php

/**
 * @file
 * This file contains all admin functions.
 */

/**
 * Admin form function.
 */
function islandora_html_snippet_admin($form, &$form_state) {

  module_load_include('inc', 'islandora', 'includes/solution_packs');
  $form += islandora_viewers_form('islandora_html_viewers', 'text/html');
  return system_settings_form($form);
}
