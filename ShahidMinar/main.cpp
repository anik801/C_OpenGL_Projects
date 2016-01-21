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


//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;

	}

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
	glShadeModel(GL_SMOOTH); //Enable smooth shading

}


//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}



float cameraAngle = 0.0f;
void autoRotate(int value) {
	cameraAngle += 0.5f;
	if (cameraAngle > 360) {
		cameraAngle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, autoRotate, 0);
}



float lightIntensity = 0.0f;
int lightFlag = 1;

void moveLight(int value) {
    if(lightFlag==0){
        lightIntensity -= 0.01f;
    }else{
        lightIntensity += 0.01f;
    }


    if(lightIntensity>=1.0f){
        lightFlag = 0;
    }else if(lightIntensity<=0.0f){
        lightFlag = 1;
    }

	glutPostRedisplay();
	glutTimerFunc(25, moveLight, 0);
}

void showLights(){

    //Add ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


	//Add directed light
	GLfloat lightColor1[] = {lightIntensity, lightIntensity, lightIntensity, 0.0f};
	GLfloat lightPos1[] = {0.0, 10.0, 2.0, 1.0f};
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


void drawGround(){
    glBegin(GL_QUADS);


    glNormal3f(0.0f, 1.0f, 0.0f);

    //Top
    glVertex3f(-15.0, -4.0, 0.0);
	glVertex3f(-15.0, -4.0, -20.0);
	glVertex3f(15.0, -4.0, -20.0);
	glVertex3f(15.0, -4.0, 0.0);


	glEnd();
}

void drawSquarePillar(){
    glBegin(GL_QUADS);


    glNormal3f(1.0f, 1.0f, 1.0f);

    //front left
    glVertex3f(-4.5, -4.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.0, 2.0, -10.0);
	glVertex3f(-4.0, -4.0, -10.0);

	//front right
    glVertex3f(-2.5, -4.0, -10.0);
	glVertex3f(-2.5, 2.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.0);
	glVertex3f(-2.0, -4.0, -10.0);

	//back left
    glVertex3f(-4.5, -4.0, -10.5);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-4.0, 2.0, -10.5);
	glVertex3f(-4.0, -4.0, -10.5);

	//back right
    glVertex3f(-2.5, -4.0, -10.5);
	glVertex3f(-2.5, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, -4.0, -10.5);

	//left left
    glVertex3f(-4.5, -4.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-4.5, -4.0, -10.5);

	//left right
    glVertex3f(-4.0, -4.0, -10.0);
	glVertex3f(-4.0, 2.0, -10.0);
	glVertex3f(-4.0, 2.0, -10.5);
	glVertex3f(-4.0, -4.0, -10.5);

	//right left
    glVertex3f(-2.5, -4.0, -10.0);
	glVertex3f(-2.5, 2.0, -10.0);
	glVertex3f(-2.5, 2.0, -10.5);
	glVertex3f(-2.5, -4.0, -10.5);

	//right right
    glVertex3f(-2.0, -4.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, -4.0, -10.5);


	//top down
    glVertex3f(-4.5, 1.5, -10.0);
	glVertex3f(-4.5, 1.5, -10.5);
	glVertex3f(-2.0, 1.5, -10.5);
	glVertex3f(-2.0, 1.5, -10.0);

	//top up
    glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.0);

	//top front
    glVertex3f(-4.5, 1.5, -10.0);
	glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.0);
	glVertex3f(-2.0, 1.5, -10.0);

	//top back
    glVertex3f(-4.5, 1.5, -10.5);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, 1.5, -10.5);


	//base front
    glVertex3f(-5.0, -4.0, -9.5);
	glVertex3f(-5.0, -3.5, -9.5);
	glVertex3f(-1.5, -3.5, -9.5);
	glVertex3f(-1.5, -4.0, -9.5);

	//base back
    glVertex3f(-5.0, -4.0, -11.0);
	glVertex3f(-5.0, -3.5, -11.0);
	glVertex3f(-1.5, -3.5, -11.0);
	glVertex3f(-1.5, -4.0, -11.0);

	//base left
	glVertex3f(-5.0, -4.0, -9.5);
	glVertex3f(-5.0, -3.5, -9.5);
	glVertex3f(-5.0, -3.5, -11.0);
	glVertex3f(-5.0, -4.0, -11.0);

	//base right
	glVertex3f(-1.5, -4.0, -9.5);
	glVertex3f(-1.5, -3.5, -9.5);
	glVertex3f(-1.5, -3.5, -11.0);
	glVertex3f(-1.5, -4.0, -11.0);

	//base top
	glVertex3f(-5.0, -3.5, -9.5);
	glVertex3f(-5.0, -3.5, -11.0);
	glVertex3f(-1.5, -3.5, -11.0);
	glVertex3f(-1.5, -3.5, -9.5);


	glEnd();
}


