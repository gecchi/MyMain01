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

//#include "wavedecorder.hpp"
//#include "oggdecorder.hpp"

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
//	LPDIRECTSOUND8 GgafDx9Sound::_pIDirectSound8; /// DirectSound
	DSCAPS m_dsCaps; ///
	float_map m_mapVolume; /// �{�����[���ݒ�
	float m_fMasterVolume; /// �}�X�^�{�����[��
	soundbuffer_vector m_vecSoundBuffer; /// �o�^���ꂽ�T�E���h�o�b�t�@

public:
	virtual ~CC3DSound(void);
	CC3DSound(void);
	void Release(void);

	/**
	 @brief		Sound�@�\��L���ɂ���
	 @param		hWnd		Window�n���h��
	 @return		true:OK/false:NG
	 @note		DirectSound�쐬����ъe�평���ݒ�B
	 */
	int CreateSound(HWND hWnd);
	/**
	 @brief		DirectSound�I�u�W�F�N�g�̎擾
	 @return		DirectSound�I�u�W�F�N�g
	 */
	LPDIRECTSOUND8 GetDirectSound(void);
	/**
	 @brief		�{�����[���ݒ��o�^
	 @param		uiID		�{�����[���ݒ�ID
	 @param		fVolume		�{�����[��(0.0�`1.0)
	 @return		true:OK/false:NG
	 @note		SE/BGM�ȂǕʁX�Ƀ{�����[����ݒ肷��ꍇ�Ɏg�p����B
	 */
	int SetVolumeSetting(unsigned int uiID, float fVolume);
	/**
	 @brief	�{�����[���ݒ肩��{�����[�����擾
	 */
	long GetVolume(unsigned int uiID, long lVolumeSrc);

	/**
	 @brief		�{�����[���ݒ�̎擾
	 @param		uiID		�擾����{�����[���ݒ��ID
	 @return		�{�����[���ݒ�
	 */
	float GetVolumeSetting(unsigned int uiID);

	/**
	 @brief		�}�X�^�{�����[���̐ݒ�
	 @param		fVolume		�ݒ肷��{�����[���l
	 @return		true:OK/false:NG
	 @note		�}�X�^�{�����[���̏����l��1.0�B
	 */
	int SetMasterVolume(float fVolume);
	/**
	 @brief		�}�X�^�{�����[���̎擾
	 @return		�}�X�^�{�����[���l
	 */
	float GetMasterVolume(void);

	/**
	 @brief		DirectSound���\�̎擾
	 */
	int GetDirectSoundCaps(DSCAPS& dsCaps);
	/**
	 @brief		SoundBuffer��o�^����
	 @note		�T�E���h�o�b�t�@��o�^���邱�ƂŁASound�N���X�̉��(Release)����
	 �S�ẴT�E���h�o�b�t�@������ł���B(Leak�΍�)
	 */
	int RegistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer);
	/**
	 @brief		SoundBuffer�̓o�^����������
	 @note		�T�E���h�o�b�t�@�̉�����ɃT�E���h�o�b�t�@����Ăт����B
	 */
	int UnregistSoundBuffer(CC3DSoundBuffer* lpSoundBuffer);

	/**
	 @brief		�S�Ẵo�b�t�@�̉��t���~����
	 */
	int Stop(void);
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
	int writeBuffer(CWaveDecorder& WaveFile);
	/**
	 @brief		SoundBuffer�̕��A
	 */
	int restore(void);

public:
	virtual ~CC3DSoundBufferSE(void);
	CC3DSoundBufferSE(void);

	CC3DSoundBufferSE(const CC3DSoundBufferSE& c3dsb);

	/**
	 @brief		SE�̉��
	 @note		���̊֐���Create����Ă��Ȃ���ԂŌĂяo���ꂽ�ꍇ�A�������Ȃ�
	 */
	void Release(void);

	/**
	 @brief		SE�̍쐬
	 @param		lpszFileName		�t�@�C����
	 @param		c3dSound			Sound�N���X
	 @return		true:OK/false:NG
	 */
	int Create(LPCSTR lpszFileName, CC3DSound& c3dSound,
			UINT uiVolumeSettingID = 0);

	/**
	 @brief		SE��炷
	 @param		lVolume		�{�����[��(min:-9600 max:0)
	 @param		lPan		�p��(left:-10000 right:10000)
	 @return		true:OK/false:NG
	 */
	int Play(long lVolume, long lPan);

	/**
	 @brief		�o�b�t�@�̕���
	 @param		c3dsbSE		�R�s�[��
	 */
	int operator =(const CC3DSoundBufferSE& c3dsbSE);
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
	virtual ~CC3DSoundSE(void);

	CC3DSoundSE(void);

	/**
	 @brief		SE���������
	 @note		���̊֐���Create���ꂸ�ɌĂ΂ꂽ�ꍇ�͉������Ȃ�
	 */
	void Release(void);

	/**
	 @brief		SE�̍쐬
	 @param		c3dSound			Sound�N���X
	 @param		lpszFilename		�t�@�C����(wav)
	 @param		nBufferCount		�o�b�t�@�̊m�ې�(����SE�𓯎��ɍĐ�����ő吔)
	 @param		uiVolumeSettingID	�{�����[���ݒ�ID(SOUND�̃}�X�^�{�����[���ݒ�)
	 @return		true:OK/false:NG
	 */
	int CreateSE(CC3DSound& c3dSound, LPCSTR lpszFilename,
			unsigned int nBufferCount, UINT uiVolumeSettingID = 0);

	/**
	 @brief		SE��炷
	 @param		lVolume		�{�����[��(min:-9600 max:0)
	 @param		lPan		�p��(left:-10000 right:10000)
	 @return		true:OK/false:NG
	 */
	int Play(long lVolume, long lPan);

};


