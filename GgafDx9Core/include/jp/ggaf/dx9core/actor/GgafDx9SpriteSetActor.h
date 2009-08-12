#ifndef GGAFDX9SPRITESETACTOR_H_
#define GGAFDX9SPRITESETACTOR_H_
namespace GgafDx9Core {

//enum GgafDx9AnimationMethod {
//    ORDER_LOOP, REVERSE_LOOP, OSCILLATE_LOOP, ORDER_NOLOOP, REVERSE_NOLOOP, NOT_ANIMATED
//};

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 */
class GgafDx9SpriteSetActor : public GgafDx9DrawableActor {

private:

    /** �����A�j���t���[���p�J�E���^ */
    unsigned int _aniframe_counter;

public:
    int _draw_set_num;
//    int _draw_set_index;
//    int _draw_object_num;


    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9SpriteSetModel* _pSpriteSetModel;

    /** �G�t�F�N�g */
    GgafDx9SpriteSetEffect* _pSpriteSetEffect;

    /** �A�j���p�^�[���ԍ��̏���ԍ� */
    unsigned int _pattno_ani_top;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ� */
    unsigned int _pattno_ani_bottom;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ�(0�`) */
    unsigned int _pattno_ani_now;
    /** �p�^�[���ƃp�^�[���̊Ԋu�t���[���� */
    unsigned int _frame_ani_interval;
    /** �A�j������ */
    GgafDx9AnimationMethod _animation_method;
    /** OSCILLATE_LOOP�p�̌��݂̃A�j������ */
    bool _is_reverse_order_in_oscillate_animation_flg;

    /** �r���{�[�h�v�� */
    bool _isBillboardingFlg;

    GgafDx9SpriteSetActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw();

    virtual ~GgafDx9SpriteSetActor(); //�f�X�g���N�^

    /**
     * �A�j���[�V���������̃R�}�֐i�߂� .
     * �A�j���[�V�������s�������ꍇ���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
     */
    void addNextAnimationFrame();

    /**
     * �A�j���[�V�����p�^�[����ݒ肷�� .
     * @param prm_pattno_ani �A�j���[�V�����p�^�[���ԍ�
     */
    void setActivAnimationPattern(int prm_pattno_ani);

    /**
     * �A�j���[�V�����p�^�[��������̃A�j���[�V�����p�^�[���ԍ��ɐݒ肷�� .
     */
    void resetActivAnimationPattern();

    /**
     * �A�j���[�V�����p�^�[���͈̔͂𐧌����� .
     * @param prm_top ����̃A�j���[�V�����p�^�[���ԍ�
     * @param prm_bottom �����̃A�j���[�V�����p�^�[���ԍ�
     */
    void setAnimationPatternRenge(int prm_top, int prm_bottom);

    /**
     * �A�j���[�V�������@��ݒ肷��.
     * @param prm_method �A�j���[�V�������@�萔
     * @param prm_interval �A�j���[�V�����Ԋu�t���[���idefault=1)
     */
    void setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_interval);

    /**
     * ���ݒ�.
     * ���I�[�o�[���C�g��
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

    /**
     * �r���{�[�h�L�� .
     * �i�f�t�H���g�͖����ł��j<BR>
     */
    void enableBillboarding() {
        _isBillboardingFlg = true;
    }

    /**
     * �r���{�[�h���� .
     * �i�f�t�H���g�͖����ł��j<BR>
     */
    void disableBillboarding() {
        _isBillboardingFlg = false;
    }
};

}
#endif /*GGAFDX9SPRITESETACTOR_H_*/
