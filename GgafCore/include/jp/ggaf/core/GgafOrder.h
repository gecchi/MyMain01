#ifndef GGAFORDER_H_
#define GGAFORDER_H_

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
	GgafObject* (*_functionForBuild)(void*);
	/** 商品製造メソッドのパラメータ */
	void* _argumentForBuild;
	/** 進捗具合（0:未着手/1:製造中/2:製造済み） */
	int _progress;
	
public:
	GgafOrder(string prm_id);
	virtual ~GgafOrder();
};

#endif /*GGAFORDER_H_*/
