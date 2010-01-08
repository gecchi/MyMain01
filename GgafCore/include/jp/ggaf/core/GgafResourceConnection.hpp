#ifndef GGAFRESOURCECONNECTION_H_
#define GGAFRESOURCECONNECTION_H_
namespace GgafCore {

/**
 * �����ڑ��N���X .
 * ����(Resource)�𖳑ʂɐ������s�킸�A�Q�Ƃ��Ďg���܂킵�����B������ new ����̂��ǂ������ӎ��������Ȃ��B<BR>
 * ����ȂƂ��Ɏg���N���X�B<BR>
 * GgafResourceManager : ����(Resource) : GgafResourceConnection  = 1 : N : N
 * �̊֌W�ŁA����Ń����Z�b�g�ł��BGgafResourceConnection �͌���� ����(Resource)�̃��b�p�[�N���X�ł��B
 * GgafResourceConnection�����N���X�̃C���X�^���X���A�}�l�[�W���[�N���X(GgafResourceManager�����N���X)
 * ����擾(getConnection ���\�b�h)���邱�ƂƂ��܂��B<BR>
 * �}�l�[�W���[�ւ̐ڑ� GgafResourceManager<T>::getConnection �Łu�ڑ��J�E���g�v��+1�A
 * �{�N���X��close()�Łu�ڑ��J�E���g�v��-1����܂��B<BR>
 * close() ���Ăяo���ƁA�����Łu�ڑ��J�E���g�v�ɂ��{���ɉ�����ۂ��𔻒f���܂��B<BR>
 * �ڑ��J�E���g��0�ɂȂ����ꍇ�A����(Resource)�͉������܂��B
 * T �ɂ͎����̌^���w�肵�Ă��������B<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafResourceConnection : public GgafObject {
    friend class GgafResourceManager<T>;

private:
    /** ���ʖ�(50�����܂�) */
    char* _idstr;
    /** ���݂̎����}�l�W���[�̎����ɐڑ����Ă���|�C���^�� */
    int _num_connection;
    /** �g���܂킷�厖�Ȏ��� */
    T* _pResource;

    static volatile bool _is_closeing_resource;
protected:
    /** �����}�l�W���[ */
    GgafResourceManager<T>* _pManager;
    /** ����GgafResourceConnection�ւ̃|�C���^�B�I�[��NULL */
    GgafResourceConnection<T>* _pNext;

    /**
     * �R���X�g���N�^<BR>
     * protected �ł��闝�R�́A�}�l�W���[(GgafResourceManager<T>) ���������邽�߁B<BR>
     * @param prm_idstr ���ʖ�(29�����܂�)
     * @param prm_pResource �g���܂킷����
     */
    GgafResourceConnection(char* prm_idstr, T* prm_pResource);


    /**
     * �f�X�g���N�^<BR>
     * protected �ł��闝�R�́Adelete �� this->Release() �݂̂łɌ��肵������<BR>
     */
    virtual ~GgafResourceConnection() {
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
    char* getIdStr();

    /**
     * ���X�g�A������Ă��鎟�̎����ڑ��I�u�W�F�N�g��Ԃ� .
     * �I�[�ł������ꍇ�� NULL ���Ԃ�B
     * @return ���̎����ڑ��I�u�W�F�N�g ���́ANULL
     */
    GgafResourceConnection<T>* getNext();

    /**
     * �������Q�ƁB .
     * �ڑ��J�E���^�͑����܂���<BR>
     * @return �����ւ̃|�C���^
     */
    virtual T* view();

    /**
     * �����ڑ������� .
     * �����Ƃ����Ă��}�l�[�W���̐ڑ��J�E���^��1���炷�����ł��B<BR>
     * �A���A�ڑ��J�E���^�� 0 �ɂȂ�΁AprocessReleaseResource���Ăяo���A�{���ɉ�����܂��B<BR>
     * @return �����ڑ�������������́A�ڑ��J�E���^
     */
    int close();
};

/////////////////////////////////// ������ /////
template<class T>
volatile bool GgafResourceConnection<T>::_is_closeing_resource = false;

template<class T>
char* GgafResourceConnection<T>::getIdStr() {
    return _idstr;
}

template<class T>
GgafResourceConnection<T>* GgafResourceConnection<T>::getNext() {
    return _pNext;
}


template<class T>
GgafResourceConnection<T>::GgafResourceConnection(char* prm_idstr, T* prm_pResource) : GgafObject() {
    TRACE3("GgafResourceConnection::GgafResourceConnection(prm_idstr = " <<  prm_idstr << ")");
    _is_closeing_resource = false;
    _pResource = prm_pResource;
    _pNext = NULL;
    _pManager = NULL;
    _num_connection = 0;
    _idstr = NEW char[51];
    strcpy(_idstr, prm_idstr);
}

template<class T>
T* GgafResourceConnection<T>::view() {
    return _pResource;
}

template<class T>
int GgafResourceConnection<T>::close() {
    if (_num_connection <= 0) {
        TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "��" << _num_connection << "Connection] ���x�������ɃR�l�N�V�����͖����ɂ�������炸�Aclose() ���悤�Ƃ��Ă܂��B");
        TRACE3("�����s�Ȃ킸return���܂����A�Ӑ}�I�łȂ��ꍇ�͉��������������ł��傤�B���[�N�̉\\������B�������ׂ��I");
        return _num_connection;
    }

