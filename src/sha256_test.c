/* Sha256 usage test */
/* Copyright © 2017 yourname */

/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the "Software"), */
/* to deal in the Software without restriction, including without limitation */
/* the rights to use, copy, modify, merge, publish, distribute, sublicense, */
/* and/or sell copies of the Software, and to permit persons to whom the */
/* Software is furnished to do so, subject to the following conditions: */

/* The above copyright notice and this permission notice shall be included */
/* in all copies or substantial portions of the Software. */

/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, */
/* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE */
/* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

/* To test using sha256sum command use,
   echo -ne "Hola\0" | sha256sum  */
#include <openssl/sha.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    
    SHA256_CTX ctx;
    unsigned char md[SHA256_DIGEST_LENGTH];
    char hash_string[SHA256_DIGEST_LENGTH * 2 + 1];
    char message[] = "Hola";
    printf("message: %s\n", message);
    if (!SHA256_Init(&ctx)) {
        fprintf(stderr, "error at SHA256_Init\n");
        exit(EXIT_FAILURE);
    }
    if (!SHA256_Update(&ctx, message, strlen(message) + 1)) {
        fprintf(stderr, "error at SHA256_Update\n");
        exit(EXIT_FAILURE);
    }
    if (!SHA256_Final(md, &ctx)) {
        fprintf(stderr, "error at SHA256_Final\n");
        exit(EXIT_FAILURE);
    }

    static const char alphabet[] = "0123456789abcdef";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hash_string[2 * i] = alphabet[md[i] / 16];
        hash_string[2 * i + 1] = alphabet[md[i] % 16];
    }
    hash_string[SHA256_DIGEST_LENGTH * 2] = '\0';

    printf("hash_string: %s\n", hash_string);
    unsigned char golden_hash[] = "e9ceb6edc7086211436868bc69a3a4c2a8ea7f3caf62e6c47b2196fd289c7d6e";
    if (!strcmp(hash_string, golden_hash)) {
        printf("Hash matches!\n");
    } else {
        printf("Hash do not match!\n");
    }

    return 0;
}
