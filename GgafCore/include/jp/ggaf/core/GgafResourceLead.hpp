#ifndef GGAFRESOURCELEAD_H_
#define GGAFRESOURCELEAD_H_
namespace GgafCore {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
template<class T>
class GgafResourceLead : public GgafObject {
protected:
	/**
	 * デストラクタ<BR>
	 * protected である理由は、delete を this->Release() のみでに限定したため<BR>
	 */
	virtual ~GgafResourceLead() {};		//デストラクタ

public:
	GgafResourceManager<T>* _pManager;

	/** 識別名(50文字まで) */
	char* _idstr;
	/** 使いまわす資源 */
	T* _pResource;
	/** 資源を参照しているポインタ数 */
	int _iLeadNum;
	/** 次のGgafResourceLeadへのポインタ。終端はNULL */
	GgafResourceLead* _pNext;

	/**
	 * コンストラクタ<BR>
	 * @param prm_idstr 識別名(29文字まで)
	 * @param prm_pResource 使いまわす資源
	 * @param prm_pIDirect3DTexture9
	 */
	GgafResourceLead(char* prm_idstr, T* prm_pResource);

	/**
	 * 資源を取得。
	 * 参照カウンタは増えません
	 */
	virtual T* getResource();



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
GgafResourceLead<T>::GgafResourceLead(char* prm_idstr, T* prm_pResource) : GgafObject() {
	_TRACE_("GgafResourceLead::GgafResourceLead(" <<  prm_idstr << ")");
    _pResource = prm_pResource;
	_pNext = NULL;
	_pManager = NULL;
	_iLeadNum = 0;
	_idstr = new char[51];
	strcpy(_idstr, prm_idstr);
}

template<class T>
T* GgafResourceLead<T>::getResource() {
	return _pResource;
}

template<class T>
int GgafResourceLead<T>::Release() {

	GgafResourceLead<T>* pCurrent;
	GgafResourceLead<T>* pPrev;
	pCurrent = _pManager->_pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent == this) {
			//発見した場合
			int rnum = _iLeadNum;
			_TRACE_("GgafResourceManager::releaseResourceLead[" << _idstr << "←" << rnum << "Lead] 発見したので開始");

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
				_TRACE_("GgafResourceManager::releaseResourceLead["<<_idstr<<"←"<<rnum<<"Lead] 最後の参照のため解放します。");
				_iLeadNum = 0;
			} else if (rnum > 0) {
				_TRACE_("GgafResourceManager::releaseResourceLead["<<_idstr<<"←"<<rnum<<"Lead] まだ残ってます");
				_iLeadNum--;
			} else if (rnum < 0) {
				_TRACE_("GgafResourceManager::releaseResourceLead["<<_idstr<<"←"<<rnum<<"Lead] 解放しすぎ(><)。作者のアホー。どないするのん。ありえません。");
				_iLeadNum = 0; //とりあえず解放
			}
			break;
		} else {
			//違った場合
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}

	if (_iLeadNum == 0) {
		T* r = pCurrent->getResource();
		if (r != NULL) {
			pCurrent->processReleaseResource(r); //本当の解放
		}
		delete[] _idstr;
		delete this;
		return 0;
	} else {
		return _iLeadNum;
	}
}


}

#endif /*GGAFRESOURCELEAD_H_*/
