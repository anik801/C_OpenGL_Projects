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

GLuint frontFace,whiteMarble,pyramidTex,blackStripe,towerTop; //The id of the texture


float xFlag=0.0f, yFlag=0.0f, zFlag=0.0f,rotateStep=0,scaleFactor=1;
float xAngle=0.0f,yAngle=0.0f;

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

    cameraAngle = 0.0f;
}


//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
        case 32:
            //space bar
            rotateFlag *= -1;
            if(rotateFlag == -1){
                makeDefault();
            }
            break;
	}

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

	Image* image = loadBMP("C:\\Users\\John\\Desktop\\frontFace.bmp");
	frontFace = loadTexture(image);
	delete image;

	Image* image2 = loadBMP("C:\\Users\\John\\Desktop\\whiteMarble.bmp");
	whiteMarble = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("C:\\Users\\John\\Desktop\\stripe.bmp");
	pyramidTex = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("C:\\Users\\John\\Desktop\\blackStripe.bmp");
	blackStripe = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("C:\\Users\\John\\Desktop\\towerTop.bmp");
	towerTop = loadTexture(image5);
	delete image5;
}




//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


void autoRotate(int value) {
	cameraAngle += 0.5f;
	if (cameraAngle > 360) {
		cameraAngle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, autoRotate, 0);
}



float power = 0.0;
int lightFlag = 1;
void moveLight(int value) {
    if(lightFlag == 1){
        power += 0.01;
    }else{
        power -= 0.01;
    }

    if(power>1){
        lightFlag = 0;
    }else if(power<0){
        lightFlag = 1;
    }


	glutPostRedisplay();
	glutTimerFunc(25, moveLight, 0);
}

void showLights(){

    //Add ambient light
	GLfloat ambientColor[] = {power, power, power, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

}





void drawBase(){
	glBegin(GL_QUADS);
//front
glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-10.0f, -5.0f, 10.0f);
	glVertex3f(-10.0f, -5.0f, -10.0f);
	glVertex3f(10.0f, -5.0f, -10.0f);
	glVertex3f(10.0f, -5.0f, 10.0f);


	glEnd();
}

