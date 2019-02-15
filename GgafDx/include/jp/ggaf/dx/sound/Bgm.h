#ifndef GGAF_DX_BGM_H_
#define GGAF_DX_BGM_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>

namespace GgafDx {

/**
 * Bgm(Ogg�t�H�[�}�b�g)�N���X .
 */
class Bgm : public GgafCore::Object {
    static std::string getOggFileName(std::string prm_file);

public:
    char* _bgm_key;
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
    /** [r]���݂̉��ʒl(0 �` 1000) */
    int _volume;
    /** [r]���݂̃p���l(left:-1.0 �` center:0 �` right:1.0) */
    float _pan;

public:
    /**
     * �R���X�g���N�^ .
     * �v���p�e�B�t�@�C�����玟�̃L�[�̒l���擾���܂��B
     * �@ prm_bgm_key         �E�E�E �l�FBGM�ƂȂ� ogg�t�@�C����
     * �A prm_bgm_key+"_BPM"  �E�E�E �l�F���ݖ��g�p(:TODO)
     * �B prm_bgm_key+"_TITLE"�E�E�E �l�F���ݖ��g�p(:TODO)
     * ���ɁA�@�̂̒l����BGM�ƂȂ� ogg�t�@�C���� �v���p�e�B�t�@�C����
     * DIR_OGG[0] �̐ݒ�l�z������T���ăI�[�v�����A�Đ��������s���܂��B
     * @param prm_bgm_key �v���p�e�B�t�@�C����key
     * @return
     */
    explicit Bgm(const char* prm_bgm_key);


    virtual char* getKeyName() {
        return _bgm_key;
    }

    virtual std::string getFileName() {
        return _ogg_file_name;
    }

    /**
     * BGM�Đ� .
     * @param prm_is_looping true:���[�v�Đ�
     */
    virtual void play(bool prm_is_looping = true);

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
     * �������A�����Ŏ��ۂɐݒ肳��鉹�ʂ́ABGM�}�X�^�[���ʗ����悶��ꂽ�l�ƂȂ�܂��B
     * @param volume 0�`1000
     */
    void setVolume(int volume);

    /**
     * BGM�̃{�����[�����擾 .
     * �擾����鉹�ʂ́ABGM�}�X�^�[���ʗ����l�������O�̒l�B
     * �܂�A�{�N���X��setVolume(int) �Őݒ肵���l�����̂܂܎擾����܂��B
     * @return BGM�̃{�����[��(0�`1000)
     */
    virtual int getVolume() {
        return _volume;
    }

    /**
     * BGM�̃p���ݒ� .
     * @param pan �� -1.0 �` 0 �` 1.0 �E
     */
    void setPan(float pan);

    virtual int getPan() {
        return _pan;
    }

    /**
     * �Đ��X���b�h���~�����A�T�E���h�o�b�t�@��������� .
     */
    virtual void clear();

    /**
     * �Đ������ǂ�����Ԃ�
     * @return
     */
    virtual bool isPlaying();

    virtual bool isPause();

    virtual bool isStopping();

    virtual ~Bgm();
};

}
#endif /*GGAF_DX_BGM_H_*/
