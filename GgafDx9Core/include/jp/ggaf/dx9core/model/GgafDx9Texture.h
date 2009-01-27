#ifndef GGAFDX9TEXRURE_H_
#define GGAFDX9TEXRURE_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9Texture : public GgafCore::GgafObject {

public:
	/** 参照しているモデルオブジェクト数 */
	int _iRefModelNum;

	/** テクスチャ識別名(＝ファイル名) */
	std::string			_texture_file_name;
	/** テクスチャ */
	LPDIRECT3DTEXTURE9 _pIDirect3DTexture9;
	/** 次のGgafDx9Textureへのポインタ。終端はNULL */
	GgafDx9Texture*	_pTexture_Next;

	/** 前回描画Texture定義名 */
	static std::string _id_lastdraw;

	/**
	 * コンストラクタ<BR>
	 * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
	 * @param prm_pIDirect3DTexture9 テクスチャ
	 */
	GgafDx9Texture(std::string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

	/**
	 *
	 */
	void release();

	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafDx9TextureManagerである<BR>
	 */
	virtual ~GgafDx9Texture();		//デストラクタ
};


}
#endif /*GGAFDX9TEXRURE_H_*/
