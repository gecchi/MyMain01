#ifndef DEFAULTMESHACTOR_H_
#define DEFAULTMESHACTOR_H_
namespace GgafDx9LibStg {


class DefaultMeshActor : public GgafDx9Core::GgafDx9MeshActor {

public:
	DWORD _dwFrameOffset;

	StgChecker* _pChecker;

	DefaultMeshActor(string prm_name, string prm_model);


	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		GgafDx9Core::GgafDx9MeshActor::processDrawPrior();
	};

	virtual void processDrawMain() {
		GgafDx9Core::GgafDx9MeshActor::processDrawMain();
	};

	virtual void processDrawTerminate();

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultMeshActor();
};


}
#endif /*DEFAULTMESHACTOR_H_*/
