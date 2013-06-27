#ifndef GGAFRESOURCEMANAGER_H_
#define GGAFRESOURCEMANAGER_H_
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

namespace GgafCore {

/**
 * �����Ǘ��N���X�B .
 * �����Ǘ��N���X�́A���������b�s���O�����w�����ڑ��I�u�W�F�N�g(GgafResourceConnection)�x���Ǘ����܂��B<BR>
 * ����(Resource)�𖳑ʂɐ������s�킸�A�Q�Ƃ��Ďg���܂킵�����B������ new ����̂��ǂ������ӎ��������Ȃ��B<BR>
 * ����ȂƂ��Ɏg���N���X�ł��B<BR>
 * GgafResourceManager : Resource : GgafResourceConnection  = 1 : N : N <BR>
 * �̊֌W�ŁA����Ń����Z�b�g�ł��B<BR>
 * �����Ǘ��N���X�͎�ȋ@�\�́A�����ڑ��N���X�̃C���X�^���X�i�̃|�C���^�j������Ƀ��X�g�ŕێ����A�擾�v�����������ꍇ�A
 * �����ێ����Ă���΂����Ԃ��A�ێ����Ă��Ȃ���ΐ������āA���X�g�ɒǉ������セ���Ԃ��܂��B
 * ���ӁF�X���b�h�Z�[�t�̕ۏ؂͓����ɂQ�X���b�h�܂ŁB�R�X���b�h�ȏ�͐��������삵�܂���B
 * (��GdxfwActorManager����ėp��)
 * @version 1.00
 * @since 2007/11/16
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
     * @return  ���]��GgafResourceConnection�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ nullptr
     */
    virtual GgafResourceConnection<T>* find(char* prm_idstr);

    /**
     * �����̂𐶐����� .
     * connect() ���A�������������ꍇ�Ăяo����܂��B
     * processCreateResource(char*, void*) ���R�[�����܂��B
     * @param prm_idstr connect() �œn���ꂽ���ʖ�
     * @param prm_p connect() �œn���ꂽ���R�p�����[�^
     */
    T* createResource(char* prm_idstr, void* prm_p);