/**
 @brief		ogg�t�@�C���̍Đ�
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
//	/// �ʒm�C�x���g�n���h���̃R���e�i
//	typedef std::vector< HANDLE> handle_vector;
//	/// Notify����Đ��ʒu�̃R���e�i
//	typedef std::vector< DSBPOSITIONNOTIFY> notify_vector;
//
//	std::string m_strFileName; /// �t�@�C����
//	COggDecorder m_OggDecorder; /// ogg�f�R�[�_
//	CC3DSound* m_lpc3dSound; /// Sound�N���X�ւ̃|�C���^
//	LPDIRECTSOUNDBUFFER8 m_lpdsBuffer; /// SoundBuffer
//	DSBUFFERDESC m_dsBufferDesc; /// SoundBuffer���
//	WAVEFORMATEX m_WaveFormat; /// WaveFormat
//	LPDIRECTSOUNDNOTIFY8 m_lpdsNotify; /// �ʒm
//	HANDLE m_hThread; /// �Đ��Ǘ��p�X���b�h
//	HANDLE m_hEventNotify; /// �Đ��ʒu�̒ʒm�C�x���g
//	HANDLE m_hEventExit; /// �X���b�h�I���ʒm�p�̃C�x���g
//	DWORD m_dwThreadResult; /// �X���b�h�̊����R�[�h�i�[��
//	DWORD m_dwNextWriteOffset; /// ���̏������݃|�C���^�̃I�t�Z�b�g
//	notify_vector m_vecNotifyPosition; /// �Đ��ʒu�ʒm�p�̃R���e�i
//	DWORD m_dwNotifySize; /// Notify�T�C�Y
//	long m_lLastBufferCount; /// ���݃o�b�t�@�ɐݒ肵�Ă��鐔
//	bool m_bExitThread; /// �X���b�h�I���t���O
//	CRITICAL_SECTION m_csThread; /// �X���b�h�ʐM�p�N���e�B�J���Z�N�V����
//	handle_vector m_vecEvent; /// �X���b�h�̃C�x���g�҂��n���h���R���e�i
//	long m_lNotifyCount; /// �T�E���h�o�b�t�@�̒ʒm�ׂ̍���
//	long m_lBufferSecond; /// �T�E���h�o�b�t�@�֊m�ۂ��鎞��
//	UINT m_uiVolumeSettingID; /// �{�����[���ݒ�ID
//
//	play_info m_PlayInfo; /// ���t���
//	fade_effect m_FadeEffect; /// �t�F�[�h����
//
//
//	/**
//	 @brief		�X���b�h���I��������
//	 @note		�X���b�h��~�w����A�^�C���A�E�g���Ԓ�~��҂B
//	 �^�C���A�E�g�����ꍇ�A�����I�ɃX���b�h���~�����ăG���[��Ԃ��B
//	 */
//	int closeThread(int nTimeOut);
//	/**
//	 @brief		SoundBuffer�̍쐬
//	 @return		true:OK/false:NG
//	 */
//	int createSoundBuffer(void);
//
//	/**
//	 @brief		�Đ��ʒu�̒ʒm���쐬
//	 @return		true:OK/false:NG
//	 @note		���̃N���X�ŃX���b�h�𐶐�����
//	 */
//	int createNotify(void);
//
//	/**
//	 @brief		stream����o�b�t�@�֎w��u���b�N�����f�[�^��]������
//	 @param		uiBlock		�]������u���b�N��
//	 @return		true:OK/false:NG
//	 */
//	int loadStream(UINT uiBlock);
//
//	/**
//	 @brief		�G�t�F�N�g�̍X�V
//	 */
//	int updateFadeEffect(void);
//
//	/**
//	 @brief		�Đ��Ǘ��X���b�h
//	 @note		createNotify�ɂ��J�n�EStop�ɂ��I������
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
//	 @brief		SoundBuffer�̉��
//	 @note		���̊֐���Create����Ă��Ȃ���ԂŌĂ΂�Ă��������Ȃ�
//	 */
//	void Release(void);
//	/**
//	 @brief		BGM�̓ǂݍ���
//	 @param		c3dSound		Sound
//	 @param		lpszFilename	�t�@�C����(ogg)
//	 @return		true:OK/false:NG
//	 */
//	int CreateBGM(CC3DSound& c3dSound, LPCSTR lpszFilename,
//			UINT uiVolumeSettingID = 0, UINT uiNotifyCount = 16,
//			long lBufferSecond = 5);
//	/**
//	 @brief		���t�̒�~
//	 @note		���̊֐���Create�܂���Play����Ă��Ȃ��ꍇ�ɌĂ΂�Ă��������Ȃ�
//	 */
//	int Stop(void);
//
//	/**
//	 @brief		���t�J�n
//	 */
//	int Play(long lVolume = 0, long lPan = 0);
//
//	//�����B1/100 dB (�f�V�x��) �P�ʂŎw�肷��B
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
//	 @brief		�t�@�C�����̎擾
//	 */
//	LPCSTR GetFileName(void);
//};

#endif	//_INCLUDE_C3DSOUND_HPP
