#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Se::GgafDx9Se(char* prm_wave_name) : GgafObject() {
    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") DirectSound ���A�܂�����������Ă��܂���B");
    }

    _wave_name = prm_wave_name;
    string wave_filename = GGAFDX9_PROPERTY(DIR_WAVE) + string(_wave_name) + ".wav";

    HRESULT hr;
    // Wave�t�@�C�����J��
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        _TRACE_("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") �t�@�C�� "<<wave_filename<<" ���J���܂���ł����B");
        //return false;
    }

    // �Z�J���_���o�b�t�@�쐬
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;//| DSBCAPS_GETCURRENTPOSITION2;// | DSBCAPS_LOCSOFTWARE; //TODO:DSBCAPS_LOCSOFTWARE or DSBCAPS_LOCDEFER���ǂ����H
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    // �o�b�t�@�쐬
    hr = GgafDx9Sound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, NULL);
    checkDxException(hr, D3D_OK, "GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") CreateSoundBuffer�Ɏ��s���܂����B�T�E���h�J�[�h�͗L���ł����H");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") ���x����GgafDx9Se::writeBuffer()�����s���Ă��܂��B");
    }
    hr = _pIDirectSoundBuffer->GetFrequency(&_dwDefaultFrequency);
    checkDxException(hr, D3D_OK, "GgafDx9Se::GgafDx9Se("<<prm_wave_name<<") GetFrequency �Ɏ��s���܂����B�T�E���h�J�[�h�͗L���ł����H");

}



int GgafDx9Se::writeBuffer(CWaveDecorder& WaveFile) {
    // �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
    LPVOID lpvPtr1; // �ŏ��̃u���b�N�̃|�C���^
    DWORD dwBytes1; // �ŏ��̃u���b�N�̃T�C�Y
    LPVOID lpvPtr2; // �Q�Ԗڂ̃u���b�N�̃|�C���^
    DWORD dwBytes2; // �Q�Ԗڂ̃u���b�N�̃T�C�Y

    HRESULT hr;

    hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

    // DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
    if (DSERR_BUFFERLOST == hr) {
        _TRACE_("GgafDx9Se::writeBuffer() DSERR_BUFFERLOST ���Ԃ���܂����B�o�b�t�@���������݂܂�");
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

void GgafDx9Se::play(int prm_iVolume, int prm_iPan, float prm_fRate_Frequency) {
    if (_pIDirectSoundBuffer == NULL) {
        _TRACE_("_pIDirectSoundBuffer==NULL;!");
    }
    DWORD dwStatus;
    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("GgafDx9Se::play() GetStatus() ���s");
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("GgafDx9Se::play() Restore() ���s");
        }
        if (!restore()) {
            _TRACE_("GgafDx9Se::play() restore() ���s");
        }
    }
    setVolume(prm_iVolume);
    setPan(prm_iPan);
    setFrequencyRate(prm_fRate_Frequency);
    HRESULT hr;
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //�o�b�t�@������
    checkDxException(hr, DS_OK, "GgafDx9Se::play() SetCurrentPosition(0) �����s���܂����B");
    hr = _pIDirectSoundBuffer->Play(0, 0, 0x00000000);
    checkDxException(hr, DS_OK, "GgafDx9Se::play() Play(0, 0, 0x00000000) �����s���܂����B");
}

void GgafDx9Se::setVolume(int prm_iVolume) {
    HRESULT hr = _pIDirectSoundBuffer->SetVolume(
                    DSBVOLUME_MIN + ((prm_iVolume - DSBVOLUME_MIN) * GgafDx9Sound::_master_volume_rate * GgafDx9Sound::_se_volume_rate)
                  );
    checkDxException(hr, DS_OK, "GgafDx9Se::setVolume() SetVolume("<<prm_iVolume<<") �����s���܂����B");
}

void GgafDx9Se::setPan(int prm_iPan) {
    HRESULT hr = _pIDirectSoundBuffer->SetPan(prm_iPan);
    checkDxException(hr, DS_OK, "GgafDx9Se::setPan() SetPan("<<prm_iPan<<") �����s���܂����B");
}

void GgafDx9Se::setFrequencyRate(float prm_fRate_Frequency) {
    HRESULT hr = _pIDirectSoundBuffer->SetFrequency((DWORD)(_dwDefaultFrequency*prm_fRate_Frequency)); //�Đ����g���ݒ�
    checkDxException(hr, DS_OK, "GgafDx9Se::setFrequencyRate() SetFrequency((DWORD)"<<(_dwDefaultFrequency*prm_fRate_Frequency)<<") �����s���܂����B");
}

int GgafDx9Se::restore(void) {
    string wave_filename = GGAFDX9_PROPERTY(DIR_WAVE) + _wave_name + ".wav";
    // Wave�t�@�C�����J��
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        return false;
    }

    if (!writeBuffer(WaveFile)) {
        return false;
    }
    return true;
}

bool GgafDx9Se::isPlaying() {
    DWORD dwStatus = 0;
    _pIDirectSoundBuffer->GetStatus( &dwStatus );
    if( dwStatus & DSBSTATUS_PLAYING ) {
        return true;
    } else {
        return false;
    }
}


GgafDx9Se::~GgafDx9Se() {
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSoundBuffer);
}
