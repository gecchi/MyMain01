#ifndef DELINEATEACTOR_H_
#define DELINEATEACTOR_H_
namespace GgafDx9LibStg {

/**
 * �����蔻��\���p�L���[�u�N���X
 * DefaultCubeActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 */
class DelineateActor : public DefaultCubeActor {
	static DelineateActor* _s_pObj;
public:
	static DelineateActor* get();
	static void release();

	DelineateActor(const char* prm_name);

	//void processDrawMain() {}; //�I�[�o�[���C�h�������ɂ���B



	void drawHitarea(StgChecker* prm_pChecker);

	virtual ~DelineateActor();

};


}
#endif /*DELINEATEACTOR_H_*/
