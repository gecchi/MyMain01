#include "stdafx.h"

/******************************************************************************
 * DirectSound����N���X
 *	@author		Ander/Echigo-ya koubou
 ******************************************************************************/

// ���̃v���O�����̃I���W�i���́A�u�z�㉮Cyber�v�̃����o�[��Ander�����A
// Blog�Ō��J����Ă����T���v���v���O�����ł��B
// �L�v�ȃT���v�����J���E���J���ĉ�������Ander���Ɋ��ӂ��A���p�����Ē����܂��B
//
//                                2008/03/25 Masatoshi Tsuge
//
// �y�ΏۃR�[�h�z
// c3dsound.hpp, oggdecorder.hpp, wavedecorder.hpp
// �y�z�㉮Cyber�z
// http://www.e-cyber.org/
// �yAnder��Blog:�T���v�����J�̋L���z
// http://ecyber.exblog.jp/824656/


CC3DSound::~CC3DSound(void) {
	Release();
}
CC3DSound::CC3DSound(void) :
	m_fMasterVolume(1.0f) {
}
void CC3DSound::Release(void) {
	// �������Ă��Ȃ��T�E���h�o�b�t�@��S�ĉ������
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
 @brief		Sound�@�\��L���ɂ���
 @param		hWnd		Window�n���h��
 @return		true:OK/false:NG
 @note		DirectSound�쐬����ъe�평���ݒ�B
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
	// ���̎擾
	m_dsCaps.dwSize = sizeof(m_dsCaps);
	hr = GgafDx9Sound::_pIDirectSound8->GetCaps(&m_dsCaps);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

/**
 @brief		DirectSound�I�u�W�F�N�g�̎擾
 @return		DirectSound�I�u�W�F�N�g
 */
LPDIRECTSOUND8 CC3DSound::GetDirectSound(void) {
	return GgafDx9Sound::_pIDirectSound8;
}

/**
 @brief		�{�����[���ݒ��o�^
 @param		uiID		�{�����[���ݒ�ID
 @param		fVolume		�{�����[��(0.0�`1.0)
 @return		true:OK/false:NG
 @note		SE/BGM�ȂǕʁX�Ƀ{�����[����ݒ肷��ꍇ�Ɏg�p����B
 */
int CC3DSound::SetVolumeSetting(unsigned int uiID, float fVolume) {
	m_mapVolume[uiID] = fVolume;
	return true;
}

/**
 @brief	�{�����[���ݒ肩��{�����[�����擾
 */
long CC3DSound::GetVolume(unsigned int uiID, long lVolumeSrc) {
	float fVolumeSetting = GetVolumeSetting(uiID);

	// Volume = src * VolumeSetting * MasterVolume
	return static_cast<long> (static_cast<float> (lVolumeSrc - _DS_MINVOLUME_)
			* fVolumeSetting * m_fMasterVolume) + _DS_MINVOLUME_;
}

/**
 @brief		�{�����[���ݒ�̎擾
 @param		uiID		�擾����{�����[���ݒ��ID
 @return		�{�����[���ݒ�
 */
float CC3DSound::GetVolumeSetting(unsigned int uiID) {
	float_map::iterator it = m_mapVolume.find(uiID);
	if (it == m_mapVolume.end()) {
		return 1.0f;
	}
	return it->second;
}

/**
 @brief		�}�X�^�{�����[���̐ݒ�
 @param		fVolume		�ݒ肷��{�����[���l
 @return		true:OK/false:NG
 @note		�}�X�^�{�����[���̏����l��1.0�B
 */
int CC3DSound::SetMasterVolume(float fVolume) {
	m_fMasterVolume = fVolume;
	return true;
}
/**
 @brief		�}�X�^�{�����[���̎擾
 @return		�}�X�^�{�����[���l
 */
float CC3DSound::GetMasterVolume(void) {
	return m_fMasterVolume;
}

/**
 @brief		DirectSound���\�̎擾
 */
int CC3DSound::GetDirectSoundCaps(DSCAPS& dsCaps) {
	if (GgafDx9Sound::_pIDirectSound8 == NULL) {
		return false;
	}
	dsCaps = m_dsCaps;
	return true;
}

/**
 @brief		SoundBuffer��o�^����
 @note		�T�E���h�o�b�t�@��o�^���邱�ƂŁASound�N���X�̉��(Release)����
 �S�ẴT�E���h�o�b�t�@������ł���B(Leak�΍�)
 */
int CC3DSound::RegistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer) {
	m_vecSoundBuffer.push_back(lpSoundBuffer);

	return true;
}
/**
 @brief		SoundBuffer�̓o�^����������
 @note		�T�E���h�o�b�t�@�̉�����ɃT�E���h�o�b�t�@����Ăт����B
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
 @brief		�S�Ẵo�b�t�@�̉��t���~����
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
 @brief		�o�b�t�@��Wave�f�[�^��]��
 */
