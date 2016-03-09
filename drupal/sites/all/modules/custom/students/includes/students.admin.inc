<?php

/**
 * @file
 * Administration functions and forms for the Modulea module.
 */

/**
 * Form constructor for the modulea settings form.
 *
 * @ingroup forms
 * @see system_settings_form().
 */

function students_edit_settings($form, &$form_state) {
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
      '#value' =>  'Save',
      '#submit' =>  array('security_settings_form_submit'),
      //'#validate' =>  array('security_settings_form_validate'),
  );
   return $form;
}

/**
 * Implements security_settings_form_submit().
 */
function security_settings_form_submit($form, $form_state) {
  // Here u can insert Your custom form values into your custom table.
  db_insert('students')
    ->fields(array(
      'name' => $form_state['values']['name'], 
      'faculty' => $form_state['values']['faculty'],
      'gender' => $form_state['values']['gender']  
    ))->execute();
    drupal_set_message("successfully saved Security Settings"); 
}