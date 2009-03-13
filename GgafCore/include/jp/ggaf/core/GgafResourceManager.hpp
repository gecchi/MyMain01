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
     * 資源のを生成。.
     * @param prm_name 識別名
     */
    T* createResource(char* prm_idstr);

    /**
     * 資源接続オブジェクトを生成.
     * @param prm_name 識別名
     */
    GgafResourceConnection<T>* createResourceConnection(char* prm_idstr, T* prm_pResource);

public:
    /** マネージャ名称 */
    const char* _manager_name;
    /** GgafResourceConnectionオブジェクトのリストの先頭のポインタ。終端はNULL */
    GgafResourceConnection<T>* _pTop;

    /**
     * コンストラクタ
     */
    GgafResourceManager(const char* prm_manager_name);

    /**
     * GgafResourceConnectionオブジェクトをリストに追加。<BR>
     * @param prm_pNew 追加するGgafResourceConnectionオブジェクトのポインタ
     */
    virtual void add(GgafResourceConnection<T>* prm_pNew);

    /**
     * GgafResourceConnectionオブジェクトをリストから検索。<BR>
     * @param prm_idstr 識別名
     * @return	所望のGgafResourceConnectionオブジェクトのポインタ。リストに存在しなかった場合 NULL
     */
    virtual GgafResourceConnection<T>* find(char* prm_idstr);

    /**
     * デストラクタ。保持リストを強制解放します。 .
     * 全ての保持リストの GgafResourceConnectionに対し、GgafResourceConnectionのrelease()を１度実行し、<BR>
     * GgafResourceConnectionの接続カウンタ0ならば、delete します。<BR>
     * GgafResourceConnectionの接続カウンタ0でなければ、使用者のロジックで解放漏れの恐れがあるので
     * 一言喋って delete します。<BR>
     */
    virtual ~GgafResourceManager();

    /**
     * GgafResourceConnectionオブジェクトを取得。<BR>
     * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
     * 保持リストから取得した場合、接続カウンタが増えます。<BR>
     * new した場合、接続カウンタは1です。<BR>
     * @param prm_idstr 識別名
     */
    virtual GgafResourceConnection<T>* getConnection(char* prm_idstr);

    /**
     * GgafResourceConnectionオブジェクトを取得。<BR>
     * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
     * 保持リストから取得した場合、接続カウンタが増えます。<BR>
     * new した場合、接続カウンタは1です。<BR>
     * @param prm_idstr 識別名
     */
    virtual GgafResourceConnection<T>* getConnection(const char* prm_idstr);

    /**
     * 実際の資源のを生成を下位で実装します。.
     * このメソッドは createResource から呼び出され、本テンプレート利用者が実装する必要があります。<BR>
     * prm_idstr から 資源を生成するロジックを実装してく下さい。<BR>
     * @param prm_idstr この識別名が渡された時、どういう資源を生成するか？ という識別名
     * @return 資源インスタンスのポインタ
     */
    virtual T* processCreateResource(char* prm_idstr) = 0;

    /**
     * 資源接続オブジェクトの生成を下位で実装します。.
     * このメソッドは createResourceConnection から呼び出され、本テンプレート利用者が実装する必要があります。<BR>
     * prm_idstr から 資源接続オブジェクトを生成するロジックを実装してく下さい。<BR>
     * ほとんどは、GgafResourceConnection 実装クラスを new して、それを返すだけでOK。BR>
     * @param prm_idstr  この識別名が渡された時、どういう資源接続オブジェクトを生成するか？ という識別名
     * @param prm_pResource 資源ポインタ
     * @return GgafResourceConnection 資源接続オブジェクトのインスタンス（＝GgafResourceConnection 実装クラスのインスタンス）
     */
    virtual GgafResourceConnection<T>* processCreateConnection(char* prm_idstr, T* prm_pResource) = 0;

    /**
     * マネジャーが保持するリストを出力します。（デバッグ用） .
     */
    virtual void dump();
};

// ---------------------------------------------------------------------//

