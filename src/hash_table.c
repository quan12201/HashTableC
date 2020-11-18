#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i-> key = strdup(k);
    i->value = strdup(v);
    return i;
}

ht_hash_table* ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->size = 100;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

void ht_del_hash_table(ht_hash_table* ht) {
    for(int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if(item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;  
    const int s_length = strlen(s);
    for(int i = 0; i <= s_length; i++) {
        hash += pow(a, s_length - (i+1))*s[i];
    }
    hash = hash % m;
    return hash;
}

static int ht_get_hash (const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, ht_prime_1, num_buckets);
    const int hash_b = ht_hash(s, ht_prime_2, num_buckets);
    return (hash_a + attempt*(hash_b + 1)) % num_buckets;    
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash (item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while(cur_item != NULL) {
        index = ht_get_hash(item->key, ht->size, 1);
        i++;
        cur_item = ht->items[index];
    }
    ht->items[index] = item;  
    ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key) {
    for(int i = 0; i < ht-> size; i++) {
        int index = ht_get_hash (key, ht->size, i);
        ht_item* item = ht->items[index];
        if(strcmp(item->key, key) == 0) {
            return item->value;
        }
    }
    return NULL;
}

static ht_item HT_DELETED_ITEM = {NULL, NULL};

void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash (key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item != NULL) {
         if(item != &HT_DELETED_ITEM) {
            
            if(strcmp(item->key, key) == 0) {
                if(i > 1) {
                    ht->items[index-1]-> key = item->key;
                }
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

static ht_hash_table* ht_new_sized(const int base_size) {

}

ht_hash_table* ht_new() {

}

static void ht_resize(ht_hash_table* ht, const int base_size) {

}

static void resize_up(ht_hash_table* ht) {

}

static void resize_down(ht_hash_table* ht) {

}