#ifndef GGAFDXCORE_GGAFDXBGM_H_
#define GGAFDXCORE_GGAFDXBGM_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <string>

namespace GgafDxCore {

/**
 * Bgm(Ogg�t�H�[�}�b�g)�N���X .
 */
class GgafDxBgm : public GgafCore::GgafObject {
    static std::string getOggFileName(std::string prm_file);

public:
//    /** [r]BGM �� BMP */
//    int _bpm;
//    /** [r]BGM �� �^�C�g�� */
//    std::string _title;
    /** [r]BGM �� ogg�t�@�C����(�p�X����) */
    std::string _ogg_file_name;
    /** [r]PCMPlayer */
    IkdLib::PCMPlayer* _pPcmPlayer;
    IkdLib::OggVorbisFile* _pOggResource;
    IkdLib::OggDecoder* _pOggDecoder;

public:
    /**
     * �R���X�g���N�^ .
     * �v���p�e�B�t�@�C�����玟�̃L�[�̒l���擾���܂��B
     * �@ prm_bgm_key+"_OGG"      �E�E�E �l�FBGM�ƂȂ� ogg�t�@�C����
     * �A prm_bgm_key+"_BPM"      �E�E�E �l�F���ݖ��g�p
     * �B prm_bgm_key+"_TITLE"    �E�E�E �l�F���ݖ��g�p
     * ���ɁA�@�̂̒l����BGM�ƂȂ� ogg�t�@�C���� �v���p�e�B�t�@�C����
     * DIR_OGG[0] �̐ݒ�l�z������T���ăI�[�v�����A�Đ��������s���܂��B
     * @param prm_bgm_key �v���p�e�B�t�@�C����key
     *                    _OGG, _BPM, _TITLE �̃v���t�B�b�N�X���w��
     * @return
     */
    explicit GgafDxBgm(const char* prm_bgm_key);

    /**
     * BGM�Đ� .
     * �{�����[���ɂ��āA�����Ń}�X�^�{�����[���̍l�������������B
     * �A�v���P�[�V�������́A�{���̉��ʂ��C�ɂ����ʏ�Đ��������ꍇ�́A
     * �{�����[����100�Őݒ肷�鎖�B
     * @param prm_volume 0�`100
     * @param prm_pan �� -1.0 �` 0 �` 1.0 �E
     * @param prm_is_looping true:���[�v�Đ�
     */
    virtual void play(int prm_volume, float prm_pan, bool prm_is_looping);

    /**
     * BGM�Đ� .
     * �{�����[���ɂ��āA�����Ń}�X�^�{�����[���̍l�������������B
     * �A�v���P�[�V�������́A�{���̉��ʂ��C�ɂ����ʏ�Đ��������ꍇ�́A
     * �{�����[����100�Őݒ肷�鎖�B
     * @param prm_is_looping true:���[�v�Đ�
     */
    virtual void play(bool prm_is_looping);

    /**
     * �ꎞ��~���� .
     * �Đ����� pause() ����ƁA�T�E���h�o�b�t�@����~����邪�A
     * �T�E���h�o�b�t�@�̓��o�͍s��ꖳ���B<BR>
     * �ꎞ��~���� pause() ���Ă�������������Ȃ��B<BR>
     * ��~���� pause() ���Ă�������������Ȃ��B<BR>
     */
    virtual void pause();

    /**
     * �ꎞ��~���������� .
     * �ꎞ��~���� unpause() ����ƁA�T�E���h�o�b�t�@���Đ������B
     * ���[�v�̐ݒ�͈����p�����B<BR>
     * �Đ����� unpause() ���Ă�������������Ȃ��B<BR>
     * ��~���� unpause() ���Ă�������������Ȃ��B<BR>
     */
    virtual void unpause();

    /**
     * BGM�̒�~ .
     * �ǂ̗l�ȏ�Ԃł��A�T�E���h�o�b�t�@����~���A�T�E���h�o�b�t�@�̓��o�����s����B
     */
    virtual void stop();

    /**
     * BGM�̃{�����[���ݒ� .
     * �����Ń}�X�^�{�����[���̍l�������������B
     * �A�v���P�[�V�������́A�{���̉��ʂ��C�ɂ����ʏ�Đ��������ꍇ�́A
     * �{�����[����100�Őݒ肷�鎖�B
     * @param volume 0�`100
     */
    virtual void setVolume(int volume);

    /**
     * BGM�̃p���ݒ� .
     * @param pan �� -1.0 �` 0 �` 1.0 �E
     */
    virtual void setPan(float pan);

    /**
     * �Đ��X���b�h���~�����A�T�E���h�o�b�t�@��������� .
     */
    virtual void clear();

    /**
     * �Đ������ǂ�����Ԃ�
     * @return
     */
    virtual bool isPlaying();

    virtual ~GgafDxBgm();
};

}
#endif /*GGAFDXCORE_GGAFDXBGM_H_*/
