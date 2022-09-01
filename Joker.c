//Rachael Seedenburg
//April 6th 2017


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card_s {
	char suit;
	int face;
	struct card_s *next, *previous;
}card;
card* create_Deck() {
	card *temp, *headp = NULL, *curr = NULL, *tailp = NULL;
	int i = 1;//the counter for the whole deck
	int c = 1;//the counter for the clubs
	int s = 1;//the counter for the spades
	int h = 1;//the counter for the hearts
	int d = 1;//the counter for the diamonds
	while (i <= 53) {//so I can get 53 cards
		temp = (card*)malloc(sizeof(card));//dynamically allocating memory
		if (i <= 13) {//for clubs
			temp->suit = 5;
			temp->face = c;
			++c;
		}
		else if (i >= 14 && i <= 26) {//for spades
			temp->suit = 6;
			temp->face = s;
			++s;
		}
		else if (i >= 27 && i <= 39) {//for hearts
			temp->suit = 3;
			temp->face = h;
			++h;
		}
		else  if (i >= 40 && i <= 52) {//for diamonds
			temp->suit = 4;
			temp->face = d;
			++d;
		}
		else if (i == 53) {//The joker
			temp->suit = 'J';
			temp->face = 100;
		}

		if (curr == NULL) {//Setting up the linked list
			headp = temp;//when it is the first card in the series
			headp->previous = NULL;
		}
		else {
			temp->previous = curr;//everything in the middle
			curr->next = temp;
		}
		if (i == 53) {
			tailp = temp;//when it is the last card in the series
			tailp->previous = curr;
			tailp->next = NULL;
		}
		else {
			curr = temp;//establishing the linked list
			temp->next = NULL;
		}
		++i;
	}
	return headp;//returning the head pointer
}
void swap(card* card1, card* card2) {
	card* tempSwapCard = (card*)malloc(sizeof(card));

	tempSwapCard->face = card1->face; //swaps the faces of the cards with a temp card
	card1->face = card2->face;
	card2->face = tempSwapCard->face;

	tempSwapCard->suit = card1->suit; //swaps the suits of the cards with a temp card
	card1->suit = card2->suit;
	card2->suit = tempSwapCard->suit;


	free(tempSwapCard);//freeing up Swapcar space
}
card* find_card(card* cardlist, int num) {
	card* temp = cardlist;//starting at the beginning of the list
	int i = 0;
	while (temp != NULL && i<num) {//going until the right card is reached
		temp = temp->next;
		++i;
	}
	return temp;
}
void shuffle(card *cardh, int size) {
	card* temp1 = cardh, *temp2 = cardh, *newhead = NULL;
	int num;
	for (int j = 0; j < 500; ++j) {//to shuffle 500 times
		while (temp1 != NULL) {//travers the whole list
			num = (rand() % size);//getting a random number
			temp2 = find_card(cardh, num);//finding the card that belongs to that number
			swap(temp1, temp2);//swapping the values
			temp1 = temp1->next;//contiuing on the list
		}
		temp1 = cardh;//restarting the temp variable to the beginning of the list
	}

	return;
}
void deal_Cards(card** deck, card** player1, card** computer) {
	int counter = 0;
	card *temp1 = *deck;
	card *curr2 = (card*)malloc(sizeof(card));
	card *curr = (card*)malloc(sizeof(card));


	while (temp1 != NULL) {
		if ((counter % 2) == 0) {//If the card is an even one
			if (counter == 0) {
				*player1 = *deck;//setting up the beginning of the player's deck
				*deck = (*deck)->next;//going to the next card in the deck
				(*player1)->next = NULL;//emptying Player 1's next
				curr = *player1;//connecting curr to player 1
				curr->previous = NULL;//making it point to previous
			}
			else {//if it is not the first card
				curr->next = temp1;//connecting to temp
				*deck = (*deck)->next;//deleting the head node and moving it to the next one
				curr->next->previous = curr;//connecting the next node to the current one
				curr = curr->next;//moving to the next item on the list
				curr->next = NULL;
			}

		}
		if ((counter % 2) == 1) {//if the card is odd it goes to computer
			if (counter == 1) {//is a copy of what I did for player
				*computer = *deck;
				*deck = (*deck)->next;
				(*computer)->next = NULL;
				curr2 = *computer;
				curr2->previous = NULL;
			}
			else {
				curr2->next = temp1;
				*deck = (*deck)->next;
				curr2->next->previous = curr2;
				curr2 = curr2->next;
				curr2->next = NULL;
			}


		}

		temp1 = *deck;
		++counter;
	}
}
int deck_size(card* p) {//Getting the size of the deck to use for suffling and picking out values
	card* temp = p;//starts at the beginning
	int counter = 0;//counts the cards
	while (temp != NULL) {
		++counter;
		temp = temp->next;//moves along the list
	}
	return counter;//returns number of cards
}
void Pause_Game() {//offers a break so user is not confused by everything that is being printed
	printf("\n\n\n~~~~~~~Press Enter to Continue~~~~~~~");
	scanf("%*c");//scanning for the variable 
	printf("\n\n\n");
	return;
}
void print_deck(card* d) {//to be able to print cards horizontally
	int i, j, k, extraLength, num;
	num = deck_size(d);
	card* temp1;
	card* temp2;
	card* temp3;
	temp1 = d;
	temp2 = d;
	temp3 = d;
	for (k = 0; k < num / 13; ++k) {
		for (i = 0; i < 8; ++i) {
			for (j = 0; j < 13; ++j) {
				if ((i == 0) || (i == 7)) {
					printf("--------");
				}
				else if (i == 1) {
					if (temp1->face < 10) {
						printf("|%c%d    |", temp1->suit, temp1->face);
					}
					else if (temp1->face == 100) {
						printf("|      |");
					}
					else {
						if (temp1->face == 10) {
							printf("|%c%d   |", temp1->suit, temp1->face);
						}
						else {
							char face = '-';
							if (temp1->face == 11) {
								face = 'J';
							}
							else if (temp1->face == 12) {
								face = 'Q';
							}
							else if (temp1->face == 13) {
								face = 'K';
							}
							printf("|%c%c    |", temp1->suit, face);
						}
					}
					temp1 = temp1->next;
				}
				else if ((i == 2) || (i == 4) || (i == 5)) {
					printf("|      |");
				}
				else if (i == 3) {
					if (temp2->face == 100) {
						printf("|  J   |");
					}
					else {
						printf("|      |");
					}
					temp2 = temp2->next;
				}
				else if (i == 6) {
					if (temp3->face < 10) {
						printf("|    %c%d|", temp3->suit, temp3->face);
					}
					else if (temp3->face == 100) {
						printf("|      |");
					}
					else {
						if (temp3->face == 10) {
							printf("|   %c%d|", temp3->suit, temp3->face);
						}
						else {
							char face = '-';
							if (temp3->face == 11) {
								face = 'J';
							}
							else if (temp3->face == 12) {
								face = 'Q';
							}
							else if (temp3->face == 13) {
								face = 'K';
							}
							printf("|    %c%c|", temp3->suit, face);
						}
					}
					temp3 = temp3->next;
				}
			}
			printf("\n");
		}
	}
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < num % 13; ++j) {
			if ((i == 0) || (i == 7)) {
				printf("--------");
			}
			else if (i == 1) {
				if (temp1->face < 10) {
					printf("|%c%d    |", temp1->suit, temp1->face);
				}
				else if (temp1->face == 100) {
					printf("|      |");
				}
				else {
					if (temp1->face == 10) {
						printf("|%c%d   |", temp1->suit, temp1->face);
					}
					else {
						char face = '-';
						if (temp1->face == 11) {
							face = 'J';
						}
						else if (temp1->face == 12) {
							face = 'Q';
						}
						else if (temp1->face == 13) {
							face = 'K';
						}
						printf("|%c%c    |", temp1->suit, face);
					}
				}
				temp1 = temp1->next;
			}
			else if ((i == 2) || (i == 4) || (i == 5)) {
				printf("|      |");
			}
			else if (i == 3) {
				if (temp2->face == 100) {
					printf("|  J   |");
				}
				else {
					printf("|      |");
				}
				temp2 = temp2->next;
			}
			else if (i == 6) {
				if (temp3->face < 10) {
					printf("|    %c%d|", temp3->suit, temp3->face);
				}
				else if (temp3->face == 100) {
					printf("|      |");
				}
				else {
					if (temp3->face == 10) {
						printf("|   %c%d|", temp3->suit, temp3->face);
					}
					else {
						char face = '-';
						if (temp3->face == 11) {
							face = 'J';
						}
						else if (temp3->face == 12) {
							face = 'Q';
						}
						else if (temp3->face == 13) {
							face = 'K';
						}
						printf("|    %c%c|", temp3->suit, face);
					}
				}
				temp3 = temp3->next;
			}
		}
		printf("\n");
	}
}
void print_computer(card *d) {
	card*temp = d;
	int counter = 1;
	while (temp != NULL) {// traverses the list
		printf("%d ", counter);//printing numbers the user can choose from
		++counter;//for what number to print
		temp = temp->next;
	}
	printf("\n");
}

