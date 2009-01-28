#ifndef GGAFDX9TEXTUREPOINTER_H_
#define GGAFDX9TEXTUREPOINTER_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9TexturePointer : public GgafCore::GgafResourcePointer<IDirect3DTexture9> {

public:

	/**
	 * コンストラクタ<BR>
	 * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
	 * @param prm_pIDirect3DTexture9 テクスチャ
	 */
	GgafDx9TexturePointer(std::string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);


	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafDx9TexturePointerManagerである<BR>
	 */
	virtual ~GgafDx9TexturePointer();		//デストラクタ
};


}
#endif /*GGAFDX9TEXTUREPOINTER_H_*/
