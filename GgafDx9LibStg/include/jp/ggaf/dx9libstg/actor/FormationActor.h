#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_
namespace GgafDx9LibStg {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
class FormationActor : public GgafDx9Core::GgafDx9UntransformedActor {

public:

	FormationActor(std::string prm_name);

	virtual void initialize() {};

	virtual void processBehavior() {};

 	/**
 	 * �T�u��������Ύ�
	 * ��OverRide �ł���<BR>
	 */
	virtual void processJudgement() {
		if (getSubFirst() == NULL) {
			farewell();
		}
	};

	virtual void processDrawPrior() {};

	virtual void processDrawMain() {};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};

	virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
