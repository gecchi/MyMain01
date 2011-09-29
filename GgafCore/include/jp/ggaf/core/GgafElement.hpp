#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define GGAF_NODE GgafCore::GgafNode<T>
/** ���ʒx������t���[���� */
#define GGAF_SAYONARA_DELAY (60*15)
//GGAF_SAYONARA_DELAY�͑SElement���ʂ̉���x���t���[�����ŁA
//���߂ɐݒ肵�Ȃ��ƁA���낢��s�s���������B
//��������Ȃ��Q�Ƃ��\�Ƃ��邽�߂̎d�g�݂ŁA
//�Ⴆ�΁A���Ō�̔���SE���ŁA3D���ʂ̂���SE���������W��񂪂��΂炭�K�v�Ƃ��A
//���Ō�̏��ŃA�N�^�[�ɑ�����q�A�N�^�[�̔��˒e���A�e�A�N�^�[�̍��W���Q�Ƃ��Ă���ȂǁA
//���ł��Ă��A���΂炭�͎c�������Ȃ���΂����Ȃ��ꍇ������B
//��{�I�ɁA���Ŋm�聨���S�ɏ����܂ł̃t���[���̍ő�t���[�����w�肷��B
//GGAF_SAYONARA_DELAY��Z�߂ɐݒ肷��ƁA���݂�10�b(60*15)
//���Ō�̎q�̔��˒e�ɂ��ẮA�c���ꂽ���˒e���ˑR������̂ŏ����s���R�B�Ƃ������x�Ŗ��͂Ȃ��B
//�������ASE��3D���ʂ́A�G���[�ɂȂ邽�߁ASE�Đ����Ԃ̍ő�t���[������ݒ肵�Ȃ���΂����Ȃ��B
//�Ⴆ�Δ���SE���P��������悤�ȕ�����ł��g�p�������ꍇ�́A�ő��1��(60*60)��ݒ肵�Ȃ���΂Ȃ�Ȃ��B



/**
 * GgafNode�ɁA�l�X�ȏ�ԑJ�ڊǗ��i�^�X�N�V�X�e���j��ǉ��B .
 * ���t���[���A�_(GgafGod)�͂��̐�(GgafUniverse)�ɁA���̃��\�b�h���ŌĂяo���d�g�݂ɂȂ��Ă���B���̐�(GgafUniverse)���{template���������Ă���B<BR>
 * nextFrame() > behave() > settleBehavior() > judge() > [preDraw() > draw() > afterDraw()] > doFinally() <BR>
 * ��L�̓��AnextFrame() doFinally() �͖��t���[�����s�����B<BR>
 * behave() settleBehavior() judge() �͊�����ԃt���O(_is_active_flg)�� true�A���A�ꎞ��~�t���O(_was_paused_flg)�� false �̏ꍇ���s�����B<BR>
 * preDraw() draw() afterDraw() �́A���t���[���܂ł̎c���Ԃɗ]�T������ꍇ���s�����B<BR>
 * ���t���[���܂ł̎c���Ԃɗ]�T�������ꍇ�A�_�͂��̂R���\�b�h���X�L�b�v���邪�AMAX_SKIP_FRAME �t���[���ɂP��͎��s����B<BR>
 * ��L�� nextFrame() �` doFinally() �̒��ڃI�[�o�[���C�h�͔񐄏��B�I�[�o�[���C�h�p�Ɋe���\�b�h�ŃR�[���o�b�N����鏃�����z�֐�(processXxxxxx()) ��p�ӂ��Ă���B<BR>
 * initialize() �́A��L�� nextFrame() �` doFinally() �����ꂩ���Ăяo���O�ɃC���X�^���X���ƂɂP�񂾂��Ă΂��d�g�݂ɂȂ��Ă���B<BR>
 * �A���A�����t���O(_can_live_flg)��false�̏ꍇ�idelete�����j�́AnextFrame() �` doFinally() �͑S�Ď��s����Ȃ��B<BR>
 * (�����N���X����GgafFactor)
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

private:

protected:

public:
    /** [r]�_�ւ̋ߓ� */
    GgafGod* _pGod;
    /** [r]initialize���s��ꂽ�ǂ����̃t���O(true=�s��ꂽ) */
    bool _was_initialize_flg;

    /** [r]�m�[�h���a��(addSub���ꂽ�j������̃t���[�������v(�A���A_was_paused_flg==true ���͉��Z���ꖳ��) */
    frame _frame_of_life;
    /** [r]�m�[�h���a��(addSub���ꂽ�j������A�U�������t���[�������v(�A���A_was_paused_flg==true ���� _is_active_flg==false ���͉��Z���ꖳ��) */
    frame _frame_of_behaving;
    /** [r]�m�[�h�������J�n(onActive())������̐U�������t���[�������v(�A���A_was_paused_flg==true ���� _is_active_flg==false ���͉��Z���ꖳ��) */
    frame _frame_of_behaving_since_onActive;
    /** [r]���΃t���[���v�Z�p */
    frame _frameEnd;
    /** [r]�m�[�h�����t���O */
    bool _is_active_flg;
    /** [r]�ꎞ��~�t���O */
    bool _was_paused_flg;
    /** [r]�m�[�h�����t���O */
    bool _can_live_flg;

    /** [r]���t���[���̃m�[�h�����t���O�A���t���[���̃t���[�����Z�� _is_active_flg �ɔ��f����� */
