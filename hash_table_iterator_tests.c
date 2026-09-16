#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"

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

void test_iterating_empty(void){
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht); 
    ioopm_hash_table_iterator_advance(it);
    CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));
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
  // copy a line below and change the information'
  // || CU_add_test(my_test_suite, "test fresh entry", test_fresh_key) == NULL
  if ( CU_add_test(my_test_suite, "iterating over empty ht", test_iterating_empty) == NULL)
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
