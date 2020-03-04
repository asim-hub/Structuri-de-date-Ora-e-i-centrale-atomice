
#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"


Player *union_teams(FootballClub *clubs, char *club_A, char *club_B) {
	FootballClub *club=clubs;
	FootballClub *aux=(FootballClub*)malloc(sizeof(FootballClub));
	aux->players=NULL;	
	aux->name=(char*)malloc(4*sizeof(char));
 	strcpy(aux->name,"new");
	 
	while(strcmp(club->name,club_A)!=0 && club != NULL)
	{
		club=club->next;	
	}
	Player *p=club->players;
	if(club!=NULL)
	while(p!= NULL)
	{
		add_player(aux,"new",p->name, p->position, p->score);
		p=p->next;
	}
	club=clubs;
	while(strcmp(club->name,club_B)!=0 && club != NULL)
	{
		club=club->next;	
	}
	p=club->players;
	if(club!=NULL)
		while(p!= NULL)
		{
			add_player(aux,"new",p->name, p->position, p->score);
			p=p->next;
		}
	
	return aux->players;
	
}

Player *get_best_player(FootballClub *clubs, char *position) {
	FootballClub *club=clubs;

	Player* jucator=(Player*)malloc(sizeof(Player));		
    jucator->score=-101;
	jucator->next=NULL;
	jucator->prev=NULL;
	jucator->injured=0;
	jucator->position=(char*)malloc((strlen(position)+1)*sizeof(char));
	jucator->name=(char*)malloc(10*sizeof(char));

	strcpy(jucator->position,position);

	Player *p;

	while(club != NULL)
	{	p=club->players;
 		while(p != NULL)
			{
				if(p->score >jucator->score && strcmp(jucator->position,p->position)==0)
				{
					jucator->score=p->score;
					strcpy(jucator->name,p->name);
				}
				else if(p->score == jucator->score && strcmp(jucator->name,p->name)>0 && strcmp(jucator->position,p->position)==0)
				{
					strcpy(jucator->name,p->name);
				}
				p=p->next;
			}
		club=club->next;
	}
if(jucator->score<-100 || jucator->score>100)
	{
	free(jucator->name);
	free(jucator->position);
	free(jucator);
	jucator=NULL;
	}

	return jucator;
	
}

Player *get_top_players(FootballClub *clubs, int N) {
	int nr=N,ok=1;
	FootballClub *club=clubs;
	FootballClub *aux=NULL;
	aux=(FootballClub*)malloc(sizeof(FootballClub));
	aux->players=NULL;
	aux->injured_players=NULL;	
	aux->name=(char*)malloc(4*sizeof(char));
	strcpy(aux->name,"new");
	Player *p;
	while(club!=NULL)
	{ nr=N;
		
		while(nr>0 && club->players !=NULL)
		{	nr--;	
				
				Player* jucator=(Player*)malloc(sizeof(Player));		
				jucator->score=-101;
				jucator->next=NULL;
				jucator->prev=NULL;
				jucator->injured=0;
				jucator->position=(char*)malloc(10*sizeof(char));
				jucator->name=(char*)malloc(10*sizeof(char));
				ok=0;
				p=club->players;
			
			while(p!=NULL)
			{ok=1;
				if(p->score > jucator->score || (p->score==jucator->score && strcmp(p->name,jucator->name)<0))
				{
					Player *a=aux->players;
					ok=1;
					while(a!=NULL)
					{
						if( strcmp(a->name,p->name)==0 )
							ok=0;
						a=a->next;
					}
					if(ok==1)
					{	
						strcpy(jucator->name,p->name);
						strcpy(jucator->position,p->position);
						jucator->score=p->score;
					}
				  		
			
				}
			p=p->next;
		}
		
		if(aux->players==NULL && ok==1)
		aux->players=jucator;
	else
	if(ok==1 && aux->players!=NULL )
	{	
		jucator->next=aux->players;
		aux->players->prev=jucator;
		aux->players=jucator;
	}
		}
		club=club->next;		
	}
	
//aici incep sa ii ordonez:
	Player *i,*j;
	int scor;
	char num[255];
	char poz[255];
	int stare;
	for(i=aux->players;i->next!=NULL;i=i->next)
		for(j=i->next;j!=NULL;j=j->next)
			if((i->score <j->score) || (i->score==j->score && strcmp(i->name,j->name)>0))
			{strcpy(num,i->name);
			strcpy(poz,i->position);
			scor=i->score;
			stare=i->injured;
			strcpy(i->name,j->name);
			strcpy(i->position,j->position);
			i->score=j->score;
			j->injured=i->injured;
			strcpy(j->name,num);
			strcpy(j->position,poz);
			j->score=scor;
			i->injured=stare;
			}
			
	return aux->players;


}

