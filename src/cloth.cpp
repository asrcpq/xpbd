#include "application.h"
#include "ball.h"
#include "constraint.h"
#include "particle.h"

#include "GL/glut.h"
#include "glm/glm.hpp"

#include <vector>

class CCloth{
	private:
		int m_Width;
		int m_Height;
		std::vector<CParticle> m_Particles;
		std::vector<CConstraint> m_Constraints;

		auto GetParticle(int w, int h) -> CParticle* {
			return &m_Particles[h * m_Width + w];
		}

		void MakeConstraint(CParticle* p1, CParticle* p2) {
			m_Constraints.push_back(CConstraint(p1, p2));
		}

		void draw_triangle(CParticle* p1, CParticle* p2, CParticle* p3, const glm::vec3 color){
			glColor3fv((GLfloat*)&color);
			glVertex3fv((GLfloat*)&(p1->GetPosition()));
			glVertex3fv((GLfloat*)&(p2->GetPosition()));
			glVertex3fv((GLfloat*)&(p3->GetPosition()));
		}

		void draw_frame(CParticle* p1, CParticle* p2, CParticle* p3, const glm::vec3 color){
			glColor3fv((GLfloat*)&color);
			glVertex3fv((GLfloat*)&(p1->GetPosition()));
			glVertex3fv((GLfloat*)&(p2->GetPosition()));
			glVertex3fv((GLfloat*)&(p3->GetPosition()));
			glVertex3fv((GLfloat*)&(p1->GetPosition()));
		}

	public:
		CCloth(float width, float height, int num_width, int num_height):
			m_Width(num_width),
			m_Height(num_height) {
				m_Particles.resize(m_Width * m_Height);
				for(int w = 0; w < m_Width; w++){
					for(int h = 0; h < m_Height; h++){
						glm::vec3 pos( width  * ((float)w/(float)m_Width ) - width  * 0.5f,
								-height * ((float)h/(float)m_Height) + height * 0.5f,
								0.0f );
						glm::vec3 gravity( 0.0f, -9.8f, 0.0f );
						GLfloat inv_mass = 0.1f;
						if ((h == 0 && w == 0) || (h == 0 && w == m_Width - 1)) {
							inv_mass = 0.0f; //fix only edge point
						}
						m_Particles[h * m_Width + w] = CParticle(inv_mass, pos, gravity);
					}
				}
				for(int w = 0; w < m_Width; w++){
					for(int h = 0; h < m_Height; h++){           // structual constraint
						if (w < m_Width - 1) {
							MakeConstraint(GetParticle(w, h), GetParticle(w+1, h));
						}
						if (h < m_Height - 1) {
							MakeConstraint(GetParticle(w, h), GetParticle(w, h+1));
						}
						if (w < m_Width - 1 && h < m_Height - 1){ // shear constraint
							MakeConstraint(GetParticle(w,   h), GetParticle(w+1, h+1));
							MakeConstraint(GetParticle(w+1, h), GetParticle(w,   h+1));
						}
					}
				}
				for(int w = 0; w < m_Width; w++){
					for(int h = 0; h < m_Height; h++){           // bend constraint
						if (w < m_Width - 2) {
							MakeConstraint(GetParticle(w, h), GetParticle(w + 2, h));
						}
						if (h < m_Height - 2){ MakeConstraint(GetParticle(w, h), GetParticle(w, h + 2)); }
						if (w < m_Width - 2 && h < m_Height - 2){
							MakeConstraint(GetParticle(w, h), GetParticle(w + 2, h + 2));
							MakeConstraint(GetParticle(w + 2, h), GetParticle(w, h+2));
						}
					}
				}
			}
		~CCloth(){}

		void Render(){
			int col_idx = 0;
			// glBegin(GL_TRIANGLES);
			for(int w = 0; w < m_Width - 1; w++){
				for(int h = 0; h < m_Height - 1; h++){
					glm::vec3 col(1.0f, 0.6f, 0.6f);
					if ( col_idx++ % 2 ){ col = glm::vec3(1.0f, 1.0f, 1.0f);}
					glBegin(GL_LINES);
					draw_frame(
						GetParticle(w + 1, h),
						GetParticle(w, h),
						GetParticle(w, h + 1),
						col
					);
					glEnd();
					glBegin(GL_LINES);
					draw_frame(
						GetParticle(w + 1, h + 1),
						GetParticle(w + 1, h),
						GetParticle(w, h + 1),
						col
					);
					glEnd();
				}
			}
			// glEnd();
		}

		void Update(CApplication& app, float dt, CBall* ball, int iteraion){
			std::vector<CParticle>::iterator particle;
			for(particle = m_Particles.begin(); particle != m_Particles.end(); particle++){
				(*particle).Update(dt); // predict position
			}
			unsigned int  solve_time_ms = 0;
			std::vector<CConstraint>::iterator constraint;
			for(constraint = m_Constraints.begin(); constraint != m_Constraints.end(); constraint++){
				(*constraint).LambdaInit();
			}
			for(int i = 0; i < iteraion; i++){
				for(particle = m_Particles.begin(); particle != m_Particles.end(); particle++){
					glm::vec3 vec    = (*particle).GetPosition() - ball->GetPosition();
					float     length = glm::length(vec);
					float     radius = ball->GetRadius() * 1.8f; // fake radius
					if (length < radius) {
						(*particle).AddPosition(glm::normalize(vec) * (radius - length));
					}
				}
				unsigned int before = glutGet(GLUT_ELAPSED_TIME);
				for(constraint = m_Constraints.begin(); constraint != m_Constraints.end(); constraint++){
					(*constraint).Solve(app, dt);
				}
				solve_time_ms += glutGet(GLUT_ELAPSED_TIME) - before;
			}
			app.SetSolveTime(solve_time_ms);
		}
};
