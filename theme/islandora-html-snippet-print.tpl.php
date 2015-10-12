<?php

/**
 * @file
 * This is the template file for the print html snippet objects
 *
 * @TODO: Add documentation about this file and the available variables
 * $islandora_object - the object being displayed
 * $islandora_content - the content of the OBJ datastream.
 */
?>

<div class="islandora-html-snippet-object islandora" vocab="http://schema.org/" prefix="dcterms: http://purl.org/dc/terms/" typeof="Article">
  <div class="islandora-html-snippet-content-wrapper clearfix">
    <?php if (isset($islandora_content)): ?>
      <div class="islandora-html-snippet-print">
        <?php print $islandora_content; ?>
      </div>
    <?php endif; ?>
  </div>
</div>