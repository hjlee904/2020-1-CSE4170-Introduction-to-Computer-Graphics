#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Shaders/LoadShaders.h"
GLuint h_ShaderProgram; // handle to shader program
GLint loc_ModelViewProjectionMatrix, loc_primitive_color; // indices of uniform variables

// include glm/*.hpp only if necessary
//#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale, ortho, etc.
glm::mat4 ModelViewProjectionMatrix;
glm::mat4 ViewMatrix, ProjectionMatrix, ViewProjectionMatrix;

#define TO_RADIAN 0.01745329252f  
#define TO_DEGREE 57.295779513f
#define BUFFER_OFFSET(offset) ((GLvoid *) (offset))

#define LOC_VERTEX 0

int win_width = 0, win_height = 0; 
float centerx = 0.0f, centery = 0.0f;
int fc = 0, a = 10, num = 1, spkey = 0;

// 2D 물체 정의 부분은 objects.h 파일로 분리
// 새로운 물체 추가 시 prepare_scene() 함수에서 해당 물체에 대한 prepare_***() 함수를 수행함.
// (필수는 아니나 올바른 코딩을 위하여) cleanup() 함수에서 해당 resource를 free 시킴.
#include "objects.h"

unsigned int timestamp = 0;
unsigned int timestamp2 = 0;
void timer(int value) {
	timestamp = (timestamp + 1) % UINT_MAX;
	glutPostRedisplay();
	glutTimerFunc(a, timer, 0);
}
void timer2(int value) {
	timestamp2 = (timestamp2 + 1) % UINT_MAX;
	glutPostRedisplay();
	glutTimerFunc(10, timer2, 0);
}

