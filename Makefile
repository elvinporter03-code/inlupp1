CFLAGS = -g -Wall -Wextra --coverage

.PHONY: all compile_ht compile_it_ht compile_ll \
        test_ht test_ht_it test_ll clean

all: compile_ht compile_it_ht compile_ll \
     test_ht test_ht_it test_ll \
	 coverage_ll coverage_ht coverage_ht_it

compile_ht: hash_table.c hash_table_tests.c
	gcc $(CFLAGS) hash_table.c hash_table_tests.c -o ht_tests -lcunit

compile_it_ht: hash_table.c hash_table_iterator_tests.c hash_table_iterator.c
	gcc $(CFLAGS) hash_table_iterator.c hash_table.c hash_table_iterator_tests.c -o ht_it_tests -lcunit

compile_ll: linked_list/linked_list.c linked_list/linked_list_tests.c linked_list/list_iterator.c
	gcc $(CFLAGS) linked_list/linked_list.c linked_list/linked_list_tests.c linked_list/list_iterator.c -o ll_tests -lcunit

test_ht: compile_ht
	./ht_tests
	valgrind --leak-check=full ./ht_tests

test_ht_it: compile_it_ht
	./ht_it_tests
	valgrind --leak-check=full ./ht_it_tests

test_ll: compile_ll
	./ll_tests
	valgrind --leak-check=full ./ll_tests

coverage_ll: ll_tests-linked_list_tests.gcda
	gcov ll_tests-linked_list.gcda

coverage_ht: ht_tests-hash_table_tests.gcda
	gcov ht_tests-hash_table_tests.gcda

coverage_ht_it: ht_it_tests-hash_table_iterator_tests.gcda
	gcov ht_it_tests-hash_table_iterator_tests.gcda

clean:
	rm -f ht_tests ht_it_tests ll_tests