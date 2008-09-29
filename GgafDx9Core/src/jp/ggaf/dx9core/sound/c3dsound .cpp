#include "stdafx.h"

/******************************************************************************
 * DirectSound制御クラス
 *	@author		Ander/Echigo-ya koubou
 ******************************************************************************/

// このプログラムのオリジナルは、「越後屋Cyber」のメンバーのAnder氏が、
// Blogで公開されていたサンプルプログラムです。
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


CC3DSound::~CC3DSound(void) {
	Release();
}
CC3DSound::CC3DSound(void) :
	m_fMasterVolume(1.0f) {
}
void CC3DSound::Release(void) {
	// 解放されていないサウンドバッファを全て解放する
	soundbuffer_vector::iterator it = m_vecSoundBuffer.begin();
	for (; it != m_vecSoundBuffer.end();) {
		CC3DSoundBuffer* lpPre = *it;
		(*it)->Release();
		if (it != m_vecSoundBuffer.end() && *it == lpPre)
			it++;
	}
	m_vecSoundBuffer.clear();

//	SAFE_RELEASE( GgafDx9Sound::_pIDirectSound8 );
}

/**
 @brief		Sound機能を有効にする
 @param		hWnd		Windowハンドル
 @return		true:OK/false:NG
 @note		DirectSound作成および各種初期設定。
 */
int CC3DSound::CreateSound(HWND hWnd) {
	HRESULT hr;
	//		hr = DirectSoundCreate8(NULL, &GgafDx9Sound::_pIDirectSound8, NULL);
	//		if (FAILED(hr)) {
	//			return false;
	//		}
	//		hr = GgafDx9Sound::_pIDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY );
	//		if (FAILED(hr)) {
	//			return false;
	//		}
	// 情報の取得
	m_dsCaps.dwSize = sizeof(m_dsCaps);
	hr = GgafDx9Sound::_pIDirectSound8->GetCaps(&m_dsCaps);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

/**
 @brief		DirectSoundオブジェクトの取得
 @return		DirectSoundオブジェクト
 */
LPDIRECTSOUND8 CC3DSound::GetDirectSound(void) {
	return GgafDx9Sound::_pIDirectSound8;
}

/**
 @brief		ボリューム設定を登録
 @param		uiID		ボリューム設定ID
 @param		fVolume		ボリューム(0.0～1.0)
 @return		true:OK/false:NG
 @note		SE/BGMなど別々にボリュームを設定する場合に使用する。
 */
int CC3DSound::SetVolumeSetting(unsigned int uiID, float fVolume) {
	m_mapVolume[uiID] = fVolume;
	return true;
}

/**
 @brief	ボリューム設定からボリュームを取得
 */
long CC3DSound::GetVolume(unsigned int uiID, long lVolumeSrc) {
	float fVolumeSetting = GetVolumeSetting(uiID);

	// Volume = src * VolumeSetting * MasterVolume
	return static_cast<long> (static_cast<float> (lVolumeSrc - _DS_MINVOLUME_)
			* fVolumeSetting * m_fMasterVolume) + _DS_MINVOLUME_;
}

/**
 @brief		ボリューム設定の取得
 @param		uiID		取得するボリューム設定のID
 @return		ボリューム設定
 */
float CC3DSound::GetVolumeSetting(unsigned int uiID) {
	float_map::iterator it = m_mapVolume.find(uiID);
	if (it == m_mapVolume.end()) {
		return 1.0f;
	}
	return it->second;
}

/**
 @brief		マスタボリュームの設定
 @param		fVolume		設定するボリューム値
 @return		true:OK/false:NG
 @note		マスタボリュームの初期値は1.0。
 */
int CC3DSound::SetMasterVolume(float fVolume) {
	m_fMasterVolume = fVolume;
	return true;
}
/**
 @brief		マスタボリュームの取得
 @return		マスタボリューム値
 */
float CC3DSound::GetMasterVolume(void) {
	return m_fMasterVolume;
}

/**
 @brief		DirectSound性能の取得
 */
int CC3DSound::GetDirectSoundCaps(DSCAPS& dsCaps) {
	if (GgafDx9Sound::_pIDirectSound8 == NULL) {
		return false;
	}
	dsCaps = m_dsCaps;
	return true;
}

/**
 @brief		SoundBufferを登録する
 @note		サウンドバッファを登録することで、Soundクラスの解放(Release)時に
 全てのサウンドバッファを解放できる。(Leak対策)
 */
int CC3DSound::RegistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer) {
	m_vecSoundBuffer.push_back(lpSoundBuffer);

	return true;
}
/**
 @brief		SoundBufferの登録を解除する
 @note		サウンドバッファの解放時にサウンドバッファから呼びだす。
 */
