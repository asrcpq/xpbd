#include "constraint.h"

void CConstraint::LambdaInit() {
	m_Lambda = 0.0F; // reset every time frame
}

CConstraint::CConstraint(CParticle* p0, CParticle* p1) :
	m_RestLength(0.0F),
	m_Particle1(p0),
	m_Particle2(p1),
	m_Stiffness(0.1F),
	m_Compliance(0.0F),
	m_Lambda(0.0F) {
	glm::vec3 p0_to_p1 = m_Particle2->GetPosition() - m_Particle1->GetPosition();
	m_RestLength = glm::length(p0_to_p1);
}

void CConstraint::Solve(CApplication& app, float dt){
	GLfloat   inv_mass1         = m_Particle1->GetInvMass();
	GLfloat   inv_mass2         = m_Particle2->GetInvMass();
	GLfloat   sum_mass          = inv_mass1 + inv_mass2;
	if (sum_mass == 0.0F) { return; }
	glm::vec3 p1_minus_p2       = m_Particle1->GetPosition() - m_Particle2->GetPosition();
	GLfloat   distance          = glm::length(p1_minus_p2);
	GLfloat   constraint        = distance - m_RestLength; // Cj(x)
	glm::vec3 correction_vector;
	if (app.m_Mode != eModePBD) { // XPBD
		m_Compliance = MODE_COMPLIANCE[app.m_Mode];
		m_Compliance /= dt * dt;    // a~
		GLfloat dlambda           = (-constraint - m_Compliance * m_Lambda) / (sum_mass + m_Compliance); // eq.18
		correction_vector = dlambda * p1_minus_p2 / (distance + FLT_EPSILON);                    // eq.17
		m_Lambda += dlambda;
	} else {                      // normal PBD
		correction_vector = m_Stiffness * glm::normalize(p1_minus_p2) * -constraint/ sum_mass;   // eq. 1
	}
	m_Particle1->AddPosition(+inv_mass1 * correction_vector);
	m_Particle2->AddPosition(-inv_mass2 * correction_vector);
}
