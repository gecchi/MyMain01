#ifndef DEFAULTPLATEACTOR_H_
#define DEFAULTPLATEACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9PlateActor �������������ۃA�N�^�[�ł��B
 */
class DefaultPlateActor : public GgafDx9Core::GgafDx9PlateActor {

public:
	DefaultPlateActor(std::string prm_name, std::string prm_model);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {};

	virtual void processDrawMain() {
		GgafDx9Core::GgafDx9PlateActor::processDrawMain();
	};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
		return false;
	};

	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultPlateActor();

};


}
#endif /*DEFAULTPLATEACTOR_H_*/
