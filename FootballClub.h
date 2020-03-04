#ifndef FOOTBALL_CLUB_H_D
#define FOOTBALL_CLUB_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// List node which contains information about one football player.
typedef struct Player {
	char *name;					// player's name
	char *position;				// player's game position
	int score;					// player's score
	int injured;				// indicator for injury (1 true, 0 false)
	struct Player *next;		// next list node
	struct Player *prev;		// previous list node
} Player;

// Structure which contains information about one football club.
typedef struct FootballClub {
	char *name;					// club's name
	Player *players;			// list with players in good shape
	Player *injured_players;	// list with injured players
	struct FootballClub *next;	// next list node
} FootballClub;

void add_injury(FootballClub *clubs, char *club_name,
		char *player_name, int days_no);

FootballClub *add_club(FootballClub *clubs, char *name) {
	FootballClub* newClub = NULL;
	newClub = (FootballClub*)malloc(sizeof(FootballClub));
	newClub->name=(char*)malloc((strlen(name)+1)*sizeof(char));
	strcpy(newClub->name,name);
	newClub->players=NULL;
	newClub->injured_players=NULL;
	newClub->next = NULL;
	FootballClub *p = clubs;
	if(p == NULL) {
		clubs = newClub;
	} else{
		while(p->next != NULL)
			p = p->next;
		p->next = newClub;
	}
	return clubs;
}

FootballClub *initialize_clubs(int clubs_no, char **names) { 
	FootballClub *clubs = NULL;
	int i;
	for(i = 0; i < clubs_no; i++) 
		clubs = add_club(clubs, names[i]);
	return clubs;
}

void add_player(FootballClub *clubs, char *club_name, 
		char *player_name, char *position, int score) {
	//daca nu obtin corect pe undeva mai trebuie umblat pe la conditii					
	Player* jucator=(Player*)malloc(sizeof(Player));		
	jucator->name=(char*)malloc((strlen(player_name)+1)*sizeof(char));
	jucator->position=(char*)malloc((strlen(position)+1)*sizeof(char));
	jucator->score=score;
	jucator->next=NULL;
	jucator->prev=NULL;
	jucator->injured=0;
	strcpy(jucator->position,position);
	strcpy(jucator->name,player_name);
	FootballClub *p;
	p=clubs;
	//verific daca nu exista clubul
	while(p!=NULL) {
		if (strcmp(p->name, club_name) == 0) {
			break;
		}
		p = p->next;
	}
	/*if(p->next!=NULL)
	  p=p->next;
	  else if(p->next==NULL && strcmp(p->name,club_name)!=0 )
	  return;
	  else if(p->next==NULL && strcmp(p->name,club_name)==0)
	  p=p->next;*/
	if(p==NULL){	
		return;
	}

	//daca nu exista jucatori in echipa adaug jucatorul ;
	if(p->players==NULL){
		p->players=jucator;
		return;
	}
	//daca exista elemente si acesta trebuie puse fix la inceput 
	if(strcmp(p->players->position,jucator->position)>0) {	
		jucator->next=p->players;
		p->players->prev=jucator;
		p->players=jucator;
		return;
	}
	else if(strcmp(p->players->position,jucator->position)==0) {
		if(p->players->score < jucator->score){
			jucator->next=p->players;
			p->players->prev=jucator;
			p->players=jucator;
			return;
		} else if (p->players->score==jucator->score) {
			if(strcmp(p->players->name,jucator->name)>0) {
				jucator->next=p->players;
				p->players->prev=jucator;
				p->players=jucator;
				return;
			}
		}
	}
	
	//cazul in care jucatorul trebuie introdus la mijloc 
	//reactualizez p pentru ca pionta la ultimul player si nu la primul
	Player *p1=p->players;
	while(p1->next!=NULL){
		if (strcmp(p1->position, jucator->position) > 0) {
			jucator->next=p1;
			jucator->prev=p1->prev;
			p1->prev=jucator;
			if (jucator->prev) {
				jucator->prev->next = jucator;
			}
			return;
		} else if (strcmp(p1->position, jucator->position) == 0) {
			if (p1->score < jucator->score) {
				jucator->next=p1;
				jucator->prev=p1->prev;
				p1->prev=jucator;
				if (jucator->prev) {
					jucator->prev->next = jucator;
				}
				return;
			} else if (p1->score == jucator->score) {
				if (strcmp(p1->name, jucator->name) >= 0) {
					jucator->next=p1;
					jucator->prev=p1->prev;
					p1->prev=jucator;
					if (jucator->prev) {
						jucator->prev->next = jucator;
					}
					return;
				}
			}
		}
		p1 = p1->next;
	}
	if (strcmp(p1->position, jucator->position) > 0) {
		jucator->next=p1;
		jucator->prev=p1->prev;
		p1->prev=jucator;
		if (jucator->prev) {
			jucator->prev->next = jucator;
		}
		return;
	} else if (strcmp(p1->position, jucator->position) == 0) {
		if (p1->score < jucator->score) {
			jucator->next=p1;
			jucator->prev=p1->prev;
			p1->prev=jucator;
			if (jucator->prev) {
				jucator->prev->next = jucator;
			}
			return;
		} else if (p1->score == jucator->score) {
			if (strcmp(p1->name, jucator->name) >= 0) {
				jucator->next=p1;
				jucator->prev=p1->prev;
				p1->prev=jucator;
				if (jucator->prev) {
					jucator->prev->next = jucator;
				}
				return;
			}
		}
	}
	p1->next = jucator;
	jucator->prev = p1;
}

