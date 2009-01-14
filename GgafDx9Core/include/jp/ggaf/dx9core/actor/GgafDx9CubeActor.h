#ifndef GGAFDX9CUBEACTORD_H_
#define GGAFDX9CUBEACTORD_H_


class GgafDx9CubeActor : virtual public GgafDx9UntransformedActor {
private:

public:

	/** モデルオブジェクトへのポインタ */
	GgafDx9MeshModel* _pMeshModel;


	GgafDx9CubeActor(int prm_type, string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

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

	virtual ~GgafDx9CubeActor();		//デストラクタ
};

#endif /*GGAFDX9CUBEACTORD_H_*/
