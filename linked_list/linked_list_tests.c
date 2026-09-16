#include <CUnit/Basic.h>
#include "linked_list.h"

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test_empty(void) {
  ioopm_list_t *listan = ioopm_list_create();
  CU_ASSERT_EQUAL(NULL, listan->first);
  CU_ASSERT_EQUAL(NULL, listan->last);
  CU_ASSERT_EQUAL(listan->size, 0);
  ioopm_list_destroy(listan);
}

void test_singleton(void) {
  ioopm_list_t *listan = ioopm_list_create();
  ioopm_list_append(listan, (ioopm_element_t) 67);
  CU_ASSERT_EQUAL(listan->first->head.integer, 67);
  CU_ASSERT_EQUAL(listan->last->head.integer, 67);
  CU_ASSERT_EQUAL(listan->size, 1);
  ioopm_list_destroy(listan);
}

void test_3_appends(void) {
  ioopm_list_t *listan = ioopm_list_create();
  ioopm_list_append(listan, (ioopm_element_t) 67);
  ioopm_list_append(listan, (ioopm_element_t) 68);
  ioopm_list_append(listan, (ioopm_element_t) 69);

  CU_ASSERT_EQUAL(listan->first->head.integer, 67);
  CU_ASSERT_EQUAL(listan->last->head.integer, 69);
  CU_ASSERT_EQUAL(listan->size, 3);
  CU_ASSERT_EQUAL(listan->first->tail->head.integer, 68);

  ioopm_list_destroy(listan);
}

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "Empty list", test_empty) == NULL) 
    || (CU_add_test(my_test_suite, "Singleton append", test_singleton) == NULL) 
    || (CU_add_test(my_test_suite, "3 entry list append", test_3_appends) == NULL)

  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_NORMAL);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
