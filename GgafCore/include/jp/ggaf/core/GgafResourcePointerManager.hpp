#ifndef GGAFRESOURCEPOINTERMANAGER_H_
#define GGAFRESOURCEPOINTERMANAGER_H_
namespace GgafCore {


/**
 * GgafResourcePointer 管理クラス .
 * 生成済み GgafResourcePointer オブジェクトを登録しておき、使いまわします。
 */
template<class T>
class GgafResourcePointerManager : public GgafObject {

protected:

	std::string _manager_name;

	/** GgafResourcePointerオブジェクトのリストの先頭のポインタ。終端はNULL */
	GgafResourcePointer<T>* _pTop;
	/**
	 * GgafResourcePointerオブジェクトをリストに追加。<BR>
	 * @param prm_pNew 追加するGgafResourcePointerオブジェクトのポインタ
	 */
	virtual void add(GgafResourcePointer<T>* prm_pNew);

	/**
	 * GgafResourcePointerオブジェクトをリストから検索。<BR>
	 * @param prm_name 識別名(＝ファイル名)
	 * @return	所望のGgafResourcePointerオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	virtual GgafResourcePointer<T>* find(std::string prm_name);

public:

	/**
	 * コンストラクタ
	 * @return
	 */
	GgafResourcePointerManager(std::string prm_manager_name);

	/**
	 * デストラクタ。保持リストを強制解放します。 .
	 * 全ての保持リストの GgafResourcePointerに対し、GgafResourcePointerのrelease()を１度実行し、<BR>
	 * GgafResourcePointerの参照カウンタ0ならば、delete します。<BR>
	 * GgafResourcePointerの参照カウンタ0でなければ、一言喋って delete します。<BR>
	 */
	virtual ~GgafResourcePointerManager();

	/**
	 * GgafResourcePointerオブジェクトを取得。<BR>
	 * モデルオブジェクトは、初期化時、このメソッドを１回だけ呼び出してを取得する。<BR>
	 * は、保持リストに存在すればそれを返し、存在しなければ new します。<BR>
	 * を保持リストから取得した場合、参照カウンタが増えます。（モデル初期時１回に限定するのはこのため）<BR>
	 * new した場合、参照カウンタは1です。<BR>
	 * 参照カウンタはモデルの delete 時にを解放するかどうかの判断に使用される。<BR>
	 * @param prm_name 識別名
	 */
	virtual T* referResource(std::string prm_resource_idstr);

	virtual void releaseResource(T* prm_pResource);

	virtual GgafResourcePointer<T>* referResourcePointer(std::string prm_resource_idstr);
	virtual void releaseResourcePointer(GgafResourcePointer<T>* prm_pResourcePointer);



	/**
	 * 資源のを生成を下位で実装します。.
	 * @param prm_name 識別名
	 */
	virtual T* createResource(std::string prm_resource_idstr);

	virtual T* processCreateResource(std::string prm_resource_idstr)= 0;


	/**
	 * 標準の資源参照オブジェクトを生成.
	 * 下位でオーバーライドしてもいいですよ。.
	 * @param prm_name 識別名
	 */
	virtual GgafResourcePointer<T>* createResourcePointer(std::string prm_resource_idstr, T* prm_pResource);
	virtual void processReleaseResource(T* prm_pResource)= 0;



