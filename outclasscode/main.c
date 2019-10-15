/*
    别踩白块儿
    2017/01/14/20:37/开始编写
    作者:邓惠东
    
    程序目标:一个小游戏,仿制别踩白块儿的规则制作一个自己的游戏。。。和抄袭差不多吧。。。不管了，练习编程而已

由于为了能够轻易控制排列数量，对各个函数进行了算法处理，仅需修改模式的nx,ny即可控制，所以代码有些难看。。。虽然这是我一贯的作风。由于用c4打的，所以很少使用长变量名(因为每个字母都要自己手打-_-||)
    
    
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <dirent.h>
#include "dtq_function.h"
//点击扩散区域控制(实际没多大用)
#define AREA 0.125
#define V_Max 6
#define V_Start 4
#define TIME_Max 10
#define ADJUST_WAY_1 0
//#define ADJUST_WAY_2 0
//黑块结构
typedef struct Black
{
	double x;
	double y;
	short position;
	short area;
}Black;


SDL_Window * Win=NULL;
SDL_Renderer* Render=NULL;
SDL_Texture* Texback=NULL;
SDL_Texture* Tex[9]={NULL};
SDL_Surface* Sur;
TTF_Font* font = NULL;
SDL_Event event;
int W,H,move,I=0;
double V=3;
double Th;
//开始标志
int begin=0;
Black black[18];
//运行信息记录文件
FILE* fpe;

//函数声明，可以藏在其他文件中
bool AdjustRect(SDL_Rect *k,int x ,int y );
SDL_Texture *Text(SDL_Renderer *Renderer,const char *f,int size,uint8_t r ,uint8_t g ,uint8_t b,uint8_t a);
SDL_Rect CreateRect(int x, int y, int w, int h);
bool SetFPS(int FlushTimes_PerSecond);
int meun(int t);
void  JiejiInit(int numx,int numy);
void  ChanjiInit(int numx,int numy);
void DrawWeb(int LR ,int UD , double curx=0 ,double cury=0 );
void DrawBlack(short nx ,short ny);
int FlashRed(int nx ,int ny , double x ,double y , double curx ,double cury ,bool isf );
int Chan(int infor);
int Jieji(int infor);

int main()
{
	int Init();Init();
	srand(time(0));
	if (opendir("./file")==NULL)
	system("mkdir ./file");
fpe=fopen("./file/IsFlush.dat","w+");
//简单的让程序一直运行的循环
	while (1)
	{
	meun(0);
	SDL_RenderPresent(Render);
	SDL_Delay(300);
	}
	
	SDL_Quit();
	return 0;
}
//假装的禅模式初始化
int ChanInit(int nx,int ny)
{
	JiejiInit(nx,ny);
}
//禅模式，参数控制运行方式
int Chan(int infor)
{
	int nx=4,ny=4,tf=0,Xi=-1,fps=60,t,downI=0;
	double x,y,cury=0,width=W*1.0/nx ,height=H*1.0/ny,V=10;
	SDL_Event event;
	I=0;
	int cv,fstart=0,fend=1,Tup=0;
	time_t time1;
	char NI[16]={0};
	SDL_Rect NiRect,TimeUpRect;
//不知道为毛，同时渲染两个文字 Texture。就会导致出错
	SDL_Texture*Time=Text(Render ,"时间快到了!",20,0xff);
//让文字为其正常的大小
	y=CalTexWidth(Time,Th);
		TimeUpRect=CreateRect(W-y*0.8,0,0.8*y,Th);
	
	if (begin==0) ChanInit(nx,ny);
	begin=1;
	RenderWhite(Render);
	SDL_RenderFillRect(Render, NULL );
	SDL_Rect fillyellow=CreateRect(0,height*(ny-1),W,height);
	RenderYellow(Render);
	SDL_RenderFillRect(Render,&fillyellow);
	DrawWeb(nx,ny,0,0);
	DrawBlack(nx,ny);
//菜单拉开中，故不进入玩耍的循环
	if (infor==1) return 0;
	SDL_FlushEvents(0x0000, 0xFFFF);
while (1)
{
//时间判定，当时间用完，则用time1作为循环是因为时间用完而终止的标志

	if ((clock()*1.0-time1) /CLOCKS_PER_SEC>TIME_Max&&fstart)
	{
	time1=-1;
	break;
	}
	if ((clock()*1.0-time1) /CLOCKS_PER_SEC>TIME_Max-5&&fstart)
	{
	     Tup=1;
	}
if (Xi!=I)
		{
		if (Tex[8]!=NULL)
		SDL_DestroyTexture(Tex[8]);
		sprintf(NI,"%d",I);
		Tex[8]=Text(Render,NI,20,0xff);
		y=CalTexWidth(Tex[8],Th);
		NiRect=CreateRect(W/2-y/2,0,y,Th);
		Xi=I;
		}
	RenderWhite(Render);
	SDL_RenderFillRect(Render, NULL );
	if (!fstart)
	{
	RenderYellow(Render);
	SDL_RenderFillRect(Render,&fillyellow);
	}
	DrawWeb(nx,ny,0,cury);
	DrawBlack(nx,ny);
	
	SDL_RenderCopy(Render ,Tex[8] ,NULL,&NiRect);
	if (Tup)
	SDL_RenderCopy(Render ,Time ,NULL,&TimeUpRect);
	SDL_RenderPresent(Render);

wait:;
		if (move==0)
		{
//由于需要判定时间是否用完，故不可以用等待事件的函数
//	if (SDL_WaitEvent(&event))
       SDL_PollEvent(&event);
        while (event.type!= SDL_FINGERDOWN)
        {
        	if ((clock()*1.0-time1) /CLOCKS_PER_SEC>TIME_Max&&fstart)
	{
	time1=-1;
	break;
	}
		if ((clock()*1.0-time1) /CLOCKS_PER_SEC>TIME_Max-5&&fstart)
	{
	     Tup=1;
	}
	if (Tup)
	SDL_RenderCopy(Render ,Time ,NULL,&TimeUpRect);
	SDL_RenderPresent(Render);
	
        	SDL_PollEvent(&event);
        }
		t=1;
		if (event.type!= SDL_FINGERDOWN)
		break;
//		else t=0;
		}
		else
		{
		if (SDL_PollEvent(&event))
		t=1;
		else t=0;
		}
		if (t)
		{
		switch (event.type)
		{
			case SDL_FINGERDOWN:
			x=event.tfinger.x*W;
			y=event.tfinger.y*H;
			tf=1;
			break;
			case SDL_FINGERMOTION:
			x=y=-1;
			break;
			default:
			tf=0;
			goto wait;
		}
		}

//触摸判定
	cv=0;
//循环末尾将x置为-1，当触摸了，则肯定不是-1
	if (x!=-1)
	{
	
	for (cv=0;cv<=ny;cv++)
	{
//判定是否点中黑块
		if (x>black[cv].x -width/10&& x<black[cv].x+width*1.1&& y>black[cv].y-height/6&& y<black[cv].y+height+height/6)
		{
		if (cv==0&&fstart)
		{
		fend=0;
		break;
		}
//正确点击黑块或已变灰的黑块。但计算之前有无未点击的黑块，有则这次判定无效
		for (int i=0;i<cv;i++)
		if (black[i].position) fend=0;
		
		if (fend)
		{
		
		if (black[cv].position)
		{
		if (cv==0&&black[0].position&&!fstart)
		{
//游戏成功开始
			fstart=1;
			time1=clock();
		}
		black[cv].position=0;
		if (!black[cv].area)
		black[cv].area=4;
		move=1;
		I++;
		}
		}
		else move=0;
		break;
		}
	}
	}
//由于点击的不是最底下的黑块，故重新循环，并等待点击
	if (!fend)
	{
		fend=1;
		continue;
	}
//没有点中任何一个黑块，失败
	if (cv==ny+1) break;
	for (cv=0;cv<=ny;cv++)
		{
			if (!black[cv].position &&black[cv+1].position)
			{
//最下的到达低端，即停止移动
				if (black[cv].y+height>=H-height*V/fps)
				move=0;
			}
		}
//最底下已被点击的超过屏幕最下端
		if (black[0].y>=H)
		{
		for (cv=1;cv<ny+1;cv++)
		black[cv-1]=black[cv];
		--cv;
		black[cv].x=(rand()%nx)* (width);
		black[cv].y=black[cv-1].y-height;
		black[cv].position=1;
		black[cv].area=0;
		}
		cury+=height*V/fps;
		for (cv=0;cv<ny+1;cv++)
		black[cv].y+=height*V/fps;
		x=y=-1;
	SetFPS(fps);
}
//清除内存占用
	SDL_DestroyTexture(Time);
	for (int i=0;i<9;i++)
	{
		if (Tex[i]!=NULL)
		SDL_DestroyTexture(Tex[i]);
	}

		cv=0;
//点击错误闪烁
	while (cv++<8&&time1!=-1)
	{
		RenderWhite(Render);
	SDL_RenderFillRect(Render, NULL );
		DrawWeb(nx,ny ,0 ,cury );
		DrawBlack(nx,ny);
		FlashRed(nx,ny,x,y,0 ,cury,cv%2);
		SDL_RenderCopy(Render ,Tex[8] ,NULL,&NiRect);
		SDL_RenderPresent(Render);
		SetFPS(8);
	}
//		if (time1==-1)
//显示结果
	{
		SDL_FlushEvents(0x0000, 0xFFFF);
		SDL_RenderClear(Render);
		SDL_SetRenderDrawColor( Render ,0 ,0,0,0);
		SDL_RenderFillRect(Render, NULL );
		SDL_DestroyTexture(Tex[8]);	Tex[8]=Text(Render,NI,20,0xff,0xff,0xff,0xff);
		y=CalTexWidth(Tex[8],Th);
		NiRect=CreateRect(W/2-y,H/4,2*y,2*Th);
		SDL_RenderCopy(Render,Tex[8],NULL,&NiRect);
		SDL_RenderPresent(Render);
		
		SDL_WaitEvent(&event);
		
		return 0;
	}

}

//横向多少块,纵向多少块(黑白都有)
void  JiejiInit(int nx ,int ny )
{
//	if (ny>7) return;
	for (int i=0;i<ny+1;i++)
	{
		black[i].x=rand()%nx* (W*1.0/nx);
		black[i].y=(ny-i-2)*(H*1.0/ny);
		black[i].position=1;
		black[i].area=0;
	}
}
//红块闪烁，主要用来提示错误，但会错位，解决不了-_-|| isf表示有无
int FlashRed(int nx ,int ny , double x ,double y , double curx ,double cury ,bool isf )
{
	if (isf) return 0;
	SDL_SetRenderDrawColor( Render ,0xff ,0,0,0);
	double w=W*1.0/nx,h=H*1.0/ny;
	cury=cury-h*(int(cury/h));
	int a=int ((x)/w) , b=int((y-cury)/h);
	SDL_Rect z=CreateRect(a*w ,b*h+cury , w,h );
	SDL_RenderFillRect(Render,&z);
}
//画黑块，包括被点击的变灰
void DrawBlack(short nx ,short ny)
{
	RenderBlack(Render);
	SDL_Rect dr;
	float w=W*1.0/nx,h=H*1.0/ny;
	for (int i=0;i<ny+1;i++)
	{
		dr=CreateRect(black[i].x ,black[i].y ,w,h);
		SDL_RenderFillRect(Render ,&dr);
	}
//四色相同即为灰，值越大越亮
	static int jj=0xc0;
	SDL_SetRenderDrawColor(Render ,jj ,jj ,jj ,jj);
	for (int i=0;i<ny+1;i++)
	if (black[i].area!=0)
		{
/*超级复杂的算式,加减1是修正坐标*/	dr=CreateRect(black[i].x+w*1.0/2-black[i].area*AREA/2*w+1 ,black[i].y+h/2-black[i].area*AREA/2*h+1 ,black[i].area*AREA*w-1 ,black[i].area*AREA*h-1  );
			SDL_RenderFillRect(Render ,&dr);
			
			switch(black[i].area)
			{
				case 4:
				black[i].area=5;
				break;
				case 5:
				black[i].area=6;
				break;
				case 6:
				black[i].area=8;
				break;
			}
			
