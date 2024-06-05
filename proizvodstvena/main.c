#include <stdio.h>
#include <stdlib.h>
#include "xor.c" //TODO: xor.h vmesto xor.c

typedef struct card {
	char value;
	char color;
} Card;

typedef struct deck {
    Card cards[52];
} Deck;

Card* createCard(char value, char color) {
    Card* card = (Card*)malloc(sizeof(Card));
    card->value = value;
    card->color = color;
    return card;
}

Deck* createDeck(const char* deckName) {
    Deck* deck = (Deck*)malloc(sizeof(Deck));
    FILE* deckFile = fopen(deckName, "r");
    
    if (deckFile == NULL) {
        perror("Error opening file");
        return NULL;
    }

    int counter = 0;
    printf("Deck file: %s\n", deckName);

    while (counter < 52 && fscanf(deckFile, " %c %c", &deck->cards[counter].value, &deck->cards[counter].color) == 2)
        counter++;

    fclose(deckFile);

    for (int i = 0; i < counter; i++)
        printf("%c %c\n", deck->cards[i].value, deck->cards[i].color);

    return deck;
}

int main() {
    char keyString[100];
    getKey(keyString, "key.txt", 100);
    fileXOR("deck.txt", "encrypted.txt", keyString);
    fileXOR("encrypted.txt", "decrypted.txt", keyString);

    Deck* deck = createDeck("decrypted.txt");

    return 0;
}