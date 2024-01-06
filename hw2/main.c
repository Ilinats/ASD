#include <stdio.h>
#include "tree.h"

int play_dialogue(Node *node, Inventory *inventory) {
    if(node == NULL) 
        return 1;

    if(node->requiredItem) {
        int flag = 0;
        inventory = use_inventory(inventory, node->requiredItem, node->requiredItemQuantity, &flag);

        if(!flag)
            return 0;
    }

    printf("%s\n\n", node->npcLine);

    if(node->replies_count) {
        if(node->replies_count == 1) {
            printf("%s\n", node->replies[0]);
            play_dialogue(node->next[0], inventory);
            return 1;
        }

        for (int i = 0; i < node->replies_count; i++) {
            printf("%d. %s", i + 1, node->replies[i]);

            if(node->next[i] != NULL && node->next[i]->requiredItem)
                printf(" (requires %d of %s)", node->next[i]->requiredItemQuantity, node->next[i]->requiredItem);

            printf("\n");
        }

        int choice;
        printf("Choose how to proceed: ");
        scanf("%d", &choice);
        printf("\n");
        
        if(choice > 0 && choice <= node->replies_count) {
            if(!play_dialogue(node->next[choice - 1], inventory))
                play_dialogue(node, inventory);
        }
        else {
            printf("Incorrect choice!\n\n");
            play_dialogue(node, inventory);
        }

    } else if(node->next_count == 1)
        play_dialogue(node->next[0], inventory);

    return 1;
}

