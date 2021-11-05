#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
SDL_Texture* player=NULL;
SDL_Texture* fenta=NULL;
SDL_Color white={255,255,255};
TTF_Font* font;
Mix_Chunk* death; 
Mix_Chunk* eat;
Window* window;
int r=0, dir, len=1, score=0, fruit[2], prevdir;
float x[100],y[100], prevx, prevy;
char* text="0";
void fentagen(){
	fruit[0]=rand()%608;
	fruit[1]=rand()%608;
	if(fruit[0]%32!=0)fruit[0]-=fruit[0]%32;
	if(fruit[1]%32!=0)fruit[1]-=fruit[1]%32;
	if(fruit[0]<=32 || fruit[1] <=32)
		fentagen();
}
int collision(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2){
	return x1<x2+w2 &&
	       y1<y2+h2 &&
	   	   x2<x1+w1 &&
	       y2<y1+h1;
}
void reset(){
	score=0;
	len=1;
	x[0]=0;
	y[0]=0;
	dir=0;
}
void init(){
	r=1;
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)printf("SUCKYSUCKY! SDL no init..... SDL_GetError: %s", SDL_GetError());
    if(IMG_Init(IMG_INIT_PNG) < 0) printf("IMG failed initializing! IMG_Error: %s\n", IMG_GetError());
    if(TTF_Init() < 0)printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());  
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) printf("Mixer could not initialize!\n");
    window = malloc(sizeof(Window));
    create_window(window, "SnaCe", 640, 640);
    player = load_texture(window, "stupid_fuckign_idiot.png");
    fenta  = load_texture(window, "druge.png");
   	font = TTF_OpenFont("font.ttf", 24);
   	death=Mix_LoadWAV("died.wav");
   	eat=Mix_LoadWAV("chomp.wav");
    fentagen();
}
void update(){
	float prevx=x[1];
	float prevy=y[1];
	x[1]=x[0];
	y[1]=y[0];
	float prevx2, prevy2;
	for(int i=2;i<len;++i){
		prevx2=x[i];
		prevy2=y[i];
		x[i]=prevx;
		y[i]=prevy;
		prevy=prevy2;
		prevx=prevx2;
		if(collision(x[0],y[0],16,16,x[i],y[i],16,16)){
			reset();
			Mix_PlayChannel(-1,death,0);
		}
	}
	switch(dir){
		case 1:
			y[0]-=16;
			break;
		case 2:
			x[0]+=16;
			break;
		case -1:
			y[0]+=16;
			break;
		case -2:
			x[0]-=16;
			break;
		default:
			break;
	}
	if(x[0]>624)
		x[0]=0;
	else if(x[0]<0)
		x[0]=624;
	if(y[0]>624)
		y[0]=0;
	else if(y[0]<0)
		y[0]=624;
	if(collision(x[0],y[0],16,16,fruit[0],fruit[1],32,32)){
		Mix_PlayChannel(-1,eat,0);
		fentagen();
		score += 10;
		len +=1;
	}
	text = malloc(strlen(text)+1);
	sprintf(text, "Score: %d; Lenght: %d", score, len);
}
void render(){
	clear(window);
	for(int i=0;i<len;++i){
		render_texture(window,player,x[i],y[i],16,16,0.0,SDL_FLIP_NONE);
	}
	
	render_texture(window,fenta,fruit[0],fruit[1],32,32,0.0,SDL_FLIP_NONE);
	render_text(window, font, text, 640/2-80,590, white);
	if(dir==0){
		render_text(window, font, "Use arrow keys to move. Press Q to quit", 130, 296, white);
	}
	display(window);
}
void input(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		if(e.type==SDL_QUIT)
			r=0;
		if(e.type==SDL_KEYDOWN){
			switch(e.key.keysym.sym){
				case SDLK_UP:
					prevdir=dir;
					dir=1;
					if(dir==-prevdir)
						dir=prevdir;
					break;
				case SDLK_DOWN:
					prevdir=dir;
					dir=-1;
					if(dir==-prevdir)
						dir=prevdir;
					break;
				case SDLK_RIGHT:
					prevdir=dir;
					dir=2;
					if(dir==-prevdir)
						dir=prevdir;
					break;
				case SDLK_LEFT:
					prevdir=dir;
					dir=-2;
					if(dir==-prevdir)
						dir=prevdir;
					break;
				case SDLK_q:
					r=0;
					break;
			}
		}
	}
}
int main(int argc, char ** argv){
	init();
	const int FPSLIM=18, DELAY=1000/FPSLIM;
	Uint32 FRAME_START;
	int FRAME_TIME;
	while(r){
		FRAME_START=SDL_GetTicks();
		FRAME_TIME=SDL_GetTicks()-FRAME_START;
		render();input();update();
		if(FRAME_TIME<DELAY)
			SDL_Delay(DELAY-FRAME_TIME);
	}
	free(text);
	kill_window(window);
	free(window);
	SDL_Quit();
	return 0;
}