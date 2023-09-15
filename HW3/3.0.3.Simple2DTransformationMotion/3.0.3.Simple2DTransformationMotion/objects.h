// firecracker1

#define FC1 0
#define FC2 1
#define FC3 2
#define FC4 3
#define FC5 4

GLfloat fc1[4][2] = { { -5, 5 }, { 5, 5 }, { 5, -5 }, { -5, -5 } };
GLfloat fc2[4][2] = { { -5, 5 }, { 5, 5 }, { 5, -5 }, { -5, -5 } };
GLfloat fc3[4][2] = { { -5, 5 }, { 5, 5 }, { 5, -5 }, { -5, -5 } };
GLfloat fc4[4][2] = { { -5, 5 }, { 5, 5 }, { 5, -5 }, { -5, -5 } };
GLfloat fc5[4][2] = { { -5, 5 }, { 5, 5 }, { 5, -5 }, { -5, -5 } };

GLfloat firecracker_color[5][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 120 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f,  0 / 255.0f },
	{ 0 / 255.0f,  255 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f,   255 / 255.0f }
};

GLuint VBO_firecracker, VAO_firecracker;

void prepare_firecracker() {
	GLsizeiptr buffer_size = sizeof(fc1) + sizeof(fc2) + sizeof(fc3) + sizeof(fc4)
		+ sizeof(fc5);

	glGenBuffers(1, &VBO_firecracker);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_firecracker);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fc1), fc1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fc1), sizeof(fc2), fc2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fc1) + sizeof(fc2), sizeof(fc3), fc3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fc1) + sizeof(fc2) + sizeof(fc3), sizeof(fc4), fc4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fc1) + sizeof(fc2) + sizeof(fc3) + sizeof(fc4), sizeof(fc5), fc5);

	glGenVertexArrays(1, &VAO_firecracker);
	glBindVertexArray(VAO_firecracker);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_firecracker);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_firecracker1() { 
	glBindVertexArray(VAO_firecracker);

	glUniform3fv(loc_primitive_color, 1, firecracker_color[FC1]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void draw_firecracker2() { 
	glBindVertexArray(VAO_firecracker);

	glUniform3fv(loc_primitive_color, 1, firecracker_color[FC2]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void draw_firecracker3() {
	glBindVertexArray(VAO_firecracker);

	glUniform3fv(loc_primitive_color, 1, firecracker_color[FC3]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void draw_firecracker4() { 
	glBindVertexArray(VAO_firecracker);

	glUniform3fv(loc_primitive_color, 1, firecracker_color[FC4]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void draw_firecracker5() { 
	glBindVertexArray(VAO_firecracker);

	glUniform3fv(loc_primitive_color, 1, firecracker_color[FC5]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

// circle
#define CIRCLE 0

GLfloat circle[8][2] = { { -200, -82.84 }, { -200, 82.84 }, { -82.84, 200 }, { 82.84, 200 },
	{ 200, 82.84 }, { 200, -82.84 }, { 82.84, -200 }, { -82.84, -200} };

GLfloat circle_color[1][3] = {
	{ 102 / 255.0f, 37 / 255.0f, 0 / 255.0f }
};

GLuint VBO_circle, VAO_circle;

void prepare_circle() {
	GLsizeiptr buffer_size = sizeof(circle);

	glGenBuffers(1, &VBO_circle);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_circle);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); 

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(circle), circle);

	glGenVertexArrays(1, &VAO_circle);
	glBindVertexArray(VAO_circle);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_circle);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_circle() { 
	glBindVertexArray(VAO_circle);

	glUniform3fv(loc_primitive_color, 1, circle_color[CIRCLE]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
	glBindVertexArray(0);
}


// blood
#define BD 0

GLfloat bd[4][2] = { { -3, 90 }, { 3, 90 }, { 3, 75 }, { -3, 75 } };

GLfloat blood_color[1][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
};

GLuint VBO_blood, VAO_blood;

void prepare_blood() {
	GLsizeiptr buffer_size = sizeof(bd);

	glGenBuffers(1, &VBO_blood);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_blood);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bd), bd);

	glGenVertexArrays(1, &VAO_blood);
	glBindVertexArray(VAO_blood);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_blood);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_blood() { 
	glBindVertexArray(VAO_blood);

	glUniform3fv(loc_primitive_color, 1, blood_color[BD]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}


// airplane
#define AIRPLANE_BIG_WING 0
#define AIRPLANE_SMALL_WING 1
#define AIRPLANE_BODY 2
#define AIRPLANE_BACK 3
#define AIRPLANE_SIDEWINDER1 4
#define AIRPLANE_SIDEWINDER2 5
#define AIRPLANE_CENTER 6

GLfloat big_wing[6][2] = { { 0.0, 0.0 }, { -20.0, 15.0 }, { -20.0, 20.0 }, { 0.0, 23.0 }, { 20.0, 20.0 }, { 20.0, 15.0 } };
GLfloat small_wing[6][2] = { { 0.0, -18.0 }, { -11.0, -12.0 }, { -12.0, -7.0 }, { 0.0, -10.0 }, { 12.0, -7.0 }, { 11.0, -12.0 } };
GLfloat body[5][2] = { { 0.0, -25.0 }, { -6.0, 0.0 }, { -6.0, 22.0 }, { 6.0, 22.0 }, { 6.0, 0.0 } };
GLfloat back[5][2] = { { 0.0, 25.0 }, { -7.0, 24.0 }, { -7.0, 21.0 }, { 7.0, 21.0 }, { 7.0, 24.0 } };
GLfloat sidewinder1[5][2] = { { -20.0, 10.0 }, { -18.0, 3.0 }, { -16.0, 10.0 }, { -18.0, 20.0 }, { -20.0, 20.0 } };
GLfloat sidewinder2[5][2] = { { 20.0, 10.0 }, { 18.0, 3.0 }, { 16.0, 10.0 }, { 18.0, 20.0 }, { 20.0, 20.0 } };
GLfloat center[1][2] = { { 0.0, 0.0 } };

GLfloat airplane_color[7][3] = {
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // big_wing
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // small_wing
	{ 111 / 255.0f,  85 / 255.0f, 157 / 255.0f },  // body
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // back
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder1
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder2
	{ 255 / 255.0f,   0 / 255.0f,   0 / 255.0f }   // center
};

GLuint VBO_airplane, VAO_airplane;

void prepare_airplane() {
	GLsizeiptr buffer_size = sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2) + sizeof(center);

	glGenBuffers(1, &VBO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); 

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(big_wing), big_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing), sizeof(small_wing), small_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing), sizeof(body), body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body), sizeof(back), back);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back),
		sizeof(sidewinder1), sidewinder1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1), sizeof(sidewinder2), sidewinder2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2), sizeof(center), center);

	glGenVertexArrays(1, &VAO_airplane);
	glBindVertexArray(VAO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_airplane() { 
	glBindVertexArray(VAO_airplane);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BIG_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SMALL_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BACK]);
	glDrawArrays(GL_TRIANGLE_FAN, 17, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER1]);
	glDrawArrays(GL_TRIANGLE_FAN, 22, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER2]);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_CENTER]);
	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 32, 1);
	glPointSize(1.0);
	glBindVertexArray(0);
}

