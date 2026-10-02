# Hashtable and linked lists

## Running the tests
    ### Do everything below:

    #### Compiling the testfiles and sourcefiles:
    make compile_ht_v1
    make compile_ht_v2
    make compile_ht_v3
    make compile_it_ht_v1
    make compile_it_ht_v2
    make compile_it_ht_v3
    make compile_ll

    #### Running the tests:
    make test_ht_v1
    make test_ht_v2
    make test_ht_v3
    make test_it_ht_v1
    make test_it_ht_v2
    make test_it_ht_v3
    make test_ll

    #### Running all CUnit tests at once:
    make test_all

        ##### All hash-table-related:
            make test_all_ht
    
    #### This also produces a gcda file which you can run in order to check the test coverage:
    make coverage_ll
    make coverage_ht
    make coverage_ht_it

    or open the gcov file to see exactly which lines dont get covered.

    #### We also have a wordcounting program that counts the frequency of each word in a txt document:
    gcc freq_count.c hash_table_iterator.c hash_table.c -o counter
    ./counter {name of your txtfile}.txt

# Design decisions:
    Everything about our implementation is pretty standard, maybe with the exception of our linked list iterator starting over from the first element after iterating through the entire list. 
    The implementation is rather foolproof and shouldnt be too easy to crash, as it returns False or nothing whenever the user uses it wrong.
    Some functions that are crashable contain a precondition in the header and the source file.

    The linked list follows this structure:
    The list element which contains pointers to the first and last element of the list for quick access, and a constant unsigned int which holds the size of the list. It gets updated dynamically whenever the user adds or removes an element from the list.
    Each listnode consists of a head which contains the value of the node, and a tail that points to the next node.

# Handy other command to remove all extra coverage files after running 
    find . \( -name "*.gcno" -o -name "*.gcda" -o -name "*.gcov" \) -delete

# Coverage:
    Average of 95,83% coverage across our tests.
    Linked list: 94,74%
    Hashtable: 97,75%
    Hashtable iterator: 95%
Missing a few edge cases in the tests but we deem those redundant since we test most of that functionality in other parts of the code. 

# Initial Profiling Results
    ## Most used functions for different textsizes:

        ### small.txt our functions:    
        (not our)   do_lookup_x             11.79%
        (not our)   __GI___tunables_init    7.38%
        (not our) _dl_relocate_object       7.02%
        ioopm_string_knr_hash               2.47%
        find_previous_entry                 1.34%
        main                                0.77%

        ### 1k-long-words.txt our functions:
        ioopm_string_knr_hash               60.38%
        (not our)    __strcspn_generic      7.75%       
        find_previous_entry                 4.31%
        (not our)    S:__strcmp_avx2        3.36%
        and many more between
        ioopm_hash_table_lookup             1.09%

        ### 10k-words.txt:
        find_previous_entry                 19.90%
        (not our)    __strcmp_avx2          18.61%
        string_compare                      15.20%
        ioopm_string_knr_hash               13.53%

        ### 16k-words.txt:
        (not our) __strcmp_avx2             30.77%
        find_previous_entry                 27.59%
        string_compare                      26.85%
        ioopm_string_knr_hash               2.05%


## Calls used to acquire numbers above
    gcc -g -O0 -o ht_v1/freq_count ht_v1/freq_count.c ht_v1/hash_table.c ht_v1/hash_table_iterator.c
    valgrind --tool=callgrind ht_v1/freq_count txt_files/{filename}.txt
    callgrind_annotate --sort=Ir callgrind.out.<pid>     

# Profiling Results with dynamic buckets
    ## Most used functions for different textsizes:

        ### small.txt our functions:    
        (not our)   do_lookup_x             10.92%
        (not our)   __GI___tunables_init    6.83%
        (not our) _dl_relocate_object       6.50%
        ioopm_string_knr_hash               3.32%
        advance_iterator_state              1.25%
        skip_sentinel_nodes                 0.98%
        find_previous_entry                 0.95%
        main                                0.71%

        ### 1k-long-words.txt our functions:
        ioopm_string_knr_hash               62.16%
        (not our)    __strcspn_generic      7.91%       
        find_previous_entry                 3.10%
        (not our)    __strcmp_avx2          2.47%
        (not our)    getdelim               1.95%
        string_compare                      1.42%
        ioopm_hash_table_lookup             1.11%

        ### 10k-words.txt:
        ioopm_string_knr_hash               22.87%
        (not our)    __strcspn_generic      12.79%
        find_previous_entry                 11.25%
        (not our)    __strcmp_avx2          6.43%
        string_compare                      5.22%

        ### 16k-words.txt:
        ioopm_string_knr_hash               15.17%
        (not our)    __strcspn_generic      7.37%
        find_previous_entry                 5.76%
        (not our)   _int_malloc             4.77%
        (not our)   _int_free               3.65%
        (not our) __strcmp_avx2             2.77%
        string_compare                      2.43%

        Conclusions:
            Total time spent comparing keys has been reduced after dynamic buckets were implemented, because we have fewer entries per bucket. Each bucket-traversal is now shorter.

            Au contraire, we do now spend more time using the hash function, because of the need for rehashing after resizing the table.

            The improvements were least significant when testing small.txt. There was even a slight increase in runtime, the reason for this is believed to be that the dynmaic buckets are not profitable when the dataset is small: triggering rehashing when the dataset is small is more expensive then then its benefits.