Player *get_players_by_score(FootballClub *clubs, int score) {

	FootballClub *club=clubs;
	FootballClub *aux=(FootballClub*)malloc(sizeof(FootballClub));
	aux->players=NULL;	
	aux->name=(char*)malloc(4*sizeof(char));
 	strcpy(aux->name,"new");
	 Player *p;
	 while(club!=NULL)
	 {
		p=club->players;
		int ok=1;
		//cazul in care lista de player este nula trec direct la injured
		if(p==NULL && club->injured_players!=NULL)
		{
			p=club->injured_players;
			ok=0;
		}
		while(p!=NULL)
		{
			if(p->score>=score)
			{
				Player* jucator=(Player*)malloc(sizeof(Player));		
				jucator->score=p->score;
				jucator->next=NULL;
				jucator->prev=NULL;
				if(ok==1)
				jucator->injured=0;
				else
				jucator->injured=1;
				jucator->position=(char*)malloc(10*sizeof(char));
				jucator->name=(char*)malloc(10*sizeof(char));
				strcpy(jucator->name,p->name);
				strcpy(jucator->position,p->position);
				if(aux->players == NULL)
				{
					aux->players=jucator;
				}
				else
				{
					jucator->next=aux->players;
					aux->players->prev=jucator;
					aux->players=jucator;	
				}

			 }
			 p=p->next;
			 if(p==NULL && ok>0)
			 {p=club->injured_players;ok--;}
		 }
		 club=club->next;
	 }
	 //ordonez lista:
	Player *i,*j;
	int scor;
	char num[255];
	char poz[255];
	int stare;
	for(i=aux->players;i->next!=NULL;i=i->next)
		for(j=i->next;j!=NULL;j=j->next)
			if((i->score <j->score) || (i->score==j->score && strcmp(i->name,j->name)>0))
			{strcpy(num,i->name);
			strcpy(poz,i->position);
			scor=i->score;
			stare=i->injured;
			strcpy(i->name,j->name);
			strcpy(i->position,j->position);
			i->score=j->score;
			i->injured=j->injured;
			strcpy(j->name,num);
			strcpy(j->position,poz);
			j->score=scor;
			j->injured=stare;
			}
	return aux->players;
}

Player *get_players_by_position(FootballClub *clubs, char *position) {
	FootballClub *club=clubs;
	FootballClub *aux=(FootballClub*)malloc(sizeof(FootballClub));
	aux->players=NULL;	
	aux->name=(char*)malloc(4*sizeof(char));
 	strcpy(aux->name,"new");
	Player *p;
	while(club!=NULL)
	{
		p=club->players;
		int ok=1;
		if(p==NULL && club->injured_players!=NULL)
		{
			ok=0;
			p=club->injured_players;
		}
		while(p!=NULL)
		{
			if(strcmp(p->position,position)==0)
			{
				Player* jucator=(Player*)malloc(sizeof(Player));		
				jucator->score=p->score;
				jucator->next=NULL;
				jucator->prev=NULL;
				if(ok==1)
				jucator->injured=0;
				else
				jucator->injured=1;
				jucator->position=(char*)malloc(10*sizeof(char));
				jucator->name=(char*)malloc(10*sizeof(char));
				strcpy(jucator->name,p->name);
				strcpy(jucator->position,p->position);
				if(aux->players == NULL)
				{
					aux->players=jucator;
				}
				else
				{
					jucator->next=aux->players;
					aux->players->prev=jucator;
					aux->players=jucator;	
				}

			 }
			 p=p->next;
			 if(ok>0 && p==NULL)
			 {p=club->injured_players;ok--;}
		 }
		 club=club->next;
	 }
	//ordonez lista:
	Player *i,*j;
	int scor;
	char num[255];
	int stare;
	if(aux->players != NULL)
	for(i=aux->players;i->next!=NULL;i=i->next)
		for(j=i->next;j!=NULL;j=j->next)
			if((i->score <j->score) || (i->score==j->score && strcmp(i->name,j->name)>0))
			{strcpy(num,i->name);
			scor=i->score;
			stare=i->injured;
			strcpy(i->name,j->name);
			i->score=j->score;
			i->injured=j->injured;
			strcpy(j->name,num);
			j->score=scor;
			j->injured=stare;
			}



	return aux->players;
}

