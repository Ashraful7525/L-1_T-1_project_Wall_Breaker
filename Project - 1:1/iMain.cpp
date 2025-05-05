#include "iGraphics.h"
#include<stdio.h> 
#include<algorithm>
#include <iostream>
#include <string>
#include <cstdio>
#include <windows.h>
#include <unistd.h>
#include <mmsystem.h>
#include <time.h>
#pragma comment(lib, "winmm.lib");

using namespace std;

#define screenWidth 800
#define screenHeight 600
double xBall = 400, yBall = 50, rBall = 10;
double dx=6, dy=4;
int flag=0;
double velocity=0.5;
const int totalBricks=36;
const int totalBalls=5;
int score=0;
int counter=0;
int level=1;
int Bricks=0;
int music=1;
int actscore=0;
int pausemenu=0;
char name[15];
int namesize = 0;

pair<int, string> SINA[11], ROSE[11], MARIA[11];

double smplballx=400;
double smplbally=300;

char photo[10][30]={"Photos\\home.bmp", "Photos\\difficulty.bmp", "Photos\\option.bmp", "Photos\\options-mscon.bmp","Photos\\help.bmp", "Photos\\highscore.bmp", "Photos\\scoreboard-1.bmp",
"Photos\\gamebackground.bmp","Photos\\pause.bmp","Photos\\pause-menu.bmp"};
const char SOUND[1][30]={"sound\\click.wav"};
int gamestate = 0;

struct BrickStructure{
	double x;
	double y;
	double dx;
	double dy;
	int showBrick=0;
	int r;
	int g;
	int b;
}Brick[totalBricks];

struct BallStructure{
	double x;
	double y;
	double dx;
	double dy;
}Ball[totalBalls];


