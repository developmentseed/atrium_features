<?php
// $Id: drupal_web_test_case.php,v 1.2.2.3.2.37 2009/04/23 05:39:52 boombatower Exp $
// Core: Id: drupal_web_test_case.php,v 1.96 2009/04/22 09:57:10 dries Exp
/**
 * @file
 * Provide required modifications to Drupal 7 core DrupalWebTestCase in order
 * for it to function properly in Drupal 6.
 *
 * Copyright 2008-2009 by Jimmy Berry ("boombatower", http://drupal.org/user/214218)
 */

//require_once drupal_get_path('module', 'atrium_test') . '/atrium_test.d6.inc';
require_once drupal_get_path('module', 'simpletest') . '/drupal_web_test_case.php';

/**
 * Test case for typical Drupal tests.
 */
class AtriumWebTestCase extends DrupalWebTestCase {

  // This will allow us to test install in other languages
  var $install_locale = 'en';
  // And we may want to try more install profiles
  var $install_profile = 'atrium_installer';
  
  /**
   * Installs Atrium instead of Drupal
   * 
   * Generates a random database prefix, runs the install scripts on the
   * prefixed database and enable the specified modules. After installation
   * many caches are flushed and the internal browser is setup so that the
   * page requests will run on the new prefix. A temporary files directory
   * is created with the same name as the database prefix.
   *
   * @param ...
   *   List of modules to enable for the duration of the test.
   */
  protected function setUp() {
    global $db_prefix, $user, $language, $profile, $install_locale; // $language (Drupal 6).
    
    // Store necessary current values before switching to prefixed database.
    $this->originalPrefix = $db_prefix;
    $this->originalLanguage = clone $language;
    $clean_url_original = variable_get('clean_url', 0);

    // Must reset locale here, since schema calls t().  (Drupal 6)
    if (module_exists('locale')) {
      $language = (object) array('language' => 'en', 'name' => 'English', 'native' => 'English', 'direction' => 0, 'enabled' => 1, 'plurals' => 0, 'formula' => '', 'domain' => '', 'prefix' => '', 'weight' => 0, 'javascript' => '');
      locale(NULL, NULL, TRUE);
    }
    
    // Generate temporary prefixed database to ensure that tests have a clean starting point.
//    $db_prefix = Database::getConnection()->prefixTables('{simpletest' . mt_rand(1000, 1000000) . '}');
    $db_prefix = 'simpletest' . mt_rand(1000, 1000000);
    $install_locale = $this->install_locale;
    $profile = $this->install_profile;
    
//    include_once DRUPAL_ROOT . '/includes/install.inc';
    include_once './includes/install.inc';
    drupal_install_system();

//    $this->preloadRegistry();
    // Set up theme system for the maintenance page.
    // Otherwise we have trouble: https://ds.openatrium.com/dsi/node/18426#comment-38118
    // @todo simpletest module patch 
    drupal_maintenance_theme();
    
    // Add the specified modules to the list of modules in the default profile.
    $args = func_get_args();
//    $modules = array_unique(array_merge(drupal_get_profile_modules('default', 'en'), $args));

    $modules = array_unique(array_merge(drupal_verify_profile($this->install_profile, $this->install_locale), $args));
//    drupal_install_modules($modules, TRUE);
    drupal_install_modules($modules);

    // Because the schema is static cached, we need to flush
    // it between each run. If we don't, then it will contain
    // stale data for the previous run's database prefix and all
    // calls to it will fail.
    drupal_get_schema(NULL, TRUE);
    
    if ($this->install_profile == 'atrium_installer') {
      // Download and import translation if needed
      if ($this->install_locale != 'en') {
        $this->installLanguage($this->install_locale);
      }
      // Install more modules
      $modules = _atrium_installer_atrium_modules();
      drupal_install_modules($modules);
      
      // Configure intranet
      // $profile_tasks = $this->install_profile . '_profile_tasks';
      _atrium_installer_intranet_configure();
      _atrium_installer_intranet_configure_check();
      variable_set('atrium_install', 1);
      
    }
    else {
      // Rebuild caches. Partly done by Atrium installer
      actions_synchronize();
      menu_rebuild();
    }
    
    _drupal_flush_css_js();
    $this->refreshVariables();
    $this->checkPermissions(array(), TRUE);
    user_access(NULL, NULL, TRUE); // Drupal 6.

    // Log in with a clean $user.
    $this->originalUser = $user;
//    drupal_save_session(FALSE);
//    $user = user_load(1);
    session_save_session(FALSE);
    $user = user_load(array('uid' => 1));

    // Restore necessary variables.
    variable_set('install_profile', $this->install_profile);
    variable_set('install_task', 'profile-finished');
    variable_set('clean_url', $clean_url_original);
    variable_set('site_mail', 'simpletest@example.com');

    // Use temporary files directory with the same prefix as database.
    $this->originalFileDirectory = file_directory_path();
    variable_set('file_directory_path', file_directory_path() . '/' . $db_prefix);
    $directory = file_directory_path();
    // Create the files directory.
    file_check_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

    set_time_limit($this->timeLimit);
  }

