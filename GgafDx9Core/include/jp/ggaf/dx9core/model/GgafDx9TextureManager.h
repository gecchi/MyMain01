#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9Texture 管理クラス .
 * 生成済み GgafDx9Texture オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9TextureManager {
protected:
	/** GgafDx9Textureオブジェクトのリストの先頭のポインタ。終端はNULL */
	static GgafDx9Texture* _pTexture_First;
	/**
	 * GgafDx9Textureオブジェクトをリストに追加。<BR>
	 * @param prm_pTexture_New 追加するGgafDx9Textureオブジェクトのポインタ
	 */
	static void add(GgafDx9Texture* prm_pTexture_New);

	/**
	 * GgafDx9Textureオブジェクトをリストから検索。<BR>
	 * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
	 * @return	所望のGgafDx9Textureオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	static GgafDx9Texture* find(std::string prm_texture_file_name);

public:

	/**
	 * GgafDx9Textureオブジェクトを取得。<BR>
	 * モデルオブジェクトは、初期化時、このメソッドを１回だけ呼び出してテクスチャを取得する。<BR>
	 * テクスチャは、保持リストに存在すればそれを返し、存在しなければ new します。<BR>
	 * テクスチャを保持リストから取得した場合、参照カウンタが増えます。（モデル初期時１回に限定するのはこのため）<BR>
	 * new した場合、参照カウンタは1です。<BR>
	 * 参照カウンタはモデルの delete 時にテクスチャを解放するかどうかの判断に使用される。<BR>
	 * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
	 */
	static GgafDx9Texture* obtain(std::string prm_texture_file_name);

	static void remove(GgafDx9Texture* prm_pTexture);

	/**
	 * GgafDx9Textureオブジェクトのリストをすべて delete を行う。<BR>
	 */
	static void release();

};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
