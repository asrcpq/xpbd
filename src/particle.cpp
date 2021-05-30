#include <GL/glut.h>
#include <glm/glm.hpp>

#include "particle.h"

void CParticle::Update(float t){
	if (m_InvMass > 0.0f){
		glm::vec3 tmp = m_Position;
		m_Position += (m_Position - m_OldPosition) + m_Acceleration * t * t;
		m_OldPosition = tmp;
	}
}

glm::vec3& CParticle::GetPosition()  { return m_Position; }

GLfloat& CParticle::GetInvMass()   { return m_InvMass;  }

void CParticle::AddPosition(const glm::vec3& pos, bool is_force) {
	if ((m_InvMass > 0.0f) || (is_force)) {
		m_Position += pos;
	}
}
