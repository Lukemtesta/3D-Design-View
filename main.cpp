/*
 *  main.h
 *  
 *
 *  Created by Luke Testa on 21/11/2011.
 *  Copyright 2011 University of Surrey. All rights reserved.
 *
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"


using namespace std;

float yposition=0.0f, xposition=0.0f;



float _angle=0;									// Declares Global Variable
float _cameraAngle=0;
float xaxis=0.0,yaxis=0.0, xrotation, yrotation, angle, BOOLEAN_ACTION, press, i=0, y=1.0f;


 //Rotating using mouse
int rotation(int x, int y)
{
	glutPostRedisplay();						// Tells GLUT Scene has Changed
		
	int angle;
	
	if( (x>0) && (y>0) )
		angle = sqrt((x*x) + (y*y));
	if ( (x<0) || (y<0) )
	{
		angle = sqrt((x*x) + (y*y));   
		angle *= -1;
	}

	//cout << "\n" << angle;
	
	return angle;
} 
		

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				 //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture 

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	glClearColor(1.0f,1.0f,1.0f,1.0f);			// Change Background to Blue
	
	Image* image = loadBMP("key1.bmp");
	_textureId = loadTexture(image);
	delete image;
}



void keyup(unsigned char key, int x, int y)
{
	if(key == 9)
		BOOLEAN_ACTION = 0;
	else {
		BOOLEAN_ACTION = 1;
	}

	if(BOOLEAN_ACTION == 0)
		press = 0;
}


// Monitor Keyboard Action
void handleKeypress (unsigned char key, int x, int y)
{	
	switch(key)
	{
		case 27:
			exit(0);
		case 9:
			xrotation = (x-619);
			yrotation = (y- 363);
			press = 1;
			//cout << "\n" << xrotation << "   " << yrotation << "\n";
			break;
	}
	
	glutPostRedisplay();						// Tells GLUT Scene has Changed
}


// Called When Window is Resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);									// Resizes Window to New Width and Height
	glMatrixMode(GL_PROJECTION);							// Prepares Matrix Dimensions
	glLoadIdentity();										// Sets Initial Camera Angle to (0,0,0)
	gluPerspective(45.0, (double)w/(double)h, 1.0, 200.0);	// Sets Users Sight Angle to 45 Degrees, 1 and 200 Sets Z Dimensions to Distance of Eye
	glutPostRedisplay();
}

void frontlineBackground(float x, float z)
{
	glPopMatrix();
	glTranslatef(0.0f,0.0f,-5.0f);
	
	if(press == 1)
		glRotatef(_angle, yrotation, xrotation, 0.0f);
	else 
		glRotatef(i, 1.0f, 1.0f, 0.0f);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	
	glPushMatrix();
	
	glBegin(GL_QUADS); //Begin quadrilateral coordinates
	
	glColor3f(1.0f,1.0f,1.0f);
	
	
	glTexCoord2f(-1.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f,0.0f);
	
	glTexCoord2f(-1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f,0.0f);
	
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f,0.0f);
	
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f,0.0f);
	
	glDisable(GL_TEXTURE_2D);

	
	glColor3f(0.0f,0.0f,0.0f);
    glVertex3f(-1.0f, 0.0f,0.0f);
    glVertex3f(-1.0f, 1.0f,0.0f);
    glVertex3f(-1.0f, 1.0f,-0.2f);
    glVertex3f(-1.0f, 0.0f,-0.2f);
	
    glVertex3f(0.0f, 0.0f,0.0f);
    glVertex3f(0.0f, 1.0f,0.0f);
    glVertex3f(0.0f, 1.0f,-0.2f);
    glVertex3f(0.0f, 0.0f,-0.2f);
	
	glVertex3f(-1.0f, 0.0f,0.0f);
    glVertex3f(-1.0f, 0.0f,-0.2f);
    glVertex3f(0.0f, 0.0f,-0.2f);
    glVertex3f(0.0f, 0.0f,0.0f);
	
	
	
	
	glColor3f(0.8f,0.8f,0.9f);
	
    glVertex3f(-1.0f, -0.1f,-0.2f);	
    glVertex3f(-1.0f, 1.1f,-0.2f);
    glVertex3f(0.0f, 1.1f,-0.2f);
    glVertex3f(0.0f, -0.1f,-0.2f);
	
	glColor3f(0.0f,0.0f,0.0f);
    glVertex3f(-1.0f, -0.1f,-0.3f);	
    glVertex3f(-1.0f, 1.1f,-0.3f);
    glVertex3f(0.0f, 1.1f,-0.3f);
    glVertex3f(0.0f, -0.1f,-0.3f);
	
	glVertex3f(-1.0f, -0.1f,-0.2f);
    glVertex3f(-1.0f, -0.1f,-0.3f);
    glVertex3f(0.0f, -0.1f,-0.3f);
    glVertex3f(0.0f, -0.1f,-0.2f);
	
	glVertex3f(-1.0f, 1.1f,-0.2f);
    glVertex3f(-1.0f, 1.1f,-0.3f);
    glVertex3f(0.0f, 1.1f,-0.3f);
    glVertex3f(0.0f, 1.1f,-0.2f);
	
	
	
	
	glVertex3f(-1.0f, -0.1f,-0.2f);
    glVertex3f(-1.0f, -0.1f,-0.3f);
    glVertex3f(-1.0f, 1.1f,-0.3f);
    glVertex3f(-1.0f, 1.1f,-0.2f);

	glEnd();
	
	glPopMatrix();
			  
	glutPostRedisplay();


}




//Draws the 3D Scene
void drawScene()
{
//	float xposition = -4.0f, z=0.0f;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
	
	frontlineBackground(xaxis, yaxis);
	
	glutSwapBuffers(); //Send the 3D scene to the screen
}






// Varies Camera Angle Over Time Program is Running
void update(int value)
{
	static int x=0;

	i++;
	
	if(i>=360)
		i -= 360;
	
	glutKeyboardUpFunc(keyup);
	glutKeyboardFunc(handleKeypress);
	_angle = rotation(xrotation,yrotation);
	
	glutTimerFunc(10, update, 0);		// Recurrsion that calls Angle Redraw Function camera_rotate Every nms (n=10ms)
}





  
int main(int argc, char** argv)
{
	glutInit(&argc, argv);											// Initializes GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);		// Sets RGB colour, Lighting and Depth
	glutInitWindowSize(600, 600);									// Sets Default Program Window Dimensions
	
	glutCreateWindow("Home CLS - 3D Design View");			// Title of Window
	
	initRendering();													// Calls 3D Rendering Function
	
	cout << "\n\n\n\n\n\n\n******INSTRUCTIONS******\n\n\n\n\n" << "Hold Tab + Move Mouse =  Rotate\n\n\n" << "ESC = EXIT\n\n\n\n\n\n\n\n";
	
	glutDisplayFunc(drawScene);											// Calls Draw Scene Function
	glutKeyboardFunc(handleKeypress);								// Takes Data From Keyboard Strokes and Processes Data
	glutReshapeFunc(handleResize);										// Calls Window Rezise Function
	
	glutKeyboardUpFunc(keyup);
	
	glutTimerFunc(10, update, 0);
	
	glutMainLoop();													// Loops Main Function
	
	return 0;
}