    GgafResourceConnection<T>* pCurrent;
    GgafResourceConnection<T>* pPrev;

    //TODO:�ȈՓI�Ȕr���B���S�ł͂Ȃ��B
    while(GgafResourceManager<T>::_is_finding_resource) {
        Sleep(1);
    }

    _is_closeing_resource = true;
    pCurrent = _pManager->_pFirstConnection;
    pPrev = NULL;
    while (pCurrent != NULL) {
        if (pCurrent == this) {
            //���������ꍇ
            int rnum = _num_connection;
            TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "��" << rnum << "Connection] ���������̂ŊJ�n");
            if (rnum == 1) {//�Ō�̐ڑ��������ꍇ
                //���ɍs���h�߂ł���̂ŁA�ێ����X�g���痣�E���s�Ȃ�
                if (pCurrent->_pNext == NULL) {
                    //����������
                    if (pPrev == NULL) {
                        //�����Ő擪�������i���Ō�̈�j
                        _pManager->_pFirstConnection = NULL;
                    } else {
                        //�����Ő擪�łȂ�����
                        pPrev->_pNext = NULL;
                    }
                } else {
                    //�����łȂ�
                    if (pPrev == NULL) {
                        //�擪������
                        _pManager->_pFirstConnection = pCurrent->_pNext; //�擪�����ɂ��炷
                    } else {
                        //�����ł��擪�ł��Ȃ��i���ԁj
                        pPrev->_pNext = pCurrent->_pNext; //���ׂ��q����
                    }
                }
                TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "��" << rnum << "Connection] �Ō�̎Q�Ƃ̂��߉�����܂��B");
                _num_connection = 0;
            } else if (rnum > 0) {
                TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "��" << rnum << "Connection] �܂��c���Ă܂�");
                _num_connection--;
            } else if (rnum < 0) {
                TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "][" << _idstr << "��" << rnum
                        << "Connection] ���������(><)�B��҂̃A�z�[�B�ǂȂ�����̂�B���肦�܂���B");
                _num_connection = 0; //�Ƃ肠�������
            }
            break;
        } else {
            //������ꍇ
            pPrev = pCurrent;
            pCurrent = pCurrent->_pNext;
        }
    }
    _is_closeing_resource = false;

    if (_num_connection == 0) {
        T* r = pCurrent->view();
        if (r != NULL) {
            TRACE3("GgafResourceManager::releaseResourceConnection[" << _pManager->_manager_name << "." << _idstr << "] //�{���̉�� processReleaseResource[" << _idstr << "��" << _num_connection <<"]");
            pCurrent->processReleaseResource(r); //�{���̉��
        }
        delete[] _idstr;
        delete this;
        return 0;
    } else {
        return _num_connection;
    }
}

}

#endif /*GGAFRESOURCECONNECTION_H_*/
