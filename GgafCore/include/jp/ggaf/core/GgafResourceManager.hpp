#ifndef GGAFRESOURCEMANAGER_H_
#define GGAFRESOURCEMANAGER_H_
namespace GgafCore {


/**
 * GgafResourceConnection �Ǘ��N���X .
 * �����ς� GgafResourceConnection �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
template<class T>
class GgafResourceManager : public GgafObject {
private:
	/**
	 * �����̂𐶐������ʂŎ������܂��B.
	 * @param prm_name ���ʖ�
	 */
	T* createResource(std::string prm_resource_idstr);

	/**
	 * �W���̎����Q�ƃI�u�W�F�N�g�𐶐�.
	 * ���ʂŃI�[�o�[���C�h���Ă������ł���B.
	 * @param prm_name ���ʖ�
	 */
	GgafResourceConnection<T>* createResourceConnection(std::string prm_resource_idstr, T* prm_pResource);

public:

	std::string _pManager_name;

	/** GgafResourceConnection�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
	GgafResourceConnection<T>* _pTop;
	/**
	 * GgafResourceConnection�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param prm_pNew �ǉ�����GgafResourceConnection�I�u�W�F�N�g�̃|�C���^
	 */
	virtual void add(GgafResourceConnection<T>* prm_pNew);

	/**
	 * GgafResourceConnection�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param prm_name ���ʖ�(���t�@�C����)
	 * @return	���]��GgafResourceConnection�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	virtual GgafResourceConnection<T>* find(std::string prm_name);

	/**
	 * �R���X�g���N�^
	 * @return
	 */
	GgafResourceManager(std::string prm_pManager_name);

	/**
	 * �f�X�g���N�^�B�ێ����X�g������������܂��B .
	 * �S�Ă̕ێ����X�g�� GgafResourceConnection�ɑ΂��AGgafResourceConnection��release()���P�x���s���A<BR>
	 * GgafResourceConnection�̎Q�ƃJ�E���^0�Ȃ�΁Adelete ���܂��B<BR>
	 * GgafResourceConnection�̎Q�ƃJ�E���^0�łȂ���΁A�ꌾ������ delete ���܂��B<BR>
	 */
	virtual ~GgafResourceManager();


	/**
	 * GgafResourceConnection�I�u�W�F�N�g���擾�B<BR>
	 * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
	 * �ێ����X�g����擾�����ꍇ�A�Q�ƃJ�E���^�������܂��B<BR>
	 * new �����ꍇ�A�Q�ƃJ�E���^��1�ł��B<BR>
	 * @param prm_name ���ʖ�
	 */
	virtual GgafResourceConnection<T>* getConnection(std::string prm_resource_idstr);

	virtual T* processCreateResource(std::string prm_resource_idstr) = 0;

	virtual GgafResourceConnection<T>* processCreateConnection(std::string prm_resource_idstr, T* prm_pResource) = 0;

	virtual void dump();
};

template<class T>
GgafResourceManager<T>::GgafResourceManager(std::string prm_pManager_name) : GgafObject() {
	_TRACE_("GgafResourceManager<T>::GgafResourceManager("<<prm_pManager_name<<")");
	_pManager_name =  prm_pManager_name;
	_pTop = NULL;
}


template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::find(std::string prm_name) {
	GgafResourceConnection<T>* pCurrent = _pTop;
	while (pCurrent != NULL) {
		if (pCurrent->_resource_idstr == prm_name) {
			return pCurrent;
		}
		pCurrent = pCurrent -> _pNext;
	}
	return NULL;
}

template<class T>
void GgafResourceManager<T>::add(GgafResourceConnection<T>* prm_pResource_New) {
	if (_pTop == NULL) {
		_pTop = prm_pResource_New;
		return;
	} else {
		GgafResourceConnection<T>* pCurrent = _pTop;
		while (pCurrent -> _pNext != NULL) {
			pCurrent = pCurrent -> _pNext;
		}
		pCurrent -> _pNext = prm_pResource_New;
		return;
	}
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::getConnection(std::string prm_resource_idstr) {
	GgafResourceConnection<T>* pObj = find(prm_resource_idstr);
	//�������Ȃ�ΐ���
	if (pObj == NULL) {
		T* pResource = createResource(prm_resource_idstr);
		pObj = createResourceConnection(prm_resource_idstr, pResource);
		pObj->_iConnectionNum = 1;
		add(pObj);
		_TRACE_("GgafResourceManager<T>::getConnection "<<prm_resource_idstr<<"��V�K�쐬���ĕێ��Ɍ���");
		return pObj;
	} else {
		pObj->_iConnectionNum ++;
		_TRACE_("GgafResourceManager<T>::getConnection "<<prm_resource_idstr<<"�͂���̂ŎQ�ƃJ�E���g."<<pObj->_iConnectionNum);
		return pObj;
	}
}

template<class T>
T* GgafResourceManager<T>::createResource(std::string prm_resource_idstr) {
	_TRACE_("GgafResourceManager<T>::createResource "<<prm_resource_idstr<<"�𐶐����܂��傤");
	return processCreateResource(prm_resource_idstr);
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::createResourceConnection(std::string prm_resource_idstr, T* prm_pResource) {
	_TRACE_("GgafResourceManager<T>::createResourceConnection "<<prm_resource_idstr<<"�𐶐����܂��傤");
	GgafResourceConnection<T>* p = processCreateConnection(prm_resource_idstr, prm_pResource);
	p->_pManager = this; //�}�l�[�W���o�^
	return p;
}

template<class T>
void GgafResourceManager<T>::dump() {
	GgafResourceConnection<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::dump �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResourceConnection<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iConnectionNum;
			_TRACE_("GgafResourceManager::dump ["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects]");
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
	_TRACE_("GgafResourceManager<T>::~GgafResourceManager "<<_pManager_name<<" ");
	GgafResourceConnection<T>* pCurrent = _pTop;
	if (_pTop == NULL) {
		_TRACE_("GgafResourceManager::GgafResourceManager �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
	} else {
		GgafResourceConnection<T>* pCurrent_Next;
		while (pCurrent != NULL) {
			int rnum = pCurrent->_iConnectionNum;
			_TRACE_("GgafResourceManager::GgafResourceManager �ێ����X�g��["<<pCurrent->_resource_idstr<<"��"<<rnum<<"Objects]���c���Ă܂��B�����폜���܂����A�{�������Ă͂����܂���B");

			T* r = pCurrent->get();
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
