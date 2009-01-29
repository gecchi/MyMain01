#ifndef GGAFRESOURCECONNECTION_H_
#define GGAFRESOURCECONNECTION_H_
namespace GgafCore {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
template<class T>
class GgafResourceConnection : public GgafObject {
protected:
	/**
	 * デストラクタ<BR>
	 * protected である理由は、delete を this->Release() のみでに限定したため<BR>
	 */
	virtual ~GgafResourceConnection() {};		//デストラクタ

public:
	GgafResourceManager<T>* _pManager;

	/** 識別名*/
	std::string	_idstr;
	/** 使いまわす資源 */
	T* _pResource;
	/** 資源を参照しているポインタ数 */
	int _iConnectionNum;
	/** 次のGgafResourceConnectionへのポインタ。終端はNULL */
	GgafResourceConnection* _pNext;

	/**
	 * コンストラクタ<BR>
	 * @param prm_idstr 識別名
	 * @param prm_pResource 使いまわす資源
	 * @param prm_pIDirect3DTexture9
	 */
	GgafResourceConnection(std::string prm_idstr, T* prm_pResource);

	/**
	 * 資源を取得。
	 * 参照カウンタは増えません
	 */
	virtual T* get();



	/**
	 * 資源を解放
	 */
	int Release();


	/**
	 * 資源の実際のリリース処理を実装します。
	 * @param prm_pResource
	 */
	virtual void processReleaseResource(T* prm_pResource)= 0;

};

template<class T>
GgafResourceConnection<T>::GgafResourceConnection(std::string prm_idstr, T* prm_pResource) : GgafObject() {
    _TRACE_("GgafResourceConnection::GgafResourceConnection(" <<  _idstr << ")");
    _idstr = prm_idstr;
    _pResource = prm_pResource;
	_pNext = NULL;
	_pManager = NULL;
	_iConnectionNum = 0;
}

template<class T>
T* GgafResourceConnection<T>::get() {
	return _pResource;
}

template<class T>
int GgafResourceConnection<T>::Release() {

	GgafResourceConnection<T>* pCurrent;
	GgafResourceConnection<T>* pPrev;
	pCurrent = _pManager->_pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent == this) {
			//発見した場合
			int rnum = _iConnectionNum;
			_TRACE_("GgafResourceManager::releaseResourceConnection["<<_idstr<<"←"<<rnum<<"Objects] 発見したので開始");

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
				_TRACE_("GgafResourceManager::releaseResourceConnection["<<_idstr<<"←"<<rnum<<"Objects] 最後の参照のため解放します。");
				_iConnectionNum = 0;
			} else if (rnum > 0) {
				_TRACE_("GgafResourceManager::releaseResourceConnection["<<_idstr<<"←"<<rnum<<"Objects] まだ残ってます");
				_iConnectionNum--;
			} else if (rnum < 0) {
				_TRACE_("GgafResourceManager::releaseResourceConnection["<<_idstr<<"←"<<rnum<<"Objects] 解放しすぎ(><)。作者のアホー。どないするのん。ありえません。");
				_iConnectionNum = 0; //とりあえず解放
			}
			break;
		} else {
			//違った場合
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}

	if (_iConnectionNum == 0) {
		T* r = pCurrent->get();
		if (r != NULL) {
			pCurrent->processReleaseResource(r); //本当の解放
		}
		delete this;
		return 0;
	} else {
		return _iConnectionNum;
	}
}


}

#endif /*GGAFRESOURCECONNECTION_H_*/