int CC3DSound::UnregistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer) {
	soundbuffer_vector::iterator it = std::find(m_vecSoundBuffer.begin(),
			m_vecSoundBuffer.end(), lpSoundBuffer);
	if (it == m_vecSoundBuffer.end()) {
		return false;
	}
	m_vecSoundBuffer.erase(it);
	return true;
}

/**
 @brief		全てのバッファの演奏を停止する
 */
int CC3DSound::Stop(void) {
	if (GgafDx9Sound::_pIDirectSound8 == NULL) {
		return false;
	}

	for (soundbuffer_vector::iterator it = m_vecSoundBuffer.begin()
	; it != m_vecSoundBuffer.end(); it++) {
		(*it)->Stop();
	}

	return true;
}

/**
 @brief		バッファへWaveデータを転送
 */
int CC3DSoundBufferSE::writeBuffer(CWaveDecorder& WaveFile) {
	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1; // 最初のブロックのポインタ
	DWORD dwBytes1; // 最初のブロックのサイズ
	LPVOID lpvPtr2; // ２番目のブロックのポインタ
	DWORD dwBytes2; // ２番目のブロックのサイズ

	HRESULT hr;

	hr = m_lpdsBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1,
			&lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr) {
		_TRACE_("DSERR_BUFFERLOST!");
		m_lpdsBuffer->Restore();
		hr = m_lpdsBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1,
				&lpvPtr2, &dwBytes2, 0);
	}

	if (FAILED(hr)) {
		return false;
	}
	// ロック成功

	// ここで，バッファに書き込む
	// バッファにデータをコピーする
	long lSize = WaveFile.GetWave(static_cast<LPBYTE> (lpvPtr1), dwBytes1);
	if (lSize > 0 && dwBytes2 != 0) {
		lSize = WaveFile.GetWave(static_cast<LPBYTE> (lpvPtr2), dwBytes2);
	}

	// 書き込みが終わったらすぐにUnlockする．
	m_lpdsBuffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);

	if (lSize < 0) {
		return false;
	}

	return true;
}

/**
 @brief		SoundBufferの復帰
 */
int CC3DSoundBufferSE::restore(void) {
	// Waveファイルを開く
	CWaveDecorder WaveFile;
	if (!WaveFile.Open(const_cast<LPSTR> (m_strFilename.c_str()))) {
		return false;
	}

	if (!writeBuffer(WaveFile)) {
		return false;
	}
	return true;
}

CC3DSoundBufferSE::~CC3DSoundBufferSE(void) {
	Release();
}
CC3DSoundBufferSE::CC3DSoundBufferSE(void) :
	m_lpdsBuffer(NULL), m_lpc3dSound(NULL), m_uiVolumeSettingID(0) {
}

CC3DSoundBufferSE::CC3DSoundBufferSE(const CC3DSoundBufferSE& c3dsb) {
	*this = c3dsb;
}

/**
 @brief		SEの解放
 @note		この関数はCreateされていない状態で呼び出された場合、何もしない
 */
void CC3DSoundBufferSE::Release(void) {
	SAFE_RELEASE( m_lpdsBuffer );
	m_strFilename.clear();

	if (m_lpc3dSound) {
		m_lpc3dSound->UnregistSoundBuffer(this);
		m_lpc3dSound = NULL;
	}
}

/**
 @brief		SEの作成
 @param		lpszFileName		ファイル名
 @param		c3dSound			Soundクラス
 @return		true:OK/false:NG
 */
