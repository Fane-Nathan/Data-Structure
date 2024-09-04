#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <openssl/sha.h>

#define TABLE_SIZE 100

typedef struct {
    char key[SHA256_DIGEST_LENGTH];
    int value;
} Entry;

typedef struct {
    Entry entries[TABLE_SIZE];
} HashTable;

void hash(const char* input, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

void insert(HashTable* table, const char* key, int value) {
    char hashedKey[SHA256_DIGEST_LENGTH * 2 + 1];
    hash(key, hashedKey);

    int index = atoi(hashedKey) % TABLE_SIZE;
    strcpy(table->entries[index].key, hashedKey);
    table->entries[index].value = value;
}

int get(HashTable* table, const char* key) {
    char hashedKey[SHA256_DIGEST_LENGTH * 2 + 1];
    hash(key, hashedKey);

    int index = atoi(hashedKey) % TABLE_SIZE;
    if (strcmp(table->entries[index].key, hashedKey) == 0) {
        return table->entries[index].value;
    }

    return -1;
}

int main() {
    HashTable table;
    insert(&table, "key1", 10);
    insert(&table, "key2", 20);

    int value = get(&table, "key1");
    printf("Value: %d\n", value);

    return 0;
}