//shirt
#define SHIRT_HEAD 0
#define SHIRT_CLOTH_LEFT 1
#define SHIRT_CLOTH_RIGHT 2
#define SHIRT_LEFT_BODY 3
#define SHIRT_RIGHT_BODY 4
#define SHIRT_LEFT_COLLAR 5
#define SHIRT_RIGHT_COLLAR 6
#define SHIRT_BUTTON1 7
#define SHIRT_BUTTON2 8
#define SHIRT_BUTTON3 9
#define SHIRT_BUTTON4 10
#define SHIRT_HEAD2 11
#define SHIRT_LEFT_ARM 12
#define SHIRT_LEFT_LEG 13
#define SHIRT_RIGHT_LEG 14
#define SHIRT_LEFT_FOOT 15
#define SHIRT_RIGHT_FOOT 16
#define SHIRT_LEFT_HAND 17
#define SHIRT_HAIR 18
#define SHIRT_LEFT_EYE 19
#define SHIRT_RIGHT_EYE 20
#define SHIRT_RIGHT_ARM 21
#define SHIRT_RIGHT_HAND 22
#define SHIRT_LEFT_ARM1 23
#define SHIRT_LEFT_ARM2 24
#define SHIRT_LEFT_HAND2 25
#define SHIRT_RIGHT_ARM1 26
#define SHIRT_RIGHT_ARM2 27
#define SHIRT_RIGHT_HAND2 28

