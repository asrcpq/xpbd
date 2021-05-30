#ifndef XPBD_APPLICATION
#define XPBD_APPLICATION

#include "emode.h"

class CApplication{
	private:
		float m_Time{0.0F};
		int m_SolveTime{0};
	public:
		int m_IterationNum{20};
		int m_Mode{eModePBD};
		int m_OldMode{eModeMax};

		auto GetTime() -> float;
		void SetTime(float time);
		auto GetSolveTime() -> int;
		void SetSolveTime(float time);
};

#endif
