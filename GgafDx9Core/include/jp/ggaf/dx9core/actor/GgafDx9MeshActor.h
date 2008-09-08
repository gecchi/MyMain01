#ifndef GGAFDX9MESHACTORD_H_
#define GGAFDX9MESHACTORD_H_


class GgafDx9MeshActor : public GgafDx9UntransformedActor {
private:
	GgafDx9MeshModel* _pMeshModel;

public:
	GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9MeshActor();		//デストラクタ
};

#endif /*GGAFDX9MESHACTORD_H_*/
