CFLAGS = -g -Wall -Wextra --coverage

# ht_v1
## compile:
compile_ht_v1: ht_v1/hash_table.c ht_v1/hash_table_tests.c
	gcc $(CFLAGS) ht_v1/hash_table.c ht_v1/hash_table_tests.c -o ht_v1/ht_tests -lcunit

compile_it_ht_v1: ht_v1/hash_table.c ht_v1/hash_table_iterator_tests.c ht_v1/hash_table_iterator.c
	gcc $(CFLAGS) ht_v1/hash_table_iterator.c ht_v1/hash_table.c ht_v1/hash_table_iterator_tests.c -o ht_v1/ht_it_tests -lcunit

## compile and run CUnit tests:
test_ht_v1: compile_ht_v1
	ht_v1/ht_tests
	valgrind --leak-check=full ht_v1/ht_tests

test_it_ht_v1: compile_it_ht_v1
	ht_v1/ht_it_tests
	valgrind --leak-check=full ht_v1/ht_it_tests

# ht_v2
## compile:
compile_ht_v2: ht_v2/hash_table2.c ht_v2/hash_table_tests.c
	gcc $(CFLAGS) ht_v2/hash_table2.c ht_v2/hash_table_tests.c -o ht_v2/ht_tests -lcunit

compile_it_ht_v2: ht_v2/hash_table2.c ht_v2/hash_table_iterator2.c ht_v2/hash_table_iterator_tests.c
	gcc $(CFLAGS) ht_v2/hash_table2.c ht_v2/hash_table_iterator2.c ht_v2/hash_table_iterator_tests.c -o ht_v2/ht_it_tests -lcunit

## compile and run CUnit tests:
test_ht_v2: compile_ht_v2
	ht_v2/ht_tests
	valgrind --leak-check=full ht_v2/ht_tests

test_it_ht_v2: compile_it_ht_v2
	ht_v2/ht_it_tests
	valgrind --leak-check=full ht_v2/ht_it_tests

# ht_v3
## compile:
compile_ht_v3: ht_v3/hash_table3.c ht_v3/hash_table_tests.c
	gcc $(CFLAGS) ht_v3/hash_table3.c ht_v3/hash_table_tests.c -o ht_v3/ht_tests -lcunit

compile_it_ht_v3: ht_v3/hash_table3.c ht_v3/hash_table_iterator3.c ht_v3/hash_table_iterator_tests.c
	gcc $(CFLAGS) ht_v3/hash_table3.c ht_v3/hash_table_iterator3.c ht_v3/hash_table_iterator_tests.c -o ht_v3/ht_it_tests -lcunit

## compile and run CUnit tests:
test_ht_v3: compile_ht_v3
	ht_v3/ht_tests
	valgrind --leak-check=full ht_v3/ht_tests

test_it_ht_v3: compile_it_ht_v3
	ht_v3/ht_it_tests
	valgrind --leak-check=full ht_v3/ht_it_tests

## compile and run all hash-table-related CUnit tests:
test_all_ht: test_ht_v1 test_ht_v2 test_ht_v3

## compile and run all CUnits tests:
test_all: test_all_ht test_ll

# freq_count
## compile:
compile_fq_ht_v1: ht_v1/hash_table.c ht_v1/hash_table_iterator.c ht_v1/freq_count.c 
	gcc -g -O0 ht_v1/hash_table.c ht_v1/hash_table_iterator.c ht_v1/freq_count.c -o ht_v1/freq_count

compile_fq_ht_v2: ht_v2/hash_table2.c ht_v2/hash_table_iterator2.c ht_v2/freq_count.c
	gcc -g -O0 ht_v2/hash_table2.c ht_v2/hash_table_iterator2.c ht_v2/freq_count.c -o ht_v2/freq_count

compile_fq_ht_v3: ht_v3/hash_table3.c ht_v3/hash_table_iterator3.c ht_v3/freq_count.c
	gcc -g -O0 ht_v3/hash_table3.c ht_v3/hash_table_iterator3.c ht_v3/freq_count.c -o ht_v3/freq_count

## run with different textfiles as input:
### freq_count with ht_v1:
run_fq_ht_v1_small: compile_fq_ht_v1
	ht_v1/freq_count txt_files/small.txt
	valgrind --leak-check=full ht_v1/freq_count txt_files/small.txt

run_fq_ht_v1_1k: compile_fq_ht_v1
	ht_v1/freq_count txt_files/1k-long-words.txt
	valgrind --leak-check=full ht_v1/freq_count txt_files/1k-long-words.txt

