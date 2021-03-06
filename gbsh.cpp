#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>  
#include <string>
#include <string.h>
#include <iostream>
#include<signal.h>
using namespace std;

extern char** environ;

void sigintHandler(int sig_num) 
{ 
    signal(SIGINT, sigintHandler); 
    cout<<"Cannot be terminated using Ctrl+C "; 
    fflush(stdout); 
} 
void User(){
	cout<<getenv("USER");
}
void Host(){
	char array[256];
	struct hostent *host_entry; 
	int hostname; 
	hostname = gethostname(array,sizeof(array)); 
	cout<<array;
}
void CWD(){
	char arr[50];
	cout<<getcwd(arr,50);
}
void Print(){
	User();
	cout<<"@";
	Host();
	cout<<" ";
	CWD();
	cout<<" : ";
}
int check(char* array){

	if(strcmp(array,"exit")==0)
		return 1;
	else if(strcmp(array,"pwd")==0)
		return 2;
	else if (strcmp(array,"clear")==0)
		return 3;
	else if (strcmp(array,"ls")==0)
		return 4;
	else if((strcmp(array,"cd")==0) || (array[0]=='c' && array[1]=='d' && array[2]==' '))
		return 5;
	else if (strcmp(array,"environ")==0)
		return 6;
	else if (array[0]=='s' &&array[1]=='e' &&array[2]=='t' &&array[3]=='e' &&array[4]=='n' &&array[5]=='v')
		return 7;
	else if (array[0]=='u' &&array[1]=='n' &&array[2]=='s' &&array[3]=='e' &&array[4]=='t' &&array[5]=='e' && array[5]=='v' && array[5]=='n')
		return 8;
	else if (strcmp(array,"&top")==0)
		return 9;
	else if (strcmp(array,"&ps")==0)
		return 10; 
	else if (strcmp(array,"&man")==0)
		return 11;
	else if (strcmp(array,"top")==0)
		return 12;
	else if (strcmp(array,"ps")==0)
		return 13; 
	else if (strcmp(array,"man")==0)
		return 14;
	else 
		return 0;
//for(int i=0;i<line.length();i++)
//cout<<line.at(i);



}
void LS(){
DIR *directory;
	char arr[50];
	struct dirent *c;
	char *path=getcwd(arr, 50);
	directory=opendir(path);
	
	while((c=readdir(directory))!=NULL){
		printf("%s\n",c->d_name);
	}

	cout<<endl;




//char s[100];

  //chdir("..");
  //cout<<getcwd(s, 100);
//closedir(dir);
}
void CD(char * array){
		if(array[0]=='c' && array[1]=='d' && array[2]!=' '){
			chdir(getenv("HOME"));
			//cout <<"CD Chal para "<<endl;
		}
		else{
			//cout <<"CD Chal else "<<endl;
			char *token;  
			token = strtok(array," ");
			token = strtok(NULL," ");
			chdir(token);
			//cout<<line.find(' ')<<endl;
			//LS();
		}
}

void Token(char * array){
	char *token;  
	/* get the first token */
	token = strtok(array," ");
				   
	/* walk through other tokens */
		while( token != NULL ) {
			printf( "%s\n", token );
			token = strtok(NULL," ");
		}
	cout<<"Command Not exist "<<endl;
}

int main(int argc, char* argv[]) {
//Print();

bool flag=1;
char array[100];
signal(SIGINT, sigintHandler); 
	while(flag){
		Print();
		cin.getline(array,100);
		int number=check(array);
		if(number==1){//1 is for exit command
			flag=0;
		}
		else if(number==2){//2 is for pwd
			char arr[50];
			cout<<getcwd(arr,50)<<endl;
		}
		else if(number==3){//3 is for clear
			//system("clear");
			printf("\033c");
		}
		else if (number==4){//4 is for ls
			LS();
		}
		else if (number==5){//5 is for cd
			CD(array);
		}
		else if (number==6){//6 is for environ
			 for (int i = 0; environ[i] != NULL; i++) {
    				cout<<environ[i]<<endl;
  			}
		}
		else if (number==7){//7 is for setenv
			char*str=*environ;
			int var=1;
			while(str){
				cout<<str<<endl;
				str=*(environ+var);
				var++;
			}
			
		}
		else if (number==8){//8 is for unsetenv
			char*str=*environ;
			int var=1;
			while(str){
				cout<<str<<endl;
				str=*(environ+var);
				var++;
			}
		}
		else if (number==9){//9 is for &top
			int num=fork();
			if(num==0){
				execlp("top","top",NULL);
			}
		}
		else if (number==10){//10 is for &ps
		int num=fork();
			if(num==0){
				execlp("ps","ps",NULL);
			}
		}
		else if (number==11){//11 is for &man
		int num=fork();
			if(num==0){
				execlp("man","man",NULL);
			}
		}
		else if (number==12){//12 is for top
			int num=fork();
			if(num==0){
				execlp("top","top",NULL);
			}
		}
		else if (number==13){//13 is for ps
		int num=fork();
			if(num==0){
				execlp("ps","ps",NULL);
			}
		}
		else if (number==14){//14 is for man
		int num=fork();
			if(num==0){
				execlp("man","man",NULL);
			}
		}
		else if (number==0){
			Token(array);
		}
	}
return 0;
}
