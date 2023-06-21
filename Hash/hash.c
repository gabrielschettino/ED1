#include <stdlib.h>

#include "hash.h"
#include "forward_list.h"

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

typedef struct
{
    void *key;
    void *val;
} HashTableItem;

HashTableItem *_hash_pair_construct(void *key, void *val)
{
    HashTableItem *p = calloc(1, sizeof(HashTableItem));
    p->key = key;
    p->val = val;
    return p;
}

void _hash_pair_destroy(HashTableItem *p)
{
    free(p);
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements = 0;

    return hash_tbl;
}

void hash_table_set(HashTable *h, void *key, void *val)
{
    unsigned int bucket_index = h->hash_fn(h, key) % h->table_size;
    ForwardList *bucket = h->buckets[bucket_index];

    if (bucket == NULL)
    {
        bucket = forward_list_construct();
        h->buckets[bucket_index] = bucket;
    }
    else
    {
        // Check if the key already exists in the bucket
        Node *n = bucket->head;
        while (n != NULL)
        {
            HashTableItem *pair = n->value;
            if (h->cmp_fn(pair->key, key) == 0)
            {
                // Key already exists, update the value
                pair->val = val;
                return;
            }
            n = n->next;
        }
    }

    HashTableItem *pair = _hash_pair_construct(key, val);
    forward_list_push_front(bucket, pair);
    h->n_elements++;
}

void *hash_table_get(HashTable *h, void *key)
{
    unsigned int bucket_index = h->hash_fn(h, key) % h->table_size;
    ForwardList *bucket = h->buckets[bucket_index];

    if (bucket != NULL)
    {
        Node *n = bucket->head;
        while (n != NULL)
        {
            HashTableItem *pair = n->value;
            if (h->cmp_fn(pair->key, key) == 0)
            {
                return pair->val;
            }
            n = n->next;
        }
    }

    return NULL;
}

void *hash_table_pop(HashTable *h, void *key)
{
    unsigned int bucket_index = h->hash_fn(h, key) % h->table_size;
    ForwardList *bucket = h->buckets[bucket_index];

    if (bucket != NULL)
    {
        Node *prev = NULL;
        Node *curr = bucket->head;

        while (curr != NULL)
        {
            HashTableItem *pair = curr->value;
            if (h->cmp_fn(pair->key, key) == 0)
            {
                void *val = pair->val;
                _hash_pair_destroy(pair);

                if (prev == NULL)
                {
                    // Key found at the head of the bucket
                    bucket->head = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }

                forward_list_remove(bucket, curr);
                h->n_elements--;

                return val;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    return NULL;
}

int hash_table_size(HashTable *h)
{
    return h->table_size;
}

int hash_table_num_elems(HashTable *h)
{
    return h->n_elements;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *pair = n->value;
                _hash_pair_destroy(pair);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}
