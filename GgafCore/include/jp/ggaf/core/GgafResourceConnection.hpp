#ifndef GGAFRESOURCECONNECTION_H_
#define GGAFRESOURCECONNECTION_H_
namespace GgafCore {

/**
 * 資源(Resource)アクセッサ.
 * 無駄な資源(Resource)の生成を行わず、参照して使いまわしたいがゆえ、開放時期を簡単にするためのクラス。<BR>
 * GgafResourceConnection実装クラスのインスタンスを、マネージャークラス(GgafResourceManager実装クラス)
 * から取得することとします。<BR>
 * 内部で参照カウンタにより開放か否かを判断したいためです。<BR>
 * マネージャーから取得で参照カウントが+1、本クラスのReleaseで参照カウントが-1されます。<BR>
 * 参照カウントが0になった場合、資源(Resource)は開放されます。
 * T には資源を指定してください。<BR>
 */
template<class T>
class GgafResourceConnection : public GgafObject {
protected:
    /**
     * デストラクタ<BR>
     * protected である理由は、delete を this->Release() のみでに限定したため<BR>
     */
    virtual ~GgafResourceConnection() {
    } //デストラクタ

public:
    GgafResourceManager<T>* _pManager;

    /** 識別名(50文字まで) */
    char* _idstr;
    /** 使いまわす資源 */
    T* _pResource;
    /** 資源を参照しているポインタ数 */
    int _num_connection;
    /** 次のGgafResourceConnectionへのポインタ。終端はNULL */
    GgafResourceConnection* _pNext;

    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名(29文字まで)
     * @param prm_pResource 使いまわす資源
     * @param prm_pIDirect3DTexture9
     */
    GgafResourceConnection(char* prm_idstr, T* prm_pResource);

    /**
     * 資源のポインタを取得。
     * 参照カウンタは増えません<BR>
     */
    virtual T* view();

    /**
     * 資源を解放
     * 参照カウンタを1減らし、0になれば本当に開放します。
     */
    int close();

    /**
     * 資源の実際のリリース処理を実装します。
     * @param prm_pResource
     */
    virtual void processReleaseResource(T* prm_pResource)= 0;

};

template<class T>
GgafResourceConnection<T>::GgafResourceConnection(char* prm_idstr, T* prm_pResource) : GgafObject() {
    TRACE("GgafResourceConnection::GgafResourceConnection(" << prm_idstr << ")");
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

    GgafResourceConnection<T>* pCurrent;
    GgafResourceConnection<T>* pPrev;
    pCurrent = _pManager->_pTop;
    pPrev = NULL;
    while (pCurrent != NULL) {
        if (pCurrent == this) {
            //発見した場合
            int rnum = _num_connection;
            TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "←" << rnum << "Connection] 発見したので開始");

            if (rnum == 1) {//最後の参照だった場合
                //死に行く宿めであるので、保持リストから離脱を行なう
                if (pCurrent->_pNext == NULL) {
                    //末尾だった
                    if (pPrev == NULL) {
                        //末尾で先頭だった（＝最後の一つ）
                        _pManager->_pTop = NULL;
                    } else {
                        //末尾で先頭でなかった
                        pPrev->_pNext = NULL;
                    }
                } else {
                    //末尾でない
                    if (pPrev == NULL) {
                        //先頭だった
                        _pManager->_pTop = pCurrent->_pNext; //先頭を次にずらす
                    } else {
                        //末尾でも先頭でもない（中間）
                        pPrev->_pNext = pCurrent->_pNext; //両隣を繋げる
                    }
                }
                TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "←" << rnum << "Connection] 最後の参照のため解放します。");
                _num_connection = 0;
            } else if (rnum > 0) {
                TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "←" << rnum << "Connection] まだ残ってます");
                _num_connection--;
            } else if (rnum < 0) {
                TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "←" << rnum
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
