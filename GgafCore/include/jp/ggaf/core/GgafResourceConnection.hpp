#ifndef GGAFRESOURCECONNECTION_H_
#define GGAFRESOURCECONNECTION_H_
namespace GgafCore {

/**
 * 資源接続クラス .
 * 無駄な資源の生成を行わず、参照して使いまわしたいがゆえ、開放時期を簡単にするためのクラス。<BR>
 * GgafResourceConnection実装クラスのインスタンスを、マネージャークラス(GgafResourceManager実装クラス)
 * から取得(getConnection メソッド)することとします。<BR>
 * 内部で接続カウンタにより開放か否かを判断したいためです。<BR>
 * マネージャーから取得で接続カウントが+1、本クラスのReleaseで接続カウントが-1されます。<BR>
 * 接続カウントが0になった場合、資源(Resource)は開放されます。
 * T には資源の型を指定してください。<BR>
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

protected:
    /** 資源マネジャー */
    GgafResourceManager<T>* _pManager;
    /** 次のGgafResourceConnectionへのポインタ。終端はNULL */
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
     * protected である理由は、delete を this->Release() のみでに限定したため<BR>
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
    virtual T* view();

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
char* GgafResourceConnection<T>::getIdStr() {
    return _idstr;
}

template<class T>
GgafResourceConnection<T>* GgafResourceConnection<T>::getNext() {
    return _pNext;
}


template<class T>
GgafResourceConnection<T>::GgafResourceConnection(char* prm_idstr, T* prm_pResource) : GgafObject() {
    TRACE("GgafResourceConnection::GgafResourceConnection([" << _pManager->_manager_name << "." << prm_idstr << "])");
    _pResource = prm_pResource;
    _pNext = NULL;
    _pManager = NULL;
    _num_connection = 0;
    _idstr = NEW char[51];
    strcpy(_idstr, prm_idstr);
}

template<class T>
T* GgafResourceConnection<T>::view() {
    return _pResource;
}

template<class T>
int GgafResourceConnection<T>::close() {
    if (_num_connection <= 0) {
        TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << _num_connection << "Connection] ＜警告＞既にコネクションは無いにもかかわらず、close() しようとしてます。");
        TRACE3("何も行なわずreturnしますが、意図的でない場合は何かがおかしいでしょう。リークの可能\性が大。調査すべし！");
        return _num_connection;
    }

    GgafResourceConnection<T>* pCurrent;
    GgafResourceConnection<T>* pPrev;
    pCurrent = _pManager->_pFirstConnection;
    pPrev = NULL;
    while (pCurrent != NULL) {
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
                TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "←" << rnum
                        << "Connection] 解放しすぎ(><)。作者のアホー。どないするのん。ありえません。");
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
        T* r = pCurrent->view();
        if (r != NULL) {
            TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "] //本当の解放 processReleaseResource[" << _idstr << "←" << _num_connection <<"]");
            pCurrent->processReleaseResource(r); //本当の解放
        }
        delete[] _idstr;
        delete this;
        return 0;
    } else {
        return _num_connection;
    }
}

}

#endif /*GGAFRESOURCECONNECTION_H_*/
