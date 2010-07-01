#ifndef GGAFDX9UVFLIPPER_H_
#define GGAFDX9UVFLIPPER_H_
namespace GgafDx9Core {

/**
 * �e�N�X�`��UV�t���b�p�[.
 * �e�N�X�`�����p���p���A�j�����@���؂�ւ��鎖���ȒP�ɍs�����߂�
 * �쐬�����N���X�B
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class GgafDx9UvFlipper : public GgafCore::GgafObject {
private:

    /** �����A�j���t���[���p�J�E���^ */
    DWORD _frame_counter_uvflip;


public:
    GgafDx9GeometricActor* _pActor;

    float _tex_width;
    float _tex_height;
    int _tex_col_num;

    /** ���ݕ\�����̃A�j���p�^�[���ԍ�(0�`) */
    int _pattno_uvflip_now;

    /** �A�j���p�^�[���ԍ��̏���ԍ� */
    int _pattno_uvflip_top;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ� */
    int _pattno_uvflip_bottom;
    /** �p�^�[���ƃp�^�[���̊Ԋu�t���[���� */
    DWORD _frame_uvflip_interval;
    /** �A�j������ */
    GgafDx9UvFlipMethod _uvflip_method;
    /** FLIP_OSCILLATE_LOOP�p�̌��݂̃A�j������ */
    bool _is_reverse_order_in_oscillate_animation_flg;

    int* _paInt_PtnOffset_Customized;
    int _nPtn_Customized;
    int _cnt_Customized;
    GgafDx9UvFlipper(GgafDx9GeometricActor* prm_pActor);


    virtual ~GgafDx9UvFlipper();


    void copyStatesFrom(GgafDx9UvFlipper* prm_pUvFlipper_Other) {
        _tex_width             = prm_pUvFlipper_Other->_tex_width;
        _tex_height            = prm_pUvFlipper_Other->_tex_height;
        _tex_col_num           = prm_pUvFlipper_Other->_tex_col_num;
        _pattno_uvflip_now     = prm_pUvFlipper_Other->_pattno_uvflip_now;
        _pattno_uvflip_top     = prm_pUvFlipper_Other->_pattno_uvflip_top;
        _pattno_uvflip_bottom  = prm_pUvFlipper_Other->_pattno_uvflip_bottom;
        _frame_uvflip_interval = prm_pUvFlipper_Other->_frame_uvflip_interval;
        _uvflip_method         = prm_pUvFlipper_Other->_uvflip_method;
        _is_reverse_order_in_oscillate_animation_flg =
                prm_pUvFlipper_Other->_is_reverse_order_in_oscillate_animation_flg;
    }

