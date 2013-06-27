#ifndef GGAFRESOURCEMANAGER_H_
#define GGAFRESOURCEMANAGER_H_
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

namespace GgafCore {

/**
 * 資源管理クラス。 .
 * 資源管理クラスは、資源をラッピングした『資源接続オブジェクト(GgafResourceConnection)』を管理します。<BR>
 * 資源(Resource)を無駄に生成を行わず、参照して使いまわしたい。しかし new するのかどうかを意識したくない。<BR>
 * そんなときに使うクラスです。<BR>
 * GgafResourceManager : Resource : GgafResourceConnection  = 1 : N : N <BR>
 * の関係で、これでワンセットです。<BR>
 * 資源管理クラスは主な機能は、資源接続クラスのインスタンス（のポインタ）を内部にリストで保持し、取得要求があった場合、
 * 内部保持していればそれを返し、保持していなければ生成して、リストに追加した後それを返します。
 * 注意：スレッドセーフの保証は同時に２スレッドまで。３スレッド以上は正しく動作しません。
 * (旧GdxfwActorManagerから汎用化)
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafResourceManager : public GgafObject {
    friend class GgafResourceConnection<T>;

private:
    /**
     * GgafResourceConnectionオブジェクトをリストに追加。<BR>
     * @param prm_pNew 追加するGgafResourceConnectionオブジェクトのポインタ
     */
    virtual void add(GgafResourceConnection<T>* prm_pNew);

    /**
     * GgafResourceConnectionオブジェクトをリストから検索。<BR>
     * @param prm_idstr 識別名
     * @return  所望のGgafResourceConnectionオブジェクトのポインタ。リストに存在しなかった場合 nullptr
     */
    virtual GgafResourceConnection<T>* find(char* prm_idstr);

    /**
     * 資源のを生成する .
     * connect() 時、資源が実生成場合呼び出されます。
     * processCreateResource(char*, void*) をコールします。
     * @param prm_idstr connect() で渡された識別名
     * @param prm_p connect() で渡された自由パラメータ
     */
    T* createResource(char* prm_idstr, void* prm_p);

    /**
     * 資源接続オブジェクトを生成.
     * @param prm_idstr 識別名
     * @param prm_pResource 資源接続オブジェクトのValue。つまり資源インスタンス。
     * @return 資源接続オブジェクト
     */
    GgafResourceConnection<T>* createResourceConnection(char* prm_idstr, T* prm_pResource);

protected:
    /** connect中はtrueの排他フラグ */
    static volatile bool _is_connecting_resource;
    /** connectするために待っているフラグ */
    static volatile bool _is_waiting_to_connect;
    /** [r]マネージャ名称 */
    const char* _manager_name;
    /** [r]GgafResourceConnectionオブジェクトのリストの先頭のポインタ。終端はnullptr */
    GgafResourceConnection<T>* _pConn_first;

protected:
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
     * 実際の資源のを生成を下位で実装します。.
     * このメソッドは createResource から呼び出され、本テンプレート利用者が実装する必要があります。<BR>
     * prm_idstr から 資源を生成するロジックを実装してく下さい。<BR>
     * @param prm_idstr この識別名が渡された時、どういう資源を生成(new)するか？ という識別名
     * @param prm_p 自由パラメータ
     * @return 資源インスタンスのポインタ
     */
    virtual T* processCreateResource(char* prm_idstr, void* prm_pConnector) = 0;

//    int GgafResourceManager<T>::getConnectionNum();

public:
    /**
     * コンストラクタ
     */
    GgafResourceManager(const char* prm_manager_name);

    /**
     * デストラクタ。保持リストを強制解放します。 .
     * 全ての保持リストの GgafResourceConnectionに対し、GgafResourceConnectionのrelease()を１度実行し、<BR>
     * GgafResourceConnectionの接続カウンタ0ならば、delete します。<BR>
     * GgafResourceConnectionの接続カウンタ0でなければ、使用者のロジックで解放漏れの恐れがあるので
     * 一言喋って delete します。<BR>
     */
    virtual ~GgafResourceManager();

