#include <stdio.h>
#define SIZE 512
int main()
{
	char buf[SIZE];
	if (setvbuf(stdin,buf,_IONBF,SIZE) != 0)
	{
		perror("将标准输入stdin的输入设置为无缓冲失败!\n");
		return 1;
	}
	printf("将标准输入stdin的输入设置为无缓冲成功!\n");
	printf("stdin类型为\n");
	if(stdin->_flags & _IO_UNBUFFERED)
	{
		printf("无缓冲\n");
	}
	if(stdin->_flags & _IO_LINE_BUF)
	{
		printf("行缓冲\n");
	}
	else
	{
		printf("全缓冲\n");
	}
	printf("缓冲区大小为%ld\n", stdin->_IO_buf_end - stdin->_IO_buf_base);
	printf("文件描述符为%d\n",fileno(stdin));
	if (setvbuf(stdin,buf,_IOFBF,SIZE) != 0)
	{
		perror("将标准输入stdin的输入设置为全缓冲失败!\n");
		return 2;
	}
	printf("修改标准输入stdin的类型成功\n");
	printf("stdin类型为\n");
	if(stdin->_flags & _IO_UNBUFFERED)
	{
		printf("无缓冲\n");
	}
	if(stdin->_flags & _IO_LINE_BUF)
	{
		printf("行缓冲\n");
	}
	else
	{
		printf("全缓冲\n");
	}
	printf("缓冲区大小为%ld\n", stdin->_IO_buf_end - stdin->_IO_buf_base);
	printf("文件描述符为%d\n",fileno(stdin));
	return 0;
}

