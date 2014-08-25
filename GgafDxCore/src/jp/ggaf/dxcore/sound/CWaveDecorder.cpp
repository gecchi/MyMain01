#include "jp/ggaf/dxcore/sound/CWaveDecorder.h"

using namespace GgafDxCore;

/****************************************************************
 *			waveデコーダ制御クラス
 *	@author		Ander/Echigo-ya koubou
 ****************************************************************/
/**
 @brief		MM I/Oの読み込み
 */
int CWaveDecorder::readMMIO(void) {
    MMCKINFO ckIn; // chunk info. for general use.
    PCMWAVEFORMAT pcmWaveFormat; // Temp PCM structure to load in.

    m_pwfx = nullptr;

    if ((0 != mmioDescend(m_hmmioIn, &m_ckInRiff, nullptr, 0))) {
        return false;
    }

    if ((m_ckInRiff.ckid != FOURCC_RIFF) || (m_ckInRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E'))) {
        return false;
    }

    // Search the input file for for the 'fmt ' chunk.
    ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (0 != mmioDescend(m_hmmioIn, &ckIn, &m_ckInRiff, MMIO_FINDCHUNK)) {
        return false;
    }

    // Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
    // if there are extra parameters at the end, we'll ignore them
    if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT)) {
        return false;
    }

    // Read the 'fmt ' chunk into <pcmWaveFormat>.
    if (mmioRead(m_hmmioIn, (HPSTR) & pcmWaveFormat, sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat)) {
        return false;
    }

    // Allocate the waveformatex, but if its not pcm format, read the next
    // word, and thats how many extra bytes to allocate.
    if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM) {
        m_pwfx = NEW WAVEFORMATEX;

        // Copy the bytes from the pcm structure to the waveformatex structure
        memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
        m_pwfx->cbSize = 0;
    } else {
        // Read in length of extra bytes.
        WORD cbExtraBytes = 0L;
        if (mmioRead(m_hmmioIn, (CHAR*) &cbExtraBytes, sizeof(WORD)) != sizeof(WORD)) {
            return false;
        }

        m_pwfx = (WAVEFORMATEX*)NEW CHAR[ sizeof(WAVEFORMATEX) + cbExtraBytes ];

        // Copy the bytes from the pcm structure to the waveformatex structure
        memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
        m_pwfx->cbSize = cbExtraBytes;

        // Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
        if (mmioRead(m_hmmioIn,
                     (CHAR*) ( ((BYTE*) &(m_pwfx->cbSize)) + sizeof(WORD) ),
                     cbExtraBytes
                    ) != cbExtraBytes) {
            GGAF_DELETE(m_pwfx);
            m_pwfx = nullptr;
            return false;
        }
    }

    // Ascend the input file out of the 'fmt ' chunk.
    if (0 != mmioAscend(m_hmmioIn, &ckIn, 0)) {
        GGAF_DELETE(m_pwfx);
        m_pwfx = nullptr;
        return false;
    }

    return true;
}

CWaveDecorder::~CWaveDecorder(void) {
    Close();
}

CWaveDecorder::CWaveDecorder(void) :
    m_pwfx(nullptr), m_hmmioIn(nullptr) {
}

/**
 @brief		Waveファイルを開く
 */
int CWaveDecorder::Open(LPSTR lpszFilename) {
    if (nullptr == (m_hmmioIn = mmioOpen(lpszFilename, nullptr, MMIO_ALLOCBUF | MMIO_READ))) {
        return false;
    }

    if (!readMMIO()) {
        mmioClose(m_hmmioIn, 0);
        return false;
    }

    if (!SetPosition(0)) {
        Close();
        return false;
    }

    return true;
}
/**
 @brief		Waveファイルを閉じる
 */
void CWaveDecorder::Close(void) {
    if (m_pwfx) {
        GGAF_DELETE_NULLABLE(m_pwfx);
        mmioClose(m_hmmioIn, 0);
    }
}

/**
 @brief		バッファ読み出し位置を指定
 @param		lPosition		バッファ読み出し位置(offsetで指定)
 */
int CWaveDecorder::SetPosition(long lPosition) {
    // Seek to the data
    if (-1 == mmioSeek(m_hmmioIn, m_ckInRiff.dwDataOffset + sizeof(FOURCC) + lPosition, SEEK_SET)) {
        return false;
    }

    // Search the input file for for the 'data' chunk.
    m_ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (0 != mmioDescend(m_hmmioIn, &m_ckIn, &m_ckInRiff, MMIO_FINDCHUNK)) {
        return false;
    }

    return true;
}

/**
 @brief		Waveデータの転送
 @return		0以上：転送されたバイト数／負数：NG
 */
long CWaveDecorder::GetWave(LPBYTE lpDest, long lSize) {
    long lReadSize = 0;
    MMIOINFO mmioinfoIn; // current status of <hmmioIn>

    if (0 != mmioGetInfo(m_hmmioIn, &mmioinfoIn, 0)) {
        return -1L;
    }

    UINT cbDataIn = lSize;
    if (cbDataIn > m_ckIn.cksize) {
        cbDataIn = m_ckIn.cksize;
    }

    m_ckIn.cksize -= cbDataIn;

    for (DWORD cT = 0; cT < cbDataIn; cT++) {
        // Copy the bytes from the io to the buffer.
        if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead) {
            if (0 != mmioAdvance(m_hmmioIn, &mmioinfoIn, MMIO_READ)) {
                return -1L;
            }

            if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead) {
                return -1L;
            }
        }

        // Actual copy.
        *(lpDest + cT) = *((BYTE*)mmioinfoIn.pchNext);
        mmioinfoIn.pchNext++;
    }

    if (0 != mmioSetInfo(m_hmmioIn, &mmioinfoIn, 0)) {
        return -1L;
    }

    lReadSize = cbDataIn;

    return lReadSize;
}

/**
 @brief		Waveデータのサイズを取得
 */
DWORD CWaveDecorder::GetWaveSize(void) {
    return m_ckIn.cksize;
}

/**
 @brief		WaveFormatの取得
 */
WAVEFORMATEX* CWaveDecorder::GetWaveFormat(void) {
    return m_pwfx;
}

