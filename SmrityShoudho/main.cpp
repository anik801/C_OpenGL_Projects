#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "GL\imageloader.h"
#include "math.h"

using namespace std;

GLuint _textureId,_textureId2,_textureId3,_textureId4; //The id of the texture


float xFlag=0.0f, yFlag=0.0f, zFlag=0.0f,rotateStep=0,scaleFactor=1;
float xAngle=0.0f,yAngle=0.0f;
float xValue=0.0f,yValue=0.0f;

void updateRotaitonAngle(){

    if(xFlag==1.0f){
        xAngle +=rotateStep;
        if (xAngle > 360) {
            xAngle -= 360;
        }

    }else if(yFlag==1.0f){
        yAngle +=rotateStep;
        if (yAngle > 360) {
            yAngle -= 360;
        }
    }

    glutPostRedisplay();
}



int light = 1;
int rotateFlag = -1;
float cameraAngle = 0.0f;

void makeDefault(){
    scaleFactor=1;
    rotateStep=0.0f;
    xAngle=0.0f;
    yAngle=0.0f;
    xFlag=0.0f;
    yFlag=0.0f;
    zFlag=0.0f;

    xValue=0.0f;
    yValue=0.0f;
    cameraAngle = 0.0f;
}


//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
        case '1':
            if(light == 1){
                light = 0;
                glDisable(GL_LIGHT0); //Disable light #0
                glDisable(GL_LIGHT1); //Disable light #1
            }else{
                light = 1;
                glEnable(GL_LIGHT0); //Enable light #0
                glEnable(GL_LIGHT1); //Enable light #1
            }
            //exit(0);
            break;
        case 32:
            //space bar
            rotateFlag *= -1;
            if(rotateFlag == -1){
                makeDefault();
            }
            break;
        case 13:
            //Enter key
            makeDefault();
            updateRotaitonAngle();
            break;
        case '+':
            scaleFactor+=0.1f;
            break;
        case '-':
            scaleFactor-=0.1f;
            break;
        case 'w':
            yValue+=0.5;
            break;
        case 's':
            yValue-=0.5;
            break;
        case 'a':
            xValue+=0.5;
            break;
        case 'd':
            xValue-=0.5;
            break;


	}

}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            //left arrow
            rotateStep=1.5f;
            xFlag=0.0f;
            yFlag=1.0f;
            zFlag=0.0f;
            break;

        case GLUT_KEY_RIGHT:
            //right arrow
            rotateStep=-1.5f;
            xFlag=0.0f;
            yFlag=1.0f;
            zFlag=0.0f;
            break;

        case GLUT_KEY_UP:
            //up arrow
            rotateStep=1.5f;
            xFlag=1.0f;
            yFlag=0.0f;
            zFlag=0.0f;
            break;

        case GLUT_KEY_DOWN:
            //down arrow
            rotateStep=-1.5f;
            xFlag=1.0f;
            yFlag=0.0f;
            zFlag=0.0f;
            break;
    }
    updateRotaitonAngle();
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

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_LIGHT2); //Enable light #2
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading

	Image* image = loadBMP("C:\\Users\\John\\Desktop\\redBrick.bmp");
	_textureId = loadTexture(image);
	delete image;

	Image* image2 = loadBMP("C:\\Users\\John\\Desktop\\concrete.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("C:\\Users\\John\\Desktop\\edge.bmp");
	_textureId3 = loadTexture(image3);
	delete image3;
}




//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


void drawBase(){
	glBegin(GL_QUADS);
//front
glNormal3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-4.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.0f, -2.5f, 0.0f);
	glTexCoord2f(16.0f, 1.0f);	glVertex3f(4.0f, -2.5f, 0.0f);
	glTexCoord2f(16.0f, 0.0f);	glVertex3f(4.0f, -3.0f, 0.0f);

//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-4.0f, -3.0f, -8.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-4.0f, -2.5f, -8.0f);
	glTexCoord2f(16.0f, 1.0f);	glVertex3f(4.0f, -2.5f, -8.0f);
	glTexCoord2f(16.0f, 0.0f);	glVertex3f(4.0f, -3.0f, -8.0f);

//Left
//glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-4.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 8.0f);	glVertex3f(-4.0f, -3.0f, -8.0f);
	glTexCoord2f(1.0f, 8.0f);	glVertex3f(-4.0f, -2.5f, -8.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-4.0f, -2.5f, 0.0f);


