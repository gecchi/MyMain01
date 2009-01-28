#ifndef GgafResourceManager_H_
#define GgafResourceManager_H_
namespace GgafCore {


/**
 * GgafResource 管理クラス .
 * 生成済み GgafResource オブジェクトを登録しておき、使いまわします。
 */
template<class T>
class GgafResourceManager : public GgafObject {

protected:

	std::string _manager_name;

	/** GgafResourceオブジェクトのリストの先頭のポインタ。終端はNULL */
	GgafResource<T>* _pTop;
	/**
	 * GgafResourceオブジェクトをリストに追加。<BR>
	 * @param prm_pNew 追加するGgafResourceオブジェクトのポインタ
	 */
	virtual void add(GgafResource<T>* prm_pNew);

	/**
	 * GgafResourceオブジェクトをリストから検索。<BR>
	 * @param prm_name 識別名(＝ファイル名)
	 * @return	所望のGgafResourceオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	virtual GgafResource<T>* find(std::string prm_name);

public:

	/**
	 * コンストラクタ
	 * @return
	 */
	GgafResourceManager(std::string prm_manager_name);

	/**
	 * デストラクタ。保持リストを強制解放します。 .
	 * 全ての保持リストの GgafResourceに対し、GgafResourceのrelease()を１度実行し、<BR>
	 * GgafResourceの参照カウンタ0ならば、delete します。<BR>
	 * GgafResourceの参照カウンタ0でなければ、一言喋って delete します。<BR>
	 */
	virtual ~GgafResourceManager();

	/**
	 * GgafResourceオブジェクトを取得。<BR>
	 * モデルオブジェクトは、初期化時、このメソッドを１回だけ呼び出してを取得する。<BR>
	 * は、保持リストに存在すればそれを返し、存在しなければ new します。<BR>
	 * を保持リストから取得した場合、参照カウンタが増えます。（モデル初期時１回に限定するのはこのため）<BR>
	 * new した場合、参照カウンタは1です。<BR>
	 * 参照カウンタはモデルの delete 時にを解放するかどうかの判断に使用される。<BR>
	 * @param prm_name 識別名
	 */
	virtual GgafResource<T>* reference(std::string prm_name);

	/**
	 * GgafResourceを生成します。.
	 * 下位で実装してください。
	 * @param prm_name 識別名
	 */
	virtual GgafResource<T>* createResource(std::string prm_name) = 0;


	/**
	 * リソースの解放.
	 * 引数の対象 GgafResourceが、保持リストにあれば GgafResourceのrelease()を実行し、<BR>
	 * GgafResourceの参照カウンタが0ならば、さらに delete します<BR>
	 * 注意：保持リストにインスタンスは残ってる可能性があります。<BR>
	 * @param prm_pResource 対象GgafResource
	 */
	virtual void release(GgafResource<T>* prm_pResource);


	virtual void dump();
};

template<class T>
GgafResourceManager<T>::GgafResourceManager(std::string prm_manager_name) : GgafObject() {
	_TRACE_("GgafResourceManager<T>::GgafResourceManager("<<prm_manager_name<<")");
	_manager_name =  prm_manager_name;
	_pTop = NULL;
}

template<class T>
GgafResourceManager<T>::~GgafResourceManager() {
	_TRACE_("GgafResourceManager<T>::~GgafResourceManager "<<_manager_name<<" ");
	GgafResource<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump 保持リストにはなにもありません。");
	} else {
		GgafResource<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			pCurrent->releaseResource(); //解放
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum != 0) {
				_TRACE_("GgafResourceManager::~GgafResourceManager ["<<pCurrent->_name<<"←"<<rnum<<"Objects] 参照0でないけどdeleteします。");
			}
			DELETE_IMPOSSIBLE_NULL(pCurrent); //本当の解放
			pCurrent_Next = pCurrent -> _pNext;
			if (pCurrent_Next == NULL) {
				//最後の一つ
				break;
			} else {
				pCurrent = pCurrent_Next;
			}
		}
	}
}

template<class T>
GgafResource<T>* GgafResourceManager<T>::find(std::string prm_name) {
	GgafResource<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (pCurrent->_name == prm_name) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourceManager<T>::add(GgafResource<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResource<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}


template<class T>
void GgafResourceManager<T>::release(GgafResource<T>* prm_pResource) {
	if (prm_pResource == NULL) {
		_TRACE_("GgafResourceManager::remove 引数 prm_pResource は NULLです");
		return;
	}
	GgafResource<T>* pCurrent;
	GgafResource<T>* pPrev;
	pCurrent = _pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent == prm_pResource) {
			//発見した場合
			_TRACE_("GgafResourceManager::release["<<pCurrent->_name<<"]");
			pCurrent->releaseResource(); //解放
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum == 0) {
				if (prm_pResource->_pNext == NULL) {
					//末尾だった
					if (pPrev == NULL) {
						//末尾で先頭だった（＝最後の一つ）
						_pTop = NULL;
					} else {
						//末尾で先頭でなかった
						pPrev->_pNext = NULL;
					}
				} else {
					//末尾でない
					if (pPrev == NULL) {
						//先頭だった
						_pTop = pCurrent->_pNext; //先頭を次にずらす
					} else {
						//末尾でも先頭でもない（中間）
						pPrev->_pNext = pCurrent->_pNext; //両隣を繋げる
					}
				}
				DELETE_IMPOSSIBLE_NULL(pCurrent); //本当の解放
			} else if (rnum > 0) {
				_TRACE_("GgafResourceManager::release["<<pCurrent->_name<<"←"<<rnum<<"Objects]");
			}  else if (rnum < 0) {
				_TRACE_("GgafResourceManager::release["<<pCurrent->_name<<"←"<<rnum<<"Objects] 解放しすぎ(><)。作者のアホー。");
			}
			return;
		} else {
			//違った場合
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}
	_TRACE_("GgafResourceManager::release prm_pResource["<<prm_pResource->_name<<"]は既にありません。意図してますか？");
}


template<class T>
GgafResource<T>* GgafResourceManager<T>::reference(std::string prm_name) {
	GgafResource<T>* pObj = find(prm_name);
	//未生成ならば生成
	if (pObj == NULL) {
		pObj = createResource(prm_name);
		pObj->_iReferenceNum = 1;
		add(pObj);
		return pObj;
	} else {
		pObj->_iReferenceNum ++;
		return pObj;
	}
}


template<class T>
void GgafResourceManager<T>::dump() {
	GgafResource<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump 保持リストにはなにもありません。");
	} else {
		GgafResource<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iResourceReferenceNum;
			_TRACE_("GgafResourceManager::dump ["<<pCurrent->_name<<"←"<<rnum<<"Objects]");
			pCurrent_Next = pCurrent -> _pNext;
			if (pCurrent_Next == NULL) {
				pCurrent = NULL;
				break;
			} else {
				pCurrent = pCurrent_Next;
			}
		}
	}
}

class ZZZ : public GgafResourceManager<GgafObject> {};

}
#endif /*GgafResourceManager_H_*/
