// Copyright 2016 The BoringSSL Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef OPENSSL_HEADER_POOL_H
#define OPENSSL_HEADER_POOL_H

#include "CCryptoBoringSSL_base.h"   // IWYU pragma: export

#include "CCryptoBoringSSL_stack.h"

#if defined(__cplusplus)
extern "C" {
#endif


// Buffers and buffer pools.
//
// |CRYPTO_BUFFER|s are simply reference-counted blobs. A |CRYPTO_BUFFER_POOL|
// is an intern table for |CRYPTO_BUFFER|s. This allows for a single copy of a
// given blob to be kept in memory and referenced from multiple places.


DEFINE_STACK_OF(CRYPTO_BUFFER)

// CRYPTO_BUFFER_POOL_new returns a freshly allocated |CRYPTO_BUFFER_POOL| or
// NULL on error.
OPENSSL_EXPORT CRYPTO_BUFFER_POOL* CRYPTO_BUFFER_POOL_new(void);

// CRYPTO_BUFFER_POOL_free frees |pool|, which must be empty.
OPENSSL_EXPORT void CRYPTO_BUFFER_POOL_free(CRYPTO_BUFFER_POOL *pool);

// CRYPTO_BUFFER_new returns a |CRYPTO_BUFFER| containing a copy of |data|, or
// else NULL on error. If |pool| is not NULL then the returned value may be a
// reference to a previously existing |CRYPTO_BUFFER| that contained the same
// data. Otherwise, the returned, fresh |CRYPTO_BUFFER| will be added to the
// pool.
OPENSSL_EXPORT CRYPTO_BUFFER *CRYPTO_BUFFER_new(const uint8_t *data, size_t len,
                                                CRYPTO_BUFFER_POOL *pool);

// CRYPTO_BUFFER_alloc creates an unpooled |CRYPTO_BUFFER| of the given size and
// writes the underlying data pointer to |*out_data|. It returns NULL on error.
//
// After calling this function, |len| bytes of contents must be written to
// |out_data| before passing the returned pointer to any other BoringSSL
// functions. Once initialized, the |CRYPTO_BUFFER| should be treated as
// immutable.
OPENSSL_EXPORT CRYPTO_BUFFER *CRYPTO_BUFFER_alloc(uint8_t **out_data,
                                                  size_t len);

// CRYPTO_BUFFER_new_from_CBS acts the same as |CRYPTO_BUFFER_new|.
OPENSSL_EXPORT CRYPTO_BUFFER *CRYPTO_BUFFER_new_from_CBS(
    const CBS *cbs, CRYPTO_BUFFER_POOL *pool);

// CRYPTO_BUFFER_new_from_static_data_unsafe behaves like |CRYPTO_BUFFER_new|
// but does not copy |data|. |data| must be immutable and last for the lifetime
// of the address space.
OPENSSL_EXPORT CRYPTO_BUFFER *CRYPTO_BUFFER_new_from_static_data_unsafe(
    const uint8_t *data, size_t len, CRYPTO_BUFFER_POOL *pool);

// CRYPTO_BUFFER_free decrements the reference count of |buf|. If there are no
// other references, or if the only remaining reference is from a pool, then
// |buf| will be freed.
OPENSSL_EXPORT void CRYPTO_BUFFER_free(CRYPTO_BUFFER *buf);

// CRYPTO_BUFFER_up_ref increments the reference count of |buf| and returns
// one.
OPENSSL_EXPORT int CRYPTO_BUFFER_up_ref(CRYPTO_BUFFER *buf);

// CRYPTO_BUFFER_data returns a pointer to the data contained in |buf|.
OPENSSL_EXPORT const uint8_t *CRYPTO_BUFFER_data(const CRYPTO_BUFFER *buf);

// CRYPTO_BUFFER_len returns the length, in bytes, of the data contained in
// |buf|.
OPENSSL_EXPORT size_t CRYPTO_BUFFER_len(const CRYPTO_BUFFER *buf);

// CRYPTO_BUFFER_init_CBS initialises |out| to point at the data from |buf|.
OPENSSL_EXPORT void CRYPTO_BUFFER_init_CBS(const CRYPTO_BUFFER *buf, CBS *out);


#if defined(__cplusplus)
}  // extern C

extern "C++" {

BSSL_NAMESPACE_BEGIN

BORINGSSL_MAKE_DELETER(CRYPTO_BUFFER_POOL, CRYPTO_BUFFER_POOL_free)
BORINGSSL_MAKE_DELETER(CRYPTO_BUFFER, CRYPTO_BUFFER_free)
BORINGSSL_MAKE_UP_REF(CRYPTO_BUFFER, CRYPTO_BUFFER_up_ref)

BSSL_NAMESPACE_END

}  // extern C++

#endif

#endif  // OPENSSL_HEADER_POOL_H