void transfer_player(FootballClub *clubs, char *player_name, 
		char *old_club, char *new_club) {
	FootballClub *club1=clubs,*club2=clubs;
	while( club1!=NULL && strcmp(club1->name,old_club)!=0  )
		club1=club1->next;
	while(club2!=NULL && strcmp(club2->name,new_club)!=0  )
		club2=club2->next;
	//acum ma duc sa caut jucatorul;
	Player *Headlist, *Headlistj;
	Headlist=club1->players;
	Headlistj=club1->injured_players;
	while( Headlist!=NULL && strcmp(Headlist->name,player_name)!=0 )
		Headlist=Headlist->next;
	while( Headlistj!=NULL && strcmp(Headlistj->name,player_name)!=0 )
		Headlistj=Headlistj->next;

	if(Headlist ==NULL && Headlistj==NULL)
		return;
	if(Headlist==NULL)
		Headlist=Headlistj;

	add_player(clubs,club2->name ,Headlist->name,Headlist->position ,Headlist->score);

	if (Headlistj) {
		add_injury(clubs, new_club, player_name, 0);
	}

	if (Headlist == club1->players) {
		club1->players = club1->players->next;
	} else if (Headlist == club1->injured_players) {
		club1->injured_players = club1->injured_players->next;
	}
	if (Headlist->next) {
		Headlist->next->prev = Headlist->prev;
	}
	if (Headlist->prev) {
		Headlist->prev->next = Headlist->next;
	}
	return; // <----------------------------------------------
	//jucatorul trebuie sters din vechea echipa
	//cazul cand e primul
	if(club1->players->prev==NULL  && strcmp(club1->players->name,player_name)==0)
	{
		int ok=0;
		Player* player_dezaloc=club1->players;
		//pentru cazul in care exista doar un element
		if(club1->players->next!=NULL)
		{
			club1->players=club1->players->next;
			ok=1;
		}
		club1->players->prev=NULL;
		player_dezaloc->next=NULL;
		free(player_dezaloc->name);
		free(player_dezaloc->position);
		free(player_dezaloc);
		if(ok!=1)
			club1->players=NULL;
		else
			player_dezaloc=NULL;
		if(club1->players!=NULL && club1!=NULL)
			while(club1->players->prev!=NULL)
				club1->players=club1->players->prev;
		return;
	}
	while(club1->players->next!=NULL)
		club1->players=club1->players->next;
	//cazul cand e ultimul
	if(club1->players->next==NULL && strcmp(club1->players->name,player_name)==0)
	{	
		Player* player_dezaloc=club1->players;
		int ok=0;
		//pentru cazul cand ultimul coincide cu primul;
		if(club1->players->prev!=NULL)
		{
			club1->players=club1->players->prev;
			ok=1;
		}

		club1->players->next=NULL;
		player_dezaloc->prev=NULL;
		free(player_dezaloc->name);
		free(player_dezaloc->position);
		free(player_dezaloc);
		if(ok!=1)
			club1->players=NULL;
		else
			player_dezaloc=NULL;
		while(club1->players->prev!=NULL)
			club1->players=club1->players->prev;
		return;
	}
	//cazul cand e in interior
	if(club1->players!=NULL){
		if(Headlist->prev != NULL){
			Headlist=Headlist->prev;
			Player* player_dezaloc=Headlist->next;
			Headlist->next=Headlist->next->next;
			Headlist->next->prev=Headlist->next->prev->prev;
			player_dezaloc->next=NULL;
			player_dezaloc->prev=NULL;
			free(player_dezaloc->name);
			free(player_dezaloc->position);
			free(player_dezaloc);
			player_dezaloc=NULL;
			while(club1->players->prev!=NULL)
				club1->players=club1->players->prev;
			return;
		}
	}
}

