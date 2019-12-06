/* ******************************************************************************************************************
*********************************************************************************************************************
***********************************League Points Table******************************************************* */

// Created by Archit
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<fstream>
#include<iomanip>
#include <cstdlib>
using namespace std;
#define MAX 100

void rvereseArray(int arr[], int start, int end)
{
while (start < end)
{
int temp = arr[start];
arr[start] = arr[end];
arr[end] = temp;
start++;
end--;
}


}
class team{
string name;
int points,played,lost,won,draw,matches[MAX][2];
string results[MAX][2];


public:
friend class tournament;
team(){
name="";
played=0;
points=0;
won=0;
lost=0;
draw=0;
for(int i=0;i<MAX;i++){
results[i][0]="Team X";
results[i][1]="No Result";}




}
team operator =(team &c)
{
this->name=c.name;

this->points=c.points;
this->played=c.played;
this->won=c.won;
this->lost-c.lost;

}


void set_team(){
cout<<"Enter name of team\n";
cin>>name;}

string get_name(){
return name;}

void display(){
cout<<"\n*"<<name<<" Stats*\n\n";
cout<<"Matches Played:-   "<<played<<endl;
cout<<"Matches Won:-      "<<won<<endl;
cout<<"Matches Lost:-     "<<lost<<endl;
cout<<"Matches Drawn:-    "<<draw<<endl;
cout<<"Points:-           "<<points<<endl<<endl;

cout<<"\n\n*****************Matches Played by Team "<<name<<" are**********************\n\n";
for(int i=0;i<played;i++){
cout<<this->name<<" vs "<<results[i][0]<<"    "<<results[i][1]<<endl;}
}

void play(team *t){

cout<<"Enter choice of winner  1."<<this->name<<"  2."<<t->name<<"  Enter 3 if match is drawn"<<endl;
int n;
cin>>n;
if(n==1){
results[played][1]="Won";
t->results[t->played][1]="Lost";
results[played++][0]=t->name;
won++;
t->results[t->played++][0]=name;
t->lost++;
points+=2;}

else if(n==2){
results[played][1]="Lost";
t->results[t->played][1]="Won";
results[played++][0]=t->name;
t->results[t->played++][0]=name;
t->won++;
lost++;
t->points+=2;}

else if(n==3){
results[played][1]="Drawn";
t->results[t->played][1]="Drawn";
results[played++][0]=t->name;
t->results[t->played++][0]=name;
t->draw+=1;
draw+=1;
points+=1;
t->points+=1;
}}};