GLfloat head[4][2] = { { -20.0, 90.0 },{ 20.0, 90.0 },{ 20.0, 50.0 }, { -20.0, 50.0 } };
GLfloat cloth_left[5][2] = { { 20.0, 54.0 },{ 55.0, 40.0 },{ 30.0, -45.0 },{ 0.0, -45.0 }, { 0.0, 50.0 } };
GLfloat cloth_right[5][2] = { { -20.0, 54.0 },{ -55.0, 40.0 },{ -30.0, -45.0 },{ 0.0, -45.0 }, { 0.0, 50.0 } };
GLfloat left_body[6][2] = { { -30.0, -45.0 },{ -40.0, -45.0 },{ -55.0, 40.0 },{ -30.0, 50.0 },{ -30.0, 45.0 },{-10, -20.0} };
GLfloat right_body[6][2] = { { 30.0, -45.0 },{ 10.0, -20.0 },{ 30.0, 45.0 },{ 30.0, 50.0 },{ 55.0, 40.0 },{ 40.0, -45.0 } };
GLfloat left_collar[4][2] = { { 0.0, 50.0 },{ -15.0, 35.0 },{ -22.0, 40.0 },{ -20.0, 55.0 } };
GLfloat right_collar[4][2] = { { 0.0, 50.0 },{ 20.0, 55.0 },{ 22.0, 40.0 },{ 15.0, 35.0 } };
GLfloat button1[3][2] = { { -5.0, 30.0 },{ 5.0, 30.0 },{ 0.0, 25.0 } };
GLfloat button2[3][2] = { { -5.0, 15.0 },{ 5.0, 15.0 },{ 0.0, 10.0 } };
GLfloat button3[3][2] = { { -5.0, 0.0 },{ 5.0, 0.0 },{ 0.0, -5.0 } };
GLfloat button4[3][2] = { { -5.0, -15.0 },{ 5.0, -15.0 },{ 0.0, -20.0 } };
GLfloat head2[4][2] = { { -30.0, 110.0 },{ 30.0, 110.0 },{ 30.0, 60.0 }, { -30.0, 60.0 } };
GLfloat left_arm[4][2] = { { -55.0, 40.0 }, { -80.0, -75.0 }, { -65.0, -80.0 }, { -35.0, 30.0 } };
GLfloat left_leg[4][2] = { { 20.0, -45.0 }, { -40.0, -45.0 }, { -80.0, -200.0 }, { -50.0, -210.0 } };
GLfloat right_leg[4][2] = { { -20.0, -45.0 }, { 40.0, -45.0 }, { 80.0, -200.0 }, { 50.0, -210.0 } };
GLfloat left_foot[4][2] = { { -50.0, -210.0 }, { -55.0, -220.0 }, { -103.0, -203.0 }, { -100.0, -193.0 } };
GLfloat right_foot[4][2] = { { 50.0, -210.0 }, { 55.0, -220.0 }, { 103.0, -203.0 }, { 100.0, -193.0 } };
GLfloat left_hand[4][2] = { { -80.0, -75.0 }, { -65.0, -80.0 }, { -75.0, -90.0 }, { -90.0, -85.0 } };
GLfloat hair[4][2] = { { -32.0, 110.0 }, { 32.0, 110.0 }, { 32.0, 130 }, { -32.0, 130 } };
GLfloat left_eye[4][2] = { { 15, 97 }, { 12, 97 }, { 12, 92 }, { 15, 92 } };
GLfloat right_eye[4][2] = { { -15, 97 }, { -12, 97 }, { -12, 92 }, { -15, 92 } };
GLfloat right_arm[4][2] = { { 55.0, 40.0 }, { 80.0, -75.0 }, { 65.0, -80.0 }, { 35.0, 30.0 } };
GLfloat right_hand[4][2] = { { 80.0, -75.0 }, { 65.0, -80.0 }, { 75.0, -90.0 }, { 90.0, -85.0 } };
GLfloat left_arm1[4][2] = { { -55.0, 40.0 }, { -70.0, -10.0 }, { -65.0, -45.0 }, { -35.0, 30.0 } };
GLfloat left_arm2[4][2] = { { -80.0, 10.0 }, { -65.0, -15.0 }, { -65.0, -45.0 }, { -90.0, -10.0 } };
GLfloat left_hand2[4][2] = { { -80.0, 10.0 }, { -90.0, 20.0 }, { -100.0, 0.0 }, { -90.0, -10.0 } };
GLfloat right_arm1[4][2] = { { 55.0, 40.0 }, { 70.0, -10.0 }, { 65.0, -45.0 }, { 35.0, 30.0 } };
GLfloat right_arm2[4][2] = { { 80.0, 10.0 }, { 65.0, -15.0 }, { 65.0, -45.0 }, { 90.0, -10.0 } };
GLfloat right_hand2[4][2] = { { 80.0, 10.0 }, { 90.0, 20.0 }, { 100.0, 0.0 }, { 90.0, -10.0 } };