int CC3DSoundBufferSE::Create(LPCSTR lpszFileName, CC3DSound& c3dSound,
		UINT uiVolumeSettingID) {
	Release();

	HRESULT hr;

	// Waveファイルを開く
	CWaveDecorder WaveFile;
	if (!WaveFile.Open((LPSTR) lpszFileName)) {
		return false;
	}

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME
			| DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE; //DSBCAPS_LOCSOFTWAREを付け足した
	dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
	dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

	LPDIRECTSOUND8 lpDS = c3dSound.GetDirectSound();
	if (lpDS == NULL) {
		return false;
	}

	// バッファを作る
	hr = lpDS->CreateSoundBuffer(&dsbdesc, &m_lpdsBuffer, NULL);
	if (FAILED(hr)) {
		return false;
	}

	m_strFilename = lpszFileName;
	m_lpc3dSound = &c3dSound;
	m_uiVolumeSettingID = uiVolumeSettingID;

	if (!writeBuffer(WaveFile)) {
		Release();
		return false;
	}

	// Soundへ登録する
	m_lpc3dSound->RegistSoundBuffer(this);

	return true;
}

/**
 @brief		SEを鳴らす
 @param		lVolume		ボリューム(min:-9600 max:0)
 @param		lPan		パン(left:-10000 right:10000)
 @return		true:OK/false:NG
 */
int CC3DSoundBufferSE::Play(long lVolume, long lPan) {
	DWORD dwStatus;

	if (FAILED(m_lpdsBuffer->GetStatus(&dwStatus))) {
		return false;
	}
	if (dwStatus == (DWORD) DSERR_BUFFERLOST) {
		if (FAILED(m_lpdsBuffer->Restore())) {
			return false;
		}
		if (!restore()) {
			return false;
		}
	}

	m_lpdsBuffer->SetVolume(m_lpc3dSound->GetVolume(m_uiVolumeSettingID,
			lVolume));
	m_lpdsBuffer->SetPan(lPan);

	m_lpdsBuffer->SetCurrentPosition(0);
	m_lpdsBuffer->Play(0, 0, 0);
	return true;
}

/**
 @brief		バッファの複製
 @param		c3dsbSE		コピー元
 */
int CC3DSoundBufferSE::operator =(const CC3DSoundBufferSE& c3dsbSE) {
	Release();
	if (c3dsbSE.m_lpc3dSound == NULL || c3dsbSE.m_lpdsBuffer == NULL) {
		return false;
	}

	m_lpc3dSound = c3dsbSE.m_lpc3dSound;
	LPDIRECTSOUND8 lpDS = c3dsbSE.m_lpc3dSound->GetDirectSound();
	HRESULT hr;
	hr = lpDS->DuplicateSoundBuffer(c3dsbSE.m_lpdsBuffer, &m_lpdsBuffer);
	if (FAILED(hr)) {
		return false;
	}

	// Soundへ登録する
	m_lpc3dSound->RegistSoundBuffer(this);

	return true;
}

CC3DSoundSE::~CC3DSoundSE(void) {
	Release();
}

CC3DSoundSE::CC3DSoundSE(void) :
	m_lpSoundBuffer(NULL) {
}

/**
 @brief		SEを解放する
 @note		この関数はCreateされずに呼ばれた場合は何もしない
 */
void CC3DSoundSE::Release(void) {
	delete[] m_lpSoundBuffer;
	m_lpSoundBuffer = NULL;
}

/**
 @brief		SEの作成
 @param		c3dSound			Soundクラス
 @param		lpszFilename		ファイル名(wav)
 @param		nBufferCount		バッファの確保数(このSEを同時に再生する最大数)
 @param		uiVolumeSettingID	ボリューム設定ID(SOUNDのマスタボリューム設定)
 @return		true:OK/false:NG
 */
int CC3DSoundSE::CreateSE(CC3DSound& c3dSound, LPCSTR lpszFilename,
		unsigned int nBufferCount, UINT uiVolumeSettingID) {
	if (nBufferCount == 0) {
		return false;
	}
	// バッファを確保
	m_lpSoundBuffer = NEW CC3DSoundBufferSE[ nBufferCount ];

		// 先頭は普通に作成
		if (!m_lpSoundBuffer[0].Create(lpszFilename, c3dSound)){
	return false;
}

// 残りは複製
			for (unsigned int i = 1; i < nBufferCount; i++) {
				if (!(m_lpSoundBuffer[i] = m_lpSoundBuffer[0])) {
					return false;
				}
			}

			// 変数などの初期化
			m_uiBufferIndex = 0;
			m_uiBufferCount = nBufferCount;

			return true;
		}

	/**
	 @brief		SEを鳴らす
	 @param		lVolume		ボリューム(min:-9600 max:0)
	 @param		lPan		パン(left:-10000 right:10000)
	 @return		true:OK/false:NG
	 */
