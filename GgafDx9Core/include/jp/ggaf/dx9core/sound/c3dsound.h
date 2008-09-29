/******************************************************************************
 * DirectSound制御クラス
 *	@author		Ander/Echigo-ya koubou
 ******************************************************************************/

// このプログラムのオリジナルは、「越後屋Cyber」のメンバーのAnder氏が、
// Blogで公開していたサンプルプログラムです。
// 当時、DirectSound + ogg のストリーミング再生で悩んでいた日々から解き放たれ、
// 頭上から光が差し込まれた思いでした。
// 有益なサンプルを開発・公開して下さったAnder氏に感謝しつつ、流用させて頂きます。
//
//                                2008/03/25 Masatoshi Tsuge
//
// 【対象コード】
// c3dsound.hpp, oggdecorder.hpp, wavedecorder.hpp
// 【越後屋Cyber】
// http://www.e-cyber.org/
// 【Ander氏Blog:サンプル公開の記事】
// http://ecyber.exblog.jp/824656/

#ifndef	_INCLUDE_C3DSOUND_HPP
#define	_INCLUDE_C3DSOUND_HPP

#include <MMSystem.h>
#include <dxerr9.h>
#include <dsound.h>
#include <vector>
#include <map>
#include <algorithm>

//#include "wavedecorder.hpp"
//#include "oggdecorder.hpp"

#ifndef	SAFE_RELEASE
#define	SAFE_RELEASE( x )		{if( x ){(x)->Release();(x)=NULL;}}
#endif	// SAFE_RELEASE
static const int _DS_MINVOLUME_ = -9600;
static const int _DS_PAN_LEFT_ = -10000;
static const int _DS_PAN_RIGHT_ = 10000;

/**
 @brief		DirectSound制御クラス
 */
class CC3DSound {
public:
	/**
	 @brief		SoundBuffer基本クラス
	 */
	class CC3DSoundBuffer {
	public:
		virtual ~CC3DSoundBuffer(void) {
		}
		virtual void Release(void) {
		}
		virtual int Play(long, long) {
			return true;
		}
		virtual int Stop(void) {
			return true;
		}
		virtual int SetVolume(long) {
			return true;
		}
		virtual int SetPan(long) {
			return true;
		}
	};

	/// ボリューム設定コンテナタイプ
	typedef std::map< unsigned int, float> float_map;

	typedef std::vector< CC3DSoundBuffer*> soundbuffer_vector;

private:
//	LPDIRECTSOUND8 GgafDx9Sound::_pIDirectSound8; /// DirectSound
	DSCAPS m_dsCaps; ///
	float_map m_mapVolume; /// ボリューム設定
	float m_fMasterVolume; /// マスタボリューム
	soundbuffer_vector m_vecSoundBuffer; /// 登録されたサウンドバッファ

public:
	virtual ~CC3DSound(void);
	CC3DSound(void);
	void Release(void);

	/**
	 @brief		Sound機能を有効にする
	 @param		hWnd		Windowハンドル
	 @return		true:OK/false:NG
	 @note		DirectSound作成および各種初期設定。
	 */
	int CreateSound(HWND hWnd);
	/**
	 @brief		DirectSoundオブジェクトの取得
	 @return		DirectSoundオブジェクト
	 */
	LPDIRECTSOUND8 GetDirectSound(void);
	/**
	 @brief		ボリューム設定を登録
	 @param		uiID		ボリューム設定ID
	 @param		fVolume		ボリューム(0.0～1.0)
	 @return		true:OK/false:NG
	 @note		SE/BGMなど別々にボリュームを設定する場合に使用する。
	 */
	int SetVolumeSetting(unsigned int uiID, float fVolume);
	/**
	 @brief	ボリューム設定からボリュームを取得
	 */
	long GetVolume(unsigned int uiID, long lVolumeSrc);

