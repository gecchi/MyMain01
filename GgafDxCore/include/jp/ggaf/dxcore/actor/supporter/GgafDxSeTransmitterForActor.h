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

public:
    /** [r/w]�eSE�i�z��j�́A�[���RD�Đ����ǂ�����ێ� */
    bool* _pa_is3D;
    /** [r]SE�������A�N�^�[ */
    GgafDxGeometricActor* _pActor;

    /**
     * �R���X�g���N�^ .
     */
    GgafDxSeTransmitterForActor(GgafDxGeometricActor* prm_pActor);

    /**
     * SE�g�p����錾���� .
     * �{�I�u�W�F�N�g�̋@�\�𗘗p����ɂ́A�K�{�B
     * @param prm_se_num SE���i��ސ��j
     */
    void useSe(int prm_se_num) override;

    /**
     * ������SE���Đ�����(�[���RD����)�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void play(int prm_id) override;

    /**
     * SE�̋[���RD�Đ� .
     * �I�u�W�F�N�g�̍��W�ƃJ�����̍��W����A���E�̃p���B
     * �����ɉ����Ẵ{�����[�������ƁA�x���Đ����s���B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void play3D(int prm_id);

    /**
     * ���t���[���̏��� .
     * updatePanVolume3D() ���Ăяo�����s���Ă���B
     * play3D()���g�p���Ă��Ȃ��̂ł���΁A�Ăяo���K�v�͂Ȃ��B
     */
    void behave();

    /**
     * �f�X�g���N�^
     */
    virtual ~GgafDxSeTransmitterForActor();
};

}
#endif /*GGAFDXSETRANSMITTERFORACTOR_H_*/