//area -> 2 ->4 ->5  ->6 ->8
		}
		
}
int Jieji(int infor)
{
//nx,ny表示横竖方块量,tf是否触摸
I=0;
	int ny=4,nx=4,x=0,y=0,tf=0,Xi=-1;
	int cv;
	char NI[16]={0},NV[24]={0};
	SDL_Rect NiRect,NvRect;
//cury偏移,即控制移动的
	double cury=0,width=W*1.0/nx ,height=H*1.0/ny;
	SDL_Event event;
//初始化
	if (begin==0) JiejiInit(nx ,ny);
	begin=1;
	SDL_Rect fillyellow=CreateRect(0,height*(ny-1),W,height);
	RenderYellow(Render);
SDL_RenderFillRect(Render,&fillyellow);
	DrawWeb(nx,ny ,0,0);
	DrawBlack(nx,ny);
	
	V=V_Start;
	int fps=65;
	if (infor==1) return 0;

fprintf(fpe,"别踩白块儿刷新测试,\n1--代表经历了等待\n0--代表直接跳过了等待,\n若0很多,则代表帧率设置过大,\n刷新速度跟不上\n");
	SDL_FlushEvents(0x0000, 0xFFFF);
	SDL_WaitEvent(&event);
	if (event.type==SDL_FINGERDOWN)
	goto ff;
	while (1)
	{
		cv=tf=0;
		RenderWhite(Render);
//	SDL_RenderClear(Render);
	SDL_RenderFillRect(Render, NULL );
		DrawWeb(nx,ny ,0 ,cury );
		DrawBlack(nx,ny);
		if (V<V_Max)
		{
		V+=1.0/fps/4;
		if (V>V_Max) V=V_Max;
/*
		if (Tex[7]!=NULL)
		SDL_DestroyTexture(Tex[7]);
		sprintf(NV,"%2.3lf个/S",V);
*/
//		Tex[7]=Text(Render ,NV ,20,0xff);
//		x=CalTexWidth(Tex[7],Th);
//		NvRect= CreateRect(W-x+10,0,x,Th);
		}
//		SDL_RenderCopy(Render ,Tex[7] ,NULL,&NvRect);
		if (Xi!=I)
		{
		if (Tex[8]!=NULL)
		SDL_DestroyTexture(Tex[8]);
		sprintf(NI,"%d",I);
		Tex[8]=Text(Render,NI,20,0xff);
		x=CalTexWidth(Tex[8],Th);
		NiRect=CreateRect(W/2-x/2,0,x,Th);
		Xi=I;
		}
		SDL_RenderCopy(Render ,Tex[8] ,NULL,&NiRect);
		SDL_RenderPresent(Render);
//触摸判定
		if (SDL_PollEvent(&event))
		{
			ff:;
			switch (event.type)
			{
			case SDL_FINGERDOWN:
			x=event.tfinger.x*W;
			y=event.tfinger.y*H;
			tf=1;
			break;
			case SDL_FINGERMOTION:
//			x=event.tfinger.x*W;
//			y=event.tfinger.y*H;
			tf=0;
			break;
			case SDL_FINGERUP:
//			if (((clock()*1.0-wi)/ CLOCKS_PER_SEC)<0.15)

			tf=0;
			break;
			}
		}
		for (cv=0;cv<ny+1&&tf;cv++)
		{
#undef ADJUST_WAY_1
#ifdef ADJUST_WAY_1

//判定的后面带了一个尾巴，是为了一定的容错，刷新和点击并非同时做到
			if (x>black[cv].x -width/8&& x<black[cv].x+width*1.2&& y>black[cv].y-height/4&& y<black[cv].y+height+height/4
//&&black[cv].position 
			)
			
#else
//新的容错方式 height*V/fps
			if (x>black[cv].x -width/8&& x<black[cv].x+width*1.2&& y>black[cv].y-2*height*V/fps&& y<black[cv].y+height+1*height*V/fps
			)

#endif
			{
			black[cv].position=0;
			if (black[cv].area==0)
			{
			black[cv].area=4;
			I++;
			break;
			}
			cv=tf=0;
			}
		}
//点击并且没点到黑灰两种方块即失败
		if ((cv==ny+1)&&tf)
		{
		
		break;
		}
//最底下的快到底了
		if (black[0].y>H-height/2&&black[0].position)
		{
			x=black[0].x+5;
			y=black[0].y+10;
			break;
		}
//灰块过底,挪动方块并新建一个
		if (black[0].y>H)
		{
			for (cv=1;cv<ny+1;cv++)
			black[cv-1]=black[cv];
			--cv;
			black[cv].x=(rand()%nx)* (width);
		black[cv].y=black[cv-1].y-height;
		black[cv].position=1;
		black[cv].area=0;
		}
//移动,控制刷新频率,输出刷新信息
		cury+=height*V/fps;
		for (cv=0;cv<ny+1;cv++)
		black[cv].y+=height*V/fps;
//Control FPS
		fprintf(fpe,"%d ",SetFPS(fps));
		
	}
//失败,闪烁红块
	cv=0;
	while (cv++<8)
	{
		RenderWhite(Render);
	SDL_RenderFillRect(Render, NULL );
		DrawWeb(nx,ny ,0 ,cury );
		DrawBlack(nx,ny);
		FlashRed(nx,ny,x,y,0 ,cury,cv%2);
		SDL_RenderCopy(Render ,Tex[7] ,NULL,&NvRect);
		SDL_RenderCopy(Render ,Tex[8] ,NULL,&NiRect);
		SDL_RenderPresent(Render);
		SetFPS(8);
	}
	fprintf(fpe,"\nThe End Number----%d\n",I);
	fprintf(fpe,"The End V----%lf\n",V);
	fprintf(fpe,"FPS:%d n/s\n\n\n",fps);
	fflush(fpe);
	
		{
		SDL_FlushEvents(0x0000, 0xFFFF);
		SDL_RenderClear(Render);
		SDL_SetRenderDrawColor( Render ,0 ,0,0,0);
		SDL_RenderFillRect(Render, NULL );
		SDL_DestroyTexture(Tex[8]);	Tex[8]=Text(Render,NI,20,0xff,0xff,0xff,0xff);
		y=CalTexWidth(Tex[8],Th);
		NiRect=CreateRect(W/2-y,H/4,2*y,2*Th);
		SDL_RenderCopy(Render,Tex[8],NULL,&NiRect);
		SDL_RenderPresent(Render);
		
		SDL_WaitEvent(&event);
		
		return 0;
	}
	
	for (cv=0;cv<9;cv++)
	SDL_DestroyTexture(Tex[cv]);
}