	/**
	 @brief		ボリューム設定の取得
	 @param		uiID		取得するボリューム設定のID
	 @return		ボリューム設定
	 */
	float GetVolumeSetting(unsigned int uiID);

	/**
	 @brief		マスタボリュームの設定
	 @param		fVolume		設定するボリューム値
	 @return		true:OK/false:NG
	 @note		マスタボリュームの初期値は1.0。
	 */
	int SetMasterVolume(float fVolume);
	/**
	 @brief		マスタボリュームの取得
	 @return		マスタボリューム値
	 */
	float GetMasterVolume(void);

	/**
	 @brief		DirectSound性能の取得
	 */
	int GetDirectSoundCaps(DSCAPS& dsCaps);
	/**
	 @brief		SoundBufferを登録する
	 @note		サウンドバッファを登録することで、Soundクラスの解放(Release)時に
	 全てのサウンドバッファを解放できる。(Leak対策)
	 */
	int RegistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer);
	/**
	 @brief		SoundBufferの登録を解除する
	 @note		サウンドバッファの解放時にサウンドバッファから呼びだす。
	 */
	int UnregistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer);

	/**
	 @brief		全てのバッファの演奏を停止する
	 */
	int Stop(void);
};

/**
 @brief		SE用サウンドバッファ制御クラス
 */
class CC3DSoundBufferSE: public CC3DSound::CC3DSoundBuffer {
private:
	LPDIRECTSOUNDBUFFER m_lpdsBuffer; /// サウンドバッファ
	CC3DSound* m_lpc3dSound; /// Soundのポインタ
	std::string m_strFilename; /// ファイル名
	UINT m_uiVolumeSettingID; /// ボリューム設定ID

	/**
	 @brief		バッファへWaveデータを転送
	 */
	int writeBuffer(CWaveDecorder& WaveFile);
	/**
	 @brief		SoundBufferの復帰
	 */
	int restore(void);

public:
	virtual ~CC3DSoundBufferSE(void);
	CC3DSoundBufferSE(void);

	CC3DSoundBufferSE(const CC3DSoundBufferSE& c3dsb);

	/**
	 @brief		SEの解放
	 @note		この関数はCreateされていない状態で呼び出された場合、何もしない
	 */
	void Release(void);

	/**
	 @brief		SEの作成
	 @param		lpszFileName		ファイル名
	 @param		c3dSound			Soundクラス
	 @return		true:OK/false:NG
	 */
	int Create(LPCSTR lpszFileName, CC3DSound& c3dSound,
			UINT uiVolumeSettingID = 0);

	/**
	 @brief		SEを鳴らす
	 @param		lVolume		ボリューム(min:-9600 max:0)
	 @param		lPan		パン(left:-10000 right:10000)
	 @return		true:OK/false:NG
	 */
	int Play(long lVolume, long lPan);

	/**
	 @brief		バッファの複製
	 @param		c3dsbSE		コピー元
	 */
	int operator =(const CC3DSoundBufferSE& c3dsbSE);
};

/**
 @brief		SE制御クラス
 @note		同じのSEを同時に再生できるように、ひとつのSEにつき複数のバッファを確保している
 */
class CC3DSoundSE: public CC3DSound::CC3DSoundBuffer {
private:
	CC3DSoundBufferSE* m_lpSoundBuffer; /// SoundBufferクラスの配列
	unsigned int m_uiBufferIndex; /// 次に再生するSoundBuffer
	unsigned int m_uiBufferCount; /// SoundBufferの確保数

public:
	virtual ~CC3DSoundSE(void);

	CC3DSoundSE(void);

	/**
	 @brief		SEを解放する
	 @note		この関数はCreateされずに呼ばれた場合は何もしない
	 */
	void Release(void);

