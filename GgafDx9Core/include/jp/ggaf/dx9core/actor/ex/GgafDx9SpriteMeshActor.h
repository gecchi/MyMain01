#ifndef GGAFDX9SPRITEMESHACTOR_H_
#define GGAFDX9SPRITEMESHACTOR_H_
namespace GgafDx9Core {

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteMeshActor : public GgafDx9MeshActor {

private:

    /** �����A�j���t���[���p�J�E���^ */
    unsigned int _aniframe_counter;


public:
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;

    float _tex_width;
    float _tex_height;
    int _tex_col_num;


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
    /** ANIMATE_OSCILLATE_LOOP�p�̌��݂̃A�j������ */
    bool _is_reverse_order_in_oscillate_animation_flg;


    GgafDx9SpriteMeshActor(const char* prm_name,
                          const char* prm_model,
                          GgafDx9Checker* prm_pChecker );

    virtual void setUV(float prm_tex_width, float prm_tex_height, int prm_tex_col_num) {
        _tex_width = prm_tex_width;
        _tex_height = prm_tex_height;
        _tex_col_num = prm_tex_col_num;
    }

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() override;

    virtual ~GgafDx9SpriteMeshActor(); //�f�X�g���N�^

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

};

}
#endif /*GGAFDX9SPRITEMESHACTOR_H_*/