void drawTri(){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, frontFace);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    //front
    glTexCoord2f(0, -1);
        glVertex3f(0.0f, -5.0f, 0.0f);
	glTexCoord2f(1, 0);
        glVertex3f(7.0f, 0.0f, 0.0f);
	glTexCoord2f(1, -1);
        glVertex3f(7.0f, -5.0f, 0.0f);
	//glTexCoord2f(7, -1.1);
        glVertex3f(7.0f, -5.0f, 0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawTop(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, whiteMarble);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    //front
    glTexCoord2f(0, -4);
        glVertex3f(0.0f, -5.0f, 0.5f);
    glTexCoord2f(4, 0);
        glVertex3f(7.0f, 0.0f, 0.5f);

    glTexCoord2f(4, -4);
        glVertex3f(7.0f, 1.5f, -6.5f);
        glVertex3f(7.0f, 1.5f, -6.5f);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawMinar(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, blackStripe);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    //left
    glTexCoord2f(0, 0);
        glVertex3f(0.0f, -5.0f, 0.0f);
	glTexCoord2f(0, 1);
        glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2f(1, 1);
        glVertex3f(0.0f, 5.0f, -1.0f);
	glTexCoord2f(1, 0);
        glVertex3f(0.0f, -5.0f, -1.0f);

	//right
	glTexCoord2f(0, 0);
        glVertex3f(1.0f, -5.0f, 0.0f);
	glTexCoord2f(0, 1);
        glVertex3f(1.0f, 5.0f, 0.0f);
	glTexCoord2f(1, 1);
        glVertex3f(1.0f, 5.0f, -1.0f);
	glTexCoord2f(1, 0);
        glVertex3f(1.0f, -5.0f, -1.0f);

	//front
	glTexCoord2f(0, 0);
        glVertex3f(0.0f, -5.0f, 0.0f);
	glTexCoord2f(0, 1);
        glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2f(1, 1);
        glVertex3f(1.0f, 5.0f, 0.0f);
	glTexCoord2f(1, 0);
        glVertex3f(1.0f, -5.0f, 0.0f);

	//back
	glTexCoord2f(0, 0);
        glVertex3f(0.0f, -5.0f, -1.0f);
	glTexCoord2f(0, 1);
        glVertex3f(0.0f, 5.0f, -1.0f);
	glTexCoord2f(1, 1);
        glVertex3f(1.0f, 5.0f, -1.0f);
	glTexCoord2f(1, 0);
        glVertex3f(1.0f, -5.0f, -1.0f);


    glEnd();
	glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, towerTop);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

	//top front
	glTexCoord2f(0, 0);
        glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2f(0, 1);
        glVertex3f(0.5f, 8.0f, -0.5f);
	glTexCoord2f(1, 1);
        glVertex3f(1.0f, 5.0f, 0.0f);
	glTexCoord2f(1, 0);
        glVertex3f(1.0f, 5.0f, 0.0f);

	//top back
	glTexCoord2f(0, 0);
        glVertex3f(0.0f, 5.0f, -1.0f);
    glTexCoord2f(0, 1);
        glVertex3f(0.5f, 8.0f, -0.5f);
	glTexCoord2f(1, 1);
        glVertex3f(1.0f, 5.0f, -1.0f);
	glTexCoord2f(1, 0);
        glVertex3f(1.0f, 5.0f, -1.0f);


	//top left
	glTexCoord2f(0, 0);
        glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2f(0, 1);
        glVertex3f(0.5f, 8.0f, -0.5f);
	glTexCoord2f(1, 1);
        glVertex3f(0.0f, 5.0f, -1.0f);
	glTexCoord2f(1, 0);
        glVertex3f(0.0f, 5.0f, -1.0f);

	//top right
	glTexCoord2f(0, 0);
        glVertex3f(1.0f, 5.0f, 0.0f);
	glTexCoord2f(0, 1);
        glVertex3f(0.5f, 8.0f, -0.5f);
	glTexCoord2f(1, 1);
        glVertex3f(1.0f, 5.0f, -1.0f);
	glTexCoord2f(1, 0);
        glVertex3f(1.0f, 5.0f, -1.0f);


	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawPyramid(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, pyramidTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    //left
    glTexCoord2f(2, 1);
        glVertex3f(0.0f, -5.0f, -7.0f);
	glTexCoord2f(0, 0);
        glVertex3f(7.0f, 2.0f, -7.0f);
	glTexCoord2f(2, 0);
        glVertex3f(7.0f, -5.0f, 0.0f);
        glVertex3f(7.0f, -5.0f, 0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawFrontLeft(){
    glColor3f(1.0, 1.0, 1.0);
    //front
    glTranslatef(-7.0, 0.0, 8.0);
    drawTri();
    glTranslatef(7.0, 0.0, -8.0);

    //left
    glTranslatef(-7.0, 0.0, 8.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    drawTri();
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glTranslatef(7.0, 0.0, -8.0);


    //glColor3f(1.0, 0.0, 0.0);
    //top front
    glTranslatef(-7.0, 0.0, 8.0);
    drawTop();
    glTranslatef(7.0, 0.0, -8.0);

    //top left
    glTranslatef(-7.0, 0.0, 8.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glScaled(-1,1,1);
    drawTop();
    glScaled(-1,1,1);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(7.0, 0.0, -8.0);


    //minar
    glTranslatef(-8.5, 0.0, 9.5);
    drawMinar();
    glTranslatef(8.5, 0.0, -9.5);


    //glColor3f(0.0, 0.0, 1.0);
    //inner pyramid
    glTranslatef(-7.0, 0.0, 8.0);
    drawPyramid();
    glTranslatef(7.0, 0.0, -8.0);
}


//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    showLights();



    if(rotateFlag==1){
        // auto rotation
        glTranslatef(0.0f, 0.0f, -30.0f);
        glRotatef(-cameraAngle, 0.0f, 1.0f, 0.0f); //John // Stopping object movement
        glTranslatef(0.0f, 0.0f, 30.0f);
    }


    glTranslatef(0.0f, 0.0f, -30.0f);
    glColor3f(0.0f, 0.2f, 0.0f);
//======================================================================================
    glPushMatrix();
        drawBase();
    glPopMatrix();
//======================================================================================

    //glColor3f(1.0f, 1.0f, 1.0f);
//======================================================================================
    glPushMatrix();
        drawFrontLeft();
    glPopMatrix();
//======================================================================================

//======================================================================================
    glPushMatrix();
        //front right
        glTranslatef(-1.0, 0.0, 1.0);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        drawFrontLeft();
        glRotatef(-90.0, 0.0, 1.0, 0.0);
        glTranslatef(1.0, 0.0, -1.0);
    glPopMatrix();
//======================================================================================

//======================================================================================
    glPushMatrix();
        //back right
        glTranslatef(0.0, 0.0, 2.0);
        glRotatef(180.0, 0.0, 1.0, 0.0);
        drawFrontLeft();
        glRotatef(-180.0, 0.0, 1.0, 0.0);
        glTranslatef(0.0, 0.0, -2.0);
    glPopMatrix();
//======================================================================================

//======================================================================================
    glPushMatrix();
        //back left
        glTranslatef(1.0, 0.0, 1.0);
        glRotatef(270.0, 0.0, 1.0, 0.0);
        drawFrontLeft();
        glRotatef(-270.0, 0.0, 1.0, 0.0);
        glTranslatef(-1.0, 0.0, -1.0);
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
	glutCreateWindow("Faisal Mosque");
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
