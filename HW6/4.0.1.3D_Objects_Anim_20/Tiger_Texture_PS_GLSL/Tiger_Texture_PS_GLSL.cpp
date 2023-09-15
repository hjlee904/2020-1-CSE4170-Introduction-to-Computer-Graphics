#define _CRT_SECURE_NO_WARNINGS


#include "my_geom_objects.h"


// include glm/*.hpp only if necessary
//#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale, lookAt, perspective, etc.
#include <glm/gtc/matrix_inverse.hpp> // inverseTranspose, etc.
glm::mat4 ModelViewProjectionMatrix, ModelViewMatrix;
glm::mat3 ModelViewMatrixInvTrans;
glm::mat4 ViewProjectionMatrix, ViewMatrix, ProjectionMatrix;

int flag_texture_mapping;
int tm = 0, rm = 0;
int qb = 0;

void prepare_shader_program(void);
void prepare_shader_program2(void);

void set_ViewMatrix_from_camera_frame(void) {
	ViewMatrix = glm::mat4(camera.uaxis[0], camera.vaxis[0], camera.naxis[0], 0.0f,
		camera.uaxis[1], camera.vaxis[1], camera.naxis[1], 0.0f,
		camera.uaxis[2], camera.vaxis[2], camera.naxis[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-camera.pos[0], -camera.pos[1], -camera.pos[2]));
}

void initialize_camera(void) {
	camera.pos[0] = 700.0f; camera.pos[1] = 130.0f;  camera.pos[2] = 0.0f;
	camera.uaxis[0] = camera.uaxis[1] = 0.0f; camera.uaxis[2] = -1.0f;
	camera.vaxis[0] = camera.vaxis[2] = 0.0f; camera.vaxis[1] = 1.0f;
	camera.naxis[1] = camera.naxis[2] = 0.0f; camera.naxis[0] = 1.0f;

	camera.move = 0;
	camera.fovy = 50.0f, camera.aspect_ratio = 1.0f; camera.near_c = 0.1f; camera.far_c = 1000.0f;

	set_ViewMatrix_from_camera_frame();
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}

enum axes { X_AXIS, Y_AXIS, Z_AXIS };
int flag_translation_axis;
#define CAM_TSPEED 1.0f
void renew_cam_position(int del) {
	switch (flag_translation_axis) {
	case X_AXIS:
		camera.pos[0] += CAM_TSPEED * del * (camera.uaxis[0]);
		camera.pos[1] += CAM_TSPEED * del * (camera.uaxis[1]);
		camera.pos[2] += CAM_TSPEED * del * (camera.uaxis[2]);
		break;
	case Y_AXIS:
		camera.pos[0] += CAM_TSPEED * del * (camera.vaxis[0]);
		camera.pos[1] += CAM_TSPEED * del * (camera.vaxis[1]);
		camera.pos[2] += CAM_TSPEED * del * (camera.vaxis[2]);
		break;
	case Z_AXIS:
		camera.pos[0] += CAM_TSPEED * del * (-camera.naxis[0]);
		camera.pos[1] += CAM_TSPEED * del * (-camera.naxis[1]);
		camera.pos[2] += CAM_TSPEED * del * (-camera.naxis[2]);
		break;
	}
}

#define CAM_RSPEED 0.1f
void renew_cam_orientation_rotation_around_u_axis(int angle) {
	// let's get a help from glm
	glm::mat3 RotationMatrix;
	glm::vec3 direction;

	RotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0), CAM_RSPEED * TO_RADIAN * angle,
		glm::vec3(camera.uaxis[0], camera.uaxis[1], camera.uaxis[2])));

	direction = RotationMatrix * glm::vec3(camera.vaxis[0], camera.vaxis[1], camera.vaxis[2]);
	camera.vaxis[0] = direction.x; camera.vaxis[1] = direction.y; camera.vaxis[2] = direction.z;
	direction = RotationMatrix * glm::vec3(camera.naxis[0], camera.naxis[1], camera.naxis[2]);
	camera.naxis[0] = direction.x; camera.naxis[1] = direction.y; camera.naxis[2] = direction.z;
}

void renew_cam_orientation_rotation_around_v_axis(int angle) {
	// let's get a help from glm
	glm::mat3 RotationMatrix;
	glm::vec3 direction;

	RotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0), CAM_RSPEED * TO_RADIAN * angle,
		glm::vec3(camera.vaxis[0], camera.vaxis[1], camera.vaxis[2])));

	direction = RotationMatrix * glm::vec3(camera.uaxis[0], camera.uaxis[1], camera.uaxis[2]);
	camera.uaxis[0] = direction.x; camera.uaxis[1] = direction.y; camera.uaxis[2] = direction.z;
	direction = RotationMatrix * glm::vec3(camera.naxis[0], camera.naxis[1], camera.naxis[2]);
	camera.naxis[0] = direction.x; camera.naxis[1] = direction.y; camera.naxis[2] = direction.z;
}

