<?php 
/**
 * @file
 *  Some helper functions to run tests without patching Drupal core
 */

/**
 * Error reporting level: display no errors.
 */
define('ERROR_REPORTING_HIDE', 0);

/**
 * Error reporting level: display errors and warnings.
 */
define('ERROR_REPORTING_DISPLAY_SOME', 1);

/**
 * Error reporting level: display all messages.
 */
define('ERROR_REPORTING_DISPLAY_ALL', 2);

/**
 * Custom PHP error handler.
 *
 * @param $error_level
 *   The level of the error raised.
 * @param $message
 *   The error message.
 * @param $filename
 *   The filename that the error was raised in.
 * @param $line
 *   The line number the error was raised at.
 * @param $context
 *   An array that points to the active symbol table at the point the error occurred.
 */
function _drupal_error_handler($error_level, $message, $filename, $line, $context) {
  if ($error_level & error_reporting()) {
    // All these constants are documented at http://php.net/manual/en/errorfunc.constants.php
    $types = array(
      E_ERROR => 'Error',
      E_WARNING => 'Warning',
      E_PARSE => 'Parse error',
      E_NOTICE => 'Notice',
      E_CORE_ERROR => 'Core error',
      E_CORE_WARNING => 'Core warning',
      E_COMPILE_ERROR => 'Compile error',
      E_COMPILE_WARNING => 'Compile warning',
      E_USER_ERROR => 'User error',
      E_USER_WARNING => 'User warning',
      E_USER_NOTICE => 'User notice',
      E_STRICT => 'Strict warning',
      E_RECOVERABLE_ERROR => 'Recoverable fatal error'
    );
    $caller = _drupal_get_last_caller(debug_backtrace());

    // We treat recoverable errors as fatal.
    _drupal_log_error(array(
      '%type' => isset($types[$error_level]) ? $types[$error_level] : 'Unknown error',
      '%message' => $message,
      '%function' => $caller['function'],
      '%file' => $caller['file'],
      '%line' => $caller['line'],
    ), $error_level == E_RECOVERABLE_ERROR);
  }
}

/**
 * Custom PHP exception handler.
 *
 * Uncaught exceptions are those not enclosed in a try/catch block. They are
 * always fatal: the execution of the script will stop as soon as the exception
 * handler exits.
 *
 * @param $exception
 *   The exception object that was thrown.
 */
function _drupal_exception_handler($exception) {
  // Log the message to the watchdog and return an error page to the user.
  _drupal_log_error(_drupal_decode_exception($exception), TRUE);
}

/**
 * Decode an exception, especially to retrive the correct caller.
 *
 * @param $exception
 *   The exception object that was thrown.
 * @return An error in the format expected by _drupal_log_error().
 */
function _drupal_decode_exception($exception) {
  $message = $exception->getMessage();

  $backtrace = $exception->getTrace();
  // Add the line throwing the exception to the backtrace.
  array_unshift($backtrace, array('line' => $exception->getLine(), 'file' => $exception->getFile()));

  // For PDOException errors, we try to return the initial caller,
  // skipping internal functions of the database layer.
  if ($exception instanceof PDOException) {
    // The first element in the stack is the call, the second element gives us the caller.
    // We skip calls that occurred in one of the classes of the database layer
    // or in one of its global functions.
    $db_functions = array('db_query', 'pager_query', 'db_query_range', 'db_query_temporary', 'update_sql');
    while (!empty($backtrace[1]) && ($caller = $backtrace[1]) &&
        ((isset($caller['class']) && (strpos($caller['class'], 'Query') !== FALSE || strpos($caller['class'], 'Database') !== FALSE || strpos($caller['class'], 'PDO') !== FALSE)) ||
        in_array($caller['function'], $db_functions))) {
      // We remove that call.
      array_shift($backtrace);
    }
    if (isset($exception->query_string, $exception->args)) {
      $message .= ": " . $exception->query_string . "; " . print_r($exception->args, TRUE);
    }
  }
  $caller = _drupal_get_last_caller($backtrace);

  return array(
    '%type' => get_class($exception),
    '%message' => $message,
    '%function' => $caller['function'],
    '%file' => $caller['file'],
    '%line' => $caller['line'],
  );
}

/**
 * Gets the last caller from a backtrace.
 *
 * @param $backtrace
 *   A standard PHP backtrace.
 * @return
 *   An associative array with keys 'file', 'line' and 'function'.
 */
function _drupal_get_last_caller($backtrace) {
  // Errors that occur inside PHP internal functions do not generate
  // information about file and line. Ignore black listed functions.
  $blacklist = array('debug');
  while (($backtrace && !isset($backtrace[0]['line'])) ||
         (isset($backtrace[1]['function']) && in_array($backtrace[1]['function'], $blacklist))) {
    array_shift($backtrace);
  }

  // The first trace is the call itself.
  // It gives us the line and the file of the last call.
  $call = $backtrace[0];

  // The second call give us the function where the call originated.
  if (isset($backtrace[1])) {
    if (isset($backtrace[1]['class'])) {
      $call['function'] = $backtrace[1]['class'] . $backtrace[1]['type'] . $backtrace[1]['function'] . '()';
    }
    else {
      $call['function'] = $backtrace[1]['function'] . '()';
    }
  }
  else {
    $call['function'] = 'main()';
  }
  return $call;
}

/**
 * Debug function used for outputting debug information.
 *
 * The debug information is passed on to trigger_error() after being converted
 * to a string using _drupal_debug_message().
 *
 * @param $data
 *   Data to be output.
 * @param $label
 *   Label to prefix the data.
 * @param $print_r
 *   Flag to switch between print_r() and var_export() for data conversion to
 *   string. Set $print_r to TRUE when dealing with a recursive data structure
 *   as var_export() will generate an error.
 */
function debug($data, $label = NULL, $print_r = FALSE) {
  // Print $data contents to string.
  $string = $print_r ? print_r($data, TRUE) : var_export($data, TRUE);
  trigger_error(trim($label ? "$label: $string" : $string));
}