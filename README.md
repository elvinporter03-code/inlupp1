#Hashtable and linked lists

##Running the tests
    ###Compiling the testfiles and sourcefiles:
    make compile_ht -hashtable
    make compile_ll -linked list
    make compile_ht_it -hashtable iterator

    ###Running the tests
    make test_ht
    make test_ll 
    make test_ht_it 

    ###This also produces a gcov file which you can run in order to check the test coverage:
    gcov linked_list.c.gcov
    gcov hash_table.c.gcov
    gcov hash_table_iterator.c.gcov

    ###We also have a wordcounting program that counts the frequency of each word in a txt document:
    gcc freq_count.c hash_table_iterator.c hash_table.c -o counter
    ./counter {name of your txtfile}.txt

##Design decisions:
    Everything about our implementation is pretty standard, maybe with the exception of our linked list iterator starting over from the first element after iterating through the entire list. 
    The implementation is rather foolproof and shouldnt be too easy to crash, as it returns False or nothing whenever the user uses it wrong.

    The linked list follows this structure:
    The list element which contains pointers to the first and last element of the list for quick access, and a constant unsigned int which holds the size of the list. It gets updated dynamically whenever the user adds or removes an element from the list.
    Each listnode consists of a head which contains the value of the node, and a tail that points to the next node.