#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include <time.h>
  
float then = clock()/CLOCKS_PER_SEC;

void DeltaTime(float &DT)
{
	float now =  clock()/CLOCKS_PER_SEC;
	DT = now-then;
	then = now;
}
class vector
{
public:
float x;
float y;
float z;
float q;
vector( float a=0,  float b=0,  float c=0)
{
	x=a;
	y=b;
	z=c;
	q=0;
}

void invert()
{ 
	x = -x; 
	y = -y;
	x = -z;
}

float squarelen()
{
	return x*x+y*y+z*z;
}
float len()
{
	return sqrt(squarelen());
}

void normalise()
{
	float l =len();
	if(l>0) (*this)*=(1.0f/l);
}

vector normal()
{
	
	float l =len();
	if(l>0)
	{vector a =  (*this)*(1.0f/l);
	return a;
	}
	else return (*this);
}

void operator*=(const float &value)
{
x *= value;
y *= value;
z *= value;
}

vector operator*(const float &value) const
{
return vector(x*value, y*value, z*value);
}

float operator*(const vector &secondvector) const
{
return x*secondvector.x+ y*secondvector.y+ z*secondvector.z;
}

vector operator+(const vector &secondvector) const
{
return vector(x+secondvector.x, y+secondvector.y, z+secondvector.z);
}
void operator+=(const vector &secondvector) 
{
	x+=secondvector.x;
	y+=secondvector.y;
	z+=secondvector.z;
}

vector operator-(const vector &secondvector) const
{
return vector(x-secondvector.x, y-secondvector.y, z-secondvector.z);
}

void operator-=(const vector &secondvector) 
{
	x-=secondvector.x;
	y-=secondvector.y;
	z-=secondvector.z;
}

vector vecprod(vector &secondvector)
{
	return vector(y*secondvector.z - z*secondvector.y, z*secondvector.x - x * secondvector.z, x*secondvector.y - y*secondvector.x);
}

void rotate(float theta = 0 , vector axis = vector(0,1,0))
{
	float l = (*this).len();
	theta *= 2*3.14f/360.0f;
	float c = cos(theta);
	float s = sin(theta);
	float t=1-c;

	float a = (t*axis.x*axis.x+c);
	float b = t*axis.x*axis.y+s*axis.z;
	float d = t*axis.x*axis.z-s*axis.y;
	float e = t*axis.x*axis.y-s*axis.z;
	float f = (t*axis.y*axis.y+c);
	float g = t*axis.y*axis.z+s*axis.x;
	float h = t*axis.x*axis.z+s*axis.y;
	float i = t*axis.y*axis.z-s*axis.x;
	float j = (t*axis.z*axis.z+c);

	(*this).x = a*(*this).x+b*(*this).y+d*(*this).z;
	(*this).y = e*(*this).x+f*(*this).y+g*(*this).z;
	(*this).z = h*(*this).x+i*(*this).y+j*(*this).z;

	(*this).normalise();
	(*this)*=l;


	
	
}


};


#endif