#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include "image.h"
#include"labyrinth.h"

#define FILENAME0 "Tileable_marble_floor_tile_texture(16).bmp"
#define FILENAME1 "metal_seamless_texture_43_by_jojo_ojoj-d8qm8o9.bmp"

//matrica rotacije
static float matrix[16];
//imena tekstura
static GLuint names[2];
// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera’s direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

void on_display(void);
void changeSize(int w, int h);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int xx, int yy);
static void initialize(void);
void draw_labyrinth();
void wall1();
void wall2();


int main(int argc, char **argv)
{
// Pravljenje prozora.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("MAT-LAV");

// Callback funkcije.
	glutDisplayFunc(on_display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(on_display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glEnable(GL_DEPTH_TEST);
	
//inicijalizacija
	initialize();

	glutMainLoop();

	return 0;
}

void processNormalKeys(unsigned char key, int x, int y)
{

	if (key == 27)
	{
		glDeleteTextures(2, names);
		exit(0);
	}
}

void processSpecialKeys(int key, int xx, int yy)
{

	float fraction = 0.5f; //bilo je 0.1f

	switch (key)
	{
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;	
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}

static void initialize(void)
{
    // Objekat koji predstavlja teskturu ucitanu iz fajla.
    Image * image;

    glClearColor(0, 0, 0, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    //Inicijalizuja objekta koji sadrzi teksture ucitane iz fajla.
    image = image_init(0, 0);

    // Kreiranje prve teksture.
    image_read(image, FILENAME0);

    // Generisanje identifikatora tekstura.
    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se druga tekstura. */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    // Iskljucuje se aktivna tekstura.
    glBindTexture(GL_TEXTURE_2D, 0);

    // Unistava se objekat za citanje tekstura iz fajla.
    image_done(image);

    // Inicijalizacija matrice rotacije.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}


void on_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
// Postavljanje kamere.
	gluLookAt( x, 1.0f, z,x+lx, 1.0f, z+lz,0.0f, 1.0f, 0.0f);
	
// Primenjuje se matrica rotacije.
    glMultMatrixf(matrix);
    glClearColor(0.7,0.5,0.0,0);
    
    
 	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    // Nulti koeficijenti refleksije materijala.
    GLfloat no_material[] = { 0, 0, 0, 1 };
    // Koeficijenti difuzne refleksije materijala.
    GLfloat material_diffuse[] = { 0.1, 0.5, 0.8, 1 };
    // Koeficijenti spekularne refleksije materijala.
    GLfloat material_specular[] = { 1, 1, 1, 1 };
    // Koeficijent spekularne refleksije za slucaj male vrednosti koeficijenta.
    GLfloat low_shininess[] = { 5 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_material);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_material);

	
	
//Iscrtavanje lavirinta.
	draw_labyrinth();
	
// Iscrtavanje poda.

	glPushMatrix();

	// Postavljanje teksture poda.
	glBindTexture(GL_TEXTURE_2D, names[0]);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			
			glTexCoord2f(-50, -50);
			glVertex3f(-200.0f, 0.0f, -200.0f);
			
			glTexCoord2f(-50, 50);
			glVertex3f(-200.0f, 0.0f, 200.0f);
			
			glTexCoord2f(50, 50);
			glVertex3f( 200.0f, 0.0f, 200.0f);
			
			glTexCoord2f(50, -50);
			glVertex3f( 200.0f, 0.0f, -200.0f);
		glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glPopMatrix();
	
	
	glutSwapBuffers();
}

void changeSize(int w, int h)
{
// Sprecava se deljenje nulom.
	if (h == 0)
	h = 1;
	float ratio = w * 1.0 / h;

// Matrica projekcije.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

// Postavljanje perspektive.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