void renew_cam_orientation_rotation_around_n_axis(int angle) {
	// let's get a help from glm
	glm::mat3 RotationMatrix;
	glm::vec3 direction;

	RotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0), CAM_RSPEED * TO_RADIAN * angle,
		glm::vec3(camera.naxis[0], camera.naxis[1], camera.naxis[2])));

	direction = RotationMatrix * glm::vec3(camera.uaxis[0], camera.uaxis[1], camera.uaxis[2]);
	camera.uaxis[0] = direction.x; camera.uaxis[1] = direction.y; camera.uaxis[2] = direction.z;
	direction = RotationMatrix * glm::vec3(camera.vaxis[0], camera.vaxis[1], camera.vaxis[2]);
	camera.vaxis[0] = direction.x; camera.vaxis[1] = direction.y; camera.vaxis[2] = direction.z;
}



 int flag_draw_hole, flag_hole_effect;
 float hole_frequency, hole_width;

 void initialize_screen(void) {
	 flag_draw_hole = flag_hole_effect = 0;
	 hole_frequency = 1.0f;
	 hole_width = 0.125f;
 }



// callbacks
float PRP_distance_scale[6] = { 0.5f, 1.0f, 2.5f, 5.0f, 10.0f, 20.0f };

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(h_ShaderProgram_simple);
	ModelViewMatrix = glm::scale(ViewMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_simple, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glLineWidth(2.0f);
	draw_axes();
	glLineWidth(1.0f);

	glUseProgram(h_ShaderProgram_TXPS);
  	set_material_floor();
	glUniform1i(loc_texture, TEXTURE_ID_FLOOR);
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-500.0f, 0.0f, 500.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(1000.0f, 1000.0f, 1000.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, -90.0f*TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_floor();

	set_material_ben();
	glUniform1i(loc_texture, TEXTURE_ID_BEN);

	int wolf_clock = (timestamp_scene % 1442) / 2 - 360;

	ModelViewMatrix = glm::rotate(ViewMatrix, 145 * TO_RADIAN - (1.0f * timestamp_scene * TO_RADIAN), glm::vec3(0.0f, 1.0f, 0.0f));
	if ((sinf(2.0f * wolf_clock * TO_RADIAN)) < (45 * TO_RADIAN)) {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(240.0f, 0.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(150.0f, -150.0f, -150.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;

		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_ben2();
	}
	else {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(240.0f, 100.0f * fabs(sinf(2.0f * wolf_clock * TO_RADIAN)) - 50.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(150.0f, -150.0f, -150.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;

		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_ben2();
	}

	set_material_ben2();
	glUniform1i(loc_texture, TEXTURE_ID_BEN2);

	ModelViewMatrix = glm::rotate(ViewMatrix, -((1.0f * timestamp_scene - 105)* TO_RADIAN), glm::vec3(0.0f, 1.0f, 0.0f));

	if ((sinf((2.0f * wolf_clock + 45)* TO_RADIAN)) < (45 * TO_RADIAN)) {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(240.0f, 0.0f, 0.0f));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, (fabs(0.1f * wolf_clock) - 30) * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(0.0f, 9 - 0.025f * fabs(wolf_clock), 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(150.0f, -150.0f, -150.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;

		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_ben();
	}
	else {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(240.0f, 100.0f * fabs(sinf((2.0f * wolf_clock + 45) * TO_RADIAN)) - 50.0f, 0.0f));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, (fabs(0.1f * wolf_clock) - 30) * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(0.0f, 9 - 0.025f * fabs(wolf_clock), 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(150.0f, -150.0f, -150.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;

		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_ben3();
	}
	

	set_material_wolf(); 
	glUniform1i(loc_texture, TEXTURE_ID_WOLF);

	ModelViewMatrix = glm::rotate(ViewMatrix, 145 * TO_RADIAN - (1.0f * timestamp_scene * TO_RADIAN), glm::vec3(0.0f, 1.0f, 0.0f));
	if ((sinf(2.0f * wolf_clock * TO_RADIAN)) < (45 * TO_RADIAN)) {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(240.0f, 0.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(100.0f, 100.0f, 100.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;

		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_wolf();
	}
	else {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(240.0f, 100.0f * fabs(sinf(2.0f * wolf_clock * TO_RADIAN)) - 50.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(100.0f, 100.0f, 100.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;

		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_wolf2();
	}

	set_material_spider();
	glUniform1i(loc_texture, TEXTURE_ID_SPIDER);
	
	int spider_clock = (timestamp_scene % 722) / 2 - 90;
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(200.0f, 0.0f, 300.0f));

	if (spider_clock < 0) {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(0.0f, 0.0f, -(fabs(spider_clock) * 150.0f) / 90));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, 180 * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(30.0f, -30.0f, 30.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
		ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, 180 * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_spider();
	}
	else if (spider_clock > 180) {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(0.0f, 100.0f - (fabs(spider_clock - 180) * 100.0f) / 90, -(fabs(spider_clock - 180) * 150.0f) / 90));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, 180 * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(30.0f, -30.0f, 30.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
		ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, 180 * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, 90 * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, (spider_clock - 180) * 3 * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_spider2();
	}
	else if ((spider_clock > 90) && (spider_clock <= 180)) {

		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(0.0f, (fabs(spider_clock - 90) * 100.0f) / 90, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(30.0f, -30.0f, 30.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
		ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, 90 * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_spider();
	}
	else {
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(30.0f, -30.0f, 30.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
		ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, spider_clock * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_spider();
	}

	set_material_wolf();
	glUniform1i(loc_texture, TEXTURE_ID_BUS);
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(200.0f, 0.0f, 350.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, -90 * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(20.0f, 20.0f, 20.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_bus();

	set_material_wolf();
	glUniform1i(loc_texture, TEXTURE_ID_GODZILLA);

	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-220.0f, 0.0f, 350.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, 90 * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(2.5f, 2.5f, 2.5f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_godzilla();

	ironman_clock = (timestamp_scene % 602) / 2;
	set_material_wolf();
	glUniform1i(loc_texture, TEXTURE_ID_IRONMAN);
	
	if (ironman_clock < 100) {
		ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-140.0f - (0.4f * ironman_clock), 480.0f - ironman_clock, 160.0f + 1.6f * ironman_clock));
	}
	else if ((ironman_clock >= 100) && (ironman_clock < 200)) {
		ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-180.0f, 380.0f, 320.0f));
	}
	else {
		ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-180.0f + (0.4f * (ironman_clock - 200)), ironman_clock + 180, 320.0f - 1.6f * (ironman_clock - 200)));
	}
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(25.0f + 0.1f * fabs(ironman_clock - 150.0f), 25.0f + 0.1f * fabs(ironman_clock - 150.0f), 25.0f + 0.1f * fabs(ironman_clock - 150.0f)));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, -60 * TO_RADIAN, glm::vec3(1.0f, 1.0f, 0.0f));
	ModelViewProjectionMatrix = glm::rotate(ModelViewProjectionMatrix, -(25 * timestamp_scene * TO_RADIAN), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_ironman();

	// need to supply position in EC for shading
	glm::vec4 position_EC = ModelViewMatrix * glm::vec4(light[3].position[0], light[3].position[1],
		light[3].position[2], light[3].position[3]);

	glUniform4fv(loc_light[3].position, 1, &position_EC[0]);
	glUniform4fv(loc_light[3].ambient_color, 1, light[3].ambient_color);
	glUniform4fv(loc_light[3].diffuse_color, 1, light[3].diffuse_color);
	glUniform4fv(loc_light[3].specular_color, 1, light[3].specular_color);

	glm::vec3 direction_EC = glm::mat3(ModelViewMatrix) * glm::vec3(light[3].spot_direction[0], light[3].spot_direction[1],
		light[3].spot_direction[2]);
	glUniform3fv(loc_light[3].spot_direction, 1, &direction_EC[0]);
	glUniform1f(loc_light[3].spot_cutoff_angle, light[3].spot_cutoff_angle);
	glUniform1f(loc_light[3].spot_exponent, light[3].spot_exponent);
	glUseProgram(0);

	glUseProgram(h_ShaderProgram_TXPS);
	if (qb) {
			prepare_shader_program2();
			position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
				light[1].position[2], light[1].position[3]);

			glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
			glUniform4fv(loc_light[1].ambient_color, 1, light[1].ambient_color);
			glUniform4fv(loc_light[1].diffuse_color, 1, light[1].diffuse_color);
			glUniform4fv(loc_light[1].specular_color, 1, light[1].specular_color);

			direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0], light[1].spot_direction[1],
				light[1].spot_direction[2]);
			glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
			glUniform1f(loc_light[1].spot_cutoff_angle, light[1].spot_cutoff_angle);
			glUniform1f(loc_light[1].spot_exponent, light[1].spot_exponent);
			prepare_shader_program();
	}
	else {
			position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
				light[1].position[2], light[1].position[3]);

			glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
			glUniform4fv(loc_light[1].ambient_color, 1, light[1].ambient_color);
			glUniform4fv(loc_light[1].diffuse_color, 1, light[1].diffuse_color);
			glUniform4fv(loc_light[1].specular_color, 1, light[1].specular_color);

			direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0], light[1].spot_direction[1],
				light[1].spot_direction[2]);
			glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
			glUniform1f(loc_light[1].spot_cutoff_angle, light[1].spot_cutoff_angle);
			glUniform1f(loc_light[1].spot_exponent, light[1].spot_exponent);
	}
	glUseProgram(h_ShaderProgram_TXPS);
	

	glUseProgram(0);

	glutSwapBuffers();
}

void timer_scene(int value) {
	timestamp_scene = (timestamp_scene + 1) % UINT_MAX;
	cur_frame_ben = timestamp_scene % N_BEN_FRAMES;
	cur_frame_wolf = timestamp_scene % N_WOLF_FRAMES;
	cur_frame_spider = timestamp_scene % N_SPIDER_FRAMES;
	rotation_angle_tiger = (timestamp_scene % 360)*TO_RADIAN;
	glutPostRedisplay();
	if (flag_tiger_animation)
		glutTimerFunc(10, timer_scene, 0);
}

unsigned int leftbutton_pressed = 0, rightbutton_pressed = 0;
int prevx, prevy;

void keyboard(unsigned char key, int x, int y) {
	static int flag_cull_face = 0;
	static int PRP_distance_level = 4;
	static int flag_blind_effect = 0;

	glm::vec4 position_EC;
	glm::vec3 direction_EC;

	if ((key >= '0') && (key <= '0' + NUMBER_OF_LIGHT_SUPPORTED - 1)) {
		int light_ID = (int)(key - '0');

		glUseProgram(h_ShaderProgram_TXPS);
		light[light_ID].light_on = 1 - light[light_ID].light_on;
		glUniform1i(loc_light[light_ID].light_on, light[light_ID].light_on);
		glUseProgram(0);

		glutPostRedisplay();
		return;
	}

	switch (key) {
	case 'e':
		if (flag_draw_hole) {
			flag_hole_effect = 1 - flag_hole_effect;
			glutPostRedisplay();
		}
		break;
	case 'u':
		flag_translation_axis = X_AXIS;
		break;
	case 'v':
		flag_translation_axis = Y_AXIS;
		break;
	case 'n':
		flag_translation_axis = Z_AXIS;
		break;
	case 'q':
		if (!qb) {
			qb = 1;
		}
		else qb = 0;
		printf("%d", qb);
		break;
	case 'a': // toggle the animation effect.
		flag_tiger_animation = 1 - flag_tiger_animation;
		if (flag_tiger_animation) {
			glutTimerFunc(100, timer_scene, 0);
			fprintf(stdout, "^^^ Animation mode ON.\n");
		}
		else
			fprintf(stdout, "^^^ Animation mode OFF.\n");
		break;
	case 'r':
		glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

		glActiveTexture(GL_TEXTURE0 + TEXTURE_ID_FLOOR);
		glBindTexture(GL_TEXTURE_2D, texture_names[TEXTURE_ID_FLOOR]);

		if (!rm) {
			My_glTexImage2D_from_file("Data/static_objects/road.png");
			rm = 1;
		}
		else {
			My_glTexImage2D_from_file("Data/static_objects/track.png");
			rm = 0;
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glutPostRedisplay();
		break;
	case 't':
		glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

		glActiveTexture(GL_TEXTURE0 + TEXTURE_ID_BUS);
		glBindTexture(GL_TEXTURE_2D, texture_names[TEXTURE_ID_BUS]);

		if (!tm) {
			My_glTexImage2D_from_file("Data/static_objects/cat2.jpg");
			tm = 1;
		}
		else {
			My_glTexImage2D_from_file("Data/static_objects/green.png");
			tm = 0;
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glutPostRedisplay();
		break;
	case 'c':
		flag_cull_face = (flag_cull_face + 1) % 3;
		switch (flag_cull_face) {
		case 0:
			glDisable(GL_CULL_FACE);
			glutPostRedisplay();
			break;
		case 1: // cull back faces;
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glutPostRedisplay();
			break;
		case 2: // cull front faces;
			glCullFace(GL_FRONT);
			glEnable(GL_CULL_FACE);
			glutPostRedisplay();
		}
			break;
		break;
	case 'p':
		flag_polygon_fill = 1 - flag_polygon_fill;
		if (flag_polygon_fill)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'w':
		flag_blind_effect = 1 - flag_blind_effect;
		glUseProgram(h_ShaderProgram_TXPS);
		glUniform1i(loc_blind_effect, flag_blind_effect);
		glUseProgram(0);
		glutPostRedisplay();
		break;
	case 27: // ESC key
		glutLeaveMainLoop(); // Incur destuction callback for cleanups
		break;
	}
}

void motion(int x, int y) {
	if (!camera.move) return;

	if (leftbutton_pressed) {
		renew_cam_position(prevy - y);
	}
	else if (rightbutton_pressed) {
		if (flag_translation_axis == X_AXIS) {
			renew_cam_orientation_rotation_around_u_axis(prevx - x);
		}
		else if (flag_translation_axis == Y_AXIS) {
			renew_cam_orientation_rotation_around_v_axis(prevx - x);
		}
		else {
			renew_cam_orientation_rotation_around_n_axis(prevx - x);
		}
	}
	
	prevx = x; prevy = y;

	set_ViewMatrix_from_camera_frame();
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON)) {
		if (state == GLUT_DOWN) {
			leftbutton_pressed = 1;
			camera.move = 1;
			prevx = x; prevy = y;
		}
		else if (state == GLUT_UP) {
			camera.move = 0;
			leftbutton_pressed = 0;
		}
	}
	if ((button == GLUT_RIGHT_BUTTON)) {
		if (state == GLUT_DOWN) {
			rightbutton_pressed = 1;
			camera.move = 1;
			prevx = x; prevy = y;
		}
		else if (state == GLUT_UP) {
			camera.move = 0;
			rightbutton_pressed = 0;
		}
	}
}

void special(int key, int x, int y) {

	glm::vec4 position_EC;
	glm::vec3 direction_EC;

	switch (key) {
	case GLUT_KEY_LEFT:
		if (camera.fovy > 20) {
			camera.fovy *= 0.8f;
		}
		ProjectionMatrix = glm::perspective(TO_RADIAN * camera.fovy, camera.aspect_ratio, 100.0f, 20000.0f);
		set_ViewMatrix_from_camera_frame();
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

		glUseProgram(h_ShaderProgram_TXPS);
		// Must update the light 1's geometry in EC.
		position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
			light[1].position[2], light[1].position[3]);
		glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
		direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0],
			light[1].spot_direction[1], light[1].spot_direction[2]);
		glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);

		

		//glUseProgram(h_ShaderProgram_TXPS);
		position_EC = ViewMatrix * glm::vec4(light[3].position[0], light[3].position[1],
			light[3].position[2], light[3].position[3]);
		glUniform4fv(loc_light[3].position, 1, &position_EC[0]);
		direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[3].spot_direction[0],
			light[3].spot_direction[1], light[3].spot_direction[2]);
		glUniform3fv(loc_light[3].spot_direction, 1, &direction_EC[0]);

		glUseProgram(0);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (camera.fovy < 150) {
			camera.fovy *= 1.25f;
		}
		ProjectionMatrix = glm::perspective(TO_RADIAN * camera.fovy, camera.aspect_ratio, 100.0f, 20000.0f);
		set_ViewMatrix_from_camera_frame();
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

		


		//glUseProgram(h_ShaderProgram_TXPS);
		position_EC = ViewMatrix * glm::vec4(light[3].position[0], light[3].position[1],
			light[3].position[2], light[3].position[3]);
		glUniform4fv(loc_light[3].position, 1, &position_EC[0]);
		direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[3].spot_direction[0],
			light[3].spot_direction[1], light[3].spot_direction[2]);
		glUniform3fv(loc_light[3].spot_direction, 1, &direction_EC[0]);

		glUseProgram(0);
		glutPostRedisplay();
		break;
	}
}

