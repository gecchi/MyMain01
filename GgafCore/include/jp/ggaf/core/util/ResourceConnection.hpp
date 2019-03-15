#ifndef GGAF_CORE_RESOURCECONNECTION_H_
#define GGAF_CORE_RESOURCECONNECTION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"
#include "windows.h"
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#ifndef _MSC_VER
    #include <atomic>
#endif

namespace GgafCore {

/**
 * �����ڑ��N���X .
 * ����(Resource)�𖳑ʂɐ������s�킸�A�Q�Ƃ��Ďg���܂킵�����B������ new ����̂��ǂ������ӎ��������Ȃ��B<BR>
 * ����ȂƂ��Ɏg���N���X�B�ȒP�ɂ�����COM�I�u�W�F�N�g�̊ȈՔłƂ������Ƃ��납�B<BR>
 * ResourceManager : ����(Resource) : ResourceConnection  = 1 : N : N
 * �̊֌W�ŁA����Ń����Z�b�g�ł��BResourceConnection �͌���� ����(Resource)�̃��b�p�[�N���X�ł��B
 * ResourceConnection�����N���X�̃C���X�^���X���A�}�l�[�W���[�N���X(ResourceManager�����N���X)
 * ����擾(getConnection ���\�b�h)���邱�ƂƂ��܂��B<BR>
 * �}�l�[�W���[�ւ̐ڑ� ResourceManager<T>::getConnection �Łu�ڑ��J�E���g�v��+1�A
 * �{�N���X��close()�Łu�ڑ��J�E���g�v��-1����܂��B<BR>
 * close() ���Ăяo���ƁA�����Łu�ڑ��J�E���g�v�ɂ��{���ɉ�����ۂ��𔻒f���܂��B<BR>
 * �ڑ��J�E���g��0�ɂȂ����ꍇ�A����(Resource)�͉������܂��B
 * T �ɂ͎����̌^���w�肵�Ă��������B<BR>
 * ���ӁF�X���b�h�Z�[�t�̕ۏ؂͓����ɂQ�X���b�h�܂ŁB�R�X���b�h�ȏ�͐��������삵�܂���B<BR>
 * ���ӁF�ŏIclose()���̉���ŁA�������f�X�g���N�^���Ăяo���ׂɁAT �̃N���X�w�b�_�� include ��Y�ꂸ�ɁI�I<BR>
 * @tparam T �����̌^�i���̌^�̃|�C���^�^�������ŊǗ������B�j
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
template<class T>
class ResourceConnection : public Object {
    friend class ResourceManager<T>;

private:
    /** ���ʖ�(50�����܂�) */
    char* _idstr;
    /** ���݂̎����}�l�W���[�̎����ɐڑ����Ă���|�C���^�� */
    int _num_connection;
    /** �g���܂킷�����ւ̃|�C���^ */
    T* _pResource;
    /** ���߂Ă̐ڑ��� */
    void* _p_first_connector;


#ifdef _MSC_VER
    //TODO:VC++2005�ȍ~(x86) �� volatile �́A�������o���A���ʂ�����i�Ǝv���j�B
    //gcc(x86)�́A�A�g�~�b�N�ۏ؂͖����� std::atomic ���g����BVC++�� atomic �����������܂ł͂Ƃ肠�����E�E�E�B
    /** close����true�̔r���t���O */
    static volatile bool _is_closing_resource;
#else
    /** close����true�̔r���t���O */
    static volatile std::atomic<bool> _is_closing_resource;
#endif

protected:
    /** [r]�����}�l�W���[ */
    ResourceManager<T>* _pManager;
    /** [r]����ResourceConnection�ւ̃|�C���^�B�I�[��nullptr */
    ResourceConnection<T>* _pNext;

protected:
    /**
     * �R���X�g���N�^<BR>
     * protected �ł��闝�R�́A�}�l�W���[(ResourceManager<T>) ���������邽�߁B<BR>
     * @param prm_idstr ���ʖ�(29�����܂�)
     * @param prm_pResource �g���܂킷����
     */
    ResourceConnection(const char* prm_idstr, T* prm_pResource);

    /**
     * �f�X�g���N�^<BR>
     * protected �ł��闝�R�́Anew �� delete �̋����B�J���� close() �g�p������<BR>
     */
    virtual ~ResourceConnection() {
    }

    /**
     * �����̎��ۂ̉�������B
     * delete �� Release �ȂǁA���̎����ɉ��������ۂ̉�����������ĉ������B
     * @param prm_pResource
     */
    virtual void processReleaseResource(T* prm_pResource)= 0;

public:
    /**
     * ���ʖ���Ԃ� .
     * @return ���ʖ�
     */
    char* getIdStr() const ;

