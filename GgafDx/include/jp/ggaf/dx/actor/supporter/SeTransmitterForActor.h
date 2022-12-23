#ifndef GGAF_DX_SETRANSMITTERFORACTOR_H_
#define GGAF_DX_SETRANSMITTERFORACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/sound/SeTransmitter.h"

namespace GgafDx {

/**
 * �A�N�^�[�p�T�E���h�G�t�F�N�g�o�͎x���N���X .
 * �Ȉ�3D���ʉ��@�\�̒ǉ��B
 * SeTransmitter ���番��
 * @version 1.00
 * @since 2012/03/22
 * @author Masatoshi Tsuge
 */
class SeTransmitterForActor : public SeTransmitter {

private:
    /**
     * �Đ���SE�̃p���ƃ{�����[�����X�V����B
     */
    void updatePanVolume3D();


public:
    /** [r/w]�eSE�i�z��j�́A�[��3D�Đ����ǂ����̏���ێ� */
    std::vector<int> _vec_is_playing_3d;
    //0:3D�Đ����Ă��Ȃ�
    //1:3D�Đ����Ă��邪�A�����܂��Ȃ��Ă��Ȃ��i���������o�̒x�����A�T�E���h�o�b�t�@�Ƀf�[�^���Ȃ��j
    //2:3D�Đ����Ă邵�A�������Ă���B
    frame _playing_3d_freames;
    /** [r]SE�������A�N�^�[ */
    GeometricActor* const _pActor;

    /** [r]�O��v�Z���̃J��������A�N�^�[�̋��� */
    double _px_d_cam_acter_prev;

    static frame _se_delay_max_depth;

public:
    /**
     * �R���X�g���N�^ .
     */
    explicit SeTransmitterForActor(GeometricActor* prm_pActor);

    /**
     * SE�̐ݒ���s�� .
     * SE�̍Đ����Ԃ� GGAF_END_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �`�����l�����́A������ prm_se_key+"_CH" �Ƃ����v���p�e�B�l���Q�Ƃ����B
     * ���݂��Ȃ��ꍇ�A�Đ��`�����l���ԍ���0�Œ�(���`�����l������1)
     * �ݒ�ς�ID�ɁA�㏑���Đݒ�\�B
     * @param se_no SE�o�^�ԍ� ( 0 �` SE��-1 )
     * @param prm_se_key SE��`���i�v���p�e�B�t�@�C���̃L�[�j
     */
    void set(int prm_se_no, const char* prm_se_key);

    /**
     * SE�̐ݒ���s�� .
     * �A���ASE�̍Đ����Ԃ� GGAF_END_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �㏑���Đݒ�\�B
     * @param se_no SE�o�^�ԍ� ( 0 �` SE��-1 )
     * @param prm_se_key SE��`���i�v���p�e�B�t�@�C���̃L�[�j
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    void set(int prm_se_no, const char* prm_se_key, int prm_cannel) override;

    /**
     * ������SE���Đ�����(�[���RD����)�B
     * @param prm_se_no SE�o�^�ԍ� ( 0 �` SE��-1 )
     */
    void play(int prm_se_no, bool prm_can_looping = false) override;

    /**
     * SE�̋[���RD�Đ� .
     * �I�u�W�F�N�g�̍��W�ƃJ�����̍��W����A���E�̃p���B<BR>
     * �����ɉ����Ẵ{�����[�������ƁA�x���Đ����s���B<BR>
     * ����� behave() �𖈃t���[���Ăяo���Ă����ƁA���ʉ��������̈ړ����[���RD���ʂ𓾂�B<BR>
     * @param prm_se_no SE�o�^�ԍ� ( 0 �` SE��-1 )
     */
    void play3D(int prm_se_no, bool prm_can_looping = false);

    /**
     * �[���RD���ʍĐ��̖��t���[���̏��� .
     * play3D() ���g�p���Ă��Ȃ��̂ł���΁A�Ăяo���K�v�͂Ȃ��B<BR>
     * play3D() ���g�p���A����Ɍ��ʉ��Đ����ɃA�N�^�[���ړ����A���̈ړ��ɔ����RD���ʂ𓾂����ꍇ�A<BR>
     * �{���\�b�h�𖈃t���[���Ăяo���K�v������B�܂�A�Đ����Ԃ��������ʉ��͌Ăяo�����ق������ʓI�B<BR>
     * SE�Đ����A�Đ��J�n�����W�ł̋[���RD���ʂ݂̂ŗǂ���΁A�Ăяo���K�v�͂Ȃ��B<BR>
     * �����͏d�߂Ǝv���̂ŁA��ʃI�u�W�F�N�g�ŌĂяo���Ȃ��悤�ɒ��ӂ��K�v<BR>
     * ���������� updatePanVolume3D() ���Ăяo���𐔃t���[�����ɍs���Ă���B<BR>
     */
    void behave();

    /**
     * �f�X�g���N�^
     */
    virtual ~SeTransmitterForActor();
};

}
#endif /*GGAF_DX_SETRANSMITTERFORACTOR_H_*/