void reshape(int width, int height) {
	camera.aspect_ratio = (float) width / height;

	ProjectionMatrix = glm::perspective(TO_RADIAN * camera.fovy, camera.aspect_ratio, 100.0f, 20000.0f);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	glutPostRedisplay();
}

void cleanup(void) {
	glDeleteVertexArrays(1, &axes_VAO); 
	glDeleteBuffers(1, &axes_VBO);

	glDeleteVertexArrays(1, &rectangle_VAO);
	glDeleteBuffers(1, &rectangle_VBO);

	glDeleteTextures(N_TEXTURES_USED, texture_names);
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer_scene, 0);
	glutCloseFunc(cleanup);
}


void prepare_shader_program(void) {
	int i;
	char string[256];
	ShaderInfo shader_info_simple[3] = {
		{ GL_VERTEX_SHADER, "Shaders/simple.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
		{ GL_NONE, NULL }
	};
	ShaderInfo shader_info_TXPS[3] = {
		{ GL_VERTEX_SHADER, "Shaders/Phong_Tx.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/Phong_Tx.frag" },
		{ GL_NONE, NULL }
	};

	h_ShaderProgram_simple = LoadShaders(shader_info_simple);
	loc_primitive_color = glGetUniformLocation(h_ShaderProgram_simple, "u_primitive_color");
	loc_ModelViewProjectionMatrix_simple = glGetUniformLocation(h_ShaderProgram_simple, "u_ModelViewProjectionMatrix");

	h_ShaderProgram_TXPS = LoadShaders(shader_info_TXPS);
	loc_ModelViewProjectionMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewProjectionMatrix");
	loc_ModelViewMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrix");
	loc_ModelViewMatrixInvTrans_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrixInvTrans");

	loc_global_ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_global_ambient_color");
	for (i = 0; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		sprintf(string, "u_light[%d].light_on", i);
		loc_light[i].light_on = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].position", i);
		loc_light[i].position = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].ambient_color", i);
		loc_light[i].ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].diffuse_color", i);
		loc_light[i].diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].specular_color", i);
		loc_light[i].specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_direction", i);
		loc_light[i].spot_direction = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_exponent", i);
		loc_light[i].spot_exponent = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_cutoff_angle", i);
		loc_light[i].spot_cutoff_angle = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].light_attenuation_factors", i);
		loc_light[i].light_attenuation_factors = glGetUniformLocation(h_ShaderProgram_TXPS, string);
	}

	loc_material.ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.ambient_color");
	loc_material.diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.diffuse_color");
	loc_material.specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_color");
	loc_material.emissive_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.emissive_color");
	loc_material.specular_exponent = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_exponent");

	loc_hole_effect = glGetUniformLocation(h_ShaderProgram_TXPS, "screen_effect");
	loc_hole_frequency = glGetUniformLocation(h_ShaderProgram_TXPS, "screen_frequency");
	loc_hole_width = glGetUniformLocation(h_ShaderProgram_TXPS, "screen_width");

	loc_blind_effect = glGetUniformLocation(h_ShaderProgram_TXPS, "u_blind_effect");

	loc_texture = glGetUniformLocation(h_ShaderProgram_TXPS, "u_base_texture");

	loc_flag_texture_mapping = glGetUniformLocation(h_ShaderProgram_TXPS, "u_flag_texture_mapping");
	
}

