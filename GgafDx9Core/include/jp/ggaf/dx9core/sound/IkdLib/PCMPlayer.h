// PCMPlayer.h
//

#ifndef IKD_DIX_PCMPLAYER_H
#define IKD_DIX_PCMPLAYER_H

//#include "DixSmartPtr.hpp"
//#include "DixComPtr.h"
//#include "PCMDecoder.h"
//#include "dsound.h"

namespace Dix {
    class PCMPlayer {
    public:
        // �Đ����
        enum STATE {
            STATE_NONE,
            STATE_PLAY,
            STATE_PAUSE,
            STATE_STOP
        };

    public:
        PCMPlayer();
        PCMPlayer( IDirectSound8* pDS8 );
        //PCMPlayer( IDirectSound8* pDS8, sp< PCMDecoder > spDecoder );
        PCMPlayer( IDirectSound8* pDS8, PCMDecoder* spDecoder );

        virtual ~PCMPlayer(); //tsuge virtual �ǉ�

        //! �f�o�C�X�ݒ�
        void setDevice(IDirectSound8* pDS8 );

        //! PCM�f�R�[�_��ݒ�
        //bool setDecoder( sp< PCMDecoder > pcmDecoder );
        bool setDecoder( PCMDecoder* pcmDecoder );
        //! �Đ�
        bool play( bool isLoop );

        //! �ꎞ��~
        void pause();

        //! ��~
        void stop();

        //! ���ʂ�ς���
        void setVolume( int volume );

        //! �p���̈ʒu��ς���
        void setPan( int pan );

        //! �N���A
        void clear();

        //! ��Ԏ擾
        STATE getState();


    public:
        //! �Đ����̃X���b�h���~
        void terminateThread();

        //! �o�b�t�@������������
        bool initializeBuffer();

        //! �o�b�t�@�R�s�[�X���b�h����
        static void __cdecl streamThread( void* player );

        //! �����ł����H
        bool isReady();

        //! �Đ����H
        bool isPlaying();


    public:
        //sp< PCMDecoder >				spPCMDecoder_;		//!< �Đ��Ώۃf�R�[�h
        PCMDecoder*                     spPCMDecoder_;
        WAVEFORMATEX					waveFormat_;		//!< WAVEFORMATEX�\����
        DSBUFFERDESC					DSBufferDesc_;		//!< DSBUFFERDESC�\����
        IDirectSound8*                  pDS8_;				//!< �T�E���h�f�o�C�X
        IDirectSoundBuffer8*            pDSBuffer_;		//!< �Z�J���_���o�b�t�@
        bool							isReady_;			//!< �����ł����H
        unsigned int					threadHandle_;		//!< �X�g���[���Đ��X���b�h�n���h��
        bool							isTerminate_;		//!< �X���b�h��~
        bool							isLoop_;			//!< ���[�v����H
        STATE							state_;				//!< �Đ����
    };
}

#endif
