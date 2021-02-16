#include<stdio.h>
#include<iostream>
// 1<N<4 no solutions
#define N 8
using namespace std;

void iniz(int griglia[][N], int n){
for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        griglia[i][j]=0;
                }
        }

}

void stampa(int griglia[][N], int n){
	for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      printf("%d ",griglia[i][j]);
               	}
		printf("\n");
        }
  printf("\n");
}

bool controllariga(int griglia[][N],int i){
  for(int j=0;j<N;j++){
    if(griglia[i][j]==1){
      return false;
    }
  }
  return true;
}

bool controllacolonna(int griglia[][N],int j){
  for(int i=0;i<N;i++){
    if(griglia[i][j]==1){
      return false;
    }
  }
  return true;
}

//asse delle x indice j colonne, asse delle y indice i righe
bool controlladiag(int griglia[][N],int i,int j){
  for(int d=0;d<N;d++){
    if(d+i<N && d+j<N && griglia[d+i][d+j]==1) //diag principale in giu
      return false;
    if(i-d>=0 && j-d>=0 && griglia[i-d][j-d]==1) // diag principale in su
      return false;
    if(i+d<N && j-d>=0 && griglia[i+d][j-d]==1)
      return false;
    if(i-d>=0 && j+d<N && griglia[i-d][j+d]==1)
      return false;
  }
  return true;
}

bool safe(int griglia[][N],int i,int j){
  if(controllariga(griglia,i)&&controllacolonna(griglia,j)&&controlladiag(griglia,i,j))
    return true;
  else
    return false;
}

bool backtracking(int griglia[][N],int col){
    if(col>=N)
      stampa(griglia,N); //stampa griglia quando trova soluzione e continua
      //return true; //prima soluzione e basta
    for(int i=0;i<N;i++){
      if(safe(griglia,i,col)){
        griglia[i][col]=1;
        if(backtracking(griglia, col+1))
          return true;
        griglia[i][col]=0;
      }
    }
    return false;
}

int main(){
	int griglia[N][N];
	iniz(griglia,N);
	//stampa(griglia,N);
  if(backtracking(griglia,0))  // compatibilità versione precedente 1 soluzione
  stampa(griglia,N);

}
