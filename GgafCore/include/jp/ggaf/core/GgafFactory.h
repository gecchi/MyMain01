#ifndef GGAFGACTORY_H_
#define GGAFGACTORY_H_
namespace GgafCore {


/**
 * インスタンス生成工場クラス .
 * メイン処理から、注文(GgafOrder)を渡されると、別スレッドにそのインスタンスを生成(new)させます。<BR>
 * 出来上がったインスタンス(商品と呼ぶ)のポインタ達は工場でストックされ、メイン処理から必要に応じて商品を取り出すことが出来ます<BR>
 * 【補足】<BR>
 * ステージとステージの間や、ボス前等、大量インスタンスを生成しなければいけない個所で、滑らかに処理したかった。<BR>
 * つまり、昔よくあった「ウッ」と止まるのを無くしたかったため生まれた(ﾅﾝﾉｺｯﾁｬ)<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafFactory {
	friend class GgafGod;

private:
	static GgafGod* _pGod;


	/** 先頭の注文 */
	static GgafOrder* ROOT_ORDER;
	/** 現在製造中の注文 */
	static GgafOrder* CREATING_ORDER;
	//全て製造済みの場合、最終注文を指しつづける
	//全て製造済みかつ、製品が全て取得されてしまった場合は NULL になる。
	//_isLastOrder == false を常に判定し、最終注文でなくなったら（新規注文があれば）、
	//製造を行って次に進める。 _isLastOrder == false になるまで製造しつづける


	/**
	 * 工場に注文を行う<BR>
	 * @param   prm_id	注文識別ID
	 * 			prm_pFunc	実際に製造処理を行う関数のポインタ<BR>
	 * 			prm_pArg	その引数<BR>
	 */
	static void order(std::string prm_id, GgafObject* (*prm_pFunc)(void*, void*), void* prm_pArg1, void* prm_pArg2);

	/**
	 * 注文した商品を取り出す。<BR>
	 * 未製造だった場合、製造が完了するまで待つ。<BR>
	 * @param   prm_id	注文識別ID
	 * @return	製品のポインタ
	 */
	static void* obtain(std::string prm_id);

public:
	/** ゴミ箱(不要なアクター置き場) */
	static GgafGarbageBox* _pGarbageBox;

	/** 掃除オブジェクト数 */
	static int _s_iCountCleanedNode;


	/** 活動フラグ(神が操作する) */
	static bool _isWorking;

	/** 完全店終い */
	static bool _isFinish;

	/**
	 * 工場にアクター作成の注文を行う<BR>
	 * @param   prm_id	注文識別ID
	 * 			prm_pFunc	実際に製造処理を行う関数のポインタ<BR>
	 * 			prm_pArg	その引数<BR>
	 */
	template <class X>
	static void orderActor(std::string prm_id, X* (*prm_pFunc)(void*, void*), void* prm_pArg1, void* prm_pArg2) {
		order(prm_id, (GgafObject* (*)(void*, void*))prm_pFunc, prm_pArg1, prm_pArg2);
	}

	/**
	 * 工場にシーン作成の注文を行う<BR>
	 * @param   prm_id	注文識別ID
	 * 			prm_pFunc	実際に製造処理を行う関数のポインタ<BR>
	 * 			prm_pArg	その引数<BR>
	 */
	template <class X>
	static void orderScene(std::string prm_id, X* (*prm_pFunc)(void*, void*), void* prm_pArg1, void* prm_pArg2) {
		order(prm_id, (GgafObject* (*)(void*, void*))prm_pFunc, prm_pArg1, prm_pArg2);
	}

	/**
	 * 注文したアクターを取り出す。<BR>
	 * 未製造だった場合、製造が完了するまで待つ。<BR>
	 * @param   prm_id	注文識別ID
	 * @return	生成されたアクターのポインタ
	 */
	static GgafMainActor* obtainActor(std::string prm_id);

	/**
	 * 注文したシーンを取り出す。<BR>
	 * 未製造だった場合、製造が完了するまで待つ。<BR>
	 * @param   prm_id	注文識別ID
	 * @return	生成されたシーンのポインタ
	 */
	static GgafMainScene* obtainScene(std::string prm_id);

	/**
	 * 工場を掃除する<BR>
	 * ROOT_ORDER が指している製品の連結リストを全て解放する<BR>
	 * 注意：必ず以下のようにクリティカルセクションで囲んで呼び出してください！。<BR>
	 * ＜コード例＞ <BR>
	 * ::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始<BR>
	 * GgafFactory::clean();<BR>
	 * ::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了<BR>
	 */
	static void clean();

	/**
	 * 稼動する。<BR>
	 * 神が初期設定時に別スレッドで一度実行する。神が死ぬまで（アプリ終了まで）永遠に稼動しっ放しである。<BR>
	 */
	static unsigned __stdcall work(void* prm_arg);

};


}
#endif /*GGAFGACTORY_H_*/