Player *get_best_team(FootballClub *clubs) {
	char position[255];
	Player *p;
	int nr;
	FootballClub *aux=(FootballClub*)malloc(sizeof(FootballClub));
	aux->players=NULL;	
	aux->name=(char*)malloc(4*sizeof(char));
 	strcpy(aux->name,"new");

	strcpy(position,"portar");
	p=get_players_by_position(clubs,position);
	if(p!=NULL)
	p->next=NULL;
	if(p!=NULL)
	{
		aux->players=p;
	}
	Player *q;
	strcpy(position,"fundas");
	p=get_players_by_position(clubs,position);
	nr=3;
	if( p!=NULL )
	{
		while( nr>0 && p->next!=NULL)
	{
		nr--;
		p=p->next;
	}
	p->next=NULL;
	while(p->prev!=NULL)
		p=p->prev;
	q=aux->players;
	if(aux->players==NULL)
		aux->players=p;
	else
	{
		while(q->next!=NULL)
			q=q->next;	
		q->next=p;
		p->prev=q;
	}
	while(q->next!=NULL)
	q=q->next;
	}
	strcpy(position,"mijlocas");
	p=get_players_by_position(clubs,position);
	nr=2;
	if( p!=NULL )
	{
	while(nr>0 && p->next!=NULL)
	{
		nr--;
		p=p->next;
	}
	p->next=NULL;
	while(p->prev!=NULL)
		p=p->prev;
	q=aux->players;
	if(aux->players==NULL)
	aux->players=p;
	else
	{
		while(q->next!=NULL)
			q=q->next;	
		q->next=p;
		p->prev=q;
	}
	while(q->next!=NULL)
	q=q->next;
	}
	nr=2;
	strcpy(position,"atacant");
	p=get_players_by_position(clubs,position);
		if( p!=NULL )
		{
	while(nr>0 && p->next!=NULL)
	{
		nr--;
		p=p->next;
	}
	p->next=NULL;
	while(p->prev!=NULL)
		p=p->prev;
	q=aux->players;
	if(aux->players==NULL)
	aux->players=p;
	else
	{
		while(q->next!=NULL)
			q=q->next;	
		q->next=p;
		p->prev=q;
	}
		}
	
	Player *i,*j;
	int scor;
	char num[255];
	char poz[255];
	int stare;
	if(aux->players!=NULL)
	for(i=aux->players;i->next!=NULL;i=i->next)
		for(j=i->next;j!=NULL;j=j->next)
			if((i->score <j->score) || (i->score==j->score && strcmp(i->name,j->name)>0))
			{	
				strcpy(num,i->name);
				strcpy(poz,i->position);
				scor=i->score;
				stare=i->injured;
				strcpy(i->name,j->name);
				strcpy(i->position,j->position);
				i->score=j->score;
				i->injured=j->injured;
				strcpy(j->name,num);
				strcpy(j->position,poz);
				j->score=scor;
				j->injured=stare;	
			}
	
	return aux->players;
}

#endif // TEAM_EXTRACTOR_H_INCLUDED