void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
	FootballClub *club=clubs;
	//am gasit clubul
	if(club->next==NULL && strcmp(club->name,club_name)!=0)
		return;
	while(club!=NULL && strcmp(club->name,club_name)!=0)
		if(club->next!=NULL)
			club=club->next;
		else	if(club->next==NULL && strcmp(club->name,club_name)!=0)
			return;
		else if(club->next==NULL && strcmp(club->name,club_name)==0)
			club=club->next;
	//caut jucator
	if(club==NULL)
		return;
	Player *headlist=club->players;
	while(club!=NULL && headlist!=NULL && strcmp(headlist->name,player_name)!=0 )
		headlist=headlist->next;

	if (headlist==NULL)
	{	
		headlist=club->injured_players;
		while(club!=NULL && headlist!=NULL && strcmp(headlist->name,player_name)!=0 )
			headlist=headlist->next;
	}

	if(headlist==NULL)
		return;

	if(club->players!=NULL && club!=NULL){
		//cazul cand e primul
		if(club->players->prev==NULL  && strcmp(club->players->name,player_name)==0){
			int ok=0;
			Player* player_dezaloc=club->players;
			//pentru cazul in care primul coincide cu ultimul
			if(club->players->next!=NULL)
			{
				club->players=club->players->next;
				ok=1;
			}

			club->players->prev=NULL;
			player_dezaloc->next=NULL;
			free(player_dezaloc->name);
			free(player_dezaloc->position);
			free(player_dezaloc);
			if(ok!=1)
				club->players=NULL;
			else
				player_dezaloc=NULL;
			return;
		}
		while(club->players->next!=NULL)
			club->players=club->players->next;

		//cazul cand e ultimul
		if(club->players->next==NULL && strcmp(club->players->name,player_name)==0)
		{
			Player* player_dezaloc=club->players;
			int ok=0;
			//pentru cazul cand ultimul coincide cu primul;
			if(club->players->prev!=NULL)
			{
				club->players=club->players->prev;
				ok=1;
			}

			club->players->next=NULL;
			player_dezaloc->prev=NULL;
			free(player_dezaloc->name);
			free(player_dezaloc->position);
			free(player_dezaloc);
			if(ok!=1)
				club->players=NULL;
			else
				player_dezaloc=NULL;
			while(club->players->prev!=NULL)
				club->players=club->players->prev;
			return;
		}
		//cazul cand e in interior
		while(club->players->prev!=NULL)
			club->players=club->players->prev;

		if(club->players!=NULL)
		{
			headlist=headlist->prev;
			Player* player_dezaloc=headlist->next;
			headlist->next=headlist->next->next;
			headlist->next->prev=headlist->next->prev->prev;
			player_dezaloc->next=NULL;
			player_dezaloc->prev=NULL;
			free(player_dezaloc->name);
			free(player_dezaloc->position);
			free(player_dezaloc);
			player_dezaloc=NULL;
			return;
		}
	}
	//iar acum caut in lista de accidentati
	while(club!=NULL && club->injured_players!=NULL && 
			strcmp(club->injured_players->name,player_name)!=0 )
		club->injured_players=club->injured_players->next;
	if(club->injured_players!=NULL && club!=NULL){
		//cazul cand e primul
		if(club->injured_players->prev==NULL)
		{
			int ok=0;
			Player* player_dezaloc=club->injured_players;
			//pentru cazul in care primul coincide cu ultimul
			if(club->injured_players->next!=NULL)
			{	
				club->injured_players=club->injured_players->next;
				ok=1;
			}

			club->injured_players->prev=NULL;
			player_dezaloc->next=NULL;
			free(player_dezaloc->name);
			free(player_dezaloc->position);
			free(player_dezaloc);
			if(ok!=1)
				club->injured_players=NULL;
			else
				player_dezaloc=NULL;
			return;
		}


		//cazul cand e ultimul
		if(club->injured_players->next==NULL)
		{	
			Player* player_dezaloc=club->injured_players;
			int ok=0;
			//pentru cazul cand ultimul coincide cu primul;
			if(club->injured_players->prev!=NULL)
			{
				club->injured_players=club->injured_players->prev;
				ok=1;
			}

			club->injured_players->next=NULL;
			player_dezaloc->prev=NULL;
			free(player_dezaloc->name);
			free(player_dezaloc->position);
			free(player_dezaloc);
			if(ok!=1)
				club->injured_players=NULL;
			else
				player_dezaloc=NULL;
			return;
		}
		//cazul cand e in interior

		if(club->injured_players->next!=NULL && club->injured_players->prev!=NULL)
		{	
			//printf("la mijloc");
			club->injured_players=club->injured_players->prev;
			Player* player_dezaloc=club->injured_players->next;
			club->injured_players->next=club->injured_players->next->next;
			club->injured_players->next->prev=club->injured_players->next->prev->prev;
			player_dezaloc->next=NULL;
			player_dezaloc->prev=NULL;
			free(player_dezaloc->name);
			free(player_dezaloc->position);
			free(player_dezaloc);
			player_dezaloc=NULL;
			return;
		}
	}
}

