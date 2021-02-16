#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
int lato=4;
int max=9;
//funzioni
void start(int griglia[][4]){
	srand(time(0));
	int riga=rand()%4;
	srand(time(0));
	int colonna=rand()%4;
	srand(time(0));
	int caso=rand()%4;
	while(caso<2){
		caso=rand()%4;}
	for(int i=0;i<lato;i++){
		for(int j=0;j<lato;j++)
			griglia[i][j]=0;
		}
	for(int i=0;i<caso;i++){
	srand(time(0));
        int riga=rand()%4;
        srand(time(0));
        int colonna=rand()%4;
	/*while(griglia[riga][colonna]!=0){
	int riga=rand()%4;
        int colonna=rand()%4;
	}*/
	griglia[riga][colonna]=2;
	}
	cout<<"Let's play 2048"<<endl<<endl;
}//migliorare random iniziale

void spostasu(int griglia[][4],int colonna){
        int temp=0;
        for(int i=0;i<lato;i++){
        	if(griglia[i][colonna]==0){
                 	 temp++;
                }
                else if(griglia[i][colonna]!=0 && i>0 && temp>0){
       		         griglia[i-temp][colonna]=griglia[i][colonna];
               		 griglia[i][colonna]=0;
                        }
        }
}//ok

void spostagiu(int griglia[][4], int colonna){
	int temp=0;
	for(int i=lato-1;i>=0;i--){
		if(griglia[i][colonna]==0)
			temp++;
		else if(griglia[i][colonna]!=0 && i<3 && temp>0){
			griglia[i+temp][colonna]=griglia[i][colonna];
			griglia[i][colonna]=0;
		}
	}
}//ok

void spostasx(int griglia[][4], int riga){
	int temp=0;
	for(int j=0;j<lato;j++){
		if(griglia[riga][j]==0){
                                temp++;
                        }
                else if(griglia[riga][j]!=0 && j>0 && temp>0){
                griglia[riga][j-temp]=griglia[riga][j];
                griglia[riga][j]=0;
			}
	}
}//ok
void spostadx(int griglia[][4], int riga){
	int temp=0;
	for(int j=lato-1;j>=0;j--){
		if(griglia[riga][j]==0)
			temp++;
		else if(griglia[riga][j]!=0 && j<3 && temp>0){
			griglia[riga][j+temp]=griglia[riga][j];
			griglia[riga][j]=0;
		}
	}
}//ok

void display(int griglia[][4]){
	for(int i=0;i<lato;i++){
		for(int j=0;j<lato;j++){
			cout<<griglia[i][j]<<"\t";
		}cout<<endl;
	}

}//ok
void chiedimossa(string *dove){
	cout<<"mosse possibili: w (su), s (giu), d (destra), a (sinistra)"<<endl;
	cout<<"inserisci una mossa"<<endl;
	cin>>*dove;
	cout<<endl;
	while(*dove!="w" && *dove!="s" && *dove!="d" && *dove!="a"){
		cout<<"inserire mossa valida"<<endl;
		cin>>*dove;}}//ok


void su(int griglia[][4]){
	int temp=0;
	for(int j=0;j<lato;j++){
		for(int i=0;i<lato;i++){
			spostasu(griglia,j);
			if(i<3 && griglia[i][j]==griglia[i+1][j]){
				griglia[i][j]+=griglia[i+1][j];
				griglia[i+1][j]=0;
			}
		}
		spostasu(griglia,j);
	}
}// ok

void giu(int griglia[][4]){
	for(int j=0;j<lato;j++){
		for(int i=lato-1;i>0;i--){
			spostagiu(griglia,j);
			if(i>0 && griglia[i][j]==griglia[i-1][j]){
				griglia[i][j]+=griglia[i-1][j];
				griglia[i-1][j]=0;
			}
		}
		spostagiu(griglia,j);
	}
}//ok

void sinistra(int griglia[][4]){
	for(int i=0;i<lato;i++){
		for(int j=0;j<lato;j++){
			spostasx(griglia,i);
			if(j<3 && griglia[i][j]==griglia[i][j+1]){
				griglia[i][j]+=griglia[i][j+1];
				griglia[i][j+1]=0;
			}
		}
		spostasx(griglia,i);
	}
}//ok

void destra(int griglia[][4]){
	for(int i=0;i<lato;i++){
		for(int j=lato-1;j>=0;j--){
			spostadx(griglia,i);
			if(j>0 && griglia[i][j]==griglia[i][j-1]){
				griglia[i][j]+=griglia[i][j-1];
				griglia[i][j-1]=0;
			}
		}
		spostadx(griglia,i);
	}
}//ok

void generanum(int griglia[][4]){
	int riga=rand()%4;
	int colonna=rand()%4;
	if(griglia[riga][colonna]==0)
		griglia[riga][colonna]=2;
	else{generanum(griglia);}
}//ok

int pieno(int griglia[][4]){
	int full=1;
	 for(int i=0;i<lato;i++){
                        for(int j=0;j<lato;j++){
				if(griglia[i][j]==0)
					full=0;
			}}
	return full;
}//ok

int croce(int griglia[][4],int i, int j){
	if(i>0)
		if(griglia[i-1][j]==griglia[i][j])
			return 1;
	if(i<3)
		if(griglia[i+1][j]==griglia[i][j])
			return 1;
	if(j>0)
		if(griglia[i][j-1]==griglia[i][j])
			return 1;
	if(j<3)
		if(griglia[i][j+1]==griglia[i][j])
			return 1;
	return 0;
}//ok

int gameover(int griglia[][4]){
	int continua=1;
	if(pieno(griglia)){
		for(int i=0;i<lato;i++){
			for(int j=0;j<lato;j++){
				continua=croce(griglia,i,j);
			}
		}
	}
	return continua;
}//ok

//main
int main(){
	//dichiarazioni
	int cella[4][4];
	string mossa;
	int perso=0;
	//codice
	start(cella);
	display(cella);
	while(gameover(cella)){
	chiedimossa(&mossa);
	if(mossa=="w")
		su(cella);
	else if(mossa=="a")
		sinistra(cella);
	else if(mossa=="d")
		destra(cella);
	else if(mossa=="s")
		giu(cella);
	if(!pieno(cella))
		generanum(cella);
	display(cella);}
	cout<<"game over"<<endl;
	return 0;
}
//fine