void drawCenterPillars(){
    glBegin(GL_QUADS);


    glNormal3f(1.0f, 1.0f, 1.0f);


//////////////////
    //upper front left
    glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.5, 4.0, -8.0);
	glVertex3f(-4.2, 4.0, -8.0);
	glVertex3f(-4.0, 2.0, -10.0);

	//upper front mid
    glVertex3f(-2.5, 2.0, -10.0);
	glVertex3f(-2.4, 4.0, -8.0);
	glVertex3f(-2.1, 4.0, -8.0);
	glVertex3f(-2.0, 2.0, -10.0);

	//upper front right
    glVertex3f(-0.5, 2.0, -10.0);
	glVertex3f(-0.3, 4.0, -8.0);
	glVertex3f(-0.0, 4.0, -8.0);
	glVertex3f(-0.0, 2.0, -10.0);
//////////////////


//////////////////
    //upper back left
    glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-4.5, 4.0, -8.5);
	glVertex3f(-4.2, 4.0, -8.5);
	glVertex3f(-4.0, 2.0, -10.5);

	//upper back mid
    glVertex3f(-2.5, 2.0, -10.5);
	glVertex3f(-2.4, 4.0, -8.5);
	glVertex3f(-2.1, 4.0, -8.5);
	glVertex3f(-2.0, 2.0, -10.5);

	//upper back right
    glVertex3f(-0.5, 2.0, -10.5);
	glVertex3f(-0.3, 4.0, -8.5);
	glVertex3f(-0.0, 4.0, -8.5);
	glVertex3f(-0.0, 2.0, -10.5);
//////////////////

//////////////////
    //upper left left
    glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.5, 4.0, -8.0);
	glVertex3f(-4.5, 4.0, -8.5);
	glVertex3f(-4.5, 2.0, -10.5);

	//upper right left
	glVertex3f(-4.0, 2.0, -10.0);
	glVertex3f(-4.2, 4.0, -8.0);
	glVertex3f(-4.2, 4.0, -8.5);
	glVertex3f(-4.0, 2.0, -10.5);


	//upper left mid
    glVertex3f(-2.5, 2.0, -10.0);
	glVertex3f(-2.4, 4.0, -8.0);
	glVertex3f(-2.4, 4.0, -8.5);
	glVertex3f(-2.5, 2.0, -10.5);

	//upper right mid
	glVertex3f(-2.0, 2.0, -10.0);
	glVertex3f(-2.1, 4.0, -8.0);
	glVertex3f(-2.1, 4.0, -8.5);
	glVertex3f(-2.0, 2.0, -10.5);


	//upper left right
    glVertex3f(-0.5, 2.0, -10.0);
	glVertex3f(-0.3, 4.0, -8.0);
	glVertex3f(-0.3, 4.0, -8.5);
	glVertex3f(-0.5, 2.0, -10.5);

	//upper right right
	glVertex3f(-0.0, 2.0, -10.0);
	glVertex3f(-0.0, 4.0, -8.0);
	glVertex3f(-0.0, 4.0, -8.5);
	glVertex3f(-0.0, 2.0, -10.5);
//////////////////



//////////////////
    //upper top front
	glVertex3f(-4.5, 4.0, -8.0);
	glVertex3f(-0.0, 4.0, -8.0);
	glVertex3f(-0.0, 3.5, -8.5);
	glVertex3f(-4.5, 3.5, -8.5);


	//upper top back
	glVertex3f(-4.5, 4.0, -8.5);
	glVertex3f(-0.0, 4.0, -8.5);
	glVertex3f(-0.0, 3.5, -9.0);
	glVertex3f(-4.5, 3.5, -9.0);


	//upper top up
	glVertex3f(-4.5, 4.0, -8.0);
	glVertex3f(-4.5, 4.0, -8.5);
	glVertex3f(-0.0, 4.0, -8.5);
	glVertex3f(-0.0, 4.0, -8.0);

	//upper top bottom
	glVertex3f(-4.5, 3.5, -8.5);
	glVertex3f(-4.5, 3.5, -9.0);
	glVertex3f(-0.0, 3.5, -9.0);
	glVertex3f(-0.0, 3.5, -8.5);

