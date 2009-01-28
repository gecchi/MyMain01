#ifndef GgafResource_H_
#define GgafResource_H_
namespace GgafCore {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
template<class T>
class GgafResource : public GgafObject {

public:

	/** ���ʖ�*/
	std::string	_name;
	/** �g���܂킷���� */
	T* _pResource;
	/** �������Q�Ƃ��Ă���|�C���^�� */
	int _iResourceReferenceNum;
	/** ����GgafResource�ւ̃|�C���^�B�I�[��NULL */
	GgafResource* _pNext;

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_name ���ʖ�(���t�@�C����)
	 * @param prm_pIDirect3DTexture9
	 */
	GgafResource(std::string prm_name);

	/**
	 * �Q�ƃJ�E���^������炷�B
	 * �Q�ƃJ�E���^��0�Ȃ��releaseResource()���Ăяo���B
	 */
	virtual void releaseResource();

	/**
	 * ������Release����������
	 */
	virtual void releaseResourceProcess() = 0;

	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafResourceManager�ł���<BR>
	 */
	virtual ~GgafResource();		//�f�X�g���N�^
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
