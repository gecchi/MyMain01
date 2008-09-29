///****************************************************************
// *			ogg Vorbisデコーダ制御クラス
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
// @brief		oggVorbisファイルデコーダ
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
//		PLAYOPTION_NONE = 0, /// オプションなし
//		PLAYOPTION_LOOP = 1, /// ループする(最初から最後まで)
//		PLAYOPTION_ABREPEAT = 2,
//	/// 指定位置のループ(Bまで到達したらAに戻る)
//	};
//
//	struct repeat_info {
//		unsigned long ulPosA;
//		unsigned long ulPosB;
//		unsigned long ulCount;
//	};
//
//private:
//	bool m_bEnable; /// ファイルを開いているか？
//	vorbis_info* m_lpVorbisInfo; /// vorbis情報
//	OggVorbis_File m_OggVorbisFile; /// oggVorbisファイル
//	FILE* m_lpFile; /// ファイルポインタ
//	int m_nBitStream; ///
//
//	unsigned long m_dwPlayMode; /// プレイオプション
//	repeat_info m_RepeatInfo; /// ABリピート情報
//	unsigned long m_ulPlayPosition; /// 演奏位置
//
//public:
//	virtual ~COggDecorder(void);
//	COggDecorder(void);
//
//	/**
//	 @brief		ファイルを閉じる
//	 @note		この関数はOpenされていない状態で呼び出された場合は何もしない
//	 */
//	void Close(void);
//
//	/**
//	 @brief		ファイルを開く
//	 @param		szFileName		ファイル名
//	 */
//	int Open(LPCTSTR szFileName);
//	/**
//	 @brief		Waveデータを転送する
//	 @param		lpDest		Waveデータの転送先
//	 @param		lBufferSize	転送するバッファサイズ
//	 */
//	int GetWave(char* lpDest, long lBufferSize);
//
//	int SetPlayPosition(unsigned long ulPosition);
//
//	/**
//	 @brief		vorbis_infoの取得
//	 */
//	int GetVorbisInfo(vorbis_info& vorbisInfo);
//
//	/**
//	 @brief		ループ(最後まで演奏完了後、先頭に戻る)を設定する
//	 */
//	void SetPlayModeLoop(bool bEnable);
//
//	/**
//	 @brief		ABリピート(Bの位置まで演奏が到達すると、Aの位置へ戻る)を設定する
//	 */
//	void SetPlayModeABRepeat(const repeat_info& repeatInfo);
//};
//
//#endif	// _INCLUDE_OGGDECORDER_HPP
