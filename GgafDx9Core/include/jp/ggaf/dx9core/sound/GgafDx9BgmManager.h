#ifndef GGAFDX9BGMMANAGER_H_
#define GGAFDX9BGMMANAGER_H_

/**
 * GgafDx9Bgm 管理クラス .
 * 生成済み GgafDx9Bgm オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9BgmManager {

public:
	/** GgafDx9Bgmオブジェクトのリストの先頭のポインタ。終端はNULL */
	static GgafDx9Bgm* _pBgm_First;
	/**
	 * GgafDx9Bgmオブジェクトをリストに追加。<BR>
	 * @param prm_pBgm_New 追加するGgafDx9Bgmオブジェクトのポインタ
	 */
	static void add(GgafDx9Bgm* prm_pBgm_New);

	/**
	 * GgafDx9Bgmオブジェクトをリストから検索。<BR>
	 * @param prm_ogg_name ogg定義の識別名。".ogg"を追加するとファイル名になる。
	 * @return	所望のGgafDx9Bgmオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	static GgafDx9Bgm* find(string prm_ogg_name);

	/**
	 * GgafDx9Bgmオブジェクトを取得。<BR>
	 * GgafDx9Bgm オブジェクトリスト（先頭は_pBgm_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9Bgmがある）場合、 GgafDx9Bgm にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * @param prm_ogg_name ogg定義の識別名。".ogg"を追加するとファイル名になる。
	 */
	static GgafDx9Bgm* get(string prm_ogg_name);


	/**
	 * GgafDx9Bgmオブジェクトのリストをすべて delete を行う。<BR>
	 */
	static void clear();

};

#endif /*GGAFDX9BGMMANAGER_H_*/
