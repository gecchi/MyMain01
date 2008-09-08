/****************************************************************
 *			ogg Vorbis�f�R�[�_����N���X
 *	@author		Ander/Echigo-ya koubou
 ****************************************************************/

#ifndef	_INCLUDE_OGGDECORDER_HPP
#define	_INCLUDE_OGGDECORDER_HPP

#include <fstream>
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

/**
 @brief		oggVorbis�t�@�C���f�R�[�_
 */
class COggDecorder {
public:

	enum {
		GETWAVE_RESULT_CONTINUE = 0,
		GETWAVE_RESULT_COMPLETE = 1,
		GETWAVE_RESULT_FAIL = -1,
	};

	enum {
		PLAYOPTION_NONE = 0, /// �I�v�V�����Ȃ�
		PLAYOPTION_LOOP = 1, /// ���[�v����(�ŏ�����Ō�܂�)
		PLAYOPTION_ABREPEAT = 2,
	/// �w��ʒu�̃��[�v(B�܂œ��B������A�ɖ߂�)
	};

	struct repeat_info {
		unsigned long ulPosA;
		unsigned long ulPosB;
		unsigned long ulCount;
	};

private:
	bool m_bEnable; /// �t�@�C�����J���Ă��邩�H
	vorbis_info* m_lpVorbisInfo; /// vorbis���
	OggVorbis_File m_OggVorbisFile; /// oggVorbis�t�@�C��
	FILE* m_lpFile; /// �t�@�C���|�C���^
	int m_nBitStream; ///

	unsigned long m_dwPlayMode; /// �v���C�I�v�V����
	repeat_info m_RepeatInfo; /// AB���s�[�g���
	unsigned long m_ulPlayPosition; /// ���t�ʒu

public:
	virtual ~COggDecorder(void) {
		Close();
	}

	COggDecorder(void) :
		m_bEnable(false), m_lpVorbisInfo(NULL), m_lpFile(NULL), m_dwPlayMode(
				PLAYOPTION_NONE) {
	}

	/**
	 @brief		�t�@�C�������
	 @note		���̊֐���Open����Ă��Ȃ���ԂŌĂяo���ꂽ�ꍇ�͉������Ȃ�
	 */
	void Close(void) {
		if (m_bEnable) {
			// �t�@�C�������
			ov_clear(&m_OggVorbisFile);
			fclose(m_lpFile);
			m_lpFile = NULL;
			m_bEnable = false;
		}
	}

	/**
	 @brief		�t�@�C�����J��
	 @param		szFileName		�t�@�C����
	 */
	int Open(LPCTSTR szFileName) {
		// open File
		m_lpFile = fopen(szFileName, "rb");
		if (m_lpFile == NULL) {
			return false;
		}

		// open vorbis file
		if (ov_open(m_lpFile, &m_OggVorbisFile, NULL, 0) < 0) {
			fclose(m_lpFile);
			return false;
		}

		// get vorbis info
		m_lpVorbisInfo = ov_info(&m_OggVorbisFile, -1);
		if (m_lpVorbisInfo == NULL) {
			ov_clear(&m_OggVorbisFile);
			fclose(m_lpFile);
			return false;
		}

		m_bEnable = true;
		m_ulPlayPosition = 0;

		return true;
	}
	/**
	 @brief		Wave�f�[�^��]������
	 @param		lpDest		Wave�f�[�^�̓]����
	 @param		lBufferSize	�]������o�b�t�@�T�C�Y
	 */
	int GetWave(char* lpDest, long lBufferSize) {
		//size_t nSize = 0;

		for (; lBufferSize > 0;) {
			int nRet = ov_read(&m_OggVorbisFile, lpDest, lBufferSize, 0, 2, 1,
					&m_nBitStream);

			if (nRet <= 0) {
				if (m_dwPlayMode & PLAYOPTION_LOOP) {
					ov_pcm_seek(&m_OggVorbisFile, 0);
				} else {
					return GETWAVE_RESULT_COMPLETE;
				}
			} else {
				m_ulPlayPosition += nRet;
				if (m_dwPlayMode & PLAYOPTION_ABREPEAT) {
					if (m_ulPlayPosition >= m_RepeatInfo.ulPosB) {
						nRet -= m_ulPlayPosition - m_RepeatInfo.ulPosB;
						ov_pcm_seek(&m_OggVorbisFile, m_RepeatInfo.ulPosA / 4);
						m_ulPlayPosition = m_RepeatInfo.ulPosA;
					}
				}

				lpDest += nRet;
				lBufferSize -= nRet;
			}
		}
		return GETWAVE_RESULT_CONTINUE;
	}

	int SetPlayPosition(unsigned long ulPosition) {
		if (!m_bEnable) {
			return false;
		}

		ov_pcm_seek(&m_OggVorbisFile, ulPosition);

		return true;
	}

	/**
	 @brief		vorbis_info�̎擾
	 */
	int GetVorbisInfo(vorbis_info& vorbisInfo) {
		if (!m_bEnable) {
			return false;
		}
		vorbisInfo = *m_lpVorbisInfo;
		return true;
	}

	/**
	 @brief		���[�v(�Ō�܂ŉ��t������A�擪�ɖ߂�)��ݒ肷��
	 */
	void SetPlayModeLoop(bool bEnable) {
		m_dwPlayMode &= PLAYOPTION_LOOP;
		m_dwPlayMode |= (bEnable * PLAYOPTION_LOOP);
	}

	/**
	 @brief		AB���s�[�g(B�̈ʒu�܂ŉ��t�����B����ƁAA�̈ʒu�֖߂�)��ݒ肷��
	 */
	void SetPlayModeABRepeat(const repeat_info& repeatInfo) {
		m_dwPlayMode |= PLAYOPTION_ABREPEAT;

		m_RepeatInfo = repeatInfo;
	}

};

#endif	// _INCLUDE_OGGDECORDER_HPP
