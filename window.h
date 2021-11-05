#ifndef WINDOW_H
#define WINDOW_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
typedef struct{
	SDL_Window* win;
	SDL_Renderer* rend;
}Window;
void create_window(Window* w, const char* pt, int pw, int ph){
	w->win=SDL_CreateWindow(pt, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,pw,ph,SDL_WINDOW_SHOWN);
	w->rend=SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED);
}
void clear(Window* w){
	SDL_SetRenderDrawColor(w->rend,0,0,0,255);
	SDL_RenderClear(w->rend);
}
void display(Window* w){
	SDL_RenderPresent(w->rend);
}
void kill_window(Window* w){
	SDL_DestroyWindow(w->win);
}
SDL_Texture* load_texture(Window* w, const char* path){
	SDL_Texture* t=IMG_LoadTexture(w->rend,path);
	if(t==NULL)
		printf("FUCK. %s\n", IMG_GetError());
	return t;
}
void render_texture(Window* win, SDL_Texture* tex, float x, float y, int w, int h, double angle, SDL_RendererFlip flip){
	SDL_Rect r;
	r.x=x;
	r.y=y;
	r.w=w;
	r.h=h;
	SDL_RenderCopyEx(win->rend, tex, NULL, &r, angle, NULL, flip);
}
void render_text(Window* win, TTF_Font* pfont,const char* text, float x, float y, SDL_Color color){
	SDL_Surface* text_s=TTF_RenderText_Solid(pfont, text, color);
	SDL_Texture* text_t=SDL_CreateTextureFromSurface(win->rend, text_s);
	SDL_Rect r={x,y,text_s->w,text_s->h};
	SDL_RenderCopy(win->rend,text_t,NULL,&r);
}
#endif