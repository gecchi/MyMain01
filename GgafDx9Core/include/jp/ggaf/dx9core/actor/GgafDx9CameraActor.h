#ifndef GGAFDX9CAMERAACTOR_H_
#define GGAFDX9CAMERAACTOR_H_
namespace GgafDx9Core {


class GgafDx9CameraActor : public GgafDx9UntransformedActor {
private:

public:

	int _gazeX, _gazeY, _gazeZ;


	GgafDx9CameraActor(string prm_name);

	virtual void initialize();

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	/**
	 * カメラの更新
	 */
	virtual void processDrawPrior();

	virtual void processDrawMain() {};

	virtual void processDrawTerminate() {};

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};

	void setGaze(int prm_tX, int prm_tY, int prm_tZ) {
		_gazeX = prm_tX;
		_gazeY = prm_tY;
		_gazeZ = prm_tZ;
	}

	void setGaze(GgafDx9UntransformedActor* prm_pActor) {
		_gazeX = prm_pActor->_X;
		_gazeY = prm_pActor->_Y;
		_gazeZ = prm_pActor->_Z;
	}


	virtual ~GgafDx9CameraActor();		//デストラクタ
};


}
#endif /*GGAFDX9CAMERAACTOR_H_*/
