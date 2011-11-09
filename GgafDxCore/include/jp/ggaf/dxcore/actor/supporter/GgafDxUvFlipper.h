#ifndef GGAFDXUVFLIPPER_H_
#define GGAFDXUVFLIPPER_H_
namespace GgafDxCore {

/**
 * �e�N�X�`��UV�t���b�p�[.
 * �e�N�X�`�����p���p���A�j�����@���؂�ւ��鎖���ȒP�ɍs�����߂�
 * �쐬�����N���X�B
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class GgafDxUvFlipper : public GgafCore::GgafObject {
private:

    /** �����A�j���t���[���p�J�E���^ */
    frame _frame_counter_uvflip;


public:

    struct UV {
        float _u;
        float _v;
    };


    GgafDxTexture* _pTexture;

    float _one_ptn_tex_width;
    float _one_ptn_tex_height;
    int _ptn_col_num;
    int _ptn_row_num;
    float _base_u;
    float _base_v;

    /** ���ݕ\�����̃A�j���p�^�[���ԍ�(0�`) */
    int _pattno_uvflip_now;
    /** �ő�A�j���p�^�[���ԍ� */
    int _pattno_uvflip_max;
    /** �A�j���p�^�[���ԍ��̏���ԍ� */
    int _pattno_uvflip_top;
    /** �A�j���p�^�[���ԍ��̉����ԍ� */
    int _pattno_uvflip_bottom;
    /** �p�^�[���ƃp�^�[���̊Ԋu�t���[���� */
    frame _uvflip_interval_frames;
    /** �A�j������ */
    GgafDxUvFlippingMethod _uvflip_method;
    /** FLIP_OSCILLATE_LOOP�p�̌��݂̃A�j������ */
    bool _is_reverse_order_in_oscillate_animation_flg;

    int* _paInt_PtnOffset_Customized;
    int _nPtn_Customized;
    int _cnt_Customized;
    UV* _paUV;


    GgafDxUvFlipper(GgafDxTexture* prm_pTexture);


    virtual ~GgafDxUvFlipper();


    void copyStatesFrom(GgafDxUvFlipper* prm_pUvFlipper_Other) {
        _one_ptn_tex_width             = prm_pUvFlipper_Other->_one_ptn_tex_width;
        _one_ptn_tex_height            = prm_pUvFlipper_Other->_one_ptn_tex_height;
        _ptn_col_num           = prm_pUvFlipper_Other->_ptn_col_num;
        _pattno_uvflip_now     = prm_pUvFlipper_Other->_pattno_uvflip_now;
        _pattno_uvflip_top     = prm_pUvFlipper_Other->_pattno_uvflip_top;
        _pattno_uvflip_bottom  = prm_pUvFlipper_Other->_pattno_uvflip_bottom;
        _pattno_uvflip_max      = prm_pUvFlipper_Other->_pattno_uvflip_max;
        _uvflip_interval_frames = prm_pUvFlipper_Other->_uvflip_interval_frames;
        _uvflip_method         = prm_pUvFlipper_Other->_uvflip_method;
        _is_reverse_order_in_oscillate_animation_flg =
                prm_pUvFlipper_Other->_is_reverse_order_in_oscillate_animation_flg;
    }

