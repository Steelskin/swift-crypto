// Copyright 2001-2016 The OpenSSL Project Authors. All Rights Reserved.
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

#include <stdio.h>

#include <CCryptoBoringSSL_bio.h>
#include <CCryptoBoringSSL_evp.h>
#include <CCryptoBoringSSL_pem.h>
#include <CCryptoBoringSSL_x509.h>

IMPLEMENT_PEM_rw(X509_AUX, X509, PEM_STRING_X509_TRUSTED, X509_AUX)
