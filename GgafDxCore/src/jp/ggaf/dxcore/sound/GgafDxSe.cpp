#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSe::GgafDxSe(char* prm_wave_name) : GgafObject() {
    if (GgafDxSound::_pIDirectSound8 == NULL) {
        throwGgafCriticalException("GgafDxSe::GgafDxSe("<<prm_wave_name<<") DirectSound ���A�܂�����������Ă��܂���B");
    }

    _wave_name = NEW char[128];
    strcpy(_wave_name, prm_wave_name);
    std::string wave_filename = getWaveFileName(std::string(_wave_name) + ".wav");

    HRESULT hr;
    // Wave�t�@�C�����J��
    CWaveDecorder WaveFile;
    if (!WaveFile.Open((LPSTR)wave_filename.c_str())) {
        throwGgafCriticalException("GgafDxSe::GgafDxSe("<<prm_wave_name<<") �t�@�C�� "<<wave_filename<<" ���J���܂���ł����B");
        //return false;
    }

    // �Z�J���_���o�b�t�@�쐬
    DSBUFFERDESC dsbdesc;
    ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    //dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE;//| DSBCAPS_GETCURRENTPOSITION2;// | DSBCAPS_LOCSOFTWARE;
    //TODO:DSBCAPS_LOCSOFTWARE or DSBCAPS_LOCDEFER���ǂ����H
    //TODO:GgafDxBgm �Ɠ��ꂵ�Ȃ��Ă����v�H
    dsbdesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS;
    dsbdesc.dwBufferBytes = WaveFile.GetWaveSize();
    dsbdesc.lpwfxFormat = WaveFile.GetWaveFormat();

    // �o�b�t�@�쐬
    hr = GgafDxSound::_pIDirectSound8->CreateSoundBuffer(&dsbdesc, &_pIDirectSoundBuffer, NULL);
    checkDxException(hr, D3D_OK, "GgafDxSe::GgafDxSe("<<prm_wave_name<<") CreateSoundBuffer�Ɏ��s���܂����B�T�E���h�J�[�h�͗L���ł����H");

    if (!writeBuffer(WaveFile)) {
        _TRACE_("GgafDxSe::GgafDxSe("<<prm_wave_name<<") ���x����GgafDxSe::writeBuffer()�����s���Ă��܂��B");
    }
    hr = _pIDirectSoundBuffer->GetFrequency(&_default_frequency);
    checkDxException(hr, D3D_OK, "GgafDxSe::GgafDxSe("<<prm_wave_name<<") GetFrequency �Ɏ��s���܂����B�T�E���h�J�[�h�͗L���ł����H");

    _TRACE_("GgafDxSe::GgafDxSe() _wave_name="<<_wave_name<<" this="<<this<<" _id="<<_id);
}


std::string GgafDxSe::getWaveFileName(std::string prm_file) {
    std::string wave_file = GGAF_PROPERTY(DIR_WAVE[2]) + "/" + prm_file;
    UTIL::strReplace(wave_file, "//", "/");
    if (PathFileExists(wave_file.c_str()) ) {
        return wave_file;
    } else {
        wave_file = GGAF_PROPERTY(DIR_WAVE[1]) + "/" + prm_file;
        UTIL::strReplace(wave_file, "//", "/");
        if (PathFileExists(wave_file.c_str()) ) {
            return wave_file; //���[�U�[�X�L���ɑ��݂���΂����D��
        } else {
            wave_file = GGAF_PROPERTY(DIR_WAVE[0]) + "/" + prm_file;
            UTIL::strReplace(wave_file, "//", "/");
            if (PathFileExists(wave_file.c_str()) ) {
                return wave_file;
            } else {
                throwGgafCriticalException("GgafDxSe::getWaveFileName wave�t�@�C����������܂���Bwave_file="<<wave_file);
            }
        }
    }
}

