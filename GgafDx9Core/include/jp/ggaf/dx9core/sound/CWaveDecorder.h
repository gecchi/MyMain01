﻿/****************************************************************
 *			waveデコーダ制御クラス
 *	@author		Ander/Echigo-ya koubou
 ****************************************************************/

#ifndef	_INCLUDE_WAVEDECORDER_HPP
#define	_INCLUDE_WAVEDECORDER_HPP

#include <mmreg.h>
#include <mmsystem.h>
namespace GgafDx9Core {
/**
 @brief		Waveファイルデコーダ
 */
class CWaveDecorder {
private:
    WAVEFORMATEX* m_pwfx; /// Waveフォーマット
    HMMIO m_hmmioIn; /// MM I/Oハンドル
    MMCKINFO m_ckIn; /// Multimedia RIFF chunk
    MMCKINFO m_ckInRiff; /// Use in opening a WAVE file

    /**
     @brief		MM I/Oの読み込み
     */
    int readMMIO(void);

public:
    virtual ~CWaveDecorder(void);

    CWaveDecorder(void);

    /**
     @brief		Waveファイルを開く
     */
    int Open(LPSTR lpszFilename);
    /**
     @brief		Waveファイルを閉じる
     */
    void Close(void);

    /**
     @brief		バッファ読み出し位置を指定
     @param		lPosition		バッファ読み出し位置(offsetで指定)
     */
    int SetPosition(long lPosition);

    /**
     @brief		Waveデータの転送
     @return		0以上：転送されたバイト数／負数：NG
     */
    long GetWave(LPBYTE lpDest, long lSize);
    /**
     @brief		Waveデータのサイズを取得
     */
    DWORD GetWaveSize(void);

    /**
     @brief		WaveFormatの取得
     */
    WAVEFORMATEX* GetWaveFormat(void);

};

}
#endif	//	_INCLUDE_WAVEDECORDER_HPP

