#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getKey(char* keyString, const char* keyName) {
    FILE* key = fopen(keyName, "r");

    if (key == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fgets(keyString, 100, key);
}

void fileXOR(const char* readName, const char* writeName, char key[100]) {
    char c;
    int keyLength = strlen(key);
    int keyIndex = 0;

    FILE* read = fopen(readName, "rb");
    FILE* write = fopen(writeName, "wb");

    if(read == NULL || write == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while ((c = fgetc(read)) != EOF) {
        c ^= key[keyIndex];
        keyIndex = (keyIndex + 1) % keyLength;
        //printf("%d", c == EOF);
        fputc(c, write);
    }

    fclose(read);
    fclose(write);
}

int main() {
    char keyString[100];
    getKey(keyString, "key.txt");
    fileXOR("deck.txt", "encrypted.txt", keyString);
    fileXOR("encrypted.txt", "decrypted.txt", keyString);

    return 0;
}