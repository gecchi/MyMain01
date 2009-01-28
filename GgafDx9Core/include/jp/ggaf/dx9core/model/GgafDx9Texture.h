#ifndef GGAFDX9TEXRURE_H_
#define GGAFDX9TEXRURE_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9Texture : public GgafCore::GgafResource<IDirect3DTexture9> {

public:

	/**
	 * コンストラクタ<BR>
	 * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
	 * @param prm_pIDirect3DTexture9 テクスチャ
	 */
	GgafDx9Texture(std::string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

	/**
	 * オーバーライド
	 */
	void releaseResourceProcess();

	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafDx9TextureManagerである<BR>
	 */
	virtual ~GgafDx9Texture();		//デストラクタ
};


}
#endif /*GGAFDX9TEXRURE_H_*/
