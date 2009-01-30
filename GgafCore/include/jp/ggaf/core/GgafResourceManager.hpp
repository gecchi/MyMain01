#ifndef GGAFRESOURCEMANAGER_H_
#define GGAFRESOURCEMANAGER_H_
namespace GgafCore {


/**
 * GgafResourceConnection 管理クラス .
 * 生成済み GgafResourceConnection オブジェクトを登録しておき、使いまわします。
 */
template<class T>
class GgafResourceManager : public GgafObject {
private:
	/**
	 * 資源のを生成を下位で実装します。.
	 * @param prm_name 識別名
	 */
	T* createResource(char* prm_idstr);

	/**
	 * 標準の資源参照オブジェクトを生成.
	 * 下位でオーバーライドしてもいいですよ。.
	 * @param prm_name 識別名
	 */
	GgafResourceConnection<T>* createResourceConnection(char* prm_idstr, T* prm_pResource);

public:
	/** マネージャ名称 */
	const char* _manager_name;

	/** GgafResourceConnectionオブジェクトのリストの先頭のポインタ。終端はNULL */
	GgafResourceConnection<T>* _pTop;
	/**
	 * GgafResourceConnectionオブジェクトをリストに追加。<BR>
	 * @param prm_pNew 追加するGgafResourceConnectionオブジェクトのポインタ
	 */
	virtual void add(GgafResourceConnection<T>* prm_pNew);

	/**
	 * GgafResourceConnectionオブジェクトをリストから検索。<BR>
	 * @param prm_name 識別名(＝ファイル名)
	 * @return	所望のGgafResourceConnectionオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	virtual GgafResourceConnection<T>* find(char* prm_name);

	/**
	 * コンストラクタ
	 * @return
	 */
	GgafResourceManager(const char* prm_manager_name);

	/**
	 * デストラクタ。保持リストを強制解放します。 .
	 * 全ての保持リストの GgafResourceConnectionに対し、GgafResourceConnectionのrelease()を１度実行し、<BR>
	 * GgafResourceConnectionの参照カウンタ0ならば、delete します。<BR>
	 * GgafResourceConnectionの参照カウンタ0でなければ、一言喋って delete します。<BR>
	 */
	virtual ~GgafResourceManager();


	/**
	 * GgafResourceConnectionオブジェクトを取得。<BR>
	 * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
	 * 保持リストから取得した場合、参照カウンタが増えます。<BR>
	 * new した場合、参照カウンタは1です。<BR>
	 * @param prm_name 識別名
	 */
	virtual GgafResourceConnection<T>* getConnection(char* prm_idstr);

	virtual T* processCreateResource(char* prm_idstr) = 0;

	virtual GgafResourceConnection<T>* processCreateConnection(char* prm_idstr, T* prm_pResource) = 0;

	virtual void dump();
};

template<class T>
GgafResourceManager<T>::GgafResourceManager(const char* prm_manager_name) : GgafObject(),
_manager_name(prm_manager_name)
{
	_TRACE_("GgafResourceManager<T>::GgafResourceManager("<<prm_manager_name<<")");
	_pTop = NULL;
}


template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::find(char* prm_name) {
	GgafResourceConnection<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (GgafUtil::strcmp_ascii(pCurrent->_idstr, prm_name) == 0) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourceManager<T>::add(GgafResourceConnection<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResourceConnection<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::getConnection(char* prm_idstr) {
	GgafResourceConnection<T>* pObj = find(prm_idstr);
	//未生成ならば生成
	if (pObj == NULL) {
		T* pResource = createResource(prm_idstr);
		pObj = createResourceConnection(prm_idstr, pResource);
		pObj->_iConnectionNum = 1;
		add(pObj);
		_TRACE_("GgafResourceManager<T>::getConnection "<<prm_idstr<<"を新規作成して保持に決定");
		return pObj;
	} else {
		pObj->_iConnectionNum ++;
		_TRACE_("GgafResourceManager<T>::getConnection "<<prm_idstr<<"はあるので参照カウント."<<pObj->_iConnectionNum);
		return pObj;
	}
}

template<class T>
T* GgafResourceManager<T>::createResource(char* prm_idstr) {
	_TRACE_("GgafResourceManager<T>::createResource "<<prm_idstr<<"を生成しましょう");
	return processCreateResource(prm_idstr);
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::createResourceConnection(char* prm_idstr, T* prm_pResource) {
	_TRACE_("GgafResourceManager<T>::createResourceConnection "<<prm_idstr<<"を生成しましょう");
	GgafResourceConnection<T>* p = processCreateConnection(prm_idstr, prm_pResource);
	p->_pManager = this; //マネージャ登録
	return p;
}

template<class T>
void GgafResourceManager<T>::dump() {
	GgafResourceConnection<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump 保持リストにはなにもありません。");
	} else {
		GgafResourceConnection<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iConnectionNum;
			_TRACE_("GgafResourceManager::dump ["<<pCurrent->_idstr<<"←"<<rnum<<"Objects]");
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



template<class T>
GgafResourceManager<T>::~GgafResourceManager() {
	_TRACE_("GgafResourceManager<T>::~GgafResourceManager "<<_manager_name<<" ");
	GgafResourceConnection<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::GgafResourceManager 保持リストにはなにもありません。");
	} else {
		GgafResourceConnection<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iConnectionNum;
			_TRACE_("GgafResourceManager::GgafResourceManager 保持リストに["<<pCurrent->_idstr<<"←"<<rnum<<"Objects]が残ってます。強制削除しますが、本来あってはいけません。");

			T* r = pCurrent->getResource();
			pCurrent_Next = pCurrent -> _pNext;
			if (r != NULL) {
				pCurrent->processReleaseResource(r); //リソースの解放
			}
			for (int i = 0; i < rnum; i++) {
				RELEASE_IMPOSSIBLE_NULL(pCurrent); //自殺するまで解放
			}
			if (pCurrent_Next == NULL) {
				//最後の一つ
				break;
			} else {
				pCurrent = pCurrent_Next;
			}
		}
	}
}
}
#endif /*GGAFRESOURCEMANAGER_H_*/