//////////////////



//////////////////
    //front left
    glVertex3f(-4.5, -4.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.0, 2.0, -10.0);
	glVertex3f(-4.0, -4.0, -10.0);

	//front mid
    glVertex3f(-2.5, -4.0, -10.0);
	glVertex3f(-2.5, 2.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.0);
	glVertex3f(-2.0, -4.0, -10.0);


	//front right
    glVertex3f(-0.5, -4.0, -10.0);
	glVertex3f(-0.5, 2.0, -10.0);
	glVertex3f(-0.0, 2.0, -10.0);
	glVertex3f(-0.0, -4.0, -10.0);
///////////////////

///////////////////
	//back left
    glVertex3f(-4.5, -4.0, -10.5);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-4.0, 2.0, -10.5);
	glVertex3f(-4.0, -4.0, -10.5);

	//back mid
    glVertex3f(-2.5, -4.0, -10.5);
	glVertex3f(-2.5, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, -4.0, -10.5);

	//back right
    glVertex3f(-0.5, -4.0, -10.5);
	glVertex3f(-0.5, 2.0, -10.5);
	glVertex3f(-0.0, 2.0, -10.5);
	glVertex3f(-0.0, -4.0, -10.5);
////////////////////


////////////////////
	//left left
    glVertex3f(-4.5, -4.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-4.5, -4.0, -10.5);

	//left right
    glVertex3f(-4.0, -4.0, -10.0);
	glVertex3f(-4.0, 2.0, -10.0);
	glVertex3f(-4.0, 2.0, -10.5);
	glVertex3f(-4.0, -4.0, -10.5);
////////////////////


////////////////////
	//mid left
    glVertex3f(-2.5, -4.0, -10.0);
	glVertex3f(-2.5, 2.0, -10.0);
	glVertex3f(-2.5, 2.0, -10.5);
	glVertex3f(-2.5, -4.0, -10.5);

	//mid right
    glVertex3f(-2.0, -4.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, -4.0, -10.5);
/////////////////////



////////////////////
	//mid left
    glVertex3f(-0.5, -4.0, -10.0);
	glVertex3f(-0.5, 2.0, -10.0);
	glVertex3f(-0.5, 2.0, -10.5);
	glVertex3f(-0.5, -4.0, -10.5);

	//mid right
    glVertex3f(0.0, -4.0, -10.0);
	glVertex3f(0.0, 2.0, -10.0);
	glVertex3f(0.0, 2.0, -10.5);
	glVertex3f(0.0, -4.0, -10.5);
/////////////////////



/*
	//top down
    glVertex3f(-4.5, 1.5, -10.0);
	glVertex3f(-4.5, 1.5, -10.5);
	glVertex3f(-2.0, 1.5, -10.5);
	glVertex3f(-2.0, 1.5, -10.0);

	//top up
    glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.0);

	//top front
    glVertex3f(-4.5, 1.5, -10.0);
	glVertex3f(-4.5, 2.0, -10.0);
	glVertex3f(-2.0, 2.0, -10.0);
	glVertex3f(-2.0, 1.5, -10.0);

	//top back
    glVertex3f(-4.5, 1.5, -10.5);
	glVertex3f(-4.5, 2.0, -10.5);
	glVertex3f(-2.0, 2.0, -10.5);
	glVertex3f(-2.0, 1.5, -10.5);
*/

	//base front
    glVertex3f(-5.0, -4.0, -9.5);
	glVertex3f(-5.0, -3.5, -9.5);
	glVertex3f(0.5, -3.5, -9.5);
	glVertex3f(0.5, -4.0, -9.5);

	//base back
    glVertex3f(-5.0, -4.0, -11.0);
	glVertex3f(-5.0, -3.5, -11.0);
	glVertex3f(0.5, -3.5, -11.0);
	glVertex3f(0.5, -4.0, -11.0);

	//base left
	glVertex3f(-5.0, -4.0, -9.5);
	glVertex3f(-5.0, -3.5, -9.5);
	glVertex3f(-5.0, -3.5, -11.0);
	glVertex3f(-5.0, -4.0, -11.0);

	//base right
	glVertex3f(0.5, -4.0, -9.5);
	glVertex3f(0.5, -3.5, -9.5);
	glVertex3f(0.5, -3.5, -11.0);
	glVertex3f(0.5, -4.0, -11.0);

	//base top
	glVertex3f(-5.0, -3.5, -9.5);
	glVertex3f(-5.0, -3.5, -11.0);
	glVertex3f(0.5, -3.5, -11.0);
	glVertex3f(0.5, -3.5, -9.5);


	glEnd();
}


