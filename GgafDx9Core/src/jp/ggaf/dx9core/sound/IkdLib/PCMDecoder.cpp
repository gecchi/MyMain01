#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace Dix;

// PCMDecoder.cpp
//

//#include <memory.h>
//#include "PCMDecoder.h"
//#include <string.h>

//namespace Dix {
//! �R���X�g���N�^
PCMDecoder::PCMDecoder() :
        _is_looping(false), _is_ready(false), _num_channel(0), _sampling_rate(0), _bit_rate(0)
{
}

//! �f�X�g���N�^
PCMDecoder::~PCMDecoder() {
}

//! �N���A
void PCMDecoder::clear() {
    _is_looping = false;
    _is_ready = false;
    _num_channel = 0;
    _sampling_rate = 0;
    _bit_rate = 0;
}

//! ���[�v�t���O�擾
bool PCMDecoder::isLooping() {
    return _is_looping;
}

//! �����ł����H
bool PCMDecoder::isReady() {
    return _is_ready;
}

//! ���[�v��ݒ�
void PCMDecoder::setLooping(bool prm_is_looping) {
    _is_looping = prm_is_looping;
}

//! WAVEFORMATEX�\���̂��擾
bool PCMDecoder::getWaveFormatEx(WAVEFORMATEX& out_waveFormatEx) {
    if (isReady() == false) {
        return false;
    }

    out_waveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
    out_waveFormatEx.nChannels = _num_channel;
    out_waveFormatEx.nSamplesPerSec = _sampling_rate;
    out_waveFormatEx.wBitsPerSample = _bit_rate;
    out_waveFormatEx.nBlockAlign = _num_channel * _bit_rate / 8;
    out_waveFormatEx.nAvgBytesPerSec = out_waveFormatEx.nSamplesPerSec * out_waveFormatEx.nBlockAlign;
    out_waveFormatEx.cbSize = 0;

    return true;
}

//! �����t���O�ݒ�
void PCMDecoder::setReady(bool prm_is_ready) {
    _is_ready = prm_is_ready;
}

//! �`�����l�����ݒ�
void PCMDecoder::setChannelNum(unsigned int prm_num_channel) {
    _num_channel = prm_num_channel;
}

//! �T���v�����O���[�g��ݒ�
void PCMDecoder::setSamplingRate(unsigned int prm_sampling_rate) {
    _sampling_rate = prm_sampling_rate;
}

//! �r�b�g���[�g��ݒ�
void PCMDecoder::setBitRate(unsigned int prm_bit_rate) {
    _bit_rate = prm_bit_rate;
}

//}