    /**
     * �e�N�X�`���̃t���b�s���O�p�^�[���̔ԍ��ɑΉ�����UV���W�̃Y����I�t�Z�b�g���`����B .
     * <pre>
     * ���၄
     *
     *   setRotation(0, 0, 1.0/5, 1.0/4, 3, 10);
     *   setActivePtnNo(5);
     *
     * �����s���̃p�^�[���T�O�}
     *
     *          3 = prm_ptn_col_num
     *     <-------->
     *     1.0/5 = 0.2 = prm_one_ptn_tex_width
     *     <-->
     * (0,0)              (1,0)
     *     +--+--+--+--+--+  ^
     *     | 0| 1| 2|  |  |  | 1.0/4 = 0.25 = prm_one_ptn_tex_height
     *     +--+--+--+--+--+  v
     *     | 3| 4|!5|  |  |
     *     +--+--+--+--+--+
     *     | 6| 7| 8|  |  |
     *     +--+--+--+--+--+
     *     | 9|  |  |  |  |
     *     +--+--+--+--+--+
     * (1,0)              (1,1)
     *  u,v
     *
     * (��"!" �͌��݃A�N�e�B�u�ȃp�^�[���ԍ�)
     *
     * �O�`�X�̓p�^�[���ԍ��ƌĂԂ��ƂƂ���B
     * �p�^�[���ԍ��̕��я��͍��ォ��E�ցA���s���čĂщE�ւ̏��ŌŒ�B
     * �A���A��ƂȂ鍶��̍��W�A���s�܂ł̃p�^�[�����͐ݒ肪�\�B
     * �`�掞�A���_�o�b�t�@�̊e���_��UV���W�ɁA
     * �A�N�e�B�u�ȃp�^�[���̍����UV���W���I�t�Z�b�g�Ƃ��ĉ��Z����邱�Ƃ�z�肵�Ė{���\�b�h���쐬�B
     * ��̐}�̗�ł́A�p�^�[���ԍ�5���A�N�e�B�u�Ȃ̂ł��̏�Ԃ�
     *
     *   float u, v;
     *   getUV(u, v);
     *
     * �����s����ƃp�^�[���ԍ�5�Ԃ̍����UV���W��
     *
     *   u = 0.4, v = 0.25
     *
     * ��������B
     * �{���\�b�h�ɂ��p�^�[���ݒ�́A���� getUV() ���\�b�h�̌��ʂɂ̂݉e����^����B
     * getUV()���g�p���Ȃ��̂ł�΁A�{���\�b�h�ɂ��ݒ�͖��Ӗ��ł���B
     *
     * �y�⑫�z
     * GgafDxUvFlipper �̓t���[�����[�N�̕`�揈���ɖ��ߍ��܂�Ă���A�N�^�[�N���X�����݂���B
     * �����o _pUvFlipper �����݂��Ă���N���X������ł���B
     *
     * �EGgafDxSpriteActor
     *   GgafDxSpriteSetActor
     *   GgafDxBoardActor
     *   GgafDxBoardSetActor
     *   GgafDxPointSpriteActor �ɂ��āE�E�E
     *       �R���X�g���N�^�ňȉ��̏������������s���Ă���B
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW GgafDxUvFlipper(this);
     *       _pUvFlipper->setRotation(�c������, ��������);
     *       _pUvFlipper->setActivePtnNo(0);
     *       _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *       �c������, ���������̓X�v���C�g��`�t�@�C��(.sprx)����擾�����B
     *
     * �EGgafDxSpriteMeshActor
     *   GgafDxSpriteMeshSetActor  �ɂ��āE�E�E
     *       �R���X�g���N�^�ňȉ��̏������������s���Ă���B�K�v�ɉ����ĉ��ʎ����N���X�� setRotation() ���Ď��s�\�B
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW GgafDxUvFlipper(this);
     *       _pUvFlipper->setRotation(1, 1);
     *       _pUvFlipper->setActivePtnNo(0);
     *       _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *
     * �E���̑��̃A�N�^�[�N���X�ɂ��āE�E�E
     *       �N���X������ GgafDxUvFlipper �͑g�ݍ��܂�Ă��Ȃ��B
     *
     * </pre>
     * @param prm_base_u �����U���W(0.0f�`1.0f)
     * @param prm_base_v �����V���W(0.0f�`1.0f)
     * @param prm_one_ptn_tex_width �P�p�^�[���̕�(0.0f�`1.0f)
     * @param prm_one_ptn_tex_height �P�p�^�[���̍���(0.0f�`1.0f)
     * @param prm_ptn_col_num �p�^�[���̃J������(���ɕ��ԃp�^�[����)
     * @param prm_num_of_max_patterns �ő�p�^�[���� (1�`)
     */
    virtual void setRotation(float prm_base_u, float prm_base_v,
                             float prm_one_ptn_tex_width, float prm_one_ptn_tex_height,
                             int prm_ptn_col_num, int prm_num_of_max_patterns);

