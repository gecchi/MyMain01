#ifndef GGAFDX9SPRITEACTORD_H_
#define GGAFDX9SPRITEACTORD_H_
namespace GgafDx9Core {

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteActor : public GgafDx9DrawableActor {

private:

    /** �����A�j���t���[���p�J�E���^ */
    unsigned int _frame_counter_uvflip;

public:
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9SpriteModel* _pSpriteModel;

    /** �G�t�F�N�g */
    GgafDx9SpriteEffect* _pSpriteEffect;
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFliper* _pUvFliper;


//    /** �A�j���p�^�[���ԍ��̏���ԍ� */
//    unsigned int _pattno_uvflip_top;
//    /** ���ݕ\�����̃A�j���p�^�[���ԍ� */
//    unsigned int _pattno_uvflip_bottom;
//    /** ���ݕ\�����̃A�j���p�^�[���ԍ�(0�`) */
//    unsigned int _pattno_uvflip_now;
//    /** �p�^�[���ƃp�^�[���̊Ԋu�t���[���� */
//    unsigned int _frame_uvflip_interval;
//    /** �A�j������ */
//    GgafDx9UvFlipMethod _uvflip_method;
//    /** FLIP_OSCILLATE_LOOP�p�̌��݂̃A�j������ */
//    bool _is_reverse_order_in_oscillate_animation_flg;


    GgafDx9SpriteActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() override;

    virtual ~GgafDx9SpriteActor(); //�f�X�g���N�^

//    /**
//     * �A�j���[�V���������̃R�}�֐i�߂� .
//     * �A�j���[�V�������s�������ꍇ���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
//     */
//    void behaveUvFlip();
//
//    /**
//     * �A�j���[�V�����p�^�[����ݒ肷�� .
//     * @param prm_pattno_uvflip �A�j���[�V�����p�^�[���ԍ�
//     */
//    void setUvFlipPtnNo(int prm_pattno_uvflip);
//
//    /**
//     * �A�j���[�V�����p�^�[��������̃A�j���[�V�����p�^�[���ԍ��ɐݒ肷�� .
//     */
//    void resetUvFlipPtnNo();
//
//    /**
//     * �A�j���[�V�����p�^�[���͈̔͂𐧌����� .
//     * @param prm_top ����̃A�j���[�V�����p�^�[���ԍ�
//     * @param prm_bottom �����̃A�j���[�V�����p�^�[���ԍ�
//     */
//    void forceUvFlipPtnRange(int prm_top, int prm_bottom);
//
//    /**
//     * �A�j���[�V�������@��ݒ肷��.
//     * @param prm_method �A�j���[�V�������@�萔
//     * @param prm_interval �A�j���[�V�����Ԋu�t���[���idefault=1)
//     */
//    void setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval);

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

//    /**
//     * �r���{�[�h�L�� .
//     * �i�f�t�H���g�͖����ł��j<BR>
//     */
//    void enableBillboarding() {
//        _isBillboardingFlg = true;
//    }
//
//    /**
//     * �r���{�[�h���� .
//     * �i�f�t�H���g�͖����ł��j<BR>
//     */
//    void disableBillboarding() {
//        _isBillboardingFlg = false;
//    }
};

}
#endif /*GGAFDX9SPRITEACTORD_H_*/
