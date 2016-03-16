<?php

/**
 * @file
 * This is the form for adding students in the Students module.
 */

/**
 * Form constructor for the Students settings form.
 *
 * @ingroup forms
 * @see students_edit_settings().
 */
function main_table() {
  // Table header
  $header = array(
    // Column 1
    'id' => array(
      'data' => 'id',
      'class' => 'col-id',
    ),
    // Column 2
    'name' => array(
      'data' => t('Name'),
      'class' => 'col-name',
    ),
    // Column 3
    'faculty' => array(
      'data' => t('Faculty Number'),
      'class' => 'col-number',
    ),
    // Column 3
    'gender' => array(
      'data' => t('Students gender'),
      'class' => 'col-gender',
    ),
    // Column 4
    'edit' => array(
      'data' => l(t('edit student'), 'students'),
      'class' => 'col-edit',
    ),
    // Column 5
    'delete' => array(
      'data' => t('Delete'),
      'class' => 'col-delete',
    ),
  );
  // Table rows
  $query = db_select('students', 's')
      ->fields('s', array('name', 'gender', 'faculty',))
      ->addTag('node_access');
  $result = $query->execute();

  $header = array('Name', 'Gender', 'Faculty', 'Edit', 'Delete');

  $rows = array();
  foreach ($result as $record) {
    $rows[] = array(
      $record->name,
      $record->gender,
      $record->faculty);
  }
  
  return array('#markup' => theme('table', array(
      'header' => $header,
      'rows' => $rows)));
}
