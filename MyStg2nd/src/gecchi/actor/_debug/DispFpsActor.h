#ifndef DISPFPSACTOR_H_
#define DISPFPSACTOR_H_
namespace MyStg2nd {


class DispFpsActor : public GgafDx9LibStg::FontPlateActor {
	char _aBuf[80];
	std::string _strFps;
public:
	DispFpsActor(const char* prm_name, const char* prm_model);

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


}
#endif /*DISPFPSACTOR_H_*/

