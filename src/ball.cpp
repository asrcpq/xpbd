#include <GL/glut.h>
#include <glm/glm.hpp>
#include "ball.h"

CBall::CBall(float radius) :
	m_Frequency(3.14f * 0.4f),
	m_Position(0.0f,0.0f,0.0f),
	m_Radius(radius){}

void CBall::Update(float dt){
	m_Position.z = cos(m_Frequency) * 2.0f;
	m_Frequency += dt / 5.0f;
	if (m_Frequency > 3.14f * 2.0f){ m_Frequency -= 3.14f * 2.0f; }
}

void CBall::Render(){
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	static const glm::vec3 color(0.0f, 0.0f, 1.0f);
	glColor3fv((GLfloat*)&color);
	glutSolidSphere(m_Radius, 30, 30);
}

glm::vec3& CBall::GetPosition(){ return m_Position; }
float CBall::GetRadius()  { return m_Radius; }
