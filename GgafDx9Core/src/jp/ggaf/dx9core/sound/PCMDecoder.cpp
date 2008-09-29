#include "stdafx.h"

// PCMDecoder.cpp
//

//#include <memory.h>
//#include "PCMDecoder.h"
//#include <string.h>

//! �R���X�g���N�^
PCMDecoder::PCMDecoder() :
	isLoop_(false), isReady_(false), channelNum_(0), samplingRate_(0),
			bitRate_(0) {
}

//! �f�X�g���N�^
PCMDecoder::~PCMDecoder() {
}

//! �N���A
void PCMDecoder::clear() {
	isLoop_ = false;
	isReady_ = false;
	channelNum_ = 0;
	samplingRate_ = 0;
	bitRate_ = 0;
}

//! ���[�v�t���O�擾
bool PCMDecoder::isLoop() {
	return isLoop_;
}

//! �����ł����H
bool PCMDecoder::isReady() {
	return isReady_;
}

//! ���[�v��ݒ�
void PCMDecoder::setLoop(bool isLoop) {
	isLoop_ = isLoop;
}

//! WAVEFORMATEX�\���̂��擾
bool PCMDecoder::getWaveFormatEx(WAVEFORMATEX& waveFormatEx) {
	if (isReady() == false) {
		return false;
	}

	waveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	waveFormatEx.nChannels = channelNum_;
	waveFormatEx.nSamplesPerSec = samplingRate_;
	waveFormatEx.wBitsPerSample = bitRate_;
	waveFormatEx.nBlockAlign = channelNum_ * bitRate_ / 8;
	waveFormatEx.nAvgBytesPerSec = waveFormatEx.nSamplesPerSec
			* waveFormatEx.nBlockAlign;
	waveFormatEx.cbSize = 0;

	return true;
}

//! �����t���O�ݒ�
void PCMDecoder::setReady(bool isReady) {
	isReady_ = isReady;
}

//! �`�����l�����ݒ�
void PCMDecoder::setChannelNum(unsigned int channelNum) {
	channelNum_ = channelNum;
}

//! �T���v�����O���[�g��ݒ�
void PCMDecoder::setSamplingRate(unsigned int samplingRate) {
	samplingRate_ = samplingRate;
}

//! �r�b�g���[�g��ݒ�
void PCMDecoder::setBitRate(unsigned int bitRate) {
	bitRate_ = bitRate;
}