void prepare_shader_program2(void) {
	int i;
	char string[256];
	ShaderInfo shader_info_simple[3] = {
		{ GL_VERTEX_SHADER, "Shaders/simple.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
		{ GL_NONE, NULL }
	};
	ShaderInfo shader_info_TXPS[3] = {
		{ GL_VERTEX_SHADER, "Shaders/Gouraud_Tx.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/Gouraud_Tx.frag" },
		{ GL_NONE, NULL }
	};

	h_ShaderProgram_simple = LoadShaders(shader_info_simple);
	loc_primitive_color = glGetUniformLocation(h_ShaderProgram_simple, "u_primitive_color");
	loc_ModelViewProjectionMatrix_simple = glGetUniformLocation(h_ShaderProgram_simple, "u_ModelViewProjectionMatrix");

	h_ShaderProgram_TXPS = LoadShaders(shader_info_TXPS);
	loc_ModelViewProjectionMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewProjectionMatrix");
	loc_ModelViewMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrix");
	loc_ModelViewMatrixInvTrans_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrixInvTrans");

	loc_global_ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_global_ambient_color");
	for (i = 0; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		sprintf(string, "u_light[%d].light_on", i);
		loc_light[i].light_on = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].position", i);
		loc_light[i].position = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].ambient_color", i);
		loc_light[i].ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].diffuse_color", i);
		loc_light[i].diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].specular_color", i);
		loc_light[i].specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_direction", i);
		loc_light[i].spot_direction = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_exponent", i);
		loc_light[i].spot_exponent = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_cutoff_angle", i);
		loc_light[i].spot_cutoff_angle = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].light_attenuation_factors", i);
		loc_light[i].light_attenuation_factors = glGetUniformLocation(h_ShaderProgram_TXPS, string);
	}

	loc_material.ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.ambient_color");
	loc_material.diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.diffuse_color");
	loc_material.specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_color");
	loc_material.emissive_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.emissive_color");
	loc_material.specular_exponent = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_exponent");

	loc_texture = glGetUniformLocation(h_ShaderProgram_TXPS, "u_base_texture");

	loc_flag_texture_mapping = glGetUniformLocation(h_ShaderProgram_TXPS, "u_flag_texture_mapping");

}