void update_score(FootballClub *clubs, char *club_name, 
		char *player_name, int score) {
	FootballClub *club=clubs;
	//am gasit clubul
	while(strcmp(club->name,club_name)!=0 && club!=NULL )
		club=club->next;
	//caut jucator
	Player* listHead = club->players;
	while(listHead!=NULL && strcmp(listHead->name,player_name)!=0 )
		listHead = listHead->next;
	if (listHead != NULL)
	{
		char nume[255],pozitie[255];
		strcpy(nume,listHead->name);
		strcpy(pozitie,listHead->position);

		remove_player(clubs, club_name, player_name);
		add_player(clubs, club_name, nume, pozitie,score);
	}
	else
	{
		Player* listHead = club->injured_players;
		while(listHead!=NULL && strcmp(listHead->name,player_name)!=0 )
			listHead = listHead->next;
		if(listHead ==NULL)
			return;	
		listHead->score=score;
	}
}	

void update_game_position(FootballClub *clubs, char *club_name, 
		char *player_name, char *position, int score) {
	FootballClub *club=clubs;
	//am gasit clubul
	while(club!=NULL  && strcmp(club->name,club_name)!=0 )
		club = club->next;
	//caut jucator
	Player* listHead = club->players;
	while(listHead!=NULL && strcmp(listHead->name,player_name)!=0 )	
		listHead = listHead->next;
	if(listHead != NULL)
	{
		char nume[255];
		strcpy(nume,listHead->name);
		remove_player(clubs,club->name, listHead->name);	
		add_player(clubs, club->name, nume, position, score);
	}
	else
	{
		Player* listHead = club->injured_players;
		while(listHead!=NULL && strcmp(listHead->name,player_name)!=0 )	
			listHead = listHead->next;
		if(listHead == NULL) return;
		free(listHead->position);
		listHead->position = (char*)malloc((strlen(position) + 1)*sizeof(char));
		strcpy(listHead->position, position);
		listHead->score=score;

	}
}

