#ifndef IKD_DIX_PCMPLAYER_H
#define IKD_DIX_PCMPLAYER_H

#include <sstream>

#ifdef __GNUG__
    #define __null
#endif
#include <dsound.h>  //��sal.h �� include ����
#ifdef __GNUG__
    #undef __null
    #undef __in
    #undef __out
#endif

namespace IkdLib {

/**
 * PCMPlayer .
 * �{�v���O�����́A<BR>
 * �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
 * �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
 * �̃T���v���v���O�������I���W�i���ł��B<BR>
 * �ύX���Ďg�p���Ă��܂��B<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class PCMPlayer {
public:
    // �Đ����
    enum STATE {
        STATE_NONE, STATE_PLAY, STATE_PAUSE, STATE_STOP
    };

public:
    PCMPlayer();
    PCMPlayer(IDirectSound8* prm_pDS8);
    PCMPlayer(IDirectSound8* prm_pDS8, PCMDecoder* prm_pDecoder);

    virtual ~PCMPlayer(); //virtual �ǉ�

    //! �f�o�C�X�ݒ�
    void setDevice(IDirectSound8* prm_pDS8);

    //! PCM�f�R�[�_��ݒ�
    bool setDecoder(PCMDecoder* prm_pPcmDecoder);
    //! �Đ�
    bool play(bool prm_is_looping);

    //! �ꎞ��~
    void pause();
    void unpause();
    //! ��~
    void stop();

    //! ���ʂ�ς���
    void setVolume(int volume);

    //! �p���̈ʒu��ς���
    void setPan(int pan);

    //! �N���A
    void clear();

    //! ��Ԏ擾
    STATE getState();

public:
    //! �Đ����̃X���b�h���~
    void terminateThread();

    //! �Đ����̃X���b�h���~
    void terminateThreadWait();

    //! �o�b�t�@������������
    bool initializeBuffer();

    //! �o�b�t�@�R�s�[�X���b�h����
    static void __cdecl streamThread(void* player);

    //! �����ł����H
    bool isReady();

    //! �Đ����H
    bool isPlaying();

public:
    IDirectSound8* _pDS8; //!< �T�E���h�f�o�C�X
    IDirectSoundBuffer8* _pDSBuffer; //!< �Z�J���_���o�b�t�@
    PCMDecoder* _pPCMDecoder;
    WAVEFORMATEX _wave_format; //!< WAVEFORMATEX�\����
    DSBUFFERDESC _buffer_desc; //!< DSBUFFERDESC�\����
    bool _is_ready; //!< �����ł����H
    unsigned int _hnd_thread; //!< �X�g���[���Đ��X���b�h�n���h��
    bool _is_terminate; //!< �X���b�h��~
    bool _is_looping; //!< ���[�v����H
    STATE _state; //!< �Đ����
};
}

#endif
