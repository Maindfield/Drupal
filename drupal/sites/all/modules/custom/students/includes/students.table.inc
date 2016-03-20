<?php

/**
 * Implements students_list().
 */
function students_list() {
  $header = array('ID', 'Name', 'Gender', 'Faculty Number', 'Action');
  $results = db_query("SELECT id,name,gender,faculty FROM {students}");
  $empty = 'No student data are added yet';
  $rows = array();
  foreach ($results as $key) {
    $id = $key->id;
    $name = $key->name;
    $gender = $key->gender;
    $faculty = $key->faculty;
    $rows[] = array($id, $name, $gender, $faculty,
      "<a href='students/edit/{$key->id}'>" . t('Edit') .
      "</a> | <a href='students/delete/{$key->id}'>" .
      t('Delete') . "</a>");
  }
  return array('#markup' => theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'empty' => $empty)));
}

function students_delete_confirm($form, &$form_state, $students_code) {
  $form['_student'] = array(
    '#type' => 'value',
    '#value' => $students_code,);

  return confirm_form($form, t('Are you sure you want to delete Student with ID ' . $students_code), isset($_GET['destination']) ? $_GET['destination'] : "students", t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

function students_delete_confirm_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  if ($form_state['values']['confirm']) {
    $students = $form_state['values']['_student'];
    $result = db_query("DELETE FROM {students} where id='{$students}'");
    drupal_set_message(t('Student has been deleted successfully.'));
  }
  drupal_goto("students");
}

function students_edit_confirm($form, &$form_state, $students_code) {
  $id = '';
  $name = '';
  $gender = '';
  $faculty = '';
  $results = db_query("SELECT id,name,gender,faculty FROM {students} WHERE id='{$students_code}'");
  foreach ($results as $key) {
    $id = $key->id;
    $name = $key->name;
    $gender = $key->gender;
    $faculty = $key->faculty;
  }
  $form = array();
  $form['id'] = array(
    '#title' => t('ID'),
    '#type' => 'hidden',
    '#default_value' => $id,
  );
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => $name,
    '#element_validate' => array('students_edit_list_validate')
  );
  $form['gender'] = array(
    '#title' => t('Gender'),
    '#type' => 'radios',
    '#options' => array(
      'male' => 'Male',
      'female' => 'Female'
    ),
    '#default_value' => $gender,
  );
  $form['faculty'] = array(
    '#title' => t('Faculty Number'),
    '#type' => 'textfield',
    '#maxlength' => 8,
    '#default_value' => $faculty,
    '#element_validate' => array('element_validate_integer_positive')
  );

  return confirm_form($form, t(''), isset($_GET['destination']) ? $_GET['destination'] : "students", t(''), t('Edit'), t('Cancel'));
}

function students_edit_list_validate($form, &$form_state) {
  $pattern = "/[^a-zA-Z\- ']/";
  $name = $form_state['values']['name'];
  if (strlen(trim($name)) > 0 && preg_match($pattern, $name)) {
    form_set_error('name', t('Your name contains invalid characters. Only letters are allowed!'));
  }
}

function students_edit_confirm_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  if ($form_state['values']['confirm']) {
    $id = $form_state['values']['id'];
    $name = $form_state['values']['name'];
    $gender = $form_state['values']['gender'];
    $faculty = $form_state['values']['faculty'];

    $rs = db_query("UPDATE  {students} SET id= '$id', gender= '$gender', name= '$name', faculty = '$faculty' WHERE  id='{$id}'");
    drupal_set_message(t('Student has been updated successfully.'));
  }
  drupal_goto("students");
}
