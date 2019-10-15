/*
一些为了实现SDL
*/

#ifndef FUNCTIONDTQ732_H
#define FUNCTIONDTQ732_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
extern TTF_Font* font ;
bool AdjustRect(SDL_Rect *k,int x ,int y )
{
	if (x>k->x&&y>k->y&&x<k->x+k->w&&y<k->y+k->h)
	return true;
	return false;
}

//return witdh
float CalTextureTxtWidthFromHeight(SDL_Texture* t,float h)
{
	int w,x;
	SDL_QueryTexture(t,NULL ,NULL,&w,&x);
	return (h/x*w);
}
#define CalTexWidth(a,b) \
CalTextureTxtWidthFromHeight(a,b)

SDL_Texture *Text(SDL_Renderer *Renderer, const char *f,int size,uint8_t r=0,uint8_t g=0,uint8_t b=0,uint8_t a=0)
{
	 
	SDL_Color *color;
	color=(SDL_Color*)malloc(sizeof (SDL_Color));
	color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
    SDL_Surface *temp = NULL;
    SDL_Texture*Texture=NULL;
  temp = TTF_RenderUTF8_Blended(font, f,*color);
  //创建贴图
  Texture = SDL_CreateTextureFromSurface(Renderer, temp);
 SDL_FreeSurface(temp);
 free(color);
 return Texture;
}

/* 创建SDL_Rect函数 */
SDL_Rect CreateRect(int x, int y, int w, int h)
{
	SDL_Rect cr;
	cr.x = x;
	cr.y = y;
	cr.h = h;
	cr.w = w;
	return cr;
}

/* 绘制矩形函数，分别为：渲染器，是否填充，x，y，w，h，颜色 
 */

void DrawRect(SDL_Renderer * ren, bool isFill, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect f_rect = CreateRect(x, y, w, h);
	/* 设置渲染器颜色 */
	SDL_SetRenderDrawColor(ren , r, g, b, a);
	if (isFill)					/* 如果填充 */
		SDL_RenderFillRect(ren, &f_rect);
	else
		SDL_RenderDrawRect(ren, &f_rect);
}
template <typename T>
int ADT_len(T *h)
{
	int i=0;
	T* m;
	m=h;
	while (m!=NULL)
	{
		i++;
		m=m->next;
	}
	return i;
}

bool SetFPS(int FlushTimes_PerSecond)
{
	static time_t time1=clock();
	double FlushTime=1000.0/FlushTimes_PerSecond;
	bool IsFlush=false;
//	CLOCKS_PER_SEC 1000000
    while (double((clock()*1.0-time1)*1000.0/CLOCKS_PER_SEC)<=FlushTime)
    {
//    time1=clock();
    IsFlush=true;
    }
    time1=clock();
    return IsFlush;
}
void C_AddStringArray(char**all,char*s,int allNum,int insertNum)
{
	if (all[insertNum]!=NULL)
	free(all[insertNum]);
	all[insertNum]=(char*)malloc( sizeof (char)*(strlen(s)+1));
	strcpy(all[insertNum],s);
	return ;
}

void CPP_AddStringArray(char**all,char*s,int allNum,int insertNum)
{
	if (all[insertNum]!=NULL)
	delete [] all[insertNum];
	all[insertNum]=(char*) new char[( sizeof (char)*(strlen(s)+1))];
	strcpy(all[insertNum],s);
	return ;
}

void RenderBlack(SDL_Renderer* r)
{
	SDL_SetRenderDrawColor( r,0 ,0 ,0 ,0 );
}

void RenderWhite(SDL_Renderer* r)
{
	SDL_SetRenderDrawColor( r,0xff,0xff,0xff,0xff);
}
void RenderYellow(SDL_Renderer* r)
{
	SDL_SetRenderDrawColor( r,0xff,0xff,0,0xff);
}

#endif /* end of file    */