#ifndef GGAFRESOURCEMANAGER_H_
#define GGAFRESOURCEMANAGER_H_
namespace GgafCore {


/**
 * GgafResourceLead �Ǘ��N���X .
 * �����ς� GgafResourceLead �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
template<class T>
class GgafResourceManager : public GgafObject {
private:
	/**
	 * �����̂𐶐������ʂŎ������܂��B.
	 * @param prm_name ���ʖ�
	 */
	T* createResource(char* prm_idstr);

	/**
	 * �W���̎����Q�ƃI�u�W�F�N�g�𐶐�.
	 * ���ʂŃI�[�o�[���C�h���Ă������ł���B.
	 * @param prm_name ���ʖ�
	 */
	GgafResourceLead<T>* createResourceLead(char* prm_idstr, T* prm_pResource);

public:
	/** �}�l�[�W������ */
	const char* _manager_name;

	/** GgafResourceLead�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
	GgafResourceLead<T>* _pTop;
	/**
	 * GgafResourceLead�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param prm_pNew �ǉ�����GgafResourceLead�I�u�W�F�N�g�̃|�C���^
	 */
	virtual void add(GgafResourceLead<T>* prm_pNew);

	/**
	 * GgafResourceLead�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param prm_idstr ���ʖ�
	 * @return	���]��GgafResourceLead�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	virtual GgafResourceLead<T>* find(char* prm_idstr);

	/**
	 * �R���X�g���N�^
	 * @return
	 */
	GgafResourceManager(const char* prm_manager_name);

	/**
	 * �f�X�g���N�^�B�ێ����X�g������������܂��B .
	 * �S�Ă̕ێ����X�g�� GgafResourceLead�ɑ΂��AGgafResourceLead��release()���P�x���s���A<BR>
	 * GgafResourceLead�̎Q�ƃJ�E���^0�Ȃ�΁Adelete ���܂��B<BR>
	 * GgafResourceLead�̎Q�ƃJ�E���^0�łȂ���΁A�ꌾ������ delete ���܂��B<BR>
	 */
	virtual ~GgafResourceManager();


	/**
	 * GgafResourceLead�I�u�W�F�N�g���擾�B<BR>
	 * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
	 * �ێ����X�g����擾�����ꍇ�A�Q�ƃJ�E���^�������܂��B<BR>
	 * new �����ꍇ�A�Q�ƃJ�E���^��1�ł��B<BR>
	 * @param prm_name ���ʖ�
	 */
	virtual GgafResourceLead<T>* lead(char* prm_idstr);
	virtual GgafResourceLead<T>* lead(const char* prm_idstr);

	virtual T* processCreateResource(char* prm_idstr) = 0;

	virtual GgafResourceLead<T>* processCreateLead(char* prm_idstr, T* prm_pResource) = 0;

	virtual void dump();
};

template<class T>
GgafResourceManager<T>::GgafResourceManager(const char* prm_manager_name) : GgafObject(),
_manager_name(prm_manager_name)
{
	_TRACE_("GgafResourceManager<T>::GgafResourceManager("<<prm_manager_name<<")");
	_pTop = NULL;
}


template<class T>
GgafResourceLead<T>* GgafResourceManager<T>::find(char* prm_idstr) {
	GgafResourceLead<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (GgafUtil::strcmp_ascii(pCurrent->_idstr, prm_idstr) == 0) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourceManager<T>::add(GgafResourceLead<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResourceLead<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}

template<class T>
GgafResourceLead<T>* GgafResourceManager<T>::lead(char* prm_idstr) {
	GgafResourceLead<T>* pObj = find(prm_idstr);
	//�������Ȃ�ΐ���
	if (pObj == NULL) {
		T* pResource = createResource(prm_idstr);
		pObj = createResourceLead(prm_idstr, pResource);
		pObj->_iLeadNum = 1;
		add(pObj);
		_TRACE_("GgafResourceManager<T>::lead "<<prm_idstr<<"��V�K�쐬���ĕێ��Ɍ���");
		return pObj;
	} else {
		pObj->_iLeadNum ++;
		_TRACE_("GgafResourceManager<T>::lead "<<prm_idstr<<"�͂���̂ŎQ�ƃJ�E���g."<<pObj->_iLeadNum);
		return pObj;
	}
}

template<class T>
GgafResourceLead<T>* GgafResourceManager<T>::lead(const char* prm_idstr) {
	return this->lead((char*)prm_idstr);
}


template<class T>
T* GgafResourceManager<T>::createResource(char* prm_idstr) {
	_TRACE_("GgafResourceManager<T>::createResource "<<prm_idstr<<"�𐶐����܂��傤");
	return processCreateResource(prm_idstr);
}

template<class T>
GgafResourceLead<T>* GgafResourceManager<T>::createResourceLead(char* prm_idstr, T* prm_pResource) {
	_TRACE_("GgafResourceManager<T>::createResourceLead "<<prm_idstr<<"�𐶐����܂��傤");
	GgafResourceLead<T>* p = processCreateLead(prm_idstr, prm_pResource);
	p->_pManager = this; //�}�l�[�W���o�^
	return p;
}

template<class T>
void GgafResourceManager<T>::dump() {
	GgafResourceLead<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResourceLead<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iLeadNum;
			_TRACE_("GgafResourceManager::dump ["<<pCurrent->_idstr<<"��"<<rnum<<"Lead]");
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



template<class T>
GgafResourceManager<T>::~GgafResourceManager() {
	_TRACE_("GgafResourceManager<T>::~GgafResourceManager "<<_manager_name<<" ");
	GgafResourceLead<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::GgafResourceManager �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResourceLead<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iLeadNum;
			_TRACE_("GgafResourceManager::GgafResourceManager �ێ����X�g��["<<pCurrent->_idstr<<"��"<<rnum<<"Lead]���c���Ă܂��B�����폜���܂����A�{�������Ă͂����܂���B");

			T* r = pCurrent->getResource();
			pCurrent_Next = pCurrent -> _pNext;
			if (r != NULL) {
				pCurrent->processReleaseResource(r); //���\�[�X�̉��
			}
			for (int i = 0; i < rnum; i++) {
				RELEASE_IMPOSSIBLE_NULL(pCurrent); //���E����܂ŉ��
			}
			if (pCurrent_Next == NULL) {
				//�Ō�̈��
				break;
			} else {
				pCurrent = pCurrent_Next;
			}
		}
	}
}
}
#endif /*GGAFRESOURCEMANAGER_H_*/
