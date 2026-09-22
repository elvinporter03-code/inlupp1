# Hashtable and linked lists

## Running the tests
    ### Do everything below:
    make all

    ### Compiling the testfiles and sourcefiles:
    make compile_ht -hashtable
    make compile_ll -linked list
    make compile_ht_it -hashtable iterator

    ### Running the tests
    make test_ht
    make test_ll 
    make test_ht_it 

    ### This also produces a gcda file which you can run in order to check the test coverage:
    make coverage_ll
    make coverage_ht
    make coverage_ht_it

    or open the gcov file to see exactly which lines dont get covered.

    ### We also have a wordcounting program that counts the frequency of each word in a txt document:
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
        (not our)    __strspn_generic       3.02%
        and many more between
        ioopm_hash_table_lookup             1.09%

        ### 10k-words.txt:
        find_previous_entry                 19.9%
        (not our)    __strcmp_avx2          18.61%
        string_compare                      15.2%
        ioopm_string_knr_hash               13.53%

        ### 16k-words.txt:
        (not our) __strcmp_avx2             30.77%
        find_previous_entry                 27.59%
        string_compare                      26.85%
            VAD ÄR DETTA!? (???:0x0000000000109170 [???])      2.83%
        ioopm_string_knr_hash               2.05%


## Calls used to acquire numbers above
    gcc -g -O0 -o freq_count freq_count.c hash_table.c hash_table_iterator.c
    valgrind --tool=callgrind ./freq_count {filename}.txt
    callgrind_annotate --sort=Ir callgrind.out.<pid>     

# Mer profilering:
    ## Initial values with 17 buckets
        Antal ord   -   körtid (ms)
            small   -   10
            1k      -   15
            10k     -   22
            16k     -   105

    ## Dynamic buckets
        Antal ord   -   körtid (ms)
            small   -   8
            1k      -   12
            10k     -   17
            16k     -   85

    ## Optimized dynamic buckets with better resizing function