    /**
     * 資源接続(GgafResourceConnection)オブジェクトを取得。<BR>
     * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
     * 保持リストから取得した場合、接続カウンタが増えます。<BR>
     * new した場合、接続カウンタは1です。<BR>
     * @param prm_idstr 識別名
     * @param prm_connector 接続元、thisを渡して下さい。
     * @return 識別名に紐付く資源接続(GgafResourceConnection)
     */
    virtual GgafResourceConnection<T>* connect(char* prm_idstr, void* prm_connector);

//    /**
//     * 資源接続(GgafResourceConnection)オブジェクトを取得。<BR>
//     * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
//     * 保持リストから取得した場合、接続カウンタが増えます。<BR>
//     * new した場合、接続カウンタは1です。<BR>
//     * @param prm_idstr 識別名
//     * @return 識別名に紐付く資源接続(GgafResourceConnection)
//     */
//    virtual GgafResourceConnection<T>* connect(char* prm_idstr) {
//        return this->connect(prm_idstr, nullptr);
//    }
//
//    /**
//     * 資源接続(GgafResourceConnection)オブジェクトを取得。<BR>
//     * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
//     * 保持リストから取得した場合、接続カウンタが増えます。<BR>
//     * new した場合、接続カウンタは1です。<BR>
//     * @param prm_idstr 識別名
//     * @return 識別名に紐付く資源接続(GgafResourceConnection)
//     */
//    virtual GgafResourceConnection<T>* connect(const char* prm_idstr) {
//        return this->connect((char*)prm_idstr, nullptr);
//    }

    /**
     * 資源接続(GgafResourceConnection)オブジェクトを取得。<BR>
     * 保持リストに存在すればそれを返し、存在しなければ new します。<BR>
     * 保持リストから取得した場合、接続カウンタが増えます。<BR>
     * new した場合、接続カウンタは1です。<BR>
     * @param prm_idstr 識別名
     * @param prm_p 何らかの引数
     * @return 識別名に紐付く資源接続(GgafResourceConnection)
     */
    virtual GgafResourceConnection<T>* connect(const char* prm_idstr, void* prm_p) {
        return this->connect((char*)prm_idstr, prm_p);
    }

    /**
     * マネジャーが保持するリストを出力します。（デバッグ用） .
     */
    virtual void dump();
};

// ---------------------------------------------------------------------//


template<class T>
volatile bool GgafResourceManager<T>::_is_connecting_resource = false;

template<class T>
volatile bool GgafResourceManager<T>::_is_waiting_to_connect = false;

