#ifndef DISPFPSACTOR
#define DISPFPSACTOR


class DispFpsActor : public FontPlateActor {
	char _aBuf[80];
	string _strFps;
public:
	DispFpsActor(string prm_name, string prm_model);

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();


	virtual ~DispFpsActor();
};


#endif /*DISPFPSACTOR*/

