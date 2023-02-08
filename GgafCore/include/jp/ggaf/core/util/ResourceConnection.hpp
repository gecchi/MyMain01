#ifndef GGAF_CORE_RESOURCECONNECTION_H_
#define GGAF_CORE_RESOURCECONNECTION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"
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
 * 資源接続クラス .
 * 資源(Resource)を無駄に生成を行わず、参照して使いまわしたい。しかし new するのかどうかを意識したくない。<BR>
 * そんなときに使うクラス。簡単にいえばCOMオブジェクトの簡易版といったところか。<BR>
 * ResourceManager : 資源(Resource) : ResourceConnection  = 1 : N : N
 * の関係で、これでワンセットです。ResourceConnection は言わば 資源(Resource)のラッパークラスです。
 * ResourceConnection実装クラスのインスタンスを、マネージャークラス(ResourceManager実装クラス)
 * から取得(getConnection メソッド)することとします。<BR>
 * マネージャーへの接続 ResourceManager<T>::getConnection で「接続カウント」が+1、
 * 本クラスのclose()で「接続カウント」が-1されます。<BR>
 * close() を呼び出すと、内部で「接続カウント」により本当に解放か否かを判断します。<BR>
 * 接続カウントが0になった場合、資源(Resource)は解放されます。
 * T には資源の型を指定してください。<BR>
 * 注意：スレッドセーフの保証は同時に２スレッドまで。３スレッド以上は正しく動作しません。<BR>
 * 注意：最終close()時の解放で、正しくデストラクタを呼び出す為に、T のクラスヘッダの include を忘れずに！！<BR>
 * @tparam T 資源の型（この型のポインタ型が内部で管理される。）
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
template<class T>
class ResourceConnection : public Object {
    friend class ResourceManager<T>;

private:
    /** 識別名(50文字まで) */
    char* _idstr;
    /** 現在の資源マネジャーの資源に接続しているポインタ数 */
    int _num_connection;
    /** 使いまわす資源へのポインタ */
    T* _pResource;
    /** 初めての接続元 */
    void* _p_first_connector;


#ifdef _MSC_VER
    //TODO:VC++2005以降(x86) の volatile は、メモリバリア効果がある（と思う）。
    //gcc(x86)は、アトミック保証は無いが std::atomic が使える。VC++に atomic が実装されるまではとりあえず・・・。
    /** close中はtrueの排他フラグ */
    static volatile bool _is_closing_resource;
#else
    /** close中はtrueの排他フラグ */
    static volatile std::atomic<bool> _is_closing_resource;
#endif

protected:
    /** [r]資源マネジャー */
    ResourceManager<T>* _pManager;
    /** [r]次のResourceConnectionへのポインタ。終端はnullptr */
    ResourceConnection<T>* _pNext;

protected:
    /**
     * コンストラクタ<BR>
     * protected である理由は、マネジャー(ResourceManager<T>) が生成するため。<BR>
     * @param prm_idstr 識別名(29文字まで)
     * @param prm_pResource 使いまわす資源
     */
    ResourceConnection(const char* prm_idstr, T* prm_pResource);

    /**
     * デストラクタ<BR>
     * protected である理由は、new と delete の強制。開放を close() 使用を強制<BR>
     */
    virtual ~ResourceConnection() {
    }

    /**
     * 資源の実際の解放処理。
     * delete や Release など、その資源に応じた実際の解放を実装して下さい。
     * @param prm_pResource
     */
    virtual void processReleaseResource(T* prm_pResource)= 0;

public:
    /**
     * 識別名を返す .
     * @return 識別名
     */
    char* getIdStr() const ;

    /**
     * リスト連結されている次の資源接続オブジェクトを返す .
     * 終端であった場合は nullptr が返る。
     * @return 次の資源接続オブジェクト 又は、nullptr
     */
    ResourceConnection<T>* getNext() const;

    /**
     * コネクション先の資源を取得 .
     * 接続カウンタは増えません<BR>
     * @return 資源へのポインタ
     */
    inline T* peek() const {
        return _pResource;
    }

    /**
     * 引数のポインタのオブジェクトが、初めてのコネクションオブジェクトかどうか調べる。 .
     * @param prm_this 調べるオブジェクト。thisを渡して下さい。
     * @return true:初めてconnectした(=resourceを new した）オブジェクトである。/false:そうではない。
     */
    bool chkFirstConnectionIs(void* prm_this) const;

    /**
     * 資源(Resource)への接続数を取得 .
     * @return 資源(Resource)への接続数
     */
    int getNumConnection() const;

    /**
     * 資源接続を解除 .
     * 解除といってもマネージャの接続カウンタを1減らすだけです。<BR>
     * 但し、接続カウンタが 0 になれば、processReleaseResourceを呼び出し、本当に解放します。<BR>
     * COMで言うところの Release() にあたる。
     * @return 資源接続を解除した後の、接続カウンタ
     */
    int close();

};

/////////////////////////////////// 実装部 /////
#ifdef _MSC_VER
template<class T>
volatile bool ResourceConnection<T>::_is_closing_resource = false;
#else
template<class T>
volatile std::atomic<bool> ResourceConnection<T>::_is_closing_resource(false);
#endif

template<class T>
char* ResourceConnection<T>::getIdStr() const {
    return _idstr;
}

template<class T>
ResourceConnection<T>* ResourceConnection<T>::getNext() const {
    return _pNext;
}

