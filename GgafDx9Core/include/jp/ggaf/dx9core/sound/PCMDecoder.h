// PCMDecoder.h
//

#ifndef IKD_DIX_PCMDECODER_H
#define IKD_DIX_PCMDECODER_H

//#include <windows.h>
//#include <mmsystem.h>

	class PCMDecoder {
	public:
		//! �R���X�g���N�^
		PCMDecoder();

		//! �f�X�g���N�^
		virtual ~PCMDecoder();

		//! �Z�O�����g�擾
		virtual bool getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd ) = 0;

		//! ���o��
		virtual void setHead() = 0;

	public:
		//! �N���A
		virtual void clear();

		//! ���[�v�t���O�擾
		bool isLoop();

		//! �����ł����H
		bool isReady();

		//! ���[�v��ݒ�
		void setLoop( bool isLoop );

		//! WAVEFORMATEX�\���̂��擾
		bool getWaveFormatEx( WAVEFORMATEX& waveFormatEx );

	protected:
		//! �����t���O�ݒ�
		void setReady( bool isReady );

		//! �`�����l�����ݒ�
		void setChannelNum( unsigned int channeNum );

		//! �T���v�����O���[�g��ݒ�
		void setSamplingRate( unsigned int samplingRate );

		//! �r�b�g���[�g��ݒ�
		void setBitRate( unsigned int bitRate );

	protected:
		bool isLoop_;				//!< ���[�v����H
		bool isReady_;				//!< �����ł����H
		unsigned int channelNum_;	//!< �`�����l����
		unsigned int samplingRate_;	//!< �T���v�����O���[�g
		unsigned int bitRate_;		//!< �r�b�g���[�g
	};

#endif
