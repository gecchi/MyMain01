#ifndef GGAFDXCORE_GGAFDXSETRANSMITTERFORACTOR_H_
#define GGAFDXCORE_GGAFDXSETRANSMITTERFORACTOR_H_
#include "jp/ggaf/dxcore/sound/GgafDxSeTransmitter.h"

namespace GgafDxCore {

/**
 * �A�N�^�[�p�T�E���h�G�t�F�N�g�o�͎x���N���X .
 * �Ȉ�3D���ʉ��@�\�̒ǉ��B
 * GgafDxSeTransmitter ���番��
 * @version 1.00
 * @since 2012/03/22
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitterForActor : public GgafDxSeTransmitter {

private:
    /**
     * �Đ���SE�̃p���ƃ{�����[�����X�V����B
     */
    void updatePanVolume3D();

    /**
     * SE�g�p����錾���� .
     * @param prm_se_num SE���i��ސ��j
     */
    void declareSeNum(int prm_se_num) override;

public:
    /** [r/w]�eSE�i�z��j�́A�[���RD�Đ����ǂ�����ێ� */
    bool* _paBool_is_playing_3d;
    /** [r]SE�������A�N�^�[ */
    GgafDxGeometricActor* _pActor;

public:
    /**
     * �R���X�g���N�^ .
     */
    GgafDxSeTransmitterForActor(GgafDxGeometricActor* prm_pActor);

    /**
     * SE�̐ݒ���s�� .
     * ���O declareSeNum() �͕s�v(�ɂȂ���)�B
     * SE�̍Đ����Ԃ� GGAF_END_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �`�����l�����́A������ prm_se_key+"_CH" �Ƃ����v���p�e�B�l���Q�Ƃ����B
     * ���݂��Ȃ��ꍇ�A�Đ��`�����l���ԍ���0�Œ�(���`�����l������1)
     * �ݒ�ς�ID�ɁA�㏑���Đݒ�\�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     * @param prm_se_key SE��`���i�v���p�e�B�t�@�C���̃L�[�j
     */
    void set(int prm_id, const char* prm_se_key);

    /**
     * SE�̐ݒ���s�� .
     * �A���ASE�̍Đ����Ԃ� GGAF_END_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �㏑���Đݒ�\�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     * @param prm_se_key SE��`���i�v���p�e�B�t�@�C���̃L�[�j
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    void set(int prm_id, const char* prm_se_key, int prm_cannel) override;

    /**
     * ������SE���Đ�����(�[���RD����)�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void play(int prm_id) override;

    /**
     * SE�̋[���RD�Đ� .
     * �I�u�W�F�N�g�̍��W�ƃJ�����̍��W����A���E�̃p���B<BR>
     * �����ɉ����Ẵ{�����[�������ƁA�x���Đ����s���B<BR>
     * ����� behave() �𖈃t���[���Ăяo���Ă����ƁA���ʉ��������̈ړ����[���RD���ʂ𓾂�B<BR>
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void play3D(int prm_id);

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
    virtual ~GgafDxSeTransmitterForActor();
};

}
#endif /*GGAFDXCORE_GGAFDXSETRANSMITTERFORACTOR_H_*/
