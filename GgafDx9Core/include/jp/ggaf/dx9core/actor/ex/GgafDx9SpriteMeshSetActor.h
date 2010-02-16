#ifndef GGAFDX9SPRITEMESHSETACTOR_H_
#define GGAFDX9SPRITEMESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteMeshSetActor : public GgafDx9MeshSetActor {

private:

//    /** �����A�j���t���[���p�J�E���^ */
//    unsigned int _frame_counter_uvflip;


public:
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFliper* _pUvFliper;

//    float _tex_width;
//    float _tex_height;
//    int _tex_col_num;


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


    GgafDx9SpriteMeshSetActor(const char* prm_name,
                          const char* prm_model,
                          GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteMeshSetActor();



//    /**
//     * �A�j���[�V������i�s������ .
//     * �{���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
//     * �Ăяo�����ƂŁAsetUvFlipMethod()�Őݒ肵�����@�ɉ�����<BR>
//     * �A�N�e�B�u�ȃp�^�[���������Ő؂�ւ��܂��B<BR>
//     */
//    void behaveUvFlip();
//
//    /**
//     * ���݂̃A�j���[�V�����p�^�[����ݒ肷�� .
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
//    void setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval = 1);

};

}
#endif /*GGAFDX9SPRITEMESHSETACTOR_H_*/