    /**
     * ���X�g�A������Ă��鎟�̎����ڑ��I�u�W�F�N�g��Ԃ� .
     * �I�[�ł������ꍇ�� nullptr ���Ԃ�B
     * @return ���̎����ڑ��I�u�W�F�N�g ���́Anullptr
     */
    ResourceConnection<T>* getNext() const;

    /**
     * �R�l�N�V������̎������擾 .
     * �ڑ��J�E���^�͑����܂���<BR>
     * @return �����ւ̃|�C���^
     */
    inline T* peek() const {
        return _pResource;
    }

    /**
     * �����̃|�C���^�̃I�u�W�F�N�g���A���߂ẴR�l�N�V�����I�u�W�F�N�g���ǂ������ׂ�B .
     * @param prm_this ���ׂ�I�u�W�F�N�g�Bthis��n���ĉ������B
     * @return true:���߂�connect����(=resource�� new �����j�I�u�W�F�N�g�ł���B/false:�����ł͂Ȃ��B
     */
    bool chkFirstConnectionIs(void* prm_this) const;

    /**
     * ����(Resource)�ւ̐ڑ������擾 .
     * @return ����(Resource)�ւ̐ڑ���
     */
    int getNumConnection() const;

    /**
     * �����ڑ������� .
     * �����Ƃ����Ă��}�l�[�W���̐ڑ��J�E���^��1���炷�����ł��B<BR>
     * �A���A�ڑ��J�E���^�� 0 �ɂȂ�΁AprocessReleaseResource���Ăяo���A�{���ɉ�����܂��B<BR>
     * COM�Ō����Ƃ���� Release() �ɂ�����B
     * @return �����ڑ�������������́A�ڑ��J�E���^
     */
    int close();

};

/////////////////////////////////// ������ /////
#ifdef _MSC_VER
template<class T>
volatile bool ResourceConnection<T>::_is_closing_resource = false;
#else
template<class T>
volatile std::atomic<bool> ResourceConnection<T>::_is_closing_resource(false);
#endif

template<class T>
char* ResourceConnection<T>::getIdStr() const {
    return _idstr;
}

template<class T>
ResourceConnection<T>* ResourceConnection<T>::getNext() const {
    return _pNext;
}

template<class T>
ResourceConnection<T>::ResourceConnection(const char* prm_idstr, T* prm_pResource) : Object() {
    _TRACE3_("prm_idstr="<<prm_idstr);
    _pResource = prm_pResource;
    _pNext = nullptr;
    _pManager = nullptr;
    _num_connection = 0;
    _p_first_connector = nullptr;

    int len = strlen(prm_idstr);
    _idstr = NEW char[len+1];
    strcpy(_idstr, prm_idstr);

}

template<class T>
int ResourceConnection<T>::getNumConnection() const {
    return _num_connection;
}

template<class T>
bool ResourceConnection<T>::chkFirstConnectionIs(void* prm_this) const {
    if (_p_first_connector == prm_this) {
        return true;
    } else {
        return false;
    }
}