void display(void) {
	glm::mat4 ModelMatrix;
	
	glClearColor( 63.0 / 255.0f, 0.0 / 255.0f, 153.0 / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	ModelMatrix = glm::mat4(1.0f);
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	
	float ran11 = (rand() % 1200) - 600, ran12 = (rand() % 800) - 400;
	float ran21 = (rand() % 1200) - 600, ran22 = (rand() % 800) - 400;
	float ran31 = (rand() % 1200) - 600, ran32 = (rand() % 800) - 400;
	float ran41 = (rand() % 1200) - 600, ran42 = (rand() % 800) - 400;

	if (num == 1) {

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(ran11, ran12, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker1();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(ran21, ran22, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker2();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(ran31, ran32, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker3();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(ran41, ran42, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker4();

		if ((fc == 1) && (a > 2)) {
			a = a / 2;
			fc = 0;
		}
		else if ((fc == 2) && (a < 1000)) {
			a = a * 2;
			fc = 0;
		}

		int rabbit_clock = (timestamp % 1442) / 2 - 360;
		float scaling_factor_rabbit = 0.5f * (1.0f - fabs(cosf(rabbit_clock * TO_RADIAN))) + 0.5f;

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 45.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f,
			100.0f * fabs(sinf(rabbit_clock * TO_RADIAN)) + 45.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaling_factor_rabbit, scaling_factor_rabbit, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rabbit();


		// person(with shirt)
		int shirt_clock = (timestamp % 1442) / 2 - 360;
		float rotation_angle_shirt = atanf(100.0f * TO_RADIAN * cosf(shirt_clock * TO_RADIAN));

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -65.0f, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_shirt();


		// hat
		int hat_clock = (timestamp % 1442) / 2 - 360;
		float rotation_angle_hat = -fabs(sinf(hat_clock * TO_RADIAN));

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, -40.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(10.0f * fabs(sinf(hat_clock * TO_RADIAN)), 0.0f * fabs(sinf(hat_clock * TO_RADIAN)), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_hat / 2, glm::vec3(0.0f, 0.0f, 1.0f));

		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_hat();

		// sword
		int sword_clock = (timestamp % 1442) / 2 - 360;
		float rotation_angle_sword = sword_clock * TO_RADIAN;

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-80.0f, -190.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 150.0f * fabs(sinf(sword_clock * TO_RADIAN * 3)) + 45.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_sword * 12, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5, 0.5, 1.0f));

		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_sword();
	}

	else if (num == 2) {
		a = 10;

		//circle
		int circle_clock = (timestamp2 % 1442) / 2 - 360;
		float rotation_angle_circle = -circle_clock * TO_RADIAN;

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, -65.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_circle * 3 , glm::vec3(0.0f, 0.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_circle();

		// person(with shirt)
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, -65.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_circle * 3, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_shirt();
		draw_shirt2();

		// cake
		int cake_clock = (timestamp2 % 1442) / 8;
		float rotation_angle_cake = cake_clock * TO_RADIAN;

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 45.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(2000.0f * cake_clock * TO_RADIAN, 100.0f * (sinf(cake_clock * TO_RADIAN * 10)), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -rotation_angle_cake * 5, glm::vec3(0.0f, 0.0f, 1.0f));

		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);

		float ft = 2000.0f * cake_clock * TO_RADIAN - 700.0f;

		if ((ft >= 0.0f) && (ft < 200.0f)) {
			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 30.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, ft / 5, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_firecracker1();

			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 30.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3((-ft / 5) * 0.59, (-ft / 5) * 0.81, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_firecracker2();

			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 30.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3((-ft / 5) * 0.95, (ft / 5) * 0.31, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_firecracker3();

			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 30.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3((ft / 5) * 0.95, (ft / 5) * 0.31, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_firecracker4();

			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 30.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3((ft / 5) * 0.59, (-ft / 5) * 0.81, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_firecracker5();

		}
		else if (ft < 0.0f) {
			draw_cake();
		}


		// airplane
		int airplane_clock = timestamp2 % 360;
		float rotation_angle_airplane = airplane_clock * TO_RADIAN;

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 25.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(500.0f * airplane_clock * TO_RADIAN, 20.0f * (sinf(airplane_clock * TO_RADIAN * 10)), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -rotation_angle_airplane * 30, glm::vec3(0.0f, 0.0f, 1.0f));

		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);

		float ft2 = 500.0f * airplane_clock * TO_RADIAN - 700.0f;

		if ((ft2 >= 0.0f) && (ft2 < 200.0f)) {
			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, -65.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_circle * 3, glm::vec3(0.0f, 0.0f, 1.0f));

			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);

			draw_blood();
		}
		else if (ft2 < 0.0f) {
			draw_airplane();
		}

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-422.0f, -(circle_clock) * 5, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_circle * 5, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(rotation_angle_circle / 2, rotation_angle_circle / 2, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_sword();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-20.0f, -(circle_clock) * 6, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_circle * 2, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(sinf(rotation_angle_circle * 3), sinf(rotation_angle_circle * 3), 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_sword();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(334.0f, -(circle_clock) * 3.5, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_circle * 4, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(sinf(rotation_angle_circle), sinf(rotation_angle_circle), 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_sword();
	}
	
	else if (num == 3) {
		a = 10;
		
		int rabbit_clock = (timestamp2 % 1442) / 2 - 360;
		float scaling_factor_rabbit = 0.5f * (1.0f - fabs(cosf(rabbit_clock * TO_RADIAN))) + 0.5f;

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -50.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(500.0f * sinf(rabbit_clock * TO_RADIAN * 0.5), 100.0f * fabs(sinf(rabbit_clock * TO_RADIAN * 1.7)), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5.0f, 5.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rabbit();

		int bg_clock = (timestamp2 % 1442) / 2 - 300;
		int bg_clock2 = (timestamp2 % 1222) / 2 - 400;

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-322.0f, 75 - (bg_clock2) * 1.8, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker1();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-144.0f, 34 - (bg_clock2 * 2.4), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker2();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(20.0f, -(bg_clock2 * 4) * 1.1, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker3();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(285.0f, 285 - (bg_clock2 * 6.1), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker4();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(583.0f, 320 - (bg_clock2) * 2.5, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker1();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-322.0f, 20-(bg_clock), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker1();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-167.0f, 50-(bg_clock*2), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker2();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-93.0f, -(bg_clock * 4), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker3();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(53.0f, 150-(bg_clock * 3), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker4();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(410.0f, 100-(bg_clock)*2.3, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker1();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(145.0f, -(bg_clock * 3.5), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker2();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(110.0f, -(bg_clock * 4), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker3();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(350.0f, -(bg_clock * 2.5), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker4();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-550.0f, 46-(bg_clock) * 5, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker1();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-470.0f, 72-(bg_clock * 1.7), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker2();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(530.0f, 34-(bg_clock * 2.2), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker3();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-400.0f, 275-(bg_clock * 1.5), 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_firecracker4();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_box1();
		draw_box3();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(270.0f, -170.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 100.0f * fabs(sinf(rabbit_clock * TO_RADIAN * 2.5)), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rabbit();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, -200.0f, 0.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 100.0f * fabs(sinf(rabbit_clock * TO_RADIAN * 3.0)), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.5f, 1.5f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rabbit();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_shirt3();

		if (spkey) {
			int spkey_clock = (timestamp2 % 1442) / 2 - 360; 
			float rotation_angle_spkey = spkey_clock * TO_RADIAN;

			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(150.0f * sinf(spkey_clock * TO_RADIAN), 150.0f * fabs(sinf(spkey_clock * TO_RADIAN * 3)), 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_spkey * 6, glm::vec3(0.0f, 0.0f, 1.0f));
			
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_box2();

			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(150.0f * sinf(spkey_clock * TO_RADIAN), 150.0f * fabs(sinf(spkey_clock * TO_RADIAN * 3)), 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, rotation_angle_spkey * 6, glm::vec3(0.0f, 0.0f, 1.0f));
			
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_shirt4();

			glutPostRedisplay();
		}
		else {
			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_box2();

			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
			glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
			draw_shirt4();

			glutPostRedisplay();
		}
	}

	glFlush();	
}   

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESC key
		glutLeaveMainLoop(); // Incur destuction callback for cleanups.
		break;
	case 49: // 1 key
		num = 1;
		break;
	case 50: // 2key
		num = 2;
		break;
	case 51: // 3key
		num = 3;
		break;
	case 32: // space key
		spkey = (spkey + 1) % 2;
		break;
	}
}

int leftbuttonpressed = 0;
void mouse(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		leftbuttonpressed = 1;
		fc = 1;
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
		leftbuttonpressed = 0;

	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		fc = 2;
	}
	
}

void motion(int x, int y) {
	if (leftbuttonpressed) {
		centerx =  x - win_width/2.0f, centery = (win_height - y) - win_height/2.0f;
		glutPostRedisplay();
	}

} 
	
void reshape(int width, int height) {
	win_width = width, win_height = height;
	
  	glViewport(0, 0, win_width, win_height);
	ProjectionMatrix = glm::ortho(-win_width / 2.0, win_width / 2.0, 
		-win_height / 2.0, win_height / 2.0, -1000.0, 1000.0);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	glutPostRedisplay();
}

void cleanup(void) {
	glDeleteVertexArrays(1, &VAO_firecracker);
	glDeleteBuffers(1, &VBO_firecracker);

	glDeleteVertexArrays(1, &VAO_circle);
	glDeleteBuffers(1, &VBO_circle);

	glDeleteVertexArrays(1, &VAO_blood);
	glDeleteBuffers(1, &VBO_blood);

	glDeleteVertexArrays(1, &VAO_airplane);
	glDeleteBuffers(1, &VBO_airplane);

	glDeleteVertexArrays(1, &VAO_shirt);
	glDeleteBuffers(1, &VBO_shirt);

	glDeleteVertexArrays(1, &VAO_hat);
	glDeleteBuffers(1, &VBO_hat);

	glDeleteVertexArrays(1, &VAO_cake);
	glDeleteBuffers(1, &VBO_cake);

	glDeleteVertexArrays(1, &VAO_sword);
	glDeleteBuffers(1, &VBO_sword);

	glDeleteVertexArrays(1, &VAO_rabbit);
	glDeleteBuffers(1, &VBO_rabbit);

	glDeleteVertexArrays(1, &VAO_box);
	glDeleteBuffers(1, &VBO_box);
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutTimerFunc(10, timer, 0);
	glutTimerFunc(1, timer2, 0);
	glutCloseFunc(cleanup);
}

void prepare_shader_program(void) {
	ShaderInfo shader_info[3] = {
		{ GL_VERTEX_SHADER, "Shaders/simple.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
		{ GL_NONE, NULL }
	};

	h_ShaderProgram = LoadShaders(shader_info);
	glUseProgram(h_ShaderProgram);

	loc_ModelViewProjectionMatrix = glGetUniformLocation(h_ShaderProgram, "u_ModelViewProjectionMatrix");
	loc_primitive_color = glGetUniformLocation(h_ShaderProgram, "u_primitive_color");
}

void initialize_OpenGL(void) {
	glEnable(GL_MULTISAMPLE); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glClearColor(44 / 255.0f, 180 / 255.0f, 49 / 255.0f, 1.0f);
	ViewMatrix = glm::mat4(1.0f);
}

void prepare_scene(void) {
	prepare_firecracker();
	prepare_circle();
	prepare_blood();
	prepare_airplane();
	prepare_shirt();
	prepare_hat();
	prepare_cake();
	prepare_sword();
	prepare_rabbit();
	prepare_box();
}

void initialize_renderer(void) {
	register_callbacks();
	prepare_shader_program(); 
	initialize_OpenGL();
	prepare_scene();
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = GL_TRUE;

    error = glewInit();
	if (error != GLEW_OK) { 
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char *program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
	fprintf(stdout, "    This program was coded for CSE4170 students\n");
	fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}

#define N_MESSAGE_LINES 2
int main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 Simple2DTransformationMotion_GLSL_3.0.3";
	char messages[N_MESSAGE_LINES][256] = {
		"    - Keys used: 'ESC'"
		"    - Mouse used: L-click and move"
	};

	glutInit (&argc, argv);
 	glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize (1200, 800);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}


