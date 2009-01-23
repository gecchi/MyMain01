#ifndef GGAFDX9SEMANAGER_H_
#define GGAFDX9SEMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9Se 管理クラス .
 * 生成済み GgafDx9Se オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9SeManager {
protected:
	/** GgafDx9Seオブジェクトのリストの先頭のポインタ。終端はNULL */
	static GgafDx9Se* _pSe_First;

	/**
	 * GgafDx9Seオブジェクトをリストに追加。<BR>
	 * @param prm_pSe_New 追加するGgafDx9Seオブジェクトのポインタ
	 */
	static void add(GgafDx9Se* prm_pSe_New);

	/**
	 * GgafDx9Seオブジェクトをリストから検索。<BR>
	 * @param prm_wave_name wav定義の識別名。".wav"を追加するとファイル名になる。
	 * @return	所望のGgafDx9Seオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	static GgafDx9Se* find(std::string prm_wave_name);
public:

	/**
	 * GgafDx9Seオブジェクトを取得。<BR>
	 * GgafDx9Se オブジェクトリスト（先頭は_pSe_First）<BR>
	 * から検索し、ヒットした（生成済みGgafDx9Seがある）場合、 GgafDx9Se にキャストしてそれを返す。<BR>
	 * ヒットしない場合は create を行いインスタンス生成後リストに追加しそれを返す。<BR>
	 * 内部で std::string の比較を見つかるまで行うため、重いです。<BR>
	 * 毎フレーム実行されるような使用は避けるべきです。<BR>
	 * 初期化関数等で１回使用し、ポインタを保持するという使用方法を想定。<BR>
	 * @param  prm_wave_name wave定義の識別名。".wav"を追加するとファイル名になる。
	 */
	static GgafDx9Se* get(std::string prm_wave_name);


	/**
	 * GgafDx9Seオブジェクトのリストをすべて delete を行う。<BR>
	 */
	static void clear();

};


}
#endif /*GGAFDX9SEMANAGER_H_*/
