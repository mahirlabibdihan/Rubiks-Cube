typedef struct
{
	unsigned char R,G,B;
}Color;

typedef struct
{
	Color Block[3][3];
}Plane;

Plane Cube[6];

#define BlockLength 80
#define BlockSmallLength 30
/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"

int Front=0,Back=2,Left=3,Right=1,Top=4,Bottom=5;

#define Up 0
#define Middle 1
#define Down 2
#define VerticalUp 3
#define VerticalMiddle 4
#define VerticalDown 5
#define None -1
int Select=None;
/*
	function iDraw() is called again and again by the system.
*/

void iDrawBlock(int Left,int Bottom)
{
	double x[8]={Left+4,Left+BlockLength-4,Left+BlockLength,Left+BlockLength,Left+BlockLength-4,Left+4,Left,Left};
	double y[8]={Bottom,Bottom,Bottom+4,Bottom+BlockLength-4,Bottom+BlockLength,Bottom+BlockLength,Bottom+BlockLength-4,Bottom+4};

	iFilledPolygon(x,y,8);
}

void iDrawSmallBlock(int Left,int Bottom)
{
	double x[8]={Left+3,Left+BlockSmallLength-3,Left+BlockSmallLength,Left+BlockSmallLength,Left+BlockSmallLength-3,Left+3,Left,Left};
	double y[8]={Bottom,Bottom,Bottom+3,Bottom+BlockSmallLength-3,Bottom+BlockSmallLength,Bottom+BlockSmallLength,Bottom+BlockSmallLength-3,Bottom+3};

	iFilledPolygon(x,y,8);
}

void iDrawFront(int x,int y)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			iSetColor(Cube[Front].Block[i][j].R,Cube[Front].Block[i][j].G,Cube[Front].Block[i][j].B);
			iDrawBlock(x+j*(BlockLength+3),y-i*(BlockLength+3));
		}
	}
}

void iDrawSmall(int x,int y,int Face)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			iSetColor(Cube[Face].Block[i][j].R,Cube[Face].Block[i][j].G,Cube[Face].Block[i][j].B);
			iDrawSmallBlock(x+j*(BlockSmallLength+2),y-i*(BlockSmallLength+2));
		}
	}
}

