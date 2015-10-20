<?php

/**
 * @file
 * Handles the uploading of the image file.
 */

/**
 * Defines a form to edit HTML in a wysiwyg.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 *
 * @return array
 *   The drupal form definition.
 */
function islandora_html_snippet_html_edit_form(array $form, array &$form_state, $islandora_object = NULL) {
  // Determine if we're editing an existing object.
  if ($islandora_object) {
    $editing = TRUE;
  }
  else {
    $editing = FALSE;
  }

  // Pass the islandora object, if editing, into $form_state,
  // And fill default values.
  if (!isset($form_state['islandora']['objects'])) {
    if ($islandora_object) {
      $form_state['islandora']['objects'] = array($islandora_object);
      if ($islandora_object['OBJ']) {
        $form_state['values']['content'] = $islandora_object['OBJ']->content;
      }
    }
  }
  $form =  array(
    'content' => array(
      '#title' => t('Content'),
      '#type' => 'text_format',
      '#description' => t('Enter your content.'),
      '#default_value' => isset($form_state['values']['content']) ? $form_state['values']['content'] : NULL,
    ),
  );

  // Add submit handler only if editing existing object.
  if ($editing) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t("Submit"),
    );
  }
  return $form;
}

/**
 * Submit handler, adds uploaded file to ingest object.
 *
 * @param array $form
 *   The drupal form.
 * @param array $form_state
 *   The drupal form state.
 */
function islandora_html_snippet_html_edit_form_submit(array $form, array &$form_state) {
  module_load_include('inc', 'islandora', 'includes/ingest.form');
  $object = islandora_ingest_form_get_object($form_state);
  if ($form_state['values']['content']) {
    if (empty($object['OBJ'])) {
      $ds = $object->constructDatastream('OBJ', 'M');
      $object->ingestDatastream($ds);
    }
    else {
      $ds = $object['OBJ'];
    }
    $content = $form_state['values']['content']['value'];
    $ds->content = $content;
    if ($ds->label != 'HTML Content') {
      $ds->label = 'HTML Content';
    }
    if ($ds->mimetype != 'text/html') {
      $ds->mimetype = 'text/html';
    }
  }
  $form_state['redirect'] = "islandora/object/{$object->id}";

}
