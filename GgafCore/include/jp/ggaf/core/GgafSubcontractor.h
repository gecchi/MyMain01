#ifndef GGAFSUBCONTRACTOR_H_
#define GGAFSUBCONTRACTOR_H_

class GgafSubcontractor {
	friend class GgafGod;

private:
	static GgafGod* _pGod;

	/** 先頭の注文 */
	static GgafOrder* _pOrder_First;
	/** 現在製造中の注文 */
	static GgafOrder* _pOrder_InManufacturing;
	//全て製造済みの場合、最終注文を指しつづける
	//全て製造済みかつ、製品が全て取得されてしまった場合は NULL になる。
	//_isLastOrder == false を常に判定し、最終注文でなくなったら（新規注文があれば）、
	//製造を行って次に進める。 _isLastOrder == false になるまで製造しつづける


	/**
	 * 工場に注文を行う<BR>
	 * @param   prm_id	注文識別ID
	 * 			prm_functionForBuild	実際に製造処理を行う関数のポインタ<BR>
	 * 			prm_argumentForBuild	その引数<BR>
	 */
	static void order(string prm_id, GgafObject* (*prm_functionForBuild)(void*), void* prm_argumentForBuild);

	/**
	 * 注文した商品を取り出す。<BR>
	 * 未製造だった場合、製造が完了するまで待つ。<BR>
	 * @param   prm_id	注文識別ID
	 * @return	製品のポインタ
	 */
	static void* obtain(string prm_id);

public:
	/** 活動フラグ(神が操作する) */
	static bool _isWorking;

	/**
	 * 工場にアクター作成の注文を行う<BR>
	 * @param   prm_id	注文識別ID
	 * 			prm_functionForBuild	実際に製造処理を行う関数のポインタ<BR>
	 * 			prm_argumentForBuild	その引数<BR>
	 */
	static void orderActor(string prm_id, GgafMainActor* (*prm_functionForBuild)(void*), void* prm_argumentForBuild);

	/**
	 * 工場にシーン作成の注文を行う<BR>
	 * @param   prm_id	注文識別ID
	 * 			prm_functionForBuild	実際に製造処理を行う関数のポインタ<BR>
	 * 			prm_argumentForBuild	その引数<BR>
	 */
	static void orderScene(string prm_id, GgafMainScene* (*prm_functionForBuild)(void*), void* prm_argumentForBuild);

	/**
	 * 注文したアクターを取り出す。<BR>
	 * 未製造だった場合、製造が完了するまで待つ。<BR>
	 * @param   prm_id	注文識別ID
	 * @return	生成されたアクターのポインタ
	 */
	static GgafMainActor* obtainActor(string prm_id);

	/**
	 * 注文したシーンを取り出す。<BR>
	 * 未製造だった場合、製造が完了するまで待つ。<BR>
	 * @param   prm_id	注文識別ID
	 * @return	生成されたシーンのポインタ
	 */
	static GgafMainScene* obtainScene(string prm_id);

	/**
	 * 工場を掃除する<BR>
	 * _pOrder_First が指している製品の連結リストを全て解放する<BR>
	 * 注意：必ず以下のようにクリティカルセクションで囲んで呼び出してください！。<BR>
	 * ＜コード例＞ <BR>
	 * ::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始<BR>
	 * GgafSubcontractor::clean();<BR>
	 * ::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了<BR>
	 */
	static void clean();

	/**
	 * 稼動する。<BR>
	 * 神が初期設定時に別スレッドで一度実行する。神が死ぬまで（アプリ終了まで）永遠に稼動しっ放しである。<BR>
	 */
	static unsigned __stdcall work(void* prm_arg);

};



#endif /*GGAFSUBCONTRACTOR_H_*/
