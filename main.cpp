#include<iostream>
#include<fstream>
#include<string>
#include"graphics.h"
#include"time.h"
#include"conio.h"
#include<deque>
#include<algorithm>
#include<mmsystem.h>//��ý�� ��Դ��
using namespace std;
#define MAX 8
#pragma comment(lib,"winmm.lib")//�ֶ����ؾ�̬����Դ
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
	//loadimage(&img, "����±���ͼ.jpg", 500, 700);//����ͼƬ
	//putimage(0, 0, &img);//��ʾͼƬ
	// ifstream ifs;
	//ifs.open("")
	settextcolor(BLACK);//����������ɫ ������ͨ����ԭɫ�ı� RGB(2,24,24)
	settextstyle(15, 0, "STXINGKA");//��������
	setbkmode(TRANSPARENT);//ʹ�ֵ���Ӱ��ʧ
	outtextxy(60, 640, "�÷֣�");//����Ļ���������
	outtextxy(170, 640, "����ֵ��");
	outtextxy(350, 640, "��߼�¼��");

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
	putimage(let[i].x, let[i].y, &img1, SRCAND);//������ͼ
	putimage(let[i].x, let[i].y, &img2, SRCPAINT);//������ͼ
	outtextxy(let[i].x + 22, let[i].y + 48, let[i].target );
}
void loadresource()
{
	loadimage(&img, "����±���ͼ.jpg", 500, 700);//����ͼƬ
	loadimage(&img1, "�ܲ�����ͼ.jpg", 50, 80);
	loadimage(&img2, "�ܲ�����ͼ.jpg", 50, 80);
	loadimage(&img3, "����ֵ.jpg", 20, 20);
	loadimage(&img4, "������ʧ.jpg", 20, 20);
}
void gameinclude(int record)
{
	//��ʾ�����������ѭ������ ����ס֮ǰ��ͼƬ
	putimage(0, 0, &img);//��ʾͼƬ
	settextcolor(BLUE);//����������ɫ ������ͨ����ԭɫ�ı� RGB(2,24,24)
	settextstyle(15, 0, "STXINGKA");//��������
	setbkmode(TRANSPARENT);//ʹ�ֵ���Ӱ��ʧ
	putimage(290, 640, &img3, SRCAND);
	//��ӡ����
	char b[20];
	sprintf_s(b, "%d", record);//��record ��ʽ��Ϊ�ַ�������
	outtextxy(110, 640, b);//ֻ������ַ���
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
		//��ʼ����ĸ
		Inittar(i);
	}
	BeginBatchDraw();//��ʼ˫����
	int record = 0;
	int life = 3;
	while (1)
	{
		
		gameinclude(record);
		outtextxy(420, 640,c);
		
		for (int i = 0; i < MAX; i++)
		{

			//��ʾ��ĸ
			showletter(i);
			let[i].y += let[i].speed;
			//�γ�ѭ��
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
				outtextxy(160, 330, "��Ϸ����");
				
					
				fwrite(&record, sizeof(int), 1, wt);
					while (1) {};

			
		}
	
		FlushBatchDraw();

		//������ĸ

		if (_kbhit())///_kbhit  �����Ƿ���ڰ��� �������ط���ֵ ���򷵻�0
		{

			char usekey = _getch();// -getch ��ȡ�������� ����Ҫ=�س�ȷ��  getchar��Ҫ�س�ȷ��
			if (usekey == ' ')//��ͣ
			{
				mciSendString("pause ��Ϸ��������.mp3", 0, 0, 0);
				settextstyle(50, 0, "STCAIYUN");
				outtextxy(200, 350, "��ͣ");
				while (_getch() != ' ');

			}
			mciSendString("resume ��Ϸ��������.mp3", 0, 0, 0);
			for (int i = 0; i < MAX; i++)
			{
				if (usekey == let[i].target || usekey == let[i].target + 32)//������������ĸ��ͬ ��ĸ���� ��������
				{
					mciSendString("close ��ը.mp3", 0, 0, 0);
					mciSendString("play ��ը.mp3", 0, 0, 0);
					Inittar(i);
					record++;
					break;


				}
			}
		}
		Sleep(50);

		//��̬����Դlib  ��̬����Դdll
		EndBatchDraw();


	}

}

int main()
{
	srand((unsigned int)time(NULL));
	initgraph(500, 700);
	//������������
	mciSendString("open ��ը.mp3", 0, 0, 0);//�������ļ� ָ�����ļ���֮ǰû�ж���
	mciSendString("open ��Ϸ��������.mp3", 0, 0, 0);
	mciSendString("play ��Ϸ��������.mp3 repeat", 0, 0, 0);

	loadresource();//����ͼƬ��Դ
	game();//��Ϸ����
	//closegraph();
	return 0;
}