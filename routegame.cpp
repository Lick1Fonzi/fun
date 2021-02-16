#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#define lato 10
using namespace std;

//funzioni
void display(char griglia[][lato]){
	for(int i=0;i<lato;i++){
                for(int j=0;j<lato;j++){
                        printf("%c ",griglia[i][j]);
                }
        	printf("\n");
        }
	printf("\n");
}
void notvalid(int* loop){printf("hai perso \n"); *loop=0;}
int check(char griglia[][lato]){
	for(int i=0;i<lato;i++){
		for(int j=0;j<lato;j++){
			if(griglia[i][j]=='+')
				return 1;
		}
	}
	printf("grande!! hai vinto \n");
	return 0;
}
 //main
int main(){
	//initialising environment
	int x;
	int y;
	int loop=1;
	char temp;
	char gamer='O';
	char griglia[lato][lato];
	char mossa;
	for(int i=0;i<lato;i++){
		for(int j=0;j<lato;j++){
			griglia[i][j]='+';
		}
		if(i%2==0){
			griglia[rand()%lato][rand()%lato]='/';
		}
	}
	srand(time(NULL));
	griglia[x=rand()%lato][y=rand()%lato]=gamer;
	printf("welcome gamer,per vincere passa sopra tutte le caselle ma mai due volte sulla stessa \n");
	display(griglia);
	//game loop
	while(loop && check(griglia)){
	printf("inserisci mossa con wasd, p per terminare \n");
	//scanf("%c",&mossa); //salta un ciclo, non so come svuotare buffer
	cin >> mossa;
	switch(mossa){
	case 'w':
	printf("su \n");
	if(x>0 && griglia[x-1][y]=='+'){
		griglia[x][y]='|';
		x--;
		griglia[x][y]='^';
	}
	else{notvalid(&loop);}
	break;
	case 's':
	printf("giu \n");
	if(x<lato-1 && griglia[x+1][y]=='+'){
                griglia[x][y]='|';
                x++;
                griglia[x][y]='v';
        }
	else{notvalid(&loop);}
	break;
	case 'd':
	printf("destra \n");
	if(y<lato-1 && griglia[x][y+1]=='+'){
		griglia[x][y]='-';
		y++;
		griglia[x][y]='>';
	}
	else{notvalid(&loop);}
	break;
	case 'a':
	printf("sinistra \n");
	if(y>0 && griglia[x][y-1]=='+'){
		griglia[x][y]='-';
		y--;
		griglia[x][y]='<';
	}
	else{notvalid(&loop);}
	break;
	case 'p':
	loop=0;
	printf("never back down U Loser \n");
	break;
	default:
	printf("inserire mossa valida \n");
	break;
	}
	display(griglia);
	}//close while
}