	/**
	 @brief		SEの作成
	 @param		c3dSound			Soundクラス
	 @param		lpszFilename		ファイル名(wav)
	 @param		nBufferCount		バッファの確保数(このSEを同時に再生する最大数)
	 @param		uiVolumeSettingID	ボリューム設定ID(SOUNDのマスタボリューム設定)
	 @return		true:OK/false:NG
	 */
	int CreateSE(CC3DSound& c3dSound, LPCSTR lpszFilename,
			unsigned int nBufferCount, UINT uiVolumeSettingID = 0);

	/**
	 @brief		SEを鳴らす
	 @param		lVolume		ボリューム(min:-9600 max:0)
	 @param		lPan		パン(left:-10000 right:10000)
	 @return		true:OK/false:NG
	 */
	int Play(long lVolume, long lPan);

};


/**
 @brief		oggファイルの再生
 */
//class CC3DSoundBGM: public CC3DSound::CC3DSoundBuffer {
//public:
//
//	struct fade_effect {
//		DWORD dwEffect;
//		long lVolumeSpeed;
//		long lVolumeTo;
//		long lPanSpeed;
//		long lPanTo;
//
//		enum {
//			FADEEFFECT_NONE = 0,
//			FADEEFFECT_VOLUME = 1,
//			FADEEFFECT_PAN = 2,
//			FADEEFFECT_FADEOUT = 4,
//		};
//	};
//
//	struct play_info {
//		long lVolume;
//		long lPan;
//
//		int operator +=(fade_effect& fadeEffect) {
//			bool bUpdate = false;
//			if (fadeEffect.dwEffect & fadeEffect.FADEEFFECT_VOLUME) {
//				lVolume += fadeEffect.lVolumeSpeed;
//				if ((fadeEffect.lVolumeSpeed < 0 && lVolume
//						<= fadeEffect.lVolumeTo) || (fadeEffect.lVolumeSpeed
//						> 0 && lVolume >= fadeEffect.lVolumeTo)) {
//					fadeEffect.dwEffect &= ~fadeEffect.FADEEFFECT_VOLUME;
//					lVolume = fadeEffect.lVolumeTo;
//				}
//				bUpdate = true;
//			}
//			if (fadeEffect.dwEffect & fadeEffect.FADEEFFECT_PAN) {
//				lPan += fadeEffect.lPanSpeed;
//				if ((fadeEffect.lPanSpeed < 0 && lPan <= fadeEffect.lPanTo)
//						|| (fadeEffect.lPanSpeed > 0 && lPan
//								>= fadeEffect.lPanTo)) {
//					fadeEffect.dwEffect &= ~fadeEffect.FADEEFFECT_PAN;
//					lPan = fadeEffect.lPanTo;
//				}
//				bUpdate = true;
//			}
//
//			return bUpdate;
//		}
//	};
//
//	void releaseNotifyObject(void);
//private:
//	/// 通知イベントハンドルのコンテナ
//	typedef std::vector< HANDLE> handle_vector;
//	/// Notifyする再生位置のコンテナ
//	typedef std::vector< DSBPOSITIONNOTIFY> notify_vector;
//
//	std::string m_strFileName; /// ファイル名
//	COggDecorder m_OggDecorder; /// oggデコーダ
//	CC3DSound* m_lpc3dSound; /// Soundクラスへのポインタ
//	LPDIRECTSOUNDBUFFER8 m_lpdsBuffer; /// SoundBuffer
//	DSBUFFERDESC m_dsBufferDesc; /// SoundBuffer情報
//	WAVEFORMATEX m_WaveFormat; /// WaveFormat
//	LPDIRECTSOUNDNOTIFY8 m_lpdsNotify; /// 通知
//	HANDLE m_hThread; /// 再生管理用スレッド
//	HANDLE m_hEventNotify; /// 再生位置の通知イベント
//	HANDLE m_hEventExit; /// スレッド終了通知用のイベント
//	DWORD m_dwThreadResult; /// スレッドの完了コード格納先
//	DWORD m_dwNextWriteOffset; /// 次の書き込みポインタのオフセット
//	notify_vector m_vecNotifyPosition; /// 再生位置通知用のコンテナ
//	DWORD m_dwNotifySize; /// Notifyサイズ
//	long m_lLastBufferCount; /// 現在バッファに設定してある数
//	bool m_bExitThread; /// スレッド終了フラグ
//	CRITICAL_SECTION m_csThread; /// スレッド通信用クリティカルセクション
//	handle_vector m_vecEvent; /// スレッドのイベント待ちハンドルコンテナ
//	long m_lNotifyCount; /// サウンドバッファの通知の細かさ
//	long m_lBufferSecond; /// サウンドバッファへ確保する時間
//	UINT m_uiVolumeSettingID; /// ボリューム設定ID
//
//	play_info m_PlayInfo; /// 演奏状態
//	fade_effect m_FadeEffect; /// フェード効果
//
//
//	/**
//	 @brief		スレッドを終了させる
//	 @note		スレッド停止指示後、タイムアウト時間停止を待つ。
//	 タイムアウトした場合、強制的にスレッドを停止させてエラーを返す。
//	 */
//	int closeThread(int nTimeOut);
//	/**
//	 @brief		SoundBufferの作成
//	 @return		true:OK/false:NG
//	 */
//	int createSoundBuffer(void);
//
//	/**
//	 @brief		再生位置の通知を作成
//	 @return		true:OK/false:NG
//	 @note		このクラスでスレッドを生成する
//	 */
//	int createNotify(void);
//
//	/**
//	 @brief		streamからバッファへ指定ブロック数分データを転送する
//	 @param		uiBlock		転送するブロック数
//	 @return		true:OK/false:NG
//	 */
//	int loadStream(UINT uiBlock);
//
//	/**
//	 @brief		エフェクトの更新
//	 */
//	int updateFadeEffect(void);
//
//	/**
//	 @brief		再生管理スレッド
//	 @note		createNotifyにより開始・Stopにより終了する
//	 */
//	DWORD ThreadProcedure(LPVOID lpParam);
//
//	void setVolume(long lVolume);
//	void setPan(long lPan);
//
//public:
//	virtual ~CC3DSoundBGM(void);
//
//	CC3DSoundBGM(void);
//	/**
//	 @brief		SoundBufferの解放
//	 @note		この関数はCreateされていない状態で呼ばれても何もしない
//	 */
//	void Release(void);
//	/**
//	 @brief		BGMの読み込み
//	 @param		c3dSound		Sound
//	 @param		lpszFilename	ファイル名(ogg)
//	 @return		true:OK/false:NG
//	 */
//	int CreateBGM(CC3DSound& c3dSound, LPCSTR lpszFilename,
//			UINT uiVolumeSettingID = 0, UINT uiNotifyCount = 16,
//			long lBufferSecond = 5);
//	/**
//	 @brief		演奏の停止
//	 @note		この関数はCreateまたはPlayされていない場合に呼ばれても何もしない
//	 */
//	int Stop(void);
//
//	/**
//	 @brief		演奏開始
//	 */
//	int Play(long lVolume = 0, long lPan = 0);
//
//	//減衰。1/100 dB (デシベル) 単位で指定する。
//	int SetVolume(long lVolume);
//	int SetPan(long lPan);
//	void SetFadeEffectVolume(long lVolumeTo, long lVolumeSpeed);
//	void SetFadeEffectPan(long lPanTo, long lPanSpeed);
//
//	int GetPlayInfo(play_info& playInfo);
//
//	static DWORD _ThreadProcedure(LPVOID lpParam);
//
//	void SetPlayModeLoop(bool bEnable);
//	void SetPlayModeABRepeat(double dfPosA, double dfPosB, ULONG ulCount);
//	int SetFadeOut(long lVolumeSpeed);
//
//	/**
//	 @brief		ファイル名の取得
//	 */
//	LPCSTR GetFileName(void);
//};

#endif	//_INCLUDE_C3DSOUND_HPP
