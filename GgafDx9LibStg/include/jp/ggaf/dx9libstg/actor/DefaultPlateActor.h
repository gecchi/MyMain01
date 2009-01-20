#ifndef DEFAULTPLATEACTOR_H_
#define DEFAULTPLATEACTOR_H_
namespace GgafDx9LibStg {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx9Core::GgafDx9PlateActor を空実装した具象アクターです。
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
