#include "stdafx.h"

/****************************************************************
 *			ogg Vorbisデコーダ制御クラス
 *	@author		Ander/Echigo-ya koubou
 ****************************************************************/

	COggDecorder::~COggDecorder(void) {
		Close();
	}

	COggDecorder::COggDecorder(void) :
		m_bEnable(false), m_lpVorbisInfo(NULL), m_lpFile(NULL), m_dwPlayMode(
				PLAYOPTION_NONE) {
	}

	/**
	 @brief		ファイルを閉じる
	 @note		この関数はOpenされていない状態で呼び出された場合は何もしない
	 */
	void COggDecorder::Close(void) {
		if (m_bEnable) {
			// ファイルを閉じる
			ov_clear(&m_OggVorbisFile);
			fclose(m_lpFile);
			m_lpFile = NULL;
			m_bEnable = false;
		}
	}

	/**
	 @brief		ファイルを開く
	 @param		szFileName		ファイル名
	 */
	int COggDecorder::Open(LPCTSTR szFileName) {
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
	 @brief		Waveデータを転送する
	 @param		lpDest		Waveデータの転送先
	 @param		lBufferSize	転送するバッファサイズ
	 */
	int COggDecorder::GetWave(char* lpDest, long lBufferSize) {
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

	int COggDecorder::SetPlayPosition(unsigned long ulPosition) {
		if (!m_bEnable) {
			return false;
		}

		ov_pcm_seek(&m_OggVorbisFile, ulPosition);

		return true;
	}

	/**
	 @brief		vorbis_infoの取得
	 */
	int COggDecorder::GetVorbisInfo(vorbis_info& vorbisInfo) {
		if (!m_bEnable) {
			return false;
		}
		vorbisInfo = *m_lpVorbisInfo;
		return true;
	}

	/**
	 @brief		ループ(最後まで演奏完了後、先頭に戻る)を設定する
	 */
	void COggDecorder::SetPlayModeLoop(bool bEnable) {
		m_dwPlayMode &= PLAYOPTION_LOOP;
		m_dwPlayMode |= (bEnable * PLAYOPTION_LOOP);
	}

	/**
	 @brief		ABリピート(Bの位置まで演奏が到達すると、Aの位置へ戻る)を設定する
	 */
	void COggDecorder::SetPlayModeABRepeat(const repeat_info& repeatInfo) {
		m_dwPlayMode |= PLAYOPTION_ABREPEAT;

		m_RepeatInfo = repeatInfo;
	}

