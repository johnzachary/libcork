/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2013, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the COPYING file in this distribution for license
 * details.
 * ----------------------------------------------------------------------
 */

#ifndef LIBCORK_DS_BLOOM_FILTER_H
#define LIBCORK_DS_BLOOM_FILTER_H

#include <libcork/core/api.h>
#include <libcork/core/hash.h>
#include <libcork/core/types.h>
#include <libcork/ds/bitset.h>


/*----------------------------------------------------------------------
 * Bloom filter
 */

struct cork_bloom_filter;

CORK_API struct cork_bloom_filter *
cork_bloom_filter_new(size_t capacity, unsigned int hash_count);

CORK_API void
cork_bloom_filter_free(struct cork_bloom_filter *bf);

CORK_API void
cork_bloom_filter_insert(struct cork_bloom_filter *bf, void *key, size_t len);

CORK_API bool
cork_bloom_filter_contains(struct cork_bloom_filter *bf, void *key, size_t len);

#endif /* LIBCORK_DS_BLOOM_FILTER_H */
