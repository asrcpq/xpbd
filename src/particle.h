#pragma once

#include <GL/glut.h>
#include <glm/glm.hpp>

class CParticle{
	private:
		GLfloat   m_InvMass;
		glm::vec3 m_Position;
		glm::vec3 m_OldPosition;
		glm::vec3 m_Acceleration;

	public:
		CParticle(GLfloat inv_mass, glm::vec3& position, glm::vec3& acceleration) :
			m_InvMass(inv_mass),
			m_Position(position),
			m_OldPosition(position),
			m_Acceleration(acceleration){}
		CParticle(){};
		~CParticle(){}

		void Update(float t);
		glm::vec3& GetPosition();
		GLfloat&   GetInvMass();
		void AddPosition(const glm::vec3& pos, bool is_force = true);
};