    /**
     * �e�N�X�`���̃t���b�s���O�p�^�[���̔ԍ��ɑΉ�����UV���W�̃Y����I�t�Z�b�g���`����B .
     * setRotation(float, float, float, float, int, int); <BR>
     * �̊ȈՐݒ�ŁB�����ő��̈����̒l�������v�Z����Ď��s�����B <BR>
     * setRotation(5, 4); �Ƃ����ꍇ�ȉ��̂悤�ɂȂ�B <BR>
     * <pre>
     *     prm_base_u = 0
     *     prm_base_v = 0
     *
     *              5 = prm_ptn_col_num
     *     <-------------->
     *     1.0/5 = 0.2 = prm_one_ptn_tex_width
     *     <-->
     * (0,0)              (1,0)
     *     +--+--+--+--+--+  ^
     *     | 0| 1| 2| 3| 4|  | 1.0/4 = 0.25 = prm_one_ptn_tex_height
     *     +--+--+--+--+--+  v
     *     | 5| 6| 7| 8| 9|
     *     +--+--+--+--+--+
     *     |10|11|12|13|14|
     *     +--+--+--+--+--+
     *     |15|16|17|18|19|
     *     +--+--+--+--+--+
     * (1,0)              (1,1)
     *
     *  prm_pattno_uvflip_max = 19
     *
     *  </pre>
     * @param prm_ptn_col_num �e�N�X�`���c������
     * @param prm_ptn_row_num �e�N�X�`����������
     */
    virtual void setRotation(int prm_ptn_col_num, int prm_ptn_row_num);

    virtual void setBaseUv(float prm_base_u, float prm_base_v) {
        _base_u = prm_base_v;
        _base_v = prm_base_u;
    }

    /**
     * �A�j���[�V������1�t���[�����i�s������ .
     * �{���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
     * �Ăяo�����ƂŁAsetFlipMethod()�Őݒ肵�����@�ɉ�����<BR>
     * �A�N�e�B�u�ȃp�^�[���ԍ�(_pattno_uvflip_now)�������Ő؂�ւ��܂��B<BR>
     */
    virtual void behave();

    /**
     * ���݂̃A�j���[�V�����p�^�[���ԍ�(_pattno_uvflip_now)�ɑΉ����鍶���UV���W���擾����B .
     * ���O�� setRotation() �̌Ăяo���s���Ă��K�v������B
     * @param out_u [out] ���WU
     * @param out_v [out] ���WV
     */
    virtual void getUV(float& out_u, float& out_v);

    virtual void getUV(int prm_pattno_uvflip, float& out_u, float& out_v);

    /**
     * ���݂̃A�j���[�V�����p�^�[����ݒ肷�� .
     * @param prm_pattno_uvflip �A�j���[�V�����p�^�[���ԍ�
     */
    void setActivePtnNo(int prm_pattno_uvflip);

    /**
     * �A�j���[�V�����p�^�[��������̃A�j���[�V�����p�^�[���ԍ�(��ԎႢ�ԍ�)�ɐݒ肷�� .
     */
    void setActivePtnNoToTop();

    /**
     * �A�j���[�V�����p�^�[���͈̔͂𐧌����� .
     * @param prm_top ����̃A�j���[�V�����p�^�[���ԍ�(�Ⴂ���̔ԍ�)
     * @param prm_bottom �����̃A�j���[�V�����p�^�[���ԍ�(�Â����̔ԍ��B�Ⴂ�̔��Ό���ĂȂ��̂�)
     */
    void forcePtnNoRange(int prm_top, int prm_bottom);

    void customizePtnOrder(int prm_aPtnOffset[], int prm_num);

    /**
     * �A�j���[�V�������@��ݒ肷�� .
     * <pre>
     * ���၄forcePtnNoRange(0,5) ���ݒ�ς݂Ƃ����ꍇ�B
     * FLIP_ORDER_LOOP     : 0,1,2,3,4,5,0,1,2,3,4,5,...
     * FLIP_REVERSE_LOOP   : 5,4,3,2,1,0,5,4,3,2,1,0,5,4...
     * FLIP_ORDER_NOLOOP   : 0,1,2,3,4,5,5,5,5,5,5,5...
     * FLIP_REVERSE_NOLOOP : 5,4,3,2,1,0,0,0,0,0,0...
     * FLIP_OSCILLATE_LOOP : 0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
     * NOT_ANIMATED        : 3,3,3,3,3,3,3... �i�������Ȃ��j
     * </pre>
     * @param prm_method �A�j���[�V�������@�萔
     * @param prm_interval �A�j���[�V�����Ԋu�t���[���idefault=1)
     */
    void setFlipMethod(GgafDxUvFlippingMethod prm_method, int prm_interval = 1);

};

}
#endif /*GGAFDXSPRITEMESHACTOR_H_*/