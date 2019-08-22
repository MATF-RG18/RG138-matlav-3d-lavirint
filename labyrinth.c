#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include "labyrinth.h"


void wall1()
{
	glPushMatrix();
		glScalef(2,20,20);
		glTranslatef(3.0f ,0.0f, 0.0f);
		glutSolidCube(1.0f);
	glPopMatrix();
}

void wall2()
{
	glPushMatrix();
		glScalef(20,20,2);
		glTranslatef(3.0f ,0.0f, 0.0f);
		glutSolidCube(1.0f);
	glPopMatrix();
}

void draw_labyrinth()
{
	// Ulaz i lavirint, zid desno.
	glPushMatrix();
		glTranslatef(-10.0,0,-10.0);
		wall1();
	glPopMatrix();
	
	// Ulaz u lavirint, zid levo.		
	glPushMatrix();
		glScalef(1,1,2);
		glTranslatef(0.0,0.0,-10.0);
		wall1();
	glPopMatrix();
	
	// Ulaz u lavirint, popreki zid pravo.
	glPushMatrix();
		glTranslatef(-75.0,0.0,-19.0);
		wall2();
	glPopMatrix();
	
	// Skretanje levo, zid levo.
	glPushMatrix();
		glTranslatef(-65.0,0.0,-30.0);
		wall2();
	glPopMatrix();
	
	// Skretanje desno, zid sa leve strane.
	glPushMatrix();
		glTranslatef(-30.0,0.0,-30.0);
		glScalef(1,1,2.1);
		wall1();
	glPopMatrix();
	
	//Skretanje desno, zid sa desne strane.
	glPushMatrix();
		glTranslatef(-20.0,0.0,-41.0);
		wall1();
	glPopMatrix();
	
	// Prvo pitanje, skretanje desno, zid desno.
	glPushMatrix();
		glScalef(2.0,1.0,1.0);
		glTranslatef(-57.5,0.0,-51.5);
		wall2();
	glPopMatrix();
	
	//Prvo pitanje skretanje levo, zid levo.
	glPushMatrix();
		glTranslatef(-93.0,0.0,-51.5);
		wall2();
	glPopMatrix();
	
	//Prvo pitanje skretanje desno, zid levo.
	glPushMatrix();
		glTranslatef(-65.0,0.0,-61.5);
		wall2();
	glPopMatrix();
	
	//Prvo pitanje skretanje levo, zid levo.
	glPushMatrix();
		glTranslatef(-93.0,0.0,-61.5);
		wall2();
	glPopMatrix();
	
	//Poprecni zid, za netacan odgovor.
	glPushMatrix();
		glTranslatef(-48.0,0.0,-51.5);
		wall1();
	glPopMatrix();
	
	// Pravo, zid sa leve strane.
	glPushMatrix();
		glTranslatef(-30.0,0.0,-77.0);
		// Skalira se da bi mogao da se napravi cosak.
		glScalef(1.0,1.0,1.5);
		wall1();
	glPopMatrix();
	
	// Pravo, zid sa desne strane.
	glPushMatrix();
		glTranslatef(-20.0,0.0,-71.5);
		wall1();
	glPopMatrix();
	
	// Skretanje desno, zid desno.
	glPushMatrix();
		glTranslatef(-65.0,0.0,-82.5);
		wall2();
	glPopMatrix();
	
	// Skretanje desno, zid levo.
	glPushMatrix();
		glScalef(1.5,1.0,1.0);
		glTranslatef(-68.0,0.0,-92.0);
		wall2();
	glPopMatrix();
	
	//Drugo pitanje, skretanje desno, desni zid.
	glPushMatrix();
		glTranslatef(-2.0,0.0,-71.5);
		wall1();
	glPopMatrix();
	
	//Drugo pitanje, skretanje desno, levi zid.
	glPushMatrix();
		glTranslatef(8.0,0.0,-67.5);
		glScalef(1.0,1.0,1.5);
		wall1();
	glPopMatrix();
	
	//Drugo pitanje, skretanje levo, levi zid.
	glPushMatrix();
		glTranslatef(-2.0,0.0,-106.0);
		glScalef(1.0,1.0,1.5);
		wall1();
	glPopMatrix();
	
	//Drugo pitanje, skretanje levo, desni zid.
	glPushMatrix();
		glTranslatef(8.0,0.0,-101.0);
		wall1();
	glPopMatrix();
	
	//Drugo pitanje, pravo, levi zid.
	glPushMatrix();
		glTranslatef(-37,0.0,-90.0);
		wall2();
	glPopMatrix();
	
	//Drugo pitanje, pravo, desni zid.
	glPushMatrix();
		glTranslatef(-62,0.0,-82.5);
		glScalef(1.5,1.0,1.0);
		wall2();
	glPopMatrix();
	
	//Skretanje levo, levi zid.
	glPushMatrix();
		glTranslatef(26.0,0.0,-101.0);
		wall1();
	glPopMatrix();
	
	//Skretanje levo, desni zid.
	glPushMatrix();
		glScalef(1.0,1.0,1.5);
		glTranslatef(37.0,0.0,-65.0);
		wall1();
	glPopMatrix();
	
	//Trece pitanje, levo, levi zid.
	glPushMatrix();
		glTranslatef(-37,0.0,-110.0);
		wall2();
	glPopMatrix();
	
	//Trece pitanje, levo, desni zid.
	glPushMatrix();
		glScalef(1.5,1.0,1.0);
		glTranslatef(-48,0.0,-120.0);
		wall2();
	glPopMatrix();
	
	//Trece pitanje, desno, desni zid.
	glPushMatrix();
		glTranslatef(-8,0.0,-112.0);
		wall2();
	glPopMatrix();
	
	//Trece pitanje, desno, levi zid.
	glPushMatrix();
		glTranslatef(-8,0.0,-120.0);
		wall2();
	glPopMatrix();
	
	//Poprecni zid za kraj.
	glPushMatrix();
		glTranslatef(57.0,0.0,-115.0);
		wall1();
	glPopMatrix();
	
	//Trece pitanje, pravo, zid levo.
	glPushMatrix();
		glTranslatef(26.0,0.0,-131.0);
		wall1();
	glPopMatrix();
	
	//Trece pitanje, pravo, zid desno.
	glPushMatrix();
		glTranslatef(37.0,0.0,-136.0);
		glScalef(1.0,1.0,1.5);
		wall1();
	glPopMatrix();
	
	//Skretanje levo, zid levo.
	glPushMatrix();
		glTranslatef(-107,0.0,-140.0);
		glScalef(2.0,1.0,1.0);
		wall2();
	glPopMatrix();
	
	//Skretanje levo, zid desno.
	glPushMatrix();
		glTranslatef(-160,0.0,-150.0);
		glScalef(3.0,1.0,1.0);
		wall2();
	glPopMatrix();
	
	// Cetvrto pitanje, skretanje levo, levi zid.
	glPushMatrix();
		glTranslatef(-14.0,0.0,-126.0);
		glScalef(1.0,1.0,1.5);
		wall1();
	glPopMatrix();
	
	// Cetvrto pitanje, skretanje levo, desni zid.
	glPushMatrix();
		glTranslatef(-25.0,0.0,-131.0);
		wall1();
	glPopMatrix();
	
	// Cetvrto pitanje, skretanje desno, desni zid.
	glPushMatrix();
		glTranslatef(-15.0,0.0,-165.0);
		glScalef(1.0,1.0,1.5);
		wall1();
	glPopMatrix();
	
	// Cetvrto pitanje, skretanje desno, levi zid.
	glPushMatrix();
		glTranslatef(-25.0,0.0,-159.0);
		wall1();
	glPopMatrix();
	
	//Cetvrto pitanje, pravo, levi zid.
	glPushMatrix();
		glTranslatef(-90,0.0,-140.0);
		wall2();
	glPopMatrix();
	
	//Cetvrto pitanje, pravo, desni zid.
	glPushMatrix();
		glScalef(1.5,1.0,1.0);
		glTranslatef(-83,0.0,-150.0);
		wall2();
	glPopMatrix();
	
	//Posle levog odgovora na pitanje, skretanje desno, desni zid.
	glPushMatrix();
		glTranslatef(-89.0,0.0,-122.0);
		wall2();
	glPopMatrix();
	
	//Posle levog odgovora na pitanje, skretanje desno, levi zid.
	glPushMatrix();
		glTranslatef(-158,0.0,-110.0);
		glScalef(2.2,1.0,1.0);
		wall2();
	glPopMatrix();
	
	// Hodnik koji spaja levo i pavo odgovor, kraci zid.
	glPushMatrix();
		glTranslatef(-45.0,0.0,-131.0);
		wall1();
	glPopMatrix();
	
	// Hodnik koji spaja levo i pravo odgovor, duzi zid.
	glPushMatrix();
		glScalef(1.0,1.0,2.2);
		glTranslatef(-54.7,0.0,-59.0);
		wall1();
	glPopMatrix();
}

