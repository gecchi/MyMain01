/******************************************************************************
 * DirectSound����N���X
 *	@author		Ander/Echigo-ya koubou
 ******************************************************************************/

// ���̃v���O�����̃I���W�i���́A�u�z�㉮Cyber�v�̃����o�[��Ander�����A
// Blog�Ō��J���Ă����T���v���v���O�����ł��B
// �����ADirectSound + ogg �̃X�g���[�~���O�Đ��ŔY��ł������X�������������A
// ���ォ������������܂ꂽ�v���ł����B
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

#ifndef	_INCLUDE_C3DSOUND_HPP
#define	_INCLUDE_C3DSOUND_HPP

#include <MMSystem.h>
#include <dxerr9.h>
#include <dsound.h>
#include <vector>
#include <map>
#include <algorithm>

#include "wavedecorder.hpp"
#include "oggdecorder.hpp"

#ifndef	SAFE_RELEASE
#define	SAFE_RELEASE( x )		{if( x ){(x)->Release();(x)=NULL;}}
#endif	// SAFE_RELEASE
static const int _DS_MINVOLUME_ = -9600;
static const int _DS_PAN_LEFT_ = -10000;
static const int _DS_PAN_RIGHT_ = 10000;

/**
 @brief		DirectSound����N���X
 */
class CC3DSound {
public:
	/**
	 @brief		SoundBuffer��{�N���X
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

	/// �{�����[���ݒ�R���e�i�^�C�v
	typedef std::map< unsigned int, float> float_map;

	typedef std::vector< CC3DSoundBuffer*> soundbuffer_vector;

private:
	LPDIRECTSOUND8 m_lpDS; /// DirectSound
	DSCAPS m_dsCaps; ///
	float_map m_mapVolume; /// �{�����[���ݒ�
	float m_fMasterVolume; /// �}�X�^�{�����[��
	soundbuffer_vector m_vecSoundBuffer; /// �o�^���ꂽ�T�E���h�o�b�t�@

public:
	virtual ~CC3DSound(void) {
		Release();
	}
	CC3DSound(void) :
		m_lpDS(NULL), m_fMasterVolume(1.0f) {
	}
	void Release(void) {
		// �������Ă��Ȃ��T�E���h�o�b�t�@��S�ĉ������
		soundbuffer_vector::iterator it = m_vecSoundBuffer.begin();
		for (; it != m_vecSoundBuffer.end();) {
			CC3DSoundBuffer* lpPre = *it;
			(*it)->Release();
			if (it != m_vecSoundBuffer.end() && *it == lpPre)
				it++;
		}
		m_vecSoundBuffer.clear();

		SAFE_RELEASE( m_lpDS );
	}

	/**
	 @brief		Sound�@�\��L���ɂ���
	 @param		hWnd		Window�n���h��
	 @return		true:OK/false:NG
	 @note		DirectSound�쐬����ъe�평���ݒ�B
	 */
	int CreateSound(HWND hWnd) {
		HRESULT hr;
		hr = DirectSoundCreate8(NULL, &m_lpDS, NULL);
		if (FAILED(hr)) {
			return false;
		}
		hr = m_lpDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY );
		if (FAILED(hr)) {
			return false;
		}
		// ���̎擾
		m_dsCaps.dwSize = sizeof(m_dsCaps);
		hr = m_lpDS->GetCaps(&m_dsCaps);
		if (FAILED(hr)) {
			return false;
		}