int CC3DSoundSE::Play(long lVolume, long lPan) {
	if (m_lpSoundBuffer == NULL) {
		return false;
	}
	int nRet = m_lpSoundBuffer[m_uiBufferIndex].Play(lVolume, lPan);
	if (!nRet)
		return nRet;

	++m_uiBufferIndex;
	if (m_uiBufferIndex >= m_uiBufferCount) {
		m_uiBufferIndex = 0;
	}

	return true;
}

//
//
//
//	void CC3DSoundBGM::releaseNotifyObject(void) {
//		if (m_lpdsNotify) {
//			// Notifyの解放
//			SAFE_RELEASE( m_lpdsNotify );
//			m_vecNotifyPosition.clear();
//
//			// イベント通知用オブジェクトを解放
//			m_vecEvent.clear();
//			CloseHandle(m_hEventNotify);
//			m_hEventNotify = NULL;
//			CloseHandle(m_hEventExit);
//			m_hEventExit = NULL;
//		}
//	}
//
//
//
//	/**
//	 @brief		スレッドを終了させる
//	 @note		スレッド停止指示後、タイムアウト時間停止を待つ。
//	 タイムアウトした場合、強制的にスレッドを停止させてエラーを返す。
//	 */
//	int CC3DSoundBGM::closeThread(int nTimeOut) {
//		if (m_hThread) {
//			// スレッドへ終了イベントを投げて終了するのを待つ
//
//			DWORD dwExitCode;
//			SetEvent(m_hEventExit);
//
//			// 終了orタイムアウトまで待つ
//			for (; nTimeOut > 0; --nTimeOut) {
//				GetExitCodeThread(m_hThread, &dwExitCode);
//				if (dwExitCode != STILL_ACTIVE) {
//					break;
//				}
//				Sleep(500);
//			}
//
//			if (nTimeOut == 0) {
//				// スレッドを強制終了させる
//				TerminateThread(m_hThread, 0);
//			}
//
//			// ハンドルを解放
//			CloseHandle(m_hThread);
//			m_hThread = NULL;
//
//			if (nTimeOut == 0) {
//				return false;
//			}
//		}
//
//		return true;
//	}
//
//	/**
//	 @brief		SoundBufferの作成
//	 @return		true:OK/false:NG
//	 */
//	int CC3DSoundBGM::createSoundBuffer(void) {
//		// vorbis情報の取得
//		vorbis_info vorbisInfo;
//		if (!m_OggDecorder.GetVorbisInfo(vorbisInfo)) {
//			return false;
//		}
//
//		ZeroMemory(&m_WaveFormat, sizeof(m_WaveFormat));
//		m_WaveFormat.nSamplesPerSec = vorbisInfo.rate;
//		m_WaveFormat.wBitsPerSample = 16; // 適当?
//		m_WaveFormat.nBlockAlign = m_WaveFormat.wBitsPerSample * vorbisInfo.channels / 8;
//		m_WaveFormat.nAvgBytesPerSec = m_WaveFormat.nBlockAlign	* m_WaveFormat.nSamplesPerSec;
//		m_WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
//		m_WaveFormat.nChannels = vorbisInfo.channels;
//
//		// SoundBufferの作成
//		ZeroMemory(&m_dsBufferDesc, sizeof(m_dsBufferDesc));
//		m_dsBufferDesc.dwSize = sizeof(m_dsBufferDesc);
//		m_dsBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCDEFER | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2;
//		m_dsBufferDesc.dwBufferBytes = m_lBufferSecond * m_WaveFormat.nAvgBytesPerSec;
//		m_dsBufferDesc.dwBufferBytes -= ((m_dsBufferDesc.dwBufferBytes/m_lNotifyCount) % 4) * m_lNotifyCount;
//		m_dsBufferDesc.guid3DAlgorithm = GUID_NULL;
//		m_dsBufferDesc.lpwfxFormat = &m_WaveFormat;
//
//		LPDIRECTSOUND8 lpDS = m_lpc3dSound->GetDirectSound();
//		LPDIRECTSOUNDBUFFER lpdsBufferTemp;
//		HRESULT hr;
//		hr = lpDS->CreateSoundBuffer(&m_dsBufferDesc, &lpdsBufferTemp, NULL);
//		if (FAILED(hr)) {
//			return false;
//		}
//
//		hr = lpdsBufferTemp->QueryInterface(IID_IDirectSoundBuffer8,
//				(LPVOID*) &m_lpdsBuffer);
//		lpdsBufferTemp->Release();
//		if (FAILED(hr)) {
//			return false;
//		}
//
//		m_dwNotifySize = m_dsBufferDesc.dwBufferBytes / m_lNotifyCount;
//		m_dwNotifySize -= m_dwNotifySize % m_WaveFormat.nBlockAlign;
//
//		return true;
//	}
//
//	/**
//	 @brief		再生位置の通知を作成
//	 @return		true:OK/false:NG
//	 @note		このクラスでスレッドを生成する
//	 */
//	int CC3DSoundBGM::createNotify(void) {
//		HRESULT hr;
//
//		// Notifyインタフェースの作成
//		hr = m_lpdsBuffer->QueryInterface(IID_IDirectSoundNotify8,
//				(LPVOID*) &m_lpdsNotify);
//		if (FAILED(hr)) {
//			return false;
//		}
//
//		// Notifyイベントの作成
//		m_hEventNotify = CreateEvent(NULL, FALSE, FALSE, NULL);
//		m_hEventExit = CreateEvent(NULL, FALSE, FALSE, NULL);
//		m_vecEvent.push_back(m_hEventNotify);
//		m_vecEvent.push_back(m_hEventExit);
//
//		//
//		m_vecNotifyPosition.clear();
//		for (int i = 0; i < m_lNotifyCount; i++) {
//			DSBPOSITIONNOTIFY PositionNotify;
//			PositionNotify.dwOffset = i * m_dwNotifySize + m_dwNotifySize - 1;
//			PositionNotify.hEventNotify = m_hEventNotify;
//			m_vecNotifyPosition.push_back(PositionNotify);
//		}
//
//		hr = m_lpdsNotify->SetNotificationPositions(
//				static_cast<DWORD> (m_vecNotifyPosition.size()),
//				&m_vecNotifyPosition[0]);
//		if (FAILED(hr)) {
//			SAFE_RELEASE( m_lpdsNotify );
//			CloseHandle(m_hEventNotify);
//			CloseHandle(m_hEventExit);
//			return false;
//		}
//
//		// Notifyイベントを受けるスレッドの作成
//		m_bExitThread = false;
//		m_hThread = CreateThread(0, 0,
//				(LPTHREAD_START_ROUTINE) CC3DSoundBGM::_ThreadProcedure, this,
//				0, &m_dwThreadResult);
//
//		return true;
//	}
//
//	/**
//	 @brief		streamからバッファへ指定ブロック数分データを転送する
//	 @param		uiBlock		転送するブロック数
//	 @return		true:OK/false:NG
//	 */
//	int CC3DSoundBGM::loadStream(UINT uiBlock) {
//		// バッファへ新しいデータを転送
//		// セカンダリ・バッファにWaveデータを書き込む
//		LPVOID lpvPtr1; // 最初のブロックのポインタ
//		DWORD dwBytes1; // 最初のブロックのサイズ
//		LPVOID lpvPtr2; // ２番目のブロックのポインタ
//		DWORD dwBytes2; // ２番目のブロックのサイズ
//		HRESULT hr;
//
//		hr = m_lpdsBuffer->Lock(m_dwNextWriteOffset, m_dwNotifySize * uiBlock,
//				&lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
//
//		// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
//		if (DSERR_BUFFERLOST == hr) {
//			_TRACE_("DSERR_BUFFERLOST!2");
//			m_lpdsBuffer->Restore();
//			hr = m_lpdsBuffer->Lock(m_dwNextWriteOffset, m_dwNotifySize
//					* uiBlock, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
//		}
//		if (FAILED(hr)) {
//			return false;
//		}
//
//		// バッファへコピー
//		int nRet;
//		nRet = m_OggDecorder.GetWave(static_cast<char*> (lpvPtr1), dwBytes1);
//		if ((nRet == m_OggDecorder.GETWAVE_RESULT_CONTINUE) && (dwBytes2 != 0)) {
//			m_OggDecorder.GetWave(static_cast<char*> (lpvPtr2), dwBytes2);
//		}
//
//		// 書き込みが終わったらすぐにUnlockする．
//		hr = m_lpdsBuffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
//
//		if (nRet == m_OggDecorder.GETWAVE_RESULT_CONTINUE) {
//			// バッファへ転送できた場合は、書き込みポインタのオフセットの更新を行う
//			m_lLastBufferCount += uiBlock; // バッファ内の未演奏のブロック数を加算
//			m_dwNextWriteOffset += m_dwNotifySize * uiBlock;
//			m_dwNextWriteOffset %= m_dsBufferDesc.dwBufferBytes;
//		}
//
//		return true;
//	}
//
//	/**
//	 @brief		エフェクトの更新
//	 */
//	int CC3DSoundBGM::updateFadeEffect(void) {
//		// Fade効果を更新
//		DWORD dwEffect = m_FadeEffect.dwEffect;
//		m_PlayInfo += m_FadeEffect;
//		if (dwEffect & m_FadeEffect.FADEEFFECT_PAN) {
//			setPan(m_PlayInfo.lPan);
//		}
//		if (dwEffect & m_FadeEffect.FADEEFFECT_VOLUME) {
//			setVolume(m_PlayInfo.lVolume);
//			if ((m_PlayInfo.lVolume <= _DS_MINVOLUME_) && (dwEffect
//					& m_FadeEffect.FADEEFFECT_FADEOUT)) {
//				return false;
//			}
//		}
//
//		return true;
//	}
//
//	/**
//	 @brief		再生管理スレッド
//	 @note		createNotifyにより開始・Stopにより終了する
//	 */
//	DWORD CC3DSoundBGM::ThreadProcedure(LPVOID lpParam) {
//		DWORD dwResult;
//		while (!m_bExitThread) {
//			dwResult = MsgWaitForMultipleObjects(
//					static_cast<DWORD> (m_vecEvent.size()), &m_vecEvent[0],
//					FALSE, INFINITE, QS_ALLEVENTS);
//			if (dwResult == WAIT_OBJECT_0) {
//				// クリティカルセクションに入る
//				EnterCriticalSection(&m_csThread);
//
//				// バッファに空きができた
//				m_lLastBufferCount--;
//
//				if (!loadStream(1)) {
//					return -1L;
//				}
//
//				if (m_lLastBufferCount <= 0) {
//					// 再生中のバッファがなくなったので再生を停止・スレッドを終了する
//					m_lpdsBuffer->Stop();
//					// Notify関連オブジェクトの解放
//					releaseNotifyObject();
//					m_bExitThread = true;
//				} else {
//					if (!updateFadeEffect()) {
//						// フェードアウトでボリュームが0となったため再生を停止・スレッドを終了する
//						m_lpdsBuffer->Stop();
//						// Notify関連オブジェクトの解放
//						releaseNotifyObject();
//						m_bExitThread = true;
//					}
//				}
//
//				// クリティカルセクションから抜ける
//				LeaveCriticalSection(&m_csThread);
//
//			} else if (dwResult == WAIT_OBJECT_0 + 1) {
//				// quit
//				break;
//			}
//		}
//
//		ExitThread(0L);
//		return 0L;
//	}
//
//	void CC3DSoundBGM::setVolume(long lVolume) {
//		m_lpdsBuffer->SetVolume(m_lpc3dSound->GetVolume(m_uiVolumeSettingID,
//				lVolume));
//		m_PlayInfo.lVolume = lVolume;
//	}
//	void CC3DSoundBGM::setPan(long lPan) {
//		m_lpdsBuffer->SetPan(lPan);
//		m_PlayInfo.lPan = lPan;
//	}
//
//	CC3DSoundBGM::~CC3DSoundBGM(void) {
//	}
//
//	CC3DSoundBGM::CC3DSoundBGM(void) :
//		m_lpc3dSound(NULL), m_lpdsBuffer(NULL), m_lpdsNotify(NULL), m_hThread(
//				NULL) {
//	}
//	/**
//	 @brief		SoundBufferの解放
//	 @note		この関数はCreateされていない状態で呼ばれても何もしない
//	 */
//	void CC3DSoundBGM::Release(void) {
//		// 演奏の停止
//		Stop();
//
//		if (m_lpdsBuffer) {
//			SAFE_RELEASE( m_lpdsBuffer );
//
//			// クリティカルセクションの削除
//			DeleteCriticalSection(&m_csThread);
//		}
//
//		// Soundから登録を削除する
//		if (m_lpc3dSound) {
//			m_lpc3dSound->UnregistSoundBuffer(this);
//			m_lpc3dSound = NULL;
//		}
//
//		m_OggDecorder.Close();
//		m_strFileName.clear();
//	}
//	/**
//	 @brief		BGMの読み込み
//	 @param		c3dSound		Sound
//	 @param		lpszFilename	ファイル名(ogg)
//	 @return		true:OK/false:NG
//	 */
//	int CC3DSoundBGM::CreateBGM(CC3DSound& c3dSound, LPCSTR lpszFilename,
//			UINT uiVolumeSettingID, UINT uiNotifyCount,
//			long lBufferSecond) {
//		Release();
//
//		m_lNotifyCount = uiNotifyCount;
//		m_lBufferSecond = lBufferSecond;
//		m_lpc3dSound = &c3dSound;
//		m_uiVolumeSettingID = uiVolumeSettingID;
//
//		// oggを開く
//		if (!m_OggDecorder.Open(lpszFilename)) {
//			return false;
//		}
//
//		// DirectSoundBufferの作成
//		if (!createSoundBuffer()) {
//			return false;
//		}
//
//		// 演奏状態の初期化
//		ZeroMemory(&m_PlayInfo, sizeof(m_PlayInfo));
//		ZeroMemory(&m_FadeEffect, sizeof(m_FadeEffect));
//
//		// クリティカルセクションの作成
//		InitializeCriticalSection(&m_csThread);
//
//		// Soundへ登録する
//		m_lpc3dSound->RegistSoundBuffer(this);
//
//		m_strFileName = lpszFilename;
//
//		return true;
//	}
//	/**
//	 @brief		演奏の停止
//	 @note		この関数はCreateまたはPlayされていない場合に呼ばれても何もしない
//	 */
//	int CC3DSoundBGM::Stop(void) {
//		if (m_lpdsNotify) {
//			// 再生中(Notifyが機能している)場合は、再生の停止・スレッド終了・オブジェクト解放を行う
//			// バッファの停止
//			m_lpdsBuffer->Stop();
//
//			// スレッドの終了
//			closeThread(10);
//
//			EnterCriticalSection(&m_csThread);
//			releaseNotifyObject();
//			LeaveCriticalSection(&m_csThread);
//
//		}
//
//		return true;
//	}
//
//	/**
//	 @brief		演奏開始
//	 */
//	int CC3DSoundBGM::Play(long lVolume, long lPan) {
//		if (m_lpdsBuffer == NULL) {
//			return false;
//		}
//
//		// 演奏を停止
//		Stop();
//
//		// oggの演奏位置を先頭へ移動
//		m_OggDecorder.SetPlayPosition(0);
//
//		m_dwNextWriteOffset = 0;
//		m_lLastBufferCount = 0;
//		if (!loadStream(m_lNotifyCount)) {
//			return false;
//		}
//
//		if (!createNotify()) {
//			return false;
//		}
//
//		// 演奏情報の設定
//		setVolume(lVolume);
//		setPan(lPan);
//
//		// 演奏開始
//		m_lpdsBuffer->SetCurrentPosition(0);
//		m_lpdsBuffer->Play(0, 0, DSBPLAY_LOOPING );
//
//		return true;
//	}
//
//	//減衰。1/100 dB (デシベル) 単位で指定する。
//	int CC3DSoundBGM::SetVolume(long lVolume) {
//		if (m_lpdsBuffer == NULL) {
//			return false;
//		}
//
//		EnterCriticalSection(&m_csThread);
//		setVolume(lVolume);
//		LeaveCriticalSection(&m_csThread);
//
//		return true;
//	}
//	int CC3DSoundBGM::SetPan(long lPan) {
//		if (m_lpdsBuffer == NULL) {
//			return false;
//		}
//
//		EnterCriticalSection(&m_csThread);
//		setPan(lPan);
//		LeaveCriticalSection(&m_csThread);
//
//		return true;
//	}
//
//	void CC3DSoundBGM::SetFadeEffectVolume(long lVolumeTo, long lVolumeSpeed) {
//		if (m_lpdsBuffer) {
//			EnterCriticalSection(&m_csThread);
//
//			m_FadeEffect.lVolumeSpeed = lVolumeSpeed;
//			m_FadeEffect.lVolumeTo = lVolumeTo;
//			m_FadeEffect.dwEffect |= m_FadeEffect.FADEEFFECT_VOLUME;
//
//			LeaveCriticalSection(&m_csThread);
//		}
//	}
//
//	void CC3DSoundBGM::SetFadeEffectPan(long lPanTo, long lPanSpeed) {
//		if (m_lpdsBuffer) {
//			EnterCriticalSection(&m_csThread);
//
//			m_FadeEffect.lPanSpeed = lPanSpeed;
//			m_FadeEffect.lPanTo = lPanTo;
//			m_FadeEffect.dwEffect |= m_FadeEffect.FADEEFFECT_PAN;
//
//			LeaveCriticalSection(&m_csThread);
//		}
//	}
//
//	int CC3DSoundBGM::GetPlayInfo(play_info& playInfo) {
//		if (m_lpdsBuffer == NULL) {
//			return false;
//		}
//
//		EnterCriticalSection(&m_csThread);
//
//		playInfo = m_PlayInfo;
//
//		LeaveCriticalSection(&m_csThread);
//
//		return true;
//	}
//
//	//static
//	DWORD CC3DSoundBGM::_ThreadProcedure(LPVOID lpParam) {
//		CC3DSoundBGM* lpBGM = reinterpret_cast<CC3DSoundBGM*> (lpParam);
//		if (lpBGM) {
//			return lpBGM->ThreadProcedure(NULL);
//		}
//		return 0L;
//	}
//
//	void CC3DSoundBGM::SetPlayModeLoop(bool bEnable) {
//		EnterCriticalSection(&m_csThread);
//
//		m_OggDecorder.SetPlayModeLoop(bEnable);
//
//		LeaveCriticalSection(&m_csThread);
//	}
//	void CC3DSoundBGM::SetPlayModeABRepeat(double dfPosA, double dfPosB, ULONG ulCount) {
//		EnterCriticalSection(&m_csThread);
//
//		COggDecorder::repeat_info repeatInfo;
//		repeatInfo.ulCount = ulCount;
//		repeatInfo.ulPosA = static_cast<ULONG> (dfPosA
//				* static_cast<double> (m_WaveFormat.nAvgBytesPerSec));
//		repeatInfo.ulPosB = static_cast<ULONG> (dfPosB
//				* static_cast<double> (m_WaveFormat.nAvgBytesPerSec));;
//		m_OggDecorder.SetPlayModeABRepeat(repeatInfo);
//
//		LeaveCriticalSection(&m_csThread);
//	}
//	int CC3DSoundBGM::SetFadeOut(long lVolumeSpeed) {
//		if (m_lpdsBuffer == NULL) {
//			return false;
//		}
//
//		if (lVolumeSpeed >= 0) {
//			return false;
//		}
//
//		EnterCriticalSection(&m_csThread);
//
//		m_FadeEffect.lVolumeSpeed = lVolumeSpeed;
//		m_FadeEffect.lVolumeTo = _DS_MINVOLUME_;
//		m_FadeEffect.dwEffect |= m_FadeEffect.FADEEFFECT_VOLUME
//				| m_FadeEffect.FADEEFFECT_FADEOUT;
//
//		LeaveCriticalSection(&m_csThread);
//
//		return true;
//	}
//
//	/**
//	 @brief		ファイル名の取得
//	 */
//	LPCSTR CC3DSoundBGM::GetFileName(void) {
//		if (m_strFileName.empty()) {
//			return NULL;
//		}
//		return m_strFileName.c_str();
//	}

