#ifndef GGAFDX9DYNAMESHACTOR_H_
#define GGAFDX9DYNAMESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9UntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * GgafDx9MeshActor との違いは、頂点バッファに直接アクセスをことに考慮して、<BR>
 * D3DXMESH_DYNAMIC オプションを使用しているところだけです。<BR>
 * 頂点をロックする場合はGgafDx9MeshActorではなく、こちらを継承してください。<BR>
 */
class GgafDx9DynaMeshActor : public GgafDx9UntransformedActor {
private:

public:
	/** モデルオブジェクトへのポインタ */
	GgafDx9MeshModel* _pMeshModel;
	/** キャラ全体のα */
	float _fAlpha;


	GgafDx9DynaMeshActor(std::string prm_name, std::string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

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


}
#endif /*GGAFDX9DYNAMESHACTOR_H_*/