int RandomR=255,RandomG=255,RandomB=0;
void iDrawSelection(int Face)
{
	if(time(NULL)%40==0)
	{
			RandomR=rand()%256;
	RandomG=rand()%256;
	RandomB=rand()%256;
	}

	iSetColor(150,150,150);
	if(Select==None)
	{
		iRectangle(828,382,250,250);
	}
	if(Select==Up)
	{
		iRectangle(828,549,250,82);
	}
	if(Select==Middle)
	{	
		iRectangle(828,465,250,82);
	}
	if(Select==Down)
	{
		iRectangle(828,382,250,82);
	}

	if(Select==VerticalUp)
	{
		iRectangle(828,382,82,250);
	}
	if(Select==VerticalMiddle)
	{
		iRectangle(912,382,82,250);
	}
	if(Select==VerticalDown)
	{
		iRectangle(995,382,82,250);
	}

}
void iDraw()
{
	iClear();
	iDrawFront(830,550);
	iDrawSmall(580,525,Left);
	iDrawSmall(1230,525,Right);
	iDrawSmall(905,220,Bottom);
	iDrawSmall(905,830,Top);
	iDrawSmall(905,950,Back);
	iDrawSelection(Front);
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
		if(key=='q')
	{
		exit(0);
	}
	if(key-1>='0'+None&&key-1<='0'+VerticalDown)
	{
		Select=key-'1';
	}


	
	//place your codes for other keys here
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
void iSpecialKeyboard(unsigned char key)
{
	int i;

	if(key==GLUT_KEY_LEFT)
	{
		if(Select==None)
		{
			int Temp=Front;
			Front=Right;
			Right=Back;
			Back=Left;
			Left=Temp;
		}

		else if(Select<=Down)
		{
			PlaySound("Data\\Music\\Reload.wav",NULL,SND_ASYNC);
			Sleep(100);
			for(i=0;i<3;i++)
			{

				Color Temp=Cube[Front].Block[Select][i];
				Cube[Front].Block[Select][i]=Cube[Right].Block[Select][i];
				Cube[Right].Block[Select][i]=Cube[Back].Block[Select][i];
				Cube[Back].Block[Select][i]=Cube[Left].Block[Select][i];
				Cube[Left].Block[Select][i]=Temp;

			}
			
		}
		else
		{
			if(Select>VerticalUp) Select--;
			else Select=VerticalDown;
		}
		
	}
	if(key==GLUT_KEY_RIGHT)
	{
		if(Select==None)
		{
			int Temp=Front;
			Front=Left;
			Left=Back;
			Back=Right;
			Right=Temp;
		}
		else if(Select<=Down)
		{
			PlaySound("Data\\Music\\Reload.wav",NULL,SND_ASYNC);
			Sleep(100);
			for(i=0;i<3;i++)
			{
				Color Temp=Cube[Front].Block[Select][i];
				Cube[Front].Block[Select][i]=Cube[Left].Block[Select][i];
				Cube[Left].Block[Select][i]=Cube[Back].Block[Select][i];
				Cube[Back].Block[Select][i]=Cube[Right].Block[Select][i];
				Cube[Right].Block[Select][i]=Temp;

			}
			
		}
		else
		{
			if(Select<VerticalDown) Select++;
			else Select=VerticalUp;
		}

	}
	if(key==GLUT_KEY_UP)
	{
		if(Select==None)
		{
			int Temp=Front;
			Front=Bottom;
			Bottom=Back;
			Back=Top;
			Top=Temp;
		}
		else if(Select>=VerticalUp)
		{
			PlaySound("Data\\Music\\Reload.wav",NULL,SND_ASYNC);
			Sleep(100);
			for(i=0;i<3;i++)
			{
				Color Temp=Cube[Front].Block[i][Select%3];
				Cube[Front].Block[i][Select%3]=Cube[Bottom].Block[i][Select%3];
				Cube[Bottom].Block[i][Select%3]=Cube[Back].Block[i][Select%3];
				Cube[Back].Block[i][Select%3]=Cube[Top].Block[i][Select%3];
				Cube[Top].Block[i][Select%3]=Temp;

			}
			
		}

		else
		{
			if(Select>Up) Select--;
			else Select=Down;
		}

	}
	if(key==GLUT_KEY_DOWN)
	{
		if(Select==None)
		{
			int Temp=Front;
			Front=Top;
			Top=Back;
			Back=Bottom;
			Bottom=Temp;
		}
		else if(Select>=VerticalUp)
		{
			PlaySound("Data\\Music\\Reload.wav",NULL,SND_ASYNC);
			Sleep(100);
			for(i=0;i<3;i++)
			{
				Color Temp=Cube[Front].Block[i][Select%3];
				Cube[Front].Block[i][Select%3]=Cube[Top].Block[i][Select%3];
				Cube[Top].Block[i][Select%3]=Cube[Back].Block[i][Select%3];
				Cube[Back].Block[i][Select%3]=Cube[Bottom].Block[i][Select%3];
				Cube[Bottom].Block[i][Select%3]=Temp;

			}
			
		}	

				else
		{
			if(Select<Down) Select++;
			else Select=Up;
		}

	}
}

void ballChange(){

}

void Initialize(int width=500, int height=500, char *title="iGraphics")
{
    iScreenHeight = height;
    iScreenWidth = width;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA) ;
    glutInitWindowSize(width , height ) ;
    glutInitWindowPosition(200, 10 ) ;
    glutCreateWindow(title) ;
    glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;
    glMatrixMode( GL_PROJECTION) ;
    glLoadIdentity() ;
    glOrtho(0.0 , width , 0.0 , height , -1.0 , 1.0) ;
    //glOrtho(-100.0 , 100.0 , -100.0 , 100.0 , -1.0 , 1.0) ;
    //SetTimer(0, 0, 10, timer_proc);
    glutFullScreen();

    iClear();

    glutDisplayFunc(displayFF) ;
    glutKeyboardFunc(keyboardHandler1FF); //normal
    glutSpecialFunc(keyboardHandler2FF); //special keys
    glutMouseFunc(mouseHandlerFF);
    glutMotionFunc(mouseMoveHandlerFF);
    glutIdleFunc(animFF) ;

    //
    // Setup Alpha channel testing.
    // If alpha value is greater than 0, then those
    // pixels will be rendered. Otherwise, they would not be rendered
    //
    glAlphaFunc(GL_GREATER,0.0f);
    glEnable(GL_ALPHA_TEST);

    glutMainLoop();
}


int main()
{
	int i,j;
	srand(time(NULL));
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Cube[Front].Block[i][j].R=255;
			Cube[Front].Block[i][j].G=0;
			Cube[Front].Block[i][j].B=0;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Cube[Back].Block[i][j].R=0;
			Cube[Back].Block[i][j].G=0;
			Cube[Back].Block[i][j].B=255;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Cube[Left].Block[i][j].R=255;
			Cube[Left].Block[i][j].G=255;
			Cube[Left].Block[i][j].B=255;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Cube[Right].Block[i][j].R=0;
			Cube[Right].Block[i][j].G=255;
			Cube[Right].Block[i][j].B=0;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Cube[Top].Block[i][j].R=255;
			Cube[Top].Block[i][j].G=255;
			Cube[Top].Block[i][j].B=0;
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			Cube[Bottom].Block[i][j].R=255;
			Cube[Bottom].Block[i][j].G=119;
			Cube[Bottom].Block[i][j].B=0;
		}
	}


	Initialize(1920,1080, "Ball Demo");

	return 0;
}

