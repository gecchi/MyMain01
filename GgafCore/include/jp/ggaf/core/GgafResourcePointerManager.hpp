#ifndef GGAFRESOURCEPOINTERMANAGER_H_
#define GGAFRESOURCEPOINTERMANAGER_H_
namespace GgafCore {


/**
 * GgafResourcePointer �Ǘ��N���X .
 * �����ς� GgafResourcePointer �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
template<class T>
class GgafResourcePointerManager : public GgafObject {

protected:

	std::string _manager_name;

	/** GgafResourcePointer�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
	GgafResourcePointer<T>* _pTop;
	/**
	 * GgafResourcePointer�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param prm_pNew �ǉ�����GgafResourcePointer�I�u�W�F�N�g�̃|�C���^
	 */
	virtual void add(GgafResourcePointer<T>* prm_pNew);

	/**
	 * GgafResourcePointer�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param prm_name ���ʖ�(���t�@�C����)
	 * @return	���]��GgafResourcePointer�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	virtual GgafResourcePointer<T>* find(std::string prm_name);

public:

	/**
	 * �R���X�g���N�^
	 * @return
	 */
	GgafResourcePointerManager(std::string prm_manager_name);

	/**
	 * �f�X�g���N�^�B�ێ����X�g������������܂��B .
	 * �S�Ă̕ێ����X�g�� GgafResourcePointer�ɑ΂��AGgafResourcePointer��release()���P�x���s���A<BR>
	 * GgafResourcePointer�̎Q�ƃJ�E���^0�Ȃ�΁Adelete ���܂��B<BR>
	 * GgafResourcePointer�̎Q�ƃJ�E���^0�łȂ���΁A�ꌾ������ delete ���܂��B<BR>
	 */
	virtual ~GgafResourcePointerManager();

	/**
	 * GgafResourcePointer�I�u�W�F�N�g���擾�B<BR>
	 * ���f���I�u�W�F�N�g�́A���������A���̃��\�b�h���P�񂾂��Ăяo���Ă��擾����B<BR>
	 * �́A�ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
	 * ��ێ����X�g����擾�����ꍇ�A�Q�ƃJ�E���^�������܂��B�i���f���������P��Ɍ��肷��̂͂��̂��߁j<BR>
	 * new �����ꍇ�A�Q�ƃJ�E���^��1�ł��B<BR>
	 * �Q�ƃJ�E���^�̓��f���� delete ���ɂ�������邩�ǂ����̔��f�Ɏg�p�����B<BR>
	 * @param prm_name ���ʖ�
	 */
	virtual T* referResource(std::string prm_resource_idstr);

	virtual void releaseResource(T* prm_pResource);

	virtual GgafResourcePointer<T>* referResourcePointer(std::string prm_resource_idstr);
	virtual void releaseResourcePointer(GgafResourcePointer<T>* prm_pResourcePointer);



	/**
	 * �����̂𐶐������ʂŎ������܂��B.
	 * @param prm_name ���ʖ�
	 */
	virtual T* createResource(std::string prm_resource_idstr);

	virtual T* processCreateResource(std::string prm_resource_idstr)= 0;


	/**
	 * �W���̎����Q�ƃI�u�W�F�N�g�𐶐�.
	 * ���ʂŃI�[�o�[���C�h���Ă������ł���B.
	 * @param prm_name ���ʖ�
	 */
	virtual GgafResourcePointer<T>* createResourcePointer(std::string prm_resource_idstr, T* prm_pResource);
	virtual void processReleaseResource(T* prm_pResource)= 0;



	virtual void dump();
};

template<class T>
GgafResourcePointerManager<T>::GgafResourcePointerManager(std::string prm_manager_name) : GgafObject() {
	_TRACE_("GgafResourcePointerManager<T>::GgafResourcePointerManager("<<prm_manager_name<<")");
	_manager_name =  prm_manager_name;
	_pTop = NULL;
}

