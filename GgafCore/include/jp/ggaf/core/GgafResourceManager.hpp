#ifndef GGAFRESOURCEMANAGER_H_
#define GGAFRESOURCEMANAGER_H_
namespace GgafCore {


/**
 * GgafResourceLead 管理クラス .
 * 生成済み GgafResourceLead オブジェクトを登録しておき、使いまわします。
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
	GgafResourceLead<T>* createResourceLead(char* prm_idstr, T* prm_pResource);

public:
	/** マネージャ名称 */
	const char* _manager_name;

	/** GgafResourceLeadオブジェクトのリストの先頭のポインタ。終端はNULL */
	GgafResourceLead<T>* _pTop;
	/**
	 * GgafResourceLeadオブジェクトをリストに追加。<BR>
	 * @param prm_pNew 追加するGgafResourceLeadオブジェクトのポインタ
	 */
	virtual void add(GgafResourceLead<T>* prm_pNew);

	/**
	 * GgafResourceLeadオブジェクトをリストから検索。<BR>
	 * @param prm_idstr 識別名
	 * @return	所望のGgafResourceLeadオブジェクトのポインタ。リストに存在しなかった場合 NULL
	 */
	virtual GgafResourceLead<T>* find(char* prm_idstr);

	/**
	 * コンストラクタ
	 * @return
	 */
	GgafResourceManager(const char* prm_manager_name);

	/**
	 * デストラクタ。保持リストを強制解放します。 .
	 * 全ての保持リストの GgafResourceLeadに対し、GgafResourceLeadのrelease()を１度実行し、<BR>
	 * GgafResourceLeadの参照カウンタ0ならば、delete します。<BR>
	 * GgafResourceLeadの参照カウンタ0でなければ、一言喋って delete します。<BR>
	 */
	virtual ~GgafResourceManager();


	/**
	 * GgafResourceLeadオブジェクトを取得。<BR>
	 * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
	 * 保持リストから取得した場合、参照カウンタが増えます。<BR>
	 * new した場合、参照カウンタは1です。<BR>
	 * @param prm_name 識別名
	 */
	virtual GgafResourceLead<T>* lead(char* prm_idstr);
	virtual GgafResourceLead<T>* lead(const char* prm_idstr);

	virtual T* processCreateResource(char* prm_idstr) = 0;

	virtual GgafResourceLead<T>* processCreateLead(char* prm_idstr, T* prm_pResource) = 0;

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
GgafResourceLead<T>* GgafResourceManager<T>::find(char* prm_idstr) {
	GgafResourceLead<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (GgafUtil::strcmp_ascii(pCurrent->_idstr, prm_idstr) == 0) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourceManager<T>::add(GgafResourceLead<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResourceLead<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}

template<class T>
GgafResourceLead<T>* GgafResourceManager<T>::lead(char* prm_idstr) {
	GgafResourceLead<T>* pObj = find(prm_idstr);
	//未生成ならば生成
	if (pObj == NULL) {
		T* pResource = createResource(prm_idstr);
		pObj = createResourceLead(prm_idstr, pResource);
		pObj->_iLeadNum = 1;
		add(pObj);
		_TRACE_("GgafResourceManager<T>::lead "<<prm_idstr<<"を新規作成して保持に決定");
		return pObj;
	} else {
		pObj->_iLeadNum ++;
		_TRACE_("GgafResourceManager<T>::lead "<<prm_idstr<<"はあるので参照カウント."<<pObj->_iLeadNum);
		return pObj;
	}
}

template<class T>
GgafResourceLead<T>* GgafResourceManager<T>::lead(const char* prm_idstr) {
	return this->lead((char*)prm_idstr);
}


template<class T>
T* GgafResourceManager<T>::createResource(char* prm_idstr) {
	_TRACE_("GgafResourceManager<T>::createResource "<<prm_idstr<<"を生成しましょう");
	return processCreateResource(prm_idstr);
}

template<class T>
GgafResourceLead<T>* GgafResourceManager<T>::createResourceLead(char* prm_idstr, T* prm_pResource) {
	_TRACE_("GgafResourceManager<T>::createResourceLead "<<prm_idstr<<"を生成しましょう");
	GgafResourceLead<T>* p = processCreateLead(prm_idstr, prm_pResource);
	p->_pManager = this; //マネージャ登録
	return p;
}

template<class T>
void GgafResourceManager<T>::dump() {
	GgafResourceLead<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump 保持リストにはなにもありません。");
	} else {
		GgafResourceLead<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iLeadNum;
			_TRACE_("GgafResourceManager::dump ["<<pCurrent->_idstr<<"←"<<rnum<<"Lead]");
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
	GgafResourceLead<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::GgafResourceManager 保持リストにはなにもありません。");
	} else {
		GgafResourceLead<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iLeadNum;
			_TRACE_("GgafResourceManager::GgafResourceManager 保持リストに["<<pCurrent->_idstr<<"←"<<rnum<<"Lead]が残ってます。強制削除しますが、本来あってはいけません。");

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