GLfloat shirt_color[29][3] = {
	{ 228 / 255.0f, 164 / 255.0f, 149 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 228 / 255.0f, 164 / 255.0f, 149 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 228 / 255.0f, 164 / 255.0f, 149 / 255.0f },
	{ 255 / 255.0f, 187 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 255 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 255 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 228 / 255.0f, 164 / 255.0f, 149 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 228 / 255.0f, 164 / 255.0f, 149 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 228 / 255.0f, 164 / 255.0f, 149 / 255.0f }

};

GLuint VBO_shirt, VAO_shirt;
void prepare_shirt() {
	GLsizeiptr buffer_size = sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(cloth_left) + sizeof(cloth_right) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head) + sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg)
		+ sizeof(left_foot) + sizeof(right_foot) + sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye)
		+ sizeof(right_arm) + sizeof(right_hand) + sizeof(left_arm1) + sizeof(left_arm2) + sizeof(left_hand2)
		+ sizeof(right_arm1) + sizeof(right_arm2) + sizeof(right_hand2);

	glGenBuffers(1, &VBO_shirt);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_shirt);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); 


	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(head), head);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head), sizeof(cloth_left), cloth_left);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left), sizeof(cloth_right), cloth_right);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right), sizeof(left_body), left_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body),
		sizeof(right_body), right_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body), sizeof(left_collar), left_collar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar), sizeof(right_collar), right_collar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar), sizeof(button1), button1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1), sizeof(button2), button2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2), sizeof(button3), button3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3), sizeof(button4), button4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4), sizeof(head2), head2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2), sizeof(left_arm), left_arm);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm), sizeof(left_leg), left_leg);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg), sizeof(right_leg), right_leg);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg), sizeof(left_foot), left_foot);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot), sizeof(right_foot), right_foot);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot), sizeof(left_hand), left_hand);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand), sizeof(hair), hair);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair), sizeof(left_eye), left_eye);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye), sizeof(right_eye), right_eye);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye), sizeof(right_arm), right_arm);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye) + sizeof(right_arm), sizeof(right_hand), right_hand);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye) + sizeof(right_arm)
		+ sizeof(right_hand), sizeof(left_arm1), left_arm1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye) + sizeof(right_arm)
		+ sizeof(right_hand) + sizeof(left_arm1), sizeof(left_arm2), left_arm2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye) + sizeof(right_arm)
		+ sizeof(right_hand) + sizeof(left_arm1) + sizeof(left_arm2), sizeof(left_hand2), left_hand2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye) + sizeof(right_arm)
		+ sizeof(right_hand) + sizeof(left_arm1) + sizeof(left_arm2) + sizeof(left_hand2), sizeof(right_arm1), right_arm1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye) + sizeof(right_arm)
		+ sizeof(right_hand) + sizeof(left_arm1) + sizeof(left_arm2) + sizeof(left_hand2)
		+ sizeof(right_arm1), sizeof(right_arm2), right_arm2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(head) + sizeof(cloth_left) + sizeof(cloth_right) + sizeof(left_body)
		+ sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4)
		+ sizeof(head2) + sizeof(left_arm) + sizeof(left_leg) + sizeof(right_leg) + sizeof(left_foot) + sizeof(right_foot)
		+ sizeof(left_hand) + sizeof(hair) + sizeof(left_eye) + sizeof(right_eye) + sizeof(right_arm)
		+ sizeof(right_hand) + sizeof(left_arm1) + sizeof(left_arm2) + sizeof(left_hand2)
		+ sizeof(right_arm1) + sizeof(right_arm2), sizeof(right_hand2), right_hand2);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_shirt);
	glBindVertexArray(VAO_shirt);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_shirt);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_shirt() {
	glBindVertexArray(VAO_shirt);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_HEAD]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_CLOTH_LEFT]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 5);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_CLOTH_RIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 9, 5);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 14, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 26, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 30, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON1]);
	glDrawArrays(GL_TRIANGLE_FAN, 34, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON2]);
	glDrawArrays(GL_TRIANGLE_FAN, 37, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON3]);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON4]);
	glDrawArrays(GL_TRIANGLE_FAN, 43, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_HEAD2]);
	glDrawArrays(GL_TRIANGLE_FAN, 46, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_ARM]);
	glDrawArrays(GL_TRIANGLE_FAN, 50, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_LEG]);
	glDrawArrays(GL_TRIANGLE_FAN, 54, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_LEG]);
	glDrawArrays(GL_TRIANGLE_FAN, 58, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_FOOT]);
	glDrawArrays(GL_TRIANGLE_FAN, 62, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_FOOT]);
	glDrawArrays(GL_TRIANGLE_FAN, 66, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_HAND]);
	glDrawArrays(GL_TRIANGLE_FAN, 70, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_HAIR]);
	glDrawArrays(GL_TRIANGLE_FAN, 74, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_EYE]);
	glDrawArrays(GL_TRIANGLE_FAN, 78, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_EYE]);
	glDrawArrays(GL_TRIANGLE_FAN, 82, 4);

	glBindVertexArray(0);
}