void add_injury(FootballClub *clubs, char *club_name,
		char *player_name, int days_no) {
	FootballClub *club=clubs;
	//am gasit clubul
	while(strcmp(club->name,club_name)!=0 && club!=NULL )
		club=club->next;
	//caut jucator
	Player *headList;
	headList=club->players;
	while(headList!=NULL && strcmp(headList->name,player_name)!=0)
		headList=headList->next;	
	if(headList==NULL)
		return;

	if (headList == club->players) {
		club->players = club->players->next;
	}
	if (headList->next) {
		headList->next->prev = headList->prev;
	}
	if (headList->prev) {
		headList->prev->next = headList->next;
	}

	Player* jucator=(Player*)malloc(sizeof(Player));		
	jucator->name=(char*)malloc((strlen(headList->name)+1)*sizeof(char));
	jucator->position=(char*)malloc((strlen(headList->position)+1)*sizeof(char));
	jucator->score=(headList->score - 0.1*days_no);
	if(jucator->score<-100)
		jucator->score=-100;
	if(jucator->score>100)
		jucator->score=100;
	jucator->next=NULL;
	jucator->prev=NULL;
	jucator->injured=1;
	strcpy(jucator->name,headList->name);
	strcpy(jucator->position,headList->position);
	//elimin jucatorul accidentatdin lista players
	remove_player(clubs,club->name, headList->name);	
	//daca nu exista jucatori in echipa adaug jucatorul ;
	if(club->injured_players==NULL)
	{
		club->injured_players=jucator; 
		return;
	}

	//la inceput
	if(strcmp(club->injured_players->name,jucator->name)>0) 
	{	
		jucator->next=club->injured_players;
		club->injured_players->prev=jucator;
		club->injured_players=jucator;
		return;
	}
	//La final
	while(club->injured_players->next!=NULL)
		club->injured_players=club->injured_players->next;

	if(strcmp(club->injured_players->name,jucator->name)<0) 
	{	
		jucator->prev=club->injured_players;
		club->injured_players->next=jucator;
		while(club->injured_players->prev!=NULL)
			club->injured_players=club->injured_players->prev;
		return;}
	//la mijloc

	while(club->injured_players->prev!=NULL)
		club->injured_players=club->injured_players->prev;

	Player *p1=club->injured_players;//cazul de dupa
	Player *p2=club->injured_players->next;//cazul din fata
	while(p2!=NULL){
		if(strcmp(p1->name,jucator->name)<=0 && strcmp(p2->name,jucator->name)>=0)
		{
			jucator->next=p2;
			p2->prev=jucator;
			p1->next=jucator;
			jucator->prev=p1;
			while(club->injured_players->prev!=NULL)
				club->injured_players=club->injured_players->prev;
			return;
		}
	}
}

