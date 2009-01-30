#ifndef GGAFRESOURCECONNECTION_H_
#define GGAFRESOURCECONNECTION_H_
namespace GgafCore {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
template<class T>
class GgafResourceConnection : public GgafObject {
protected:
	/**
	 * �f�X�g���N�^<BR>
	 * protected �ł��闝�R�́Adelete �� this->Release() �݂̂łɌ��肵������<BR>
	 */
	virtual ~GgafResourceConnection() {};		//�f�X�g���N�^

public:
	GgafResourceManager<T>* _pManager;

	/** ���ʖ�(29�����܂�) */
	char* _idstr;
	/** �g���܂킷���� */
	T* _pResource;
	/** �������Q�Ƃ��Ă���|�C���^�� */
	int _iConnectionNum;
	/** ����GgafResourceConnection�ւ̃|�C���^�B�I�[��NULL */
	GgafResourceConnection* _pNext;

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_idstr ���ʖ�(29�����܂�)
	 * @param prm_pResource �g���܂킷����
	 * @param prm_pIDirect3DTexture9
	 */
	GgafResourceConnection(char* prm_idstr, T* prm_pResource);

	/**
	 * �������擾�B
	 * �Q�ƃJ�E���^�͑����܂���
	 */
	virtual T* getResource();



	/**
	 * ���������
	 */
	int Release();


	/**
	 * �����̎��ۂ̃����[�X�������������܂��B
	 * @param prm_pResource
	 */
	virtual void processReleaseResource(T* prm_pResource)= 0;

};

template<class T>
GgafResourceConnection<T>::GgafResourceConnection(char* prm_idstr, T* prm_pResource) : GgafObject() {
	_TRACE_("GgafResourceConnection::GgafResourceConnection(" <<  prm_idstr << ")");
    _pResource = prm_pResource;
	_pNext = NULL;
	_pManager = NULL;
	_iConnectionNum = 0;
	_idstr = new char[30];
	strcpy(_idstr, prm_idstr);
}

template<class T>
T* GgafResourceConnection<T>::getResource() {
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
			//���������ꍇ
			int rnum = _iConnectionNum;
			_TRACE_("GgafResourceManager::releaseResourceConnection[" << _idstr << "��" << rnum << "Objects] ���������̂ŊJ�n");

			if (rnum == 1) {//�Ō�̎Q�Ƃ������ꍇ
				//���ɍs���h�߂ł���̂ŁA�ێ����X�g���痣�E���s�Ȃ�
				if (pCurrent->_pNext == NULL) {
					//����������
					if (pPrev == NULL) {
						//�����Ő擪�������i���Ō�̈�j
						_pManager->_pTop = NULL;
					} else {
						//�����Ő擪�łȂ�����
						pPrev->_pNext = NULL;
					}
				} else {
					//�����łȂ�
					if (pPrev == NULL) {
						//�擪������
						_pManager->_pTop = pCurrent->_pNext; //�擪�����ɂ��炷
					} else {
						//�����ł��擪�ł��Ȃ��i���ԁj
						pPrev->_pNext = pCurrent->_pNext; //���ׂ��q����
					}
				}
				_TRACE_("GgafResourceManager::releaseResourceConnection["<<_idstr<<"��"<<rnum<<"Objects] �Ō�̎Q�Ƃ̂��߉�����܂��B");
				_iConnectionNum = 0;
			} else if (rnum > 0) {
				_TRACE_("GgafResourceManager::releaseResourceConnection["<<_idstr<<"��"<<rnum<<"Objects] �܂��c���Ă܂�");
				_iConnectionNum--;
			} else if (rnum < 0) {
				_TRACE_("GgafResourceManager::releaseResourceConnection["<<_idstr<<"��"<<rnum<<"Objects] ���������(><)�B��҂̃A�z�[�B�ǂȂ�����̂�B���肦�܂���B");
				_iConnectionNum = 0; //�Ƃ肠�������
			}
			break;
		} else {
			//������ꍇ
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}

	if (_iConnectionNum == 0) {
		T* r = pCurrent->getResource();
		if (r != NULL) {
			pCurrent->processReleaseResource(r); //�{���̉��
		}
		delete _idstr;
		delete this;
		return 0;
	} else {
		return _iConnectionNum;
	}
}


}

#endif /*GGAFRESOURCECONNECTION_H_*/
