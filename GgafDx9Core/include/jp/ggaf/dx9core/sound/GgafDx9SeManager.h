#ifndef GGAFDX9SEMANAGER_H_
#define GGAFDX9SEMANAGER_H_

class GgafDx9SeManager {

public:
	/** GgafDx9Seオブジェクトのリストの先頭のポインタ。終端はNULL */
	static GgafDx9Se* _pSe_First;
	/**
	 * GgafDx9Seオブジェクトをリストに追加。<BR>
	 * @param 追加するGgafDx9Seオブジェクトのポインタ
	 */
	static void add(GgafDx9Se* prm_pSe_New);

	/**
	 * GgafDx9Seオブジェクトをリストから検索。<BR>
	 * @param wav定義の識別名。".wav"を追加するとファイル名になる。
	 * @return	所望のGgafDx9Seオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	static GgafDx9Se* find(string prm_wave_name);

	/**
	 * GgafDx9Seオブジェクトを取得。<BR>
	 * GgafDx9Se オブジェクトリスト（先頭は_pSe_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9Seがある）場合、 GgafDx9Se にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * @param wav定義の識別名。".wav"を追加するとファイル名になる。
	 */
	static GgafDx9Se* get(string prm_wave_name);


	/**
	 * GgafDx9Seオブジェクトのリストをすべて delete を行う。<BR>
	 */
	static void clear();

};

#endif /*GGAFDX9SEMANAGER_H_*/
