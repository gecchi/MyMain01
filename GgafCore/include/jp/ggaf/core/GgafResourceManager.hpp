#ifndef GGAFRESOURCEMANAGER_H_
#define GGAFRESOURCEMANAGER_H_
namespace GgafCore {

/**
 * �����Ǘ��N���X�B .
 * �����Ǘ��N���X�́A���������b�s���O����w�����ڑ��N���X(GgafResourceConnection)�x���Ǘ����܂��B<BR>
 * ����(Resource)�𖳑ʂɐ������s�킸�A�Q�Ƃ��Ďg���܂킵�����B������ new ����̂��ǂ������ӎ��������Ȃ��B<BR>
 * ����ȂƂ��Ɏg���N���X�ł��B<BR>
 * GgafResourceManager : Resource : GgafResourceConnection  = 1 : N : N <BR>
 * �̊֌W�ŁA����Ń����Z�b�g�ł��B<BR>
 * �����Ǘ��N���X�͎�ȋ@�\�́A�����ڑ��N���X�̃C���X�^���X��������Ƀ��X�g�ŕێ����A�擾�v�����������ꍇ�A
 * �����ێ����Ă���΂����Ԃ��A�ێ����Ă��Ȃ���ΐ������āA���X�g�ɒǉ������セ���Ԃ��܂��B
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafResourceManager : public GgafObject {
    friend class GgafResourceConnection<T>;

private:
    /**
     * GgafResourceConnection�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
     * @param prm_pNew �ǉ�����GgafResourceConnection�I�u�W�F�N�g�̃|�C���^
     */
    virtual void add(GgafResourceConnection<T>* prm_pNew);

    /**
     * GgafResourceConnection�I�u�W�F�N�g�����X�g���猟���B<BR>
     * @param prm_idstr ���ʖ�
     * @return  ���]��GgafResourceConnection�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
     */
    virtual GgafResourceConnection<T>* find(char* prm_idstr);

    /**
     * �����̂𐶐��B.
     * @param prm_name ���ʖ�
     */
    T* createResource(char* prm_idstr);

    /**
     * �����ڑ��I�u�W�F�N�g�𐶐�.
     * @param prm_name ���ʖ�
     */
    GgafResourceConnection<T>* createResourceConnection(char* prm_idstr, T* prm_pResource);

protected:
    /** �}�l�[�W������ */
    const char* _manager_name;
    /** GgafResourceConnection�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
    GgafResourceConnection<T>* _pFirstConnection;


    /**
     * �����ڑ��I�u�W�F�N�g�̐��������ʂŎ������܂��B.
     * ���̃��\�b�h�� createResourceConnection ����Ăяo����A�{�e���v���[�g���p�҂���������K�v������܂��B<BR>
     * prm_idstr ���� �����ڑ��I�u�W�F�N�g�𐶐����郍�W�b�N���������Ă��������B<BR>
     * �قƂ�ǂ́AGgafResourceConnection �����N���X�� new ���āA�����Ԃ�������OK�BBR>
     * @param prm_idstr  ���̎��ʖ����n���ꂽ���A�ǂ����������ڑ��I�u�W�F�N�g�𐶐����邩�H �Ƃ������ʖ�
     * @param prm_pResource �����|�C���^
     * @return GgafResourceConnection �����ڑ��I�u�W�F�N�g�̃C���X�^���X�i��GgafResourceConnection �����N���X�̃C���X�^���X�j
     */
    virtual GgafResourceConnection<T>* processCreateConnection(char* prm_idstr, T* prm_pResource) = 0;

    /**
     * ���ۂ̎����̂𐶐������ʂŎ������܂��B.
     * ���̃��\�b�h�� createResource ����Ăяo����A�{�e���v���[�g���p�҂���������K�v������܂��B<BR>
     * prm_idstr ���� �����𐶐����郍�W�b�N���������Ă��������B<BR>
     * @param prm_idstr ���̎��ʖ����n���ꂽ���A�ǂ����������𐶐�(new)���邩�H �Ƃ������ʖ�
     * @return �����C���X�^���X�̃|�C���^
     */
    virtual T* processCreateResource(char* prm_idstr) = 0;


public:
    /**
     * �R���X�g���N�^
     */
    GgafResourceManager(const char* prm_manager_name);

    /**
     * �f�X�g���N�^�B�ێ����X�g������������܂��B .
     * �S�Ă̕ێ����X�g�� GgafResourceConnection�ɑ΂��AGgafResourceConnection��release()���P�x���s���A<BR>
     * GgafResourceConnection�̐ڑ��J�E���^0�Ȃ�΁Adelete ���܂��B<BR>
     * GgafResourceConnection�̐ڑ��J�E���^0�łȂ���΁A�g�p�҂̃��W�b�N�ŉ���R��̋��ꂪ����̂�
     * �ꌾ������ delete ���܂��B<BR>
     */
    virtual ~GgafResourceManager();

    /**
     * GgafResourceConnection�I�u�W�F�N�g���擾�B<BR>
     * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
     * �ێ����X�g����擾�����ꍇ�A�ڑ��J�E���^�������܂��B<BR>
     * new �����ꍇ�A�ڑ��J�E���^��1�ł��B<BR>
     * @param prm_idstr ���ʖ�
     */
    virtual GgafResourceConnection<T>* connect(char* prm_idstr);

