#include "jp/ggaf/dx/sound/Se.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/CWaveDecorder.h"
#include "jp/ggaf/dx/manager/SeManager.h"
#ifdef __GNUG__
    #define __null
    #define NULL    0
    #define __in
    #define __out
#endif
#include <dsound.h>  //��sal.h �� include ����
#ifdef __GNUG__
    #undef __null
    #undef __in
    #undef __out
#endif
#include <Shlwapi.h>
#include <d3d9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


using namespace GgafDx;

Se::Se(const char* prm_wave_key) : GgafCore::Object() {
    if (Sound::_pIDirectSound8 == nullptr) {
        throwCriticalException("prm_wave_key="<<prm_wave_key<<" DirectSound ���A�܂�����������Ă��܂���B");
    }

    int len = strlen(prm_wave_key);
    _wave_key = NEW char[len+1];
    strcpy(_wave_key, prm_wave_key);

    _wave_file_name = GgafCore::Config::_properties.getStr(std::string(_wave_key));
    std::string full_wave_file_name = getWaveFileName(_wave_file_name);

    HRESULT hr;
    // Wave�t�@�C�����J��
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)full_wave_file_name.c_str())) {
        throwCriticalException("prm_wave_key="<<prm_wave_key<<" �t�@�C�� "<<full_wave_file_name<<" ���J���܂���ł����B");
        //return false;
    }

    // �Z�J���_���o�b�t�@�쐬
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    //dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;//| DSBCAPS_GETCURRENTPOSITION2;// | DSBCAPS_LOCSOFTWARE;
    //TODO:DSBCAPS_LOCSOFTWARE or DSBCAPS_LOCDEFER���ǂ����H
    //TODO:Bgm �Ɠ��ꂵ�Ȃ��Ă����v�H
    dsbdesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS;
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    // �o�b�t�@�쐬
    hr = Sound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, nullptr);
    checkDxException(hr, D3D_OK, "prm_wave_key="<<prm_wave_key<<" CreateSoundBuffer�Ɏ��s���܂����B�T�E���h�J�[�h�͗L���ł����H");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("Se::Se("<<prm_wave_key<<") �y�x���zSe::writeBuffer()�����s���Ă��܂��B");
    }
    hr = _pIDirectSoundBuffer->GetFrequency(&_default_frequency);
    checkDxException(hr, D3D_OK, "prm_wave_key="<<prm_wave_key<<" GetFrequency �Ɏ��s���܂����B�T�E���h�J�[�h�͗L���ł����H");

    _pActor_last_played = nullptr;
    setVolume(GGAF_MAX_VOLUME);
    setPan(0.0f);
    setFrequencyRate(1.0);
    _TRACE_("Se::Se("<<prm_wave_key<<") _wave_file_name="<<_wave_file_name<<" this="<<this<<" _id="<<getId());
}


std::string Se::getWaveFileName(std::string prm_file) {
    std::string wave_file = CONFIG::DIR_SE[2] + "/" + prm_file;
    UTIL::strReplace(wave_file, "//", "/");
    if (PathFileExists(wave_file.c_str()) ) {
        return wave_file;
    } else {
        wave_file = CONFIG::DIR_SE[1] + "/" + prm_file;
        UTIL::strReplace(wave_file, "//", "/");
        if (PathFileExists(wave_file.c_str()) ) {
            return wave_file; //���[�U�[�X�L���ɑ��݂���΂����D��
        } else {
            wave_file = CONFIG::DIR_SE[0] + "/" + prm_file;
            UTIL::strReplace(wave_file, "//", "/");
            if (PathFileExists(wave_file.c_str()) ) {
                return wave_file;
            } else {
                throwCriticalException("Se::getWaveFileName() wave�t�@�C����������܂���Bwave_file="<<wave_file);
            }
        }
    }
}

