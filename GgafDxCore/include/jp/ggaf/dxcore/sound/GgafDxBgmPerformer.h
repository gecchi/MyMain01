#ifndef GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#define GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * BGM���t�x���N���X .
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformer : public GgafCore::GgafObject {

public:
//    static int _active_bgm_bpm;
    /** [r]BGM�`�����l���� */
    int _bgm_num;
    /** [r]BGM�̃{�����[���z��(�Y����BGM�`�����l���ԍ�) */
    double* _paDouble_volume;
    /** [r]Bgm�����ڑ� */
    GgafDxBgmConnection** _papBgmConnection;

public:
    GgafDxBgmPerformer();

    /**
     * BGM��ݒ肷��B
     * @param prm_id BGM�`�����l���ԍ�(0 �` )
     * @param prm_bgm_name �v���p�e�B�t�@�C����_OGG, _BPM, _TITLE �̃v���t�B�b�N�X�ƂȂ��Ă���key������
     */
    virtual void ready(int prm_id, const char* prm_bgm_name);

    /**
     * �{�����[����ݒ肷��B
     * @param prm_id     BGM�`�����l���ԍ�(0 �` )
     * @param prm_volume �{�����[���l(0 �` 100)
     */
    virtual void setVolume(int prm_id, int prm_volume);

    /**
     * BGM���Đ�����B
     * @param prm_id       BGM�`�����l���ԍ�(0 �` )
     * @param prm_volume   �{�����[���l(0 �` 100)
     * @param prm_is_loop  ���[�v���邩�ǂ����itrue:���[�v�Đ�����^false:���[�v�Đ����Ȃ��j
     */
    virtual void play(int prm_id, int prm_volume, bool prm_is_loop);

    /**
     * BGM���Đ�����(���[�v�Đ�)�B
     * @param prm_id     BGM�`�����l���ԍ�(0 �` )
     * @param prm_volume �{�����[���l(0 �` 100)
     */
    virtual void play(int prm_id, int prm_volume) {
        play(prm_id, prm_volume, true);
    }

    /**
     * BGM���Đ�����(���[�v�Đ�, �{�����[��GGAF_MAX_VOLUME)�B
     * @param prm_id BGM�`�����l���ԍ�(0 �` )
     */
    virtual void play(int prm_id) {
        play(prm_id, GGAF_MAX_VOLUME);
    }

    /**
     * BGM���~���� .
     * @param prm_id BGM�`�����l���ԍ�(0 �` )
     */
    virtual void stop(int prm_id);

    /**
     * BGM���ꎞ��~���� .
     * @param prm_id BGM�`�����l���ԍ�(0 �` )
     */
    virtual void pause(int prm_id);

    /**
     * BGM�̈ꎞ��~���������� .
     * @param prm_id  BGM�`�����l���ԍ�(0 �` )
     */
    virtual void unpause(int prm_id);

    /**
     * �SBGM�`�����l���ԍ���BGM���~ .
     */
    virtual void stop();

    /**
     * �SBGM�`�����l���ԍ���BGM���ꎞ��~ .
     */
    virtual void pause();

    /**
     * �SBGM�`�����l���ԍ���BGM�̈ꎞ��~���������� .
     */
    virtual void unpause();

    virtual ~GgafDxBgmPerformer();
};

}
#endif /*GGAFDXCORE_GGAFDXBGMPERFORMER_H_*/
