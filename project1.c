#include <stdio.h>
#include <stdlib.h>

int eT;
int eP;
int *T;
int *P;
int *pi;
int badchar_list[4];
int *Z_box;

int * buildT(int h){

  int A = 2;
  int r = 1;
  
  T = malloc(A*sizeof(int));
  h = getchar();

  while(r){
    h = getchar();

    if(h == '\n' || h==13){r=0;}
    else{

      if(eT == A){
	A = A*2;
	T = realloc(T, A*sizeof(int));}

      T[eT] = h;

      eT++;    }
  }
  return T;
}


int * buildP(int h){

  int A = 2;
  int r = 1;

  P = malloc(A*sizeof(int));
  h = getchar();
  while(r){
    h = getchar();
    if(h == '\n'|| h==13){r=0;}
    else{
      if(eP == A){
	A = A*2;
	P = realloc(P, A*sizeof(int));}
      P[eP] = h;
      eP++;    }
  }

  return P;
}



void naive(){

  int i;
  int j;
  int contador = 0;
  for(i=0; i < eT; i++){
    j=0;
    while(j<eP && P[j] == T[i+j]){contador++;j++;}
    if(j==eP){printf("%d ", i);}
    else{contador++;}

  }

  printf("\n");

}

int * pi_aux(int m){

  int A = 2;
  int j; 
  int i;
  pi = malloc(A*sizeof(int));
  pi[0]=0;
  j = 0;
  for(i = 1; i < eP; i++){
    if(i == A){
      A = A*2;
      pi = realloc(pi, A*sizeof(int));}
    while(j > 0 && P[j] != P[i]){
      j = pi[j-1];
    }
    if(P[j] == P[i]){
      j++;
    }
    pi[i] = j; 
  }
  return pi;
}

void kmp(){
  int i = 0;
  int k = 0;
  int contador = 0;
  pi = pi_aux(eP);

  while(i < eT){
    while(k > 0 && P[k] != T[i]){
      k = pi[k-1];
      contador++;
    }
    contador++;
    if(P[k] == T[i]) {
      k++;
    }
    if(k == eP) {
      printf("%d ", i-k+1);
      k = pi[k-1];
      if(i != eT - 1){contador++;}
  }
    i++;
  }
  printf("\n");
  printf("%d \n",contador);

}

void badchar_aux(){
  int i = 0;
  badchar_list[0] = -1;
  badchar_list[1] = -1;
  badchar_list[2] = -1;
  badchar_list[3] = -1;
  while(i < eP){
    if(P[i] == 'A'){
      badchar_list[0] = i;
    }
    else if(P[i] == 'C'){
      badchar_list[1] = i;
    }
    else if(P[i] == 'G'){
      badchar_list[2] = i;
    }
    else if(P[i] == 'T'){
      badchar_list[3] = i;
    }
    i++;
  }
  
}


int badchar(int j, char bad){
    if(bad == 'A'){
      return j - badchar_list[0];
    }
    else if(bad == 'C'){
      return j - badchar_list[1];
    }
    else if(bad == 'G'){
      return j - badchar_list[2];
    }
    else if(bad == 'T'){
      return j - badchar_list[3];
    }
    return 0;
}

int * Z_box_aux(){

  int A = 2;
  int j = 0;
  int i = 1;
  int r = 0;
  int r0 = 0;
  
  Z_box = malloc(A*sizeof(int));
  Z_box[0] = 0;
  
  while(i < eP){
    if(i == A){
      A = A*2;
      Z_box = realloc(Z_box, A*sizeof(int));}

    if(i >= r){

      while (P[eP-1 - j] == P[eP-1 - i - j]){j++;}
      
      Z_box[i] = j;
      r0 = i;
      r = i + j-1;
      j = 0;
    }

    else{

      if(Z_box[i-r0] < r - i){Z_box[i] = Z_box[i-r0];}

      else{

	while(P[eP-1 - r - 1 - j] == P[eP-1 - Z_box[i-r0]-j]){j++;}

     	Z_box[i] = r - (eP-1-i) + j;
	r0 = i;
	r = r + j;
	j = 0;
      }
      
    }
    i++;

  }
  return Z_box;
}

int strongsuff(int alpha_size){
  int not_found = 1;
  int j = 0;
  int k = eP;
  while(not_found && j < eP){
    if (Z_box[j] == alpha_size){not_found = 0;}
    else{j++;}
    if(Z_box[j]== eP-j && eP-j < alpha_size && k == eP){k = j;}

  }
  if (!not_found){return j;}
  else{return k;}
}
 
void bm(){
  int i = 0;
  int badchar1;
  int strongsuff1;
  int j;
  int b;
  int alpha_size;
  int contador = 0;
  while(i + eP-1 < eT){
    b = 0;
    j = eP - 1;
    alpha_size = 0;
    while(b == 0){
      if(T[i+j] == P[j]){
        j--;
	alpha_size++;
      }
      else {b = 1;}
      if(j == -1) {
        printf("%d ", i); 
        b = 2;
      }
      contador++;
    }
    if(b > 0){
      if(b == 1){badchar1 = badchar(j, T[i+j]);}
      else{badchar1 = 0;}
      strongsuff1 = strongsuff(alpha_size);
      if(badchar1 < 1 && strongsuff1 < 1){ i++; }
      else if (badchar1 <= strongsuff1) {i = i + strongsuff1;}
      else{ i = i + badchar1;}
    }
  }

  printf("\n%d \n", contador);

}

int main(){

  int h;
  int r0 = 1;
  while(r0){

      h = getchar();
      if(h == 'T') {eT = 0; T = buildT(h);}
      else if(h == 'N'){eP = 0; P = buildP(h); naive();}
      else if(h == 'K'){eP = 0; P = buildP(h); kmp();}
      else if(h == 'B'){eP = 0; P = buildP(h); badchar_aux(); Z_box = Z_box_aux(); bm();}
      else if(h == 'X'){r0 = 0;}
      
  }  

  free(T);
  free(P);
  free(pi);
  free(Z_box);
  return  0;
}