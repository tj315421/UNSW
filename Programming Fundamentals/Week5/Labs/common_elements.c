// copy all of the values in source1 which are also found in source2 into destination
// return the number of elements copied into destination

// This program was written by Leon) WANG LIAO z5306312
// on 18/10/2020

int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    // PUT YOUR CODE HERE (you must change the next line!)
    int *p = destination;
    int counter = 0;
    // set i and j as counters of source1 and source2
    int i = 0;
    while (i < length) {
        int j = 0;
        // using a loop inside another to traverse all elements
        // in source1 and source2
        while (j < length) {
            // when elements in source1 equal to source2
            // copy the values.
            if (source1[i] == source2[j]) {
                // set these equal values to the destination array
                *p = source1[i];
                // return the numbers of copied elements
                counter++;
                p++;
                
                break;
            }
            
            j++;
        }
        
        i++;
    }
    
    return counter;
}

// You may optionally add a main function to test your common_elements function.
// It will not be marked.
// Only your common_elements function will be marked.
