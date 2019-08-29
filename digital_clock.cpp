#include<stdlib.h>
//#include<stdio.h>
#include<gl\glut.h>
#include<time.h>
//#include<iostream> 
#pragma warning(disable : 4996)
#define WT 1366
#define HT 705

using namespace std;

void digitPoint(int,int,int,int);
void wait();
int initPosition(int,int,int);
void clear(int, int, int, int);
void initial();
void timeTemp();
void timeCurrent();
void splitYear();
void digitRect(int, int, int);
int get12Hour();
void disColon();
void boundryAndArrows();
void arrowForDate();

time_t t;
clock_t tcount;
tm* timePtr;
int once = 0,y[4];
int count1 = 0;


struct Time
{
	int d, mo, y;
	int h, mi, s;
}T,C;

struct color
{
	float r, g, b;
	float r1=40, g1=10, b1=35;
}TC,MIC;

struct Param
{
	int a[13][7] = { { 1,1,1,0,1,1,1 },
	{ 0,0,0,0,0,1,1 },
	{ 0,1,1,1,1,1,0 },
	{ 0,0,1,1,1,1,1 },
	{ 1,0,0,1,0,1,1 },
	{ 1,0,1,1,1,0,1 },
	{ 1,1,1,1,1,0,1 },
	{ 0,0,1,0,0,1,1 },
	{ 1,1,1,1,1,1,1 },
	{ 1,0,1,1,1,1,1 },
	{ 1,1,1,1,0,1,1 },
	{ 1,1,1,0,0,1,0 },
	{ 1,0,1,0,0,1,1 } };
	int Tx = 100, Ty = 150, Th = 100, Tw = 20;
	int Dx = 35, Dy = 410, Dh = 125, Dw = 25;
	int Bxx[2][7] = { { Tx,Tx,Tx,Tx,Tx,Tx + Th - Tw,Tx + Th - Tw },
	                  { Dx,Dx,Dx,Dx,Dx,Dx + Dh - Dw,Dx + Dh - Dw } };
	int Byy[2][7] = { { Ty + Th - Tw,Ty,Ty + Th - Tw + Th - Tw,Ty + Th - Tw,Ty,Ty + Th - Tw,Ty },
	                  { Dy + Dh - Dw,Dy,Dy + Dh - Dw + Dh - Dw,Dy + Dh - Dw,Dy,Dy + Dh - Dw,Dy } };
	int Bww[2][7] = { { Tw,Tw,Th,Th,Th,Tw,Tw },
	                  { Dw,Dw,Dh,Dh,Dh,Dw,Dw } };
	int Bhh[2][7] = { { Th,Th,Tw,Tw,Tw,Th,Th },
	                  { Dh,Dh,Dw,Dw,Dw,Dh,Dh } };
	int Bp[2][9];
	int ok = initPosition(Th,Dh, 55);
	int bothPlusPos(int tORd,int i, int pos)
	{
		return (Bxx[tORd][i] +Bp[tORd][pos]);
	}
}ob;

int initPosition(int th, int dh, int d)
{
	int th1 = th;
	int dh1 = dh;
	ob.Bp[0][0] = 0;
	ob.Bp[0][1] = th = th1 + 10;
	ob.Bp[0][2] = th = th1 + th + 10 + d;
	ob.Bp[0][3] = th = th1 + th + 10;
	ob.Bp[0][4] = th = th1 + th + 10 + d;
	ob.Bp[0][5] = th = th1 + th + 10;
	ob.Bp[0][6] = th = th1 + th + 10 + d;
	ob.Bp[0][7] = th = th1 + th + 10;
	ob.Bp[0][8] = th = th1 + th - ob.Tw;
	ob.Bp[1][0] = 0;
	ob.Bp[1][1] = dh = dh1 + 10;
	ob.Bp[1][2] = dh = dh1 + dh + 10 + d + d;
	ob.Bp[1][3] = dh = dh1 + dh + 10;
	ob.Bp[1][4] = dh = dh1 + dh + 10 + d + d;
	ob.Bp[1][5] = dh = dh1 + dh + 10;
	ob.Bp[1][6] = dh = dh1 + dh + 10;
	ob.Bp[1][7] = dh = dh1 + dh + 10;
	return 1;
}

