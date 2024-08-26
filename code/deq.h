#ifndef DEQ_H //header guard
#define DEQ_H

// put: append onto an end, len++
// get: return from an end, len--
// ith: return by 0-base index, len unchanged
// rem: return by == comparing, len-- (iff found)

typedef void *Deq; //type definition, pointer to Deq
typedef void *Data; //type definition, pointer to some Data
		    //Deq user makes sure Data is stored in Dynamic Memory
		    //Deq user manages freeing memory. Unless deq_del on deq

extern Deq deq_new(); //malloc a new Deq Head ptr, tail ptr, int len 24 bytes
extern int deq_len(Deq q); //return Deq len int

extern void deq_head_put(Deq q, Data d); //put data on head
extern Data deq_head_get(Deq q); //return data from head and remove
extern Data deq_head_ith(Deq q, int i); //return ith data from head don't rem 
extern Data deq_head_rem(Deq q, Data d); //return 1st occurance from head & rem

extern void deq_tail_put(Deq q, Data d); //put data on tail
extern Data deq_tail_get(Deq q); //return data from tail and remove
extern Data deq_tail_ith(Deq q, int i); //return ith data from dead don't rem
extern Data deq_tail_rem(Deq q, Data d); //return 1st occurance from head & rem

typedef char *Str; //type definition for string. char * = Str
typedef void (*DeqMapF)(Data d); //Function performed on the entire data
typedef Str  (*DeqStrF)(Data d); //Stringify data

extern void deq_map(Deq q, DeqMapF f); // foreach
extern void deq_del(Deq q, DeqMapF f); // free. 0 in DeqMapF skips map
extern Str  deq_str(Deq q, DeqStrF f); // toString the Deq. 0 frees the strings

#endif