card* delete_card(card** c) {//we want to get rid of the card c from the deck
	card*temp, *temp2 = *c;
	temp = (*c);//have temp equal to the card
	if ((*c)->previous == NULL && (*c)->next == NULL) {
		temp2 = NULL;

	}
	if ((*c)->previous != NULL) {//if the card is in the middle of the list
		if ((*c)->next != NULL) {
			((*c)->previous)->next = (*c)->next;
			((*c)->next)->previous = (*c)->previous;
			(temp2) = (*c)->next;
		}
		else {
			(*c)->previous->next = NULL;//if the card is at the end of the list
			(temp2) = (*c)->previous;
		}


	}
	else {
		temp2 = (*c)->next;// if the card is at the beginning of the list
		if ((*c)->next == NULL) {
			temp2 = NULL;
		}
		else {
			(temp2)->previous = NULL;
		}
	}
	free(temp);

	return temp2;
}
void print_removed(card* c1, card* c2) {
	char face1 = '-';
	char face2 = '-';
	if ((c1->face > 10) || (c2->face > 10)) {
		if ((c1->face > 10) && (c2->face > 10)) {
			if (c1->face == 11) {
				face1 = 'J';
			}
			else if (c1->face == 12) {
				face1 = 'Q';
			}
			else if (c1->face == 13) {
				face1 = 'K';
			}
			if (c2->face == 11) {
				face2 = 'J';
			}
			else if (c2->face == 12) {
				face2 = 'Q';
			}
			else if (c2->face == 13) {
				face2 = 'K';
			}
			printf("Remove Pairs: %c%c %c%c\n", face1, c1->suit, face2, c2->suit);
		}
		else {
			if (c1->face == 11) {//To print the faces when we print the pairs removed
				printf("Remove Pairs: J%c %d%c\n", c1->suit, c2->face, c2->suit);
			}
			else if (c1->face == 12) {
				printf("Remove Pairs: Q%c %d%c\n", c1->suit, c2->face, c2->suit);
			}
			else if (c1->face == 13) {
				printf("Remove Pairs: K%c %d%c\n", c1->suit, c2->face, c2->suit);
			}
			else if (c2->face == 11) {
				printf("Remove Pairs: %d%c J%c\n", c1->face, c1->suit, c2->suit);
			}
			else if (c2->face == 12) {
				printf("Remove Pairs: %d%c Q%c\n", c1->face, c1->suit, c2->suit);
			}
			else if (c2->face == 13) {
				printf("Remove Pairs: %d%c K%c\n", c1->face, c1->suit, c2->suit);
			}
		}
	}
	else {
		printf("Remove Pairs: %d%c %d%c\n", c1->face, c1->suit, c2->face, c2->suit);
	}
}
void match_card(card** deck) {
	card* temp1;
	card* temp2;
	int counter = 0;
	temp1 = *deck;
	temp2 = (*deck)->next;
	int num = 0;
	num = deck_size(*deck);
	if (num == 2 && (temp1->face == temp2->face)) {//If there are only 2 cards in the deck and they match the deck is NULL
		*deck = NULL;
		temp1 = NULL;
		temp2 = NULL;
		return;
	}


	while (temp1 != NULL) {//traverses through the list once
		counter = 0;
		while (temp2 != NULL) {//goes through the list everytime temp 1 is updated
			if (temp1 == NULL) {
				break;
			}
			if (temp1->face == temp2->face && temp1->suit != temp2->suit) {//if they have the same face value but they are not the same cards
				print_removed(temp1, temp2);
				temp2 = delete_card(&temp2);//deleting the card from the list
				if (temp2 == temp1) {
					temp2 = *deck;
				}

				temp1 = delete_card(&temp1);//deleting the card from the list
				if (temp1->previous == NULL) {//if the card is the first card
					*deck = temp1;//changing where the head pointer is

				}

				++counter;//counting if there was a match
				break;
			}
			else {
				temp2 = temp2->next;//traverse through list
			}
		}
		if (counter == 0) {
			temp1 = temp1->next;// if there was no matches
		}
		temp2 = temp1;//starting temp2 at temp1 so cards are not checked repeatedly
	}
}
void add_card(card **c, card **deck, card **secondDeck) {
	card* cardToAdd = (card*)malloc(sizeof(card));//Juat saving the values of the card
	cardToAdd->face = (*c)->face;
	cardToAdd->suit = (*c)->suit;
	cardToAdd->next = NULL;
	cardToAdd->previous = NULL;


	if (*deck == NULL) {
		*deck = cardToAdd;//if the deck if null
	}
	else {
		card* temp = *deck;
		while (temp->next != NULL) {//getting to the end of deck
			temp = temp->next;
		}
		temp->next = cardToAdd;//adding the card to the end of the list
		cardToAdd->previous = temp;//connecting it to the previous term
		cardToAdd->next = NULL;//setting next to NULL
	}
	if (*c == *secondDeck) {
		if ((*secondDeck)->next == NULL) {
			*secondDeck = NULL;
		}
		*secondDeck = (*c)->next;//if it belong to the second cards deck'd hdpt we wan to make sure that the headpt is moved
	}

	*c = delete_card(c);//deleting the card from the original deck;


}
int check_win(card* deck) {
	if (deck == NULL) {//if the list in null then we have a winner
		return 100;
	}
	else {
		return 200;
	}
}

