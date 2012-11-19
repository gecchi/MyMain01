#ifndef GGAFDXSETRANSMITTERFORACTOR_H_
#define GGAFDXSETRANSMITTERFORACTOR_H_
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
     * �p���ƃ{�����[�����X�V����B
     * play3D�̌��ʂ��p�����邽�߂ɖ��t���[���Ăяo���K�v������B
     */
    void updatePanVolume3D();

    /**
     * SE�g�p����錾���� .
     * @param prm_se_num SE���i��ސ��j
     */
    void declareSeNum(int prm_se_num) override;

    /**
     * SE�̐ݒ���s�� .
     * �A���ASE�̍Đ����Ԃ� GGAF_SAYONARA_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �㏑���Đݒ�\�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     * @param prm_se_key SE��`���i�v���p�e�B�t�@�C���̃L�[�j
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    void set(int prm_id, const char* prm_se_key, int prm_cannel) override;

public:
    /** [r/w]�eSE�i�z��j�́A�[���RD�Đ����ǂ�����ێ� */
    bool* _paBool_is_playing_3d;
    /** [r]SE�������A�N�^�[ */
    GgafDxGeometricActor* _pActor;

    /**
     * �R���X�g���N�^ .
     */
    GgafDxSeTransmitterForActor(GgafDxGeometricActor* prm_pActor);

    /**
     * SE�̐ݒ���s�� .
     * ���O declareSeNum() �͕s�v(�ɂȂ���)�B
     * SE�̍Đ����Ԃ� GGAF_SAYONARA_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �`�����l�����́A������ prm_se_key+"_CH" �Ƃ����v���p�e�B�l���Q�Ƃ����B
     * ���݂��Ȃ��ꍇ�A�Đ��`�����l���ԍ���0�Œ�(���`�����l������1)
     * �ݒ�ς�ID�ɁA�㏑���Đݒ�\�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     * @param prm_se_key SE��`���i�v���p�e�B�t�@�C���̃L�[�j
     */
    void set(int prm_id, const char* prm_se_key);

    /**
     * ������SE���Đ�����(�[���RD����)�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void play(int prm_id) override;

    /**
     * SE�̋[���RD�Đ� .
     * �I�u�W�F�N�g�̍��W�ƃJ�����̍��W����A���E�̃p���B
     * �����ɉ����Ẵ{�����[�������ƁA�x���Đ����s���B
     * behave() �𖈃t���[���Ăяo���Ă����ƁASE�Đ������[���RD���ʂ𓾂�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void play3D(int prm_id);

    /**
     * ���t���[���̏��� .
     * updatePanVolume3D() ���Ăяo�����s���Ă���B
     * play3D()���g�p���Ă��Ȃ��̂ł���΁A�Ăяo���K�v�͂Ȃ��B
     * ����SE�Đ����ɁA�t���[�����Ԃɂ܂������ċ[���RD���ʂ𓾂�ꍇ�́A�Ăяo���K�v������B
     * SE�Đ����A�Đ��J�n���_�ł̋[���RD���ʂŗǂ���΁A�Ăяo���K�v���Ȃ��B
     */
    void behave();

    /**
     * �f�X�g���N�^
     */
    virtual ~GgafDxSeTransmitterForActor();
};

}
#endif /*GGAFDXSETRANSMITTERFORACTOR_H_*/