    /**
     * �����ڑ��I�u�W�F�N�g�𐶐�.
     * @param prm_idstr ���ʖ�
     * @param prm_pResource �����ڑ��I�u�W�F�N�g��Value�B�܂莑���C���X�^���X�B
     * @return �����ڑ��I�u�W�F�N�g
     */
    GgafResourceConnection<T>* createResourceConnection(char* prm_idstr, T* prm_pResource);

protected:
    /** connect����true�̔r���t���O */
    static volatile bool _is_connecting_resource;
    /** connect���邽�߂ɑ҂��Ă���t���O */
    static volatile bool _is_waiting_to_connect;
    /** [r]�}�l�[�W������ */
    const char* _manager_name;
    /** [r]GgafResourceConnection�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��nullptr */
    GgafResourceConnection<T>* _pConn_first;

protected:
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
     * @param prm_p ���R�p�����[�^
     * @return �����C���X�^���X�̃|�C���^
     */
    virtual T* processCreateResource(char* prm_idstr, void* prm_pConnector) = 0;

//    int GgafResourceManager<T>::getConnectionNum();

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
     * �����ڑ�(GgafResourceConnection)�I�u�W�F�N�g���擾�B<BR>
     * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
     * �ێ����X�g����擾�����ꍇ�A�ڑ��J�E���^�������܂��B<BR>
     * new �����ꍇ�A�ڑ��J�E���^��1�ł��B<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_connector �ڑ����Athis��n���ĉ������B
     * @return ���ʖ��ɕR�t�������ڑ�(GgafResourceConnection)
     */
    virtual GgafResourceConnection<T>* connect(char* prm_idstr, void* prm_connector);

//    /**
//     * �����ڑ�(GgafResourceConnection)�I�u�W�F�N�g���擾�B<BR>
//     * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
//     * �ێ����X�g����擾�����ꍇ�A�ڑ��J�E���^�������܂��B<BR>
//     * new �����ꍇ�A�ڑ��J�E���^��1�ł��B<BR>
//     * @param prm_idstr ���ʖ�
//     * @return ���ʖ��ɕR�t�������ڑ�(GgafResourceConnection)
//     */
//    virtual GgafResourceConnection<T>* connect(char* prm_idstr) {
//        return this->connect(prm_idstr, nullptr);
//    }
//
//    /**
//     * �����ڑ�(GgafResourceConnection)�I�u�W�F�N�g���擾�B<BR>
//     * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
//     * �ێ����X�g����擾�����ꍇ�A�ڑ��J�E���^�������܂��B<BR>
//     * new �����ꍇ�A�ڑ��J�E���^��1�ł��B<BR>
//     * @param prm_idstr ���ʖ�
//     * @return ���ʖ��ɕR�t�������ڑ�(GgafResourceConnection)
//     */
//    virtual GgafResourceConnection<T>* connect(const char* prm_idstr) {
//        return this->connect((char*)prm_idstr, nullptr);
//    }

    /**
     * �����ڑ�(GgafResourceConnection)�I�u�W�F�N�g���擾�B<BR>
     * �ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
     * �ێ����X�g����擾�����ꍇ�A�ڑ��J�E���^�������܂��B<BR>
     * new �����ꍇ�A�ڑ��J�E���^��1�ł��B<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_p ���炩�̈���
     * @return ���ʖ��ɕR�t�������ڑ�(GgafResourceConnection)
     */
    virtual GgafResourceConnection<T>* connect(const char* prm_idstr, void* prm_p) {
        return this->connect((char*)prm_idstr, prm_p);
    }

    /**
     * �}�l�W���[���ێ����郊�X�g���o�͂��܂��B�i�f�o�b�O�p�j .
     */
    virtual void dump();
};

// ---------------------------------------------------------------------//


template<class T>
volatile bool GgafResourceManager<T>::_is_connecting_resource = false;

template<class T>
volatile bool GgafResourceManager<T>::_is_waiting_to_connect = false;

template<class T>
GgafResourceManager<T>::GgafResourceManager(const char* prm_manager_name) : GgafObject(),
      _manager_name(prm_manager_name) {
    TRACE3("GgafResourceManager<T>::GgafResourceManager(" << prm_manager_name << ")");
    _pConn_first = nullptr;
    _is_connecting_resource = false;
    _is_waiting_to_connect = false;
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::find(char* prm_idstr) {
    GgafResourceConnection<T>* pCurrent = _pConn_first;

    while (pCurrent) {
        //_TRACE_("pCurrent->_idstr -> "<<(pCurrent->_idstr)<<" prm_idstr="<<prm_idstr);
        if (UTIL::strcmp_ascii(pCurrent->_idstr, prm_idstr) == 0) {
            return pCurrent;
        }
        pCurrent = pCurrent->_pNext;
    }
    return nullptr;
}

template<class T>
void GgafResourceManager<T>::add(GgafResourceConnection<T>* prm_pResource_new) {
    if (_pConn_first == nullptr) {
        _pConn_first = prm_pResource_new;
        return;
    } else {
        GgafResourceConnection<T>* pCurrent = _pConn_first;
        while (pCurrent->_pNext) {
            pCurrent = pCurrent->_pNext;
        }
        pCurrent->_pNext = prm_pResource_new;
        return;
    }
}

template<class T>
GgafResourceConnection<T>* GgafResourceManager<T>::connect(char* prm_idstr, void* prm_connector) {
    if (prm_idstr == nullptr) {
        TRACE3("�x�� GgafResourceManager<T>::connect(nullptr) [" << _manager_name << "]");
    }
    if (_is_waiting_to_connect || _is_connecting_resource) {
        _TRACE_("GgafResourceManager<T>::connect() "<<_manager_name<<"�́A�R�l�N�g�������ł��B�ҋ@���������܂����E�E �ҋ@��("<<prm_idstr<<")");
    }
    for(int i = 0; _is_waiting_to_connect || _is_connecting_resource; i++) {
        Sleep(10);
        if (i > 10*100*60) {
            //10���ȏ㖳������
            _TRACE_("GgafResourceManager<T>::connect() "<<_manager_name<<"�ցAprm_idstr="<<prm_idstr<<" �� connect()���悤�Ƃ��āA�����̃R�l�N�g������10���ҋ@�E�E�E");
            throwGgafCriticalException("GgafResourceManager<T>::connect()  "<<_manager_name<<"�ցAprm_idstr="<<prm_idstr<<" �� connect()���悤�Ƃ��āA�����̃R�l�N�g������10���ҋ@�Bconnect() ���ɁAconnect()���Ă��邩�A�������x�����܂��B(1)");
        }
    }
    _is_waiting_to_connect = false;
    _is_connecting_resource = true;

    //TODO:�ȈՓI�Ȕr���B�قڊ����������S�ł͂Ȃ��B
    GgafResourceConnection<T>* pObj = nullptr;
    for(int i = 0; GgafResourceConnection<T>::_is_closing_resource; i++) {
        _is_waiting_to_connect = true;
        Sleep(10);
        if (i > 10*100*60) {
            //�P���ȏ㖳������
            _TRACE_("GgafResourceManager<T>::connect()  "<<_manager_name<<"�ցAprm_idstr="<<prm_idstr<<" �� connect()���悤�Ƃ��āA�����̃N���[�Y������10���ҋ@�E�E�E");
            throwGgafCriticalException("GgafResourceManager<T>::connect()  "<<_manager_name<<"�ցAprm_idstr="<<prm_idstr<<" ��  connect()���悤�Ƃ��āA�����̃N���[�Y������10���ҋ@�Bconnect() ���ɁAconnect()���Ă��邩�A�������x�����܂��B(2)");
        }
    }
    //TODO:����
    //close()���ɁA�ʃX���b�h��connect()����ƁB
    //�V�r�A�ȃ^�C�~���O�Ń�������j�󂷂鋰�ꂪ�c���Ă���A�X�X�����v�Ǝv���̂����ǂ��I�B
    //int (�v���~�e�B�u) �̃A�g�~�b�N���𗘗p���Ĕr���ł���ƈ��Ղɍl���Ă����A
    //�X���b�h�Z�[�t���S�Ή����悤�Ƃ���ƁA���Ȃ�߂�ǂ��������Ƃ����������B�׋��ɂȂ����B
    //���Ԃ�S�Ă� connect() �Ăяo������ connect() ���s���̏������`����ׂ��������B
    //template�ɂ����͎̂��s�������̂��G�ivoid*�ɂ��ׂ����������j�B
    //����g�ގ��͋C�����悤�A�R�R�͎��Ԃ̂���Ƃ��ɂ�����낤�B���̂����G�G�G
    //_TRACE_(" connect to " << _manager_name<<" for "<<prm_idstr<<"...");
    pObj = find(prm_idstr);
    if (pObj == nullptr) {
        //�������Ȃ�ΐ����B�ڑ��J�E���^���P
        T* pResource = createResource(prm_idstr, prm_connector);
        pObj = createResourceConnection(prm_idstr, pResource);
        pObj->_num_connection = 1;
        pObj->_first_connector = prm_connector;
        add(pObj);
        TRACE3("GgafResourceManager<T>::connect [" << _manager_name << "]" << prm_idstr << "�͖����̂ŁA�V�K�쐬���ĕێ��Ɍ���");
        _is_connecting_resource = false;
        return pObj;
    } else {
        //�����ς݂Ȃ炻���Ԃ��B�ڑ��J�E���^���{�P
        pObj->_num_connection++;
        TRACE3("GgafResourceManager<T>::connect [" << _manager_name << "]" << prm_idstr << "�͂���̂Őڑ��J�E���g�{�P." << pObj->_num_connection);
        _is_connecting_resource = false;
        return pObj;
    }
}

template<class T>
T* GgafResourceManager<T>::createResource(char* prm_idstr, void* prm_p) {
    TRACE3("GgafResourceManager<T>::createResource [" << _manager_name << "]" << prm_idstr << "�𐶐����܂��傤");
    T* p = processCreateResource(prm_idstr, prm_p);
    return p;
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
    GgafResourceConnection<T>* pCurrent = _pConn_first;
    if (_pConn_first == nullptr) {
        _TRACE_("GgafResourceManager::dump[" << _manager_name << "] �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
    } else {
        GgafResourceConnection<T>* pCurrent_next;
        while (pCurrent) {
            _TRACE_("GgafResourceManager::dump[" << _manager_name << "] [" << pCurrent->_idstr << "��" << pCurrent->_num_connection << "Connection]");
            pCurrent_next = pCurrent->_pNext;
            if (pCurrent_next == nullptr) {
                pCurrent = nullptr;
                break;
            } else {
                pCurrent = pCurrent_next;
            }
        }
    }
}

//template<class T>
//int* GgafResourceManager<T>::getConnectionNum() {
//    GgafResourceConnection<T>* pCurrent = _pConn_first;
//    int n = 0;
//    while (pCurrent) {
//        n++;
//        pCurrent = pCurrent->_pNext;
//    }
//    return n;
//}


template<class T>
GgafResourceManager<T>::~GgafResourceManager() {
    TRACE3("GgafResourceManager<T>::~GgafResourceManager[" << _manager_name << "] " << _manager_name << " ");
#ifdef MY_DEBUG
    _TRACE_("GgafResourceManager<T>::~GgafResourceManager()["<<_manager_name<<"] begin --->");
    _TRACE_("������ODumping��");
    dump();
#endif
    GgafResourceConnection<T>* pCurrent = _pConn_first;
    if (_pConn_first == nullptr) {
        TRACE3("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] �ێ����X�g�ɂ͂Ȃɂ�����܂���B");
    } else {
        GgafResourceConnection<T>* pCurrent_next;
        while (pCurrent) {
            int rnum = pCurrent->_num_connection;
            _TRACE_("GgafResourceManager::~GgafResourceManager[" << _manager_name << "] �ێ����X�g��[" << pCurrent->_idstr << "��" << rnum
                    << "Connection]���c���Ă܂��B�����폜���܂����A�{�������Ă͂����܂���B���ʂ�" << rnum << "�� close()�𔭍s���܂�");
//            T* r = pCurrent->peek();
            pCurrent_next = pCurrent->_pNext;
//            if (r) {
//                pCurrent->processReleaseResource(r); //���\�[�X�̉��
//            }
            for (int i = 0; i < rnum; i++) {
                pCurrent->close(); //���E����܂ŉ��
            }
            if (pCurrent_next == nullptr) {
                //�Ō�̈��
                break;
            } else {
                pCurrent = pCurrent_next;
            }
        }
    }
#ifdef MY_DEBUG
    _TRACE_("<--- GgafResourceManager<T>::~GgafResourceManager() ["<<_manager_name<<"] end");
#endif
}

}
#endif /*GGAFRESOURCEMANAGER_H_*/
