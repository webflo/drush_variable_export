<?php
// $Id$

/**
 * @file
 *  TextMate Commadns for Drush.
 */

/**
 * Implementation of hook_drush_command().
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing each command.
 */
function drush_variable_export_drush_command() {
  $items = array();

  $items['variable-export'] = array(
    'description' => "Export variables",
    'arguments' => array(
      'name' => 'A string to filter the variables by. Only variables beginning with the string will be listed.',
    ),
    'options' => array(
      'contains' => 'list all variables which contains [name]',
      'pipe' => 'return a list',
    ),
    'examples' => array(
      'drush vexport ubercart',
      'drush vexport --contains node',
      'drush variable-export --pipe i18n'
    ),
    'aliases' => array('vexport'),
  );
  
  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function drush_variable_export_drush_help($section) {
  switch ($section) {
    case 'drush:variable-export':
      return dt("Export variables in various formats.");
  }
}

/**
 * Drush variable-export command callback.
 */
function drush_drush_variable_export_variable_export() {
  global $conf;
  $found = FALSE;
  
  $keys = array_keys($conf);
  if (!drush_get_option('contains')) {
    if ($args = func_get_args()) {
      $keys = preg_grep("/^{$args[0]}/", $keys);
    }
  } else {
    if ($args = func_get_args()) {
      $keys = preg_grep("/{$args[0]}/", $keys);
    }
  }
  
  if (!empty($keys)) {
    $found = TRUE;
    if (drush_get_option('pipe')) {
      drush_print_pipe(implode("\n", $keys));
    } else {
      array_walk($keys, '_drush_drush_variable_export_features');
    }
  }
  if (!$found) {
    return drush_set_error('No matching variable found.');
  }
}

function _drush_drush_variable_export_features($name) {
  drush_print('features[variable][] ="'. $name . '"');
}