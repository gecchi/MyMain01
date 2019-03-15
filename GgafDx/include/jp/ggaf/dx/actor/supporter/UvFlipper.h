#ifndef GGAF_DX_UVFLIPPER_H_
#define GGAF_DX_UVFLIPPER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafDx {

/**
 * �e�N�X�`��UV�t���b�p�[.
 * �e�N�X�`�����p���p���A�j�����@���؂�ւ��鎖���ȒP�ɍs�����߂�
 * �쐬�����N���X�B
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class UvFlipper : public GgafCore::Object {
private:

    /** �����A�j���t���[���p�J�E���^ */
    frame _frame_counter_uvflip;

public:

    struct UV {
        float _u;
        float _v;
    };

    /** [r]�A�j���p�^�[���e�N�X�`�� */
    Texture* const _pTexture;
    /** [r/w]�A�j���p�^�[��0�Ԃ̍���U���W(0.0�`1.0) */
    float _base_u;
    /** [r/w]�A�j���p�^�[��0�Ԃ̍���V���W(0.0�`1.0) */
    float _base_v;
    /** [r/w]�P�̃A�j���p�^�[���̕�(0.0�`1.0) */
    float _one_ptn_tex_width;
    /** [r/w]�P�̃A�j���p�^�[���̍���(0.0�`1.0) */
    float _one_ptn_tex_height;
    /** [r]�A�j���p�^�[���̃J������(���ɕ��ԃp�^�[����) */
    int _ptn_col_num;
    /** [r]�A�j���p�^�[���̍s��(�c�ɕ��ԃp�^�[����) */
    int _ptn_row_num;

    /** [r/w]���ݕ\�����̃A�j���p�^�[���ԍ�(0�`) */
    int _pattno_uvflip_now;
    /** [r/w]�ő�A�j���p�^�[���ԍ� */
    int _pattno_uvflip_max;
    /** [r/w]�A�j���p�^�[���ԍ��̏���ԍ� */
    int _pattno_uvflip_top;
    /** [r/w]�A�j���p�^�[���ԍ��̉����ԍ� */
    int _pattno_uvflip_bottom;
    /** [r/w]�p�^�[���ƃp�^�[���̊Ԋu�t���[���� */
    frame _uvflip_interval_frames;
    /** [r]�A�j������ */
    UvFlippingMethod _uvflip_method;
    /** [r]FLIP_OSCILLATE_LOOP�p�̌��݂̃A�j������ */
    bool _is_reverse_order_in_oscillate_animation_flg;

    int* _pa_ptn_offset_customized;
    int _ptn_customized;
    int _cnt_customized;
    /** [r]����UV�z�� */
    UV* _paUV;

