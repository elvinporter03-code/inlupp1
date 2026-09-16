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
    CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));
    ioopm_hash_table_iterator_destroy(it);
    ioopm_hash_table_destroy_iter(ht);
}

void test_iterating_singleton(void){
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *key = "A*";
  int value = 123;
  ioopm_hash_table_insert(ht, key, value);
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht); 
  int result = ioopm_hash_table_iterator_current_value(it);
  CU_ASSERT_EQUAL(result, 123);

  CU_ASSERT_FALSE(ioopm_hash_table_iterator_at_end(it));
  CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it), value);
  ioopm_hash_table_iterator_advance(it);
  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy_iter(ht);
}

void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy_iter(ht);
  CU_ASSERT_EQUAL(iteration_count, 3);
}
void test_iterator_several_unique() {
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};
  bool visited[3] = {false, false, false};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  while(!ioopm_hash_table_iterator_at_end(it)) {
    int current_value = ioopm_hash_table_iterator_current_value(it);
    char *current_key = ioopm_hash_table_iterator_current_key(it);
    
    for (int i = 0; i < 3; i++) {
      if (strcmp(current_key, keys[i]) == 0 &&
          current_value == values[i])
      {
          // This is one of the entries we inserted
          CU_ASSERT_FALSE(visited[i]);

          visited[i] = true;
      }
    }
    ioopm_hash_table_iterator_advance(it);
  }

  for (int i = 0; i < 3; i++) {
    CU_ASSERT_TRUE(visited[i])
  }
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy_iter(ht);

}


void test_iterator_several_unique_same_bucket()
{
  char *keys[3] = {"A*", "B-", "C0"};
  int values[3] = {0, 1, 2};
  bool visited[3] = {false, false, false};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    for(int i = 0; i < 3; i++){
      if(ioopm_hash_table_iterator_current_value(it) == values[i]){
        if(!visited[i]){
          visited[i] = true;
        } else{
          CU_ASSERT(1);
        }
      }
    }
    ioopm_hash_table_iterator_advance(it);
    iteration_count++;
  }
  
  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy_iter(ht); 
  CU_ASSERT_EQUAL(iteration_count, 3);
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
  if ( CU_add_test(my_test_suite, "iterating over empty ht", test_iterating_empty) == NULL
   ||  CU_add_test(my_test_suite, "iterating over singleton ht", test_iterating_singleton) == NULL
   ||  CU_add_test(my_test_suite, "iterating over ht with several entries", test_iterator_several_entries) == NULL
   || CU_add_test(my_test_suite, "iterating over ht with several entries and checking if theyre unique", test_iterator_several_unique) == NULL
   || CU_add_test(my_test_suite, "iterating over ht with several entries in same bucket and checking if theyre unique", test_iterator_several_unique_same_bucket) == NULL)
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