void draw_shirt2() {
	glBindVertexArray(VAO_shirt);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_ARM]);
	glDrawArrays(GL_TRIANGLE_FAN, 86, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_HAND]);
	glDrawArrays(GL_TRIANGLE_FAN, 90, 4);
	
	glBindVertexArray(0);
}

void draw_shirt3() {
	glBindVertexArray(VAO_shirt);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_HEAD]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_HEAD2]);
	glDrawArrays(GL_TRIANGLE_FAN, 46, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_HAIR]);
	glDrawArrays(GL_TRIANGLE_FAN, 74, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_EYE]);
	glDrawArrays(GL_TRIANGLE_FAN, 78, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_EYE]);
	glDrawArrays(GL_TRIANGLE_FAN, 82, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_LEG]);
	glDrawArrays(GL_TRIANGLE_FAN, 54, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_LEG]);
	glDrawArrays(GL_TRIANGLE_FAN, 58, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_FOOT]);
	glDrawArrays(GL_TRIANGLE_FAN, 62, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_FOOT]);
	glDrawArrays(GL_TRIANGLE_FAN, 66, 4);

	glBindVertexArray(0);
}

void draw_shirt4() {
	glBindVertexArray(VAO_shirt);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_CLOTH_LEFT]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 5);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_CLOTH_RIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 9, 5);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 14, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 26, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 30, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON1]);
	glDrawArrays(GL_TRIANGLE_FAN, 34, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON2]);
	glDrawArrays(GL_TRIANGLE_FAN, 37, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON3]);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON4]);
	glDrawArrays(GL_TRIANGLE_FAN, 43, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_ARM1]);
	glDrawArrays(GL_TRIANGLE_FAN, 94, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_ARM2]);
	glDrawArrays(GL_TRIANGLE_FAN, 98, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_HAND2]);
	glDrawArrays(GL_TRIANGLE_FAN, 102, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_ARM1]);
	glDrawArrays(GL_TRIANGLE_FAN, 106, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_ARM2]);
	glDrawArrays(GL_TRIANGLE_FAN, 110, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_HAND2]);
	glDrawArrays(GL_TRIANGLE_FAN, 114, 4);

	glBindVertexArray(0);
}


// hat
#define HAT_LEAF 0
#define HAT_BODY 1
#define HAT_STRIP 2
#define HAT_BOTTOM 3
#define HAT_ARM1 4
#define HAT_ARM2 5
#define HAT_RIGHT_HAND 6

GLfloat hat_leaf[4][2] = { { -19.0, 160.0 },{ -19.0, 176.0 },{ -7.0, 184.0 },{ -7.0, 168.0 } };
GLfloat hat_body[4][2] = { { -69.0, 104.0 },{ 19.0, 104.0 },{ 14.0, 160.0 },{ -64.0, 160.0 } };
GLfloat hat_strip[4][2] = { { -70.0, 100.0 },{ 20.0, 100.0 },{ 19.0, 104.0 },{ -69.0, 104.0 } };
GLfloat hat_bottom[4][2] = { { 30.0, 100.0 },{ -80.0, 100.0 },{ -80.0, 92.0 },{ 30.0, 92.0 } };
GLfloat hat_arm1[4][2] = { { 33.0, 97.0 },{ 27.0, 90.0 },{ 40.0, 40.0 },{ 60.0, 40.0 } };
GLfloat hat_arm2[4][2] = { { 40.0, 40.0 },{ 60.0, 40.0 },{ 0.0, -15.0 },{ 0.0, 15.0 } };
GLfloat hat_right_hand[4][2] = { { 27.0, 90.0 },{ 33.0, 97.0 },{ 28.0, 102.0 },{ 22.0, 95.0 } };

