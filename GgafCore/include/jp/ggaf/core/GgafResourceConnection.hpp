#ifndef GGAFRESOURCECONNECTION_H_
#define GGAFRESOURCECONNECTION_H_
namespace GgafCore {

/**
 * 資源接続クラス .
 * 資源(Resource)を無駄に生成を行わず、参照して使いまわしたい。しかし new するのかどうかを意識したくない。<BR>
 * そんなときに使うクラス。<BR>
 * GgafResourceManager : 資源(Resource) : GgafResourceConnection  = 1 : N : N
 * の関係で、これでワンセットです。GgafResourceConnection は言わば 資源(Resource)のラッパークラスです。
 * GgafResourceConnection実装クラスのインスタンスを、マネージャークラス(GgafResourceManager実装クラス)
 * から取得(getConnection メソッド)することとします。<BR>
 * マネージャーへの接続 GgafResourceManager<T>::getConnection で「接続カウント」が+1、
 * 本クラスのclose()で「接続カウント」が-1されます。<BR>
 * close() を呼び出すと、内部で「接続カウント」により本当に解放か否かを判断します。<BR>
 * 接続カウントが0になった場合、資源(Resource)は解放されます。
 * T には資源の型を指定してください。<BR>
 * 注意：スレッドセーフの保証は同時に２スレッドまで。３スレッド以上は正しく動作しません。
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafResourceConnection : public GgafObject {
    friend class GgafResourceManager<T>;

private:
    /** 識別名(50文字まで) */
    char* _idstr;
    /** 現在の資源マネジャーの資源に接続しているポインタ数 */
    int _num_connection;
    /** 使いまわす大事な資源 */
    T* _pResource;

    bool _is_new;

    /** close中はtrueの排他フラグ */
    static volatile bool _is_closing_resource;

protected:
    /** [r]資源マネジャー */
    GgafResourceManager<T>* _pManager;
    /** [r]次のGgafResourceConnectionへのポインタ。終端はNULL */
    GgafResourceConnection<T>* _pNext;

    /**
     * コンストラクタ<BR>
     * protected である理由は、マネジャー(GgafResourceManager<T>) が生成するため。<BR>
     * @param prm_idstr 識別名(29文字まで)
     * @param prm_pResource 使いまわす資源
     */
    GgafResourceConnection(char* prm_idstr, T* prm_pResource);

