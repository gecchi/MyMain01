#ifndef GGAFDX9MESHACTORD_H_
#define GGAFDX9MESHACTORD_H_


class GgafDx9MeshActor : public GgafDx9UntransformedActor {
private:
	GgafDx9MeshModel* _pMeshModel;

public:
	GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * _Zの値により、大まかにレンダリング順序を設定する。
	 * 任意の優先順位でレンダリングしたい場合は、このメソッドをオーバーライドし
	 * GgafWorld::_apActorDrawOrder[n] の好きな n に addSubLast(this) を行って下さい。
	 * 但し 0 ≦ n ＜ MAX_DEPTH_LEVEL
	 */
	virtual void processDrawPrior();

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9MeshActor();		//デストラクタ
};

#endif /*GGAFDX9MESHACTORD_H_*/
