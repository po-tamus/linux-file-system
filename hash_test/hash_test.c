#include "ut_hash.h"

char *key; 

typedef struct {
    char hash_key[16]; //key
    UT_hash_handle hh; //this is the hash handle 
} record_t;

record_t *records = NULL;

record_t *data_w = malloc(sizeof(record_t)); 
data_w->key = "qwegjioa9hhsuhs";

//HASH_ADD(handle, )
HASH_ADD(hh, records, data->key, 16, data_w); 