template<class T>
GgafResourcePointerManager<T>::~GgafResourcePointerManager() {
	_TRACE_("GgafResourcePointerManager<T>::~GgafResourcePointerManager "<<_manager_name<<" ");
	GgafResourcePointer<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourcePointerManager::dump �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResourcePointer<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			processReleaseResource(pCurrent->getResource()); //���
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum != 0) {
				_TRACE_("GgafResourcePointerManager::~GgafResourcePointerManager ["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects] �Q��0�łȂ�����delete���܂��B");
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
GgafResourcePointer<T>* GgafResourcePointerManager<T>::find(std::string prm_name) {
	GgafResourcePointer<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (pCurrent->_resource_idstr == prm_name) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourcePointerManager<T>::add(GgafResourcePointer<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResourcePointer<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}

template<class T>
void GgafResourcePointerManager<T>::releaseResource(T* prm_pResource) {
	if (prm_pResource == NULL) {
		_TRACE_("GgafResourcePointerManager::releaseResource ���� prm_pResource �� NULL�ł�");
		return;
	}
	GgafResourcePointer<T>* pCurrent;
	GgafResourcePointer<T>* pPrev;
	pCurrent = _pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent->getResource() == prm_pResource) {
			//���������ꍇ
			_TRACE_("GgafResourcePointerManager::releaseResource["<<pCurrent->_resource_idstr<<"]");
			processReleaseResource(pCurrent->getResource()); //���
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum == 0) {
				if (pCurrent->_pNext == NULL) {
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
				_TRACE_("GgafResourcePointerManager::releaseResource["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects]");
			}  else if (rnum < 0) {
				_TRACE_("GgafResourcePointerManager::releaseResource["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects] ���������(><)�B��҂̃A�z�[�B");
			}
			return;
		} else {
			//������ꍇ
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}
	_TRACE_("GgafResourcePointerManager::releaseResource prm_pResource�͂���܂���B�Ӑ}���Ă܂����H");
}


template<class T>
void GgafResourcePointerManager<T>::releaseResourcePointer(GgafResourcePointer<T>* prm_pResourcePointer) {
	if (prm_pResourcePointer == NULL) {
		_TRACE_("GgafResourcePointerManager::releaseResourcePointer ���� prm_pResourcePointer �� NULL�ł�");
		return;
	}
	GgafResourcePointer<T>* pCurrent;
	GgafResourcePointer<T>* pPrev;
	pCurrent = _pTop;
	pPrev    = NULL;
	while (pCurrent != NULL) {
		if (pCurrent == prm_pResourcePointer) {
			//���������ꍇ
			_TRACE_("GgafResourcePointerManager::releaseResourcePointer["<<pCurrent->_resource_idstr<<"]");
			processReleaseResource(pCurrent->getResource()); //���
			int rnum = pCurrent->_iResourceReferenceNum;
			if (rnum == 0) {
				if (pCurrent->_pNext == NULL) {
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
				_TRACE_("GgafResourcePointerManager::releaseResourcePointer["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects]");
			}  else if (rnum < 0) {
				_TRACE_("GgafResourcePointerManager::releaseResourcePointer["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects] ���������(><)�B��҂̃A�z�[�B");
			}
			return;
		} else {
			//������ꍇ
			pPrev = pCurrent;
			pCurrent = pCurrent -> _pNext;
		}
	}
	_TRACE_("GgafResourcePointerManager::releaseResourcePointer prm_pResourcePointer["<<prm_pResourcePointer->_resource_idstr<<"]�͊��ɂ���܂���B�Ӑ}���Ă܂����H");
}




template<class T>
T* GgafResourcePointerManager<T>::referResource(std::string prm_resource_idstr) {
	GgafResourcePointer<T>* pObj = find(prm_resource_idstr);
	//�������Ȃ�ΐ���
	if (pObj == NULL) {
		T* pResource = createResource(prm_resource_idstr);
		pObj = createResourcePointer(prm_resource_idstr, pResource);
		pObj->_iResourceReferenceNum = 1;
		add(pObj);
		return pResource;
	} else {
		pObj->_iResourceReferenceNum ++;
		return pObj->getResource();
	}
}

template<class T>
GgafResourcePointer<T>* GgafResourcePointerManager<T>::referResourcePointer(std::string prm_resource_idstr) {
	GgafResourcePointer<T>* pObj = find(prm_resource_idstr);
	//�������Ȃ�ΐ���
	if (pObj == NULL) {
		T* pResource = createResource(prm_resource_idstr);
		pObj = createResourcePointer(prm_resource_idstr, pResource);
		pObj->_iResourceReferenceNum = 1;
		add(pObj);
		return pObj;
	} else {
		pObj->_iResourceReferenceNum ++;
		return pObj;
	}
}

template<class T>
T* GgafResourcePointerManager<T>::createResource(std::string prm_resource_idstr) {
	_TRACE_("GgafResourcePointerManager<T>::createResource "<<prm_resource_idstr<<"�𐶐����܂��傤");
	return processCreateResource(prm_resource_idstr);
}

template<class T>
GgafResourcePointer<T>* GgafResourcePointerManager<T>::createResourcePointer(std::string prm_resource_idstr, T* prm_pResource) {
	GgafResourcePointer<T>* p = NEW GgafResourcePointer<T>(prm_resource_idstr, prm_pResource);
	return p;
}

template<class T>
void GgafResourcePointerManager<T>::dump() {
	GgafResourcePointer<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourcePointerManager::dump �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResourcePointer<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iResourceReferenceNum;
			_TRACE_("GgafResourcePointerManager::dump ["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects]");
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

}
#endif /*GGAFRESOURCEPOINTERMANAGER_H_*/
