#ifndef XPBD_BALL
#define XPBD_BALL

#include "GL/glut.h"
#include "glm/glm.hpp"

class CBall{
	private:
		float     m_Frequency;
		glm::vec3 m_Position;
		float     m_Radius;

	public:
		explicit CBall(float radius);
		void Update(float dt);
		void Render();
		auto GetPosition() -> glm::vec3&;
		auto GetRadius() -> float;
};

#endif
