#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>

static float hours;
static int timer_active;
void plot_function();
void set_vertex_and_normal(float u, float v);

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void mouse_callback(int key, int state, int x, int y);
static void on_timer(int value);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MAT-LAV");
	
	glClearColor(0.99f, 0.66f, 0.85f, 0.0f);
	printf("Starting the game!\n");
	hours = 0;
    timer_active = 0;
    
	glutMouseFunc(mouse_callback);
	glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

	
    glClearColor(0.99f, 0.66f, 0.85f, 0.0f);
    glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        // Kraj programa
        exit(0);
        break;

    case 'g':
    case 'G':
        //Pokretanje
        if (!timer_active) {
            glutTimerFunc(50, on_timer, 0);
            timer_active = 1;
        }
        break;

    case 's':
    case 'S':
        //Zustavljanje
        timer_active = 0;
        break;
    }
}

static void mouse_callback(int key, int state, int x, int y)
{
	//na klik misa
}

static void on_timer(int value)
{
    //Da li callback dolazi do tajmera
    if (value != 0)
        return;

    hours += 18; //Azuriranje vremena

    glutPostRedisplay(); //Ponovno iscrtavanje prozora

    if (timer_active) //Postavljanje tajmera ponovo
        glutTimerFunc(50, on_timer, 0);   
}

static void on_reshape(int width, int height)
{
    //Postavlja se tacka gledista:
    glViewport(0, 0, width, height);

    //Postavljanje parametara projekcije:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);
}


void set_vertex_and_normal(float u, float v)
{
    glNormal3f(0, 1, 0); // Normala na tangentnu ravan - priblizna vrednost
	glVertex3f(u, 0, v); //Postavljanje verteksa
}

void plot_function()
{
	float scale;
	int u,v;
	
	glPushMatrix();
		scale = 2.0/100;
		glScalef(scale,scale,scale);
		
		for (u = -50; u < 50; u++)
		{
        	glBegin(GL_TRIANGLE_STRIP);
        	
        	for (v = -50; v <= 50; v++)
        	{
            	set_vertex_and_normal(u, v);
            	set_vertex_and_normal(u + 1, v);
        	}
        	glEnd();
    	}
    glPopMatrix();
}


static void on_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0, 1, 1, 0, 0, 0, 0, 1, 0);
	
	//Pozicija svetla:
    GLfloat light_position[] = { 1, 1, 1, 0 };

    //Ambijentalna boja svetla:
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };

    //Difuzna boja svetla:
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    //Spekularna boja svetla:
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    //Koeficijenti ambijentalne refleksije materijala:
    GLfloat ambient_coeffs[] = { 1.0, 0.9, 0.1, 1 };

    //Koeficijenti difuzne refleksije materijala:
    GLfloat diffuse_coeffs[] = { 0.8, 1.0, 0.8, 1 };

    //Koeficijenti spekularne refleksije materijala:
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    //Koeficijent glatkosti materijala:
    GLfloat shininess = 20;


	//Ukljucuje se osvjetljenje i podesavaju parametri svetla:
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    //Podesavaju se parametri materijala:
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    glColor3f(1,1,1);
    	glShadeModel(GL_SMOOTH);
	
	/*glColor3f(1, 1, 1);
        glutSolidSphere(200,200,200);
    
    //Pozicija svetla (u pitanju je direkcionalno svetlo)
    GLfloat light_position2[] = { 1, 1, 1, 0 };

    //Ambijentalna boja svetla
    GLfloat light_ambient2[] = { 0.1, 0.1, 0.1, 1 };

    //Difuzna boja svetla.
    GLfloat light_diffuse2[] = { 0.7, 0.7, 0.7, 1 };

    //Spekularna boja svetla
    GLfloat light_specular2[] = { 0.9, 0.9, 0.9, 1 };
        
    //Koeficijenti ambijentalne refleksije materijala
    GLfloat ambient_coeffs2[] = { 0.3, 0.3, 0.7, 1 };

    //Koeficijenti difuzne refleksije materijala
    GLfloat diffuse_coeffs2[] = { 0.2, 0.2, 1, 1 };

    //Koeficijenti spekularne refleksije materijala
    GLfloat specular_coeffs2[] = { 1, 0, 0, 1 };

    /Koeficijent glatkosti materijala
    GLfloat shininess2 = 30;
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular2);
        
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess2);*/
    

    //glShadeModel(GL_SMOOTH);
		
	plot_function();
		
	glutSwapBuffers();
}
