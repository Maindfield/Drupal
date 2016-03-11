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
function students_theme_table($variables) {
  // Table header
  $table_header = array(
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
  );
  // Table rows
  $sql = "SELECT id, name, faculty, gender FROM {students}";
  $res = db_query($sql);
  $table_rows = array();
  while ($row = db_fetch_object($res)) {
    $table_rows[] = array(
      'id' => array(
        // Column 1
        'id' => array(
          'data' => $row->id,
          'class' => 'col-id',
        ),
        // Column 2
        'name' => array(
          'data' => l($row->name, 'students/' . $row->id),
          'class' => 'col-name',
        ),
        // Column 3
        'faculty' => array(
          'data' => l($row->faculty, 'students/' . $row->faculty),
          'class' => 'col-faculty',
        ),
      ),
      // Row attributes
      'id' => 'students-row-' . $row->id,
      'class' => 'students-row',
    );
  }
  // Format and print out the table.
  return theme('table', array(
    'header' => $table_header,
    'rows' => $table_rows,
    'id' => 'table-articles',
    'class' => 'students',
  ));
}
