<?php

/**
 * @file
 * This file contains all theme and preprocess functions
 */

/**
 * Prepares variables for islandora-html-snippet templates.
 *
 * Default template: islandora-html-snippet.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - islandora_object: An AbstractObject from Islandora.
 */
function islandora_html_snippet_preprocess_islandora_html_snippet(&$variables) {
  drupal_add_js('misc/form.js'); // ??
  drupal_add_js('misc/collapse.js'); // ??
  $islandora_object = $variables['islandora_object'];
  $repository = $islandora_object->repository;
  module_load_include('inc', 'islandora', 'includes/datastream');
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/metadata');

  // We should eventually remove the DC object and dc_array code as it only
  // exists to not break legacy implementations.
  try {
    if (isset($islandora_object['DC']) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $islandora_object['DC'])) {
      $dc = $islandora_object['DC']->content;
      $dc_object = DublinCore::importFromXMLString($dc);
    }
  }
  catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
  $variables['islandora_dublin_core'] = isset($dc_object) ? $dc_object : NULL;
  $variables['dc_array'] = isset($dc_object) ? $dc_object->asArray() : array();
  $variables['islandora_object_label'] = $islandora_object->label;
  $variables['theme_hook_suggestions'][] = 'islandora_html_snippet__' . str_replace(':', '_', $islandora_object->id);
  $variables['parent_collections'] = islandora_get_parents_from_rels_ext($islandora_object);
  $variables['metadata'] = islandora_retrieve_metadata_markup($islandora_object);
  $variables['description'] = islandora_retrieve_description_markup($islandora_object);

  if (isset($islandora_object['OBJ'])) {
    $datastream = $islandora_object['OBJ'];
    $variables['islandora_content'] = $datastream->content;
  }
}

/**
 * Prepares variables for islandora-html-snippet-print templates.
 *
 * Default template: islandora-html-snippet-print.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - islandora_object: An AbstractObject from Islandora.
 */
function islandora_html_snippet_preprocess_islandora_html_snippet_print(&$variables) {
  $islandora_object = $variables['islandora_object'];
  if (isset($islandora_object['OBJ'])) {
    $variables['islandora_content'] = $islandora_object['OBJ']->getContent();
    $variables['islandora_preview_img'] = theme('image', $params);
  }
}
