#ifndef GGAF_CORE_RESOURCEMANAGER_H_
#define GGAF_CORE_RESOURCEMANAGER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "windows.h"
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * 資源管理クラス。 .
 * 資源管理クラスは、資源をラッピングした『資源接続オブジェクト(ResourceConnection)』を管理します。<BR>
 * 資源(Resource)を無駄に生成を行わず、参照して使いまわしたい。しかし new するのかどうかを意識したくない。<BR>
 * そんなときに使うクラスです。<BR>
 * ResourceManager : Resource : ResourceConnection  = 1 : N : N <BR>
 * の関係で、これでワンセットです。<BR>
 * 資源管理クラスは主な機能は、資源接続クラスのインスタンス（のポインタ）を内部にリストで保持し、取得要求があった場合、
 * 内部保持していればそれを返し、保持していなければ生成して、リストに追加した後それを返します。
 * 注意：スレッドセーフの保証は同時に２スレッドまで。３スレッド以上は正しく動作しません。
 * (旧GdxfwActorManagerから汎用化)
 * @tparam T 資源の型（この型に紐付いた資源接続オブジェクトを取得できる）
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
template<class T>
class ResourceManager : public Object {
    friend class ResourceConnection<T>;

private:
    /**
     * ResourceConnectionオブジェクトをリストに追加。<BR>
     * @param prm_pNew 追加するResourceConnectionオブジェクトのポインタ
     */
    virtual void add(ResourceConnection<T>* prm_pNew);

    /**
     * ResourceConnectionオブジェクトをリストから検索。<BR>
     * @param prm_idstr 識別名
     * @return  所望のResourceConnectionオブジェクトのポインタ。リストに存在しなかった場合 nullptr
     */
    virtual ResourceConnection<T>* find(const char* prm_idstr);

    /**
     * 資源のを生成する .
     * connect() 時、資源が実生成場合呼び出されます。
     * processCreateResource(const char*, void*) をコールします。
     * @param prm_idstr connect() で渡された識別名
     * @param prm_p connect() で渡された自由パラメータ
     */
    T* createResource(const char* prm_idstr, void* prm_p);

    /**
     * 資源接続オブジェクトを生成.
     * @param prm_idstr 識別名
     * @param prm_pResource 資源接続オブジェクトのValue。つまり資源インスタンス。
     * @return 資源接続オブジェクト
     */
    ResourceConnection<T>* createResourceConnection(const char* prm_idstr, T* prm_pResource);

protected:
#ifdef _MSC_VER
    //TODO:VC++2005以降(x86) の volatile は、メモリバリア効果がある（と思う）。
    //gcc(x86)は、アトミック保証は無いが std::atomic が使える。VC++に atomic が実装されるまではとりあえず・・・。
    /** connect中はtrueの排他フラグ */
    static volatile bool _is_connecting_resource;
    /** connectするために待っているフラグ */
    static volatile bool _is_waiting_to_connect;
#else
    /** connect中はtrueの排他フラグ */
    static volatile std::atomic<bool> _is_connecting_resource;
    /** connectするために待っているフラグ */
    static volatile std::atomic<bool> _is_waiting_to_connect;
#endif


    /** [r]マネージャ名称 */
    char* _manager_name;
    /** [r]ResourceConnectionオブジェクトのリストの先頭のポインタ。終端はnullptr */
    ResourceConnection<T>* _pConn_first;

protected:
    /**
     * 資源接続オブジェクトの生成を下位で実装します。.
     * このメソッドは createResourceConnection から呼び出され、本テンプレート利用者が実装する必要があります。<BR>
     * prm_idstr から 資源接続オブジェクトを生成するロジックを実装してく下さい。<BR>
     * ほとんどは、ResourceConnection 実装クラスを new して、それを返すだけでOK。BR>
     * @param prm_idstr  この識別名が渡された時、どういう資源接続オブジェクトを生成するか？ という識別名
     * @param prm_pResource 資源ポインタ
     * @return ResourceConnection 資源接続オブジェクトのインスタンス（＝ResourceConnection 実装クラスのインスタンス）
     */
    virtual ResourceConnection<T>* processCreateConnection(const char* prm_idstr, T* prm_pResource) = 0;

