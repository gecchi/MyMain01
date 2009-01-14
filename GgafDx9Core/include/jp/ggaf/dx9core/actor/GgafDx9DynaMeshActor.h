#ifndef GGAFDX9DYNAMESHACTOR_H_
#define GGAFDX9DYNAMESHACTOR_H_


class GgafDx9DynaMeshActor : virtual public GgafDx9UntransformedActor {
private:

public:
	/** モデルオブジェクトへのポインタ */
	GgafDx9MeshModel* _pMeshModel;


	GgafDx9DynaMeshActor(int prm_type, string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	void setAlpha(float prm_fAlpha) {
		_fAlpha = prm_fAlpha;
	}

	float getAlpha() {
		return _fAlpha;
	}

	virtual ~GgafDx9DynaMeshActor();		//デストラクタ
};

#endif /*GGAFDX9DYNAMESHACTOR_H_*/