  // Download and install language
  function installLanguage($langcode) {
    $this->addLanguage($langcode, TRUE, TRUE);

    if (module_exists('atrium_translate')) {
      module_load_install('atrium_translate');
      module_load_include('inc', 'l10n_update');
      $release = _atrium_translate_default_release($langcode);
      //$release = l10n_update_project_get_release('atrium', $langcode, ATRIUM_L10N_VERSION, ATRIUM_L10N_SERVER);
      if ($release && !empty($release['download_link'])) {
        $project = _l10n_update_build_project('atrium', ATRIUM_L10N_VERSION, ATRIUM_L10N_SERVER);
        if ($file = l10n_update_download_file($release['download_link'])) {
          l10n_update_import_file($file, $langcode);
          l10n_update_download_history($project, $release);
        }
      }
    }
  }

  /**
   * Adds a language
   * 
   * @param $langcode
   * @param $default
   *   Whether this is the default language
   * @param $load
   *   Whether to load available translations for that language
   */
  function addLanguage($langcode, $default = FALSE, $load = TRUE) {
    require_once './includes/locale.inc';
    // Enable installation language as default site language.
    locale_add_language($langcode, NULL, NULL, NULL, NULL, NULL, 1, $default);
    // Reset language list
    language_list('language', TRUE);
    // We may need to refresh default language
    drupal_init_language();
  }

  /**
   * Create a user with a given set of permissions. The permissions correspond to the
   * names given on the privileges page.
   *
   * @param $role
   *   Role for the user: admin, manager, user
   * @return
   *   A fully loaded user object with pass_raw property, or FALSE if account
   *   creation fails.
   */
  function atriumCreateUser($role = 'user') {
    // Get the rid from the role
    $roles = array(
      'user' => 2,
      'admin' => 3,
      'manager' => 4,
    );
    $rid = $roles[$role];
    // Create a user assigned to that role.
    $edit = array();
    $edit['name']   = $this->randomName();
    $edit['mail']   = $edit['name'] . '@example.com';
    $edit['roles']  = array($rid => $rid);
    $edit['pass']   = user_password();
    $edit['status'] = 1;

    $account = user_save('', $edit);

    $this->assertTrue(!empty($account->uid), t('User created with name %name, pass %pass and mail %mail', array('%name' => $edit['name'], '%pass' => $edit['pass'], '%mail' => $edit['mail'])), t('User login'));
    if (empty($account->uid)) {
      return FALSE;
    }

    // Add the raw password so that we can log in as this user.
    $account->pass_raw = $edit['pass'];
    return $account;
  }
  
  /**
   * Rewrite assertText function so it prints page when fails
   */
  function assertText($text, $message = '', $group = 'Other') {
    $result = $this->assertTextHelper($text, $message, $group, FALSE);
    if (!$result) {
      $this->printPage();
    }
    return $result;
  }

  /**
   * Rewrite assertUniqueText function so it prints page when fails
   */
  protected function assertUniqueText($text, $message = '', $group = 'Other') {
    $result = $this->assertUniqueTextHelper($text, $message, $group, TRUE);
    if (!$result) {
      $this->printPage();
    }
    return $result;
  }
 
  /**
   * Print out a variable for debugging
   */
  function printDebug($data, $title = '') {
    $string = is_array($data) || is_object($data) ? print_r($data, TRUE) : $data;
    $output = $title ? $title . ':' . $string : $string;
    //$this->assertTrue(TRUE, $output);
    $this->assertTrue(TRUE, $output, 'Debug');
  }
  /**
   * Debug dump object with some formatting
   */ 
  function printObject($object, $title = 'Object') {
    $output = $this->formatTable($object);
    $this->printDebug($output, $title);
  }
  
  /**
   * Print out current HTML page
   */
  function printPage() {
    $this->printDebug($this->drupalGetContent());
  }
  /**
   * Format object as table, recursive
   */
  function formatTable($object) {
    foreach ($object as $key => $value) {
      $rows[] = array(
        $key,
        is_array($value) || is_object($value) ? $this->formatTable($value) : $value,
      );
    }
    if (!empty($rows)) {
      return theme('table', array(), $rows);
    }
    else {
      return 'No properties';
    }
  }
  
  /**
   * Reset original language
   * 
   * If we don't do this after test tearDown, we get some errors when the system tries to translate
   * the test result messages, which is next step.
   */
  protected function tearDown() {
    global $language;
      
    parent::tearDown();
    $language = $this->originalLanguage;
  }
}
