void (* signal( int signo, void (*func)(int) )  )(int);

typedef void (*fp)(int);
fp func(int a) 
{

}
fp (*fpa)(int);

int main()
{
	fpa = func;
}