//Right
//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(4.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 8.0f);	glVertex3f(4.0f, -3.0f, -8.0f);
	glTexCoord2f(1.0f, 8.0f);	glVertex3f(4.0f, -2.5f, -8.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(4.0f, -2.5f, 0.0f);


//Bottom
//glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-4.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 8.0f);	glVertex3f(-4.0f, -3.0f, -8.0f);
	glTexCoord2f(16.0f, 8.0f);	glVertex3f(4.0f, -3.0f, -8.0f);
	glTexCoord2f(16.0f, 0.0f);	glVertex3f(4.0f, -3.0f, 0.0f);


//Top
//glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-4.0f, -2.5f, 0.0f);
	glTexCoord2f(0.0f, 8.0f);	glVertex3f(-4.0f, -2.5f, -8.0f);
	glTexCoord2f(16.0f, 8.0f);	glVertex3f(4.0f, -2.5f, -8.0f);
	glTexCoord2f(16.0f, 0.0f);	glVertex3f(4.0f, -2.5f, 0.0f);


	glEnd();
}


void drawPillarTops(){
    glBegin(GL_QUADS);

glNormal3f(1.0f, 1.0f, 1.0f);
    //Middle front rectangle
    //Front
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-0.18f, -0.25f, -1.40f);
	glTexCoord2f(0.0f, .10f);	glVertex3f(-0.17f, -0.10f, -1.40f);
	glTexCoord2f(1.0f, .10f);	glVertex3f(0.17f, -0.10f, -1.40f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.18f, -0.25f, -1.40f);

    //Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -1.0f, -6.85f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(-3.9f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-4.0f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, -1.0f, -7.0f);

