#ifndef GGAFDX9MODELLEAD_H_
#define GGAFDX9MODELLEAD_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9ModelLead : public GgafCore::GgafResourceLead<GgafDx9Model> {

public:

	/**
	 * コンストラクタ<BR>
	 * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
	 * @param prm_pIDirect3DModel9 テクスチャ
	 */
	GgafDx9ModelLead(char* prm_idstr, GgafDx9Model* prm_pIDirect3DModel9);

	/**
	 * オーバーライド
	 */
	void processReleaseResource(GgafDx9Model* prm_pResource);

	/**
	 * デストラクタ<BR>
	 */
	virtual ~GgafDx9ModelLead() {
	};
};


}
#endif /*GGAFDX9MODELLEAD_H_*/