GLfloat hat_color[7][3] = {
	{ 167 / 255.0f, 255 / 255.0f, 55 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 228 / 255.0f, 164 / 255.0f, 149 / 255.0f }
};

GLuint VBO_hat, VAO_hat;

void prepare_hat() {
	GLsizeiptr buffer_size = sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip) + sizeof(hat_bottom) + sizeof(hat_arm1) + sizeof(hat_arm2) + sizeof(hat_right_hand);

	glGenBuffers(1, &VBO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); 

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(hat_leaf), hat_leaf);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf), sizeof(hat_body), hat_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body), sizeof(hat_strip), hat_strip);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip), sizeof(hat_bottom), hat_bottom);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip) + sizeof(hat_bottom), sizeof(hat_arm1), hat_arm1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip) + sizeof(hat_bottom) + sizeof(hat_arm1), sizeof(hat_arm2), hat_arm2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip) + sizeof(hat_bottom) + sizeof(hat_arm1)
		+ sizeof(hat_arm2), sizeof(hat_right_hand), hat_right_hand);

	glGenVertexArrays(1, &VAO_hat);
	glBindVertexArray(VAO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_hat() {
	glBindVertexArray(VAO_hat);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_LEAF]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_STRIP]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_ARM1]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_ARM2]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_RIGHT_HAND]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);

	glBindVertexArray(0);
}

// cake
#define CAKE_FIRE 0
#define CAKE_CANDLE 1
#define CAKE_BODY 2
#define CAKE_BOTTOM 3
#define CAKE_DECORATE 4

GLfloat cake_fire[4][2] = { { -2.5, 70.0 },{ -2.5, 65.0 },{ 2.5, 65.0 },{ 1.5, 70.0 } };
GLfloat cake_candle[4][2] = { { -5.0, 40.0 } ,{ -5.0, 65.0 },{ 5.0, 65.0 },{ 5.0, 40.0 } };
GLfloat cake_body[4][2] = { { 40.0, 25.0 },{ -40.0, 25.0 } ,{ -40.0, 40.0 },{ 40.0, 40.0 } };
GLfloat cake_bottom[4][2] = { { -50.0, 5.0 },{ -50.0, 25.0 },{ 50.0, 25.0 },{ 50.0, 5.0 } };
GLfloat cake_decorate[4][2] = { { -50.0, 0.0 },{ -50.0, 5.0 },{ 50.0, 1.0 },{ 50.0, 0.0 } };

GLfloat cake_color[5][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 204 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 102 / 255.0f, 51 / 255.0f, 0 / 255.0f }
};

GLuint VBO_cake, VAO_cake;

void prepare_cake() {
	int size = sizeof(cake_fire);
	GLsizeiptr buffer_size = sizeof(cake_fire) * 5;

	glGenBuffers(1, &VBO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, size, cake_fire);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, cake_candle);
	glBufferSubData(GL_ARRAY_BUFFER, size * 2, size, cake_body);
	glBufferSubData(GL_ARRAY_BUFFER, size * 3, size, cake_bottom);
	glBufferSubData(GL_ARRAY_BUFFER, size * 4, size, cake_decorate);

	glGenVertexArrays(1, &VAO_cake);
	glBindVertexArray(VAO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_cake() {
	glBindVertexArray(VAO_cake);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_FIRE]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_CANDLE]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_DECORATE]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glBindVertexArray(0);
}

// sword

#define SWORD_BODY 0
#define SWORD_BODY2 1
#define SWORD_HEAD 2
#define SWORD_HEAD2 3
#define SWORD_IN 4
#define SWORD_DOWN 5
#define SWORD_BODY_IN 6

GLfloat sword_body[4][2] = { { -30.0, 0.0 },{ -30.0, -20.0 },{ 30.0, -20.0 },{ 30.0, 0.0 } };
GLfloat sword_body2[4][2] = { { -10.0, -20.0 },{ -10.0, -30.0 } ,{ 10.0, -30.0 },{ 10.0, -20.0 } };
GLfloat sword_head[4][2] = { { -10.0, 0.0 },{ -10.0, 80.0 } ,{ 10.0, 80.0 },{ 10.0, 0.0 } };
GLfloat sword_head2[3][2] = { { -10.0, 80.0 },{ 0.0, 97.3 } ,{ 10.0, 80.0 } };
GLfloat sword_in[4][2] = { { -1.5, 3.5 },{ -1.5, 76.5 } ,{ 1.5, 76.5 },{ 1.5, 3.5 } };
GLfloat sword_down[4][2] = { { -10.0, -30.0 } ,{ 10.0, -30.0 },{ 20.0, -40.0 },{ -20.0, -40.0 } };
GLfloat sword_body_in[4][2] = { { 0.0, -5.0 } ,{ 5.0, -13.66 },{ 0.0, -22.32 },{ -5.0, -13.66 } };