class tournament:private team{
string name;
team t[MAX];
int teams;
int total_matches,matches_played;
int matches[MAX][3];

public:

string get_name(){
return name;}

int get_teams(){
return teams;}

int get_total_matches(){
return total_matches;}

int get_matches_played(){
return matches_played;}

team get_team(int i){
return t[i];}



friend class team;
tournament(){
matches_played=0;}

void init(){
cout<<"Enter the name of tournament:-";
cin>>name;
cout<<"Enter NO Of matches in tournament:-";
cin>>total_matches;
cout<<endl;
cout<<"Enter NO Of teams in tournament:-";
cin>>teams;
cout<<endl;
for(int i=0;i<teams;i++){
t[i].set_team();}
}

void set_teams(){
cout<<"Enter NO Of teams in tournament:-";
cin>>teams;
cout<<endl;
for(int i=0;i<teams;i++){
t[i].set_team();}}

void match(){

cout<<"\n\nTHE TEAMS:\n";
for(int i=0;i<teams;i++){
cout<<i+1<<"."<<t[i].name<<"\n";
}
cout<<"Enter team id's\n";
int id1,id2;
cout<<"Enter id of team 1:-";
cin>>id1;
cout<<"Enter id of team 2:-";
cin>>id2;
t[id1-1].play(&t[id2-1]);
cout<<matches_played<<endl;
matches[matches_played][0]=id1-1;
matches[matches_played][1]=id2-1;
matches[matches_played++][2]=Winner_Determiner(id1-1,id2-1);


}



void displaysummary(){

cout<<"************************The whole summary of "<<name<<"is******************************\n";
for(int i=0;i<matches_played;i++){
cout<<t[matches[i][0]].name<<"   vs   "<<t[matches[i][1]].name<<" ----->    ";
if(matches[i][2]==-1){
cout<<"Drawn"<<endl;
}
else{
cout<<"Won by "<<t[matches[i][2]].name<<endl;}
}}




int Winner_Determiner(int i1,int i2){
string str1="Won",str2="Lost",str3="Draw";
if(str1.compare(t[i1].results[t[i1].played-1][1])==0){
return i1;}

if(str1.compare(t[i2].results[t[i2].played-1][1])==0){
return i2;}

return -1;

}
void displaytable()
{   int x=1;

//team x[5];



cout<<"\n"<<"|"<<left<<setw(12)<<"Rank"<<"|"<<left<<setw(12)<<"Name"<<"|"<<left<<setw(12)<<"Played"<<"|"<<left<<setw(12)<<"won"<<"|"<<left<<setw(12)<<"lost"<<"|"<<left<<setw(12)<<"draw"<<"|"<<left<<setw(12)<<"points";
cout<<"\n";
int index[teams];
int tourn_points[teams];

for(int i=0;i<teams;i++)
{
tourn_points[i]=t[i].points;
index[i]=i;
}

int temp;
for (int i=1;i<teams; i++)
{
temp= tourn_points[i];
int tempind=index[i];
int j=i-1;
while(j>=0 && tourn_points[j]>temp )
{
tourn_points[j+1]=tourn_points[j];
index[j+1]=index[j];
j--;
}
tourn_points[j+1]=temp;
index[j+1]=tempind;

}
rvereseArray(tourn_points,0,teams-1);
rvereseArray(index, 0, teams-1);


for(int i=0;i<teams;i++)
{
cout<<"|"<<left<<setw(12)<<i+1<<"|"<<left<<setw(12)<<t[index[i]].name<<"|"<<left<<setw(12)<<t[index[i]].played<<"|"<<left<<setw(12)<<t[index[i]].won<<"|"<<left<<setw(12)<<t[index[i]].lost<<"|"<<left<<setw(12)<<t[index[i]].draw<<"|"<<left
<<setw(12)<<t[index[i]].points<<"\n";
}
}

friend void save_records(tournament t1);
};



void save_records(tournament t1){
ofstream file;
file.open("tournament.txt",ios::out);
team t;
for(int i=0;i<t1.teams-1;i++){
file.write((char*)&t1.t[i],sizeof(t1.t[i]));}
file.close();
}

void read_records(){
ifstream file_read;
file_read.open("tournament.txt",ios::in);
team t;
file_read.read((char*)&t,sizeof(t));
while(!file_read.eof()){
t.display();
file_read.read((char*)&t,sizeof(t));
}
file_read.close();
}







int main(){

tournament t1;
cout<<"*********************************Welcome to League Points table************************************\n";
t1.init();
system("cls");
int x;
while(x!=5)
{

cout<<"\n\n\n\nCHOOSE AMONGST THE FOLLOWING:\n1:PLAY A MATCH\n2:SHOW TOURNAMENT STATUS OF A TEAM\n3:SHOW POINTS TABLE\n4:SHOW SUMMARY OF TOURNAMENT\n5:EXIT\n YOUR CHOICE:";
cin>>x;

switch (x)
{

case 1:

system("cls");
if(t1.get_matches_played()+1<=t1.get_total_matches()){
cout<<"PLAYING MATCH ";
t1.match();}
else{
cout<<"*****************************All matches done,Can't Play Further,Tournament Ended...!***************************************!\n";}
save_records(t1);
break;
case 2:

system("cls");
 int y;
cout<<"DISPLAYING TEAM DETAILS :\n";

cout<<"\n\nTHE TEAMS:\n";
for(int i=0;i<t1.get_teams();i++){
cout<<i+1<<"."<<t1.get_team(i).get_name()<<"\n";
}
cout<<"ENTER INDEX OF TEAM:";
cin>>y;
t1.get_team(y-1).display();
save_records(t1);
break;

case 3:
system("cls");
cout<<"*******************************"<<t1.get_name()<<" Points Table*****************************\n";
t1.displaytable();
save_records(t1);
break;

case 4:
system("cls");
t1.displaysummary();
break;
case 5:
exit(0);
system("cls");
save_records(t1);
break;


default:
system("cls");
   cout<<"Enter Correct Option!";
}
}
}
