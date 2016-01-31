#ifndef BALL_H
#define BALL_H
#define GLFW_DLL
#include <GL/glfw.h>
#include "vector.h"
#include "textglut.h"







//This class can be used to simulate the edges of any polygon.
class edge  
{
public:
	
		bool isPlayer;
		vector start , end , unit1, unit2,unit3;
		float length;

		/*The Constructor takes the start and end of the edge and calculates
		the length and two unit vectors. "unit1" is the unit vector parallel to the edge
		and "unit2" is perpendicular. */
		edge( vector st = vector(0,0,0) , vector en = vector(0.5f,0.5f,0.5f),bool isplayer=0)
		{
			start = st;
			end = en; 
			unit1 = (end-start);
			unit1.normalise();
			unit3 = start.vecprod(unit1).normal();
			if(unit3.z>0)unit2 =unit3.vecprod(unit1);
			else unit2 =unit1.vecprod(unit3);
			unit2.normalise();
			length = (end-start).len();
			isPlayer=isplayer;
		}
		
		void draw()
		{
			//I use a triangle fan to draw an rectangle of width 0.05
			glBegin(GL_LINES);
			glVertex3f(start.x, start.y,0);    
			glVertex3f( end.x , end.y  , 0); 

			//If you want to see where the unit2 vector is:
			//glColor3f(	1,0,0);
			//glLineWidth(4);
			//glVertex3f(start.x, start.y,0); 
			//glVertex3f(start.x+unit2.x/5.0f, start.y+unit2.y/5.0f,0); 
			//glColor3f(	1,1,1);
            
            glEnd();
		}

		//A simple function to move the player.
		void move(vector &speed, float &DT)
		{
			start +=speed*DT;
			end +=speed*DT;
		}
		void MoveStart(vector &n)
		{
			start=n;
			end=start+unit1*length;
		}
		void rotate(float degrees,vector axis)
		{
			unit1.rotate(degrees,axis);
			unit2.rotate(degrees,axis);
			end=start+unit1*length;
		}








};



class hoop
{
public:

	edge mHorizon;
	bool mActive;
	
	

	hoop(vector start = vector(1,0,0) , vector end = vector(1,0.5,0),bool isActive=1)
	{
		mHorizon = edge(start,end,0);
		mActive = isActive;
		
	}

	void moveleft(float DT,float speed)
	{
		mHorizon.move(vector(-speed,0,0),DT);
	}


	//I have separated the drawing of the back and front parts of the hoops.
	//This way i can first draw the back part , then the ball, and then the front part.	
	void DrawFront()
	{
		float centerX=0.5* (mHorizon.start.x + mHorizon.end.x);
		float centerY=0.5* (mHorizon.start.y + mHorizon.end.y);

		
		if(mActive)	glColor3f(0,0,1);
		else glColor3f(0,1,0);
		glLineWidth(4);
		glBegin(GL_LINE_STRIP);

			

        for (int i=-90; i < 90; i++)
		{
			float degInRad = i*3.14159/180;
			float x = cos(degInRad)*0.05;
			float y = sin(degInRad)*mHorizon.length*0.5;
			float a = x*mHorizon.unit1.y-y*mHorizon.unit1.x;
			float b = x*mHorizon.unit1.x+y*mHorizon.unit1.y;
			a += centerX ;
			b += centerY;

			 glVertex2f(a,b);
		  }
 
		 glEnd();
		 glLineWidth(2);
		 glColor3f(1,1,1);
	}

	void DrawBack()
	{
		float centerX=0.5* (mHorizon.start.x + mHorizon.end.x);
		float centerY=0.5* (mHorizon.start.y + mHorizon.end.y);

		if(mActive)	glColor3f(0,0,1);
		else glColor3f(0,1,0);
		
		glBegin(GL_LINE_STRIP);
 
        for (int i=90; i < 270; i++)
		{
			float degInRad = i*3.14159/180;
			float x = cos(degInRad)*0.05;
			float y = sin(degInRad)*mHorizon.length*0.5;
			float a = x*mHorizon.unit1.y-y*mHorizon.unit1.x;
			float b = x*mHorizon.unit1.x+y*mHorizon.unit1.y;
			a += centerX ;
			b += centerY;
			
			 glVertex2f(a,b);
		
		  }
 
		 glEnd();
		 glColor3f(1,1,1);
	}
};



//This class represents the pong ball.
class ball
{
public:

		vector position;
		vector velocity;
		float radius;
		float Red;
		float Green;
		float Blue;
		float mass;
		

	
		ball(vector pos = vector(0,0,0), vector vel = vector(0,0,0),float R=0.05,float Mass = 1.0f)
		{
			position = pos;
			velocity = vel;
			radius = R;
			Red = rand()%10/10.0f;
			Green = rand()%10/10.0f;
			Blue = rand()%10/10.0f;
			mass = Mass;
			
		}

		
		
		void move(float &DT)
		{
			//Friction:
			//velocity-=velocity.normal()*(0.1*DT);


			//gravity
			velocity.y -= 10.0f*DT;

			
			position += velocity*DT;
		}

