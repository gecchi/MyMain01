#include "jp/ggaf/dx/sound/IkdLib/OggDecoder.h"

#include "jp/ggaf/dx/sound/IkdLib/OggVorbisResource.h"

using namespace IkdLib;

namespace {
//const unsigned int requestSize_g = 4096; // 読み込み単位
const unsigned int requestSize_g = 2048; // 読み込み単位
}

//! コンストラクタ
OggDecoder::OggDecoder() {
    _pOggVorbisResource = nullptr;
}

OggDecoder::OggDecoder(OggVorbisResource* prm_pOggVorbisResource) {
    _pOggVorbisResource = nullptr;
    setResource(prm_pOggVorbisResource);
}

OggDecoder::~OggDecoder() {
    GGAF_DELETE(_pOggVorbisResource);
    clear();
}

void OggDecoder::clear() {
    PCMDecoder::clear();
}

bool OggDecoder::getSegment(char* prm_buffer, unsigned int prm_size, unsigned int* pUInt_write_size, bool* pBool_is_end) {
    if (isReady() == false) {
        return false;
    }

    if (prm_buffer == 0) {
        if (pBool_is_end) *pBool_is_end = true;
        if (pUInt_write_size) *pUInt_write_size = 0;
        return false;
    }

    OggVorbis_File& ovf = _pOggVorbisResource->getOggVorbisFile();

    if (pBool_is_end) *pBool_is_end = false;

    memset(prm_buffer, 0, prm_size);
    unsigned int requestSize = requestSize_g;
    int bitstream = 0;
    int readSize = 0;
    unsigned int comSize = 0;
    bool isAdjust = false;

    if (prm_size < requestSize) {
        requestSize = prm_size;
        isAdjust = true; // 調整段階
    }

    while (1) {
        readSize = ov_read(&ovf, (char*) (prm_buffer + comSize ), requestSize, 0, 2, 1, &bitstream );
        if(readSize == 0 ) {
            // ファイルエンドに達した
            if (isLooping()) {
                // ループする場合読み込み位置を最初に戻す
                ov_time_seek( &ovf, 0.0 );
            } else {
                // ループしない場合ファイルエンドに達したら終了
                if (pBool_is_end ) {
                    *pBool_is_end = true;
                }
                if (pUInt_write_size ) {
                    *pUInt_write_size = comSize;
                }
                return true;
            }
        }

        comSize += readSize;

//          if (comSize <= prm_size) {
//              _TRACE_("バッファオーバー");
//          }
        //_ASSERT( comSize <= prm_size );   // バッファオーバー

        if (comSize >= prm_size) {
            // バッファを埋め尽くしたので終了
            if (pUInt_write_size) *pUInt_write_size = comSize;
            return true;
        }

        if (prm_size - comSize < requestSize_g) {
            isAdjust = true; // 調整段階
            requestSize = prm_size - comSize;
        }
    }

    if (pUInt_write_size) *pUInt_write_size = 0;
    return false; //不明エラー
}

void OggDecoder::setHead() {
    if (isReady()) {
        ov_time_seek(&_pOggVorbisResource->getOggVorbisFile(), 0.0);
    }
}

PCMDecoder* OggDecoder::createClone() {
    OggDecoder * spObj = NEW OggDecoder;
    if (_pOggVorbisResource->isReady() == false) {
        return spObj; // 空を返す
    }
    spObj->setResource(_pOggVorbisResource);
    return spObj;
}

bool OggDecoder::setResource(OggVorbisResource* prm_pOggVorbisResource) {
    clear();
    if (prm_pOggVorbisResource == nullptr || prm_pOggVorbisResource->isReady() == false) {
        return false;
    }

    _pOggVorbisResource = prm_pOggVorbisResource->createClone();
    if (_pOggVorbisResource == nullptr) {
        // クローン作成失敗
        return false;
    }
    // Oggから基本情報を格納
    vorbis_info *info = ov_info(&_pOggVorbisResource->getOggVorbisFile(), -1);
    setChannelNum(info->channels);
    setBitRate(16);
    setSamplingRate(info->rate);
    setReady(true);
    return true;
}
