<?php

//require_once drupal_get_path('module', 'atrium_test') . '/atrium_test.d6.inc';
require_once drupal_get_path('module', 'simpletest') . '/drupal_web_test_case.php';

/**
 * Test case for typical Drupal tests.
 */
class AtriumWebTestCase extends DrupalWebTestCase {

  // This will allow us to test install in other languages
  var $install_locale = 'en';
  // And we may want to try more install profiles
  var $install_profile = 'openatrium';

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

    if ($this->install_profile == 'openatrium') {
      // Download and import translation if needed
      if ($this->install_locale != 'en') {
        $this->installLanguage($this->install_locale);
      }
      // Install more modules
      $modules = _openatrium_atrium_modules();
      drupal_install_modules($modules);

      // Configure intranet
      // $profile_tasks = $this->install_profile . '_profile_tasks';
      _openatrium_intranet_configure();
      _openatrium_intranet_configure_check();
      variable_set('atrium_install', 1);

      // Clear views cache before rebuilding menu tree. Requires patch
      // [patch_here] to Views, as new modules have been included and
      // default views need to be re-detected.
      module_exists('views') ? views_get_all_views(TRUE) : TRUE;
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
   * Create basic conditions for testing.
   */
  function atriumBasic() {
    // Create public and private groups.
    $this->drupalLogin($this->atriumCreateUser('administrator'));
    $this->atriumGroups = array();
    $group_types = array(
      'public' => 'atrium_groups_public',
      'private' => 'atrium_groups_private',
    );
    foreach ($group_types as $key => $preset) {
      $this->atriumGroups[$key] = $this->atriumCreateGroup($preset);
    }

    // Create a user for each role.
    $this->atriumUsers = array();
    $user_roles = array('user', 'manager', 'administrator');
    foreach ($user_roles as $role) {
      $this->atriumUsers[$role] = $this->atriumCreateUser($role, $this->atriumGroups);
    }
  }

  /**
   * Create a group with the given preset
   */
  function atriumCreateGroup($preset = 'atrium_groups_private') {
    $group = new stdClass();
    $group->type = 'group';
    $group->title = $this->randomName(8);
    $group->description = $this->randomName(32);
    $group->path = strtolower($this->randomName(8, ''));
    $group->preset = $preset;
    $this->drupalGet('node/add/group');
    $edit = array(
      'title' => $group->title,
      'og_description' => $group->description,
      'purl[value]' => $group->path,
      'spaces_preset_og' => $group->preset,
    );
    $this->drupalPost('node/add/group', $edit, t('Save'));
    $group->nid = db_result(db_query("SELECT id FROM {purl} WHERE value = '%s'", $group->path));
    return $group;
  }

  /**
   * Create group content
   */
  function atriumCreateGroupContent($group, $type, $edit = array()) {
    $node->type = $type;
    $node->title = $this->randomName(8);
    $node->body = $this->randomName(32);
    $edit += array(
      'title' => $node->title,
      'body' => $node->body,
    );
    $path = "$group->path/node/add/" . str_replace('_', '-', $type);
    $this->drupalGet($path);
    $this->drupalPost($path, $edit, t('Save'));
    // Get nid from database
    $node->nid = db_result(db_query("SELECT nid FROM {node} WHERE title = '%s'", $node->title));
    // Reload page and assert title
    $this->drupalGet("$group->path/node/$node->nid");
    $this->assertText($node->title);
    return $node;
  }

  /**
   * Create a user with a given set of permissions. The permissions correspond to the
   * names given on the privileges page.
   *
   * @param $role
   *   Role for the user: administrator, manager, user
   * @param $groups
   *   Optional: An array of group nids or group node objects to which the newly
   *   created account should be a member of.
   * @return
   *   A fully loaded user object with pass_raw property, or FALSE if account
   *   creation fails.
   */
  function atriumCreateUser($role = 'user', $groups = array()) {
    // Abbreviate 'authenticated user' to just 'user'.
    $role = $role === 'user' ? 'authenticated user' : $role;
    $rid = db_result(db_query("SELECT rid FROM {role} WHERE name = '%s'", $role));

    if ($rid) {
      // Create a user assigned to that role.
      $edit = array();
      $edit['name']   = $this->randomName();
      $edit['mail']   = $edit['name'] . '@example.com';
      $edit['roles']  = array($rid => $rid);
      $edit['pass']   = user_password();
      $edit['status'] = 1;

      $account = user_save('', $edit);

      // Add groups.
      if (!empty($account->uid) && !empty($groups)) {
        foreach ($groups as $value) {
          $gid = is_object($value) && !empty($value->nid) ? $value->nid : $value;
          og_save_subscription($gid, $account->uid, array('is_active' => TRUE));
        }
        // Reload user account with OG associations.
        og_get_subscriptions($account->uid, 1, TRUE); // Reset static cache.
        $account = user_load($account->uid);
      }

      $this->assertTrue(!empty($account->uid), t('User created with name %name, pass %pass and mail %mail', array('%name' => $edit['name'], '%pass' => $edit['pass'], '%mail' => $edit['mail'])), t('User login'));
      if (!empty($account->uid)) {
        // Add the raw password so that we can log in as this user.
        $account->pass_raw = $edit['pass'];
        return $account;
      }
    }
    return FALSE;
  }

  /**
   * Enable the specified feature.
   *
   * @param $feature
   *   A feature's name, e.g. 'atrium_blog'
   * @param $space_type
   *   Optional: The space type that this feature should be enabled for.
   * @param $space_id
   *   Optional: If the space type was specified, the ID of the space.
   */
  function atriumEnableFeature($feature, $space_type = NULL, $space_id = NULL) {
    if (isset($space_type, $space_id)) {
      $space = spaces_load($space_type, $space_id);
      $features = $space->controllers->variable->get('spaces_features');
      $features[$feature] = TRUE;
      $space->controllers->variable->set('spaces_features', $features);
    }
    else if (!isset($space_type)) {
      $features = variable_get('spaces_features', array());
      $features[$feature] = TRUE;
      variable_set('spaces_features', $features);
    }
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

  /**
   * Override of refreshVariables().
   */
  protected function refreshVariables() {
    parent::refreshVariables();
    // If strongarm is enabled, we need to reload its variable bootstrap
    // for this page load.
    // @TODO: Do we need to do this for Spaces too?
    if (module_exists('strongarm')) {
      strongarm_set_conf(TRUE);
      $_GET['q'] = strongarm_language_strip($_REQUEST['q']);
      drupal_init_path();
    }
  }
}
