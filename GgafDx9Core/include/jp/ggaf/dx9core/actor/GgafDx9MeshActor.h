#ifndef GGAFDX9MESHACTOR_H_
#define GGAFDX9MESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9UntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9MeshActor : public GgafDx9UntransformedActor {
private:

public:
	/** モデルオブジェクトへのポインタ */
	GgafDx9MeshModel* _pMeshModel;
	/** キャラ全体のα */
	float _fAlpha;


	GgafDx9MeshActor(std::string prm_name, std::string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

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

	virtual ~GgafDx9MeshActor();		//デストラクタ
};


}
#endif /*GGAFDX9MESHACTOR_H_*/