public:
    explicit UvFlipper(Texture* prm_pTexture);

    virtual ~UvFlipper();

    void copyStatesFrom(UvFlipper* prm_pUvFlipper_other) {
        _one_ptn_tex_width      = prm_pUvFlipper_other->_one_ptn_tex_width;
        _one_ptn_tex_height     = prm_pUvFlipper_other->_one_ptn_tex_height;
        _ptn_col_num            = prm_pUvFlipper_other->_ptn_col_num;
        _pattno_uvflip_now      = prm_pUvFlipper_other->_pattno_uvflip_now;
        _pattno_uvflip_top      = prm_pUvFlipper_other->_pattno_uvflip_top;
        _pattno_uvflip_bottom   = prm_pUvFlipper_other->_pattno_uvflip_bottom;
        _pattno_uvflip_max      = prm_pUvFlipper_other->_pattno_uvflip_max;
        _uvflip_interval_frames = prm_pUvFlipper_other->_uvflip_interval_frames;
        _uvflip_method          = prm_pUvFlipper_other->_uvflip_method;
        _is_reverse_order_in_oscillate_animation_flg =
                prm_pUvFlipper_other->_is_reverse_order_in_oscillate_animation_flg;
    }

    /**
     * �e�N�X�`���̃t���b�s���O�p�^�[���̔ԍ��ɑΉ�����UV���W�̃Y����I�t�Z�b�g���`����B .
     * <pre>
     * ���၄
     *
     *   _pUvFlipper->locatePatternNo(0, 0, 1.0/5, 1.0/4, 3, 10);
     *   _pUvFlipper->setActivePtn(5);
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
     * �O�`�X�̓p�^�[���ԍ��ƌĂԂ��ƂƂ���B(prm_num_of_max_patterns �Ŕԍ��������܂�)
     * �p�^�[���ԍ��̕��я��͍��ォ��E�ցA���s���čĂщE�ւ̏��ŌŒ�B
     * �A���A��ƂȂ鍶��̍��W�A���s�܂ł̃p�^�[�����͐ݒ肪�\�B
     * �`�掞�A���_�o�b�t�@�̊e���_��UV���W�ɁA
     * �A�N�e�B�u�ȃp�^�[���̍����UV���W���I�t�Z�b�g�Ƃ��ĉ��Z����邱�Ƃ�z�肵�Ė{���\�b�h���쐬�B
     * ��̐}�̗�ł́A�p�^�[���ԍ�5���A�N�e�B�u�Ȃ̂ł��̏�Ԃ�
     *
     *   float u, v;
     *   _pUvFlipper->getUV(u, v);
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
     * UvFlipper �̓t���[�����[�N�̕`�揈���ɖ��ߍ��܂�Ă���A�N�^�[�N���X�����݂���B
     * �����o _pUvFlipper �����݂��Ă���N���X������ł���B
     *
     * �ESpriteActor
     *   SpriteSetActor
     *   BoardActor
     *   BoardSetActor
     *   PointSpriteActor �ɂ��āE�E�E
     *       �R���X�g���N�^�ňȉ��̏������������s���Ă���B
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW UvFlipper(this);
     *       _pUvFlipper->locatePatternNo(�c������, ��������);
     *       _pUvFlipper->setActivePtn(0);
     *       _pUvFlipper->exec(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *       �c������, ���������̓X�v���C�g��`�t�@�C��(.sprx)����擾�����B
     *
     * �ESpriteMeshActor
     *   SpriteMeshSetActor  �ɂ��āE�E�E
     *       �R���X�g���N�^�ňȉ��̏������������s���Ă���B�K�v�ɉ����ĉ��ʎ����N���X�� locatePatternNo() ���Ď��s�\�B
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW UvFlipper(this);
     *       _pUvFlipper->locatePatternNo(1, 1);
     *       _pUvFlipper->setActivePtn(0);
     *       _pUvFlipper->exec(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *
     * �E���̑��̃A�N�^�[�N���X�ɂ��āE�E�E
     *       �N���X������ UvFlipper �͑g�ݍ��܂�Ă��Ȃ��B
     *
     * </pre>
     * @param prm_base_u �����U���W(0.0f�`1.0f)
     * @param prm_base_v �����V���W(0.0f�`1.0f)
     * @param prm_one_ptn_tex_width �P�p�^�[���̕�(0.0f�`1.0f)
     * @param prm_one_ptn_tex_height �P�p�^�[���̍���(0.0f�`1.0f)
     * @param prm_ptn_col_num �p�^�[���̃J������(���ɕ��ԃp�^�[����)
     * @param prm_num_of_max_patterns �ő�p�^�[���� (1�`)
     */
    virtual void locatePatternNo(float prm_base_u, float prm_base_v,
                                 float prm_one_ptn_tex_width, float prm_one_ptn_tex_height,
                                 int prm_ptn_col_num, int prm_num_of_max_patterns);

    /**
     * �e�N�X�`���̃t���b�s���O�p�^�[���̔ԍ��ɑΉ�����UV���W�̃Y����I�t�Z�b�g���`����B .
     * locatePatternNo(float, float, float, float, int, int); <BR>
     * �̊ȈՐݒ�ŁB�����ő��̈����̒l�������v�Z����Ď��s�����B <BR>
     * locatePatternNo(5, 4); �Ƃ����ꍇ�ȉ��̂悤�ɂȂ�B <BR>
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
     *  prm_pattno_uvflip_max = 20 �͈����ɖ������A���������v�Z
     *
     *  </pre>
     * @param prm_ptn_col_num �e�N�X�`���c������
     * @param prm_ptn_row_num �e�N�X�`����������
     */
    virtual void locatePatternNo(int prm_ptn_col_num, int prm_ptn_row_num);

    void remapPatternNoUv(int prm_ptn_num, ...);

    virtual void setBaseUv(float prm_base_u, float prm_base_v) {
        _base_u = prm_base_u;
        _base_v = prm_base_v;
    }

    /**
     * �A�j���[�V������1�t���[�����i�s������ .
     * �{���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
     * �Ăяo�����ƂŁAexec()�Őݒ肵�����@�ɉ�����<BR>
     * �A�N�e�B�u�ȃp�^�[���ԍ�(_pattno_uvflip_now)�������Ő؂�ւ��܂��B<BR>
     */
    virtual void behave();

    /**
     * ���݂̃A�j���[�V�����p�^�[���ԍ�(_pattno_uvflip_now)�ɑΉ����鍶���UV���W���擾����B .
     * ���O�� locatePatternNo() �̌Ăяo���s���Ă��K�v������B
     * @param out_u[out] ���WU
     * @param out_v[out] ���WV
     */
    virtual void getUV(float& out_u, float& out_v);

    /**
     * �����̃A�j���[�V�����p�^�[���ԍ��ɑΉ����鍶���UV���W���擾����B .
     * @param prm_pattno_uvflip �A�j���[�V�����p�^�[���ԍ�
     * @param out_u[out] �A�j���[�V�����p�^�[���ԍ��̍��WU
     * @param out_v[out] �A�j���[�V�����p�^�[���ԍ����WV
     */
    virtual void getUV(int prm_pattno_uvflip, float& out_u, float& out_v);

    /**
     * ���݂̃A�j���[�V�����p�^�[����ݒ肷�� .
     * setFlipPtnRange(int, int) �͈̔͊O�ł����Ȃ��ݒ�o���܂��B
     * @param prm_pattno_uvflip �A�j���[�V�����p�^�[���ԍ�
     */
    void setActivePtn(int prm_pattno_uvflip);

    /**
     * ���݂̃A�j���[�V�����p�^�[�����擾���� .
     * @return ���݂̃A�j���[�V�����p�^�[���ԍ�
     */
    inline int getActivePtn() {
        return _pattno_uvflip_now;
    }

    /**
     * �t���b�v�A�j���[�V�����p�^�[���̏���̉����̃p�^�[���ԍ���ݒ� .
     * �����܂ŁA�t���b�v�̏�������ł���A���݂̃p�^�[���ԍ��𐧌�������̂ł͂���܂���B<BR>
     * setActivePtn(int) �Ŕ͈͊O�Ńp�^�[���ԍ������Ȃ��ݒ�o���܂��B
     * @param prm_top ����̃A�j���[�V�����p�^�[���ԍ�(�Ⴂ���̔ԍ�)
     * @param prm_bottom �����̃A�j���[�V�����p�^�[���ԍ�(�Â����̔ԍ��B�Ⴂ�ԍ��̔��Ό���ČÂ��ԍ��Ȃ̂��낤���G)
     */
    void setFlipPtnRange(int prm_top, int prm_bottom);

    /**
     * ����p�^�[���ԍ��i�ł��Ⴂ�ԍ��j���擾 .
     */
    int getTopPtnno() {
        return _pattno_uvflip_top;
    }

    /**
     * �����p�^�[���ԍ��i�ł��Â��ԍ��j���擾 .
     */
    int getBottomPtnno() {
        return _pattno_uvflip_bottom;
    }

    /**
     * �A�j���[�V�����p�^�[��������p�^�[���ԍ��i�ł��Ⴂ�ԍ��j�ɐݒ肷�� .
     */
    void setActivePtnToTop() {
        setActivePtn(_pattno_uvflip_top);
    }

    /**
     * �A�j���[�V�����p�^�[���������p�^�[���ԍ��i�ł��Â��ԍ��j�ɐݒ肷�� .
     */
    void setActivePtnToBottom() {
        setActivePtn(_pattno_uvflip_bottom);
    }

    /**
     * ���݂̃A�j���[�V�����p�^�[���ԍ�������p�^�[���ԍ������(����)�ԍ����Őݒ肷�� .
     * @param prm_pattno_uvflip_from_top ����p�^�[���ԍ�����̃p�^�[���ԍ���
     */
    void setActivePtnFromTop(int prm_pattno_uvflip_from_top) {
        setActivePtn(_pattno_uvflip_top + prm_pattno_uvflip_from_top);
    }

    /**
     * FLIP_CUSTOMIZED_LOOP�AFLIP_CUSTOMIZED_NOLOOP���̃p�^�[�������`�BTODO:���e�X�g�B .
     * @param prm_aPtnOffset
     * @param prm_num
     */
    void customizePtnOrder(int prm_aPtnOffset[], int prm_num);

    /**
     * �A�j���[�V�������@��ݒ肷�� .
     * <pre>
     * ���၄setFlipPtnRange(0,5) ���ݒ�ς݂Ƃ����ꍇ�B
     * FLIP_ORDER_LOOP     : 0,1,2,3,4,5,0,1,2,3,4,5,...
     * FLIP_REVERSE_LOOP   : 5,4,3,2,1,0,5,4,3,2,1,0,5,4...
     * FLIP_ORDER_NOLOOP   : 0,1,2,3,4,5,5,5,5,5,5,5...
     * FLIP_REVERSE_NOLOOP : 5,4,3,2,1,0,0,0,0,0,0...
     * FLIP_OSCILLATE_LOOP : 0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
     * NOT_ANIMATED        : 3,3,3,3,3,3,3... �i�������Ȃ��j
     *
     * �����傱���Ɠ���Ȏg������
     * �y��P�z
     * setActivePtn(0);
     * setFlipPtnRange(3,5);
     * exec(FLIP_ORDER_LOOP); �Ƃ����ꍇ�A
     * �p�^�[���ԍ�: 0,1,2,3,4,5,3,4,5,3,4,5,...
     *
     * �y��Q�z
     * setActivePtn(5);
     * setFlipPtnRange(0,3);
     * exec(FLIP_REVERSE_LOOP); �Ƃ����ꍇ�A
     * �p�^�[���ԍ�: 5,4,3,2,1,0,3,2,1,0,3,2,1,0,...
     *
     * </pre>
     * @param prm_method �t���b�v���̕��@
     * @param prm_interval �t���b�v�Ԋu�t���[���idefault=1)
     */
    void exec(UvFlippingMethod prm_method, int prm_interval = 1);

    /**
     * �A�j���[�V�������~ .
     */
    void stop() {
        exec(NOT_ANIMATED);
    }

    /**
     * �A�j���[�V�������ł��邩 .
     * @return true : �A�j���[�V������ / false : �A�j���[�V�������ł͂Ȃ�
     */
    bool isFlipping() {
        return _uvflip_method == NOT_ANIMATED ? false : true;
    }

};

}
#endif /*GGAF_DX_SPRITEMESHACTOR_H_*/