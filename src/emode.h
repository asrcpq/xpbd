#ifndef XPBD_EMODE
#define XPBD_EMODE

enum eMode {
	eModePBD,
	eModeXPBD_Concrete,
	eModeXPBD_Wood,
	eModeXPBD_Leather,
	eModeXPBD_Tendon,
	eModeXPBD_Rubber,
	eModeXPBD_Muscle,
	eModeXPBD_Fat,
	eModeMax,
};

extern const char* MODE_STRING[eModeMax];

extern const float MODE_COMPLIANCE[eModeMax];

#endif
