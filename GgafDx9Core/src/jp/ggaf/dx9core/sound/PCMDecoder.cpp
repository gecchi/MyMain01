#include "stdafx.h"

// PCMDecoder.cpp
//

//#include <memory.h>
//#include "PCMDecoder.h"
//#include <string.h>

//! コンストラクタ
PCMDecoder::PCMDecoder() :
	isLoop_(false), isReady_(false), channelNum_(0), samplingRate_(0),
			bitRate_(0) {
}

//! デストラクタ
PCMDecoder::~PCMDecoder() {
}

//! クリア
void PCMDecoder::clear() {
	isLoop_ = false;
	isReady_ = false;
	channelNum_ = 0;
	samplingRate_ = 0;
	bitRate_ = 0;
}

//! ループフラグ取得
bool PCMDecoder::isLoop() {
	return isLoop_;
}

//! 準備できた？
bool PCMDecoder::isReady() {
	return isReady_;
}

//! ループを設定
void PCMDecoder::setLoop(bool isLoop) {
	isLoop_ = isLoop;
}

//! WAVEFORMATEX構造体を取得
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

//! 準備フラグ設定
void PCMDecoder::setReady(bool isReady) {
	isReady_ = isReady;
}

//! チャンネル数設定
void PCMDecoder::setChannelNum(unsigned int channelNum) {
	channelNum_ = channelNum;
}

//! サンプリングレートを設定
void PCMDecoder::setSamplingRate(unsigned int samplingRate) {
	samplingRate_ = samplingRate;
}

//! ビットレートを設定
void PCMDecoder::setBitRate(unsigned int bitRate) {
	bitRate_ = bitRate;
}

