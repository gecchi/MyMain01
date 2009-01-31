#ifndef GGAFDX9SECONNECTION_H_
#define GGAFDX9SECONNECTION_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9SeLead : public GgafCore::GgafResourceLead<GgafDx9Se> {

public:

	/**
	 * コンストラクタ<BR>
	 * @param prm_texture_file_name OGG識別名(＝ファイル名)
	 * @param prm_pGgafDx9Se OGG
	 */
	GgafDx9SeLead(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se);

	/**
	 * オーバーライド
	 */
	void processReleaseResource(GgafDx9Se* prm_pResource);

	/**
	 * デストラクタ<BR>
	 */
	virtual ~GgafDx9SeLead() {
	};
};


}
#endif /*GGAFDX9SECONNECTION_H_*/