//菜单,模式选取
int meun(int po)
{
	
/*
r_fill 控制的布局,无线村16像素字体
|---------------------|
|		 		|		 		|
|		 0  	| 	1 		|
|	 			|		 		|
|---------------------|
|	 			|	 			|
|	 	2  	| 	 3		|
|	 			|		 		|
|---------------------|
|	 			|	 			|
|	 	4  	| 	 5		|
|	 			|		 		|
|---------------------|
*/
	begin=move=0;
	int i=0;
	SDL_Rect r_mod[6] ,r_fill[6];
	int wi,x,y,modnum=6;
	SDL_Event event;
	Tex[0]=Text(Render ,"街机模式",20 ,0,0,0,0);
	Tex[1]=Text(Render , "禅模式" ,20 ,0xff ,0xff ,0xff ,0xff );
	Tex[2]=Text(Render , "待开发" ,20 ,0xff ,0xff ,0xff ,0xff );
	Tex[3]=Text(Render , "待开发" ,20 ,0 ,0 ,0 ,0 );
	Tex[4]=Text(Render , "待开发" ,20 ,0 ,0 ,0 ,0 );
	Tex[5]=Text(Render , "待开发" ,20 ,0xff ,0xff ,0xff ,0xff );
	
	for (x=1;x<modnum;x+=2)
	{
	wi=CalTexWidth(Tex[x],Th);
r_mod[x]=CreateRect(W/4*3-wi/2,(H*1.0/6)*x-Th/2,wi,Th);
	}
	for (x=0;x<modnum;x+=2)
	{
	wi=CalTexWidth(Tex[x],Th);
r_mod[x]=CreateRect(W/4-wi/2,(H*1.0/6)*(x+1)-Th/2,wi,Th);
	}
	bool cu=0;
	if(H/3!=H/3.0) cu=1;
	for (int c=0;c<modnum;c++)
r_fill[c]=CreateRect((c%2)*W/2,(H/3.0)*(int(sqrt(c*2+1))-1),W/2,H/3+int(c/2)*cu);
/* 以下等价于 121~122行
r_fill[0]=CreateRect(0,0,W/2,H/3);
r_fill[1]=CreateRect(W/2,0,W/2,H/3);
r_fill[2]=CreateRect(0,H/3,W/2,H/3+1*cu);
r_fill[3]=CreateRect(W/2,H/3,W/2,H/3+1*cu);
r_fill[4]=CreateRect(0,H/3*2,W/2,H/3+2*cu);
r_fill[5]=CreateRect(W/2,H/3*2,W/2,H/3+2*cu);
*/
	RenderWhite(Render);
	SDL_RenderClear(Render);
SDL_RenderFillRect(Render,NULL);
	RenderBlack(Render);
	SDL_RenderFillRect(Render, &r_fill[1]);
	SDL_RenderFillRect(Render, &r_fill[2]);
	SDL_RenderFillRect(Render, &r_fill[5]);
	for (int c=0;c<modnum;c++)
		SDL_RenderCopy(Render ,Tex[c] ,NULL ,&r_mod[c]);
	SDL_RenderPresent(Render);
SDL_FlushEvents(0x0000, 0xFFFF);
	while (1)
	{
     while (SDL_PollEvent(&event))
   	{
		switch (event.type)
		{
			case SDL_FINGERDOWN:
			x=event.tfinger.x*W;
			y=event.tfinger.y*H;
			wi=clock();
			break;
			
			case SDL_FINGERUP:
			if (((clock()*1.0-wi)/ CLOCKS_PER_SEC)<0.15)
			goto out;
			break;
		}
   	}
	}
out:;
zhankai:;

//ve越大，每次移动就越慢，时间也yiyang(当然，是在运行速度允许下)
	int ve=8 ;
	int v=W/2/ve;
	SDL_FlushEvents(0x0000, 0xFFFF);
	while (r_fill[4].x>=-W/2)
	{
		SDL_RenderClear(Render);
		RenderWhite(Render);
SDL_RenderFillRect(Render,NULL);
//根据触摸,选取模式,显示特效,并在底层显示模式样子
	if (x<W/2)
    {
    	if (y<H/3)
    	{
    	Jieji(1);
    	}
    	else
    	2;
    }
    else
    {
    	if (y<H/3)
    	Chan(1);
    	else 
    	3;
    }
//这个嵌套if..else,菜单选择特效
    if (r_fill[0].x>-W/2)
    {
    	r_mod[0].x-=v;
		r_mod[1].x+=v;
	RenderWhite(Render);
r_fill[0].x-=v;
SDL_RenderFillRect(Render, &r_fill[0]);
SDL_RenderFillRect(Render, &r_fill[3]);
SDL_RenderFillRect(Render, &r_fill[4]);
	RenderBlack(Render);
r_fill[1].x+=v;
		SDL_RenderFillRect(Render, &r_fill[1]);
		SDL_RenderFillRect(Render, &r_fill[2]);
		SDL_RenderFillRect(Render, &r_fill[5]);
    }
	else
	if (r_fill[2].x>=-W/2)
	{
		r_mod[2].x-=v;
		r_mod[3].x+=v;
	RenderWhite(Render);
r_fill[3].x+=v;
SDL_RenderFillRect(Render, &r_fill[3]);
SDL_RenderFillRect(Render, &r_fill[4]);
	RenderBlack(Render);
r_fill[2].x-=v;
		SDL_RenderFillRect(Render, &r_fill[2]);
		SDL_RenderFillRect(Render, &r_fill[5]);
	}
	else
	{
		r_mod[4].x-=v;
		r_mod[5].x+=v;
		RenderWhite(Render);
r_fill[4].x-=v;
SDL_RenderFillRect(Render, &r_fill[4]);
	RenderBlack(Render);
r_fill[5].x+=v;
		SDL_RenderFillRect(Render, &r_fill[5]);
	}

		for (int c=0;c<modnum;c++)
		SDL_RenderCopy(Render ,Tex[c] ,NULL ,&r_mod[c]);
	SDL_RenderPresent(Render);
		SetFPS(ve*6);
	}
	for (i=0;i<9;i++)
	{
		if (Tex[i]!=NULL)
		SDL_DestroyTexture(Tex[i]);
	}
//	SDL_Delay(200);
I=0;

    if (x<W/2)
    {
    	if (y<H/3)
    	Jieji(0);
    	else
    	return 3;
    }
    else
    {
    	if (y<H/3)
    	Chan(0);
    	else 
    	return 4;
    }
}