int Se::writeBuffer(CWaveDecorder& WaveFile) {
    // �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
    LPVOID lpvPtr1; // �ŏ��̃u���b�N�̃|�C���^
    DWORD dwBytes1; // �ŏ��̃u���b�N�̃T�C�Y
    LPVOID lpvPtr2; // �Q�Ԗڂ̃u���b�N�̃|�C���^
    DWORD dwBytes2; // �Q�Ԗڂ̃u���b�N�̃T�C�Y
    HRESULT hr;
    hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
    // DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
    if (DSERR_BUFFERLOST == hr) {
        _TRACE_("DSERR_BUFFERLOST ���Ԃ���܂����B�o�b�t�@���������݂܂�");
        _pIDirectSoundBuffer->Restore();
        hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
    }

    if (hr != D3D_OK) {
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
    _pIDirectSoundBuffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
    if (lSize < 0) {
        return false;
    }
    return true;
}

void Se::play(bool prm_is_looping) {
    int v = (int)(_volume * Sound::_pSeManager->getSeMasterVolumeRate());
    if (v == 0) {
        return;
    }
    if (_pIDirectSoundBuffer == nullptr) {
        _TRACE_("_pIDirectSoundBuffer==nullptr;!");
    }
    DWORD dwStatus;
    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("���s");
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("���s");
        }
        if (!restore()) {
            _TRACE_("���s");
        }
    }
    HRESULT hr;
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //�o�b�t�@������
    checkDxException(hr, DS_OK, "SetCurrentPosition(0) �����s���܂����B");
    if (prm_is_looping) {
        hr = _pIDirectSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
        checkDxException(hr, DS_OK, "Play(0, 0, DSBPLAY_LOOPING) �����s���܂����B");
    } else {
        hr = _pIDirectSoundBuffer->Play(0, 0, 0x00000000);
        checkDxException(hr, DS_OK, "Play(0, 0, 0x00000000) �����s���܂����B");
    }
}

void Se::stop() {
    HRESULT hr;
    hr = _pIDirectSoundBuffer->Stop();
#ifdef MY_DEBUG
    if (hr != DS_OK) {
        _TRACE_("Se::stop() Stop() ���s���܂����B_wave_key="<<_wave_key);
    }
#endif
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //�o�b�t�@������
#ifdef MY_DEBUG
    if (hr != DS_OK) {
        _TRACE_("Se::stop() SetCurrentPosition(0) ���s���܂����B_wave_key="<<_wave_key);
    }
#endif
}

void Se::setVolume(int prm_volume) {
    _volume = prm_volume;
    //�}�X�^�[SE���ʗ����l��
    int v = (int)(_volume * Sound::_pSeManager->getSeMasterVolumeRate());
    if (v > GGAF_MAX_VOLUME) {
        v = GGAF_MAX_VOLUME;
    }
    int db = Sound::_a_db_volume[v];
    HRESULT hr = _pIDirectSoundBuffer->SetVolume(db);
    checkDxException(hr, DS_OK, "SetVolume("<<prm_volume<<") �����s���܂����B");
}

void Se::setPan(float prm_pan) {
    _pan = prm_pan;
    //TODO: �}�X�^�[�p�����͂܂�����
    HRESULT hr = _pIDirectSoundBuffer->SetPan((LONG)(_pan*DSBPAN_RIGHT));
    checkDxException(hr, DS_OK, "SetPan("<<prm_pan<<") �����s���܂����B");
}

void Se::setFrequencyRate(float prm_frequency_rate) {
    _frequency_rate = prm_frequency_rate;
    //TODO: �}�X�^�[���g�����͂܂�����
    DWORD frequency = (DWORD)(_default_frequency*prm_frequency_rate);
    static DWORD min_frequency = Sound::_pDsCaps->dwMinSecondarySampleRate; //���g������
    static DWORD max_frequency = Sound::_pDsCaps->dwMaxSecondarySampleRate; //���g�����
    if (frequency < min_frequency) {
        frequency = min_frequency;
    } else if (frequency > max_frequency) {
        frequency = max_frequency;
    }
    HRESULT hr = _pIDirectSoundBuffer->SetFrequency(frequency); //�Đ����g���ݒ�
    checkDxException(hr, DS_OK, "SetFrequency("<<frequency<<") �����s���܂����B");
}

int Se::restore(void) {
    std::string full_wave_file_name = getWaveFileName(_wave_file_name);
    // Wave�t�@�C�����J��
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)full_wave_file_name.c_str())) {
        return false;
    }
    if (!writeBuffer(WaveFile)) {
        return false;
    }
    return true;
}

bool Se::isPlaying() {
    DWORD dwStatus = 0;
    _pIDirectSoundBuffer->GetStatus( &dwStatus );
    if( (dwStatus & DSBSTATUS_PLAYING) != 0 ) {
        return true;
    } else {
        return false;
    }
}

Se::~Se() {
    _TRACE_("_wave_key="<<_wave_key<<" _wave_file_name="<<_wave_file_name<<" this="<<this);
    GGAF_DELETEARR_NULLABLE(_wave_key);
    GGAF_RELEASE(_pIDirectSoundBuffer);
}