//Top
//glColor3f(1.0f, 1.0f, 1.0f);
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -1.0f, -6.85f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(3.9f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(4.0f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, -1.0f, -7.0f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -.59f, -6.0f);
    glTexCoord2f(0.0f, 4.0f);	glVertex3f(-3.4f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-3.51f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, -.59f, -6.15f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -.59f, -6.0f);
    glTexCoord2f(0.0f, 4.0f);	glVertex3f(3.4f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(3.51f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, -.59f, -6.15f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, -5.15f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(-2.85f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-2.96f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 0.0f, -5.3f);


//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, -5.15f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(2.85f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(2.96f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 0.0f, -5.3f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 0.93f, -4.35f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(-2.29f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-2.40f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 0.93f, -4.5f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 0.93f, -4.35f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(2.29f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(2.40f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 0.93f, -4.5f);


//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 1.86f, -3.45f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(-1.73f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-1.84f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 1.86f, -3.6f);



//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 1.86f, -3.45f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(1.73f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(1.84f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 1.86f, -3.6f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 2.79f, -2.73f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(-1.09f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-1.20f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 2.79f, -2.8f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 2.79f, -2.73f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(1.09f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(1.20f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 2.79f, -2.8f);

//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 3.8f, -1.75f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(-.44f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-0.55f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 3.8f, -1.9f);


//Top
//glNormal3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 3.8f, -1.75f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(.44f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(0.55f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 3.8f, -1.9f);


    glEnd();
}

void drawPillars(){
    glBegin(GL_QUADS);

// >>>> Start 1st pillar <<<<   //
//Left half
//Back
glNormal3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -7.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, -1.0f, -7.0f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(-4.0f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(-4.0f, -2.5f, -1.0f);

//Front
//glColor3f(0.0f, 0.0f, 1.0f);
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -6.85f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, -1.0f, -6.85f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-3.9f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-3.9f, -2.5f, -1.0f);




//Right Half
//Back
//glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -7.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, -1.0f, -7.0f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(4.0f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(4.0f, -2.5f, -1.0f);

//Front
//glColor3f(0.0f, 0.0f, 1.0f);
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -6.85f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, -1.0f, -6.85f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(3.9f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.9f, -2.5f, -1.0f);



// >>>> Start 2nd pillar <<<< //
//Left half
//Back

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -6.15f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, -.59f, -6.15f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(-3.51f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(-3.51f, -2.5f, -1.0f);

//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -6.0f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, -.59f, -6.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-3.4f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-3.4f, -2.5f, -1.0f);


//Right half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -6.15f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, -.59f, -6.15f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(3.51f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(3.51f, -2.5f, -1.0f);

//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -6.0f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, -.59f, -6.0f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(3.4f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(3.4f, -2.5f, -1.0f);



//    >>>> End 2nd pillar <<<<   //


// >>>> Start 3rd pillar <<<< //
//Left half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -5.3f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 0.0f, -5.3f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(-2.96f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(-2.96f, -2.5f, -1.0f);

//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -5.15f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 0.0f, -5.15f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-2.85f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-2.85f, -2.5f, -1.0f);




//Right half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -5.3f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 0.0f, -5.3f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(2.96f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(2.96f, -2.5f, -1.0f);

//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -5.15f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 0.0f, -5.15f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(2.85f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.85f, -2.5f, -1.0f);



//    >>>> End 3rd pillar <<<<   //


// >>>> Start 4th pillar <<<< //
//Left half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -4.5f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 0.93f, -4.5f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(-2.40f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(-2.40f, -2.5f, -1.0f);

//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -4.35f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 0.93f, -4.35f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-2.29f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-2.29f, -2.5f, -1.0f);




//Right half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -4.5f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 0.93f, -4.5f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(2.40f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(2.40f, -2.5f, -1.0f);

//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -4.35f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 0.93f, -4.35f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(2.29f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.29f, -2.5f, -1.0f);



//    >>>> End 4th pillar <<<<   //


// >>>> Start 5th pillar <<<< //
//Left half
//Back
//glNormal3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 1.86f, -3.6f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(-1.84f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(-1.84f, -2.5f, -1.0f);


//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -3.45f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 1.86f, -3.45f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-1.73f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.73f, -2.5f, -1.0f);



//Right half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -3.6f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 1.86f, -3.6f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(1.84f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(1.84f, -2.5f, -1.0f);


//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -3.45f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 1.86f, -3.45f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(1.73f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.73f, -2.5f, -1.0f);



// >>>> End 5th pillar <<<< //

// >>>> Start 6th pillar <<<< //
//Left half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -2.8f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 2.79f, -2.8f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(-1.20f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(-1.20f, -2.5f, -1.0f);


//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -2.73f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 2.79f, -2.73f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-1.09f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.09f, -2.5f, -1.0f);



//Right half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -2.8f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 2.79f, -2.8f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(1.20f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(1.20f, -2.5f, -1.0f);


//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -2.73f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 2.79f, -2.73f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(1.09f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.09f, -2.5f, -1.0f);



// >>>> End 6th pillar <<<< //

// >>>> Start 7th pillar <<<< //
//Left half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -1.9f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 3.8f, -1.9f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(-0.55f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(-0.55f, -2.5f, -1.0f);

//Front
//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -1.75f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 3.8f, -1.75f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(-.44f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-.44f, -2.5f, -1.0f);



//Right half
//Back
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -1.9f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 3.8f, -1.9f);
	glTexCoord2f(4.0f, 1.0f);	glVertex3f(0.55f, -2.5f, -1.0f);
	glTexCoord2f(4.0f, 0.0f);	glVertex3f(0.55f, -2.5f, -1.0f);

//Front
//glNormal3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.5f, -1.75f);
	glTexCoord2f(0.0f, 4.0f);	glVertex3f(0.0f, 3.8f, -1.75f);
	glTexCoord2f(1.0f, 4.0f);	glVertex3f(.44f, -2.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(.44f, -2.5f, -1.0f);


// >>>> End 7th pillar <<<< //
    glEnd();
}


void drawCenterTop(){
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 1.0f, 1.0f);
    //Middle front rectangle
    //Front
    /*
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-0.18f, -0.25f, -1.40f);
	glTexCoord2f(0.0f, .10f);	glVertex3f(-0.17f, -0.10f, -1.40f);
	glTexCoord2f(1.0f, .10f);	glVertex3f(0.17f, -0.10f, -1.40f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.18f, -0.25f, -1.40f);
*/
    //Top
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-0.18f, -0.10f, -1.40f);
	glTexCoord2f(0.0f, 8.0f);	glVertex3f(0.0f, -0.10f, -1.66f);
	glTexCoord2f(16.0f, 8.0f);	glVertex3f(0.0f, -0.10f, -1.66f);
	glTexCoord2f(16.0f, 0.0f);	glVertex3f(0.18f, -0.10f, -1.40f);

    //Bottom
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-0.18f, -0.25f, -1.40f);
	glTexCoord2f(0.0f, 8.0f);	glVertex3f(0.0f, -0.25f, -1.66f);
	glTexCoord2f(16.0f, 8.0f);	glVertex3f(0.0f, -0.25f, -1.66f);
	glTexCoord2f(16.0f, 0.0f);	glVertex3f(0.18f, -0.25f, -1.40f);


// Lower triangle
    glTexCoord2f(1.0f, 1.0f);   glVertex3f(-0.15f, -0.23f, -1.50f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.15f, -0.23f, -1.50f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, -2.4f, -1.66f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, -2.4f, -1.66f);
// Upper triangle
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(-0.15f, -0.10f, -1.50f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.15f, -0.10f, -1.50f);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 2.13f, -1.66f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.0f, 2.13f, -1.66f);

	glEnd();
}


void drawCenterBottom(){
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 1.0f, 1.0f);
//Base front rectangle
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-0.44f, -2.5f, -1.0f);
	glTexCoord2f(0.0f, 0.5f);	glVertex3f(-0.44f, -2.4f, -1.0f);
	glTexCoord2f(2.0f, 0.5f);	glVertex3f(0.44f, -2.4f, -1.0f);
	glTexCoord2f(2.0f, 0.0f);	glVertex3f(0.44f, -2.5f, -1.0f);

	glEnd();