    /**
     * GgafResourceConnection�I�u�W�F�N�g���擾�B<BR>
     * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
     * �ێ����X�g����擾�����ꍇ�A�ڑ��J�E���^�������܂��B<BR>
     * new �����ꍇ�A�ڑ��J�E���^��1�ł��B<BR>
     * @param prm_idstr ���ʖ�
     */
    virtual GgafResourceConnection<T>* connect(const char* prm_idstr);


    /**
     * �}�l�W���[���ێ����郊�X�g���o�͂��܂��B�i�f�o�b�O�p�j .
     */
    virtual void dump();
};

// ---------------------------------------------------------------------//

template<class T>
GgafResourceManager<T>::GgafResourceManager(const char* prm_manager_name) : GgafObject(),
      _manager_name(prm_manager_name) {
    TRACE3("GgafResourceManager<T>::GgafResourceManager(" << prm_manager_name << ")");
    _pFirstConnection = NULL;
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::find(char* prm_idstr) {
    GgafResourceConnection<T>* pCurrent = _pFirstConnection;
    while (pCurrent != NULL) {
        //_TRACE_("pCurrent->_idstr -> "<<(pCurrent->_idstr)<<" prm_idstr="<<prm_idstr);
        if (GgafUtil::strcmp_ascii(pCurrent->_idstr, prm_idstr) == 0) {
            return pCurrent;
        }
        pCurrent = pCurrent->_pNext;
    }
    return NULL;
}

template<class T>
void GgafResourceManager<T>::add(GgafResourceConnection<T>* prm_pResource_New) {
    if (_pFirstConnection == NULL) {
        _pFirstConnection = prm_pResource_New;
        return;
    } else {
        GgafResourceConnection<T>* pCurrent = _pFirstConnection;
        while (pCurrent->_pNext != NULL) {
            pCurrent = pCurrent->_pNext;
        }
        pCurrent->_pNext = prm_pResource_New;
        return;
    }
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::connect(char* prm_idstr) {
    if (prm_idstr == NULL) {
        TRACE3("�x�� GgafResourceManager<T>::connect(NULL) [" << _manager_name << "]");
    }
    GgafResourceConnection<T>* pObj = find(prm_idstr);
    if (pObj == NULL) {
        //�������Ȃ�ΐ����B�ڑ��J�E���^���P
        T* pResource = createResource(prm_idstr);
        pObj = createResourceConnection(prm_idstr, pResource);
        pObj->_num_connection = 1;
        add(pObj);
        TRACE3("GgafResourceManager<T>::getConnection [" << _manager_name << "]" << prm_idstr << "�͖����̂ŁA�V�K�쐬���ĕێ��Ɍ���");
        return pObj;
    } else {
        //�����ς݂Ȃ炻���Ԃ��B�ڑ��J�E���^���{�P
        pObj->_num_connection++;
        TRACE3("GgafResourceManager<T>::getConnection [" << _manager_name << "]" << prm_idstr << "�͂���̂Őڑ��J�E���g�{�P." << pObj->_num_connection);
        return pObj;
    }
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::connect(const char* prm_idstr) {
    return this->connect((char*)prm_idstr);
}

template<class T>
T* GgafResourceManager<T>::createResource(char* prm_idstr) {
    TRACE3("GgafResourceManager<T>::createResource [" << _manager_name << "]" << prm_idstr << "�𐶐����܂��傤");
    return processCreateResource(prm_idstr);
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::createResourceConnection(char* prm_idstr, T* prm_pResource) {
    TRACE3("GgafResourceManager<T>::createResourceConnection [" << _manager_name << "]" << prm_idstr << "�𐶐����܂��傤");
    GgafResourceConnection<T>* p = processCreateConnection(prm_idstr, prm_pResource);
    p->_pManager = this; //�}�l�[�W���o�^
    return p;
}

template<class T>
void GgafResourceManager<T>::dump() {
    GgafResourceConnection<T>* pCurrent = _pFirstConnection;
    if (_pFirstConnection == NULL) {
        TRACE3("GgafResourceManager::dump[" << _manager_name << "] �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
    } else {
        GgafResourceConnection<T>* pCurrent_Next;
        while (pCurrent != NULL) {
            TRACE3("GgafResourceManager::dump[" << _manager_name << "] [" << pCurrent->_idstr << "��" << pCurrent->_num_connection << "Connection]");
            pCurrent_Next = pCurrent->_pNext;
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
    TRACE3("GgafResourceManager<T>::~GgafResourceManager[" << _manager_name << "] " << _manager_name << " ");
    GgafResourceConnection<T>* pCurrent = _pFirstConnection;
    if (_pFirstConnection == NULL) {
        TRACE3("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
    } else {
        GgafResourceConnection<T>* pCurrent_Next;
        while (pCurrent != NULL) {
            int rnum = pCurrent->_num_connection;
            TRACE3("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] �ێ����X�g��[" << pCurrent->_idstr << "��" << rnum
                    << "Connection]���c���Ă܂��B�����폜���܂����A�{�������Ă͂����܂���B���ʂ�" << rnum << "�� close()�𔭍s���܂�");
//            T* r = pCurrent->view();
            pCurrent_Next = pCurrent->_pNext;
//            if (r != NULL) {
//                pCurrent->processReleaseResource(r); //���\�[�X�̉��
//            }
            for (int i = 0; i < rnum; i++) {
                pCurrent->close(); //���E����܂ŉ��
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
