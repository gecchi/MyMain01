#include "jp/ggaf/dxcore/sound/IkdLib/OggDecoder.h"

#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisResource.h"

using namespace IkdLib;

namespace {
const unsigned int requestSize_g = 4096; // �ǂݍ��ݒP��
}

//! �R���X�g���N�^
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
        isAdjust = true; // �����i�K
    }

    while (1) {
        readSize = ov_read(&ovf, (char*) (prm_buffer + comSize ), requestSize, 0, 2, 1, &bitstream );
        if(readSize == 0 ) {
            // �t�@�C���G���h�ɒB����
            if (isLooping()) {
                // ���[�v����ꍇ�ǂݍ��݈ʒu���ŏ��ɖ߂�
                ov_time_seek( &ovf, 0.0 );
            } else {
                // ���[�v���Ȃ��ꍇ�t�@�C���G���h�ɒB������I��
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
//              _DTRACE_("�o�b�t�@�I�[�o�[");
//          }
        //_ASSERT( comSize <= prm_size );   // �o�b�t�@�I�[�o�[

        if (comSize >= prm_size) {
            // �o�b�t�@�𖄂ߐs�������̂ŏI��
            if (pUInt_write_size) *pUInt_write_size = comSize;
            return true;
        }

        if (prm_size - comSize < requestSize_g) {
            isAdjust = true; // �����i�K
            requestSize = prm_size - comSize;
        }
    }

    if (pUInt_write_size) *pUInt_write_size = 0;
    return false; //�s���G���[
}

void OggDecoder::setHead() {
    if (isReady()) {
        ov_time_seek(&_pOggVorbisResource->getOggVorbisFile(), 0.0);
    }
}

PCMDecoder* OggDecoder::createClone() {
    OggDecoder * spObj = NEW OggDecoder;
    if (_pOggVorbisResource->isReady() == false) {
        return spObj; // ���Ԃ�
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
        // �N���[���쐬���s
        return false;
    }
    // Ogg�����{�����i�[
    vorbis_info *info = ov_info(&_pOggVorbisResource->getOggVorbisFile(), -1);
    setChannelNum(info->channels);
    setBitRate(16);
    setSamplingRate(info->rate);
    setReady(true);
    return true;
}