template<class T>
int ResourceConnection<T>::close() {
    //close() �͕����X���b�h�����t�����e����B
    if ( _is_closing_resource || ResourceManager<T>::_is_connecting_resource) {
        _TRACE_("���x���� ResourceConnection<T>::close() �ʂ̃X���b�h��connect() ������ close() �B�ҋ@���������܂����E�E�E�E�Ӑ}�I�Ȃ�Ηǂ��ł��B[" << _pManager->_manager_name << "(" << _idstr << ")" << "]�B");
    }

    for (int i = 0; _is_closing_resource || ResourceManager<T>::_is_connecting_resource; i++) {
        Sleep(10);
        if (i > 100*60) {
            throwCriticalException("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << " \n"
                                       "���� connect() ������ close() ���ɂ�������炸�Aclose()���悤�Ƃ��ă^�C���A�E�g�ɂȂ�܂����Bconnect�`colse �̃X���b�h���P�{�ɂ��ĉ������B");
        }
        if (i % 100 == 0) {
            _TRACE_("���x���� ResourceConnection<T>::close() �ʂ̃X���b�h��connect() ������ close() ���ɁA�����close()�v�����������ߑҋ@�B[" << _pManager->_manager_name << "(" << _idstr << ")" << "]�B�҂�����="<<i);
        }
    }
    _is_closing_resource = true;

    if (_num_connection <= 0) {
        _TRACE3_(" [" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  ���x�������ɃR�l�N�V�����͖����ɂ�������炸�Aclose() ���悤�Ƃ��Ă܂��B");
        _TRACE3_("�����s�Ȃ킸return���܂����A�Ӑ}�I�łȂ��ꍇ�͉��������������ł��傤�B���[�N�̉\������B�������ׂ��I");
        return _num_connection;
    }

    ResourceConnection<T>* pCurrent = _pManager->_pConn_first;
    ResourceConnection<T>* pPrev = nullptr;
    while (pCurrent) {
        if (pCurrent == this) {
            //���������ꍇ
            int rnum = _num_connection;
            _TRACE3_("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  ���������̂ŊJ�n");
            if (rnum == 1) {//�Ō�̐ڑ��������ꍇ
                //���ɍs���h�߂ł���̂ŁA�ێ����X�g���痣�E���s�Ȃ�
                if (pCurrent->_pNext == nullptr) {
                    //����������
                    if (pPrev == nullptr) {
                        //�����Ő擪�������i���Ō�̈�j
                        _pManager->_pConn_first = nullptr;
                    } else {
                        //�����Ő擪�łȂ�����
                        pPrev->_pNext = nullptr;
                    }
                } else {
                    //�����łȂ�
                    if (pPrev == nullptr) {
                        //�擪������
                        _pManager->_pConn_first = pCurrent->_pNext; //�擪�����ɂ��炷
                    } else {
                        //�����ł��擪�ł��Ȃ��i���ԁj
                        pPrev->_pNext = pCurrent->_pNext; //���ׂ��q����
                    }
                }
                _TRACE3_("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  �Ō�̎Q�Ƃ̂��߉�����܂��B");
                _num_connection = 0;
            } else if (rnum > 0) {
                _TRACE3_("[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  �܂��c���Ă܂�");
                _num_connection--;
            } else if (rnum < 0) {
                //�R�R�͒ʂ�Ȃ��E�E�E
                _TRACE_(FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection << "  "
                        "����������I�A�ǂȂ���˂�B�A�z�[(>_<)�B�Ƃ肠�����X���[�B");
                _num_connection = 0; //�Ƃ肠�������
            }
            break;
        } else {
            //������ꍇ
            pPrev = pCurrent;
            pCurrent = pCurrent->_pNext;
        }
    }

    if (_num_connection == 0) {
        T* r = pCurrent->peek();
        if (r) {
            _TRACE_(FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection <<" processReleaseResource() Begin.");
            pCurrent->processReleaseResource(r); //�{���̉��
            _TRACE_(FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "]<-" << _num_connection <<" processReleaseResource() Done.");
        }

        if (ResourceManager<T>::_is_waiting_to_connect) {
            //�ʃX���b�h�Ŋ���connet()�҂���Ԃɓ����Ă���ΊJ�����Ȃ��B
            //����́A�����ꎟ�̏u�� new ����邱�Ƃ��m�肵�Ă���̂ŁA���ʂ�delete ���s��Ȃ��悤�ɂ���Ƃ������Ӑ}�B
            //�ނ��낱�̂悤�ɂ��Ȃ��ƁA��u�����|�C���^��ԂɂȂ�̂ŁAconnet()���ŏ����ɂ���Ă͗����Ă��܂��i�Ǝv���j�B
            _is_closing_resource = false;
            return 0;
        } else {
            //�ʃX���b�h��connet()�҂���Ԃ������̂ŁA���S���ĊJ������Ƃ��悤�B
            _is_closing_resource = false; //this�|�C���^���g�p���Ă��Ȃ��̂ő���\
            _TRACE_(FUNC_NAME<<"[" << _pManager->_manager_name << "(" << _idstr << ")" << "] Now, delete this !!!");
            delete[] _idstr;
            delete this;     //����Ȃ��Ƃ��o�����ł��ˁI�B
//            if (ResourceManager<T>::_is_waiting_to_connect) {
//                //�����ɗ��āAconnet()�҂��ɕς���Ă�����A�������߂�B
//                //���݂̔r�������S�ł͂Ȃ��ƍl����̂́A���̂�����̏������܂�
//                //TODO:���S�Ή��ɂ́Aconnect()���p������@�\�����˂΂Ȃ�ʁB
//                _TRACE_("���x����ResourceConnection<T>::close() delete this ���� connect() ���悤�Ƃ��܂����B���v�ł��傤���B�E�E�E���͂�ǂ����悤�������̂ł����I");
//            }
//            _is_closing_resource = false; //this�|�C���^���g�p���Ă��Ȃ��̂ő���\
            return 0;
        }
    } else {
        _is_closing_resource = false;
        return _num_connection;
    }
}

}

#endif /*GGAF_CORE_RESOURCECONNECTION_H_*/