    /**
     * �e�N�X�`���̃t���b�s���O�p�^�[���̔ԍ��ɑΉ�����UV���W�̃Y����I�t�Z�b�g���`����B .
     * <pre>
     * ���၄
     *
     *   setTextureUvRotation(3, 1.0/5, 1.0/4);
     *   forcePtnNoRange(0,9);
     *   setPtnNo(5);
     *
     * �����s���̃p�^�[���T�O�}
     *
     *          3 = prm_tex_col_num
     *     <-------->
     *     0.2 = prm_tex_width
     *     <-->
     * (0,0)              (1,0)
     *     +--+--+--+--+--+  ^
     *     | 0| 1| 2|  |  |  | 0.25 = prm_tex_height
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
     * GgafDx9UvFlipper �̓t���[�����[�N�̕`�揈���ɖ��ߍ��܂�Ă���A�N�^�[�N���X�����݂���B
     * �����o _pUvFlipper �����݂��Ă���N���X������ł���B
     * �`�掞�ɂǂ̂悤�ɍ�p���Ă��邩�����Ƀ������c���B
     *
     * �EGgafDx9SpriteActor
     *   GgafDx9SpriteSetActor
     *   GgafDx9BoardActor
     *   GgafDx9BoardSetActor
     *   GgafDx9PointSpriteActor �ɂ��āE�E�E
     *       �`�掞�A���݃p�^�[���ԍ�(_pattno_uvflip_now) �̂ݎQ�Ƃ���Ă���BgetUV() �͓����Ŏg�p���Ă��Ȃ��B
     *       ���������āAsetTextureUvRotation() �̌Ăяo���̓t���[�����[�N�̕`�揈���ł͖��Ӗ��B
     *       �A�j���[�V������UV���W�̃I�t�Z�b�g���́A��`X�t�@�C��(�g���q.sprx)����ǂݎ���āA���f���ŕێ����Ă���B
     *       ��L�A�N�^�[�����҂� _pattno_uvflip_now �̑��삾���ŗǂ��B�i�����Ď����҂͉��j
     *       �R���X�g���N�^�ňȉ��̏������������s���Ă���B
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW GgafDx9UvFlipper(this);
     *       _pUvFlipper->forcePtnNoRange(0, �ő�A�j���[�V�����p�^�[���ԍ�);
     *       _pUvFlipper->setPtnNo(0);
     *       _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *
     * �EGgafDx9SpriteMeshActor
     *   GgafDx9SpriteMeshSetActor  �ɂ��āE�E�E
     *       ������ getUV() ���g�p���Ă���B����� setTextureUvRotation() �ɂ��ݒ肪�K�{�B
     *       �`�掞���_�o�b�t�@��UV���W�� getUV() �œ���UV�I�t�Z�b�g�l���V�F�[�_�[�֓n�����Z���Ă���B
     *       �������wsetTextureUvRotation() �͓����Ŏ��s���Ă��Ȃ��x���߁A�p���N���X���̏��������ȂǂŁA
     *       ���O�ɂP��� setTextureUvRotation() ���Ăяo���āA�p�^�[���̔ԍ���UV���W�i�I�t�Z�b�g�l�j��
     *       �Ή����`���Ă��������O��ƂȂ���ɂȂ��Ă���BUV�؂�ւ����Ȃ��̂ł���Εʂ̌Ă΂Ȃ��Ă����v�B
     *       �R���X�g���N�^�ňȉ��̏������������s���Ă���B�K�v�ɉ����ĉ��ʎ����N���X�� setTextureUvRotation() �����s���Ƃ����d�g�݁B
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW GgafDx9UvFlipper(this);
     *       _pUvFlipper->forcePtnNoRange(0, �Z�o�����ő�A�j���[�V�����p�^�[���ԍ�);
     *       _pUvFlipper->setPtnNo(0);
     *       _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *
     * �E���̑��̃A�N�^�[�N���X�ɂ��āE�E�E
     *       �N���X������ GgafDx9UvFlipper �͑g�ݍ��܂�Ă��Ȃ��B
     *
     * �y�܂Ƃ߁z
     * �v�� GgafDx9SpriteMeshActor, GgafDx9SpriteSetMeshActor ���p����
     * setTextureUvRotation() �̎��O���s���K�v�A���͕s�v�B
     * �iTODO:�{�N���X�̎��O�Ăяo�����N���X�̎d�g�݂ŋ���������d�g�݂͌��ݖ����B�������肽���B���A�Ƃ肠�������͎����ŋC��t����j
     * </pre>
     * @param prm_tex_col_num �p�^�[���̃J�������BUV���W�����s���邽�߂Ɏg�p�����(���R��)
     * @param prm_tex_width �P�p�^�[���̕�(0.0f�`1.0f)
     * @param prm_tex_height �P�p�^�[���̍���(0.0f�`1.0f)
     */
    virtual void setTextureUvRotation(int prm_tex_col_num, float prm_tex_width, float prm_tex_height);

    /**
     * �A�j���[�V������1�t���[�����i�s������ .
     * �{���\�b�h���AprocessBehavior() ���Ŗ��t���[���Ăяo���K�v������܂��B<BR>
     * �Ăяo�����ƂŁAsetFlipMethod()�Őݒ肵�����@�ɉ�����<BR>
     * �A�N�e�B�u�ȃp�^�[���ԍ�(_pattno_uvflip_now)�������Ő؂�ւ��܂��B<BR>
     */
    virtual void behave();

    /**
     * ���݂̃A�j���[�V�����p�^�[���ԍ�(_pattno_uvflip_now)�ɑΉ�����UV���W���擾����B .
     * ���O�� setTextureUvRotation() �̌Ăяo���s���Ă��K�v������B
     * @param out_u [out] ���WU
     * @param out_v [out] ���WV
     */
    virtual void getUV(float& out_u, float& out_v);


    /**
     * ���݂̃A�j���[�V�����p�^�[����ݒ肷�� .
     * @param prm_pattno_uvflip �A�j���[�V�����p�^�[���ԍ�
     */
    void setPtnNo(int prm_pattno_uvflip);

    /**
     * �A�j���[�V�����p�^�[��������̃A�j���[�V�����p�^�[���ԍ�(��ԎႢ�ԍ�)�ɐݒ肷�� .
     */
    void setPtnNoToTop();

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
    void setFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval = 1);

};

}
#endif /*GGAFDX9SPRITEMESHACTOR_H_*/