template<class T>
ResourceConnection<T>::ResourceConnection(const char* prm_idstr, T* prm_pResource) : Object() {
    _TRACE3_("prm_idstr="<<prm_idstr);
    _pResource = prm_pResource;
    _pNext = nullptr;
    _pManager = nullptr;
    _num_connection = 0;
    _p_first_connector = nullptr;

    int len = strlen(prm_idstr);
    _idstr = NEW char[len+1];
    strcpy(_idstr, prm_idstr);

}

template<class T>
int ResourceConnection<T>::getNumConnection() const {
    return _num_connection;
}

template<class T>
bool ResourceConnection<T>::chkFirstConnectionIs(void* prm_this) const {
    if (_p_first_connector == prm_this) {
        return true;
    } else {
        return false;
    }
}


template<class T>
int ResourceConnection<T>::close() {
    //close() は複数スレッドから受付を許容する。
    if ( _is_closing_resource || ResourceManager<T>::_is_connecting_resource) {
        _TRACE_("【警告】 ResourceConnection<T>::close() 別のスレッドがconnect() 或いは close() 。待機が発生しました・・・・意図的ならば良いです。[" << _pManager->_manager_name << "(" << _idstr << ")" << "]。");
    }

    for (int i = 0; _is_closing_resource || ResourceManager<T>::_is_connecting_resource; i++) {
        Sleep(10);
        if (i > 100*60) {
            throwCriticalException("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << " \n"
                                       "現在 connect() 或いは close() 中にもかかわらず、close()しようとしてタイムアウトになりました。connect～colse のスレッドを１本にして下さい。");
        }
        if (i % 100 == 0) {
            _TRACE_("【警告】 ResourceConnection<T>::close() 別のスレッドがconnect() 或いは close() 中に、さらにclose()要求がきたため待機。[" << _pManager->_manager_name << "(" << _idstr << ")" << "]。待ち時間="<<i);
        }
    }
    _is_closing_resource = true;

    if (_num_connection <= 0) {
        _TRACE_("【警告】 [" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  既にコネクションは無いにもかかわらず、close() しようとしてます。");
        _TRACE_("【警告】何も行なわずreturnしますが、意図的でない場合は何かがおかしいでしょう。リークの可能性が大。調査すべし！");
        return _num_connection;
    }

    ResourceConnection<T>* pCurrent = _pManager->_pConn_first;
    ResourceConnection<T>* pPrev = nullptr;
    while (pCurrent) {
        if (pCurrent == this) {
            //発見した場合
            int rnum = _num_connection;
            _TRACE3_("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  発見したので開始");
            if (rnum == 1) {//最後の接続だった場合
                //死に行く宿めであるので、保持リストから離脱を行なう
                if (pCurrent->_pNext == nullptr) {
                    //末尾だった
                    if (pPrev == nullptr) {
                        //末尾で先頭だった（＝最後の一つ）
                        _pManager->_pConn_first = nullptr;
                    } else {
                        //末尾で先頭でなかった
                        pPrev->_pNext = nullptr;
                    }
                } else {
                    //末尾でない
                    if (pPrev == nullptr) {
                        //先頭だった
                        _pManager->_pConn_first = pCurrent->_pNext; //先頭を次にずらす
                    } else {
                        //末尾でも先頭でもない（中間）
                        pPrev->_pNext = pCurrent->_pNext; //両隣を繋げる
                    }
                }
                _TRACE3_("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  最後の参照のため解放します。");
                _num_connection = 0;
            } else if (rnum > 0) {
                _TRACE3_("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  まだ残ってます");
                _num_connection--;
            } else if (rnum < 0) {
                //ココは通らない・・・
                _TRACE_("【警告】"<<FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  "
                        "解放しすぎ！、どないやねん。アホー(>_<)。とりあえずスルー。");
                _num_connection = 0; //とりあえず解放
            }
            break;
        } else {
            //違った場合
            pPrev = pCurrent;
            pCurrent = pCurrent->_pNext;
        }
    }

    if (_num_connection == 0) {
        T* r = pCurrent->peek();
        if (r) {
            _TRACE_(FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection <<" processReleaseResource() Begin.");
            pCurrent->processReleaseResource(r); //本当の解放
            _TRACE_(FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection <<" processReleaseResource() Done.");
        }

        if (ResourceManager<T>::_is_waiting_to_connect) {
            //別スレッドで既にconnet()待ち状態に入っていれば開放しない。
            //これは、いずれ次の瞬間 new されることが確定しているので、無駄なdelete を行わないようにするといった意図。
            //むしろこのようにしないと、一瞬無効ポインタ状態になるので、connet()側で処理によっては落ちてしまう（と思う）。
            _is_closing_resource = false;
            return 0;
        } else {
            //別スレッドでconnet()待ち状態が無いので、安心して開放するとしよう。
            _is_closing_resource = false; //thisポインタを使用していないので代入可能
            _TRACE_(FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "] Now, delete this !!!");
            delete[] _idstr;
            delete this;     //こんなことが出来るんですね！。
//            if (ResourceManager<T>::_is_waiting_to_connect) {
//                //ここに来て、connet()待ちに変わっていたら、もう諦める。
//                //現在の排他が完全ではないと考えるのは、このあたりの処理も含む
//                //TODO:完全対応には、connect()を却下する機構を作らねばならぬ。
//                _TRACE_("【警告】ResourceConnection<T>::close() delete this 中に connect() しようとしました。大丈夫でしょうか。・・・もはやどうしようも無いのですが！");
//            }
//            _is_closing_resource = false; //thisポインタを使用していないので代入可能
            return 0;
        }
    } else {
        _is_closing_resource = false;
        return _num_connection;
    }
}

}

#endif /*GGAF_CORE_RESOURCECONNECTION_H_*/