//Base top triangle
	glBegin(GL_TRIANGLES);

    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-0.44f, -2.4f, -1.0f);
	glTexCoord2f(1.5f, 1.5f);	glVertex3f(0.0f, -2.2f, -1.66f);
	glTexCoord2f(3.0f, 0.0f);	glVertex3f(0.44f, -2.4f, -1.0f);

	glEnd();
}


void autoRotate(int value) {
	cameraAngle += 0.5f;
	if (cameraAngle > 360) {
		cameraAngle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, autoRotate, 0);
}



float diff=0.2f,maxX=10.0f;
float lx=maxX, ly=0.0f;
int lxFlag=0,lyFlag=1;

void moveLight(int value) {

    if(lxFlag==0){
        lx -= diff;
        if(lx<=-maxX){
            lxFlag=1;
        }
    }else{
        lx += diff;
        if(lx>=maxX){
            lxFlag=0;
        }
    }

    if(lx>=0){
        ly+=diff;
    }else{
        ly-=diff;
    }


	glutPostRedisplay();
	glutTimerFunc(25, moveLight, 0);
}

void showLights(){
/*
    //Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
/*
*/

	//Add directed light
	GLfloat lightColor1[] = {1.0f, 0.721f, 0.074f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {lx, ly, 2, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

}


void drawFilledCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	float x = r;//we start at angle = 0

	float y = 0;

	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -y;
		float ty = x;

		//add the tangential vector

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}


void drawFlag(){
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(2.0, 2.0, -1.0);
        glVertex3f(5.0, 2.0, -1.0);
        glVertex3f(5.0, 0.0, -1.0);
        glVertex3f(2.0, 0.0, -1.0);
    glEnd();


    glTranslatef(0.3, 0.0, -0.99);
    glColor3f(1.0, 0.0, 0.0);
    drawFilledCircle(3.2, 1.0, 0.4, 100);
    glTranslatef(-0.3, 0.0, 0.99);

    glTranslatef(0.3, 0.0, -1.01);
    glColor3f(1.0, 0.0, 0.0);
    drawFilledCircle(3.2, 1.0, 0.4, 100);
    glTranslatef(-0.3, 0.0, 1.09);


    glColor3f(1.0, 1.0, 1.0);

}

void drawFlagStand(){
    glBegin(GL_QUADS);
        glVertex3f(0.8, 1.0, -0.99);
        glVertex3f(0.9, 1.0, -0.99);
        glVertex3f(0.9, -3.0, -0.99);
        glVertex3f(0.8, -3.0, -0.99);
    glEnd();
}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -8.0f);



    showLights();



    if(rotateFlag==1){
        // auto rotation
        glTranslatef(0.0f, 0.0f, -4.0f);
        glRotatef(cameraAngle, 0.0f, 1.0f, 0.0f); //John // Stopping object movement
        glTranslatef(0.0f, 0.0f, 4.0f);
    }



    // up-down key rotation
    glTranslatef(0.0f, 0.0f, -4.0f);
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 4.0f);

    // left-right key rotation
    glTranslatef(0.0f, 0.0f, -4.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 4.0f);


    glTranslatef(xValue,yValue,0);
    glScalef(1.0,0.7,1.0);
    glScalef(scaleFactor,scaleFactor,scaleFactor);



//======================================================================================
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glColor3f(5.0f, 0.0f, 0.0f);
        drawBase();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//======================================================================================



//======================================================================================
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glColor3f(0.0f, 1.0f, 1.0f);
        drawPillars();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//======================================================================================



//======================================================================================
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId3);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glColor3f(0.0f, 1.0f, 1.0f);
        drawPillarTops();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//======================================================================================



//======================================================================================
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        drawCenterTop();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//======================================================================================



//======================================================================================
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        drawCenterBottom();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//======================================================================================


//======================================================================================
    glPushMatrix();
        glTranslatef(30.0, 25.0, -100.0);
        glColor3f(1.0, 1.0, 1.0);

        glScalef(0.8, 1.0, 1.0);
        drawFilledCircle(3.0, 6.0, 2.0, 100);   //Moon

        glTranslatef(-30.0, -25.0, 100.0);
    glPopMatrix();
//======================================================================================


//======================================================================================
    glTranslatef(1.0, 0.0, 0.7);
    glPushMatrix();
        glScalef(0.5, 0.5, 1.0);
        glScalef(0.8, 1.0, 1.0);
        drawFlag();
    glPopMatrix();

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        drawFlagStand();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glTranslatef(1.0, 0.0, -0.7);
//======================================================================================


	glutSwapBuffers();
}





int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);  //width x height

	//Create the window
	glutCreateWindow("Smrity Shoudho");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutSpecialFunc(SpecialInput);

	glutTimerFunc(25, autoRotate, 0); //Add a timer
	glutTimerFunc(25,moveLight,0);



	glutMainLoop();
	return 0;
}