int main(void) {
	srand((int)time(0));
	int computer, player, userChoice, computerChoice, win = 0;
	char userName[50], userAnswer = ' ';
	card *deck, *playerdeck = NULL, *computerdeck = NULL, *temp, *temp2;

	while (userAnswer != 'q') {
		deck = create_Deck();
		temp = (card*)malloc(sizeof(card));//for adding the card
		playerdeck = (card*)malloc(sizeof(card));//the players deck
		computerdeck = (card*)malloc(sizeof(card));//the computers deck
		print_deck(deck);//Printing out the created linked list
		Pause_Game();
		shuffle(deck, 53);
		print_deck(deck);//Printing the shuffled linked list
		Pause_Game();
		deal_Cards(&deck, &playerdeck, &computerdeck);//dealing the cards to the players


		printf("Enter your name:");
		fgets(userName, 50, stdin);
		printf("Hello ");
		for (int i = 0; i < strlen(userName) - 1; ++i) {
			printf("%c", userName[i]);
		}
		printf(" Let's Play Joker\n\n\n");


		player = deck_size(playerdeck);//getting the sizes of each deck
		computer = deck_size(computerdeck);


		for (int i = 0; i < strlen(userName) - 1; ++i) {
			printf("%c", userName[i]);
		}
		printf(", you have %d cards\n", player);
		print_deck(playerdeck);
		Pause_Game();



		//Match and Delete for computer
		printf("dealer's hand\n");
		print_deck(computerdeck);
		Pause_Game();


		printf("Dealer's Hand Matched Pairs:\n");
		match_card(&computerdeck);
		computer = deck_size(computerdeck);//state the number of cards that the computer has after removing the pairs
		printf("I have %d cards now\n", computer);
		print_deck(computerdeck);
		Pause_Game();




		//Match and Delete for player
		for (int i = 0; i < strlen(userName) - 1; ++i) {
			printf("%c", userName[i]);
		}
		printf("'s Hand Matched Pairs:\n");
		//print deleted pairs
		match_card(&playerdeck);
		//show the players deck after deletion
		player = deck_size(playerdeck);

		print_deck(playerdeck);
		Pause_Game();





		if (player > computer) {//determine who has more cards
			for (int i = 0; i < strlen(userName) - 1; ++i) {
				printf("%c", userName[i]);
			}
			printf(" you have more cards, you start\n");
			while (win != 100) {
				printf("I have %d cards now\n", computer);
				shuffle(computerdeck, computer);
				print_computer(computerdeck);
				printf("Which one of my cards do you want to choose (1-%d)?", computer);
				scanf("%d%*c", &userChoice);
				while (userChoice == 0 || userChoice > computer) {//if the user picks a card I do not have
					printf("I have ONLY %d cards\n", computer);
					printf("Which one of my cards do you want to choose (1-%d)?", computer);
					scanf("%d%*c", &userChoice);
				}

				temp = find_card(computerdeck, (userChoice - 1));//finding the card
																 //add temp to player deck
				add_card(&temp, &playerdeck, &computerdeck);
				//check player deck for matches

				match_card(&playerdeck);//checking if the added card is a match


				win = check_win(playerdeck);//checking if someone won
				if (win == 100) {
					printf("You win, I am the joker\n");
					break;
				}
				win = check_win(computerdeck);
				if (win == 100) {
					printf("I win, You are the joker\n");
					break;
				}
				player = deck_size(playerdeck);//printing out the player deck (shuffled)
				shuffle(playerdeck, player);
				print_deck(playerdeck);


				//The computers turn to choose from player deck

				computerChoice = (rand() % player);

				printf("I choose card #%d from your deck\n", computerChoice + 1);
				temp = find_card(playerdeck, computerChoice);
				//add temp to computer deck
				add_card(&temp, &computerdeck, &playerdeck);
				//check computer deck for matches
				match_card(&computerdeck);
				win = check_win(computerdeck);
				if (win == 100) {//checking for win
					printf("I win, You are the Joker\n");
					break;
				}
				win = check_win(playerdeck);
				if (win == 100) {
					printf("\nYou win, I am the joker\n");
					break;
				}

				computer = deck_size(computerdeck);
				printf("I have %d cards now\n", computer);
				for (int i = 0; i < strlen(userName) - 1; ++i) {
					printf("%c", userName[i]);
				}
				printf(" this is your hand\n");
				print_deck(playerdeck);
				Pause_Game();

				//Repeat!
			}

		}





		else {
			printf("You have less cards, so I will start\n");//Same as above but the computer starts instead of the user
			while (win != 100) {
				computerChoice = (rand() % player);

				printf("I choose card #%d from your deck\n", computerChoice + 1);
				temp = find_card(playerdeck, computerChoice);
				//add temp to computer deck
				add_card(&temp, &computerdeck, &playerdeck);
				//check computer deck for matches
				match_card(&computerdeck);


				computer = deck_size(computerdeck);
				printf("I have %d cards now\n", computer);


				win = check_win(computerdeck);
				if (win == 100) {
					printf("I win, You are the Joker\n");
				}
				win = check_win(playerdeck);
				if (win == 100) {
					printf("You win, I am the joker\n");
					break;
				}
				for (int i = 0; i < strlen(userName) - 1; ++i) {
					printf("%c", userName[i]);
				}
				printf(" this is your hand\n");
				print_deck(playerdeck);
				Pause_Game();
				shuffle(computerdeck, computer);
				print_computer(computerdeck);
				printf("Which one of my cards do you want to choose (1-%d)?", computer);
				scanf("%d%*c", &userChoice);
				while (userChoice == 0 || userChoice > computer) {
					printf("I have ONLY %d cards\n", computer);
					printf("Which one of my cards do you want to choose (1-%d)?", computer);
					scanf("%d%*c", &userChoice);
				}

				temp = find_card(computerdeck, (userChoice - 1));
				//add temp to player deck
				add_card(&temp, &playerdeck, &computerdeck);
				//check player deck for matches
				match_card(&playerdeck);


				win = check_win(playerdeck);
				if (win == 100) {
					printf("You win, I am the joker\n");
					break;
				}
				win = check_win(computerdeck);
				if (win == 100) {
					printf("I win, You are the joker\n");
					break;
				}
				player = deck_size(playerdeck);
				shuffle(playerdeck, player);
				print_deck(playerdeck);

			}
		}
		printf("Do you want to play another Game (q to quit)");
		scanf(" %c%*c", &userAnswer);
		win = 0;
	}
}