		void GoThroughHoop(hoop *h , float before,int &hoops_done,bool &mouse_clicked,int &score,bool &reset)
		{
			vector a = position-h->mHorizon.start;
			vector b = position-h->mHorizon.end;
			
			
			if((a*h->mHorizon.unit1)>=0&&(a*h->mHorizon.unit1)<=h->mHorizon.length)
			{ 
				if((a*h->mHorizon.unit2)*before<=0)
				{
					reset=1;
					
					if(mouse_clicked==1)
					{
						//You get one point for one hoop in a row;
						hoops_done = 1;
						mouse_clicked=0;
						
						
						
					}
					//+6 points for 3 hoops in a row;
					else if(mouse_clicked==0 && hoops_done ==3)hoops_done = 6;
					//+10 points for 4 hoops in a row;
					else if(mouse_clicked==0 && hoops_done ==6)hoops_done = 10;
					//+20 points for 5 hoops in a row,max 40 points;
					else if(mouse_clicked==0 && hoops_done ==10)hoops_done = 20;
					//+3 points for 2 hoops in a row;
					else hoops_done = 3;

					if(h->mActive==1)h->mActive=0 ;
					else h->mActive=1;

					score+=hoops_done;
					
					
				}
				
			}

			if(a.len()<=radius && velocity *a.normal()<0)
			{
				//penalty if you collide with the hoop:
				score--;
				velocity-=a.normal()*((velocity*a.normal())*2);

			}
			if (b.len()<=radius && velocity * b.normal()<0)
			{
				score--;
				velocity-=b.normal()*((velocity*b.normal())*2);
			}
		}







		/*The bounce function checks for collision with an edge 
		and calculates the speed if a collision occurs.*/
		void bounce( edge & p )
		{
			vector a = position-p.start;
			vector b = position - p.end;
			vector c;

					
			//if the ball is somewhere above the player
			//then the projection(dot product) of vector "a" on "unit1"
			//will be >0 and less than the length.

			if(a*p.unit1>=0&&a*p.unit1<=p.length&&(a*p.unit2)<=radius)
			{
				//if the distance is less than the radius, and the closing velocity is negative 
				
					position+=p.unit2*(radius-a*p.unit2);
					if(velocity*p.unit2<=0){
					velocity-=p.unit2*((velocity*p.unit2)*2);
					velocity*=(1.0f/1.2f);
					}

													
			}

			//If the ball colides with either the start or the end:
			else if (a*p.unit2>0&&a.len()<radius && velocity *a.normal()<0)
			{
				velocity-=a.normal()*((velocity*a.normal())*2);
			}
			else if (b*p.unit2>0&&b.len()<radius && velocity * b.normal()<0)
			{
				velocity-=b.normal()*((velocity*b.normal())*2);
			}

		}

			
		//The Draw function makes a regular polygon with 36 sides.
		void draw()
		{
			glColor3f(Red,Green,Blue);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(position.x, position.y,0.0);
			for (float angle = 0 ; angle<=360; angle +=10 )glVertex3f(position.x + sin(angle*(2*3.14/360)) * radius, position.y + cos(angle*(2*3.14/360)) * radius,0.0);
			glEnd();
			glColor3f(1,1,1);
		}


		//Simple collision with another ball

		void collide(ball *second)
		{
			vector delta = second->position-position;
			vector normal = delta.normal();
			float  distance = delta.len();
			vector v1n, v2n;
			float closing_velocity = velocity*normal-second->velocity*normal;

			if(distance<=radius+second->radius)
			{
				//if the balls are overlapping , push them apart.
				position-=normal*(radius+second->radius-distance)*0.5;
				second->position+=normal*(radius+second->radius-distance)*0.5;
				
				if(closing_velocity>=0)
				{	
					//Resolve the Collision.

					v2n = normal*(second->velocity*normal);
					v1n = normal*(velocity*normal);

					second->velocity-=v2n;
					second->velocity+=v1n;//*(1/1.1f);

					velocity-=v1n;
					velocity+=v2n;//*(1/1.1f);
				}
			}
		}
			



};

void DrawBoard()
{

	glColor3f(0.5,0.5,0.5);
		
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(-1,-1);
		glVertex2f(-0.95,-1);
		glVertex2f(-0.95,1);
		glVertex2f(-1,1);
		glEnd();
	
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(1.95,-1);
		glVertex2f(2,-1);
		glVertex2f(2,1);
		glVertex2f(1.95,1);
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(-1,0.95);
		glVertex2f(2,0.95);
		glVertex2f(2,1);
		glVertex2f(-1,1);
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(-1,-0.95);
		glVertex2f(2,-0.95);
		glVertex2f(2,-1);
		glVertex2f(-1,-1);
		glEnd();

		for(int i = 0 ; i<40 ; i++)
		{
			glColor3f(0,0,0);
			glBegin(GL_LINES);
			glVertex2f(-1,-1+0.1*i);
			glVertex2f(+2,-1+0.1*i);
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(-1+0.1*i,-1);
			glVertex2f(-1+0.1*i,1);
			glEnd();
		}


}
#endif