GLfloat sword_color[7][3] = {
	{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f }
};

GLuint VBO_sword, VAO_sword;

void prepare_sword() {
	GLsizeiptr buffer_size = sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down) + sizeof(sword_body_in);

	glGenBuffers(1, &VBO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sword_body), sword_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body), sizeof(sword_body2), sword_body2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2), sizeof(sword_head), sword_head);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head), sizeof(sword_head2), sword_head2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2), sizeof(sword_in), sword_in);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in), sizeof(sword_down), sword_down);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down), sizeof(sword_body_in), sword_body_in);

	glGenVertexArrays(1, &VAO_sword);
	glBindVertexArray(VAO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_sword() {
	glBindVertexArray(VAO_sword);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY2]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 3);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_DOWN]);
	glDrawArrays(GL_TRIANGLE_FAN, 19, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 23, 4);

	glBindVertexArray(0);
}

// rabbit
#define RABBIT_LEFTEAR 0
#define RABBIT_RIGHTEAR 1
#define RABBIT_HEAD 2
#define RABBIT_BODY 3
#define RABBIT_LEFTLEG 4
#define RABBIT_RIGHTLEG 5
#define RABBIT_TAIL 6
#define RABBIT_LEFTEYE 7
#define RABBIT_RIGHTEYE 8
#define RABBIT_LEFTARM 9
#define RABBIT_RIGHTARM 10

GLfloat rabbit_leftear[6][2] = { { -7, 35 }, { -10, 40 }, { -13, 35 },{ -13, 25 },{ -8, 20 }, { -5, 25 } };
GLfloat rabbit_rightear[6][2] = { { 7, 35 }, { 10, 40 }, { 13, 35 },{ 13, 25 },{ 8, 20 }, { 5, 25 } };
GLfloat rabbit_head[6][2] = { { -10, 20 }, { 10, 20 }, { 17, 10 }, { 10, 0 }, { -10, 0 }, { -17, 10 } };
GLfloat rabbit_body[6][2] = { { -10, 0 },{ 10, 0 },{ 25, -15 },{ 10, -30 }, { -10, -30 }, { -25, -15 } };
GLfloat rabbit_leftleg[4][2] = { { -25, -30 },{ -5, -30 },{ -5, -35 },{ -25, -35 } };
GLfloat rabbit_rightleg[4][2] = { { 25, -30 },{ 5, -30 },{ 5, -35 },{ 25, -35 } };
GLfloat rabbit_tail[4][2] = { { 18.5, -18.5 },{ 24, -18.5 },{ 24, -24 },{ 18.5, -24 } };
GLfloat rabbit_lefteye[4][2] = { { 5, 16 },{ 5, 14 },{ 3.5, 14 },{ 3.5, 16 } };
GLfloat rabbit_righteye[4][2] = { { -5, 16 },{ -5, 14 },{ -3.5, 14 },{ -3.5, 16 } };
GLfloat rabbit_leftarm[4][2] = { { -10, -5 },{ -7, -5 },{ -7, -12 },{ -10, -12 } };
GLfloat rabbit_rightarm[4][2] = { { 10, -5 },{ 7, -5 },{ 7, -12 },{ 10, -12 } };

