///****************************************************************
// *			ogg Vorbis�f�R�[�_����N���X
// *	@author		Ander/Echigo-ya koubou
// ****************************************************************/
//
//#ifndef	_INCLUDE_OGGDECORDER_HPP
//#define	_INCLUDE_OGGDECORDER_HPP
//
////#include <fstream>
////#include "vorbis/codec.h"
////#include "vorbis/vorbisfile.h"
//
///**
// @brief		oggVorbis�t�@�C���f�R�[�_
// */
//class COggDecorder {
//public:
//
//	enum {
//		GETWAVE_RESULT_CONTINUE = 0,
//		GETWAVE_RESULT_COMPLETE = 1,
//		GETWAVE_RESULT_FAIL = -1,
//	};
//
//	enum {
//		PLAYOPTION_NONE = 0, /// �I�v�V�����Ȃ�
//		PLAYOPTION_LOOP = 1, /// ���[�v����(�ŏ�����Ō�܂�)
//		PLAYOPTION_ABREPEAT = 2,
//	/// �w��ʒu�̃��[�v(B�܂œ��B������A�ɖ߂�)
//	};
//
//	struct repeat_info {
//		unsigned long ulPosA;
//		unsigned long ulPosB;
//		unsigned long ulCount;
//	};
//
//private:
//	bool m_bEnable; /// �t�@�C�����J���Ă��邩�H
//	vorbis_info* m_lpVorbisInfo; /// vorbis���
//	OggVorbis_File m_OggVorbisFile; /// oggVorbis�t�@�C��
//	FILE* m_lpFile; /// �t�@�C���|�C���^
//	int m_nBitStream; ///
//
//	unsigned long m_dwPlayMode; /// �v���C�I�v�V����
//	repeat_info m_RepeatInfo; /// AB���s�[�g���
//	unsigned long m_ulPlayPosition; /// ���t�ʒu
//
//public:
//	virtual ~COggDecorder(void);
//	COggDecorder(void);
//
//	/**
//	 @brief		�t�@�C�������
//	 @note		���̊֐���Open����Ă��Ȃ���ԂŌĂяo���ꂽ�ꍇ�͉������Ȃ�
//	 */
//	void Close(void);
//
//	/**
//	 @brief		�t�@�C�����J��
//	 @param		szFileName		�t�@�C����
//	 */
//	int Open(LPCTSTR szFileName);
//	/**
//	 @brief		Wave�f�[�^��]������
//	 @param		lpDest		Wave�f�[�^�̓]����
//	 @param		lBufferSize	�]������o�b�t�@�T�C�Y
//	 */
//	int GetWave(char* lpDest, long lBufferSize);
//
//	int SetPlayPosition(unsigned long ulPosition);
//
//	/**
//	 @brief		vorbis_info�̎擾
//	 */
//	int GetVorbisInfo(vorbis_info& vorbisInfo);
//
//	/**
//	 @brief		���[�v(�Ō�܂ŉ��t������A�擪�ɖ߂�)��ݒ肷��
//	 */
//	void SetPlayModeLoop(bool bEnable);
//
//	/**
//	 @brief		AB���s�[�g(B�̈ʒu�܂ŉ��t�����B����ƁAA�̈ʒu�֖߂�)��ݒ肷��
//	 */
//	void SetPlayModeABRepeat(const repeat_info& repeatInfo);
//};
//
//#endif	// _INCLUDE_OGGDECORDER_HPP
