#ifndef GGAFRESOURCEPOINTER_H_
#define GGAFRESOURCEPOINTER_H_
namespace GgafCore {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
template<class T>
class GgafResourcePointer : public GgafObject {

public:

	/** ���ʖ�*/
	std::string	_resource_idstr;
	/** �g���܂킷���� */
	T* _pResource;
	/** �������Q�Ƃ��Ă���|�C���^�� */
	int _iResourceReferenceNum;
	/** ����GgafResourcePointer�ւ̃|�C���^�B�I�[��NULL */
	GgafResourcePointer* _pNext;

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_resource_idstr ���ʖ�
	 * @param prm_pResource �g���܂킷����
	 * @param prm_pIDirect3DTexture9
	 */
	GgafResourcePointer(std::string prm_resource_idstr, T* prm_pResource);

	/**
	 * �������擾�B
	 * �Q�ƃJ�E���^�͑����܂���
	 */
	virtual T* getResource();

	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafResourcePointerManager�ł���<BR>
	 */
	virtual ~GgafResourcePointer();		//�f�X�g���N�^
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