void defineBricks(){
	flag=0;
	score=0;
	counter=0;
	actscore=0;
	if(level==1){
		Bricks=18;
		for(int i=0; i<Bricks/3; i++){
			Brick[i].dx=98;
			Brick[i].dy=30;
			Brick[i].x=100*(i+1);
			Brick[i].y=500-20;
			Brick[i].showBrick=3;

			if(i%2==0 ){
				Brick[i].r=188;
				Brick[i].g=74;
				Brick[i].b=60;
			}
			else{
				Brick[i].r=119;
				Brick[i].g=36;
				Brick[i].b=36;
			}
		}
		for(int i=Bricks/3; i<2*Bricks/3; i++){
			Brick[i].dx=98;
			Brick[i].dy=30;
			Brick[i].x=100*(i+1)-100*Bricks/3;
			Brick[i].y=468-20;
			Brick[i].showBrick=3;

			if(i%2 == 1){
				Brick[i].r=188;
				Brick[i].g=74;
				Brick[i].b=60;
			}
			else{
				Brick[i].r=119;
				Brick[i].g=36;
				Brick[i].b=36;
			}
		}
		for(int i=2*Bricks/3; i<Bricks; i++){
			Brick[i].dx=98;
			Brick[i].dy=30;
			Brick[i].x=100*(i+1)-100*2*Bricks/3;
			Brick[i].y=436-20;
			Brick[i].showBrick=3;

			if(i%2==0 ){
				Brick[i].r=188;
				Brick[i].g=74;
				Brick[i].b=60;
			}
			else{
				Brick[i].r=119;
				Brick[i].g=36;
				Brick[i].b=36;
			}
		}
	}
	else if(level==2){
		Bricks=25;
		int cnt=0;
		for(int i=0; i<9; i++){
			int j=0;
			if(i<5) j=i;
			else j=8-i;
			for(int k=0; k<=j; k++){
				Brick[cnt].dx=116;
				Brick[cnt].dy=28;
				Brick[cnt].x=100+k*121+float(abs(4-j))*60.5;
				Brick[cnt].y=520-i*30;
				Brick[cnt].showBrick=3;
				

				if((cnt)%3==0){
					Brick[cnt].r=162;
					Brick[cnt].g=88;
					Brick[cnt].b=58;
				}
				else if((cnt)%3==1){
					Brick[cnt].r=230;
					Brick[cnt].g=149;
					Brick[cnt].b=95;
					
				}
				else if((cnt)%3==2){
					Brick[cnt].r=195;
					Brick[cnt].g=111;
					Brick[cnt].b=62;
				}

				cnt+=1;
			}
		}
	}
	else if(level==3){
		Bricks = 25;
		int cnt=0;
		for(; cnt<8; cnt++){
			Brick[cnt].dx = 100;
			Brick[cnt].dy = 30;
			Brick[cnt].x = cnt*100;
			Brick[cnt].y = 330;

			if((cnt)%3==0){
				Brick[cnt].r=162;
				Brick[cnt].g=88;
				Brick[cnt].b=58;
			}
			else if((cnt)%3==1){
				Brick[cnt].r=230;
				Brick[cnt].g=149;
				Brick[cnt].b=95;
				
			}
			else if((cnt)%3==2){
				Brick[cnt].r=195;
				Brick[cnt].g=111;
				Brick[cnt].b=62;
			}
		}


		for(cnt=8;cnt<14; cnt++){
			Brick[cnt].dx = 100;
			Brick[cnt].dy = 30;
			Brick[cnt].x = (cnt-7)*100;
			Brick[cnt].y = 390;
			if((cnt)%3==0){
				Brick[cnt].r=162;
				Brick[cnt].g=88;
				Brick[cnt].b=58;
			}
			else if((cnt)%3==1){
				Brick[cnt].r=230;
				Brick[cnt].g=149;
				Brick[cnt].b=95;
				
			}
			else if((cnt)%3==2){
				Brick[cnt].r=195;
				Brick[cnt].g=111;
				Brick[cnt].b=62;
			}
		}

		Brick[14].dx = 100;
		Brick[14].dy = 30;
		Brick[14].x = 600;
		Brick[14].y = 450;
		Brick[14].r=162;
		Brick[14].g=88;
		Brick[14].b=58;

		Brick[15].dx = 100;
		Brick[15].dy = 30;
		Brick[15].x = 100;
		Brick[15].y = 420;
		Brick[15].r=162;
		Brick[15].g=88;
		Brick[15].b=58;


		Brick[16].dx = 100;
		Brick[16].dy = 30;
		Brick[16].x = 100;
		Brick[16].y = 450;
		Brick[16].r=230;
		Brick[16].g=149;
		Brick[16].b=95;

		Brick[17].dx = 100;
		Brick[17].dy = 30;
		Brick[17].x = 600;
		Brick[17].y = 420;
		Brick[17].r=195;
		Brick[17].g=111;
		Brick[17].b=62;


		for(cnt=18; cnt<24; cnt++){
			Brick[cnt].dx = 100;
			Brick[cnt].dy = 30;
			Brick[cnt].x = (cnt-17)*100;
			Brick[cnt].y = 480;
			if((cnt)%3==0){
				Brick[cnt].r=162;
				Brick[cnt].g=88;
				Brick[cnt].b=58;
			}
			else if((cnt)%3==1){
				Brick[cnt].r=230;
				Brick[cnt].g=149;
				Brick[cnt].b=95;
				
			}
			else if((cnt)%3==2){
				Brick[cnt].r=195;
				Brick[cnt].g=111;
				Brick[cnt].b=62;
			}
		}

		Brick[24].dx=100;
		Brick[24].dy=30;
		Brick[24].x=350;
		Brick[24].y=435;
		Brick[24].r=188;
		Brick[24].g=74;
		Brick[24].b=60;


		for(int i=0; i<25; i++){
			Brick[i].showBrick=3;
			Brick[i].y+=25;
		}
		
	}
}

void defineBalls(){
	for(int i=0; i<totalBalls; i++){
		Ball[i].x=xBall;
		Ball[i].y=yBall;
		Ball[i].dx=0;
		Ball[i].dy=0;
	}
}

