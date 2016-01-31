#include <stdlib.h>
#include <sstream>
#include "parts.h"






//Hide the Console Window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")



int main( void )
{


	int SCORE=0;//to keep score...
	string a = "SCORE:";
	string score;
	string hoops;
	stringstream ss;
	stringstream hoo;
	string endg = "Your HighScore was : ";
	
	

	ball *Balls[1];
	int bal=1;

	hoop *Hoops[21];
	int h=21;

	float before[21];

	edge wall(vector(10.950f, 0.95f, 0),vector(-10.95f, 0.95f, 0),0);
	edge wallleft(vector(-0.95f, 10.95f, 0),vector(-0.95f, -10.95f, 0),0);
	edge wallright(vector(1.95f, -10.95f, 0),vector(1.95f, 10.95f, 0),0);
	edge floor(vector(-10.950f, -0.95f, 0),vector(10.95f, -0.95f, 0),0);
	
	//DeltaTime variable and a useful boolean for when you
	//controling the game states.
	bool gamestate = 0;
	float DT;
	float time;
	bool Alpha = 1;
	float speed = 0.5;
	int *x = new int;
	int *y = new int;
	float Xmax , Ymax;
	float Ux , Uy;
	bool reset = 0;
	bool endgame = 0;

	float pointsX , pointsY;


	//Some variables to handle bunus points system:
	bool mouse_clicked = 0;
	int hoops_done = 0;



	for (int i = 0 ; i<bal ; i++)
	{
		Balls[i]= new ball(vector(0,0,0),vector(0,1,0),0.05);
		for (int j = 0 ; j <h ;j++)
		{
			float random = (rand()%3);
			Hoops[j]= new hoop(vector(2+1.5*j,-0.5+random*0.5,0),vector(2+1.5*j,random*0.5-0.1,0));
			before[j] = (Balls[i]->position-Hoops[j]->mHorizon.start)*Hoops[j]->mHorizon.unit2;;	
		}
	}

	
	

	

	string s = "PRESS 'D' TO START THE GAME ";
	//string d = "CONTROL WITH 'A' AND 'S'";
	
	
	int running = GL_TRUE;
	// Initialize GLFW
	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE ) ;

	// Open an OpenGL window
	if( !glfwOpenWindow( 800,480, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glfwSetWindowTitle( "''Hoops-1.0  Jumps Through The Hoops!!!''" );  

    glOrtho(-1, 2, -1, 1, -1.0, 1.0);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2);


	string welcome1 = "Hi there! You see that Little Red Ball onn your screen? THAT'S ME , HOOPS!!!";
	string welcome2 = "Whenever you click on the screen i will jump up to meet your cursor!";
	string welcome3 = "Go Ahead! Give it a try!";

	
	
	Balls[0]->Red=1.0f;
	Balls[0]->Green=0;
	Balls[0]->Blue=0;


	FadingText t(hoops,540,400,GLUT_BITMAP_TIMES_ROMAN_24,3.0);
	

	
// Main loop
	while( running )
	{
		//Calculate the DeltaTime
		//The function is in "vector.h" and it uses the clock() function.
		DeltaTime(DT);
		time+=DT;
		//if(DT>0.01)DT=0.005;
		glClear( GL_COLOR_BUFFER_BIT );
		DrawBoard();

		
			
				

		if(Hoops[20]->mHorizon.start.x<-1) endgame = 1;

		if(endgame)
		{
			
			Hoops[20]->mHorizon= edge(vector(1.5,0.5,0),vector(1.95,0.5,0));
		

		}


		

		
		
		
		glColor3f(1,1,1);
		ss<<SCORE;
	    score=ss.str();
		ss.str("");
		text(score,640,450,GLUT_BITMAP_TIMES_ROMAN_24);
		text(a,550,450,GLUT_BITMAP_TIMES_ROMAN_24);

		hoo<<"+";
		hoo<<hoops_done;
	    hoops=hoo.str();
		hoo.str("");
		t.t=hoops;
		
		
		
		
		
		
		
		

		//Move the player around with 'A' and 'S'
		if(glfwGetKey('A'))
		{
			
		}

		
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)&&Alpha)
		{
			mouse_clicked=1;
			hoops_done=0;
			glfwGetMousePos( x, y );
			Xmax = ((*x)/(800.0f/3.0f)-1);
			Ymax = (1-(*y)/240.0f);
			if(*x<800&&*y<480){
			
			for (int i = 0 ; i<bal ; i++)
	        {
				//if(Balls[i]->position.y<-0.5&&Ymax>-0.5)
				//{
				Xmax-=Balls[i]->position.x;
				Ymax -= Balls[i]->position.y;
				if(Ymax>=0)
				{
				Uy = sqrt(2*10.0f*Ymax);
				Ux = Xmax* 10.0f /Uy;
				
				Balls[i]->velocity=vector(Ux,Uy,0);
				}
				//else Balls[i]->velocity=(vector(Xmax+Balls[i]->position.x,Ymax+Balls[i]->position.y,0)-Balls[i]->position).normal()*2;
				}
			//}
			}
			Alpha = 0;
		}	
		if(!glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)&&Alpha==0)Alpha=1;
	

		//if(glfwGetKey('F')&&Alpha)
		//{
		//	for (int i = 0 ; i<bal ; i++)
	    //    {
		//		
		//		Balls[i]->velocity+=vector(0,0.3f,0);
				
		//	}
		//	Alpha = 0;
		//}	
		//if(!glfwGetKey('F')&&Alpha==0)Alpha=1;

		



		
		

		for(int j=0;j<h;j++)
		{
			Hoops[j]->DrawBack();
			
		}

		for (int i = 0 ; i<bal ; i++)
		{
			
			Balls[i]->draw();
			Balls[i]->bounce(wallleft);
			Balls[i]->bounce(wallright);
			Balls[i]->bounce(floor);
			Balls[i]->bounce(wall);
	
			for(int j=0;j<h;j++)
		    {
			
			Balls[i]->GoThroughHoop(Hoops[j],before[j],hoops_done,mouse_clicked,SCORE,reset);
			if(reset)
			{
				t.timer=0;
				pointsX=Hoops[j]->mHorizon.end.x;
				pointsY=Hoops[j]->mHorizon.end.y;
			}

			Hoops[j]->DrawFront();
			before[j] =(Balls[i]->position-Hoops[j]->mHorizon.start)*Hoops[j]->mHorizon.unit2;
			if(endgame==0)Hoops[j]->moveleft(DT,speed);
			
			
			
			}

			Balls[i]->move(DT);
		}

		t.draw(DT);
		reset = 0;
		// Swap front and back rendering buffers
		

		glfwSwapBuffers();
		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
		glfwGetWindowParam( GLFW_OPENED );


		
	}
	
	
	// Close window and terminate GLFW
	glfwTerminate();
	// Exit program
	exit( EXIT_SUCCESS );
}