    /**
     * 実際の資源のを生成を下位で実装します。.
     * このメソッドは createResource から呼び出され、本テンプレート利用者が実装する必要があります。<BR>
     * prm_idstr から 資源を生成するロジックを実装してく下さい。<BR>
     * @param prm_idstr この識別名が渡された時、どういう資源を生成(new)するか？ という識別名
     * @param prm_p 自由パラメータ
     * @return 資源インスタンスのポインタ
     */
    virtual T* processCreateResource(const char* prm_idstr, void* prm_pConnector) = 0;

//    int ResourceManager<T>::getConnectionNum();

public:
    /**
     * コンストラクタ
     */
    ResourceManager(const char* prm_manager_name);

    /**
     * デストラクタ。保持リストを強制解放します。 .
     * 全ての保持リストの ResourceConnectionに対し、ResourceConnectionのrelease()を１度実行し、<BR>
     * ResourceConnectionの接続カウンタ0ならば、delete します。<BR>
     * ResourceConnectionの接続カウンタ0でなければ、使用者のロジックで解放漏れの恐れがあるので
     * 一言喋って delete します。<BR>
     */
    virtual ~ResourceManager();

    /**
     * 資源接続(ResourceConnection)オブジェクトを取得。<BR>
     * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
     * 保持リストから取得した場合、接続カウンタが増えます。<BR>
     * new した場合、接続カウンタは1です。<BR>
     * @param prm_idstr 識別名
     * @param prm_connector 何らかの引数。何もない場合は、接続元thisを渡して下さい。
     * @return 識別名に紐付く資源接続(ResourceConnection)
     */
    virtual ResourceConnection<T>* connect(const char* prm_idstr, void* prm_connector);

    /**
     * マネジャーが保持するリストを出力します。（デバッグ用） .
     */
    virtual void dump();
};

// ---------------------------------------------------------------------//



#ifdef _MSC_VER

template<class T>
volatile bool ResourceManager<T>::_is_connecting_resource = false;

template<class T>
volatile bool ResourceManager<T>::_is_waiting_to_connect = false;

#else

template<class T>
volatile std::atomic<bool> ResourceManager<T>::_is_connecting_resource(false);

template<class T>
volatile std::atomic<bool> ResourceManager<T>::_is_waiting_to_connect(false);

#endif



template<class T>
ResourceManager<T>::ResourceManager(const char* prm_manager_name) : Object() {
    _TRACE3_("ResourceManager<T>::ResourceManager(" << prm_manager_name << ")");

    int len = strlen(prm_manager_name);
    _manager_name = NEW char[len+1];
    strcpy(_manager_name, prm_manager_name);
    _pConn_first = nullptr;
}

template<class T>
ResourceConnection<T>* ResourceManager<T>::find(const char* prm_idstr) {
    ResourceConnection<T>* pCurrent = _pConn_first;

    while (pCurrent) {
        //_TRACE_("pCurrent->_idstr -> "<<(pCurrent->_idstr)<<" prm_idstr="<<prm_idstr);
        if (strcmp(pCurrent->_idstr, prm_idstr) == 0) {
            return pCurrent;
        }
        pCurrent = pCurrent->_pNext;
    }
    return nullptr;
}

template<class T>
void ResourceManager<T>::add(ResourceConnection<T>* prm_pResource_new) {
    if (_pConn_first == nullptr) {
        _pConn_first = prm_pResource_new;
        return;
    } else {
        ResourceConnection<T>* pCurrent = _pConn_first;
        while (pCurrent->_pNext) {
            pCurrent = pCurrent->_pNext;
        }
        pCurrent->_pNext = prm_pResource_new;
        return;
    }
}

