#ifndef DEQ_H
#define DEQ_H

// put: append onto an end, len++
// get: return from an end, len--
// ith: return by 0-base index, len unchanged
// rem: return by == comparing, len-- (iff found)

typedef void *Deq; //type definition, pointer to Deq
typedef void *Data; //type definition, pointer to some Data

extern Deq deq_new(); //malloc a new Deq Head ptr, tail ptr, int len 24 bytes
extern int deq_len(Deq q); //return Deq len int

extern void deq_head_put(Deq q, Data d); //put data on head
extern Data deq_head_get(Deq q); //return data from head don't remove
extern Data deq_head_ith(Deq q, int i); //return ith data from head don't rem 
extern Data deq_head_rem(Deq q, Data d); //return 1st occurance from head & rem

extern void deq_tail_put(Deq q, Data d); //put data on tail
extern Data deq_tail_get(Deq q); //return data from tail don't remove
extern Data deq_tail_ith(Deq q, int i); //return ith data from dead don't rem
extern Data deq_tail_rem(Deq q, Data d); //return 1st occurance from head & rem

typedef char *Str;
typedef void (*DeqMapF)(Data d); 
typedef Str  (*DeqStrF)(Data d); 

extern void deq_map(Deq q, DeqMapF f); // foreach
extern void deq_del(Deq q, DeqMapF f); // free
extern Str  deq_str(Deq q, DeqStrF f); // toString

#endif
