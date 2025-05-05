#include "iGraphics.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <windows.h>
#include <unistd.h>

#define screenWidth 800
#define screenHeight 600
double xBall = 400, yBall = 50, rBall = 10;
double dx=3, dy=2;
int flag=0;
double velocity=0.5;
const int totalBricks=18;
const int totalBalls=5;
int score=0;
int counter=0;

char photo[1][20]={"play-button.bmp"};
int gamestate = 0;

struct BrickStructure{
	int x;
	int y;
	int dx;
	int dy;
	int showBrick=3;
}Brick[totalBricks];

struct BallStructure{
	double x;
	double y;
	double dx;
	double dy;
}Ball[totalBalls];


void defineBricks(){
	for(int i=0; i<totalBricks/3; i++){
		Brick[i].dx=95;
		Brick[i].dy=30;
		Brick[i].x=100*(i+1);
		Brick[i].y=500;
		//Brick[i].showBrick=3;
	}
	for(int i=totalBricks/3; i<2*totalBricks/3; i++){
		Brick[i].dx=95;
		Brick[i].dy=30;
		Brick[i].x=100*(i+1)-100*totalBricks/3;
		Brick[i].y=465;
		//Brick[i].showBrick=3;
	}
	for(int i=2*totalBricks/3; i<totalBricks; i++){
		Brick[i].dx=95;
		Brick[i].dy=30;
		Brick[i].x=100*(i+1)-100*2*totalBricks/3;
		Brick[i].y=430;
		//Brick[i].showBrick=3;
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
		iShowBMP(200, 300, photo[0]);
		
		char play[20]="Press P to start";
		iSetColor(255, 255, 255);
		iText(310, 340, play, GLUT_BITMAP_HELVETICA_18);

	}
	else if(gamestate==1){
	/*Initialize*/
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

			if(Ball[j].y>=screenHeight-rBall){
				Ball[j].dy*=-1;
			}

			if(Ball[j].y<=0){
				Ball[j].x = 400, Ball[j].y = 50;
				Ball[j].dx= 0, Ball[j].dy = 0; 
				counter+=1;
			}


			for(int i=0; i<totalBricks; i++){
				if(Brick[i].showBrick>0 && Ball[j].x>=Brick[i].x-rBall && Ball[j].x<=Brick[i].x+Brick[i].dx+rBall && Ball[j].y>=Brick[i].y-rBall && Ball[j].y<= Brick[i].y+Brick[i].dy+rBall ){
					Brick[i].showBrick-=1;
					
					if(abs(Ball[j].x-(Brick[i].x-rBall))<10 || abs(Ball[j].x-(Brick[i].x+Brick[i].dx+rBall))<10) Ball[j].dx*=-1;
					else Ball[j].dy*=-1;
					score+=1;
				}
			}
		}

		if(counter==totalBalls) {
			flag=0;
			counter=0;
		}
	/*Did Bricks show up?*/
		iSetColor(20, 200, 0);
		for(int i=0; i<totalBricks; i++){
			if(Brick[i].showBrick!=0){
				iSetColor(210, 30, 90);
				iFilledRectangle(Brick[i].x, Brick[i].y, Brick[i].dx, Brick[i].dy);

				iSetColor(255, 255, 255);
				if(Brick[i].showBrick==3) iText(Brick[i].x+Brick[i].dx/2,Brick[i].y+Brick[i].dy/2,"3", GLUT_BITMAP_HELVETICA_18);
				else if(Brick[i].showBrick==2) iText(Brick[i].x+Brick[i].dx/2,Brick[i].y+Brick[i].dy/2,"2", GLUT_BITMAP_HELVETICA_18);
				else if(Brick[i].showBrick==1) iText(Brick[i].x+Brick[i].dx/2,Brick[i].y+Brick[i].dy/2,"1", GLUT_BITMAP_HELVETICA_18);
				
			}
		}

	/*Text are also important*/
		char str[]="Score:";
		sprintf(str, "%s%d",str, score);
		iText(100, 100,str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
	/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
}
	/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	// if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
 	//place your codes here
	// }
	if(gamestate==1){
		if(button == GLUT_LEFT_BUTTON && flag==0){
			double theta=atan((mx-xBall)/(my-yBall));
			dx=velocity*sin(theta);
			dy=velocity*cos(theta);
			flag=1;
			//xBall=rand()%500+50;
		}

	}
}
/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key) {
	
	if(key=='p' && gamestate==0){
		gamestate=1;
	}
}
/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if(key == GLUT_KEY_LEFT && score==totalBricks*3){
			gamestate=0;
			score=0;
			//defineBalls();
			//defineBricks();
		}
}



// void BallChange(){
// 	for(int j=0; j<totalBalls; j++){
// 		if(j==0){
// 			if(flag==1){
// 				Ball[j].dx=dx;
// 				Ball[j].dy=dy;
// 				flag++;
// 			}
// 		}
// 		else{
// 			if(sqrt((Ball[j-1].x-xBall)*(Ball[j-1].x-xBall)+(Ball[j-1].y-yBall)*(Ball[j-1].y-yBall))>100 && flag==j+1){
// 				Ball[j].dx=dx;
// 				Ball[j].dy=dy;
// 				flag++;
// 			}
// 		}
// 	}

// 	for(int j=0; j<totalBalls; j++){
// 			Ball[j].x+=Ball[j].dx;
// 			Ball[j].y+=Ball[j].dy;

// 		if(Ball[j].x>=screenWidth-rBall || Ball[j].x<=0+rBall){
// 			Ball[j].dx*=-1;
// 		}

// 		if(Ball[j].y>=screenHeight-rBall){
// 			Ball[j].dy*=-1;
// 		}

// 		if(Ball[j].y<=0){
// 			Ball[j].x = 400, Ball[j].y = 50;
// 			Ball[j].dx= 0, Ball[j].dy = 0; 
// 			counter+=1;
// 		}


// 		for(int i=0; i<totalBricks; i++){
// 			if(Brick[i].showBrick>0 && Ball[j].x>=Brick[i].x-rBall && Ball[j].x<=Brick[i].x+Brick[i].dx+rBall && Ball[j].y>=Brick[i].y-rBall && Ball[j].y<= Brick[i].y+Brick[i].dy+rBall ){
// 				Brick[i].showBrick-=1;
				
// 				if(abs(Ball[j].x-(Brick[i].x-rBall))<10 || abs(Ball[j].x-(Brick[i].x+Brick[i].dx+rBall))<10) Ball[j].dx*=-1;
// 				else Ball[j].dy*=-1;
// 				score+=1;
// 			}
// 		}
// 	}

// 	if(counter==totalBalls) {
// 		flag=0;
// 		counter=0;
// 	}

// 	//printf("Flag=%d Counter=%d\n", flag, counter);
// }


int main() {
	defineBricks();
	defineBalls();

	//iSetTimer(25, BallChange);

	iInitialize(screenWidth, screenHeight, "Play_with_life");

	return 0;
}