run_fq_ht_v1_10k: compile_fq_ht_v1
	ht_v1/freq_count txt_files/10k-words.txt
	valgrind --leak-check=full ht_v1/freq_count txt_files/10k-words.txt

run_fq_ht_v1_16k: compile_fq_ht_v1
	ht_v1/freq_count txt_files/16k-words.txt
	valgrind --leak-check=full ht_v1/freq_count txt_files/16k-words.txt

### freq_count with ht_v2:
run_fq_ht_v2_small: compile_fq_ht_v2
	ht_v2/freq_count txt_files/small.txt
	valgrind --leak-check=full ht_v2/freq_count txt_files/small.txt

run_fq_ht_v2_1k: compile_fq_ht_v2
	ht_v2/freq_count txt_files/1k-long-words.txt
	valgrind --leak-check=full ht_v2/freq_count txt_files/1k-long-words.txt

run_fq_ht_v2_10k: compile_fq_ht_v2
	ht_v2/freq_count txt_files/10k-words.txt
	valgrind --leak-check=full ht_v2/freq_count txt_files/10k-words.txt

run_fq_ht_v2_16k: compile_fq_ht_v2
	ht_v2/freq_count txt_files/16k-words.txt
		valgrind --leak-check=full ht_v2/freq_count txt_files/16k-words.txt

### freq_count with ht_v3:
run_fq_ht_v3_small: compile_fq_ht_v3
	ht_v3/freq_count txt_files/small.txt
	valgrind --leak-check=full ht_v3/freq_count txt_files/small.txt

run_fq_ht_v3_1k: compile_fq_ht_v3
	ht_v3/freq_count txt_files/1k-long-words.txt
	valgrind --leak-check=full ht_v3/freq_count txt_files/1k-long-words.txt

run_fq_ht_v3_10k: compile_fq_ht_v3
	ht_v3/freq_count txt_files/10k-words.txt
	valgrind --leak-check=full ht_v3/freq_count txt_files/10k-words.txt

run_fq_ht_v3_16k: compile_fq_ht_v3
	ht_v3/freq_count txt_files/16k-words.txt
	valgrind --leak-check=full ht_v3/freq_count txt_files/16k-words.txt

# linked_list
## compile:
compile_ll: linked_list/linked_list.c linked_list/linked_list_tests.c linked_list/list_iterator.c
	gcc $(CFLAGS) linked_list/linked_list.c linked_list/linked_list_tests.c linked_list/list_iterator.c -o linked_list/ll_tests -lcunit

## compile and run CUnit tests:
test_ll: compile_ll
	linked_list/ll_tests
	valgrind --leak-check=full linked_list/ll_tests

## run coverage:
coverage_ll: linked_list/ll_tests-linked_list_tests.gcda
	gcov linked_list/ll_tests-linked_list.gcda

coverage_ht_v1: ht_v1/ht_tests-hash_table_tests.gcda
	gcov ht_v1/ht_tests-hash_table_tests.gcda

coverage_ht_v2: ht_v2/ht_tests-hash_table_tests.gcda
	gcov ht_v2/ht_tests-hash_table_tests.gcda

coverage_ht_v3: ht_v3/ht_tests-hash_table_tests.gcda
	gcov ht_v3/ht_tests-hash_table_tests.gcda

coverage_it_ht_v1: ht_v1/ht_it_tests-hash_table_iterator_tests.gcda
	gcov ht_v1/ht_it_tests-hash_table_iterator_tests.gcda

coverage_it_ht_v2: ht_v2/ht_it_tests-hash_table_iterator_tests.gcda
	gcov ht_v2/ht_it_tests-hash_table_iterator_tests.gcda

coverage_it_ht_v3: ht_v3/ht_it_tests-hash_table_iterator_tests.gcda
	gcov ht_v3/ht_it_tests-hash_table_iterator_tests.gcda

# clean compiled files:
# LÄGG TILL SÅ CLEAN KAN TA BORT ALLA COVERAGE O CALLGRIND FILER!
clean:
	rm -f ht_v1/ht_tests ht_v1/ht_it_tests ht_v1/freq_count ht_v2/ht_tests ht_v2/ht_it_tests ht_v2/freq_count ht_v3/ht_tests ht_v3/ht_it_tests ht_v3/freq_count linked_list/ll_tests
	find . \( -name "*.gcno" -o -name "*.gcda" -o -name "*.gcov" \) -delete
