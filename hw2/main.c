#include <stdio.h>
#include "tree.h"

int main() {
    Node *node2, *node3, *node4, *node5, *node6, *node7, *node8, *node9, *node10, *node11;
    Node *node12, *node13, *node14, *node15, *node16, *node17, *node18, *node19, *node20, *node21, *node22, *node23;

    node2 = init_node("Stella: That's the spirit! So, first things first. We're heading to Professor \
                            Faragonda's office. Ready to go?", 
                            (char *[]){"Absolutely! Lead the way, Stella.", "Can we explore the grounds a bit first?", 
                            "Um, sure. Where is her office, though?"},
                            (Node *[]){node5, node6, node7});

    node3 = init_node("Flora: It's perfectly normal to feel that way. Don't worry, we're all friends here. Ready \
                            to head to Professor Faragonda's office?", 
                            (char *[]){"Can you tell me more about Professor Faragonda?", "Actually, I'd like to take a moment to breathe."},
                            (Node *[]){node8, node9});

    node4 = init_node("Musa: It's surreal, isn't it? Alfea has a way of making dreams come true. Ready for our next adventure?", 
                            (char *[]){"Absolutely! What's the plan?", "Tell me more about the school, Musa."},
                            (Node *[]){node10, node11});

    node5 = init_node("Stella: Great! Follow me.\nAs you walk, she shares some fun stories about her experiences \
                            at Alfea, making you feel more at ease.", 
                            NULL,
                            (Node *[]){node12});

    node6 = init_node("Stella: Of course! We can take a quick tour before heading to the office. What area are you curious about?", 
                            (char *[]){"The courtyard.", "The mystical gardens.", "The library."},
                            (Node *[]){node13, node14, node15});

    node7 = init_node("Stella: It's in the main tower, just past the courtyard. Come on, I'll show you. \
                            Anything specific you want to know about Alfea?", 
                            (char *[]){"No, I don't think I have any question thought out at the moment. Thanks for the help!"},
                            NULL);

    node8 = init_node("Flora: Professor Faragonda is the headmistress of Alfea. She's knowledgeable about all things \
                            magical. Ready to meet her?", 
                            (char *[]){"Yes, let's go!", "No, I don't think I am. I don't even think I am ready for this \
                            school, maybe it's better if I don't attend this year."},
                            (Node *[]){node16, NULL});

    node9 = init_node("Flora: Take your time. When you're ready, we'll be right here. Is there anything specific on your mind?", 
                            (char *[]){"Tell me about the most mysterious place in Alfea.", "I'd like to know more about the Winx Club."},
                            (Node *[]){node17, node18});

    node10 = init_node("Musa: It's surreal, isn't it? Alfea has a way of making dreams come true. Ready for our next adventure?", 
                            (char *[]){"Absolutely! What do you have in mind.?", "I'm not sure I am."},
                            (Node *[]){node19, NULL});

    node11 = init_node("Musa: Alfea is filled with magic, from classrooms to hidden passages. Ready to explore? \
                            Any particular area you're curious about?", 
                            (char *[]){"Tell me about the classrooms.", "Are there any secret passages?"},
                            (Node *[]){node20, node21});

    node12 = init_node("You are having a great time and end up being good friends with the Winx. You sucessfully graduate from Alfea.", 
                            NULL,
                            NULL);

    node13 = init_node("Stella: The courtyard is the heart of Alfea. It's where we often gather, practice magic, \
                            and enjoy the beauty of the surroundings.", 
                            NULL,
                            NULL);

    node14 = init_node("Stella: Ah, the mystical gardens! They're filled with rare and magical plants. Some even \
                            respond to our emotions. Let's take a stroll.", 
                            NULL,
                            NULL);

    node15 = init_node("The library is a treasure trove of magical knowledge. You'll find books on spells, creatures, \
                            and the history of the magical realm. Ready to explore?", 
                            NULL,
                            NULL);

    node16 = init_node("You meet with Professor Faragonda and she ends up liking you a lot.", 
                            NULL,
                            NULL);

    node17 = init_node("Flora: The Forbidden Caverns—hidden beneath Alfea. Rumor has it, ancient secrets and untold \
                            mysteries reside there. Only the bravest venture in.", 
                            NULL,
                            NULL);

    node18 = init_node("Flora: (Beaming with pride) The Winx Club—our extraordinary sisterhood on a mission to       \
                            safeguard the magical realm! Imagine facing mythical creatures, unraveling ancient prophecies, \
                            and standing strong against dark forces. Intrigued?", 
                            (char *[]){"I'm definitely interested in joining the Winx Club!", "What's the most powerful \
                            magical combination the Winx Club has used?"},
                            (Node *[]){node22, node23});

    node19 = init_node("How about exploring the realms beyond Alfea?", 
                            (char *[]){"Sure, I'd love to!"},
                            NULL);

    node20 = init_node(" The classrooms are like mini-wonderlands! We have the Elemental Chamber for honing elemental  \
                            skills, the Starlight Studio for creative magic, and the Crystal Observatory for celestial studies.", 
                            NULL,
                            NULL);

    node21 = init_node("Oh, you've got a taste for adventure! We do have a few secret passages. The Whispering Tunnels \
                            connect different parts of Alfea, and the Enchanted Staircase can take you to unexpected places. \
                            Ready for a bit of mystery?", 
                            NULL,
                            NULL);

    node22 = init_node("Oh, you've got a taste for adventure! We do have a few secret passages. The Whispering Tunnels \
                            connect different parts of Alfea, and the Enchanted Staircase can take you to unexpected places. \
                            Ready for a bit of mystery?", 
                            NULL,
                            NULL);

    node23 = init_node("Oh, you've got a taste for adventure! We do have a few secret passages. The Whispering Tunnels \
                            connect different parts of Alfea, and the Enchanted Staircase can take you to unexpected places. \
                            Ready for a bit of mystery?", 
                            NULL,
                            NULL);

    Node *root = init_node("You, a talented fairy, have just arrived at Alfea to begin your magical education.            \
                            The school's grand entrance is adorned with colorful flowers, and the air is filled with the  \
                            enchanting aroma of magic. As you step onto the grounds, you encounter your friends from the  \
                            Winx Club: Bloom, Stella, Flora, Musa, Tecna, and Aisha.\n Bloom: Hey there, how are you feeling?", 
                            (char *[]){"Excited! It's such a magical place.", "A bit nervous, to be honest.", 
                           "I can't believe I'm finally here!"},
                            (Node *[]){node2, node3, node4});
    
    return 0;
}