    /**
     * デストラクタ<BR>
     * protected である理由は、new と delete の強制。開放を close() 使用を強制<BR>
     */
    virtual ~GgafResourceConnection() {
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
    char* getIdStr();

    /**
     * リスト連結されている次の資源接続オブジェクトを返す .
     * 終端であった場合は NULL が返る。
     * @return 次の資源接続オブジェクト 又は、NULL
     */
    GgafResourceConnection<T>* getNext();

    /**
     * 資源を参照。 .
     * 接続カウンタは増えません<BR>
     * @return 資源へのポインタ
     */
    virtual T* use();

    bool isNew();


    int getNumConnection();



    /**
     * 資源接続を解除 .
     * 解除といってもマネージャの接続カウンタを1減らすだけです。<BR>
     * 但し、接続カウンタが 0 になれば、processReleaseResourceを呼び出し、本当に解放します。<BR>
     * @return 資源接続を解除した後の、接続カウンタ
     */
    int close();
};

/////////////////////////////////// 実装部 /////
template<class T>
volatile bool GgafResourceConnection<T>::_is_closing_resource = false;

template<class T>
char* GgafResourceConnection<T>::getIdStr() {
    return _idstr;
}

template<class T>
GgafResourceConnection<T>* GgafResourceConnection<T>::getNext() {
    return _pNext;
}

template<class T>
GgafResourceConnection<T>::GgafResourceConnection(char* prm_idstr, T* prm_pResource) : GgafObject() {
    TRACE3("GgafResourceConnection::GgafResourceConnection(prm_idstr = " <<  prm_idstr << ")");
    _is_closing_resource = false;
    _pResource = prm_pResource;
    _pNext = NULL;
    _pManager = NULL;
    _num_connection = 0;
    _is_new = false;
    _idstr = NEW char[51];
    strcpy(_idstr, prm_idstr);
}

template<class T>
T* GgafResourceConnection<T>::use() {
    return _pResource;
}
template<class T>
int GgafResourceConnection<T>::getNumConnection() {
    return _num_connection;
}

template<class T>
bool GgafResourceConnection<T>::isNew() {
    return _is_new;
}


template<class T>
int GgafResourceConnection<T>::close() {
    //close() は複数スレッドから受付を許容する。
    if ( _is_closing_resource || GgafResourceManager<T>::_is_connecting_resource) {
        _TRACE_("GgafResourceConnection<T>::close() 別のスレッドがconnect() 或いは close() 。待機が発生しました・・・・意図的ならば良いです。[" << _pManager->_manager_name << "." << _idstr << "]。")
    }

    for(int i = 0; _is_closing_resource || GgafResourceManager<T>::_is_connecting_resource; i++) {
        Sleep(1);
        if (i > 1000*60) {
            throwGgafCriticalException("GgafResourceConnection<T>::close() [" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << _num_connection << "Connection]\n"<<
                                       "現在 connect() 或いは close() 中にもかかわらず、close()しようとしてタイムアウトになりました。connect～colse のスレッドを１本にして下さい。")
        }
    }
    _is_closing_resource = true;

    if (_num_connection <= 0) {
        TRACE3("GgafResourceManager::close() [" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << _num_connection << "Connection] ＜警告＞既にコネクションは無いにもかかわらず、close() しようとしてます。");
        TRACE3("何も行なわずreturnしますが、意図的でない場合は何かがおかしいでしょう。リークの可能性が大。調査すべし！");
        return _num_connection;
    }

    GgafResourceConnection<T>* pCurrent;
    GgafResourceConnection<T>* pPrev;
    pCurrent = _pManager->_pFirstConnection;
    pPrev = NULL;
    while (pCurrent) {
        if (pCurrent == this) {
            //発見した場合
            int rnum = _num_connection;
            TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << rnum << "Connection] 発見したので開始");
            if (rnum == 1) {//最後の接続だった場合
                //死に行く宿めであるので、保持リストから離脱を行なう
                if (pCurrent->_pNext == NULL) {
                    //末尾だった
                    if (pPrev == NULL) {
                        //末尾で先頭だった（＝最後の一つ）
                        _pManager->_pFirstConnection = NULL;
                    } else {
                        //末尾で先頭でなかった
                        pPrev->_pNext = NULL;
                    }
                } else {
                    //末尾でない
                    if (pPrev == NULL) {
                        //先頭だった
                        _pManager->_pFirstConnection = pCurrent->_pNext; //先頭を次にずらす
                    } else {
                        //末尾でも先頭でもない（中間）
                        pPrev->_pNext = pCurrent->_pNext; //両隣を繋げる
                    }
                }
                TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << rnum << "Connection] 最後の参照のため解放します。");
                _num_connection = 0;
            } else if (rnum > 0) {
                TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << rnum << "Connection] まだ残ってます");
                _num_connection--;
            } else if (rnum < 0) {
                //通常ココは通らない
                _TRACE_("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << rnum
                        << "Connection] 解放しすぎ！。おかしい。どないやねん。アホー(>_<)。とりあえずスルー。");
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
        T* r = pCurrent->use();
        if (r) {
            TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "] //本当の解放 processReleaseResource[" << _idstr << "←" << _num_connection <<"]");
            pCurrent->processReleaseResource(r); //本当の解放
        }


        if (GgafResourceManager<T>::_is_waiting_to_connect) {
            //別スレッドで既にconnet()待ち状態に入っていれば開放しない。
            //これは、いずれ次の瞬間 new されることが確定しているので、無駄なdelete を行わないようにするといった意図。
            //むしろこのようにしないと、一瞬無効ポインタ状態になるので、connet()側で処理によっては落ちてしまう（と思う）。
            _is_closing_resource = false;
            return 0;
        } else {
            //別スレッドでconnet()待ち状態では無いので安心して開放するとしよう。
            _is_closing_resource = false; //thisポインタを使用していないので代入可能
            delete[] _idstr;
            delete this;
//            if (GgafResourceManager<T>::_is_waiting_to_connect) {
//                //ここに来て、connet()待ちに変わっていたら、もう諦める。
//                //現在の排他が完全ではないと考えるのは、このあたりの処理も含む
//                //TODO:完全対応には、connect()を却下する機構を作らねばならぬ。
//                _TRACE_("＜警告＞GgafResourceConnection<T>::close() delete this 中に connect() しようとしました。大丈夫でしょうか。・・・もはやどうしようも無いのですが！");
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

#endif /*GGAFRESOURCECONNECTION_H_*/