		return true;
	}

	/**
	 @brief		DirectSound�I�u�W�F�N�g�̎擾
	 @return		DirectSound�I�u�W�F�N�g
	 */
	LPDIRECTSOUND8 GetDirectSound(void) {
		return m_lpDS;
	}

	/**
	 @brief		�{�����[���ݒ��o�^
	 @param		uiID		�{�����[���ݒ�ID
	 @param		fVolume		�{�����[��(0.0�`1.0)
	 @return		true:OK/false:NG
	 @note		SE/BGM�ȂǕʁX�Ƀ{�����[����ݒ肷��ꍇ�Ɏg�p����B
	 */
	int SetVolumeSetting(unsigned int uiID, float fVolume) {
		m_mapVolume[uiID] = fVolume;
		return true;
	}

	/**
	 @brief	�{�����[���ݒ肩��{�����[�����擾
	 */
	long GetVolume(unsigned int uiID, long lVolumeSrc) {
		float fVolumeSetting = GetVolumeSetting(uiID);

		// Volume = src * VolumeSetting * MasterVolume
		return static_cast<long> (static_cast<float> (lVolumeSrc
				- _DS_MINVOLUME_) * fVolumeSetting * m_fMasterVolume)
				+ _DS_MINVOLUME_;
	}

	/**
	 @brief		�{�����[���ݒ�̎擾
	 @param		uiID		�擾����{�����[���ݒ��ID
	 @return		�{�����[���ݒ�
	 */
	float GetVolumeSetting(unsigned int uiID) {
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
	int SetMasterVolume(float fVolume) {
		m_fMasterVolume = fVolume;
		return true;
	}
	/**
	 @brief		�}�X�^�{�����[���̎擾
	 @return		�}�X�^�{�����[���l
	 */
	float GetMasterVolume(void) {
		return m_fMasterVolume;
	}

	/**
	 @brief		DirectSound���\�̎擾
	 */
	int GetDirectSoundCaps(DSCAPS& dsCaps) {
		if (m_lpDS == NULL) {
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
	int RegistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer) {
		m_vecSoundBuffer.push_back(lpSoundBuffer);

		return true;
	}
	/**
	 @brief		SoundBuffer�̓o�^����������
	 @note		�T�E���h�o�b�t�@�̉�����ɃT�E���h�o�b�t�@����Ăт����B
	 */
	int UnregistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer) {
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
	int Stop(void) {
		if (m_lpDS == NULL) {
			return false;
		}

		for (soundbuffer_vector::iterator it = m_vecSoundBuffer.begin()
		; it != m_vecSoundBuffer.end(); it++) {
			(*it)->Stop();
		}

		return true;
	}
};

/**
 @brief		SE�p�T�E���h�o�b�t�@����N���X
 */
class CC3DSoundBufferSE: public CC3DSound::CC3DSoundBuffer {
private:
	LPDIRECTSOUNDBUFFER m_lpdsBuffer; /// �T�E���h�o�b�t�@
	CC3DSound* m_lpc3dSound; /// Sound�̃|�C���^
	std::string m_strFilename; /// �t�@�C����
	UINT m_uiVolumeSettingID; /// �{�����[���ݒ�ID

	/**
	 @brief		�o�b�t�@��Wave�f�[�^��]��
	 */
	int writeBuffer(CWaveDecorder& WaveFile) {
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
			hr = m_lpdsBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1,
					&dwBytes1, &lpvPtr2, &dwBytes2, 0);
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
	int restore(void) {
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

public:
	virtual ~CC3DSoundBufferSE(void) {
		Release();
	}
	CC3DSoundBufferSE(void) :
		m_lpdsBuffer(NULL), m_lpc3dSound(NULL), m_uiVolumeSettingID(0) {
	}

	CC3DSoundBufferSE(const CC3DSoundBufferSE& c3dsb) {
		*this = c3dsb;
	}

	/**
	 @brief		SE�̉��
	 @note		���̊֐���Create����Ă��Ȃ���ԂŌĂяo���ꂽ�ꍇ�A�������Ȃ�
	 */
	void Release(void) {
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
	int Create(LPCSTR lpszFileName, CC3DSound& c3dSound,
			UINT uiVolumeSettingID = 0) {
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
	int Play(long lVolume, long lPan) {
		DWORD dwStatus;

		if (FAILED(m_lpdsBuffer->GetStatus(&dwStatus))) {
			return false;
		}
		if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
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
	int operator =(const CC3DSoundBufferSE& c3dsbSE) {
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
};

/**
 @brief		SE����N���X
 @note		������SE�𓯎��ɍĐ��ł���悤�ɁA�ЂƂ�SE�ɂ������̃o�b�t�@���m�ۂ��Ă���
 */
class CC3DSoundSE: public CC3DSound::CC3DSoundBuffer {
private:
	CC3DSoundBufferSE* m_lpSoundBuffer; /// SoundBuffer�N���X�̔z��
	unsigned int m_uiBufferIndex; /// ���ɍĐ�����SoundBuffer
	unsigned int m_uiBufferCount; /// SoundBuffer�̊m�ې�

public:
	virtual ~CC3DSoundSE(void) {
		Release();
	}

	CC3DSoundSE(void) :
		m_lpSoundBuffer(NULL) {
	}

	/**
	 @brief		SE���������
	 @note		���̊֐���Create���ꂸ�ɌĂ΂ꂽ�ꍇ�͉������Ȃ�
	 */
	void Release(void) {
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
	int CreateSE(CC3DSound& c3dSound, LPCSTR lpszFilename,
			unsigned int nBufferCount, UINT uiVolumeSettingID = 0) {
		if (nBufferCount == 0) {
			return false;
		}
		// �o�b�t�@���m��
		m_lpSoundBuffer = NEW CC3DSoundBufferSE[ nBufferCount ];

		// �擪�͕��ʂɍ쐬
		if (!m_lpSoundBuffer[0].Create(lpszFilename, c3dSound)) {
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
	int Play(long lVolume, long lPan) {
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

};

/**
 @brief		ogg�t�@�C���̍Đ�
 */
class CC3DSoundBGM: public CC3DSound::CC3DSoundBuffer {
public:

	struct fade_effect {
		DWORD dwEffect;
		long lVolumeSpeed;
		long lVolumeTo;
		long lPanSpeed;
		long lPanTo;

		enum {
			FADEEFFECT_NONE = 0,
			FADEEFFECT_VOLUME = 1,
			FADEEFFECT_PAN = 2,
			FADEEFFECT_FADEOUT = 4,
		};
	};

	struct play_info {
		long lVolume;
		long lPan;

		int operator +=(fade_effect& fadeEffect) {
			bool bUpdate = false;
			if (fadeEffect.dwEffect & fadeEffect.FADEEFFECT_VOLUME) {
				lVolume += fadeEffect.lVolumeSpeed;
				if ((fadeEffect.lVolumeSpeed < 0 && lVolume
						<= fadeEffect.lVolumeTo) || (fadeEffect.lVolumeSpeed
						> 0 && lVolume >= fadeEffect.lVolumeTo)) {
					fadeEffect.dwEffect &= ~fadeEffect.FADEEFFECT_VOLUME;
					lVolume = fadeEffect.lVolumeTo;
				}
				bUpdate = true;
			}
			if (fadeEffect.dwEffect & fadeEffect.FADEEFFECT_PAN) {
				lPan += fadeEffect.lPanSpeed;
				if ((fadeEffect.lPanSpeed < 0 && lPan <= fadeEffect.lPanTo)
						|| (fadeEffect.lPanSpeed > 0 && lPan
								>= fadeEffect.lPanTo)) {
					fadeEffect.dwEffect &= ~fadeEffect.FADEEFFECT_PAN;
					lPan = fadeEffect.lPanTo;
				}
				bUpdate = true;
			}

			return bUpdate;
		}
	};

	void releaseNotifyObject(void) {
		if (m_lpdsNotify) {
			// Notify�̉��
			SAFE_RELEASE( m_lpdsNotify );
			m_vecNotifyPosition.clear();

			// �C�x���g�ʒm�p�I�u�W�F�N�g�����
			m_vecEvent.clear();
			CloseHandle(m_hEventNotify);
			m_hEventNotify = NULL;
			CloseHandle(m_hEventExit);
			m_hEventExit = NULL;
		}
	}

private:
	/// �ʒm�C�x���g�n���h���̃R���e�i
	typedef std::vector< HANDLE> handle_vector;
	/// Notify����Đ��ʒu�̃R���e�i
	typedef std::vector< DSBPOSITIONNOTIFY> notify_vector;

	std::string m_strFileName; /// �t�@�C����
	COggDecorder m_OggDecorder; /// ogg�f�R�[�_
	CC3DSound* m_lpc3dSound; /// Sound�N���X�ւ̃|�C���^
	LPDIRECTSOUNDBUFFER8 m_lpdsBuffer; /// SoundBuffer
	DSBUFFERDESC m_dsBufferDesc; /// SoundBuffer���
	WAVEFORMATEX m_WaveFormat; /// WaveFormat
	LPDIRECTSOUNDNOTIFY8 m_lpdsNotify; /// �ʒm
	HANDLE m_hThread; /// �Đ��Ǘ��p�X���b�h
	HANDLE m_hEventNotify; /// �Đ��ʒu�̒ʒm�C�x���g
	HANDLE m_hEventExit; /// �X���b�h�I���ʒm�p�̃C�x���g
	DWORD m_dwThreadResult; /// �X���b�h�̊����R�[�h�i�[��
	DWORD m_dwNextWriteOffset; /// ���̏������݃|�C���^�̃I�t�Z�b�g
	notify_vector m_vecNotifyPosition; /// �Đ��ʒu�ʒm�p�̃R���e�i
	DWORD m_dwNotifySize; /// Notify�T�C�Y
	long m_lLastBufferCount; /// ���݃o�b�t�@�ɐݒ肵�Ă��鐔
	bool m_bExitThread; /// �X���b�h�I���t���O
	CRITICAL_SECTION m_csThread; /// �X���b�h�ʐM�p�N���e�B�J���Z�N�V����
	handle_vector m_vecEvent; /// �X���b�h�̃C�x���g�҂��n���h���R���e�i
	long m_lNotifyCount; /// �T�E���h�o�b�t�@�̒ʒm�ׂ̍���
	long m_lBufferSecond; /// �T�E���h�o�b�t�@�֊m�ۂ��鎞��
	UINT m_uiVolumeSettingID; /// �{�����[���ݒ�ID

	play_info m_PlayInfo; /// ���t���
	fade_effect m_FadeEffect; /// �t�F�[�h����


	/**
	 @brief		�X���b�h���I��������
	 @note		�X���b�h��~�w����A�^�C���A�E�g���Ԓ�~��҂B
	 �^�C���A�E�g�����ꍇ�A�����I�ɃX���b�h���~�����ăG���[��Ԃ��B
	 */
	int closeThread(int nTimeOut) {
		if (m_hThread) {
			// �X���b�h�֏I���C�x���g�𓊂��ďI������̂�҂�

			DWORD dwExitCode;
			SetEvent(m_hEventExit);

			// �I��or�^�C���A�E�g�܂ő҂�
			for (; nTimeOut > 0; --nTimeOut) {
				GetExitCodeThread(m_hThread, &dwExitCode);
				if (dwExitCode != STILL_ACTIVE) {
					break;
				}
				Sleep(500);
			}

			if (nTimeOut == 0) {
				// �X���b�h�������I��������
				TerminateThread(m_hThread, 0);
			}

			// �n���h�������
			CloseHandle(m_hThread);
			m_hThread = NULL;

			if (nTimeOut == 0) {
				return false;
			}
		}

		return true;
	}

	/**
	 @brief		SoundBuffer�̍쐬
	 @return		true:OK/false:NG
	 */
	int createSoundBuffer(void) {
		// vorbis���̎擾
		vorbis_info vorbisInfo;
		if (!m_OggDecorder.GetVorbisInfo(vorbisInfo)) {
			return false;
		}

		ZeroMemory(&m_WaveFormat, sizeof(m_WaveFormat));
		m_WaveFormat.nSamplesPerSec = vorbisInfo.rate;
		m_WaveFormat.wBitsPerSample = 16; // �K��?
		m_WaveFormat.nBlockAlign = m_WaveFormat.wBitsPerSample * vorbisInfo.channels / 8;
		m_WaveFormat.nAvgBytesPerSec = m_WaveFormat.nBlockAlign	* m_WaveFormat.nSamplesPerSec;
		m_WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
		m_WaveFormat.nChannels = vorbisInfo.channels;

		// SoundBuffer�̍쐬
		ZeroMemory(&m_dsBufferDesc, sizeof(m_dsBufferDesc));
		m_dsBufferDesc.dwSize = sizeof(m_dsBufferDesc);
		m_dsBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCDEFER | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2;
		m_dsBufferDesc.dwBufferBytes = m_lBufferSecond * m_WaveFormat.nAvgBytesPerSec;
		m_dsBufferDesc.dwBufferBytes -= ((m_dsBufferDesc.dwBufferBytes/m_lNotifyCount) % 4) * m_lNotifyCount;
		m_dsBufferDesc.guid3DAlgorithm = GUID_NULL;
		m_dsBufferDesc.lpwfxFormat = &m_WaveFormat;

		LPDIRECTSOUND8 lpDS = m_lpc3dSound->GetDirectSound();
		LPDIRECTSOUNDBUFFER lpdsBufferTemp;
		HRESULT hr;
		hr = lpDS->CreateSoundBuffer(&m_dsBufferDesc, &lpdsBufferTemp, NULL);
		if (FAILED(hr)) {
			return false;
		}

		hr = lpdsBufferTemp->QueryInterface(IID_IDirectSoundBuffer8,
				(LPVOID*) &m_lpdsBuffer);
		lpdsBufferTemp->Release();
		if (FAILED(hr)) {
			return false;
		}

		m_dwNotifySize = m_dsBufferDesc.dwBufferBytes / m_lNotifyCount;
		m_dwNotifySize -= m_dwNotifySize % m_WaveFormat.nBlockAlign;

		return true;
	}

	/**
	 @brief		�Đ��ʒu�̒ʒm���쐬
	 @return		true:OK/false:NG
	 @note		���̃N���X�ŃX���b�h�𐶐�����
	 */
	int createNotify(void) {
		HRESULT hr;

		// Notify�C���^�t�F�[�X�̍쐬
		hr = m_lpdsBuffer->QueryInterface(IID_IDirectSoundNotify8,
				(LPVOID*) &m_lpdsNotify);
		if (FAILED(hr)) {
			return false;
		}

		// Notify�C�x���g�̍쐬
		m_hEventNotify = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hEventExit = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_vecEvent.push_back(m_hEventNotify);
		m_vecEvent.push_back(m_hEventExit);

		//
		m_vecNotifyPosition.clear();
		for (int i = 0; i < m_lNotifyCount; i++) {
			DSBPOSITIONNOTIFY PositionNotify;
			PositionNotify.dwOffset = i * m_dwNotifySize + m_dwNotifySize - 1;
			PositionNotify.hEventNotify = m_hEventNotify;
			m_vecNotifyPosition.push_back(PositionNotify);
		}

		hr = m_lpdsNotify->SetNotificationPositions(
				static_cast<DWORD> (m_vecNotifyPosition.size()),
				&m_vecNotifyPosition[0]);
		if (FAILED(hr)) {
			SAFE_RELEASE( m_lpdsNotify );
			CloseHandle(m_hEventNotify);
			CloseHandle(m_hEventExit);
			return false;
		}

		// Notify�C�x���g���󂯂�X���b�h�̍쐬
		m_bExitThread = false;
		m_hThread = CreateThread(0, 0,
				(LPTHREAD_START_ROUTINE) CC3DSoundBGM::_ThreadProcedure, this,
				0, &m_dwThreadResult);

		return true;
	}

	/**
	 @brief		stream����o�b�t�@�֎w��u���b�N�����f�[�^��]������
	 @param		uiBlock		�]������u���b�N��
	 @return		true:OK/false:NG
	 */
	int loadStream(UINT uiBlock) {
		// �o�b�t�@�֐V�����f�[�^��]��
		// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
		LPVOID lpvPtr1; // �ŏ��̃u���b�N�̃|�C���^
		DWORD dwBytes1; // �ŏ��̃u���b�N�̃T�C�Y
		LPVOID lpvPtr2; // �Q�Ԗڂ̃u���b�N�̃|�C���^
		DWORD dwBytes2; // �Q�Ԗڂ̃u���b�N�̃T�C�Y
		HRESULT hr;

		hr = m_lpdsBuffer->Lock(m_dwNextWriteOffset, m_dwNotifySize * uiBlock,
				&lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

		// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
		if (DSERR_BUFFERLOST == hr) {
			_TRACE_("DSERR_BUFFERLOST!2");
			m_lpdsBuffer->Restore();
			hr = m_lpdsBuffer->Lock(m_dwNextWriteOffset, m_dwNotifySize
					* uiBlock, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
		}
		if (FAILED(hr)) {
			return false;
		}

		// �o�b�t�@�փR�s�[
		int nRet;
		nRet = m_OggDecorder.GetWave(static_cast<char*> (lpvPtr1), dwBytes1);
		if ((nRet == m_OggDecorder.GETWAVE_RESULT_CONTINUE) && (dwBytes2 != 0)) {
			m_OggDecorder.GetWave(static_cast<char*> (lpvPtr2), dwBytes2);
		}

		// �������݂��I������炷����Unlock����D
		hr = m_lpdsBuffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);

		if (nRet == m_OggDecorder.GETWAVE_RESULT_CONTINUE) {
			// �o�b�t�@�֓]���ł����ꍇ�́A�������݃|�C���^�̃I�t�Z�b�g�̍X�V���s��
			m_lLastBufferCount += uiBlock; // �o�b�t�@���̖����t�̃u���b�N�������Z
			m_dwNextWriteOffset += m_dwNotifySize * uiBlock;
			m_dwNextWriteOffset %= m_dsBufferDesc.dwBufferBytes;
		}

		return true;
	}

	/**
	 @brief		�G�t�F�N�g�̍X�V
	 */
	int updateFadeEffect(void) {
		// Fade���ʂ��X�V
		DWORD dwEffect = m_FadeEffect.dwEffect;
		m_PlayInfo += m_FadeEffect;
		if (dwEffect & m_FadeEffect.FADEEFFECT_PAN) {
			setPan(m_PlayInfo.lPan);
		}
		if (dwEffect & m_FadeEffect.FADEEFFECT_VOLUME) {
			setVolume(m_PlayInfo.lVolume);
			if ((m_PlayInfo.lVolume <= _DS_MINVOLUME_) && (dwEffect
					& m_FadeEffect.FADEEFFECT_FADEOUT)) {
				return false;
			}
		}

		return true;
	}

	/**
	 @brief		�Đ��Ǘ��X���b�h
	 @note		createNotify�ɂ��J�n�EStop�ɂ��I������
	 */
	DWORD ThreadProcedure(LPVOID lpParam) {
		DWORD dwResult;
		while (!m_bExitThread) {
			dwResult = MsgWaitForMultipleObjects(
					static_cast<DWORD> (m_vecEvent.size()), &m_vecEvent[0],
					FALSE, INFINITE, QS_ALLEVENTS);
			if (dwResult == WAIT_OBJECT_0) {
				// �N���e�B�J���Z�N�V�����ɓ���
				EnterCriticalSection(&m_csThread);

				// �o�b�t�@�ɋ󂫂��ł���
				m_lLastBufferCount--;

				if (!loadStream(1)) {
					return -1L;
				}

				if (m_lLastBufferCount <= 0) {
					// �Đ����̃o�b�t�@���Ȃ��Ȃ����̂ōĐ����~�E�X���b�h���I������
					m_lpdsBuffer->Stop();
					// Notify�֘A�I�u�W�F�N�g�̉��
					releaseNotifyObject();
					m_bExitThread = true;
				} else {
					if (!updateFadeEffect()) {
						// �t�F�[�h�A�E�g�Ń{�����[����0�ƂȂ������ߍĐ����~�E�X���b�h���I������
						m_lpdsBuffer->Stop();
						// Notify�֘A�I�u�W�F�N�g�̉��
						releaseNotifyObject();
						m_bExitThread = true;
					}
				}

				// �N���e�B�J���Z�N�V�������甲����
				LeaveCriticalSection(&m_csThread);

			} else if (dwResult == WAIT_OBJECT_0 + 1) {
				// quit
				break;
			}
		}

		ExitThread(0L);
		return 0L;
	}

	void setVolume(long lVolume) {
		m_lpdsBuffer->SetVolume(m_lpc3dSound->GetVolume(m_uiVolumeSettingID,
				lVolume));
		m_PlayInfo.lVolume = lVolume;
	}
	void setPan(long lPan) {
		m_lpdsBuffer->SetPan(lPan);
		m_PlayInfo.lPan = lPan;
	}

public:
	virtual ~CC3DSoundBGM(void) {
	}

	CC3DSoundBGM(void) :
		m_lpc3dSound(NULL), m_lpdsBuffer(NULL), m_lpdsNotify(NULL), m_hThread(
				NULL) {
	}
	/**
	 @brief		SoundBuffer�̉��
	 @note		���̊֐���Create����Ă��Ȃ���ԂŌĂ΂�Ă��������Ȃ�
	 */
	void Release(void) {
		// ���t�̒�~
		Stop();

		if (m_lpdsBuffer) {
			SAFE_RELEASE( m_lpdsBuffer );

			// �N���e�B�J���Z�N�V�����̍폜
			DeleteCriticalSection(&m_csThread);
		}

		// Sound����o�^���폜����
		if (m_lpc3dSound) {
			m_lpc3dSound->UnregistSoundBuffer(this);
			m_lpc3dSound = NULL;
		}

		m_OggDecorder.Close();
		m_strFileName.clear();
	}
	/**
	 @brief		BGM�̓ǂݍ���
	 @param		c3dSound		Sound
	 @param		lpszFilename	�t�@�C����(ogg)
	 @return		true:OK/false:NG
	 */
	int CreateBGM(CC3DSound& c3dSound, LPCSTR lpszFilename,
			UINT uiVolumeSettingID = 0, UINT uiNotifyCount = 16,
			long lBufferSecond = 5) {
		Release();

		m_lNotifyCount = uiNotifyCount;
		m_lBufferSecond = lBufferSecond;
		m_lpc3dSound = &c3dSound;
		m_uiVolumeSettingID = uiVolumeSettingID;

		// ogg���J��
		if (!m_OggDecorder.Open(lpszFilename)) {
			return false;
		}

		// DirectSoundBuffer�̍쐬
		if (!createSoundBuffer()) {
			return false;
		}

		// ���t��Ԃ̏�����
		ZeroMemory(&m_PlayInfo, sizeof(m_PlayInfo));
		ZeroMemory(&m_FadeEffect, sizeof(m_FadeEffect));

		// �N���e�B�J���Z�N�V�����̍쐬
		InitializeCriticalSection(&m_csThread);

		// Sound�֓o�^����
		m_lpc3dSound->RegistSoundBuffer(this);

		m_strFileName = lpszFilename;

		return true;
	}
	/**
	 @brief		���t�̒�~
	 @note		���̊֐���Create�܂���Play����Ă��Ȃ��ꍇ�ɌĂ΂�Ă��������Ȃ�
	 */
	int Stop(void) {
		if (m_lpdsNotify) {
			// �Đ���(Notify���@�\���Ă���)�ꍇ�́A�Đ��̒�~�E�X���b�h�I���E�I�u�W�F�N�g������s��
			// �o�b�t�@�̒�~
			m_lpdsBuffer->Stop();

			// �X���b�h�̏I��
			closeThread(10);

			EnterCriticalSection(&m_csThread);
			releaseNotifyObject();
			LeaveCriticalSection(&m_csThread);

		}

		return true;
	}

	/**
	 @brief		���t�J�n
	 */
	int Play(long lVolume = 0, long lPan = 0) {
		if (m_lpdsBuffer == NULL) {
			return false;
		}

		// ���t���~
		Stop();

		// ogg�̉��t�ʒu��擪�ֈړ�
		m_OggDecorder.SetPlayPosition(0);

		m_dwNextWriteOffset = 0;
		m_lLastBufferCount = 0;
		if (!loadStream(m_lNotifyCount)) {
			return false;
		}

		if (!createNotify()) {
			return false;
		}

		// ���t���̐ݒ�
		setVolume(lVolume);
		setPan(lPan);

		// ���t�J�n
		m_lpdsBuffer->SetCurrentPosition(0);
		m_lpdsBuffer->Play(0, 0, DSBPLAY_LOOPING );

		return true;
	}

	//�����B1/100 dB (�f�V�x��) �P�ʂŎw�肷��B
	int SetVolume(long lVolume) {
		if (m_lpdsBuffer == NULL) {
			return false;
		}

		EnterCriticalSection(&m_csThread);
		setVolume(lVolume);
		LeaveCriticalSection(&m_csThread);

		return true;
	}
	int SetPan(long lPan) {
		if (m_lpdsBuffer == NULL) {
			return false;
		}

		EnterCriticalSection(&m_csThread);
		setPan(lPan);
		LeaveCriticalSection(&m_csThread);

		return true;
	}

	void SetFadeEffectVolume(long lVolumeTo, long lVolumeSpeed) {
		if (m_lpdsBuffer) {
			EnterCriticalSection(&m_csThread);

			m_FadeEffect.lVolumeSpeed = lVolumeSpeed;
			m_FadeEffect.lVolumeTo = lVolumeTo;
			m_FadeEffect.dwEffect |= m_FadeEffect.FADEEFFECT_VOLUME;

			LeaveCriticalSection(&m_csThread);
		}
	}

	void SetFadeEffectPan(long lPanTo, long lPanSpeed) {
		if (m_lpdsBuffer) {
			EnterCriticalSection(&m_csThread);

			m_FadeEffect.lPanSpeed = lPanSpeed;
			m_FadeEffect.lPanTo = lPanTo;
			m_FadeEffect.dwEffect |= m_FadeEffect.FADEEFFECT_PAN;

			LeaveCriticalSection(&m_csThread);
		}
	}

	int GetPlayInfo(play_info& playInfo) {
		if (m_lpdsBuffer == NULL) {
			return false;
		}

		EnterCriticalSection(&m_csThread);

		playInfo = m_PlayInfo;

		LeaveCriticalSection(&m_csThread);

		return true;
	}

	static DWORD _ThreadProcedure(LPVOID lpParam) {
		CC3DSoundBGM* lpBGM = reinterpret_cast<CC3DSoundBGM*> (lpParam);
		if (lpBGM) {
			return lpBGM->ThreadProcedure(NULL);
		}
		return 0L;
	}

	void SetPlayModeLoop(bool bEnable) {
		EnterCriticalSection(&m_csThread);

		m_OggDecorder.SetPlayModeLoop(bEnable);

		LeaveCriticalSection(&m_csThread);
	}
	void SetPlayModeABRepeat(double dfPosA, double dfPosB, ULONG ulCount) {
		EnterCriticalSection(&m_csThread);

		COggDecorder::repeat_info repeatInfo;
		repeatInfo.ulCount = ulCount;
		repeatInfo.ulPosA = static_cast<ULONG> (dfPosA
				* static_cast<double> (m_WaveFormat.nAvgBytesPerSec));
		repeatInfo.ulPosB = static_cast<ULONG> (dfPosB
				* static_cast<double> (m_WaveFormat.nAvgBytesPerSec));;
		m_OggDecorder.SetPlayModeABRepeat(repeatInfo);

		LeaveCriticalSection(&m_csThread);
	}
	int SetFadeOut(long lVolumeSpeed) {
		if (m_lpdsBuffer == NULL) {
			return false;
		}

		if (lVolumeSpeed >= 0) {
			return false;
		}

		EnterCriticalSection(&m_csThread);

		m_FadeEffect.lVolumeSpeed = lVolumeSpeed;
		m_FadeEffect.lVolumeTo = _DS_MINVOLUME_;
		m_FadeEffect.dwEffect |= m_FadeEffect.FADEEFFECT_VOLUME
				| m_FadeEffect.FADEEFFECT_FADEOUT;

		LeaveCriticalSection(&m_csThread);

		return true;
	}

	/**
	 @brief		�t�@�C�����̎擾
	 */
	LPCSTR GetFileName(void) {
		if (m_strFileName.empty()) {
			return NULL;
		}
		return m_strFileName.c_str();
	}
};

#endif	//_INCLUDE_C3DSOUND_HPP
