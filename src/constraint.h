#ifndef XPBD_CONSTRAINT
#define XPBD_CONSTRAINT

#include "GL/glut.h"
#include "glm/glm.hpp"

#include "particle.h"
#include "application.h"

class CConstraint{
	private:
		GLfloat    m_RestLength;
		CParticle* m_Particle1;
		CParticle* m_Particle2;
		GLfloat    m_Stiffness;   // for  PBD(0.0f-1.0f)
		GLfloat    m_Compliance;  // for XPBD
		GLfloat    m_Lambda;      // for XPBD
	public:
		void LambdaInit();
		CConstraint(CParticle* p0, CParticle* p1);
		void Solve(CApplication& app, float dt);
};

#endif
