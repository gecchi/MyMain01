#ifndef GGAFDX9SPRITEACTORD_H_
#define GGAFDX9SPRITEACTORD_H_
namespace GgafDx9Core {

enum GgafDx9AnimationMethod {
    ORDER_LOOP, REVERSE_LOOP, OSCILLATE_LOOP, ORDER_NOLOOP, REVERSE_NOLOOP, NOT_ANIMATED
};

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDx9UntransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 */
class GgafDx9SpriteActor : public GgafDx9UntransformedActor {

private:

    /** �����A�j���t���[���p�J�E���^ */
    unsigned int _iCounter_AnimationFrame;

public:
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9ModelLead* _pModelLead;
    GgafDx9SpriteModel* _pSpriteModel;
    /** �L�����S�̂̃� */
    float _fAlpha;

    /** �A�j���p�^�[���ԍ��̏���ԍ� */
    unsigned int _iAnimationPatternNo_Top;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ� */
    unsigned int _iAnimationPatternNo_Bottom;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ�(0�`) */
    unsigned int _iAnimationPatternNo_Active;
    /** �p�^�[���ƃp�^�[���̊Ԋu�t���[���� */
    unsigned int _iAnimationFrame_Interval;
    /** �A�j������ */
    GgafDx9AnimationMethod _animation_method;
    /** OSCILLATE_LOOP�p�̌��݂̃A�j������ */
    bool _oscillateAnimationOrderFlg;

    /** �r���{�[�h�v�� */
    bool _isBillboarding;

    GgafDx9SpriteActor(const char* prm_name,
                       const char* prm_spritemodel_name,
                       GgafDx9GeometryMover* prm_pGeoMover,
                       GgafDx9GeometryChecker* prm_pGeoChecker);

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDrawMain();

    virtual ~GgafDx9SpriteActor(); //�f�X�g���N�^

    /**
     * �A�j���[�V���������̃R�}�֐i�߂� .
     * �A�j���[�V�������s�������ꍇ���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
     */
    void nextAnimationFrame();

    /**
     * �A�j���[�V�����p�^�[����ݒ肷�� .
     * @param prm_iAnimationPatternNo �A�j���[�V�����p�^�[���ԍ�
     */
    void setActivAnimationPattern(int prm_iAnimationPatternNo);

    /**
     * �A�j���[�V�����p�^�[���͈̔͂𐧌����� .
     * @param prm_iTop����̃A�j���[�V�����p�^�[���ԍ�
     * @param prm_bottom �����̃A�j���[�V�����p�^�[���ԍ�
     */
    void setAnimationPatternRenge(int prm_iTop, int prm_bottom);

    /**
     * �A�j���[�V�������@��ݒ肷��.
     * @param prm_method �A�j���[�V�������@�萔
     * @param prm_iInterval �A�j���[�V�����Ԋu�t���[���idefault=1)
     */
    void setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_iInterval);

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
        _isBillboarding = true;
    }

    /**
     * �r���{�[�h���� .
     * �i�f�t�H���g�͖����ł��j<BR>
     */
    void disableBillboarding() {
        _isBillboarding = false;
    }
};

}
#endif /*GGAFDX9SPRITEACTORD_H_*/