void drawCircle(){
    glTranslatef(1.5, 2.0, -11.0);
    drawFilledCircle(0.0, 0.0, 4.0, 100);
    glTranslatef(-1.5, -2.0, 11.0);
}


//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    showLights();

	glTranslatef(0.0f, 0.0f, -18.0f);


    // auto rotation
    glTranslatef(0.0f, 0.0f, -8.0f);
	glRotatef(cameraAngle, 0.0f, 1.0f, 0.0f); //John // Stopping object movement
    glTranslatef(0.0f, 0.0f, 8.0f);


//base
//======================================================================================
    glPushMatrix();

    glColor3f(0.0f, 0.5f, 0.0f);
    drawGround();

    glPopMatrix();
//======================================================================================


    glTranslatef(0.0f,0.0f,-5.0f);
    glRotatef(7.0f, 0.0f, 1.0f, 0.0f);


//left  1st
//======================================================================================
    glPushMatrix();

    glTranslatef(2.25f, 0.0f, 0.0f);    //bring to center

    glTranslatef(0.0f, 4.0f, 10.25f);    //bring to center
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -4.0f, -10.25f);    //bring to center


    glColor3f(0.5f, 0.5f, 0.5f);
    drawSquarePillar();

    glPopMatrix();
//======================================================================================


//left 2nd
//======================================================================================
    glPushMatrix();

    glTranslatef(3.25f, 0.0f, 0.0f);    //bring to center

    glTranslatef(0.0f, 4.0f, 10.25f);    //bring to center
    glRotatef(20.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -4.0f, -10.25f);    //bring to center



    glScalef(1.0f, 1.5f, 1.0f);
    glTranslatef(0.0f, 1.35f, 0.0f);

    glColor3f(0.5f, 0.5f, 0.5f);
    drawSquarePillar();

    glPopMatrix();
//======================================================================================



//right 1st
//======================================================================================
    glPushMatrix();

    glTranslatef(1.0f, 0.0f, 3.5f);    //bring to center

    glTranslatef(0.0f, 4.0f, 10.25f);    //bring to center
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -4.0f, -10.25f);    //bring to center


    glScalef(1.0f, 1.5f, 1.0f);
    glTranslatef(0.0f, 1.35f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    drawSquarePillar();

    glPopMatrix();
//======================================================================================


//right 2nd
//======================================================================================
    glPushMatrix();

    glTranslatef(-0.25f, 0.0f, 3.5f);    //bring to center

    glTranslatef(0.0f, 4.0f, 10.25f);    //bring to center
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -4.0f, -10.25f);    //bring to center


    glColor3f(0.5f, 0.5f, 0.5f);
    drawSquarePillar();

    glPopMatrix();
//======================================================================================



//center
//======================================================================================
    glPushMatrix();

    glScalef(1.5, 1.5, 1.0);
    glRotatef(-8.0f, 0.0f, 1.0f, 0.0f);

    glTranslatef(1.8, 1.0, 0.0);

    glColor3f(0.5f, 0.5f, 0.5f);
    drawCenterPillars();

    glPopMatrix();
//======================================================================================


//circle
//======================================================================================
    glPushMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle();

    glPopMatrix();
//======================================================================================

	glutSwapBuffers();
}





int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);  //width x height

	//Create the window
	glutCreateWindow("Shahid Minar");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, autoRotate, 0); //Add a timer
	glutTimerFunc(25,moveLight,0);



	glutMainLoop();
	return 0;
}

