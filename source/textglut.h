#include <string>
#include <glut.h>
using namespace std;



//Text function
void text(string s, float x, float y,void * font)
{
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 750, 0.0, 500);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}



class FadingText
{
public:
	string t;
	float fadingTime;
	float timer;
	float X;
	float Y;
	void *Font;
	FadingText(string a = "string", float x = 0, float y = 0,void * font = GLUT_BITMAP_TIMES_ROMAN_24 ,float time = 3.0f)
	{
		t=a;
		fadingTime=time;
		timer=0;
		X=x;
		Y=y;
		Font=font;
	}

	void draw(float DT)
	{
		timer+=DT;
		float R = 1-(timer/fadingTime);
		if (fadingTime==0)glColor3f(1,1,1);
		else glColor3f(R,R,R);
		text(t,X,Y,Font);
		
	}
};