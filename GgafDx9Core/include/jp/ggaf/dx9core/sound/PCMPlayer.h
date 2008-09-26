// PCMPlayer.h
//

#ifndef IKD_DIX_PCMPLAYER_H
#define IKD_DIX_PCMPLAYER_H

//#include "DixSmartPtr.h"
//#include "PCMDecoder.h"
//#include "DixComPtr.h"
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
		PCMPlayer( Com_ptr< IDirectSound8 > cpDS8 );
		PCMPlayer( Com_ptr< IDirectSound8 > cpDS8, sp< PCMDecoder > spDecoder );

		~PCMPlayer();

		//! �f�o�C�X�ݒ�
		void setDevice( Com_ptr< IDirectSound8 > cpDS8 );

		//! PCM�f�R�[�_��ݒ�
		bool setDecoder( sp< PCMDecoder > pcmDecoder );

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

	private:
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

		//! ��Ԏ擾
		STATE getState();

	private:
		sp< PCMDecoder >				spPCMDecoder_;		//!< �Đ��Ώۃf�R�[�h
		WAVEFORMATEX					waveFormat_;		//!< WAVEFORMATEX�\����
		DSBUFFERDESC					DSBufferDesc_;		//!< DSBUFFERDESC�\����
		Com_ptr< IDirectSound8 >		cpDS8_;				//!< �T�E���h�f�o�C�X
		Com_ptr< IDirectSoundBuffer8 >	cpDSBuffer_;		//!< �Z�J���_���o�b�t�@
		bool							isReady_;			//!< �����ł����H
		unsigned int					threadHandle_;		//!< �X�g���[���Đ��X���b�h�n���h��
		bool							isTerminate_;		//!< �X���b�h��~
		bool							isLoop_;			//!< ���[�v����H
		STATE							state_;				//!< �Đ����
	};
}

#endif
