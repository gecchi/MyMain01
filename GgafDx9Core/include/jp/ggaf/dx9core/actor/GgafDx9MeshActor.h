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
	/** モデル */
	GgafDx9ModelLead* _pModelLead;
	GgafDx9MeshModel* _pMeshModel;

	GgafDx9MeshActor(std::string prm_name, std::string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	/**
	 * α設定.
	 * ＜オーバーライト＞
	 * @param prm_fAlpha
	 */
	void setAlpha(float prm_fAlpha);

	virtual ~GgafDx9MeshActor();		//デストラクタ
};


}
#endif /*GGAFDX9MESHACTOR_H_*/
