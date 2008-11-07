#ifndef GGAFORDER_H_
#define GGAFORDER_H_

/**
 * 商品（何かのインスタンス）の注文クラス .
 * 工場(GgafFactory)に渡す注文を表したクラスで、 商品（何かのインスタンス）１つを内部保持します。<BR>
 * また注文オブジェクト同士で連結リストを作成でき、そのリストは工場(GgafFactory)が操作することになります。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafOrder : public GgafObject {
	friend class GgafGod;
	friend class GgafFactory;

private:
	/** 注文識別ID */
	string _id;
	/** 一つ次の注文 */
	GgafOrder* _pOrder_Next;
	/** 一つ前の注文 */
	GgafOrder* _pOrder_Prev;
	/** 先頭の注文フラグ */
	bool _isFirstOrder;
	/** 最後の注文フラグ */
	bool _isLastOrder;
	/** 商品へのポインタ */
	GgafObject* _pObject_Creation;
	/** 商品製造メソッド */
	GgafObject* (*_functionForBuild)(void*, void*);
	/** 商品製造メソッドのパラメータ */
	void* _argumentForBuild1;
	void* _argumentForBuild2;
	/** 進捗具合（0:未着手/1:製造中/2:製造済み） */
	int _progress;

public:
	GgafOrder(string prm_id);
	virtual ~GgafOrder();
};

#endif /*GGAFORDER_H_*/
