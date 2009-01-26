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
	static LPDIRECT3DTEXTURE9 _pTexture_First;
	/**
	 * GgafDx9Textureオブジェクトをリストに追加。<BR>
	 * @param prm_pTexture_New 追加するGgafDx9Textureオブジェクトのポインタ
	 */
	static void add(LPDIRECT3DTEXTURE9 prm_pTexture_New);

	/**
	 * GgafDx9Textureオブジェクトをリストから検索。<BR>
	 * @param prm_ogg_name ogg定義の識別名。".ogg"を追加するとファイル名になる。
	 * @return	所望のGgafDx9Textureオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	static LPDIRECT3DTEXTURE9 find(std::string prm_ogg_name);

public:

	/**
	 * GgafDx9Textureオブジェクトを取得。<BR>
	 * GgafDx9Texture オブジェクトリスト（先頭は_pTexture_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9Textureがある）場合、 GgafDx9Texture にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
	 * @param prm_ogg_name ogg定義の識別名。".ogg"を追加するとファイル名になる。
	 */
	static LPDIRECT3DTEXTURE9 get(std::string prm_ogg_name);


	/**
	 * GgafDx9Textureオブジェクトのリストをすべて delete を行う。<BR>
	 */
	static void clear();

};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