int CC3DSoundBufferSE::writeBuffer(CWaveDecorder& WaveFile) {
	// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
	LPVOID lpvPtr1; // �ŏ��̃u���b�N�̃|�C���^
	DWORD dwBytes1; // �ŏ��̃u���b�N�̃T�C�Y
	LPVOID lpvPtr2; // �Q�Ԗڂ̃u���b�N�̃|�C���^
	DWORD dwBytes2; // �Q�Ԗڂ̃u���b�N�̃T�C�Y

	HRESULT hr;

	hr = m_lpdsBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1,
			&lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
	if (DSERR_BUFFERLOST == hr) {
		_TRACE_("DSERR_BUFFERLOST!");
		m_lpdsBuffer->Restore();
		hr = m_lpdsBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1,
				&lpvPtr2, &dwBytes2, 0);
	}

	if (FAILED(hr)) {
		return false;
	}
	// ���b�N����

	// �����ŁC�o�b�t�@�ɏ�������
	// �o�b�t�@�Ƀf�[�^���R�s�[����
	long lSize = WaveFile.GetWave(static_cast<LPBYTE> (lpvPtr1), dwBytes1);
	if (lSize > 0 && dwBytes2 != 0) {
		lSize = WaveFile.GetWave(static_cast<LPBYTE> (lpvPtr2), dwBytes2);
	}

	// �������݂��I������炷����Unlock����D
	m_lpdsBuffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);

	if (lSize < 0) {
		return false;
	}

	return true;
}

/**
 @brief		SoundBuffer�̕��A
 */
