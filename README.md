# pure_c_collections

Finally I decided implement the most common collections that I myself usually need. All implementations support "objects". APIs are not necessarily consistent. Implementations are not necessarily efficient for large lists. 

 - Arraylist: a preallocated fixed size list
 - Linkedlist: good old linkedlist
 - Set: based on the linkedlist implementation (i.e. no hashmap)
 - Dict: will be based on the set implementation (i.e. no hashmap)

 Set and Dict should ideally use hashmaps but that will complicate things a lot.
 For the time being this is a library for small/embedded use-cases where sizes shouldnt grow too big.