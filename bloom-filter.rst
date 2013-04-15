.. _bloom-filter

*************
Bloom filters
*************

.. highlight:: c

::

  #include <libcork/ds.h>

This section defines a type for Bloom filters in libcork.  Bloom filters are
simple probabilistic data structures used for set membership.  They tradeoff
space-efficiency for a non-zero change of false positives.

.. type:: struct cork_bloom_filter

   A structure containing a :c:type:`cork_bitset`.  You should not allocate
   any instances of this type; use :c:func:`cork_bloom_filter_new` instead.

   .. member:: struct cork_bitset filter

      The Bloom filter represented as a bit set.

   .. member:: size_t count

      The number of elements stored in the Bloom filter (set).


.. function:: struct cork_bloom_filter \*cork_bloom_filter_new(size_t
max_elements)

   Create a new Bloom filter with enough space to store the given number of
   set elements.  Note that we do not allow the use to specify hash functions
   to use.

.. function:: void cork_bloom_filter_free(struct cork_bloom_filter \*bf)

   Free a Bloom filter

.. function:: void cork_bloom_filter_clear(struct cork_bloom_filter \*bf)

   Clear an existing Bloom filter, effectively setting the set to NULL.

.. function:: void cork_bloom_filter_insert(struct cork_bloom_filter \*bf, const
char \*key)

   Insert *key* into the set.  It is your responsibility to assure that *key*
   is in the range of the set; we will quietly drop *key* if it is greater than
   the set size.

.. function:: bool cork_bloom_filter_contains(struct cork_bloom_filter \*bf,
const char \*key)

   Return whether *key* is a member of the set.  If is your responsibility to
   assure that *key* is in the range of the set; we will return *false* if *key*
   is greater than the set size.