int CC3DSoundBufferSE::restore(void) {
	// Wave�t�@�C�����J��
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
 @brief		SE�̉��
 @note		���̊֐���Create����Ă��Ȃ���ԂŌĂяo���ꂽ�ꍇ�A�������Ȃ�
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
 @brief		SE�̍쐬
 @param		lpszFileName		�t�@�C����
 @param		c3dSound			Sound�N���X
 @return		true:OK/false:NG
 */
int CC3DSoundBufferSE::Create(LPCSTR lpszFileName, CC3DSound& c3dSound,
		UINT uiVolumeSettingID) {
	Release();

	HRESULT hr;

	// Wave�t�@�C�����J��
	CWaveDecorder WaveFile;
	if (!WaveFile.Open((LPSTR) lpszFileName)) {
		return false;
	}

	// �Z�J���_���E�o�b�t�@���쐬����
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME
			| DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE; //DSBCAPS_LOCSOFTWARE��t��������
	dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
	dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

	LPDIRECTSOUND8 lpDS = c3dSound.GetDirectSound();
	if (lpDS == NULL) {
		return false;
	}

	// �o�b�t�@�����
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

	// Sound�֓o�^����
	m_lpc3dSound->RegistSoundBuffer(this);

	return true;
}

/**
 @brief		SE��炷
 @param		lVolume		�{�����[��(min:-9600 max:0)
 @param		lPan		�p��(left:-10000 right:10000)
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
 @brief		�o�b�t�@�̕���
 @param		c3dsbSE		�R�s�[��
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

	// Sound�֓o�^����
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
 @brief		SE���������
 @note		���̊֐���Create���ꂸ�ɌĂ΂ꂽ�ꍇ�͉������Ȃ�
 */
void CC3DSoundSE::Release(void) {
	delete[] m_lpSoundBuffer;
	m_lpSoundBuffer = NULL;
}

/**
 @brief		SE�̍쐬
 @param		c3dSound			Sound�N���X
 @param		lpszFilename		�t�@�C����(wav)
 @param		nBufferCount		�o�b�t�@�̊m�ې�(����SE�𓯎��ɍĐ�����ő吔)
 @param		uiVolumeSettingID	�{�����[���ݒ�ID(SOUND�̃}�X�^�{�����[���ݒ�)
 @return		true:OK/false:NG
 */
int CC3DSoundSE::CreateSE(CC3DSound& c3dSound, LPCSTR lpszFilename,
		unsigned int nBufferCount, UINT uiVolumeSettingID) {
	if (nBufferCount == 0) {
		return false;
	}
	// �o�b�t�@���m��
	m_lpSoundBuffer = NEW CC3DSoundBufferSE[ nBufferCount ];

		// �擪�͕��ʂɍ쐬
		if (!m_lpSoundBuffer[0].Create(lpszFilename, c3dSound)){
	return false;
}

// �c��͕���
			for (unsigned int i = 1; i < nBufferCount; i++) {
				if (!(m_lpSoundBuffer[i] = m_lpSoundBuffer[0])) {
					return false;
				}
			}

			// �ϐ��Ȃǂ̏�����
			m_uiBufferIndex = 0;
			m_uiBufferCount = nBufferCount;

			return true;
		}

	/**
	 @brief		SE��炷
	 @param		lVolume		�{�����[��(min:-9600 max:0)
	 @param		lPan		�p��(left:-10000 right:10000)
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
//			// Notify�̉��
//			SAFE_RELEASE( m_lpdsNotify );
//			m_vecNotifyPosition.clear();
//
//			// �C�x���g�ʒm�p�I�u�W�F�N�g�����
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
//	 @brief		�X���b�h���I��������
//	 @note		�X���b�h��~�w����A�^�C���A�E�g���Ԓ�~��҂B
//	 �^�C���A�E�g�����ꍇ�A�����I�ɃX���b�h���~�����ăG���[��Ԃ��B
//	 */
//	int CC3DSoundBGM::closeThread(int nTimeOut) {
//		if (m_hThread) {
//			// �X���b�h�֏I���C�x���g�𓊂��ďI������̂�҂�
//
//			DWORD dwExitCode;
//			SetEvent(m_hEventExit);
//
//			// �I��or�^�C���A�E�g�܂ő҂�
//			for (; nTimeOut > 0; --nTimeOut) {
//				GetExitCodeThread(m_hThread, &dwExitCode);
//				if (dwExitCode != STILL_ACTIVE) {
//					break;
//				}
//				Sleep(500);
//			}
//
//			if (nTimeOut == 0) {
//				// �X���b�h�������I��������
//				TerminateThread(m_hThread, 0);
//			}
//
//			// �n���h�������
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
//	 @brief		SoundBuffer�̍쐬
//	 @return		true:OK/false:NG
//	 */
//	int CC3DSoundBGM::createSoundBuffer(void) {
//		// vorbis���̎擾
//		vorbis_info vorbisInfo;
//		if (!m_OggDecorder.GetVorbisInfo(vorbisInfo)) {
//			return false;
//		}
//
//		ZeroMemory(&m_WaveFormat, sizeof(m_WaveFormat));
//		m_WaveFormat.nSamplesPerSec = vorbisInfo.rate;
//		m_WaveFormat.wBitsPerSample = 16; // �K��?
//		m_WaveFormat.nBlockAlign = m_WaveFormat.wBitsPerSample * vorbisInfo.channels / 8;
//		m_WaveFormat.nAvgBytesPerSec = m_WaveFormat.nBlockAlign	* m_WaveFormat.nSamplesPerSec;
//		m_WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
//		m_WaveFormat.nChannels = vorbisInfo.channels;
//
//		// SoundBuffer�̍쐬
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
//	 @brief		�Đ��ʒu�̒ʒm���쐬
//	 @return		true:OK/false:NG
//	 @note		���̃N���X�ŃX���b�h�𐶐�����
//	 */
//	int CC3DSoundBGM::createNotify(void) {
//		HRESULT hr;
//
//		// Notify�C���^�t�F�[�X�̍쐬
//		hr = m_lpdsBuffer->QueryInterface(IID_IDirectSoundNotify8,
//				(LPVOID*) &m_lpdsNotify);
//		if (FAILED(hr)) {
//			return false;
//		}
//
//		// Notify�C�x���g�̍쐬
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
//		// Notify�C�x���g���󂯂�X���b�h�̍쐬
//		m_bExitThread = false;
//		m_hThread = CreateThread(0, 0,
//				(LPTHREAD_START_ROUTINE) CC3DSoundBGM::_ThreadProcedure, this,
//				0, &m_dwThreadResult);
//
//		return true;
//	}
//
//	/**
//	 @brief		stream����o�b�t�@�֎w��u���b�N�����f�[�^��]������
//	 @param		uiBlock		�]������u���b�N��
//	 @return		true:OK/false:NG
//	 */
//	int CC3DSoundBGM::loadStream(UINT uiBlock) {
//		// �o�b�t�@�֐V�����f�[�^��]��
//		// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
//		LPVOID lpvPtr1; // �ŏ��̃u���b�N�̃|�C���^
//		DWORD dwBytes1; // �ŏ��̃u���b�N�̃T�C�Y
//		LPVOID lpvPtr2; // �Q�Ԗڂ̃u���b�N�̃|�C���^
//		DWORD dwBytes2; // �Q�Ԗڂ̃u���b�N�̃T�C�Y
//		HRESULT hr;
//
//		hr = m_lpdsBuffer->Lock(m_dwNextWriteOffset, m_dwNotifySize * uiBlock,
//				&lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
//
//		// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
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
//		// �o�b�t�@�փR�s�[
//		int nRet;
//		nRet = m_OggDecorder.GetWave(static_cast<char*> (lpvPtr1), dwBytes1);
//		if ((nRet == m_OggDecorder.GETWAVE_RESULT_CONTINUE) && (dwBytes2 != 0)) {
//			m_OggDecorder.GetWave(static_cast<char*> (lpvPtr2), dwBytes2);
//		}
//
//		// �������݂��I������炷����Unlock����D
//		hr = m_lpdsBuffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
//
//		if (nRet == m_OggDecorder.GETWAVE_RESULT_CONTINUE) {
//			// �o�b�t�@�֓]���ł����ꍇ�́A�������݃|�C���^�̃I�t�Z�b�g�̍X�V���s��
//			m_lLastBufferCount += uiBlock; // �o�b�t�@���̖����t�̃u���b�N�������Z
//			m_dwNextWriteOffset += m_dwNotifySize * uiBlock;
//			m_dwNextWriteOffset %= m_dsBufferDesc.dwBufferBytes;
//		}
//
//		return true;
//	}
//
//	/**
//	 @brief		�G�t�F�N�g�̍X�V
//	 */
//	int CC3DSoundBGM::updateFadeEffect(void) {
//		// Fade���ʂ��X�V
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
//	 @brief		�Đ��Ǘ��X���b�h
//	 @note		createNotify�ɂ��J�n�EStop�ɂ��I������
//	 */
//	DWORD CC3DSoundBGM::ThreadProcedure(LPVOID lpParam) {
//		DWORD dwResult;
//		while (!m_bExitThread) {
//			dwResult = MsgWaitForMultipleObjects(
//					static_cast<DWORD> (m_vecEvent.size()), &m_vecEvent[0],
//					FALSE, INFINITE, QS_ALLEVENTS);
//			if (dwResult == WAIT_OBJECT_0) {
//				// �N���e�B�J���Z�N�V�����ɓ���
//				EnterCriticalSection(&m_csThread);
//
//				// �o�b�t�@�ɋ󂫂��ł���
//				m_lLastBufferCount--;
//
//				if (!loadStream(1)) {
//					return -1L;
//				}
//
//				if (m_lLastBufferCount <= 0) {
//					// �Đ����̃o�b�t�@���Ȃ��Ȃ����̂ōĐ����~�E�X���b�h���I������
//					m_lpdsBuffer->Stop();
//					// Notify�֘A�I�u�W�F�N�g�̉��
//					releaseNotifyObject();
//					m_bExitThread = true;
//				} else {
//					if (!updateFadeEffect()) {
//						// �t�F�[�h�A�E�g�Ń{�����[����0�ƂȂ������ߍĐ����~�E�X���b�h���I������
//						m_lpdsBuffer->Stop();
//						// Notify�֘A�I�u�W�F�N�g�̉��
//						releaseNotifyObject();
//						m_bExitThread = true;
//					}
//				}
//
//				// �N���e�B�J���Z�N�V�������甲����
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
//	 @brief		SoundBuffer�̉��
//	 @note		���̊֐���Create����Ă��Ȃ���ԂŌĂ΂�Ă��������Ȃ�
//	 */
//	void CC3DSoundBGM::Release(void) {
//		// ���t�̒�~
//		Stop();
//
//		if (m_lpdsBuffer) {
//			SAFE_RELEASE( m_lpdsBuffer );
//
//			// �N���e�B�J���Z�N�V�����̍폜
//			DeleteCriticalSection(&m_csThread);
//		}
//
//		// Sound����o�^���폜����
//		if (m_lpc3dSound) {
//			m_lpc3dSound->UnregistSoundBuffer(this);
//			m_lpc3dSound = NULL;
//		}
//
//		m_OggDecorder.Close();
//		m_strFileName.clear();
//	}
//	/**
//	 @brief		BGM�̓ǂݍ���
//	 @param		c3dSound		Sound
//	 @param		lpszFilename	�t�@�C����(ogg)
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
//		// ogg���J��
//		if (!m_OggDecorder.Open(lpszFilename)) {
//			return false;
//		}
//
//		// DirectSoundBuffer�̍쐬
//		if (!createSoundBuffer()) {
//			return false;
//		}
//
//		// ���t��Ԃ̏�����
//		ZeroMemory(&m_PlayInfo, sizeof(m_PlayInfo));
//		ZeroMemory(&m_FadeEffect, sizeof(m_FadeEffect));
//
//		// �N���e�B�J���Z�N�V�����̍쐬
//		InitializeCriticalSection(&m_csThread);
//
//		// Sound�֓o�^����
//		m_lpc3dSound->RegistSoundBuffer(this);
//
//		m_strFileName = lpszFilename;
//
//		return true;
//	}
//	/**
//	 @brief		���t�̒�~
//	 @note		���̊֐���Create�܂���Play����Ă��Ȃ��ꍇ�ɌĂ΂�Ă��������Ȃ�
//	 */
//	int CC3DSoundBGM::Stop(void) {
//		if (m_lpdsNotify) {
//			// �Đ���(Notify���@�\���Ă���)�ꍇ�́A�Đ��̒�~�E�X���b�h�I���E�I�u�W�F�N�g������s��
//			// �o�b�t�@�̒�~
//			m_lpdsBuffer->Stop();
//
//			// �X���b�h�̏I��
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
//	 @brief		���t�J�n
//	 */
//	int CC3DSoundBGM::Play(long lVolume, long lPan) {
//		if (m_lpdsBuffer == NULL) {
//			return false;
//		}
//
//		// ���t���~
//		Stop();
//
//		// ogg�̉��t�ʒu��擪�ֈړ�
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
//		// ���t���̐ݒ�
//		setVolume(lVolume);
//		setPan(lPan);
//
//		// ���t�J�n
//		m_lpdsBuffer->SetCurrentPosition(0);
//		m_lpdsBuffer->Play(0, 0, DSBPLAY_LOOPING );
//
//		return true;
//	}
//
//	//�����B1/100 dB (�f�V�x��) �P�ʂŎw�肷��B
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
//	 @brief		�t�@�C�����̎擾
//	 */
//	LPCSTR CC3DSoundBGM::GetFileName(void) {
//		if (m_strFileName.empty()) {
//			return NULL;
//		}
//		return m_strFileName.c_str();
//	}

