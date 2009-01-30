#ifndef GGAFDX9TEXTURECONNECTION_H_
#define GGAFDX9TEXTURECONNECTION_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9TextureConnection : public GgafCore::GgafResourceConnection<IDirect3DTexture9> {

public:

	/**
	 * コンストラクタ<BR>
	 * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
	 * @param prm_pIDirect3DTexture9 テクスチャ
	 */
	GgafDx9TextureConnection(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

	/**
	 * オーバーライド
	 */
	void processReleaseResource(IDirect3DTexture9* prm_pResource);

	/**
	 * デストラクタ<BR>
	 */
	virtual ~GgafDx9TextureConnection() {
	};
};


}
#endif /*GGAFDX9TEXTURECONNECTION_H_*/
