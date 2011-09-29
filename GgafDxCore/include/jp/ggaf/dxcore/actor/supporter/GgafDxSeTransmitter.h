#ifndef GGAFDXSEREFLECTOR_H_
#define GGAFDXSEREFLECTOR_H_
namespace GgafDxCore {

/**
 * �T�E���h�G�t�F�N�g�o�͎x���N���X .
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitter : public GgafCore::GgafObject {

private:
    /**
     * �p���ƃ{�����[�����X�V����B
     * play3D�̌��ʂ��p�����邽�߂ɖ��t���[���Ăяo���K�v������B
     */
    void updatePanVolume3D();

public:
    /** SE�����ڑ� */
    GgafDxSeConnection** _papSeCon;
    /** �[���RD�Đ����ۂ� */
    bool* _pa_is3D;

    int _se_num;
    GgafDxGeometricActor* _pActor;
    /**
     * �R���X�g���N�^ .
     */
    GgafDxSeTransmitter(GgafDxGeometricActor* prm_pActor);

    /**
     * SE�g�p����錾���� .
     * �{�I�u�W�F�N�g�̋@�\�𗘗p����ɂ́A�K�{�B
     * @param prm_se_num SE��
     */
    void useSe(int prm_se_num);

    /**
     * SE�̐ݒ���s�� .
     * �A���ASE�̍Đ����Ԃ� GGAF_SAYONARA_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     * @param prm_se_name SE��`��
     * @param prm_cannel �`�����l��
     */
    void set(int prm_id, const char* prm_se_name, int prm_cannel = 1);

    /**
     * ������SE���Đ�����(�[���RD����)�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void playImmediately(int prm_id);

    /**
     * SE���Đ�����(�[���RD����)�B
     * playImmediately(int) �ƈႢ�A���t���[���ɍĐ������\�胊�X�g�ɒǉ������B
     * �����A����t���[���ɁA�����ނ�SE�������o�^���ꂽ�ꍇ�A���̒��ˏオ���}���邽�߁A
     * �ő�W�t���[���x�����A�΂炯�čĐ������@�\�������Ă���B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    void play(int prm_id);

    /**
     * SE�̋[���RD�Đ� .
     * �I�u�W�F�N�g�̍��W�ƃJ�����̍��W����A
     * ���E�̃p���A�����ɉ����Ẵ{�����[�������ƁA�x���Đ��B
     * ���s���B
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
    virtual ~GgafDxSeTransmitter();
};

}
#endif /*GGAFDXSEREFLECTOR_H_*/