//画线函数，白色背景。LR左右被分成多少块，-1->NoDrawUD上下被分成多少块-1->NoDraw,curx,cury横纵偏移.
void DrawWeb(int LR ,int UD ,double curx ,double cury)
{
	double lrw,lrh;

	RenderBlack(Render);
	lrw=W*1.0/(LR);
	lrh=H*1.0/(UD);
	if (curx<0)
	while (curx<=-lrw) curx+=lrw;
	else while (curx>=lrw) curx-=lrw;
	if (cury<0)
	while (cury<=-lrh) cury+=lrh;
	else while (cury>=lrh) cury-=lrh;
	
//不知道把内括号去掉在有些编译器上会不会出错
	while ((--LR)>=-1)
	{
		SDL_RenderDrawLine(Render , (W/lrw-2-LR)*lrw+curx , 0 , (W/lrw-2-LR)*lrw+curx ,H );
	}
	while ((--UD)>=-1)
	SDL_RenderDrawLine(Render , 0 ,(H/lrh-2-UD)*lrh+cury ,W , (H/lrh-2-UD)*lrh+cury  );
}

int TQ_Load()
{
	
}
//初始化
int Init()
{
SDL_Init(SDL_INIT_EVERYTHING);
Win=SDL_CreateWindow("SDL_Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 640  , 480 , SDL_WINDOW_SHOWN);
  if (Win == NULL)
    return -1;
 Render=SDL_CreateRenderer(Win, -1,
 SDL_RENDERER_SOFTWARE
 );
  IMG_Init(IMG_INIT_PNG);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();
    // 打开字体/* 字体路径 /*字体大小
  font = TTF_OpenFont("./res/font.ttf", 28); SDL_GetWindowSize(Win,&W,&H);
  Th=H/10;
  return 0;
}