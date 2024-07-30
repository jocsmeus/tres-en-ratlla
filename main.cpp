#include <iostream>
#include <vector>
using namespace std;
int tauler[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

void imprimir(){
  cout << "+---+---+---+" << endl;
  for(int x=0; x<3; x++){
    cout << "| ";
    for(auto i : tauler[x]){
      if(i == 0)cout << ' ';
      else if(i == 1)cout << 'x';
      else cout << 'o';
      cout << " | ";
    }
    cout << endl <<"+---+---+---+" << endl;
  }
}

bool mat(){
  int a=0, b=0, c=0, d=0;
  for(int x=0; x<3; x++){
    c += tauler[x][x];
    d += tauler[x][2-x];
    for(int y=0; y<3; y++){
      a += tauler[x][y];
      b += tauler[y][x];
    }
    if(a == 3 || a == -3 || b == 3 || b == -3)return true;
    a = b = 0;
  }
  if(c == 3 || c == -3 || d == 3 || d == -3)return true;
  return false;
}

int avantatge(int n, bool tirar){
  if(mat())
    if(tirar)return -1;
    else return 1;

  if(n==0)return 0;
  bool q=true;
  vector<int> llista(0);
  if(tirar)q=false;
  for(int x=0; x<3; x++)
  for(int y=0; y<3; y++)
    if(tauler[x][y] == 0){
      if(tirar)tauler[x][y]=1;
      else tauler[x][y]=-1;
      llista.push_back(avantatge(n-1, q));
      tauler[x][y]=0;
    }
  int millor = llista[0];
  if(tirar){
    for(int i=1; i<llista.size(); i++)
      if(llista[i] > millor)millor = llista[i];
  }else{
    for(int i=1; i<llista.size(); i++)
      if(llista[i] < millor)millor = llista[i];
  }
  return millor;
}

int millor(int num, bool peca){
  vector<int> posibilitats(0);
  for(int a=0; a<3; a++)
  for(int b=0; b<3; b++)
    if(tauler[a][b] == 0){
      if(peca){
        tauler[a][b] = 1;
	posibilitats.push_back(avantatge(num, false));
      }else{
        tauler[a][b] = -1;
        posibilitats.push_back(avantatge(num, true));
      }
      tauler[a][b] = 0;
    }
  vector<int> millor(0); bool q=true; int mesbona = -1;
  if(peca)mesbona = 1;
  for(int i=0; i<posibilitats.size(); i++)
    if(posibilitats[i] == mesbona){millor.push_back(i); q=false;}

  if(q){
    for(int i=0; i<posibilitats.size(); i++)
      if(posibilitats[i] == 0)millor.push_back(i);
  }
  return millor[rand() % millor.size()];
}

void moure(int num){
  int cont = 0;
  for(int a=0; a<3; a++)
  for(int b=0; b<3; b++)
    if(tauler[a][b] == 0){
      if(cont == num)tauler[a][b] = 1;
      cont++;
    }
}

int main(){
  srand(time(nullptr));
  tauler[rand() % 3][rand() % 3] = 1;
  int x, y, prof=6;
  imprimir();
  while(true){
    cout << "digue'm [x,y] ";
    while(cin >> x >> y){
      if(tauler[x][y] == 0)break;
      cout << "Ilegal" << endl;
    }
    tauler[x][y] = -1;
    moure(millor(prof, true));
    prof-=2;
    imprimir();
    if(mat()){cout << "has perdut"; break;}
    if(prof == 0){cout << "taules" << endl; break;}
  }
}
