#ifndef GgafResource_H_
#define GgafResource_H_
namespace GgafCore {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
template<class T>
class GgafResource : public GgafObject {

public:

	/** 識別名*/
	std::string	_name;
	/** 使いまわす資源 */
	T* _pResource;
	/** 資源を参照しているポインタ数 */
	int _iResourceReferenceNum;
	/** 次のGgafResourceへのポインタ。終端はNULL */
	GgafResource* _pNext;

	/**
	 * コンストラクタ<BR>
	 * @param prm_name 識別名(＝ファイル名)
	 * @param prm_pIDirect3DTexture9
	 */
	GgafResource(std::string prm_name);

	/**
	 * 参照カウンタを一つ減らす。
	 * 参照カウンタが0ならばreleaseResource()を呼び出す。
	 */
	virtual void releaseResource();

	/**
	 * 資源のRelease処理を実装
	 */
	virtual void releaseResourceProcess() = 0;

	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafResourceManagerである<BR>
	 */
	virtual ~GgafResource();		//デストラクタ
};

template<class T>
GgafResource<T>::GgafResource(std::string prm_name) : GgafObject() {
    _TRACE_("GgafResource::GgafResource(" <<  _name << ")");
    _name = prm_name;
	_pNext = NULL;
	_iResourceReferenceNum = 0;
}

template<class T>
void GgafResource<T>::releaseResource() {
	_iResourceReferenceNum--;
	if (_iResourceReferenceNum <= 0) {
		releaseResourceProcess();
	}
}

template<class T>
GgafResource<T>::~GgafResource() {
	_TRACE_("GgafResource::~GgafResource() " <<  _name << " start-->");
	_TRACE_("GgafResource::~GgafResource() " <<  _name << " <--end");
}

}

#endif /*GgafResource_H_*/