template<class T>
GgafResourceManager<T>::GgafResourceManager(const char* prm_manager_name) : GgafObject(),
      _manager_name(prm_manager_name) {
    TRACE3("GgafResourceManager<T>::GgafResourceManager(" << prm_manager_name << ")");
    _pTop = NULL;
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::find(char* prm_idstr) {
    GgafResourceConnection<T>* pCurrent = _pTop;
    while (pCurrent != NULL) {
        if (GgafUtil::strcmp_ascii(pCurrent->_idstr, prm_idstr) == 0) {
            return pCurrent;
        }
        pCurrent = pCurrent->_pNext;
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
        while (pCurrent->_pNext != NULL) {
            pCurrent = pCurrent->_pNext;
        }
        pCurrent->_pNext = prm_pResource_New;
        return;
    }
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::getConnection(char* prm_idstr) {
    if (prm_idstr == NULL) {
        TRACE3("警告 GgafResourceManager<T>::getConnection(NULL) [" << _manager_name << "]");
    }
    GgafResourceConnection<T>* pObj = find(prm_idstr);
    if (pObj == NULL) {
        //未生成ならば生成。接続カウンタを１
        T* pResource = createResource(prm_idstr);
        pObj = createResourceConnection(prm_idstr, pResource);
        pObj->_num_connection = 1;
        add(pObj);
        TRACE3("GgafResourceManager<T>::getConnection [" << _manager_name << "]" << prm_idstr << "は無いので、新規作成して保持に決定");
        return pObj;
    } else {
        //生成済みならそれを返す。接続カウンタを＋１
        pObj->_num_connection++;
        TRACE3("GgafResourceManager<T>::getConnection [" << _manager_name << "]" << prm_idstr << "はあるので接続カウント＋１." << pObj->_num_connection);
        return pObj;
    }
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::getConnection(const char* prm_idstr) {
    return this->getConnection((char*)prm_idstr);
}

template<class T>
T* GgafResourceManager<T>::createResource(char* prm_idstr) {
    TRACE3("GgafResourceManager<T>::createResource [" << _manager_name << "]" << prm_idstr << "を生成しましょう");
    return processCreateResource(prm_idstr);
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::createResourceConnection(char* prm_idstr, T* prm_pResource) {
    TRACE3("GgafResourceManager<T>::createResourceConnection [" << _manager_name << "]" << prm_idstr << "を生成しましょう");
    GgafResourceConnection<T>* p = processCreateConnection(prm_idstr, prm_pResource);
    p->_pManager = this; //マネージャ登録
    return p;
}

template<class T>
void GgafResourceManager<T>::dump() {
    GgafResourceConnection<T>* pCurrent = _pTop;
    if (_pTop == NULL) {
        TRACE3("GgafResourceManager::dump[" << _manager_name << "] 保持リストにはなにもありません。");
    } else {
        GgafResourceConnection<T>* pCurrent_Next;
        while (pCurrent != NULL) {
            TRACE3("GgafResourceManager::dump[" << _manager_name << "] [" << pCurrent->_idstr << "←" << pCurrent->_num_connection << "Connection]");
            pCurrent_Next = pCurrent->_pNext;
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
    TRACE3("GgafResourceManager<T>::~GgafResourceManager[" << _manager_name << "] " << _manager_name << " ");
    GgafResourceConnection<T>* pCurrent = _pTop;
    if (_pTop == NULL) {
        TRACE3("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] 保持リストにはなにもありません。");
    } else {
        GgafResourceConnection<T>* pCurrent_Next;
        while (pCurrent != NULL) {
            int rnum = pCurrent->_num_connection;
            TRACE3("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] 保持リストに[" << pCurrent->_idstr << "←" << rnum
                    << "Connection]が残ってます。強制削除しますが、本来あってはいけません。特別に" << rnum << "回 close()を発行します");
//            T* r = pCurrent->view();
            pCurrent_Next = pCurrent->_pNext;
//            if (r != NULL) {
//                pCurrent->processReleaseResource(r); //リソースの解放
//            }
            for (int i = 0; i < rnum; i++) {
                pCurrent->close(); //自殺するまで解放
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
