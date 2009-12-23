<?php 
// *Id*
/**
 * @file
 *   Atrium translate common variables
 */

// Atrium version. This should be defined somewhere else
define('ATRIUM_L10N_VERSION', '6.x-1.0');
// This module is specific for Atrium package so we already know some data
define('ATRIUM_L10N_SERVER', 'https://translate.openatrium.com');
// This is the default folder to place translation files
define('ATRIUM_L10N_DIRECTORY', 'translations');
// Location of the l10n_update module we need to know to check requirements
// define('ATRIUM_L10N_UPDATE', './profiles/atrium_translation/modules/l10n_update');

// Temporary variables that help with installation
define('ATRIUM_L10N_UPDATE_PATH', '/l10n/status/project/atrium');

/**
 * Get defatult Atrium projects
 */
function _atrium_translate_default_projects() {
  $projects['drupal'] = array(
    'name' => 'drupal',
    'title' => 'Drupal core',
    'info' => array(
      'version' => VERSION,
      'translate status url' => ATRIUM_L10N_SERVER,
    ),
  );
  $projects['atrium_contrib'] = array(
    'name' => 'atrium_contrib',
    'title' => 'Atrium contrib',
    'info' => array(
      'version' => ATRIUM_L10N_VERSION,
      'translate status url' => ATRIUM_L10N_SERVER,
    ),
  );
  $projects['atrium_custom'] = array(
    'name' => 'atrium_custom',
    'title' => 'Atrium custom',
    'info' => array(
      'version' => ATRIUM_L10N_VERSION,
      'translate status url' => ATRIUM_L10N_SERVER,
    ),
  );
  $projects['atrium_features'] = array(
    'name' => 'atrium_features',
    'title' => 'Atrium features',
    'info' => array(
      'version' => ATRIUM_L10N_VERSION,
      'translate status url' => ATRIUM_L10N_SERVER,
    ),
  );
  return $projects;
}