//    bool _is_active_flg_in_next_frame;
    /** [r]���t���[���̈ꎞ��~�t���O�A���t���[���̃t���[�����Z�� _was_paused_flg �ɔ��f����� */
    bool _was_paused_flg_in_next_frame;
    /** [r]���t���[���̈ꎞ��\���t���O�A���t���[���̃t���[�����Z�� _can_live_flg �ɔ��f�����  */
    //bool _can_live_flg_in_next_frame;

    /** [r]�I���t���O */
    bool _will_end_after_flg;
    /** [r]�I������\��� _frame_of_life */
    frame _frame_of_life_when_end;


    /** [r]���ƂŊ����\��t���O */
    bool _will_activate_after_flg;
    /** [r]�����J�n����\��� _frame_of_life */
    frame _frame_of_life_when_activation;

    /** [r]���ƂŔ񊈓��\��t���O */
    bool _will_inactivate_after_flg;
    /** [r]�����I������\��� _frame_of_life */
    frame _frame_of_life_when_inactivation;

    /** [r]�m�[�h�������ɐ؂�ւ����(_is_active_flg �� false �� true)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _on_change_to_active_flg;
    /** [r]�m�[�h����~�ɐ؂�ւ����(_is_active_flg �� true �� false)�u�ԂɂP�t���[�������Z�b�g�����t���O */
    bool _on_change_to_inactive_flg;

    /** [r]�擪�m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h���擪�m�[�h�Ɉړ����� */
    bool _will_mv_first_in_next_frame_flg;
    /** [r]�����m�[�h�Ɉړ��\��t���O�A���t���[���̃t���[�����Z���ɁA���m�[�h�������m�[�h�Ɉړ����� */
    bool _will_mv_last_in_next_frame_flg;

    bool _is_already_reset;

    GgafProgress* _pProg;

    /**
     * �R���X�g���N�^
     * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
     */
    GgafElement(const char* prm_name);

    /**
     * �f�X�g���N�^�B���c���[�m�[�h���������B .
     */
    virtual ~GgafElement();

    /**
     * �|��(���c���[) .
     * �_���������Ԃɗ]�T���ł��Ƃ����ɁA�_���Ăт����B<BR>
     * �z���m�[�h�̒��Ƀm�[�h�����t���O(_can_live_flg)�� false �ɂȂ��Ă���m�[�h������� prm_num_cleaning ���� delete ����B<BR>
     * @param prm_num_cleaning �������I�u�W�F�N�g��
     */
    virtual void clean(int prm_num_cleaning);

    /**
     * �m�[�h��������(�P��) .
     * �C���X�^���X������A���ꂩ���Ăяo�����O�ɁA�ŏ��ɕK���P�񂾂��Ăяo�����B<BR>
     * �⑫�Finitialize()���Ăяo���ꂽ��Areset() ���Ăяo����܂��B
     */
    virtual void initialize() = 0;

    /**
     * �m�[�h�̃t���[�������Z�ƁA�t���[���J�n�ɂ������Ă̂��낢��ȏ�������(���c���[) .
     * �l�X�ȏ�ԃt���O�̍X�V����ɍs�� <BR>
     * _is_active_flg_in_next_frame _was_paused_flg_in_next_frame _can_live_flg_in_next_frame ��<BR>
     * _is_active_flg _was_paused_flg _can_live_flg �ɔ��f�i�R�s�[�j����B<BR>
     * �܂��A_will_mv_first_in_next_frame_flg, _will_mv_last_in_next_frame_flg �� true �̏ꍇ�́A<BR>
     * ���ꂼ��A���m�[�h�̐擪�m�[�h�ւ̈ړ��A�����m�[�h�ւ̈ړ����������s�����B<BR>
     * ���̌�A�z���m�[�h�S�Ă� nextFrame() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� nextFrame() ���s��A���� behave() �����s���邱�ƂɂȂ�B<BR>
     * ���̂悤�ȍ\���̏ꍇ�A���s���͇@�`�L�̏����ƂȂ�B<BR>
     * �m�[�h�ԂŎQ�Ɗ֌W������ꍇ�́A���ӂ��K�v�B<BR>
     * <pre>
     * (�o)�̇@�o��(�o)
     *         ��
     * (�d)�̇A�`�̇E�a�̇J�b�̇K�c�̇L�d��(�`)
     *         ��    ����������������������������
     *         ��                              ��
     * (�g)�̇B�e�̇C�f�̇D�g��(�e)    (�k)�̇F�h�̇G�i�̇H�j�̇I�k��(�h)
     *
     * ���T�u�����݂���ΐ�Ɏ��s�A���݂��Ȃ���Ύ�(��)�����s�B
     * <pre>
     * ���\�b�h�����Ɂw(���c���[)�x�ƋL�q����Ă���ꍇ�́A�S�ď�L�̏����Ŏ��s�����B
     */
    virtual void nextFrame();

    /**
     * �m�[�h�̃t���[�����̐U�镑������(���c���[) .
     * ���̏����ł́A�S�m�[�h���W�ړ��������s�����ƂƂ���B<BR>
     * ���s����邽�߂̃t���O�̏����́A<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i _is_active_flg && !_was_paused_flg && _can_live_flg �j�̏ꍇ <BR>
     * behave() �� ���z�֐� processBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� behave() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processBehavior() ���I�[�o�[���C�h���ċ�̓I�ȍ��W�ړ����W�b�N����������B <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� behave() ���s��A���� settleBehavior() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void behave();

    /**
     * �񊈓����������ɐ؂�ւ�������̏���(�P��) .
     * �񊈓���Ԃ��犈����Ԃɕω������Ƃ��ɁA behave() �����O�ɂP��R�[���o�b�N�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     * ���R�[�������^�C�~���O�ڍׁ�
     * �@�񊈓����������ɐ؂�ւ������
     * nextFrame() �������A�O�t���[���̏�ԃt���O�u�񊈓���ԁv�ŁA���t���[���̏�ԃt���O���u������ԁv�ƂȂ�ꍇ�A
     * nextFrame() ���ŁA���t���[���̏�ԃt���O���u������ԁv�ɂ��A�t���[�����Z������ �R�[���o�b�N
     * �A������A�P�t���[���ڂ̎�
     * ���ۂɂ͑��݂��Ȃ��O�t���[��(0�t���[����)�̏�ԃt���O���A������̏����l�Łu�񊈓���ԁv�Ƃ��Ă���ׁB
     * ������A���߂� nextFrame() ���������ꍇ�AnextFrame() ���ŃR�[���o�b�N����邱�ƂɂȂ�B
     */
    virtual void onActive() {
    }

    /**
     * �������񊈓����ɐ؂�ւ�������̏���(�P��) .
     * ������Ԃ���񊈓���Ԃɕω������Ƃ��ɂP��R�[���o�b�N�����B<BR>
     * �Ăяo�����^�C�~���O�̓t���[�����Z����ł���B�ʏ� behave() �����O�Ɏ��s�����B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h����B<BR>
     */
    virtual void onInactive() {
    }

    /**
     * �m�[�h�̃t���[�����̐U�镑�����㏈��(���c���[) .
     * ���̏����ł́A�S�m�[�h���W�ړ����������Ă��邱�Ƃ��ۏ؂��ꂽ��̏������s�����Ƃ���݌v�B<BR>
     * �X�V�������������W��񂩂�A����ɔ��������̗l�X�ȃX�e�[�^�X���̍X�V�����������ōs������ړI�Ƃ���<BR>
     * ���s����邽�߂̃t���O�̏����́Abehave()�Ɠ������A�����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g�B<BR>
     * �܂� ( _is_active_flg && !_was_paused_flg && _can_live_flg )�̏ꍇ�ł���B <BR>
     * settleBehavior()�́A���z�֐� processSettlementBehavior() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� settleBehavior() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processSettlementBehavior() ���I�[�o�[���C�h���ă��W�b�N���������邱�ƂƂ���B <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� settleBehavior() ���s��A���� judge() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void settleBehavior();


    /**
     * �m�[�h�̃t���[�����̔��菈��(���c���[) .
     * ���̏����ł́A�m�[�h�Ԃ̗l�X�Ȕ��菈�����s�����Ƃ���݌v�B<BR>
     * �S�m�[�h���W�ړ������Ɣ��Ȃ��X�e�[�^�X�ނ̍X�V�����S�Ɋ������Ă��O��Ƃ��鏈�����s����B<BR>
     * ���s����邽�߂̃t���O�̏����́Abehave()�Ɠ������A<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �܂� ( _is_active_flg && !_was_paused_flg && _can_live_flg )�̏ꍇ <BR>
     * judge() �� ���z�֐� processJudgement() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� judge() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�Ŗ{���\�b�h�𒼐ڌĂяo�����s��Ȃ����ƂƂ���B<BR>
     * ���ʃN���X�ł̓R�[������� processJudgement() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� judge() ���s��A<BR>
     * �_(GgafGod)�͂��̌�A���t���[���܂ł̎c���Ԃɗ]�T������� preDraw() ������� doFinally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void judge();

    /**
     * �m�[�h�̃t���[�����̕`�掖�O����(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processPreDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� preDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processPreDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� preDraw() ���s��A���� draw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void preDraw();

    /**
     * �m�[�h�̃t���[�����̕`��{����(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g�A<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� draw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� draw() ���s��A���� afterDraw() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void draw();

    /**
     * �m�[�h�̃t���[�����̕`�掖�㏈��(���c���[)�i�t���[���X�L�b�v����ČĂяo����Ȃ��ꍇ������B�j .
     * �����t���O�A�����t���O���Z�b�g<BR>
     * (�܂� _is_active_flg && _can_live_flg)�̏ꍇ <BR>
     * processAfterDraw() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� afterDraw() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processAfterDraw() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� afterDraw() ���s��A���� doFinally() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void afterDraw();

    /**
     * �m�[�h�̃t���[�����̍ŏI����(���c���[) .
     * ���W�ړ������A���菈���A�`�揈�����I��������ɁA�Ō�ɍs����n���������s�����Ƃ���݌v�B<BR>
     * �����t���O�A�����t���O���Z�b�g�A���ꎞ��~�t���O���A���Z�b�g<BR>
     * �i_is_active_flg && !_was_paused_flg && _can_live_flg�j�̏ꍇ <BR>
     * processFinally() ���R�[��������A�z���̃m�[�h�S�Ăɂ��� doFinally() ���ċA�I�Ɏ��s����B<BR>
     * �_(GgafGod)�����s���郁�\�b�h�ł���A�ʏ�͉��ʃ��W�b�N�ł͎g�p���Ȃ��͂��ł���B<BR>
     * ���ʃN���X�ł̓R�[������� processFinally() ���I�[�o�[���C�h���ă��W�b�N���������� <BR>
     * �_(GgafGod)�́A���̐�(GgafUniverse)�ɑ΂��� doFinally() ���s��A<BR>
     * ���t���[���܂ł̎c���Ԃɗ]�T������� clean() �����s����B<BR>
     * ���̌�� nextFrame() �����s���邱�ƂɂȂ�B<BR>
     */
    virtual void doFinally();


    /**
     * �t���[�����̌ʐU�镑�������������B(���[�U�[�����p�A�P��) .
     * behave() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̐U�镑������������������B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ��������ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAnextFrame() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * �t���[�����̌ʐU�镑�����㏈���������B(�t���[�����[�N�����p�A�P��) .
     */
    virtual void processSettlementBehavior() {}

    /**
     * �t���[�����̌ʔ��f�����������B(���[�U�[�����p�A�P��) .
     * judge() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʔ��f�������L�q����B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��ĂāAprocessBehavior() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     * �{�����o�֐��̑��݈Ӑ}�Ƃ��āAprocessBehavior() �ō��W�ړ��������S�Ċ���������A
     * �{�����o�֐��œ����蔻�菈������������Ƃ������g������z�肵�Ă���B<BR>
     */
    virtual void processJudgement() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ`�掖�O�����������B(�t���[�����[�N�����p�A�P��) .
     * preDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���A�_(GgafGod)���`��X�L�b�v�����ꍇ�A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`�掖�O��������������B<BR>
     * �ʕ`�掖�O�����Ƃ́A��ɓ�����w�i�`��Ȃǂł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessJudgement() �����s�ς݂ł��邱�Ƃ��ۏ؂���B<BR>
     * ����ɁA�{�����o�֐����s��AprocessDraw()�AprocessAfterDraw() ���Ăяo����邱�Ƃ��ۏ؂����B
     */
    virtual void processPreDraw() {};

    /**
     * �m�[�h�̃t���[�����̌ʕ`��{�����������B(�t���[�����[�N�����p�^���[�U�[�����p�A�P��) .
     * draw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ`��{��������������B<BR>
     * �ʕ`��{�����Ƃ͎�ɃL�����N�^��A�w�i�̕`���z�肵�Ă���B
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessPreDraw() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processDraw() = 0;

    /**
     * �m�[�h�̃t���[�����̌ʕ\�����㏈�����L�q�B(�t���[�����[�N�����p�A�P��) .
     * afterDraw() ���̏����擪�ŃR�[���o�b�N�����B �A���ApreDraw() �Ɠ��l�ɐ_(GgafGod)���`��X�L�b�v���ꂽ�ꍇ�́A�t���[�����ŌĂяo����܂���B<BR>
     * ���̃����o�֐����I�[�o�[���C�h���āA�m�[�h�ʕ\�����㏈������������B<BR>
     * �ʕ\�����㏈���Ƃ́A�őO�ʃ��C���[�Ŏ�������t�F�[�h�G�t�F�N�g��A��ɍőO�ʂɕ\���������\���Ȃǂł���B<BR>
     * �{�����o���R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessDraw() �����s�ς݂ł��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processAfterDraw() {};

    /**
     * �m�[�h�̃t���[�����̌ʏI�[�����������B(���[�U�[�����p�A�P��) .
     * doFinally() ���̏����擪�ŃR�[���o�b�N�����B<BR>
     * ���̃����o�֐������ʃN���X�ŃI�[�o�[���C�h���āA�m�[�h�ʂ̏I�[��������������B<BR>
     * �I�[�����Ƃ́A�t���O�Ǘ��̎��s�Ȃǂł���B<BR>
     * �z�肵�Ă���U�镑�������Ƃ́A��ɍ��W�v�Z�ƈړ������ł���B���̑��Ȃ�ł��ǂ��ł���B<BR>
     * �{�����o�֐����R�[���o�b�N�����ƌ������́A�S�m�[�h�΂��āAprocessJudgement() �����s�ς݂� �`�揈���͏I�����Ă��邱�Ƃ�ۏ؂���B<BR>
     */
    virtual void processFinal() = 0;

    /**
     * ���m�[�h�����e�ɂ�����m�[�h�S�ĂɃC�x���g���b�Z�[�W��ʒm���܂� .
     * �C�x���g���󂯎�鑤�́AonCatchEvent(UINT32, void) ���������K�v�ł��B
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     * @param prm_pSource  �C�x���g�p�ėp�|�C���^
     */
    virtual void throwEventToLowerTree(UINT32 prm_no, void* prm_pSource = NULL);

    /**
     * �z���m�[�h�S�ĂɃC�x���g���b�Z�[�W��ʒm���܂� .
     * �C�x���g���󂯎�鑤�́AonCatchEvent(UINT32, void) ���������K�v�ł��B
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     * @param prm_pSource  �C�x���g�p�ėp�|�C���^
     */
    virtual void throwEventToUpperTree(UINT32 prm_no, void* prm_pSource = NULL);


    /**
     * �C�x���g�������̏��� .
     * @param prm_no �C�x���g���b�Z�[�W�ԍ�
     * @param prm_pSource  �C�x���g�p�ėp�|�C���^
     */
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) = 0;


    virtual bool isDisappear();
    /**
     * �_�ɉy�� .
     * @return  �Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() = 0;

    //==================��ԑJ�ڃ��\�b�h�S==================>
    /**
     * ������Ԃɂ���(���c���[�E�R�[���o�b�N�L��) .
     * ���m�ɂ́A���t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����Ŋ�����ԂɂȂ鎖�Ƃ���B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateTree() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���m�[�h�� processBehavior() �� ���g�� activateTree() ���Ăяo���R�[�h�������Ă��A�^�X�N�V�X�e���̎d�g�ݏ�A<BR>
     * processBehavior()�͊�����Ԃɂ̂ݎ��s�����̂ŁA���s����邱�Ƃ������Ӗ��������B<BR>
     * ���m�[�h�֎��s������AprocessFinal() �Ȃǂł̎g�p��z��B<BR>
     * <B>[�⑫]</B>�m�[�h��������́A������ԂƂȂ��Ă���B<BR>
     */
    virtual void activateTree();

    /**
     * ������Ԃɂ���(�P�́E�R�[���o�b�N�L��) .
     * ���m�[�h�������t���[�����犈����Ԃɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void activate();

    /**
     * ������Ԃɂ���(�P�́E�R�[���o�b�N�L��).
     * �����̃t���[�����x������ activate() �����s����܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateDelay(frame) �����s�����B<BR>
     * activateDelay(1) �́Aactivate() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͊�����Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * @param prm_offset_frames �x���t���[����(1�`)
     */
    virtual void activateDelay(frame prm_offset_frames = 1);


    virtual void activateTreeDelay(frame prm_offset_frames = 1);

    /**
     * ��莞�Ԃ���������Ԃɂ���(�P�́E�R�[���o�b�N�L��).
     * ������Ԃɂ�����A�����̃t���[�����o�߂���ƁA�񊈓���ԂɂȂ�܂��B
     * activateWhile(10); ��
     * activate(); inactivateDelay(10); �̎��s�Ɠ����̌��ʂł��B
     * @param prm_offset_frames �����t���[��
     */
    virtual void activateWhile(frame prm_frames = 1);

    /**
     * ������Ԃɂ���(�P�́E�����E�R�[���o�b�N����) .
     * ���m�[�h�ɂ��āA�����Ɋ�����Ԃɂ���B�������ȊO�Ŗ{���\�b�h�̎g�p�͔񐄏��B<BR>
     * onActive() �R�[���o�b�N�͎��s����Ȃ��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�������ȊO�ł̎g�p���͈ȉ��̓_�𗯈ӂ��āA�g�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��ėL���ɂȂ��Ă��܂��B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\�����傫���A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h��������ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void activateImmediately();

    /**
     * ������Ԃɂ���(���c���[�E�����E�R�[���o�b�N����)
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� activateImmediately() �����s�����B<BR>
     * activateImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void activateTreeImmediately();
    //===================
    /**
     * �񊈓���Ԃɂ���(���c���[�E�R�[���o�b�N�L��) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��āA���t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă܂��B
     * ���t���[���̓����擪����(nextFrame())���Ŋ��S�ɔ񊈓���ԂƂȂ�܂��B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivate() �����s����鎖�Ɠ����ł��B<BR>
     */
    virtual void inactivateTree();

    /**
     * �񊈓���Ԃɂ���(�P�́E�R�[���o�b�N�L��) .
     * ���m�[�h�������t���[������񊈓���Ԃɂ���\��t���O�𗧂Ă܂��B
     * ���t���[���̓����擪����(nextFrame())���Ŋ��S�ɔ񊈓���ԂƂȂ�܂��B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     */
    virtual void inactivate();

    /**
     * �񊈓��\�񂷂�(���c���[�E�R�[���o�b�N�L��) .
     * �����̃t���[�����x������ inactivate() �����s����܂��B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateDelay(UINT32) �����s�����B<BR>
     * inactivateDelay(1) �́Ainactivate() �Ɠ����Ӗ��ɂȂ�܂��B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͔񊈓���Ԃ̕ω��͖�����ѐ��͕ۂ����B<BR>
     * @param prm_offset_frames �x���t���[����(1�`)
     */
    virtual void inactivateDelay(frame prm_offset_frames = 1);



    virtual void inactivateTreeDelay(frame prm_offset_frames = 1);

    /**
     * �񊈓���Ԃɂ���(�P�́E�����E�R�[���o�b�N����)  .
     * ���m�[�h�ɂ��āA�����ɔ񊈓���Ԃɂ���B�������ȊO�ŁA�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * onInactive() �R�[���o�b�N�͎��s����Ȃ��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�������ȊO�ł̎g�p���͈ȉ��̓_�𗯈ӂ��āA�g�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\�����傫���A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h���񊈓���ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void inactivateImmediately();

    /**
     * �񊈓���Ԃɂ���(���c���[�E�����E�R�[���o�b�N����)  .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� inactivateImmediately() �����s�����B<BR>
     * inactivateImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void inactivateTreeImmediately();

    //===================
    /**
     * �ꎞ��~�ɂ���(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~�ɂȂ鎖�Ƃ���B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pause() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~�̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void pauseTree();

    /**
     * �ꎞ��~�ɂ���(�P��) .
     * ���m�[�h�������t���[������ꎞ��~�ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~�̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void pause();

    /**
     * �ꎞ��~��Ԃɂ���(�P�́E����) .
     * ���m�[�h�ɂ��āA�����Ɉꎞ��~��ԁi _was_paused_flg = true �j�ɂ���B�ʏ�A�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��Ďg�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �ω������V���ȃt���O��Ԃ́A�w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\��������A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h���ꎞ��~��ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void pauseImmediately();

    /**
     * �ꎞ��~��Ԃɂ���(���c���[�E����) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� pauseImmediately() �����s�����B<BR>
     * pauseImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void pauseTreeImmediately();

    //===================
    /**
     * �ꎞ��~��Ԃ���������(���c���[) .
     * ���m�ɂ́A���t���[������ꎞ��~��Ԃ���������\��t���O�𗧂Ă�B<BR>
     * �����āA���t���[���擪�����ňꎞ��~��Ԃ���������鎖�ɂȂ�B<BR>
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpause() �����s�����B<BR>
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~��Ԃ������̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void unpauseTree();
    /**
     * �ꎞ��~��Ԃ���������(�P��) .
     * ���m�[�h�������t���[������ꎞ��~��Ԃ������ɂ���\��t���O�𗧂Ă�B<BR>
     * �z���m�[�h�ɂ͉����e��������܂���B
     * �{���\�b�h�����s���Ă��A�w����t���[�����x�͈ꎞ��~��Ԃ������̕ω��͖�����ѐ��͕ۂ����B<BR>
     */
    virtual void unpause();

    /**
     * �ꎞ��~��Ԃ���������(���c���[�E����) .
     * ���g�Ɣz���m�[�h�S�Ăɂ��čċA�I�� unpauseImmediately() �����s�����B<BR>
     * unpauseImmediately() �̐�����v�Q�ƁB<BR>
     * �g�p����Ƃ��́A���m�[�h�̉e����ǂ��l���Ē��ӂ��Ďg�p���邱�ƁB<BR>
     */
    virtual void unpauseTreeImmediately();

    /**
     * �ꎞ��~��Ԃ���������(�P�́E����) .
     * ���m�[�h�ɂ��āA�����Ɉꎞ��~���Ă��Ȃ���ԁi _was_paused_flg = false �j�ɂ���B�ʏ�A�{���\�b�h�̎g�p�͔񐄏��B<BR>
     * �����ɏ�Ԃ��ω����邽�߁A�ȉ��̓_�𗯈ӂ��Ďg�p����ۂ͒��ӂ��K�v�ł���B<BR>
     * �ω������V���ȃt���O��Ԃ́A�w����t���[�����x�̎c��̖������̃m�[�h�ɑ΂��Ă̂ݗL���ƂȂ�B�܂�A<BR>
     * �w����t���[�����x�ł����Ă��A���ɏ������ꂽ�m�[�h�Ƃ͈قȂ��ԂɂȂ�\��������A<BR>
     * ���m�[�h�̃��W�b�N���A�u���̃m�[�h���ꎞ��~��ԂȂ�΁E�E�E�v���A���̏�ԁi�t���O�j�ɂ�菈�����򂵂Ă����ꍇ�A<BR>
     * ����t���[�����̏������ʂ̐�����������鋰�ꂪ����B<BR>
     * ���m�[�h�̉e���A�c���[�\����ǂ��l���Ďg�p���邱�ƁB<BR>
     */
    virtual void unpauseImmediately();
    //===================
    /**
     * ��Ԃ����Z�b�g���� .
     * ���̂悤�ȓ�����w�����x�ɍs���܂��i���t���[���̐擪�������ł͂���܂���j�B<BR>
     * �@ ����t���[�����ŁA���߂Ă̌Ăяo���ł��邩�`�F�b�N<BR>
     *   �E���߂Ă̌Ăяo���ł���B  �� �A��<BR>
     *   �E�Q��ȏ�Ăяo����Ă���B�� �������Ȃ���return<BR>
     * �A ���̓����t���[���J�E���^�����Z�b�g<BR>
     *   �EgetBehaveingFrame() �� 0 �ɂ���B<BR>
     *   �EgetActivePartFrame() �� 0 �ɂ���B<BR>
     * �B ���ʎ��������� onReset() ���Ăяo���܂��B<BR>
     * �⑫:������ initialize() �Ăяo������ɁA�P�񂾂� reset() �͎����I�ɌĂяo����܂��B<BR>
     * <pre>
     */
    virtual void reset();
    // ������ initialize(), onReset(), onActive() �̎g�������ɂ��ā�
    // ��Ԃ����Z�b�g�����́A�ǂ��Ɏ�������ׂ����H
    // initialize() �E�E�E ������A�ŏ��̂P�񂾂����O�ɃR�[���o�b�N�����B�������������Ɏg�p���邱�Ƃ�z��B
    // onReset()    �E�E�E ������Ainitialize() �̌�A�P�񂾂��������ŃR�[�������B���̌�Areset() ���s�łŃR�[���o�b�N�����B
    // onActive()   �E�E�E ������Ainitialize() �̌�̊�����Ԏ� �P�t���[���ڂ� behave() ���O�ɃR�[�������B
    //                     ���̌� �񊈓���������ԂɂȂ������A�����I�ɃR�[���o�b�N�����B
    // �m�[�h(�A�N�^�[��V�[��)�̏����T�C�N���ɂ���Ďg��������B
    //
    // �E�P�T�C�N���ȃm�[�h(�A�N�^�[��V�[��)�̏ꍇ
    // ������A���߂Ắu�I���v�Ƃ�����Ԃ��}�����ۂɁA���̂܂܉���ƂȂ�ꍇ�B�܂�A�C���X�^���X���g���܂킳�Ȃ��ꍇ�B
    // initialize(), onReset(), onActive() �͎��O�Ɋe�P����s�����̂ŁA�ǂ��ɏ�Ԃ����Z�b�g�������������Ă����ق͖����͂��B
    // �����̒ʏ�̃A�N�^�[��A�ꎞ�I�ȒZ���V�[���͂���ɊY������Ɨ\�z����B
    // �ǂ��Ɏ������Ă��ǂ����Ainitialize() �Ŏ����𓝈ꂵ���ق����A���̃I�u�W�F�N�g���瑀�삵�₷���B
    //
    // �EonActive() ���g�p���ׂ��ꍇ
    // �������ꂽ�m�[�h�ɁA�u�\���v�u��\���v�Ƃ�����Ԃ����݂��A�g���܂킷�ꍇ�B
    // �\��(����) �` ��\��(�񊈓�) ���A�m�[�h�̂P�T�C�N���̂ƈ�v����ꍇ�B
    // initialize() �E�E�E �����������A
    // onActive()   �E�E�E ��ԃ��Z�b�g����
    // �Ǝg�������ċL�q���B inacivate()�Aactive() �ŏ�ԃ��Z�b�g�s���B
    // �Ȃ� onReset() �ɏ�ԃ��Z�b�g�������L�q���Areset()�R�[���ł͂����Ȃ��̂��Ƃ����ƁA
    // �����̒��S�ł��� processBehavior() ���\�b�h�́A��\��(�񊈓�) �̓R�[������Ȃ����߁A
    // ���g�̃I�u�W�F�N�g�̏����� reset() ���L�q���Ă����s����邱�Ƃ������Ƃ������̂Ɋׂ�B
    // �������A���̃I�u�W�F�N�g����A��\��(�񊈓�)���\��(����) ���`�F�b�N���Areset() �����s���Ă������
    // ���Ȃ����A�����Z�b�g�����̂��A������ǂ������Ȃ��ƕ�����Ȃ��悤�ɂȂ�Ƃ����f�����b�g������̂ł͂Ȃ����낤���B
    // onActive() ���R�[������Ă��AgetBehaveingFrame() �́u���Z�b�g����Ȃ��v���A
    // getActivePartFrame()�́u���Z�b�g�v����鎖�ɒ��ӁB
    // ��ɓG�e�Ȃǔėp�I�ȃA�N�^�[�́A����ɊY������Ɨ\�z����B
    //
    // �EonReset() ���g�p���ׂ��ꍇ
    // �������ꂽ�m�[�h�ɁA�u�\���v�u��\���v�Ƃ����T�O�������i�����͕\�������ςȂ��j�ŁA
    // �Ȃ����A�����T�C�N���i���Z�b�g�j�̊T�O������m�[�h�ꍇ
    // initialize() �E�E�E �����������A
    // onReset()    �E�E�E ��ԃ��Z�b�g����
    // �Ǝg�������ċL�q���B reset() �ŏ�ԃ��Z�b�g���s���B
    // onReset() �R�[���o�b�N���́A�����t���[���J�E���^�́u���Z�b�g�����v���ɒ��ӁB
    // ��ɃV�[���ƁA�ꕔ�̃A�N�^�[�́A����ɊY������Ɨ\�z����B
    //
    // �EonActive() onReset() �������Ďg�p���ׂ��ꍇ�B
    // �\��(����) �` ��\��(�񊈓�) ���A�m�[�h�̂P�T�C�N���ƈ�v���Ȃ��ꍇ�A
    // initialize() �E�E�E �����������A
    // onActive()   �E�E�E ��ʕ`�掞����������
    // onReset()    �E�E�E ��ԃ��Z�b�g����
    // �Ǝg�������ċL�q���B inacivate()�Aactivate() �� reset() ���R�[�����B
    // reset() �ŏ�ԃ��Z�b�g���s���B
    // ���@�͂���ɊY������Ɨ\�z�B
    //
    // �Einitialize() onActive() onReset() �ǂ����ł��悢�ꍇ�B
    // �\��(����) �` ��\��(�񊈓�) ���A�m�[�h�̐����`����Ɉ�v����ꍇ�B
    // �܂胊�Z�b�g�Ƃ������g���񂷊T�O���Ȃ��I�u�W�F�N�g�́A�I�u�W�F�N�g�̏�������
    // initialize() onActive() onReset() �̉����ɋL�q���Ă��قڈӖ��͓����ł���B
    // ��������A�\��(����)�܂łɃ^�C�����O���݂�Ȃ�΁AonActive() onReset() �̂ǂ��炩��
    // �L�q���ׂ����B


    /**
     * ��Ԃ����Z�b�g����i���c���[�j .
     * ���c���[�S�ẴI�u�W�F�N�g�ɑ΂� reset() ���w�����x���s���܂��B
     */
    virtual void resetTree();

    /**
     * ��Ԃ����Z�b�g����(���[�U�[�����p) .
     * reset() �����́AresetTree() �����s���邱�ƂŌĂяo����܂��B
     * �ʂ̂̏�ԃ��Z�b�g�������A���ʃN���X�ŃI�[�o�[���C�h���Ă��������B
     */
    virtual void onReset() {}


    /**
     * �I�����܂��B(���c���[) .
     * ���m�[�h�������̃t���[����Ɂu�����I���v��Ԃɂ��邱�Ƃ�錾����B�i�I���t���O�𗧂Ă�j <BR>
     * ���c���[�m�[�h�S�ē��A��ŁA�I��(end())�����m�点���͂��B<br>
     * �e�m�[�h���I������΁A�q�m�[�h���I��������𓾂Ȃ�����ł���B<BR>
     * �I���t���O�͈�x���Ă�ƌ��ɂ��ǂ��܂���B�ȍ~ end() ���d�˂ČĂяo���Ă��������܂��B<BR>
     * �����̗P�\�t���[����ɐ����I���Ƃ���B<BR>
     * �u�����I���v�Ƃ͋�̓I�ɂ́A�U�镑���t���O(_is_active_flg)�A�����t���O(_can_live_flg) ���A
     * ���t���[������A���Z�b�g����\��t���O�𗧂Ă邱�Ǝ��ł���B<BR>
     * _can_live_flg ���A���Z�b�g����邱�Ƃɂ��A�S�~��(GgafGarbageBox) �ɏ������邱�ƂɂȂ�B<BR>
     * �����Đ_(GgafGod)�����ɗ]�T�̂��鎞�����v�炢 clean() ���\�b�h�ɂ��A<BR>
     * GgafGarbageBox���ێ�����GgafDisusedActor �z���m�[�h�� delete ���邱�ƂƂȂ�B<BR>
     * ���������āA�{�����o�֐������s���Ĉ����̗P�\�t���[����ɂȂ��Ă��A�܂�delete�͍s�Ȃ�ꂸ�A<BR>
     * GgafDisusedActor �z���Ɉڂ邾���B�i�^�X�N����͏��O����Ă���j�B<BR>
     * ���t���[���ȍ~�ł������ɂ� delete �����Ƃ͌���Ȃ��B<BR>
     * �C���X�^���X�������ɉ������Ȃ����Ƃɒ��ӂ���I�i�����I�ȃo�O�𐶂݂₷���j�B<BR>
     * @param prm_offset_frames �����I���P�\�t���[��(1�`)
     */
    virtual void end(frame prm_offset_frames = 1);

    /**
     * ���c���[�m�[�h���ŏI�m�[�h�Ɉړ�����(�P��) .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̍ŏI�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂Ȃ��B<BR>
     */
    virtual void moveLast() override {
        _will_mv_last_in_next_frame_flg = true;
    }

    virtual void moveLastImmediately() {
        GGAF_NODE::moveLast();
    }
    /**
     * ���c���[�m�[�h��擪�m�[�h�Ɉړ�����(�P��) .
     * ���t���[���̐擪����(nextFrame())�Ŏ��c���[�m�[�h���Z��m�[�h�O���[�v�̐擪�ɃV�t�g����B<BR>
     * <B>[����]</B>�����ɏ��J�菈�������s�����킯�ł͂Ȃ��B<BR>
     */
    virtual void moveFirst() override {
        _will_mv_first_in_next_frame_flg = true;
    }

    virtual void moveFirstImmediately() {
        GGAF_NODE::moveFirst();
    }
//    /**
//     * �����c���[����Ɨ�����(�P��)
//     * extract() �̃��b�p�[�ŁA�����m�F�̃`�F�b�N�t���B�ʏ�͂�������g�p����B
//     * @return  T* �E�ނ��Ɨ��������m�[�h�̃|�C���^
//     */
//    virtual T* extract() override;


    /**
     * �񊈓����犈���ɐ؂�ւ�������ǂ��� .
     * �������AonActive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h�����������B<BR>
     * @return  bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    virtual bool onChangeToActive();

    /**
     * ���������~�ɐ؂�ւ�������ǂ��� .
     * �������AonInactive() �I�[�o�[���C�h�Ŏ������ꍇ�́A���̕�����������L�q�ł���͂��B<BR>
     * ���̃m�[�h�̏�ԕω���m�肽�����̂��߂ɁA�{���\�b�h�����������B<BR>
     * @return  bool true:�؂�ւ�����^false:�؂�ւ���Ă��Ȃ�
     */
    virtual bool onChangeToInactive();

    /**
     * �����\�����ׂ�
     * @return  bool true:�����\�^false:�����s��
     */
    virtual bool canLive() {
        return _can_live_flg;
    }

    /**
     * �����������ׂ�
     * @return  bool true:�������^false:�񊈓���
     */
//    virtual bool isActive();

    /**
     * �U�镑���\�����ׂ�i���ꎞ��~����Ă��Ȃ����j
     * @return  bool true:�U�镑���\�i�������ňꎞ��~�ł͖����j�^false:�U�镑���s��
     */
    virtual bool canBehave();

    /**
     */
    virtual bool wasPause();

    /**
     * �I���錾�������ǂ���
     * @return
     */
    virtual bool wasDeclaredEnd();

    /**
     * �U�镑����Ԃɉ��Z�����t���[�������擾���� .
     * �����Z�b�g���Ȃ��ꍇ�A���̂悤�Ȓl��Ԃ��B<BR>
     * 1 Frame �` ����̒l�ɂȂ�B0 Frame��Ԃ͊�{���݂��Ȃ��B�A����O�I��<BR>
     * �������R���X�g���N�^���A����сA�ŏ��� initialize() ���ł� 0 Frame ��Ԃ��B<BR>
     * ������s�� onActive()�AprocessBehavior()�AprocessJudgement() ���̒��� 1 �ɂȂ��Ă���B<BR>
     * �ȍ~�A�U�镑���Ԏ��Ƀt���[�����Z�����B<BR>
     * �u�U�镑����ԁv�Ƃ́AcanBehave() == true �̏����������̎����Ӗ�����B<BR>
     * @return �U�镑���t���[�������v
     */
    virtual UINT32 getBehaveingFrame();

    /**
     * �U�镑�����onActive()����J�n�����A�U�镑����Ԃ͉��t���[���ڂ���Ԃ��B .
     * �ėp�I�u�W�F�N�g�ȂǁA��x�������Ďg���܂킷(delete���Ȃ�)�ꍇ�A<BR>
     * �������� inactivate() �A �o���� activate() ���J��Ԃ����Ƃ�z��B<BR>
     * getBehaveingFrame() �Ɠ����^�C�~���O�ŉ��Z�����BprocessBehavior()�ł́A1 �` ��Ԃ��B
     * onActive()�R�[���o�b�N�����������Ƀ��Z�b�g�����B<BR>
     * @return onActive()����̐U�镑���t���[����
     */
    virtual UINT32 getActivePartFrame();


    /**
     * ���Όo�ߐU�镑���t���[���̔���B
     * ���O�� relativeFrame(int) ���s���i���ʂ�true/false�Ɋւ�炸�j�̃t���[��������̌o�߃t���[�����ɒB���������肷��B
     * ����Ăяo���́AgetBehaveingFrame() == �O����̑��΃t���[�����ƂȂ邽�߁A�P�x�͋�Ăяo�����s���i�Ȃ�Ƃ��������j���ɂȂ邩������Ȃ��B
     * ���ӁF����q���������ɂ��ArelativeFrame(int) ���Ăяo�����񐔂��ω�����ꍇ�A���Όo�߃t���[�����ω�����B
     * @param   prm_frameEnd    ���ΐU�镑���t���[����
     * @return  bool    true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
     */
    virtual bool relativeFrame(frame prm_frameEnd);




    /**
     * �z���S�ẴI�u�W�F�N�g�ɑ΂��Ďw��̊֐������s������ .
     * �z���I�u�W�F�N�g�i�A�N�^�[���V�[���j�̃|�C���^���A�����֐��|�C���^�� pFunc�̑�P�����ɓn���Ă���B<BR>
     * �����֐��|�C���^�� pFunc �̑�Q�����ɂ́AexecuteFuncToLowerTree �Ăяo������ prm1(�����P)�̃|�C���^���n���Ă���B<BR>
     * �����֐��|�C���^�� pFunc �̑�R�����ɂ́AexecuteFuncToLowerTree �Ăяo������ prm2(�����Q)�̃|�C���^���n���Ă���B<BR>
     * �z���̃I�u�W�F�N�g�����ł���̂������Ă����Ŏg�p���Ȃ��Ɗ댯�ł���B<BR>
     * ���ƁA����C++�Ń����_�����g�킹�Ă��������B<BR>
     *
     * ���g�p�၄<BR>
     * XXXXScene �z���̃I�u�W�F�N�g�S�ẴA�N�^�[(�A��GgafDxGeometricActor)�̃����o�ϐ� _X �ɁA
     * XXXXScene�����o�ϐ� _velo �̒l�����Z������B<BR>
     * XXXXScene �N���X�̎����T���v�����ȉ��ɋL��<BR>
     * <code><pre>
     *
     * class XXXXScene : public GgafScene {
     *
     *     int _velo;
     *
     *     static void addX(GgafObject* pThat, void* p1, void* p2) { //p1��_velo���n��
     *         if (pThat->_obj_class >= Obj_GgafScene) {
     *             return; //�V�[���Ȃ�Ζ���
     *         }
     *         GgafActor* pActor = (GgafActor*)pThat;
     *         if (pActor->_obj_class & Obj_GgafDxGeometricActor) {
     *             //GgafDxGeometricActor�Ȃ�� _X �����Z
     *             ((GgafDxGeometricActor*)pActor)->_X += (*((int*)p1));
     *         }
     *     }
     *
     *     void processBehavior() {
     *         //�z���A�N�^�[�S�Ă�addX���s
     *         executeFuncToLowerTree(XXXXScene::addX, _velo, NULL);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc �I�u�W�F�N�g�Ɏ��s���������֐�
     * @param prm1 �����ɓn�������������̂P
     * @param prm2 �����ɓn�������������̂Q
     */
    virtual void executeFuncToLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2);


    virtual void useProgress(int prm_num = 10) {
        if (_pProg == NULL) {
            _pProg = NEW GgafProgress(&_frame_of_behaving, prm_num);
        } else {
            _TRACE_("["<<GGAF_NODE::getName()<<"] �͊��� useProgress ���Ă��܂��Bprm_num="<<prm_num);
        }
    }

};

///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : GgafCore::GgafNode<T>(prm_name),
_pGod(NULL),
_was_initialize_flg(false),
_frame_of_life(0),
_frame_of_behaving(0),
_frame_of_behaving_since_onActive(0),
_frameEnd(0),
_is_active_flg(true),
_was_paused_flg(false),
_can_live_flg(true),
//_is_active_flg_in_next_frame(true),
_was_paused_flg_in_next_frame(false),
//_can_live_flg_in_next_frame(true),
_will_end_after_flg(false),
_frame_of_life_when_end(MAXDWORD),
_will_activate_after_flg(false),
_frame_of_life_when_activation(0),
_will_inactivate_after_flg(false),
_frame_of_life_when_inactivation(0),
_on_change_to_active_flg(false),
_on_change_to_inactive_flg(false),
_will_mv_first_in_next_frame_flg(false),
_will_mv_last_in_next_frame_flg(false),
_is_already_reset(false),
_pProg(NULL)
{

}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _frame_of_behaving=" << _frame_of_behaving << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);
    _was_paused_flg  = _was_paused_flg_in_next_frame;
    if (_was_paused_flg) {
        return;
    }
    //moveLast�\��
    if (_will_mv_last_in_next_frame_flg) {
        _will_mv_last_in_next_frame_flg = false;
        GGAF_NODE::moveLast();
        return;
        //��return���鎖�͏d�v�BnextFrame() �����̂Q�d���s�������邽�߁B
        //���̃m�[�h�́A�����ɉ񂳂�Ă��邽�߁A�K��������x nextFrame() �̋@��K���B
    }


    //�I���̎���
    if (_will_end_after_flg && _frame_of_life_when_end == _frame_of_life+1) { //�܂� _frame_of_life ���i��Ŗ�������+1
       // _is_active_flg_in_next_frame = false;
        _can_live_flg = false;
    }

    //_can_live_flg    = _can_live_flg_in_next_frame;

    _on_change_to_active_flg = false;
    _on_change_to_inactive_flg = false;
    _frame_of_life++;
    if (_can_live_flg) {

        if(_was_initialize_flg == false) {
            initialize();       //������
            _was_initialize_flg = true;
            reset(); //���Z�b�g
        }


        if (_is_active_flg && _frame_of_life == 1) {
            //���܂�Ă��̂܂܂Ȃ�΁A�����Ȃ��񂾂�onActive()�B
            _on_change_to_active_flg = true;
            //�t���[�����Z���Ă���onActive()
            _frame_of_behaving++;
            _frame_of_behaving_since_onActive = 1;
            onActive(); //�R�[���o�b�N
            _frame_of_life_when_activation = 0;
            _will_activate_after_flg = false;
        } else if (_will_activate_after_flg) {
            if (_is_active_flg) { //���Ƃ��Ɗ�����
                _frame_of_behaving++;
                _frame_of_behaving_since_onActive++;
            } else if(_frame_of_life == _frame_of_life_when_activation) {
                //activate����
                if (_is_active_flg == false) {//_is_active_flg = false �� true  ��
                    _is_active_flg = true; //�����t���OON!!!
                    _on_change_to_active_flg = true;
                    //�t���[�����Z���Ă���onActive()
                    _frame_of_behaving++;
                    _frame_of_behaving_since_onActive = 1;
                    onActive(); //�R�[���o�b�N
                    _frame_of_life_when_activation = 0;
                    _will_activate_after_flg = false;
                } else {                      //���Ƃ��Ɗ�����
                    _frame_of_behaving++;
                    _frame_of_behaving_since_onActive++;
                }
            }
        } else {
            _frame_of_behaving++;
            _frame_of_behaving_since_onActive++;
        }

        if (_will_inactivate_after_flg) {
            if (_frame_of_life == _frame_of_life_when_inactivation) {
                _frame_of_life_when_inactivation = 0;
                _will_inactivate_after_flg = false;
                //inactivate����
                if (_is_active_flg == true) { //_is_active_flg = true �� false ��
                    _is_active_flg = false;//�����t���OOFF!!!
                    _on_change_to_inactive_flg = true;
                    onInactive(); //�R�[���o�b�N

                } else {
                    //���Ƃ��Ɣ񊈓���
                }
            } else {

            }
        }
        _is_already_reset = false;
    }

    //�z����nextFrame()���s
    if (GGAF_NODE::_pSubFirst) {
        T* pElementTemp = GGAF_NODE::_pSubFirst;
        while(true) {

            if (pElementTemp->_is_last_flg) {
                pElementTemp->nextFrame();
                if (pElementTemp->_can_live_flg == false) {
                    GgafFactory::_pGarbageBox->add(pElementTemp); //�S�~����
                }
                break;
            } else {
                pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                pElementTemp->GGAF_NODE::_pPrev->nextFrame();
                if (pElementTemp->GGAF_NODE::_pPrev->_can_live_flg == false) {
                    GgafFactory::_pGarbageBox->add(pElementTemp->GGAF_NODE::_pPrev); //�S�~����
                }
            }
        }
    }


    if (_will_mv_first_in_next_frame_flg) {
        _will_mv_first_in_next_frame_flg = false;
        GGAF_NODE::moveFirst();
        //moveFirst����ԍŌ�ɂ��邱�Ƃ͏d�v�B
        //����� nextFrame() �̂Q�d���s������邽�߁B
    }

    // �i���𔽉f
    if (_pProg) {
        _pProg->update();
    }
    TRACE("GgafElement::nextFrame END _frame_of_behaving="<<_frame_of_behaving<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processBehavior();    //���[�U�[�����p
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::settleBehavior() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    //if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processSettlementBehavior(); //�t���[�����[�N�p
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->settleBehavior();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}


template<class T>
void GgafElement<T>::judge() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processJudgement();    //���[�U�[�����p
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::preDraw() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processPreDraw();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->preDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::draw() {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processDraw();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->draw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::afterDraw() {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processAfterDraw();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->afterDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}


template<class T>
void GgafElement<T>::doFinally() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processFinal();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->doFinally();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::reset() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //������
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            _frame_of_behaving = 0;
            _frame_of_behaving_since_onActive = 0;
            onReset();
            _is_already_reset = true;
        }
    }
}


template<class T>
void GgafElement<T>::resetTree() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //������
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            _frame_of_behaving = 0;
            _frame_of_behaving_since_onActive = 0;
            onReset();
            _is_already_reset = true;
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->resetTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activate() {
    if (_can_live_flg) {
        activateDelay(1);
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        activateDelay(1);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateImmediately() {
    if (_can_live_flg) {
        _is_active_flg = true;
    }
}

template<class T>
void GgafElement<T>::activateTreeImmediately() {
    if (_can_live_flg) {
        activateImmediately();
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        //����inactivateDelay()���s�ς݂̏ꍇ��
        //����inactivateDelay()�͖����������B
        _will_inactivate_after_flg = false;

        //����activateDelay()���s�ς݂̏ꍇ�́A����w��Z�t���[���ŏ㏑������i�㏟���j�B
        //(��inactivateDelay() �ƗD��̍l�����Ⴄ���ߒ���)
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + prm_offset_frames;
    }
}
template<class T>
void GgafElement<T>::activateWhile(frame prm_frames) {
    if (_can_live_flg) {
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + 1;
        _will_inactivate_after_flg = true;
        _frame_of_life_when_inactivation = _frame_of_life + prm_frames;
    }
}


template<class T>
void GgafElement<T>::activateTreeDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        activateDelay(prm_offset_frames);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivate() {
    if (_can_live_flg) {
        inactivateDelay(1);
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        inactivateDelay(1);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        if (_will_activate_after_flg) {
            //����activateDelay()���s�ς݂̏ꍇ
            if (_frame_of_life_when_activation >= _frame_of_life + prm_offset_frames) {
                //inactive �\�������� active �\��Ȃ�΁A(active�ɂ͂Ȃ�Ȃ�����)�����ɂ���B
                _will_activate_after_flg = false;
            }
        }

        if (_will_inactivate_after_flg) {
            //����inactivateDelay()���s�ς݂̏ꍇ�A��葁�� inactivate ����Ȃ�Ώ㏑������
            if (_frame_of_life_when_inactivation < _frame_of_life + prm_offset_frames) {
                //����w��Z�t���[���̕����x���ꍇ�͖��������B
                return;
            }
        }
        _will_inactivate_after_flg = true;
        _frame_of_life_when_inactivation = _frame_of_life + prm_offset_frames;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        inactivateDelay(prm_offset_frames);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeDelay(prm_offset_frames);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateImmediately() {
    if (_can_live_flg) {
        _is_active_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeImmediately() {
    if (_can_live_flg) {
        inactivateImmediately();
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
        //_is_active_flg = false;
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->pauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpauseImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
    }
}
template<class T>
void GgafElement<T>::end(frame prm_offset_frames) {
    if (_will_end_after_flg) {
        //����end()���s�ς݂̏ꍇ�A��葁��end()����Ȃ�ΗL���Ƃ���
        if (_frame_of_life_when_end < _frame_of_life + prm_offset_frames + GGAF_SAYONARA_DELAY) {
            //����w��̕����x���t���[���w��ł��邽�ߖ�������B
            return;
        }
    }
    _will_end_after_flg = true;
    _frame_of_life_when_end = _frame_of_life + prm_offset_frames + GGAF_SAYONARA_DELAY;
    inactivateDelay(prm_offset_frames); //�w��t���[���ɂ�inactivate���s����
    if (GGAF_NODE::_pSubFirst) {
        T* pElementTemp = GGAF_NODE::_pSubFirst;
        while(true) {
            if (prm_offset_frames > 2) {
                pElementTemp->end(prm_offset_frames-1); //�o���邾�����[����end����
            } else {
                pElementTemp->end(prm_offset_frames);
            }
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->GGAF_NODE::_pNext;
            }
        }
    }
}


//template<class T>
//bool GgafElement<T>::isActive() {
//    if (_can_live_flg && _is_active_flg) {
//        return true;
//    } else {
//        return false;
//    }
//}

template<class T>
bool GgafElement<T>::onChangeToActive() {
    if (_can_live_flg && _on_change_to_active_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::onChangeToInactive() {
    if (_can_live_flg && _on_change_to_inactive_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::canBehave() {
    if (_can_live_flg && _is_active_flg && !_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}


template<class T>
bool GgafElement<T>::wasPause() {
    if (_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::wasDeclaredEnd() {
    if (_will_end_after_flg || _can_live_flg == false) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(frame prm_frameEnd) {
    if (_frame_of_behaving == _frameEnd) {
        _frameEnd += prm_frameEnd;
        return true;
    } else {
        return false;
    }
}


//template<class T>
//T* GgafElement<T>::extract() {
//    if (_can_live_flg) {
//        return GGAF_NODE::extract();
//    } else {
//        //_TRACE_("[GgafElement<"<<GGAF_NODE::_class_name<<">::extract()] ���x���� "<<GGAF_NODE::getName()<<"�́A����ł��܂��B");
//        return GGAF_NODE::extract();
//    }
//}

template<class T>
void GgafElement<T>::clean(int prm_num_cleaning) {
    if (GGAF_NODE::_pSubFirst == NULL) {
        return;
    }

    T* pElementTemp = GGAF_NODE::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafFactory::_cnt_cleaned < prm_num_cleaning) {

        if (pElementTemp->_pSubFirst) {
            //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
            pElementTemp->clean(prm_num_cleaning);
            if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }

        if (pElementTemp->_is_first_flg) { //�Ō�̈��
            if (pElementTemp->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pElementTemp->clean(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pElementTemp);
                GgafFactory::_cnt_cleaned++;
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //�q�̎q���܂��̂��Ă���ꍇ����ɂ�����
                pWk->clean(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pWk);
                GgafFactory::_cnt_cleaned++;
            }
        }
    }
}


template<class T>
UINT32 GgafElement<T>::getBehaveingFrame() {
   return _frame_of_behaving;
}

template<class T>
UINT32 GgafElement<T>::getActivePartFrame() {
   return _frame_of_behaving_since_onActive;
}
template<class T>
void GgafElement<T>::executeFuncToLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    if (_can_live_flg) {
        if (_was_initialize_flg) {
            pFunc(this, prm1, prm2);
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->executeFuncToLowerTree(pFunc, prm1, prm2);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventToLowerTree(UINT32 prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        _frameEnd = 0;
        onCatchEvent(prm_no, prm_pSource);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->throwEventToLowerTree(prm_no, this);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventToUpperTree(UINT32 prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            onCatchEvent(prm_no, prm_pSource);
        }
        if (GGAF_NODE::_pParent) {
            T* pElementTemp = GGAF_NODE::_pParent;
            pElementTemp->throwEventToUpperTree(prm_no, this);
        } else {
            //�Ă��؂�
        }
    }
}


template<class T>
bool GgafElement<T>::isDisappear() {
    if (_is_active_flg == false) {
//    if (_will_inactivate_after_flg ||
//        _is_active_flg_in_next_frame == false ||
//        _will_end_after_flg ) {
        return true;
    } else {
        return false;
    }
}


template<class T>
GgafElement<T>::~GgafElement() {
    DELETE_POSSIBLE_NULL(_pProg);
}

}
#endif /*GGAFELEMENT_H_*/