## Calls used to acquire numbers above
    gcc -g -O0 -o ht_v2/freq_count ht_v2/freq_count.c ht_v2/hash_table2.c ht_v2/hash_table_iterator2.c
    valgrind --tool=callgrind ht_v2/freq_count txt_files/{filename}.txt
    callgrind_annotate --sort=Ir callgrind.out.<pid>

# Profiling Results with dynamic buckets with dubble-pointer-buckets (instead of sentinel nodes)
    ## Most used functions for different textsizes:

        ### small.txt our functions:
        (not our)   __GI___tunables_init    33,467 (12.48%)
        (not our)   do_lookup_x             27,164 (10.13%)
        (not our)   _dl_relocate_object     16,159 ( 6.03%)
        (not our)   _dl_lookup_symbol_x     10,520 ( 3.92%)
        (not our)   _int_malloc             10,265 ( 3.83%)
        (not our)   _dl_lookup_symbol_x      9,818 ( 3.66%)   
        ioopm_string_knr_hash                8,265 ( 3.08%)
                    (many inbetween)
        advance_iterator_state               2,649 ( 0.99%)
        find_previous_entry                  2,220 ( 0.83%)
        main                                 1,763 ( 0.66%)

        ### 1k-long-words.txt our functions:
        ioopm_string_knr_hash               2,864,610 (60.79%)
        (not our)   __strcspn_generic         364,564 ( 7.74%)
        (not our)   __strcmp_sse42            181,257 ( 3.85%)
        (not our)   __strspn_generic          142,000 ( 3.01%)
        find_previous_entry                   134,562 ( 2.86%)
        (not our)   getdelim                   89,554 ( 1.90%)
        string_compare                         65,379 ( 1.39%)
        (not our)   _int_free                  63,467 ( 1.35%)
        (not our)   strtok_r                   61,000 ( 1.29%)
        ioopm_hash_table_lookup                51,264 ( 1.09%)

        ### 10k-words.txt:
        ioopm_string_knr_hash               2,946,315 (22.72%)
        (not our)    __strcspn_generic      1,647,238 (12.70%)
        (not our)   __strspn_generic        1,458,062 (11.24%)
        find_previous_entry                 1,366,306 (10.54%)
        (not our)    __strcmp_sse42           993,567 ( 7.66%)
        string_compare                        672,923 ( 5.19%)

        ### 16k-words.txt:
        ioopm_string_knr_hash               5,710,680 (15.04%)
        (not our)   __strcspn_generic       2,772,869 ( 7.30%)
        (not our)   __strspn_generic        2,545,999 ( 6.71%)
        find_previous_entry                 2,038,112 ( 5.37%)
        (not our)   _int_malloc             1,821,886 ( 4.80%)
        (not our)   _int_free               1,374,153 ( 3.62%)
        (not our)   __strcmp_sse42          1,325,431 ( 3.49%)
        string_compare                        913,976 ( 2.41%)

        Conclusions:
            TODO: conclusions
## Calls used to acquire numbers above
    gcc -g -O0 -o ht_v3/freq_count ht_v3/freq_count.c ht_v3/hash_table3.c ht_v3/hash_table_iterator3.c
    valgrind --tool=callgrind ht_v3/freq_count txt_files/{filename}.txt
    callgrind_annotate --sort=Ir callgrind.out.<pid>

# freq_count.c runtime with different textfiles:
    ## Initial values with 17 buckets
        Antal ord   -   körtid (ms)
            small   -   10
            1k      -   15
            10k     -   22
            16k     -   105

    ## Dynamic buckets
        Antal ord   -   körtid (ms)     procentuell förbättring mot ht_v1
            small   -   11                      - 9%
            1k      -   16                      - 6%
            10k     -   20                      +10%
            16k     -   69                      +52%

    ## Dynamic buckets with dubble-pointer-buckets (without sentinel nodes)
        Antal ord   -   körtid (ms)     procentuell förbättring mot ht_v2
            small   -   10                      +10%
            1k      -   14                      +14%
            10k     -   18                      +11%
            16k     -   65                      + 6%

# Profiling memory consumption 
## studied heap behavior of freq_count.c together with different versions of hash table implementation and 16k-words.txt
### Heap consumption with ht_v1
The program reached a peak total heap usage of 353,352 B. Of this, 215,587 B was useful heap allocated by the program, while 137,765 B was allocator overhead.

### Heap consumption with ht_v2
The program reached a peak total heap usage of 864,248 B. Of this, 735,086 B was useful heap allocated by the program, while 129,162 B was allocator overhead.

### Heap consumption with ht_v3
The program reached a peak total heap usage of 484,208 B. Of this, 346,251 B was useful heap allocated by the program, while 137,957 B was allocator overhead.

## Conclusions
When running the second version we see an additional 500kB allocated at the peak, this is mostly due to us upsizing the hashtable and allocating both the latest sizes of buckets until rehashing is complete. Meaning that at the peak we had roughly 24,000 sentinel nodes taking up space. While in the previous version we had 17 sentinel nodes at most. But in V3 we replaced the sentinel nodes with only a pointer to the first element. Effectively freeing up 2/3 of that space as a pointer takes 8B but a full entry_t takes 24B. Meaning we freed up roughly 385kB in the final benchmark. While still using a fair bit more memory than our first version, we get a lot faster performance out of it (61,9% when handling 16k words). So we deem it a valuable upgrade.

## plotting command
valgrind --tool=massif ./ditt_program [argument]
