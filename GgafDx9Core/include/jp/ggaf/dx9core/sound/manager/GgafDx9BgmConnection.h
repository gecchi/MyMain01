#ifndef GGAFDX9BGMCONNECTION_H_
#define GGAFDX9BGMCONNECTION_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9BgmConnection : public GgafCore::GgafResourceConnection<GgafDx9Bgm> {

public:

	/**
	 * コンストラクタ<BR>
	 * @param prm_texture_file_name OGG識別名(＝ファイル名)
	 * @param prm_pGgafDx9Bgm OGG
	 */
	GgafDx9BgmConnection(char* prm_idstr, GgafDx9Bgm* prm_pGgafDx9Bgm);

	/**
	 * オーバーライド
	 */
	void processReleaseResource(GgafDx9Bgm* prm_pResource);

	/**
	 * デストラクタ<BR>
	 */
	virtual ~GgafDx9BgmConnection() {
	};
};


}
#endif /*GGAFDX9BGMCONNECTION_H_*/
