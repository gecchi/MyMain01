#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Se::GgafDx9Se(char* prm_wave_name, int prm_cnt_buffer) : GgafObject() {
    if (GgafDx9Sound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<","<<prm_cnt_buffer<<") DirectSound ���A�܂�����������Ă��܂���B");
    }

    _wave_name = prm_wave_name;
    string wave_filename = GGAFDX9_PROPERTY(DIR_WAVE) + string(_wave_name) + ".wav";

    HRESULT hr;
    // Wave�t�@�C�����J��
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        _TRACE_("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<","<<prm_cnt_buffer<<") �t�@�C�� "<<wave_filename<<" ���J���܂���ł����B");
        //return false;
    }

    // �Z�J���_���o�b�t�@�쐬
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS
            | DSBCAPS_LOCSOFTWARE; //DSBCAPS_LOCSOFTWARE��t��������
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    // �o�b�t�@�쐬
    hr = GgafDx9Sound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, NULL);
    potentialGgafDx9CriticalException(hr, D3D_OK, "GgafDx9Se::GgafDx9Se("<<prm_wave_name<<","<<prm_cnt_buffer<<") CreateSoundBuffer�Ɏ��s���܂����B�T�E���h�J�[�h�͗L���ł����H");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("GgafDx9Se::GgafDx9Se("<<prm_wave_name<<","<<prm_cnt_buffer<<") ���x����GgafDx9Se::writeBuffer()�����s���Ă��܂��B");
    }
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


/**
 @brief		SE��炷
 @param		lVolume		�{�����[��(min:-9600 max:0)
 @param		lPan		�p��(left:-10000 right:10000)
 @return		true:OK/false:NG
 */
void GgafDx9Se::play() {
    if (_pIDirectSoundBuffer == NULL) {
        _TRACE_("_pIDirectSoundBuffer==NULL;!");
    }
    DWORD dwStatus;

    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("GgafDx9Se::play() GetStatus() ���s");
        //return false;
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("GgafDx9Se::play() Restore() ���s");
            //return false;
        }
        if (!restore()) {
            _TRACE_("GgafDx9Se::play() restore() ���s");
            //return false;
        }
    }

    //	_pIDirectSoundBuffer->SetVolume(m_lpc3dSound->GetVolume(m_uiVolumeSettingID, lVolume));
    _pIDirectSoundBuffer->SetVolume(0);
    //_pIDirectSoundBuffer->SetPan(lPan);
    _pIDirectSoundBuffer->SetPan(0);
    _pIDirectSoundBuffer->SetCurrentPosition(0);
    _pIDirectSoundBuffer->Play(0, 0, 0);

    //_pSoundSE->Play(0,0);
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

void GgafDx9Se::play(int prm_iVolume, int prm_iPan) {
    //_pSoundSE->Play(prm_iVolume, prm_iPan);
}

GgafDx9Se::~GgafDx9Se() {
    //	if (_pSoundSE != NULL) {
    //		_pSoundSE->Release();
    //		delete _pSoundSE;
    //		_pSoundSE = NULL;
    //	}
}
