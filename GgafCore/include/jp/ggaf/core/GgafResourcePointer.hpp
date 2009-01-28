#ifndef GGAFRESOURCEPOINTER_H_
#define GGAFRESOURCEPOINTER_H_
namespace GgafCore {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
template<class T>
class GgafResourcePointer : public GgafObject {

public:

	/** 識別名*/
	std::string	_resource_idstr;
	/** 使いまわす資源 */
	T* _pResource;
	/** 資源を参照しているポインタ数 */
	int _iResourceReferenceNum;
	/** 次のGgafResourcePointerへのポインタ。終端はNULL */
	GgafResourcePointer* _pNext;

	/**
	 * コンストラクタ<BR>
	 * @param prm_resource_idstr 識別名
	 * @param prm_pResource 使いまわす資源
	 * @param prm_pIDirect3DTexture9
	 */
	GgafResourcePointer(std::string prm_resource_idstr, T* prm_pResource);

	/**
	 * 資源を取得。
	 * 参照カウンタは増えません
	 */
	virtual T* getResource();

	/**
	 * デストラクタ<BR>
	 * deleteするのはGgafResourcePointerManagerである<BR>
	 */
	virtual ~GgafResourcePointer();		//デストラクタ
};

template<class T>
GgafResourcePointer<T>::GgafResourcePointer(std::string prm_resource_idstr, T* prm_pResource) : GgafObject() {
    _TRACE_("GgafResourcePointer::GgafResourcePointer(" <<  _resource_idstr << ")");
    _resource_idstr = prm_resource_idstr;
    _pResource = prm_pResource;
	_pNext = NULL;
	_iResourceReferenceNum = 0;
}

template<class T>
T* GgafResourcePointer<T>::getResource() {
	return _pResource;
}

template<class T>
GgafResourcePointer<T>::~GgafResourcePointer() {
	_TRACE_("GgafResourcePointer::~GgafResourcePointer() " <<  _resource_idstr << " start-->");
	_TRACE_("GgafResourcePointer::~GgafResourcePointer() " <<  _resource_idstr << " <--end");
}

}

#endif /*GGAFRESOURCEPOINTER_H_*/