int GgafDxSe::writeBuffer(CWaveDecorder& WaveFile) {
    // �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
    LPVOID lpvPtr1; // �ŏ��̃u���b�N�̃|�C���^
    DWORD dwBytes1; // �ŏ��̃u���b�N�̃T�C�Y
    LPVOID lpvPtr2; // �Q�Ԗڂ̃u���b�N�̃|�C���^
    DWORD dwBytes2; // �Q�Ԗڂ̃u���b�N�̃T�C�Y

    HRESULT hr;

    hr = _pIDirectSoundBuffer->Lock(0, WaveFile.GetWaveSize(), &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

    // DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
    if (DSERR_BUFFERLOST == hr) {
        _TRACE_("GgafDxSe::writeBuffer() DSERR_BUFFERLOST ���Ԃ���܂����B�o�b�t�@���������݂܂�");
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

void GgafDxSe::play(int prm_volume, float prm_pan, float prm_frequency) {
    if (_pIDirectSoundBuffer == NULL) {
        _TRACE_("_pIDirectSoundBuffer==NULL;!");
    }
    DWORD dwStatus;
    if (FAILED(_pIDirectSoundBuffer->GetStatus(&dwStatus))) {
        _TRACE_("GgafDxSe::play() GetStatus() ���s");
    }
    if (dwStatus == (DWORD)DSERR_BUFFERLOST) {
        if (FAILED(_pIDirectSoundBuffer->Restore())) {
            _TRACE_("GgafDxSe::play() Restore() ���s");
        }
        if (!restore()) {
            _TRACE_("GgafDxSe::play() restore() ���s");
        }
    }
    setVolume(prm_volume);
    setPan(prm_pan);
    setFrequencyRate(prm_frequency);
    HRESULT hr;
    hr = _pIDirectSoundBuffer->SetCurrentPosition(0); //�o�b�t�@������
    checkDxException(hr, DS_OK, "GgafDxSe::play() SetCurrentPosition(0) �����s���܂����B");
    hr = _pIDirectSoundBuffer->Play(0, 0, 0x00000000);
    checkDxException(hr, DS_OK, "GgafDxSe::play() Play(0, 0, 0x00000000) �����s���܂����B");
}
void GgafDxSe::play() {
    play(GgafDxSound::_se_volume, 0.0f);
}
void GgafDxSe::setVolume(int prm_volume) {
    int db = GgafDxSound::aDbVolume[(int)(prm_volume * GgafDxSound::_master_volume_rate * GgafDxSound::_se_volume_rate)];
    HRESULT hr = _pIDirectSoundBuffer->SetVolume(db);
    checkDxException(hr, DS_OK, "GgafDxSe::setVolume() SetVolume("<<prm_volume<<") �����s���܂����B");
}

void GgafDxSe::setPan(float prm_pan) {
    HRESULT hr = _pIDirectSoundBuffer->SetPan((LONG)(prm_pan*DSBPAN_RIGHT));
    checkDxException(hr, DS_OK, "GgafDxSe::setPan() SetPan("<<prm_pan<<") �����s���܂����B");
}

void GgafDxSe::setFrequencyRate(float prm_frequency) {
    HRESULT hr = _pIDirectSoundBuffer->SetFrequency((DWORD)(_default_frequency*prm_frequency)); //�Đ����g���ݒ�
    checkDxException(hr, DS_OK, "GgafDxSe::setFrequencyRate() SetFrequency((DWORD)"<<(_default_frequency*prm_frequency)<<") �����s���܂����B");
}

int GgafDxSe::restore(void) {
    std::string wave_filename = getWaveFileName( std::string(_wave_name) + ".wav");
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




bool GgafDxSe::isPlaying() {
    DWORD dwStatus = 0;
    _pIDirectSoundBuffer->GetStatus( &dwStatus );
    if( (dwStatus & DSBSTATUS_PLAYING) != 0 ) {
        return true;
    } else {
        return false;
    }
}


GgafDxSe::~GgafDxSe() {
    _TRACE_("GgafDxSe::~GgafDxSe() _wave_name="<<_wave_name<<" this="<<this<<" _id="<<_id);
    DELETEARR_IMPOSSIBLE_NULL(_wave_name);
    RELEASE_IMPOSSIBLE_NULL(_pIDirectSoundBuffer);
}