GLfloat rabbit_color[11][3] = {
	{ 240 / 255.0f, 128 / 255.0f, 128 / 255.0f },
{ 240 / 255.0f, 128 / 255.0f, 128 / 255.0f },
{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
{ 240 / 255.0f, 128 / 255.0f, 128 / 255.0f },
{ 240 / 255.0f, 128 / 255.0f, 128 / 255.0f },
{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },	
{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 240 / 255.0f, 128 / 255.0f, 128 / 255.0f },
{ 240 / 255.0f, 128 / 255.0f, 128 / 255.0f },
};

GLuint VBO_rabbit, VAO_rabbit;

void prepare_rabbit() {
	GLsizeiptr buffer_size = sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body) + sizeof(rabbit_leftleg) + sizeof(rabbit_rightleg) + sizeof(rabbit_tail)
		+ sizeof(rabbit_lefteye) + sizeof(rabbit_righteye) + sizeof(rabbit_leftarm) + sizeof(rabbit_rightarm);

	glGenBuffers(1, &VBO_rabbit);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_rabbit);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); 

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rabbit_leftear), rabbit_leftear);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear), sizeof(rabbit_rightear), rabbit_rightear);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear), sizeof(rabbit_head), rabbit_head);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head), sizeof(rabbit_body), rabbit_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body), sizeof(rabbit_leftleg), rabbit_leftleg);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body) + sizeof(rabbit_leftleg), sizeof(rabbit_rightleg), rabbit_rightleg);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body) + sizeof(rabbit_leftleg) + sizeof(rabbit_rightleg), sizeof(rabbit_tail), rabbit_tail);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body) + sizeof(rabbit_leftleg) + sizeof(rabbit_rightleg) + sizeof(rabbit_tail),
		sizeof(rabbit_lefteye), rabbit_lefteye);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body) + sizeof(rabbit_leftleg) + sizeof(rabbit_rightleg) + sizeof(rabbit_tail)
		+ sizeof(rabbit_lefteye), sizeof(rabbit_righteye), rabbit_righteye);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body) + sizeof(rabbit_leftleg) + sizeof(rabbit_rightleg) + sizeof(rabbit_tail)
		+ sizeof(rabbit_lefteye) + sizeof(rabbit_righteye), sizeof(rabbit_leftarm), rabbit_leftarm);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rabbit_leftear) + sizeof(rabbit_rightear) + sizeof(rabbit_head) + sizeof(rabbit_body) + sizeof(rabbit_leftleg) + sizeof(rabbit_rightleg) + sizeof(rabbit_tail)
		+ sizeof(rabbit_lefteye) + sizeof(rabbit_righteye) + sizeof(rabbit_leftarm), sizeof(rabbit_rightarm), rabbit_rightarm);

	glGenVertexArrays(1, &VAO_rabbit);
	glBindVertexArray(VAO_rabbit);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_rabbit);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_rabbit() {
	glBindVertexArray(VAO_rabbit);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_LEFTEAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_RIGHTEAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_HEAD]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 6);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 18, 6);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_LEFTLEG]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_RIGHTLEG]);
	glDrawArrays(GL_TRIANGLE_FAN, 28, 4);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_TAIL]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 4);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_LEFTEYE]);
	glDrawArrays(GL_TRIANGLE_FAN, 36, 4);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_RIGHTEYE]);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 4);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_LEFTARM]);
	glDrawArrays(GL_TRIANGLE_FAN, 44, 4);

	glUniform3fv(loc_primitive_color, 1, rabbit_color[RABBIT_RIGHTARM]);
	glDrawArrays(GL_TRIANGLE_FAN, 48, 4);

	glBindVertexArray(0);
}

// box
#define BOX1 0
#define BOX2 1
#define BOX3 2

GLfloat box1[4][2] = { { -110, 140 }, { 110, 140 }, { 110, 50 }, { -110, 50 } };
GLfloat box2[4][2] = { { -110, 50 }, { 110, 50 }, { 110, -45 }, { -110, -45 } };
GLfloat box3[4][2] = { { -110, -45 }, { 110, -45 }, { 110, -230 }, { -110, -230 } };

GLfloat box_color[3][3] = {
	{ 166 / 255.0f, 166 / 255.0f, 166 / 255.0f },
	{ 166 / 255.0f, 166 / 255.0f, 166 / 255.0f },
	{ 166 / 255.0f, 166 / 255.0f, 166 / 255.0f }
};

GLuint VBO_box, VAO_box;

void prepare_box() {
	GLsizeiptr buffer_size = sizeof(box1) + sizeof(box2) + sizeof(box3);

	glGenBuffers(1, &VBO_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); 

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(box1), box1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(box1), sizeof(box2), box2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(box1) + sizeof(box2), sizeof(box3), box3);

	glGenVertexArrays(1, &VAO_box);
	glBindVertexArray(VAO_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_box1() {
	glBindVertexArray(VAO_box);

	glUniform3fv(loc_primitive_color, 1, box_color[BOX1]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}
void draw_box2() {
	glBindVertexArray(VAO_box);

	glUniform3fv(loc_primitive_color, 1, box_color[BOX2]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glBindVertexArray(0);
}
void draw_box3() {
	glBindVertexArray(VAO_box);

	glUniform3fv(loc_primitive_color, 1, box_color[BOX3]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glBindVertexArray(0);
}