void initialize_lights_and_material(void) { // follow OpenGL conventions for initialization
	int i;

	glUseProgram(h_ShaderProgram_TXPS);

	glUniform4f(loc_global_ambient_color, 0.115f, 0.115f, 0.115f, 1.0f);
	for (i = 0; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		glUniform4f(loc_light[i].position, 0.0f, 0.0f, 1.0f, 0.0f);
		glUniform4f(loc_light[i].ambient_color, 0.0f, 0.0f, 0.0f, 1.0f);
		if (i == 0) {
			glUniform1i(loc_light[i].light_on, 1); // turn on all lights initially
			glUniform4f(loc_light[i].diffuse_color, 1.0f, 1.0f, 1.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (i == 1){
			glUniform1i(loc_light[i].light_on, 1); // turn on all lights initially
			glUniform4f(loc_light[i].diffuse_color, 0.0f, 0.0f, 0.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (i == 2) {
			glUniform1i(loc_light[i].light_on, 0); // turn off all lights initially
			glUniform4f(loc_light[i].diffuse_color, 0.0f, 0.0f, 0.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			glUniform1i(loc_light[i].light_on, 0); // turn off all lights initially
			glUniform4f(loc_light[i].diffuse_color, 0.0f, 0.0f, 0.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		glUniform3f(loc_light[i].spot_direction, 0.0f, 0.0f, -1.0f);
		glUniform1f(loc_light[i].spot_exponent, 0.0f); // [0.0, 128.0]
		glUniform1f(loc_light[i].spot_cutoff_angle, 180.0f); // [0.0, 90.0] or 180.0 (180.0 for no spot light effect)
		glUniform4f(loc_light[i].light_attenuation_factors, 1.0f, 0.0f, 0.0f, 0.0f); // .w != 0.0f for no ligth attenuation
	}

	glUniform4f(loc_material.ambient_color, 0.2f, 0.2f, 0.2f, 1.0f);
	glUniform4f(loc_material.diffuse_color, 0.8f, 0.8f, 0.8f, 1.0f);
	glUniform4f(loc_material.specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform4f(loc_material.emissive_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform1f(loc_material.specular_exponent, 0.0f); // [0.0, 128.0]

	glUniform1i(loc_hole_effect, 0);
	glUniform1f(loc_hole_frequency, 1.0f);
	glUniform1f(loc_hole_width, 0.125f);

	glUniform1i(loc_blind_effect, 0);

	glUseProgram(0);
}

void initialize_flags(void) {
	flag_tiger_animation = 1;
	flag_polygon_fill = 1;
	flag_texture_mapping = 1;

	glUseProgram(h_ShaderProgram_TXPS);
	glUniform1i(loc_flag_texture_mapping, flag_texture_mapping);
	glUseProgram(0);
}

void initialize_OpenGL(void) {

	glEnable(GL_MULTISAMPLE);


  	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//ViewMatrix = glm::lookAt(PRP_distance_scale[0] * glm::vec3(500.0f, 300.0f, 500.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	initialize_camera();
	initialize_lights_and_material();
	initialize_flags();

	ProjectionMatrix = glm::mat4(1.0f);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	flag_translation_axis = Z_AXIS;

	glGenTextures(N_TEXTURES_USED, texture_names);
}

void set_up_scene_lights(void) {
	// point_light_EC: use light 0
	light[0].light_on = 1;
	light[0].position[0] = 0.0f; light[0].position[1] = 1000.0f; 	// point light position in EC
	light[0].position[2] = 0.0f; light[0].position[3] = 1.0f;

	light[0].ambient_color[0] = 0.13f; light[0].ambient_color[1] = 0.13f;
	light[0].ambient_color[2] = 0.13f; light[0].ambient_color[3] = 1.0f;

	light[0].diffuse_color[0] = 0.5f; light[0].diffuse_color[1] = 0.5f;
	light[0].diffuse_color[2] = 0.5f; light[0].diffuse_color[3] = 1.5f;

	light[0].specular_color[0] = 0.8f; light[0].specular_color[1] = 0.8f;
	light[0].specular_color[2] = 0.8f; light[0].specular_color[3] = 1.0f;

	// spot_light_WC: use light 1
	light[1].light_on = 1;
	light[1].position[0] = 300.0f; light[1].position[1] = 1000.0f; // spot light position in WC
	light[1].position[2] = 200.0f; light[1].position[3] = 1.0f;

	light[1].ambient_color[0] = 0.52f; light[1].ambient_color[1] = 0.52f;
	light[1].ambient_color[2] = 0.52f; light[1].ambient_color[3] = 1.0f;

	light[1].diffuse_color[0] = 0.0f; light[1].diffuse_color[1] = 0.0f;
	light[1].diffuse_color[2] = 1.0f; light[1].diffuse_color[3] = 1.0f;

	light[1].specular_color[0] = 0.772f; light[1].specular_color[1] = 0.772f;
	light[1].specular_color[2] = 0.772f; light[1].specular_color[3] = 1.0f;

	light[1].spot_direction[0] = 0.0f; light[1].spot_direction[1] = -1.0f; // spot light direction in WC
	light[1].spot_direction[2] = 0.0f;
	light[1].spot_cutoff_angle = 20.0f;
	light[1].spot_exponent = 8.0f;


	// spot_light_WC: use light 2
	light[2].light_on = 0;
	light[2].position[0] = 100.0f; light[2].position[1] = 500.0f; // spot light position in WC
	light[2].position[2] = 100.0f; light[2].position[3] = 1.0f;

	light[2].ambient_color[0] = 0.152f; light[2].ambient_color[1] = 0.152f;
	light[2].ambient_color[2] = 0.152f; light[2].ambient_color[3] = 1.0f;
	
	light[2].diffuse_color[0] = 1.0f; light[2].diffuse_color[1] = 0.0f;
	light[2].diffuse_color[2] = 0.0f; light[2].diffuse_color[3] = 1.5f;

	light[2].specular_color[0] = 0.772f; light[2].specular_color[1] = 0.772f;
	light[2].specular_color[2] = 0.772f; light[2].specular_color[3] = 1.0f;

	light[2].spot_direction[0] = 0.0f; light[2].spot_direction[1] = -1.0f; // spot light direction in WC
	light[2].spot_direction[2] = 0.0f;
	light[2].spot_cutoff_angle = 10.0f;
	light[2].spot_exponent = 8.0f;

	// spot_light_WC: use light 3
	light[3].light_on = 0;
	light[3].position[0] = -30.0f; light[3].position[1] = 500.0f; // spot light position in WC
	light[3].position[2] = 30.0f; light[3].position[3] = 1.0f;

	light[3].ambient_color[0] = 0.752f; light[3].ambient_color[1] = 0.752f;
	light[3].ambient_color[2] = 0.752f; light[3].ambient_color[3] = 1.0f;

	light[3].diffuse_color[0] = 0.0f; light[3].diffuse_color[1] = 0.0f;
	light[3].diffuse_color[2] = 1.0f; light[3].diffuse_color[3] = 1.0f;

	light[3].specular_color[0] = 0.772f; light[3].specular_color[1] = 0.772f;
	light[3].specular_color[2] = 0.772f; light[3].specular_color[3] = 1.0f;
	
	light[3].spot_direction[0] = 0.053f; light[3].spot_direction[1] = -1.0f; // spot light direction in WC
	light[3].spot_direction[2] = -0.053f;
	light[3].spot_cutoff_angle = 0.8f;
	light[3].spot_exponent = 8.0f;

	glUseProgram(h_ShaderProgram_TXPS);
	glUniform1i(loc_light[0].light_on, light[0].light_on);
	glUniform4fv(loc_light[0].position, 1, light[0].position);
	glUniform4fv(loc_light[0].ambient_color, 1, light[0].ambient_color);
	glUniform4fv(loc_light[0].diffuse_color, 1, light[0].diffuse_color);
	glUniform4fv(loc_light[0].specular_color, 1, light[0].specular_color);

	glUniform1i(loc_light[1].light_on, light[1].light_on);
	// need to supply position in EC for shading
	glm::vec4 position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
												light[1].position[2], light[1].position[3]);
	glUniform4fv(loc_light[1].position, 1, &position_EC[0]); 
	glUniform4fv(loc_light[1].ambient_color, 1, light[1].ambient_color);
	glUniform4fv(loc_light[1].diffuse_color, 1, light[1].diffuse_color);
	glUniform4fv(loc_light[1].specular_color, 1, light[1].specular_color);

	glm::vec3 direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0], light[1].spot_direction[1],
		light[1].spot_direction[2]);
	glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
	glUniform1f(loc_light[1].spot_cutoff_angle, light[1].spot_cutoff_angle);
	glUniform1f(loc_light[1].spot_exponent, light[1].spot_exponent);
	glUseProgram(0);

	glUseProgram(h_ShaderProgram_TXPS);
	glUniform1i(loc_light[2].light_on, light[2].light_on);
	// need to supply position in EC for shading
	position_EC = ViewMatrix * glm::vec4(light[2].position[0], light[2].position[1],
		light[2].position[2], light[2].position[3]);
	glUniform4fv(loc_light[2].position, 1, &position_EC[0]);
	glUniform4fv(loc_light[2].ambient_color, 1, light[2].ambient_color);
	glUniform4fv(loc_light[2].diffuse_color, 1, light[2].diffuse_color);
	glUniform4fv(loc_light[2].specular_color, 1, light[2].specular_color);

	direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[2].spot_direction[0], light[2].spot_direction[1],
		light[2].spot_direction[2]);
	glUniform3fv(loc_light[2].spot_direction, 1, &direction_EC[0]);
	glUniform1f(loc_light[2].spot_cutoff_angle, light[2].spot_cutoff_angle);
	glUniform1f(loc_light[2].spot_exponent, light[2].spot_exponent);
	glUseProgram(0);

	glUseProgram(h_ShaderProgram_TXPS);
	glUniform1i(loc_light[3].light_on, light[3].light_on);
	// need to supply position in EC for shading
	position_EC = ViewMatrix * glm::vec4(light[3].position[0], light[3].position[1],
		light[3].position[2], light[3].position[3]);
	glUniform4fv(loc_light[3].position, 1, &position_EC[0]);
	glUniform4fv(loc_light[3].ambient_color, 1, light[3].ambient_color);
	glUniform4fv(loc_light[3].diffuse_color, 1, light[3].diffuse_color);
	glUniform4fv(loc_light[3].specular_color, 1, light[3].specular_color);
	// need to supply direction in EC for shading in this example shader
	// note that the viewing transform is a rigid body transform
	// thus transpose(inverse(mat3(ViewMatrix)) = mat3(ViewMatrix)

	direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[3].spot_direction[0], light[3].spot_direction[1], 
		light[3].spot_direction[2]);
	glUniform3fv(loc_light[3].spot_direction, 1, &direction_EC[0]); 
	glUniform1f(loc_light[3].spot_cutoff_angle, light[3].spot_cutoff_angle);
	glUniform1f(loc_light[3].spot_exponent, light[3].spot_exponent);

	glUseProgram(0);
}

void prepare_scene(void) {
	prepare_axes();
	prepare_floor();
	prepare_ben();
	prepare_ben2();
	prepare_wolf();
	prepare_spider();
	prepare_bus();
	prepare_godzilla();
	prepare_ironman();
	set_up_scene_lights();
	initialize_screen();
}

void initialize_renderer(void) {
	register_callbacks();
	prepare_shader_program();
	initialize_OpenGL();
	prepare_scene();
	initialize_camera();
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = GL_TRUE;

	error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*init********************************************************\n");
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

#define N_MESSAGE_LINES 1
void main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 3D Objects";
	char messages[N_MESSAGE_LINES][256] = { "    - Keys used: '0', '1', 'a', 't', 'f', 'c', 'd', 'y', 'u', 'i', 'o', 'ESC'"  };

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 800);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}