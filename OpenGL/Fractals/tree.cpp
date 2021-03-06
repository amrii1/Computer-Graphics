/*
This implementation of Fractal  will be done using L-Systems (Lindenmayer system). 
This utlizes a grammar based approach for building these systems making them easily changable.
The class LSys is is defined create these grammar based structure currently a simple tree 
is shown as the grammar. 

Since this file uses the class defined within LSys.cpp this needed to be contained within the compilation 
statement as follows:

 g++ tree.cpp LSys.cpp  -lGL -lGLU -lglut -lm 
 
*/

//Internal Libraries 
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <float.h>

//Local Files 
#include "LSys.h"

using namespace std; 

//Screen Size Macros 
#define MAX_WIDTH 500 
#define MAX_HEIGHT 500 

//Iterations Macro 
#define MAX_VALUE 8

//Extrema Values for Resize 
static float left = FLT_MAX;   //X-Min
static float right = -FLT_MAX; //X-Max

static float bottom = FLT_MAX; //Y-Min
static float top = -FLT_MAX;   //Y-Max

/*
    This function will resize the vector of lines passed to it. 
The resize consists of scalling the figure to 75% of the screen size and 
The center along the X-axis. 
*/
void resize( vector<line> &start){
    
    //Find the Extremas of the lines 
    for ( int b =0; b< start.size(); b++ ){
        
        //Find the Max x within the first line 
        if( start[b].a.x < ::left)
            ::left = start[b].a.x; 

        else if ( start[b].a.x> ::right)
            ::right = start[b].a.x; 

        //Find the Max x within the Second line 
        if( start[b].b.x < ::left)
            ::left = start[b].b.x; 

         else if ( start[b].b.x> ::right)
            ::right = start[b].b.x; 
      
        //Find the Max y within the first line 
        if( start[b].a.y > ::top)
            ::top = start[b].a.y; 
            
        else if( start[b].a.y < ::bottom)
            ::bottom = start[b].a.y; 

        //Find the Max x within the second line 
        if( start[b].b.y > ::top)
            ::top = start[b].b.y; 

        else if( start[b].b.y < ::bottom)
            ::bottom = start[b].b.y ; 
            
    }

    //Find Width and Height of the image 
    float Width, Height  = 0; 
    
    if( ::left < 0 && ::right > 0 ){ //Is there a negative part
        Width = abs(::left) + ::right;
    }
    else { // All positive 
        Width = abs(::right) - abs (::left);
    }

    if( ::top > 0 && ::bottom < 0 ){ //Is there a negative part
        Height = abs(::bottom) + ::top;
    }
    else { // All positive
        Height = abs(::top) - abs (::bottom);
    }

    float span = Width > Height ? Width : Height; 

    //Scale to 75% and center in the window 
    for( int b = 0; b < start.size(); b++){
        start[b].a.x = ((start[b].a.x/span)*(MAX_WIDTH*.75)) +(MAX_WIDTH/2);
        start[b].a.y = ((start[b].a.y/span)*(MAX_HEIGHT*.75));

        start[b].b.x = ((start[b].b.x/span)*(MAX_WIDTH*.75)) +(MAX_WIDTH/2);
        start[b].b.y = ((start[b].b.y/span)*(MAX_HEIGHT*.75));
    }
    
}


/*
    This function will create a tree using the LSys Class included above. It will pass the 
    grammar to the LSys and generate all lines in the window. 

*/
void tree_construction( ){
    //Use the LSys Constructor of the following parameters: Axoim, F, X, Length of Line, Rotation(phi)
    LSys snowflake = LSys("X","FF", "-F[+F][---X]+F-F[++++X]-X", 1, 13.0);

    vector<line> lines = snowflake.buildLSys( MAX_VALUE ); 
    resize(lines); 

    for ( int b = 0; b< lines.size() ; b++){
      
            glColor3f(1.0 ,0,0); //Color of the Tree 

            //Build Lines 
            glBegin(GL_LINES);
                glVertex2f(lines[b].a.x, lines[b].a.y);
                glVertex2f(lines[b].b.x, lines[b].b.y);
            glEnd();    
        }     
            glFlush(); 

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    tree_construction(); //Starts the construction 
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, MAX_WIDTH, 0, MAX_HEIGHT);
}

int main(int argc, char **argv, char**arg){
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(MAX_WIDTH/2, MAX_HEIGHT/2);
	glutInitWindowSize(MAX_WIDTH,MAX_HEIGHT);
	glutCreateWindow("L-Systems");
    init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}