void iDraw(){
	iClear();

	if(gamestate==0){
		iShowBMP(0, 0, photo[0]);
		iSetColor(20, 200, 200);
	}
	else if(gamestate==1){
		iShowBMP(0, 0, photo[1]);
	}
	else if(gamestate==2){
		if(music==0) {
			iShowBMP(0, 0, photo[2]);
		}
		else{
			iShowBMP(0, 0, photo[3]);
		}
	}
	else if(gamestate==3){
		iShowBMP(0, 0, photo[4]);
	}
	else if(gamestate == 4){
		//highscore
		iShowBMP(0, 0, photo[5]);

		FILE *fptr = fopen("sina.txt", "r");
		int x; char str[20];
		for(int i=0; i<10; i++){
			fscanf(fptr, "%d", &x);
			fscanf(fptr, "%s", str);
			sprintf(str, "%s - %d",str, x);
			iSetColor(0, 0, 0);
			iText(60, 420-i*30, str, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		fclose(fptr);

		fptr = fopen("rose.txt", "r");
		for(int i=0; i<10; i++){
			fscanf(fptr, "%d", &x);
			fscanf(fptr, "%s", str);
			sprintf(str, "%s - %d",str, x);
			iSetColor(0, 0, 0);
			iText(310, 420-i*30, str, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		fclose(fptr);

		fptr = fopen("maria.txt", "r");
		for(int i=0; i<10; i++){
			fscanf(fptr, "%d", &x);
			fscanf(fptr, "%s", str);
			sprintf(str, "%s - %d",str, x);
			iSetColor(0, 0, 0);
			iText(560, 420-i*30, str, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		fclose(fptr);


	}
	else if(gamestate==6){
		//iShowBMP(0, 0, photo[7]);
	/*Initialize*/
		iSetColor(123, 39, 22);
		iFilledRectangle(0, 0, 800, 50);

		iSetColor(123, 39, 22);
		iFilledRectangle(0, 550, 800, 50);

		if(pausemenu == 0) iShowBMP(5, 551, photo[8]);
		for(int i=0; i<totalBalls; i++){
			iSetColor(20, 200, 200);
			iFilledCircle(Ball[i].x, Ball[i].y, rBall, 1000);
		}
	/*Condition on velocities and Collisions*/
		for(int j=0; j<totalBalls; j++){
			if(j==0){
				if(flag==1){
					Ball[j].dx=dx;
					Ball[j].dy=dy;
					flag++;
				}
			}
			else{
				if((Ball[j-1].x-xBall)*(Ball[j-1].x-xBall)+(Ball[j-1].y-yBall)*(Ball[j-1].y-yBall)>10000 && flag==j+1){
					Ball[j].dx=dx;
					Ball[j].dy=dy;
					flag++;
				}
			}
		}

		for(int j=0; j<totalBalls; j++){
				Ball[j].x+=Ball[j].dx;
				Ball[j].y+=Ball[j].dy;

			if(Ball[j].x>=screenWidth-rBall || Ball[j].x<=0+rBall){
				Ball[j].dx*=-1;
			}

			if(Ball[j].y>=screenHeight-50-rBall){
				Ball[j].dy*=-1;
			}

			if(Ball[j].y<=0){
				Ball[j].x = 400, Ball[j].y = 50;
				Ball[j].dx= 0, Ball[j].dy = 0; 
				counter+=1;
				actscore-=1;
			}


			for(int i=0; i<Bricks; i++){
				if(Brick[i].showBrick>0 && Ball[j].x>=Brick[i].x-rBall && Ball[j].x<=Brick[i].x+Brick[i].dx+rBall && Ball[j].y>=Brick[i].y-rBall && Ball[j].y<= Brick[i].y+Brick[i].dy+rBall ){
					Brick[i].showBrick-=1;
					if(music == 1) PlaySound("sound\\Soft Brick (Brick).wav", NULL, SND_ASYNC);
					if(abs(Ball[j].x-(Brick[i].x-rBall))<10 || abs(Ball[j].x-(Brick[i].x+Brick[i].dx+rBall))<10) Ball[j].dx*=-1;
					else Ball[j].dy*=-1;
					score+=1;
					actscore+=1;
				}
			}
		}

		if(counter==totalBalls){
			flag=0;
			counter=0;
		}
	/*Did Bricks show up?*/
		iSetColor(20, 200, 0);
		for(int i=0; i<Bricks; i++){
			if(Brick[i].showBrick!=0){
				iSetColor(Brick[i].r, Brick[i].g, Brick[i].b);
				iFilledRectangle(Brick[i].x, Brick[i].y, Brick[i].dx, Brick[i].dy);

				iSetColor(255, 255, 255);
				if(Brick[i].showBrick==3) iText(Brick[i].x+Brick[i].dx/2,Brick[i].y+Brick[i].dy/2-5,"3", GLUT_BITMAP_HELVETICA_18);
				else if(Brick[i].showBrick==2) iText(Brick[i].x+Brick[i].dx/2,Brick[i].y+Brick[i].dy/2-5,"2", GLUT_BITMAP_HELVETICA_18);
				else if(Brick[i].showBrick==1) iText(Brick[i].x+Brick[i].dx/2,Brick[i].y+Brick[i].dy/2-5,"1", GLUT_BITMAP_HELVETICA_18);
				
			}
		}

	/*Text are also important*/
		
		if(score==Bricks*3){
			// char endline[50]="Your Score is ";
			// sprintf(endline, "%s%d", endline, score);
			// iText(350, 400,endline, GLUT_BITMAP_TIMES_ROMAN_24);
			gamestate=7;
		}
		else{
			char str[]="Score:";
			iSetColor(255, 218, 177);
			sprintf(str, "%s%d",str, actscore);
			iText(20, 20,str, GLUT_BITMAP_TIMES_ROMAN_24);
		}


		if(pausemenu==1){
			iShowBMP(186, 200, photo[9]);
		}
	}
	else if(gamestate == 7){
		iShowBMP(0, 0, photo[6]);
		char aaaa[5];
		for(int i=0;i<5; i++) aaaa[i]='\0';
		iSetColor(0, 0, 0);
		sprintf(aaaa, "%s%d",aaaa, actscore);
		iText(455, 275 , aaaa , GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
		iText(440, 167 , name , GLUT_BITMAP_TIMES_ROMAN_24);

	}
}

void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
}

void iMouse(int button, int state, int mx, int my) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){

		if(gamestate != 6 && music == 1) PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		else if(gamestate == 6 && music == 1){
			if(pausemenu == 0 && mx>=5 && mx<=50 && my>=555 && my<=600) PlaySound("sound\\click.wav", NULL, SND_ASYNC);
			else if(pausemenu == 1) PlaySound("sound\\click.wav", NULL, SND_ASYNC);
		}



		if(gamestate==0){
			if(mx>=200 && mx<=395 && my>=151 && my<=215){
				gamestate=1;
			}
			else if( mx>=405 && mx<=600 && my>=151 && my<=215){
				gamestate=2;
			}
			else if(mx>=200 && mx<=395 && my>=75+12 && my<=131+12){
				gamestate=4;


			}
			else if(mx>=405 && mx<=600 && my>=75+12 && my<=131+12){
				exit(0);
			}
		}
		else if(gamestate==1){
			if(mx>=229 && mx<=229+342 && my>=352 && my<=352+53){
				gamestate=6; level=1;
				defineBalls();
				defineBricks();
			}
			else if(mx>=229 && mx<=229+342 && my>=260 && my<=260+50){
				gamestate=6; level=2;
				defineBalls();
				defineBricks();
			}
			else if(mx>=229 && mx<=229+342 && my>=170 && my<=170+50){
				gamestate=6; level=3;
				defineBalls();
				defineBricks();
			}
			else if(mx>=20 && mx<=90 && my>=20 && my<=90){
				gamestate=0;
			}
		}
		else if(gamestate==2){
			if(mx>=172 && mx<=172+162 && my>=316 && my<=316+66){
				//music
				if(music==0) music=1;
				else music=0;
				
			}
			else if(mx>=172 && mx<=172+338 && my>=228 && my<=228+66){
				//how to play
				gamestate=3;
			}
			else if(mx>=172 && mx<=172+162 && my>=142 && my<=142+66){
				//back
				gamestate=0;
			}
		}
		else if(gamestate == 3){
			if(mx>=15 && mx<=90 && my>=12 && my<=85){
				gamestate=2;
			}
		}
		else if(gamestate == 4){
			if(mx>=5 && mx<=78 && my>=3 && my<=73) gamestate = 0;
		}
		else if(gamestate == 6){
			if(flag==0 && pausemenu==0 && my>=50 && my<=550){
				double theta=atan((mx-xBall)/(my-yBall));
				dx=velocity*sin(theta);
				dy=velocity*cos(theta);
				flag=1;
			}
			else if(flag == 0 && pausemenu==0 && mx>=5 && mx<=50 && my>=555 && my<=600){
				pausemenu=1;
			}
			else if(flag == 0 && pausemenu==1 && mx>=246 && mx<=346 && my>=211 && my<=305){
				pausemenu = 0;
			}
			else if(flag == 0 && pausemenu==1 && mx>=452 && mx<=553 && my>=211 && my<=305){
				gamestate = 0;
				pausemenu = 0;
			}
		}
		else if(gamestate == 7){
			if(mx>=701 && mx<=786 && my>=13 && my<=93) {

				if(level == 1){
					FILE *fptr = fopen("sina.txt", "a"); 
					if (fptr == NULL){ 
						printf("Could not open file"); 
					} 

					fprintf(fptr,"%d %s ", actscore, name); 
					fclose(fptr); 


					int i=0;
					fptr = fopen("sina.txt", "r");
					if(fptr == NULL){ 
						printf("Could not open file"); 
					}

					for(i=0; i<11; i++){
						fscanf(fptr, "%d", &SINA[i].first);
						fscanf(fptr, "%s", &SINA[i].second);
						SINA[i].first*=-1;
					}
					fclose(fptr); 


					sort(SINA, SINA+11);

					fptr = fopen("sina.txt", "w");
					for(int j=0; j<10; j++){
						fprintf(fptr,"%d %s ",-SINA[j].first ,SINA[j].second); 
					}
					fclose(fptr); 



				}
				else if(level == 2){
					FILE *fptr = fopen("rose.txt", "a"); 
					if (fptr == NULL) 
					{ 
						printf("Could not open file"); 
					} 

					fprintf(fptr,"%d %s\n", actscore, name); 
					fclose(fptr); 

					int i=0;
					fptr = fopen("rose.txt", "r");
					if(fptr == NULL){ 
						printf("Could not open file"); 
					}

					for(i=0; i<11; i++){
						fscanf(fptr, "%d", &SINA[i].first);
						fscanf(fptr, "%s", &SINA[i].second);
						SINA[i].first*=-1;
					}
					fclose(fptr); 


					sort(SINA, SINA+11);

					fptr = fopen("rose.txt", "w");
					for(int j=0; j<10; j++){
						fprintf(fptr,"%d %s ",-SINA[j].first ,SINA[j].second); 
					}
					fclose(fptr);
				}
				else if(level == 3){
					FILE *fptr = fopen("maria.txt", "a"); 
					if (fptr == NULL) 
					{ 
						printf("Could not open file"); 
					} 

					fprintf(fptr,"%d %s\n", actscore, name); 
					fclose(fptr); 

					int i=0;
					fptr = fopen("maria.txt", "r");
					if(fptr == NULL){ 
						printf("Could not open file"); 
					}

					for(i=0; i<11; i++){
						fscanf(fptr, "%d", &SINA[i].first);
						fscanf(fptr, "%s", &SINA[i].second);
						SINA[i].first*=-1;
					}
					fclose(fptr); 


					sort(SINA, SINA+11);

					fptr = fopen("maria.txt", "w");
					for(int j=0; j<10; j++){
						fprintf(fptr,"%d %s ",-SINA[j].first ,SINA[j].second); 
					}
					fclose(fptr);
				}


				for(int i=0; i<15; i++){
					name[i]='\0';
				}
				namesize=0;
				gamestate = 0;
				
			}
		}
	}
}

void iKeyboard(unsigned char key) {

	if(gamestate == 7){
		if(key=='\b'){
			if(namesize>0){
				namesize--;
				name[namesize]='\0';
			}
		}
		else{
			if(namesize < 9){
				sprintf(name, "%s%c", name, key);
				namesize++;
			}
		}
	}
}

void iSpecialKeyboard(unsigned char key) {

	if(key == GLUT_KEY_LEFT && score==totalBricks*3){
			gamestate=0;
			score=0;
			//defineBalls();
			//defineBricks();
		}
}

int main() {

	iInitialize(screenWidth, screenHeight, "Play_with_life");

	return 0;
}
