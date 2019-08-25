#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include "image.h"
#include"labyrinth.h"

#define FILENAME0 "Tileable_marble_floor_tile_texture(16).bmp"
#define FILENAME1 "prvo_pitanje.bmp"
#define FILENAME2 "drugo_pitanje.bmp"
#define FILENAME3 "trece_pitanje.bmp"
#define FILENAME4 "cetvrto_pitanje.bmp"
#define STOP 1
#define MOVE 0

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
char move_trigger = MOVE;
char q_counter = 0;

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
	
	printf("Game rules:\n");
    printf("Right answers give you a hit which way to go,\n");
    printf("to find the right path to exit the labyrinth.\n");
    printf("If the correct answer is (l) you should turn left,\n");
    printf("if it's (f) you should continue your path ahead, and if it's (r),\n");
    printf("you should turn right.\n");

	glutMainLoop();

	return 0;
}

void processNormalKeys(unsigned char key, int x_f, int y_f)
{

	if (key == 27)
	{
		glDeleteTextures(2, names);
		exit(0);
	}
	
	if (key == 'z')
	{
		printf("%f\n",z+lz);
	}
	if (key == 'x')
	{
		printf("%f\n",x);
	}
	
	if (key == 'r')
	{
		if (q_counter == 1 || q_counter == 3 || q_counter == 2)
		{
			printf("Wrong answer! You're now dead! :( Good luck in resurrection.");
			exit(EXIT_SUCCESS);
		}
		else if (q_counter == 4)
		{
			move_trigger = MOVE;
			x -= 0.6;
		}
	}
	
	if (key == 'f')
	{
		if (q_counter == 1)
		{
			move_trigger = MOVE;
			z -= 0.6;
		}
		
		else if (q_counter == 2 || q_counter == 4 || q_counter == 3)
		{
			printf("Wrong answer! You're now dead! :( Good luck in resurrection.");
			exit(EXIT_SUCCESS);
		}
	}
	
	if (key == 'l')
	{
		if (q_counter == 1 || q_counter == 4)
		{
			printf("Wrong answer! You're now dead! :( Good luck in resurrection.");
			exit(EXIT_SUCCESS);
		}
		else if (q_counter == 2 || q_counter == 3)
		{
			move_trigger = MOVE;
			x += 0.6;
		}

	}
}

void processSpecialKeys(int key, int xx, int yy)
{

	float fraction = 0.1f;

	switch (key)
	{
		case GLUT_KEY_LEFT :
			if (move_trigger != STOP)
			{
				angle -= 0.01f;
				lx = sin(angle);
				lz = -cos(angle);
			}
			
			break;
		case GLUT_KEY_RIGHT :
			if (move_trigger != STOP)
			{
				angle += 0.01f;
				lx = sin(angle);
				lz = -cos(angle);
			}
			break;
		case GLUT_KEY_UP :
			if (move_trigger != STOP)
			{
				x += lx * fraction;
				z += lz * fraction;
			}
			break;	
		case GLUT_KEY_DOWN :
			if (move_trigger != STOP)
			{
				x -= lx * fraction;
				z -= lz * fraction;
			}
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
    glGenTextures(5, names);

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

    // Kreira se druga tekstura.
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
                 
     image_read(image, FILENAME2);

    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    
    image_read(image, FILENAME3);

    glBindTexture(GL_TEXTURE_2D, names[3]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
                 
                 
    image_read(image, FILENAME4);

    glBindTexture(GL_TEXTURE_2D, names[4]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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

void question()
{
	//Prvo pitanje.
	if (z<= -52.0 && z> -52.5)
	{
		move_trigger = STOP;
		
		glPushMatrix();	
		glBindTexture(GL_TEXTURE_2D, names[1]);
			glBegin(GL_QUADS);
							
				
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(x+lx+1.5, 3.0f, z+lz-4.2);
			
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(x+lx+1.5, 0.0f, z+lz-4.2);
			
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(x+lx-1.5, 0.0f, z+lz-4.0);
				
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(x+lx-1.5, 3.0f, z+lz-4.0);
				
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);		
	glPopMatrix();	
	q_counter = 1;
	}
	
	//Drugo pitanje.
	if(x >=-5.0 && x <= -4.5 && z<=-86.0 && z >= -88.0)
	{
		move_trigger = STOP;
		glPushMatrix();
	// Postavljanje pitanja.
		glBindTexture(GL_TEXTURE_2D, names[2]);
			glBegin(GL_QUADS);
							
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(x+lx+4.0, 3.0f, z+lz-1.5);
			
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(x+lx+4.0, 3.0f, z+lz+1.5);
			
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(x+lx+4.0, 0.0f, z+lz+1.5);
			
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(x+lx+4.0, 0.0f, z+lz-1.5);
			
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);		
		glPopMatrix();	
		q_counter = 2;
	}
	
	//Trece pitanje.
	if(x >=22.0 && x <= 22.5 && z<=-113.0 && z >= -118.0)
	{
		move_trigger = STOP;
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, names[3]);
			glBegin(GL_QUADS);
							
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(x+lx+4.0, 3.0f, z+lz-1.5);
			
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(x+lx+4.0, 3.0f, z+lz+1.5);
			
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(x+lx+4.0, 0.0f, z+lz+1.5);
			
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(x+lx+4.0, 0.0f, z+lz-1.5);
			
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);		
		glPopMatrix();	
		q_counter = 3;
	}
	
	//Cetvrto pitanje.
	if(x >=7.0 && x <= 7.5 && z>=-148.0 && z <= -143.0)
	{
		move_trigger = STOP;
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, names[4]);
			glBegin(GL_QUADS);
							
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(x+lx-4.0, 3.0f, z+lz-1.5);
			
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(x+lx-4.0, 3.0f, z+lz+1.5);
			
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(x+lx-4.0, 0.0f, z+lz+1.5);
			
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(x+lx-4.0, 0.0f, z+lz-1.5);
			
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);		
		glPopMatrix();	
		q_counter = 4;
	}
	
}

void on_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
// Postavljanje kamere.
	gluLookAt(x, 1.0f, z,x+lx, 1.0f, z+lz,0.0f, 1.0f, 0.0f);
	
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
			//glNormal3f(0, 0, 1);
			
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
	
	question();
	
	if (z<= -162)
	{
		printf("You have successfully found the way out of the labyrinth! :D\n");
		exit(EXIT_SUCCESS);
	}
	
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