	virtual void dump();
};

template<class T>
GgafResourcePointerManager<T>::GgafResourcePointerManager(std::string prm_manager_name) : GgafObject() {
	_TRACE_("GgafResourcePointerManager<T>::GgafResourcePointerManager("<<prm_manager_name<<")");
	_manager_name =  prm_manager_name;
	_pTop = NULL;
}

template<class T>
GgafResourcePointerManager<T>::~GgafResourcePointerManager() {
	_TRACE_("GgafResourcePointerManager<T>::~GgafResourcePointerManager "<<_manager_name<<" ");
	GgafResourcePointer<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourcePointerManager::dump 保持リストにはなにもありません。");
	} else {
		GgafResourcePointer<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			processReleaseResource(pCurrent->getResource()); //解放
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum != 0) {
				_TRACE_("GgafResourcePointerManager::~GgafResourcePointerManager ["<<pCurrent->_resource_idstr<<"←"<<rnum<<"Objects] 参照0でないけどdeleteします。");
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
GgafResourcePointer<T>* GgafResourcePointerManager<T>::find(std::string prm_name) {
	GgafResourcePointer<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (pCurrent->_resource_idstr == prm_name) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourcePointerManager<T>::add(GgafResourcePointer<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResourcePointer<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}

template<class T>
void GgafResourcePointerManager<T>::releaseResource(T* prm_pResource) {
	if (prm_pResource == NULL) {
		_TRACE_("GgafResourcePointerManager::releaseResource 引数 prm_pResource は NULLです");
		return;
	}
	GgafResourcePointer<T>* pCurrent;
	GgafResourcePointer<T>* pPrev;
	pCurrent = _pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent->getResource() == prm_pResource) {
			//発見した場合
			_TRACE_("GgafResourcePointerManager::releaseResource["<<pCurrent->_resource_idstr<<"]");
			processReleaseResource(pCurrent->getResource()); //解放
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum == 0) {
				if (pCurrent->_pNext == NULL) {
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
				_TRACE_("GgafResourcePointerManager::releaseResource["<<pCurrent->_resource_idstr<<"←"<<rnum<<"Objects]");
			}  else if (rnum < 0) {
				_TRACE_("GgafResourcePointerManager::releaseResource["<<pCurrent->_resource_idstr<<"←"<<rnum<<"Objects] 解放しすぎ(><)。作者のアホー。");
			}
			return;
		} else {
			//違った場合
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}
	_TRACE_("GgafResourcePointerManager::releaseResource prm_pResourceはありません。意図してますか？");
}


template<class T>
void GgafResourcePointerManager<T>::releaseResourcePointer(GgafResourcePointer<T>* prm_pResourcePointer) {
	if (prm_pResourcePointer == NULL) {
		_TRACE_("GgafResourcePointerManager::releaseResourcePointer 引数 prm_pResourcePointer は NULLです");
		return;
	}
	GgafResourcePointer<T>* pCurrent;
	GgafResourcePointer<T>* pPrev;
	pCurrent = _pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent == prm_pResourcePointer) {
			//発見した場合
			_TRACE_("GgafResourcePointerManager::releaseResourcePointer["<<pCurrent->_resource_idstr<<"]");
			processReleaseResource(pCurrent->getResource()); //解放
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum == 0) {
				if (pCurrent->_pNext == NULL) {
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
				_TRACE_("GgafResourcePointerManager::releaseResourcePointer["<<pCurrent->_resource_idstr<<"←"<<rnum<<"Objects]");
			}  else if (rnum < 0) {
				_TRACE_("GgafResourcePointerManager::releaseResourcePointer["<<pCurrent->_resource_idstr<<"←"<<rnum<<"Objects] 解放しすぎ(><)。作者のアホー。");
			}
			return;
		} else {
			//違った場合
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}
	_TRACE_("GgafResourcePointerManager::releaseResourcePointer prm_pResourcePointer["<<prm_pResourcePointer->_resource_idstr<<"]は既にありません。意図してますか？");
}




template<class T>
T* GgafResourcePointerManager<T>::referResource(std::string prm_resource_idstr) {
	GgafResourcePointer<T>* pObj = find(prm_resource_idstr);
	//未生成ならば生成
	if (pObj == NULL) {
		T* pResource = createResource(prm_resource_idstr);
		pObj = createResourcePointer(prm_resource_idstr, pResource);
		pObj->_iResourceReferenceNum = 1;
		add(pObj);
		return pResource;
	} else {
		pObj->_iResourceReferenceNum ++;
		return pObj->getResource();
	}
}

template<class T>
GgafResourcePointer<T>* GgafResourcePointerManager<T>::referResourcePointer(std::string prm_resource_idstr) {
	GgafResourcePointer<T>* pObj = find(prm_resource_idstr);
	//未生成ならば生成
	if (pObj == NULL) {
		T* pResource = createResource(prm_resource_idstr);
		pObj = createResourcePointer(prm_resource_idstr, pResource);
		pObj->_iResourceReferenceNum = 1;
		add(pObj);
		return pObj;
	} else {
		pObj->_iResourceReferenceNum ++;
		return pObj;
	}
}

template<class T>
T* GgafResourcePointerManager<T>::createResource(std::string prm_resource_idstr) {
	_TRACE_("GgafResourcePointerManager<T>::createResource "<<prm_resource_idstr<<"を生成しましょう");
	return processCreateResource(prm_resource_idstr);
}

template<class T>
GgafResourcePointer<T>* GgafResourcePointerManager<T>::createResourcePointer(std::string prm_resource_idstr, T* prm_pResource) {
	GgafResourcePointer<T>* p = NEW GgafResourcePointer<T>(prm_resource_idstr, prm_pResource);
	return p;
}

template<class T>
void GgafResourcePointerManager<T>::dump() {
	GgafResourcePointer<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourcePointerManager::dump 保持リストにはなにもありません。");
	} else {
		GgafResourcePointer<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iResourceReferenceNum;
			_TRACE_("GgafResourcePointerManager::dump ["<<pCurrent->_resource_idstr<<"←"<<rnum<<"Objects]");
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

}
#endif /*GGAFRESOURCEPOINTERMANAGER_H_*/
