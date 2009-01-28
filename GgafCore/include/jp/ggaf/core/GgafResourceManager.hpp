#ifndef GgafResourceManager_H_
#define GgafResourceManager_H_
namespace GgafCore {


/**
 * GgafResource �Ǘ��N���X .
 * �����ς� GgafResource �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
template<class T>
class GgafResourceManager : public GgafObject {

protected:

	std::string _manager_name;

	/** GgafResource�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
	GgafResource<T>* _pTop;
	/**
	 * GgafResource�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param prm_pNew �ǉ�����GgafResource�I�u�W�F�N�g�̃|�C���^
	 */
	virtual void add(GgafResource<T>* prm_pNew);

	/**
	 * GgafResource�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param prm_name ���ʖ�(���t�@�C����)
	 * @return	���]��GgafResource�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	virtual GgafResource<T>* find(std::string prm_name);

public:

	/**
	 * �R���X�g���N�^
	 * @return
	 */
	GgafResourceManager(std::string prm_manager_name);

	/**
	 * �f�X�g���N�^�B�ێ����X�g������������܂��B .
	 * �S�Ă̕ێ����X�g�� GgafResource�ɑ΂��AGgafResource��release()���P�x���s���A<BR>
	 * GgafResource�̎Q�ƃJ�E���^0�Ȃ�΁Adelete ���܂��B<BR>
	 * GgafResource�̎Q�ƃJ�E���^0�łȂ���΁A�ꌾ������ delete ���܂��B<BR>
	 */
	virtual ~GgafResourceManager();

	/**
	 * GgafResource�I�u�W�F�N�g���擾�B<BR>
	 * ���f���I�u�W�F�N�g�́A���������A���̃��\�b�h���P�񂾂��Ăяo���Ă��擾����B<BR>
	 * �́A�ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
	 * ��ێ����X�g����擾�����ꍇ�A�Q�ƃJ�E���^�������܂��B�i���f���������P��Ɍ��肷��̂͂��̂��߁j<BR>
	 * new �����ꍇ�A�Q�ƃJ�E���^��1�ł��B<BR>
	 * �Q�ƃJ�E���^�̓��f���� delete ���ɂ�������邩�ǂ����̔��f�Ɏg�p�����B<BR>
	 * @param prm_name ���ʖ�
	 */
	virtual GgafResource<T>* reference(std::string prm_name);

	/**
	 * GgafResource�𐶐����܂��B.
	 * ���ʂŎ������Ă��������B
	 * @param prm_name ���ʖ�
	 */
	virtual GgafResource<T>* createResource(std::string prm_name) = 0;


	/**
	 * ���\�[�X�̉��.
	 * �����̑Ώ� GgafResource���A�ێ����X�g�ɂ���� GgafResource��release()�����s���A<BR>
	 * GgafResource�̎Q�ƃJ�E���^��0�Ȃ�΁A����� delete ���܂�<BR>
	 * ���ӁF�ێ����X�g�ɃC���X�^���X�͎c���Ă�\��������܂��B<BR>
	 * @param prm_pResource �Ώ�GgafResource
	 */
	virtual void release(GgafResource<T>* prm_pResource);


	virtual void dump();
};

template<class T>
GgafResourceManager<T>::GgafResourceManager(std::string prm_manager_name) : GgafObject() {
	_TRACE_("GgafResourceManager<T>::GgafResourceManager("<<prm_manager_name<<")");
	_manager_name =  prm_manager_name;
	_pTop = NULL;
}

template<class T>
GgafResourceManager<T>::~GgafResourceManager() {
	_TRACE_("GgafResourceManager<T>::~GgafResourceManager "<<_manager_name<<" ");
	GgafResource<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResource<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			pCurrent->releaseResource(); //���
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum != 0) {
				_TRACE_("GgafResourceManager::~GgafResourceManager ["<<pCurrent->_name<<"��"<<rnum<<"Objects] �Q��0�łȂ�����delete���܂��B");
			}
			DELETE_IMPOSSIBLE_NULL(pCurrent); //�{���̉��
			pCurrent_Next = pCurrent -> _pNext;
			if (pCurrent_Next == NULL) {
				//�Ō�̈��
				break;
			} else {
				pCurrent = pCurrent_Next;
			}
		}
	}
}

template<class T>
GgafResource<T>* GgafResourceManager<T>::find(std::string prm_name) {
	GgafResource<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (pCurrent->_name == prm_name) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourceManager<T>::add(GgafResource<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResource<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}


template<class T>
void GgafResourceManager<T>::release(GgafResource<T>* prm_pResource) {
	if (prm_pResource == NULL) {
		_TRACE_("GgafResourceManager::remove ���� prm_pResource �� NULL�ł�");
		return;
	}
	GgafResource<T>* pCurrent;
	GgafResource<T>* pPrev;
	pCurrent = _pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent == prm_pResource) {
			//���������ꍇ
			_TRACE_("GgafResourceManager::release["<<pCurrent->_name<<"]");
			pCurrent->releaseResource(); //���
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum == 0) {
				if (prm_pResource->_pNext == NULL) {
					//����������
					if (pPrev == NULL) {
						//�����Ő擪�������i���Ō�̈�j
						_pTop = NULL;
					} else {
						//�����Ő擪�łȂ�����
						pPrev->_pNext = NULL;
					}
				} else {
					//�����łȂ�
					if (pPrev == NULL) {
						//�擪������
						_pTop = pCurrent->_pNext; //�擪�����ɂ��炷
					} else {
						//�����ł��擪�ł��Ȃ��i���ԁj
						pPrev->_pNext = pCurrent->_pNext; //���ׂ��q����
					}
				}
				DELETE_IMPOSSIBLE_NULL(pCurrent); //�{���̉��
			} else if (rnum > 0) {
				_TRACE_("GgafResourceManager::release["<<pCurrent->_name<<"��"<<rnum<<"Objects]");
			}  else if (rnum < 0) {
				_TRACE_("GgafResourceManager::release["<<pCurrent->_name<<"��"<<rnum<<"Objects] ���������(><)�B��҂̃A�z�[�B");
			}
			return;
		} else {
			//������ꍇ
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}
	_TRACE_("GgafResourceManager::release prm_pResource["<<prm_pResource->_name<<"]�͊��ɂ���܂���B�Ӑ}���Ă܂����H");
}


template<class T>
GgafResource<T>* GgafResourceManager<T>::reference(std::string prm_name) {
	GgafResource<T>* pObj = find(prm_name);
	//�������Ȃ�ΐ���
	if (pObj == NULL) {
		pObj = createResource(prm_name);
		pObj->_iReferenceNum = 1;
		add(pObj);
		return pObj;
	} else {
		pObj->_iReferenceNum ++;
		return pObj;
	}
}


template<class T>
void GgafResourceManager<T>::dump() {
	GgafResource<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResource<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iResourceReferenceNum;
			_TRACE_("GgafResourceManager::dump ["<<pCurrent->_name<<"��"<<rnum<<"Objects]");
			pCurrent_Next = pCurrent -> _pNext;
			if (pCurrent_Next == NULL) {
				pCurrent = NULL;
				break;
			} else {
				pCurrent = pCurrent_Next;
			}
		}
	}
}

class ZZZ : public GgafResourceManager<GgafObject> {};

}
#endif /*GgafResourceManager_H_*/