void recover_from_injury(FootballClub *clubs, char *club_name, 
		char *player_name) {
	FootballClub *club=clubs;
	//am gasit clubul
	while(strcmp(club->name,club_name)!=0 && club!=NULL )
		club=club->next;
	//caut jucator
	while( club->injured_players!=NULL && strcmp(club->injured_players->name,player_name)!=0 )
		club->injured_players=club->injured_players->next;
	if(club->injured_players==NULL)
		return;
	add_player(clubs, club_name, player_name, club->injured_players->position, 
			club->injured_players->score);
	//cazul cand e primul
	if(club->injured_players->prev==NULL)
	{
		int ok=0;
		Player* player_dezaloc=club->injured_players;
		//pentru cazul in care primul coincide cu ultimul
		if(club->injured_players->next!=NULL)
		{
			club->injured_players=club->injured_players->next;
			ok=1;
		}

		club->injured_players->prev=NULL;
		player_dezaloc->next=NULL;
		free(player_dezaloc->name);
		free(player_dezaloc->position);
		free(player_dezaloc);
		if(ok!=1)
			club->injured_players=NULL;
		else
			player_dezaloc=NULL;
		return;
	}

	//cazul cand e ultimul
	if(club->injured_players->next==NULL)
	{	
		Player* player_dezaloc=club->injured_players;
		int ok=0;
		//pentru cazul cand ultimul coincide cu primul;
		if(club->injured_players->prev!=NULL)
		{
			club->injured_players=club->injured_players->prev;
			ok=1;
		}
		club->injured_players->next=NULL;
		player_dezaloc->prev=NULL;
		free(player_dezaloc->name);
		free(player_dezaloc->position);
		free(player_dezaloc);
		if(ok!=1)
			club->injured_players=NULL;
		else
			player_dezaloc=NULL;
		return;
	}
	//cazul cand e in interior
	if(club->injured_players->next!=NULL && club->injured_players->prev!=NULL)
	{
		club->injured_players=club->injured_players->prev;
		Player* player_dezaloc=club->injured_players->next;
		club->injured_players->next=club->injured_players->next->next;
		club->injured_players->next->prev=club->injured_players->next->prev->prev;
		player_dezaloc->next=NULL;
		player_dezaloc->prev=NULL;
		free(player_dezaloc->name);
		free(player_dezaloc->position);
		free(player_dezaloc);
		player_dezaloc=NULL;
		return;
	}
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player) {

	Player *dezaloc1,*dezaloc2;
	dezaloc1=player;
	while(dezaloc1 != NULL)
	{
		dezaloc2=dezaloc1->next;
		free(dezaloc1->name);
		free(dezaloc1->position);
		free(dezaloc1);
		dezaloc1=dezaloc2;
	}
	player=NULL;

}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
	FootballClub *dezaloc1,*dezaloc2;
	dezaloc1=clubs;
	while(dezaloc1 != NULL)
	{
		dezaloc2=dezaloc1->next;
		free(dezaloc1->name);
		destroy_player_list(dezaloc1->players);
		destroy_player_list(dezaloc1->injured_players);
		free(dezaloc1);
		dezaloc1=dezaloc2;
	}
	clubs=NULL;

}

// Displays a list of players.
void show_list(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	while (player) {
		fprintf(f, "(%s, %s, %d, %c) ", 
				player->name,
				player->position,
				player->score,
				player->injured ? 'Y' : '_');
		player = player->next;
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}

// Displays a list of players in reverse.
void show_list_reverse(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;

	if (player) {
		while (player->next) {
			player = player->next;
		}
		while (player) {
			fprintf(f, "(%s, %s, %d, %c) ", 
					player->name,
					player->position,
					player->score,
					player->injured ? 'Y' : '_');
			player = player->prev;
		}
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}


// Displays information about a football club.
void show_clubs_info(FILE *f, FootballClub *clubs) {
	fprintf(f, "FCs:\n");
	while (clubs) {
		fprintf(f, "%s\n", clubs->name);
		fprintf(f, "\t");
		show_list(f, clubs->players, 0);
		fprintf(f, "\t");
		show_list(f, clubs->injured_players, 0);
		clubs = clubs->next;
	}
}

#endif // FOOTBALL_CLUB_H_INCLUDED
