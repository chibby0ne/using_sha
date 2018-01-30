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

#include <openssl/sha.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAX_MESSAGE_LENGTH 1000
#define DEFAULT_WORD "Hello"

void print_usage(int count, char *argv[])
{
    printf("used: %s", argv[0]);
    for (int i = 1; i < count; ++i) {
        printf(" %s", argv[i]);
    }
    printf("\ncorrect usage: %s WORD_TO_HASH [Default word: %s]\n",
            argv[0], DEFAULT_WORD);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    char *word_to_hash;
    if (argc > 2) {
        print_usage(argc, argv);
    } else if (argc == 2) {
        word_to_hash = argv[1];
    } else {
        word_to_hash = DEFAULT_WORD;
    }
    
    SHA256_CTX ctx;
    unsigned char md[SHA256_DIGEST_LENGTH];
    char hash_string[SHA256_DIGEST_LENGTH * 2 + 1];
    printf("Word to hash: %s\n", word_to_hash);
    if (!SHA256_Init(&ctx)) {
        fprintf(stderr, "error at SHA256_Init\n");
        exit(EXIT_FAILURE);
    }
    if (!SHA256_Update(&ctx, word_to_hash, strlen(word_to_hash))) {
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

    printf("Calculated hash: %s\n", hash_string);

    char command[MAX_MESSAGE_LENGTH];
    strcpy(command, "echo -ne \"");
    strcat(command, word_to_hash);
    strcat(command, "\" | sha256sum");

    FILE *output = popen(command, "r");
    if (output == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
    }

    char golden_hash[MAX_MESSAGE_LENGTH];
    if (fgets(golden_hash, SHA256_DIGEST_LENGTH * 2 + 1, output) != NULL) {
        fprintf(stdout, "Golden hash (sha256sum): %s\n", golden_hash);
    }

    if (!strcmp(hash_string, golden_hash)) {
        printf("Hash matches!\n");
    } else {
        printf("Hash do not match!\n");
    }

    return 0;
}