void initial()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, WT, 0.0, HT);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void timeTemp()
{
	t = time(NULL);
	timePtr = localtime(&t);
	T.d = (timePtr->tm_mday);
	T.mo = (timePtr->tm_mon) + 1;
	T.y = (timePtr->tm_year) + 1900;
	T.h = (timePtr->tm_hour);
	T.mi = (timePtr->tm_min);
	T.s = (timePtr->tm_sec);
}

void timeCurrent()
{
	t = time(NULL);
	timePtr = localtime(&t);
	C.d = (timePtr->tm_mday);
	C.mo = (timePtr->tm_mon) + 1;
	C.y = (timePtr->tm_year) + 1900;
	C.h = (timePtr->tm_hour);
	C.mi = (timePtr->tm_min);
	C.s = (timePtr->tm_sec);
}

void splitYear()
{
	int year = C.y;
	int n = 0;
	while (year != 0)
	{
		y[n] = year % 10;
		year = year / 10;
		n++;
	}
}

int get12Hour()
{
	if (C.h > 12)
	{
		ob.a[10][6] = 0;
		return (C.h - 12);
	}
	else
	{
		if (C.h == 12)
			ob.a[10][6] = 0;
		else
			ob.a[10][6] = 1;
		return C.h;
	}
}

void clear(int x, int y, int h, int w)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();
	glFlush();
}

void setColor()
{
   TC.r = rand() % 50;
	TC.g = rand() % 50;
	TC.b = rand() % 50;
	if ((TC.r == MIC.r) || (TC.g == MIC.g) || (TC.b == MIC.b))
		setColor();
	glColor3f(((float)TC.r+TC.r1) / 100, ((float)TC.g+TC.g1) / 100, ((float)TC.b+TC.b1) / 100);
}

color getMinColor()
{
	return TC;
}

void arrowForDate()
{
	//s(ob.Dx + ob.Bp[1][3] + ob.Dh + 10, ob.Dy + ob.Dh - ob.Dw, 25, 100);
	int x, y, h, w;
	x = ob.Dx + ob.Bp[1][1] + ob.Dh + 10, ob.Dy;
	y = ob.Dy + ob.Dh - ob.Dw;
	h = 100;
	w = 50;
	setColor();
	glBegin(GL_QUADS);
	glVertex2f(x + w, y + (h / 2));
	glVertex2f(x + h, y);
	glVertex2f(x + w, y - (h / 2));
	glVertex2f(x + ((h+w)/2) , y);
	glEnd();
	x=ob.Dx + ob.Bp[1][3] + ob.Dh + 10;
	glBegin(GL_QUADS);
	glVertex2f(x + w, y + (h / 2));
	glVertex2f(x + h, y);
	glVertex2f(x + w, y - (h / 2));
	glVertex2f(x + ((h + w) / 2), y);
	glEnd();
	glFlush();
}

void disColon()
{
	setColor();
	digitPoint(ob.Tx + ob.Bp[0][1] + ob.Th + 10+(ob.Tw/2), ob.Ty + ob.Tw+ (ob.Tw / 2), 25, 24);
	digitPoint(ob.Tx + ob.Bp[0][1] + ob.Th + 10+(ob.Tw / 2), ob.Ty + ob.Th+ (ob.Tw / 2), 25, 24);
	digitPoint(ob.Tx + ob.Bp[0][3] + ob.Th + 10+(ob.Tw / 2), ob.Ty + ob.Tw+ (ob.Tw / 2), 25, 24);
	digitPoint(ob.Tx + ob.Bp[0][3] + ob.Th + 10+(ob.Tw / 2), ob.Ty + ob.Th+ (ob.Tw / 2), 25, 24);
}

void boundryAndArrows()
{
	int x, y, h, w;
	x = 20;
	y = HT/2;
	h = 20;
	w = 5;
	setColor();
	glRecti(0,0,20,705);
	glRecti(0, 0, 1366, 30);
	glRecti(1340,0, 1366,705);
	glRecti(0, 685, 1366, 705);
	x = C.s * 11 + 20;
	glBegin(GL_QUADS);
	setColor();
	glVertex2f(x + w, y + (h / 2)); setColor();
	glVertex2f(x + h, y); setColor();
	glVertex2f(x + w, y - (h / 2)); setColor();
	glVertex2f(x + ((h + w) / 2), y); setColor();
	glEnd();
	x = 1366 - x;
	glBegin(GL_QUADS); setColor();
	glVertex2f(x - w, y + (h / 2)); setColor();
	glVertex2f(x - h, y); setColor();
	glVertex2f(x - w, y - (h / 2)); setColor();
	glVertex2f(x - ((h + w) / 2), y); setColor();
	glEnd();
	glFlush();
}

