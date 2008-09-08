#ifndef DISPFPSACTOR
#define DISPFPSACTOR


class DispFpsActor : public FontPlateActor {
	char _aBuf[80];
	string _strFps;
public:
	DispFpsActor(string prm_name, string prm_xname);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processBehavior();


	virtual ~DispFpsActor();
};


#endif /*DISPFPSACTOR*/

