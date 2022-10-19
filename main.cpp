#include<iostream>
#include<fstream>
#include<string>
#include"graphics.h"
#include"time.h"
#include"conio.h"
#include<deque>
#include<algorithm>
#include<mmsystem.h>//多媒体 资源库
using namespace std;
#define MAX 8
#pragma comment(lib,"winmm.lib")//手动加载静态库资源
IMAGE img;
IMAGE img1;
IMAGE img2;
IMAGE img3;
IMAGE img4;
class myprint
{
public:
	bool operator()(int a, int b)
	{
		return a > b;
	}
};
struct letter
{
	int x;
	int y;
	int speed;
	char target;

};
struct letter let[MAX];
void setbackboard()
{
	//loadimage(&img, "马里奥背景图.jpg", 500, 700);//加载图片
	//putimage(0, 0, &img);//显示图片
	// ifstream ifs;
	//ifs.open("")
	settextcolor(BLACK);//设置字体颜色 还可以通过三原色改变 RGB(2,24,24)
	settextstyle(15, 0, "STXINGKA");//设置字体
	setbkmode(TRANSPARENT);//使字的阴影消失
	outtextxy(60, 640, "得分：");//在屏幕上输出积分
	outtextxy(170, 640, "生命值：");
	outtextxy(350, 640, "最高记录：");

	putimage(230, 640, &img3,SRCAND);
	putimage(260, 640, &img3, SRCAND);


}
void Inittar(int i)
{
	//srand((unsigned int)time(NULL));
	(let[i]).x = rand()%400+50;
	(let[i]).y = rand() % 200 - 400;
	(let[i]).speed = rand() % 3 + 2;
	(let[i]).target = 'A' + rand() % 26;

}
void showletter(int i)
{
	putimage(let[i].x, let[i].y, &img1, SRCAND);//贴掩码图
	putimage(let[i].x, let[i].y, &img2, SRCPAINT);//贴背景图
	outtextxy(let[i].x + 22, let[i].y + 48, let[i].target );
}
void loadresource()
{
	loadimage(&img, "马里奥背景图.jpg", 500, 700);//加载图片
	loadimage(&img1, "萝卜掩码图.jpg", 50, 80);
	loadimage(&img2, "萝卜背景图.jpg", 50, 80);
	loadimage(&img3, "生命值.jpg", 20, 20);
	loadimage(&img4, "红心消失.jpg", 20, 20);
}
void gameinclude(int record)
{
	//显示背景必须放在循环里面 覆盖住之前的图片
	putimage(0, 0, &img);//显示图片
	settextcolor(BLUE);//设置字体颜色 还可以通过三原色改变 RGB(2,24,24)
	settextstyle(15, 0, "STXINGKA");//设置字体
	setbkmode(TRANSPARENT);//使字的阴影消失
	putimage(290, 640, &img3, SRCAND);
	//打印积分
	char b[20];
	sprintf_s(b, "%d", record);//将record 格式化为字符串类型
	outtextxy(110, 640, b);//只能输出字符串
	setbackboard();
}
void game()
{
	FILE* wt;
	fopen_s(&wt,"record.txt", "at+" );
	char c[20];
	int buf[2040] = { 0 };
	fread(buf, sizeof(int), 50, wt);
	sort(buf, &buf[1000], myprint());
	sprintf_s(c, "%d", buf[0]);



	
	//sort(d.begin(), d.end(), myprint());

	for (int i = 0; i < MAX; i++)
	{
		//初始化字母
		Inittar(i);
	}
	BeginBatchDraw();//开始双缓冲
	int record = 0;
	int life = 3;
	while (1)
	{
		
		gameinclude(record);
		outtextxy(420, 640,c);
		
		for (int i = 0; i < MAX; i++)
		{

			//显示字母
			showletter(i);
			let[i].y += let[i].speed;
			//形成循环
			if (let[i].y > 700)
			{
				Inittar(i);
				life--;

			}

		}
		if (life == 2)
		{
			putimage(290, 640, &img4,SRCPAINT);
		}
		if(life == 1)
		{
			putimage(290, 640, &img4, SRCPAINT);
			putimage(260, 640, &img4, SRCPAINT);
		}
		if (life == 0)
		{
			putimage(290, 640, &img4);
			putimage(260, 640, &img4);
			putimage(230, 640, &img4);
			
				settextstyle(50, 0, "STCAIYUN");
				outtextxy(160, 330, "游戏结束");
				
					
				fwrite(&record, sizeof(int), 1, wt);
					while (1) {};

			
		}
	
		FlushBatchDraw();

		//消除字母

		if (_kbhit())///_kbhit  监听是否存在按键 按键返回非零值 否则返回0
		{

			char usekey = _getch();// -getch 获取键盘输入 不需要=回车确认  getchar需要回车确认
			if (usekey == ' ')//暂停
			{
				mciSendString("pause 游戏背景音乐.mp3", 0, 0, 0);
				settextstyle(50, 0, "STCAIYUN");
				outtextxy(200, 350, "暂停");
				while (_getch() != ' ');

			}
			mciSendString("resume 游戏背景音乐.mp3", 0, 0, 0);
			for (int i = 0; i < MAX; i++)
			{
				if (usekey == let[i].target || usekey == let[i].target + 32)//键盘输入与字母相同 字母消除 重新生成
				{
					mciSendString("close 爆炸.mp3", 0, 0, 0);
					mciSendString("play 爆炸.mp3", 0, 0, 0);
					Inittar(i);
					record++;
					break;


				}
			}
		}
		Sleep(50);

		//静态库资源lib  动态库资源dll
		EndBatchDraw();


	}

}

int main()
{
	srand((unsigned int)time(NULL));
	initgraph(500, 700);
	//背景声音设置
	mciSendString("open 爆炸.mp3", 0, 0, 0);//打开声音文件 指令与文件名之前没有逗号
	mciSendString("open 游戏背景音乐.mp3", 0, 0, 0);
	mciSendString("play 游戏背景音乐.mp3 repeat", 0, 0, 0);

	loadresource();//加载图片资源
	game();//游戏主体
	//closegraph();
	return 0;
}