int main() {

    Inventory *inventory = add_inventory(NULL, "map", 2);
    inventory = add_inventory(inventory, "garden key", 2);
    inventory = add_inventory(inventory, "magic book", 4);
    printInventory(inventory);

    Node *cyclic_node = init_node("\nTry again!\n", NULL, 0, (Node *[]){NULL}, 1, NULL, 0);

    Node *node24 = init_node("Flora: The Winx Club has used many powerful combinations. One of my favorites is the Enchantix Convergence. It's a combination of all our powers. It's so powerful, it can even bring someone back to life!", 
        (char *[]){"Wow, this is so impressive, I wish I could do that."}, 0, 
        NULL, 0, NULL, 0);

    Node *node23 = init_node("Well, that's great. We'd love to have you join us!", 
        NULL, 0, (Node *[]){cyclic_node}, 1, "enchantix", 1);

    Node *node22 = init_node("You end up poisoning yourself with a poisonous flower and die.", 
        NULL, 0, 
        (Node *[]){cyclic_node}, 1, NULL, 0);
    
    Node *node21 = init_node("Oh, you've got a taste for adventure! We do have a few secret passages. The Whispering Tunnels connect different parts of Alfea, and the Enchanted Staircase can take you to unexpected places. Ready for a bit of mystery?", 
        (char *[]){"Oh, you've got a taste for adventure! We do have a few secret passages."}, 1, 
        (Node *[]){cyclic_node}, 1, "map", 3);

    Node *node20 = init_node("The classrooms are like mini-wonderlands! We have the Elemental Chamber for honing elemental skills, the Starlight Studio for creative magic, and the Crystal Observatory for celestial studies.", 
        (char *[]){"That sounds great! Thank you for sharing this!"}, 1, 
        (Node *[]){cyclic_node}, 1, NULL, 0);
    
    Node *node19 = init_node("How about exploring the realms beyond Alfea?", 
        (char *[]){"Sure, I'd love to!"}, 1,
        NULL, 0, NULL, 0);
    
    Node *node18 = init_node("Flora: (Beaming with pride) The Winx Club - our extraordinary sisterhood on a mission to safeguard the magical realm! Imagine facing mythical creatures, unraveling ancient prophecies, and standing strong against dark forces. Intrigued?", 
        (char *[]){"I'm definitely interested in joining the Winx Club!", "What's the most powerful magical combination the Winx Club has used?"}, 2,
        (Node *[]){node23, node24}, 2, NULL, 0);
    
    Node *node17 = init_node("Flora: The Forbidden Caverns—hidden beneath Alfea. Rumor has it, ancient secrets and untold mysteries reside there. Only the bravest venture in.", 
        NULL, 0, (Node *[]){cyclic_node}, 1, NULL, 0);
    
    Node *node16 = init_node("You meet with Professor Faragonda and she ends up liking you a lot.", 
        NULL, 0, 
        (Node *[]){cyclic_node}, 1, NULL, 0);
    
    Node *node15 = init_node("The library is a treasure trove of magical knowledge. You'll find books on spells, creatures, and the history of the magical realm. Ready to explore?", 
        NULL, 0, NULL, 0, "magic book", 4);
    
    Node *node14 = init_node("Stella: Ah, the mystical gardens! They're filled with rare and magical plants. Some even respond to our emotions. Let's take a stroll.", 
        NULL, 0, 
        (Node *[]){node22}, 1, "garden key", 1);
    
    Node *node13 = init_node("Stella: The courtyard is the heart of Alfea. It's where we often gather, practice magic, and enjoy the beauty of the surroundings.", 
        NULL, 0, NULL, 0, NULL, 0);

    Node *node12 = init_node("You are having a great time and end up being good friends with the Winx. You sucessfully graduate from Alfea.", 
        NULL, 0, NULL, 0, NULL, 0);

    Node *node11 = init_node("Musa: Alfea is filled with magic, from classrooms to hidden passages. Ready to explore? Any particular area you're curious about?", 
        (char *[]){"Tell me about the classrooms.", "Are there any secret passages?"}, 2,
        (Node *[]){node20, node21}, 2, NULL, 0);
    
    Node *node10 = init_node("Musa: Want to join us on our next mission?", 
        (char *[]){"I would love to!", "I'm not sure I am."}, 2,
        (Node *[]){node19, cyclic_node}, 2, NULL, 0);
    
    Node *node9 = init_node("Flora: Take your time. When you're ready, we'll be right here. Is there anything specific on your mind?", 
        (char *[]){"Tell me about the most mysterious place in Alfea.", "I'd like to know more about the Winx Club."}, 2,
        (Node *[]){node17, node18}, 2, NULL, 0);
    
    Node *node8 = init_node("Flora: Professor Faragonda is the headmistress of Alfea. She's knowledgeable about all things magical. Ready to meet her?", 
        (char *[]){"Yes, let's go!", "No, I don't think I am. I don't even think I am ready for this school, maybe it's better if I don't attend this year."}, 2,
        (Node *[]){node16, NULL}, 2, NULL, 0);
    
    Node *node7 = init_node("Stella: It's in the main tower, just past the courtyard. Come on, I'll show you. Anything specific you want to know about Alfea?", 
        (char *[]){"No, I don't think I have any question thought out at the moment. Thanks for the help!"}, 1,
        (Node *[]){cyclic_node}, 1, NULL, 0);
    
    Node *node6 = init_node("Stella: Of course! We can take a quick tour before heading to the office. What area are you curious about?", 
        (char *[]){"The courtyard.", "The mystical gardens.", "The library."}, 3,
        (Node *[]){node13, node14, node15}, 3, "map", 2);

    Node *node5 = init_node("Stella: Great! Follow me.\nAs you walk, she shares some fun stories about her experiences at Alfea, making you feel more at ease.", 
        (char *[]){"That's so cool! I can't wait to make my own memories here."}, 1,
        (Node *[]){node12}, 1, NULL, 0);

    Node *node4 = init_node("Musa: It's surreal, isn't it? Alfea has a way of making dreams come true. Ready for our next adventure?", 
        (char *[]){ "Absolutely! What's the plan?", 
                    "Tell me more about the school, Musa."}, 2,
        (Node *[]){node10, node11}, 2, NULL, 0);

    Node *node3 = init_node("Flora: It's perfectly normal to feel that way. Don't worry, we're all friends here. Ready to head to Professor Faragonda's office?", 
        (char *[]){ "Can you tell me more about Professor Faragonda?", 
                    "Actually, I'd like to take a moment to breathe."}, 2,
        (Node *[]){node8, node9}, 2, NULL, 0);
    
    Node *node2 = init_node("Stella: That's the spirit! So, first things first. We're heading to Professor Faragonda's office. Ready to go?", 
        (char *[]){ "Absolutely! Lead the way, Stella.", 
                    "Can we explore the grounds a bit first?", 
                    "Um, sure. Where is her office, though?"}, 3,
        (Node *[]){node5, node6, node7}, 3, NULL, 0);

    Node * root = init_node("You, a talented fairy, have just arrived at Alfea to begin your magical education. The school's grand entrance is adorned with colorful flowers, and the air is filled with the enchanting aroma of magic.\n \
    As you step onto the grounds, you encounter your friends from the Winx Club: Bloom, Stella, Flora, Musa, Tecna, and Layla.\nBloom: Hey there, how are you feeling?", 
        (char *[]){
            "Excited! It's such a magical place.", 
            "A bit nervous, to be honest.", 
            "I can't believe I'm finally here!"
        }, 3,
        (Node *[]){node2, node3, node4}, 3, NULL, 0);

    cyclic_node->next[0] = root;

    play_dialogue(root, inventory);

    return 0;
}