template<class T>
GgafResourceManager<T>::GgafResourceManager(const char* prm_manager_name) : GgafObject(),
      _manager_name(prm_manager_name) {
    TRACE3("GgafResourceManager<T>::GgafResourceManager(" << prm_manager_name << ")");
    _pConn_first = nullptr;
    _is_connecting_resource = false;
    _is_waiting_to_connect = false;
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::find(char* prm_idstr) {
    GgafResourceConnection<T>* pCurrent = _pConn_first;

    while (pCurrent) {
        //_TRACE_("pCurrent->_idstr -> "<<(pCurrent->_idstr)<<" prm_idstr="<<prm_idstr);
        if (UTIL::strcmp_ascii(pCurrent->_idstr, prm_idstr) == 0) {
            return pCurrent;
        }
        pCurrent = pCurrent->_pNext;
    }
    return nullptr;
}

template<class T>
void GgafResourceManager<T>::add(GgafResourceConnection<T>* prm_pResource_new) {
    if (_pConn_first == nullptr) {
        _pConn_first = prm_pResource_new;
        return;
    } else {
        GgafResourceConnection<T>* pCurrent = _pConn_first;
        while (pCurrent->_pNext) {
            pCurrent = pCurrent->_pNext;
        }
        pCurrent->_pNext = prm_pResource_new;
        return;
    }
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::connect(char* prm_idstr, void* prm_connector) {
    if (prm_idstr == nullptr) {
        TRACE3("警告 GgafResourceManager<T>::connect(nullptr) [" << _manager_name << "]");
    }
    if (_is_waiting_to_connect || _is_connecting_resource) {
        _TRACE_("GgafResourceManager<T>::connect() "<<_manager_name<<"は、コネクト処理中です。待機が発生しました・・ 待機中("<<prm_idstr<<")");
    }
    for(int i = 0; _is_waiting_to_connect || _is_connecting_resource; i++) {
        Sleep(10);
        if (i > 10*100*60) {
            //10分以上無応答時
            _TRACE_("GgafResourceManager<T>::connect() "<<_manager_name<<"へ、prm_idstr="<<prm_idstr<<" が connect()しようとして、既存のコネクト処理を10分待機・・・");
            throwGgafCriticalException("GgafResourceManager<T>::connect()  "<<_manager_name<<"へ、prm_idstr="<<prm_idstr<<" が connect()しようとして、既存のコネクト処理を10分待機。connect() 中に、connect()しているか、処理が遅すぎます。(1)");
        }
    }
    _is_waiting_to_connect = false;
    _is_connecting_resource = true;

    //TODO:簡易的な排他。ほぼ完璧だが完全ではない。
    GgafResourceConnection<T>* pObj = nullptr;
    for(int i = 0; GgafResourceConnection<T>::_is_closing_resource; i++) {
        _is_waiting_to_connect = true;
        Sleep(10);
        if (i > 10*100*60) {
            //１分以上無応答時
            _TRACE_("GgafResourceManager<T>::connect()  "<<_manager_name<<"へ、prm_idstr="<<prm_idstr<<" が connect()しようとして、既存のクローズ処理を10分待機・・・");
            throwGgafCriticalException("GgafResourceManager<T>::connect()  "<<_manager_name<<"へ、prm_idstr="<<prm_idstr<<" が  connect()しようとして、既存のクローズ処理を10分待機。connect() 中に、connect()しているか、処理が遅すぎます。(2)");
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
        pObj->_first_connector = prm_connector;
        add(pObj);
        TRACE3("GgafResourceManager<T>::connect [" << _manager_name << "]" << prm_idstr << "は無いので、新規作成して保持に決定");
        _is_connecting_resource = false;
        return pObj;
    } else {
        //生成済みならそれを返す。接続カウンタを＋１
        pObj->_num_connection++;
        TRACE3("GgafResourceManager<T>::connect [" << _manager_name << "]" << prm_idstr << "はあるので接続カウント＋１." << pObj->_num_connection);
        _is_connecting_resource = false;
        return pObj;
    }
}

template<class T>
T* GgafResourceManager<T>::createResource(char* prm_idstr, void* prm_p) {
    TRACE3("GgafResourceManager<T>::createResource [" << _manager_name << "]" << prm_idstr << "を生成しましょう");
    T* p = processCreateResource(prm_idstr, prm_p);
    return p;
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
    GgafResourceConnection<T>* pCurrent = _pConn_first;
    if (_pConn_first == nullptr) {
        _TRACE_("GgafResourceManager::dump[" << _manager_name << "] 保持リストにはなにもありません。");
    } else {
        GgafResourceConnection<T>* pCurrent_next;
        while (pCurrent) {
            _TRACE_("GgafResourceManager::dump[" << _manager_name << "] [" << pCurrent->_idstr << "←" << pCurrent->_num_connection << "Connection]");
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
//int* GgafResourceManager<T>::getConnectionNum() {
//    GgafResourceConnection<T>* pCurrent = _pConn_first;
//    int n = 0;
//    while (pCurrent) {
//        n++;
//        pCurrent = pCurrent->_pNext;
//    }
//    return n;
//}


template<class T>
GgafResourceManager<T>::~GgafResourceManager() {
    TRACE3("GgafResourceManager<T>::~GgafResourceManager[" << _manager_name << "] " << _manager_name << " ");
#ifdef MY_DEBUG
    _TRACE_("GgafResourceManager<T>::~GgafResourceManager()["<<_manager_name<<"] begin --->");
    _TRACE_("＜解放前Dumping＞");
    dump();
#endif
    GgafResourceConnection<T>* pCurrent = _pConn_first;
    if (_pConn_first == nullptr) {
        TRACE3("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] 保持リストにはなにもありません。");
    } else {
        GgafResourceConnection<T>* pCurrent_next;
        while (pCurrent) {
            int rnum = pCurrent->_num_connection;
            _TRACE_("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] 保持リストに[" << pCurrent->_idstr << "←" << rnum
                    << "Connection]が残ってます。強制削除しますが、本来あってはいけません。特別に" << rnum << "回 close()を発行します");
//            T* r = pCurrent->peek();
            pCurrent_next = pCurrent->_pNext;
//            if (r) {
//                pCurrent->processReleaseResource(r); //リソースの解放
//            }
            for (int i = 0; i < rnum; i++) {
                pCurrent->close(); //自殺するまで解放
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
    _TRACE_("<--- GgafResourceManager<T>::~GgafResourceManager() ["<<_manager_name<<"] end");
#endif
}

}
#endif /*GGAFRESOURCEMANAGER_H_*/
