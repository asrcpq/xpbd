#include "emode.h"

const char* MODE_STRING[eModeMax] = {
	"PBD",
	"XPBD(Concrete)",
	"XPBD(Wood)",
	"XPBD(Leather)",
	"XPBD(Tendon)",
	"XPBD(Rubber)",
	"XPBD(Muscle)",
	"XPBD(Fat)",
};

const float MODE_COMPLIANCE[eModeMax] = {
	0.0F,            // Miles Macklin's blog (http://blog.mmacklin.com/2016/10/12/xpbd-slides-and-stiffness/)
	0.00000000004F, // 0.04 x 10^(-9) (M^2/N) Concrete
	0.00000000016F, // 0.16 x 10^(-9) (M^2/N) Wood
	0.000000001F,   // 1.0  x 10^(-8) (M^2/N) Leather
	0.000000002F,   // 0.2  x 10^(-7) (M^2/N) Tendon
	0.0000001F,     // 1.0  x 10^(-6) (M^2/N) Rubber
	0.00002F,       // 0.2  x 10^(-3) (M^2/N) Muscle
	0.0001F,        // 1.0  x 10^(-3) (M^2/N) Fat
};