void digitPoint(int x,int y,int h,int w)
{
	float w2=0;
	glBegin(GL_POLYGON);
	if (h > w)
	{
		 w2 = (float)w / 2;
		glVertex2f(x, y + w);
		glVertex2f(x + w2, y + w2);
		glVertex2f(x + w, y + w);
		glVertex2f(x + w, y + h - w);
		glVertex2f(x + w2, y + h - w2);
		glVertex2f(x, y + h - w);
	}
	else
	{
		w2 = (float)h / 2;
		glVertex2f(x+h, y + h);
		glVertex2f(x + w2, y + w2);
		glVertex2f(x + h, y);
		glVertex2f(x + w-h, y);
		glVertex2f(x + w-w2, y + w2);
		glVertex2f(x+w-h, y+h);
	}
	glEnd();
	glFlush();
}

void digitRect(int tORd,int digi, int pos)
{
	for (int i = 0; i <=6; i++)
	{
		if (ob.a[digi][i] == 1)
		{
			digitPoint(ob.bothPlusPos(tORd,i, pos), ob.Byy[tORd][i], ob.Bhh[tORd][i], ob.Bww[tORd][i]);
		}
	}
}

void wait()
{
	while (clock() < tcount) {}
}

void display()
{
	int i = 0, j = 0, hour = 0, year = 0;
	tcount = clock() + CLOCKS_PER_SEC;
	timeCurrent();
	
	clear(ob.Tx + ob.Bp[0][4], ob.Ty, ob.Th - ob.Tw + ob.Th, ob.Bp[0][5] - ob.Bp[0][4]+ob.Th);
	//if (T.d != C.d || once == 0)
	if (T.mi != C.mi || once == 0)
	{
		clear(0, 0, HT, WT);
		boundryAndArrows();
		disColon();
		arrowForDate();
		splitYear();
		setColor();
		//cout << "R ="<<TC.r << "   G ="<<TC.g << "   B ="<<TC.b << endl;
		digitRect(1, (C.d / 10), 0);
		digitRect(1, (C.d % 10), 1);
		digitRect(1, (C.mo / 10), 2);
		digitRect(1, (C.mo % 10), 3);
		digitRect(1, y[3], 4);
		digitRect(1, y[2], 5);
		digitRect(1, y[1], 6);
		digitRect(1, y[0], 7);
	//}
	//if (T.mi != C.mi || once == 0 )
	//{
		hour = get12Hour();
		clear(ob.Tx + ob.Bp[0][2], ob.Ty, ob.Th - ob.Tw + ob.Th, ob.Bp[0][3] - ob.Bp[0][2] + ob.Th);
		clear(ob.Tx + ob.Bp[0][0], ob.Ty, ob.Th - ob.Tw + ob.Th, ob.Bp[0][1] - ob.Bp[0][0] + ob.Th);
		clear(ob.Tx + ob.Bp[0][6], ob.Ty, ob.Th - ob.Tw + ob.Th, ob.Bp[0][8] - ob.Bp[0][6] + ob.Th);
		setColor();
		MIC = getMinColor();
		digitRect(0,(hour / 10), 0);
		digitRect(0,(hour % 10), 1);
		digitRect(0,(C.mi / 10), 2);
		digitRect(0,(C.mi % 10), 3);
		setColor();
		digitRect(0, 10, 6);
		digitRect(0, 11, 7);
		digitRect(0, 12, 8);
		clear(20, 705 / 2-15, 30, 1316);
	}
	glColor3f(((float)MIC.r + MIC.r1) / 100, ((float)MIC.g + MIC.g1) / 100, ((float)MIC.b + MIC.b1) / 100);
		digitRect(0,(C.s/10), 4);
		digitRect(0,(C.s % 10), 5);
		boundryAndArrows();
		disColon();
		arrowForDate();
		once = 1;
		T = C;
	wait();
	display();
}

 int main(int argc, char** argv)
 { 
	 timeTemp();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WT, HT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DIGITAL CLOCK");
	glutDisplayFunc(display);
	initial();
	glutMainLoop();
}

