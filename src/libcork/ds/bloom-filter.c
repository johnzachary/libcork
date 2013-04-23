/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2013, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the COPYING file in this distribution for license
 * details.
 * ----------------------------------------------------------------------
 */

#include <stdlib.h>

#include "libcork/core.h"
#include "libcork/ds/bitset.h"
#include "libcork/ds/bloom-filter.h"
#include "libcork/helpers/errors.h"


/* cork-hash of "ds-bloom-filter" */
#define HASH_SEED  0x66fe6d2a


/*----------------------------------------------------------------------
 * Bloom filter data structure
 */

struct cork_bloom_filter {
    struct cork_bitset  *filter;
    size_t  capacity;
    unsigned int  hash_count;
};


/*----------------------------------------------------------------------
 * Bloom filter operations
 */

struct cork_bloom_filter *
cork_bloom_filter_new(size_t capacity, unsigned int hash_count)
{
    struct cork_bloom_filter  *self = cork_new(struct cork_bloom_filter);

    self->filter = cork_bitset_new(capacity);
    self->capacity = capacity;
    self->hash_count = hash_count;
    return self;
}

void
cork_bloom_filter_free(struct cork_bloom_filter *bf)
{
    cork_bitset_free(bf->filter);
    free(bf);
}

void
cork_bloom_filter_insert(struct cork_bloom_filter *bf, void *key, size_t len)
{
    cork_hash  hash1 = cork_hash_buffer(HASH_SEED, key, len);
    cork_hash  hash2 = cork_hash_buffer(hash1, key, len);
    cork_hash  hash;
    unsigned int  i;

    for (i = 0; i < bf->hash_count; i++) {
        hash = (hash1 + i*hash2) % bf->capacity;
        cork_bitset_set(bf->filter, hash, true);
    }
}

bool
cork_bloom_filter_contains(struct cork_bloom_filter *bf, void *key, size_t len)
{
    cork_hash  hash1 = cork_hash_buffer(HASH_SEED, key, len);
    cork_hash  hash2 = cork_hash_buffer(hash1, key, len);
    cork_hash  hash;
    unsigned int  i;

    for (i = 0; i < bf->hash_count; i++) {
        hash = (hash1 + i*hash2) % bf->capacity;
        if (cork_bitset_get(bf->filter, hash) == false) {
            return false;
        }
    }
    return true;
}
