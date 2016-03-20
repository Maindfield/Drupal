<?php

/**
 * @file
 * This is the form for adding students in the Students module.
 */

/**
 * Form constructor for the Students add form.
 *
 * @ingroup forms
 * @see students_edit_settings().
 */

function students_add_list($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Student Name'),
    '#size' => 60,
    '#required' => TRUE,
    '#maxlength' => 32,
  );
  $form['faculty'] = array(
    '#type' => 'textfield',
    '#title' => t('Faculty Number'),
    '#size' => 60,
    '#required' => TRUE,
    '#maxlength' => 8,
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['gender'] = array(
    '#type' => 'radios',
    '#title' => t('Student gender'),
    '#options' => array(
      'male' => t('Male'),
      'female' => t('Female'),
    ),
    '#default_value' => variable_get('gender', 'male'),
    '#description' => t('Select your gender'),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#submit' => array('students_add_form_submit'),
  );
  return $form;
}

function students_add_list_validate($form, &$form_state) {
  $pattern = "/[^a-zA-Z\- ']/";
  $name = $form_state['values']['name'];
  if (strlen(trim($name)) > 0 && preg_match($pattern, $name)) {
    form_set_error('name', t('Your name contains invalid characters. Only letters are allowed!'));
  }
}

/**
 * Implements students_settings_form_submit().
 */
function students_add_form_submit($form, $form_state) {
  db_insert('students')
      ->fields(array(
        'name' => $form_state['values']['name'],
        'faculty' => $form_state['values']['faculty'],
        'gender' => $form_state['values']['gender']
      ))->execute();
  drupal_set_message("Successfully saved students form");
}
