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
    dsbdesc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCSOFTWARE; //TODO:DSBCAPS_LOCSOFTWARE or DSBCAPS_LOCDEFER���ǂ����H
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

void GgafDx9Se::play(GgafDx9GeometricActor* prm_pActor) {
//    /** [r]�������ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
//    FLOAT _fDist_VpPlnTop;
//    /** [r]�����䉺�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
//    FLOAT _fDist_VpPlnBottom;
//    /** [r]�����䍶�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
//    FLOAT _fDist_VpPlnLeft;
//    /** [r]������E�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
//    FLOAT _fDist_VpPlnRight;
//    /** [r]�������O�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
//    FLOAT _fDist_VpPlnFront;
//    /** [r]�����䉜�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
//    FLOAT _fDist_VpPlnBack;
//#define DSBPAN_LEFT                 -10000
//#define DSBPAN_CENTER               0
//#define DSBPAN_RIGHT                10000
//
//#define DSBVOLUME_MIN               -10000
//#define DSBVOLUME_MAX               0
//    int GgafDx9Sound::_master_volume = 100;
//    int GgafDx9Sound::_bgm_volume = 100;
//    int GgafDx9Sound::_se_volume = 100;

//    /** �J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0 */
//    float _zn;
//    /** �J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn  */
//    float _zf;

//    �܂��A�����o�b�t�@�̉��������Đ��ł��Ȃ��������́ADuplicateSoundBuffer()�֐����g���ăo�b�t�@�̊O�g�݂̂̃R�s�[������Ă������Ƃŉ����ł��B�Ⴆ�΁A�����8����Ă����Ɠ����o�b�t�@�̉���8�܂œ����Đ��ł��܂��B
//    �����A�����Ȕj�Ђ�1�b�Ԃɐ��S�����������肷��̂ŁA��������100���炢�����Đ����悤�Ƃ���Ɖ����r�؂�܂��c�B
//
//    ��́A�Đ����O��
//
//        lpDSBuf->SetVolume(LONG); //���ʐݒ� ��������db 0�`-10000
//        lpDSBuf->SetPan(LONG); //�p���ݒ� -10000�`+10000
//        lpDSBuf->SetFrequency(DWORD); //�Đ����g���ݒ�
//
//    _dwDefaultFrequency
//    ���������ݒ肪�o���邱�Ƃ�������܂����B�Ō�̍Đ����g���ݒ�́A�Ⴆ�΃T���v�����O���[�g44.1KHz�̃o�b�t�@�̏ꍇ�͂�����44100���w�肷��ƒʏ�ʂ�̍Đ��ɂȂ�A22050���w�肷��Ɣ����̑��x�i�����������j�ōĐ������Ƃ�����ł��B
//    ����A�G�̔��j�����ʒu�ɍ��킹�Đݒ肵�Ă��Ƃ��������̓I�Ń��A���B�Ƃ��ɁA�����̔����͍Đ����g��������悤�ɂ���ƁA���������������������ɂȂ��Ă܂�ŉf��݂����B�ŏ��͗V�ѐS�ł������Ă����ǁA�����܂ŏ�肭�n�}��Ƃ͎v��Ȃ������ȁB
//
//    �����A���ӓ_�������āA�o�b�t�@����������DSBUFFERDESC�\���̂̐ݒ�ŁA
//
//        DSBufferDesc.dwFlags = DSBCAPS_LOCDEFER | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;
//
//    �̂悤�ȃt���O��ݒ肵�āA�e�p�����[�^���R���g���[�����邱�Ƃ�`���Ă����K�v������BMSDN���Ă��ASetVolume()�̉���̂Ƃ���Ȃ񂩂ɂ��̃t���O�̎��������Ė����āA���΂炭�l�b�g��T������Ă��܂����B���ƁASetVolume�̒l��MSDN���Ɛ��̒l���Ə����Ă��邯�ǁA���ۂ͕��̒l�����Ȃ��Ƃ����Ȃ��BMSDN���Ăǂ��������Ă�c�H�H


}
/**
 @brief		SE��炷
 @param		prm_iVolume		�{�����[��(min:-9600 max:0)
 @param		prm_iPan		�p��(left:-10000 right:10000)
 */
void GgafDx9Se::play(int prm_iVolume, int prm_iPan) {
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
    //�}�X�^�[�{�����[��TODO
    //_pIDirectSoundBuffer->SetVolume(GgafDx9Sound::_master_volume �� prm_iVolume�Ōv�Z));

    _pIDirectSoundBuffer->SetVolume(prm_iVolume);
    _pIDirectSoundBuffer->SetPan(prm_iPan);
    _pIDirectSoundBuffer->SetCurrentPosition(0); //�o�b�t�@������
    _pIDirectSoundBuffer->Play(0, 0, 0x00000000);

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



GgafDx9Se::~GgafDx9Se() {
    //	if (_pSoundSE != NULL) {
    //		_pSoundSE->Release();
    //		delete _pSoundSE;
    //		_pSoundSE = NULL;
    //	}
}