template<class T>
ResourceConnection<T>* ResourceManager<T>::connect(const char* prm_idstr, void* prm_connector) {
    if (prm_idstr == nullptr) {
        _TRACE3_("警告 ResourceManager<T>::connect(nullptr) [" << _manager_name << "]");
    }
    if (_is_waiting_to_connect || _is_connecting_resource) {
        _TRACE_("【警告】 ResourceManager<T>::connect() "<<_manager_name<<"は、コネクト処理中にもかかわらず、更にconnect() 要求が来たため待機が発生しました・・ 待機中("<<prm_idstr<<")");
    }
    for (int i = 0; _is_waiting_to_connect || _is_connecting_resource; i++) {
        Sleep(10);
        if (i > 10*100*60) {
            //10分以上無応答時
            _TRACE_("ResourceManager<T>::connect() "<<_manager_name<<"へ、prm_idstr="<<prm_idstr<<" が connect()しようとして、既存のコネクト処理を10分待機・・・");
            throwCriticalException("中に、connect()しているか、処理が遅すぎます。(1)");
        }
        if (i % 100 == 0) {
            _TRACE_("【警告】 ResourceManager<T>::connect() "<<_manager_name<<"は、コネクト処理中にもかかわらず、更にconnect() 要求が来たため待機が発生しました・・ 待機中("<<prm_idstr<<") 待ち時間="<<i);
        }
    }
    _is_waiting_to_connect = false;
    _is_connecting_resource = true;

    //TODO:簡易的な排他。ほぼ完璧だが完全ではない。
    ResourceConnection<T>* pObj = nullptr;
    for (int i = 0; ResourceConnection<T>::_is_closing_resource; i++) {
        _is_waiting_to_connect = true;
        Sleep(10);
        if (i > 10*100*60) {
            //１分以上無応答時
            _TRACE_("ResourceManager<T>::connect()  "<<_manager_name<<"へ、prm_idstr="<<prm_idstr<<" が connect()しようとして、既存のクローズ処理を10分待機・・・");
            throwCriticalException("中に、connect()しているか、処理が遅すぎます。(2)");
        }
        if (i % 100 == 0) {
            _TRACE_("【警告】 ResourceManager<T>::connect() "<<_manager_name<<"は、既存のクローズ処理中に、connect() 要求が来たため待機が発生しました・・ 待機中("<<prm_idstr<<") 待ち時間="<<i);
        }
    }
    //TODO:メモ
    //close()中に、別スレッドでconnect()すると。
    //シビアなタイミングでメモリを破壊する恐れが残っている、９９％大丈夫と思うのだけども！。
    //int (プリミティブ) のアトミック性を利用して排他できると安易に考えてたが、
    //スレッドセーフ完全対応しようとすると、かなりめんどくさいことが分かった。勉強になった。
    //たぶん全ての connect() 呼び出し元で connect() 失敗時の処理を定義するべきだった。
    //templateにしたのは失敗だったのか；（void*にすべきだったか）。
    //次回組む時は気をつけよう、ココは時間のあるときにちゃんやろう。そのうち；；；
    //_TRACE_(" connect to " << _manager_name<<" for "<<prm_idstr<<"...");
    pObj = find(prm_idstr);
    if (pObj == nullptr) {
        //未生成ならば生成。接続カウンタを１
        T* pResource = createResource(prm_idstr, prm_connector);
        pObj = createResourceConnection(prm_idstr, pResource);
        pObj->_num_connection = 1;
        pObj->_p_first_connector = prm_connector;
        add(pObj);
        _TRACE3_("ResourceManager<T>::connect [" << _manager_name << "]" << prm_idstr << "は無いので、新規作成して保持に決定");
        _is_connecting_resource = false;
        return pObj;
    } else {
        //生成済みならそれを返す。接続カウンタを＋１
        pObj->_num_connection++;
        _TRACE3_("ResourceManager<T>::connect [" << _manager_name << "]" << prm_idstr << "はあるので接続カウント＋１." << pObj->_num_connection);
        _is_connecting_resource = false;
        return pObj;
    }
}

