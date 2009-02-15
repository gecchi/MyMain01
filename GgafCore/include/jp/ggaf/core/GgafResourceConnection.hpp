#ifndef GGAFRESOURCECONNECTION_H_
#define GGAFRESOURCECONNECTION_H_
namespace GgafCore {

/**
 * ����(Resource)�A�N�Z�b�T.
 * ���ʂȎ���(Resource)�̐������s�킸�A�Q�Ƃ��Ďg���܂킵�������䂦�A�J���������ȒP�ɂ��邽�߂̃N���X�B<BR>
 * GgafResourceConnection�����N���X�̃C���X�^���X���A�}�l�[�W���[�N���X(GgafResourceManager�����N���X)
 * ����擾���邱�ƂƂ��܂��B<BR>
 * �����ŎQ�ƃJ�E���^�ɂ��J�����ۂ��𔻒f���������߂ł��B<BR>
 * �}�l�[�W���[����擾�ŎQ�ƃJ�E���g��+1�A�{�N���X��Release�ŎQ�ƃJ�E���g��-1����܂��B<BR>
 * �Q�ƃJ�E���g��0�ɂȂ����ꍇ�A����(Resource)�͊J������܂��B
 * T �ɂ͎������w�肵�Ă��������B<BR>
 */
template<class T>
class GgafResourceConnection : public GgafObject {
protected:
    /**
     * �f�X�g���N�^<BR>
     * protected �ł��闝�R�́Adelete �� this->Release() �݂̂łɌ��肵������<BR>
     */
    virtual ~GgafResourceConnection() {
    } //�f�X�g���N�^

public:
    GgafResourceManager<T>* _pManager;

    /** ���ʖ�(50�����܂�) */
    char* _idstr;
    /** �g���܂킷���� */
    T* _pResource;
    /** �������Q�Ƃ��Ă���|�C���^�� */
    int _num_connection;
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
     * �����̃|�C���^���擾�B
     * �Q�ƃJ�E���^�͑����܂���<BR>
     */
    virtual T* view();

    /**
     * ���������
     * �Q�ƃJ�E���^��1���炵�A0�ɂȂ�Ζ{���ɊJ�����܂��B
     */
    int close();

    /**
     * �����̎��ۂ̃����[�X�������������܂��B
     * @param prm_pResource
     */
    virtual void processReleaseResource(T* prm_pResource)= 0;

};

template<class T>
GgafResourceConnection<T>::GgafResourceConnection(char* prm_idstr, T* prm_pResource) : GgafObject() {
    TRACE("GgafResourceConnection::GgafResourceConnection(" << prm_idstr << ")");
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

    GgafResourceConnection<T>* pCurrent;
    GgafResourceConnection<T>* pPrev;
    pCurrent = _pManager->_pTop;
    pPrev = NULL;
    while (pCurrent != NULL) {
        if (pCurrent == this) {
            //���������ꍇ
            int rnum = _num_connection;
            TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "��" << rnum << "Connection] ���������̂ŊJ�n");

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
                TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "��" << rnum << "Connection] �Ō�̎Q�Ƃ̂��߉�����܂��B");
                _num_connection = 0;
            } else if (rnum > 0) {
                TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "��" << rnum << "Connection] �܂��c���Ă܂�");
                _num_connection--;
            } else if (rnum < 0) {
                TRACE("GgafResourceManager::releaseResourceConnection[" << _idstr << "��" << rnum
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

    if (_num_connection == 0) {
        T* r = pCurrent->view();
        if (r != NULL) {
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