template<class T>
T* ResourceManager<T>::createResource(const char* prm_idstr, void* prm_p) {
    _TRACE3_("ResourceManager<T>::createResource [" << _manager_name << "]" << prm_idstr << "を生成しましょう");
    T* p = processCreateResource(prm_idstr, prm_p);
    return p;
}

template<class T>
ResourceConnection<T>* ResourceManager<T>::createResourceConnection(const char* prm_idstr, T* prm_pResource) {
    _TRACE3_("ResourceManager<T>::createResourceConnection [" << _manager_name << "]" << prm_idstr << "を生成しましょう");
    ResourceConnection<T>* p = processCreateConnection(prm_idstr, prm_pResource);
    p->_pManager = this; //マネージャ登録
    return p;
}

template<class T>
void ResourceManager<T>::dump() {
    ResourceConnection<T>* pCurrent = _pConn_first;
    if (_pConn_first == nullptr) {
        _TRACE_(FUNC_NAME << " [" << _manager_name << "] 保持リストにはなにもありません。");
    } else {
        ResourceConnection<T>* pCurrent_next;
        while (pCurrent) {
            _TRACE_(FUNC_NAME << " [" << _manager_name << "] [" << pCurrent->_idstr << "←" << pCurrent->_num_connection << "Connection]");
            pCurrent_next = pCurrent->_pNext;
            if (pCurrent_next == nullptr) {
                pCurrent = nullptr;
                break;
            } else {
                pCurrent = pCurrent_next;
            }
        }
    }
}

//template<class T>
//int* ResourceManager<T>::getConnectionNum() {
//    ResourceConnection<T>* pCurrent = _pConn_first;
//    int n = 0;
//    while (pCurrent) {
//        n++;
//        pCurrent = pCurrent->_pNext;
//    }
//    return n;
//}


template<class T>
ResourceManager<T>::~ResourceManager() {
#ifdef MY_DEBUG
    _TRACE_(FUNC_NAME << " ["<<_manager_name<<"] begin --->");
    dump();
#endif
    ResourceConnection<T>* pCurrent = _pConn_first;
    if (_pConn_first == nullptr) {
        _TRACE3_("コネクションリストは空です。["<<_manager_name<<"]は正常に開放されるでしょう。");
    } else {
        ResourceConnection<T>* pCurrent_next;
        while (pCurrent) {
            int rnum = pCurrent->_num_connection;
            _TRACE_("【警告】["<<_manager_name<<"]に、コネクション[" << pCurrent->_idstr << "←" << rnum
                    << "Connection]が残っているので削除出来ません。close()漏れ要調査です。特別に" << rnum << "回 close() を試みます。");
//            T* r = pCurrent->peek();
            pCurrent_next = pCurrent->_pNext;
//            if (r) {
//                pCurrent->processReleaseResource(r); //リソースの解放
//            }
            for (int i = 0; i < rnum; i++) {
                _TRACE_("【警告】["<<i<<"回目] close() 今からします。pCurrent="<<(pCurrent->_idstr)<<"("<<pCurrent<<")");
                pCurrent->close(); //自殺するまで解放
                _TRACE_("【警告】["<<i<<"回目] close() 完了しました。");
            }
            if (pCurrent_next == nullptr) {
                //最後の一つ
                break;
            } else {
                pCurrent = pCurrent_next;
            }
        }
    }
#ifdef MY_DEBUG
    _TRACE_(FUNC_NAME << " ["<<_manager_name<<"] end   <---");
#endif
    GGAF_DELETEARR_NULLABLE(_manager_name);
}

}
#endif /*GGAF_CORE_RESOURCEMANAGER_H_*/
