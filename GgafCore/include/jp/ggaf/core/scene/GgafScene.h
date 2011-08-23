#ifndef GGAFSCENE_H_
#define GGAFSCENE_H_

namespace GgafCore {

/**
 * �V�[���N���X .
 * �{�v���O�����ł́w�V�[���x�Ƃ́A�A�v����ł́u��ʁv�Ƃ����T�O���u����Z�܂������́v�ƍl���A<BR>
 * �؂蕪����ꂽ�I�u�W�F�N�g�̎��ł��B�������������ƁA�Q�[���i�A�v���j�Ƃ������̂́A<BR>
 * �u�l�X�ȁw��ʁA�V�[��(GgafScene)�x�ɂ����āw�L�����A�A�N�^�[(GgafActor)�x���������􂷂���̂ł���B�v<BR>
 * �Ƃ����T�O�̕����͋��ʉ��ł���͂����ƐM���Đ݌v���s���܂����B�ȒP�Ɍ����Ɖ�������ł��ˁB<BR>
 * �A�v���S�̂����ɃA�j�����Đ����Ă�����̂ƍl�����ꍇ�A�V�[���I�u�W�F�N�g�Ƃ́A<BR>
 * ���C���[�i�Z���j�̂悤�ȕ��ɂ�����܂��B<BR>
 * �@�\�Ƃ��āA�V�[���I�u�W�F�N�g���m���|�C���^�ڍ����A�c���[�K�w�\�����̂鎖���ł��܂��B�i���̃c���[�\���̓N���X�̌p���Ɗ֌W����܂���B�j<BR>
 * �V�[���Ɏ�������Ă��郁�\�b�h�S�̂قƂ�ǂ́A�������g�Ǝ����z���̃V�[���i���c���[�V�[���j�S�Ăɉe������d�l�ɂȂ��Ă��܂��B<BR>
 * �e�V�[���́A�K���P�̊ēA�N�^�[(GgafDirector)�������o�Ƃ��ĕێ����Ă��܂��B<BR>
 * �ēA�N�^�[�Ƃ͊e�V�[���̃A�N�^�[�̑�e���̂悤�Ȃ��̂ŁAGgafDirector �̃R�����g���Q�Ƃ��ĉ������B<BR>
 *
 * <B>�y�p��⑫�z</B>
 * <TABLE border='1'>
 * <TR>
 * <TD>�u�V�[���v</TD>
 * <TD>�V�[���N���X�̃C���X�^���X�i�ւ̃|�C���^�j���ȗ����āA�P�ɃV�[���ƌĂԂ��Ƃɂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>�������g�̃C���X�^���X(this����)�B�����́A�����̘b��̒��S�ƂȂ��Ă���V�[�������V�[���ɂȂ鎞������܂��B</TD>
 * </TR><TR>
 * <TD>�u�T�u�V�[���v�u�T�u�v�u�q�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA���V�[����<B>����</B>�Ԃ牺����P�K�w���̃V�[���B���w���Ă��܂��B<BR>
 * �V�[���N���X���p�������N���X�Ƃ����Ӗ��ł͖������ƂƂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u�V�[���z���v�u�z���v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA���V�[��<B>��</B>�Ԃ牺����S�ẴV�[���B���w���Ă��܂��B�T�u�V�[�������R�܂܂�܂��B<BR>
 * �V�[���N���X���p�����N���X�Ƃ����Ӗ��ł͖������ƂƂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u�e�V�[���v�u�e�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA���V�[��<B>��</B>���ڈ����͊ԐړI�ɂԂ牺�����Ă���V�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>���V�[���ȊO�̃V�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�c���[�v</TD>
 * <TD>�V�[�����m���c���[�K�w�\���ɂ���ĘA������Ă���1�̂܂Ƃ܂��\�����錾�t�B</TD>
 * </TR><TR>
 * <TD>�u�������c���[�v</TD>
 * <TD>���V�[�����܂܂�Ă��镔���c���[(�����̓c���[�S��)�̊K�w�\�����w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�v</TD>
 * <TD>���V�[���𒸓_�Ƃ���A���V�[���{���V�[���z���̃c���[�K�w�\�����w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�V�[���v</TD>
 * <TD>���c���[�̃V�[���B�܂莩�V�[���{���V�[���z���̃V�[���S�Ă��w���܂��B���V�[�����c���[�̒��_�i�ł��e�j�Ɉʒu���Ă��邱�Ƃ��Ӗ����Ă��܂�</TD>
 * </TR><TR>
 * <TD>�u�V�[���N���X�v</TD>
 * <TD>GgafActor�N���X�𒼐ځE�Ԑڌp�����Ă���N���X�S�ʂ��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u��ʃN���X�v�u���ʃN���X�v</TD>
 * <TD>�V�[���N���X�̃N���X�̌p���֌W��\���Ă��܂��B
 * �N���X�p���֌W�̕\���́u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�͎g�킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B<BR>
 * �u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�ƌ������ꍇ�̓c���[�K�w�\���̂��Ƃ������Ă��܂��B</TD>
 * </TR>
 * </TABLE>
 * <BR>
 * �{�N���X�͒��ۃN���X�ł��̂܂� new �ł��܂���B<BR>
 * �S�ẴV�[���N���X�́A�{�N���X�𒼐ځE�Ԑڌp�������Ȃ��Ƃ��ȉ��̉��z�֐����������Ȃ���΂Ȃ�܂���B<BR>
 * <BR>
 * void initialize() �E�E�E�������� <BR>
 * void processBehavior() �E�E�E�t���[�����̐U�镑������ <BR>
 * void processSettlementBehavior() �E�E�E�t���[�����̗l�X�Ȕ��菈���̎��O���������i�S�V�[���U�镑������������̏����j <BR>
 * void processJudgement() �E�E�E�t���[�����̗l�X�Ȕ��菈���̖{���� <BR>
 * void processPreDraw() �E�E�E�t���[�����̕`�掖�O���� <BR>
 * void processDraw() �E�E�E�t���[�����̕`��{���� <BR>
 * void processAfterDraw() �E�E�E�t���[�����̕`�掖�㏈�� <BR>
 * void processFinal() �E�E�E�t���[�����̏I�[���� <BR>
 * void onCatchEvent(UINT32 prm_no, void* prm_pSource) �E�E�E���̑��̃C�x���g������ <BR>
 * <BR>
 * @version 1.00
 * @since 2006/06/27
 * @author Masatoshi Tsuge
 */
class GgafScene : public GgafElement<GgafScene> {

    friend class GgafGod;
    friend class GgafUniverse;
    friend class GgafActor;
    friend class GgafGroupHead;
    friend class GgafDirector;

protected:

    /** ���̃V�[���̊ē� */
    GgafDirector* _pDirector;

public:

    frame _n_once;
    /**
     * �R���X�g���N�^ .
     * �����F prm_name �V�[����<BR>
     */
    GgafScene(const char* prm_name);

    /**
     * �f�X�g���N�^ .
     * ���V�[���̊ē̃c���[�A�N�^�[�̉�����s���Ă���B<BR>
     * ���c���[�V�[���̉�����s���܂�<BR>
     */
    virtual ~GgafScene();

    /**
     * ���t���[���ɂP����s���邩���w�� .
     * �X���[�ɂ��������Ɏg�p���邱�Ƃ�z��B<BR>
     * �K���1�B���{�i�s�B��ʃV�[����1�t���[���ŁA���g��1�t���[���i�ށB<BR>
     * 2 ��ݒ肷��� 1/2�{���i�s�B��ʃV�[����2�t���[����1�t���[���i�ށB<BR>
     * 3 ��ݒ肷��� 1/3�{���i�s�B��ʃV�[����3�t���[����1�t���[���i�ށB<BR>
     * 4 ��ݒ肷��� 1/4�{���i�s�B��ʃV�[����4�t���[����1�t���[���i�ށB<BR>
     * @param prm_n_once ���t���[���ɂP����s���邩
     */
    void setRunFrameOnce(frame prm_n_once) {
        _n_once = prm_n_once;
    }

    virtual void addSubLast(GgafScene* prm_pScene) override {
        GgafElement<GgafScene>::addSubLast(prm_pScene);
//        if(prm_pScene->_was_initialize_flg == false) {
//            prm_pScene->initialize();
//            prm_pScene->_was_initialize_flg = true;
//        }
    }

    virtual void nextFrame() override;
    virtual void behave() override;
    virtual void settleBehavior() override;
    virtual void judge() override;
    virtual void preDraw() override;
    virtual void draw() override;
    virtual void afterDraw() override;
    virtual void doFinally() override;
    virtual void throwEventToLowerTree(UINT32 prm_no, void* prm_pSource = NULL) override;
    virtual void throwEventToUpperTree(UINT32 prm_no, void* prm_pSource = NULL) override;
    virtual void activateTree() override;
    virtual void activateDelay(frame prm_offset_frames = 1) override;
    virtual void activate() override;
    virtual void activateTreeImmediately() override;
    virtual void activateImmediately() override;
    virtual void inactivateTree() override;
    virtual void inactivateDelay(frame prm_offset_frames = 1) override;
    virtual void inactivate() override;
    virtual void inactivateTreeImmediately() override;
    virtual void inactivateImmediately() override;

    virtual void pauseTree() override;
    virtual void pause() override;
    virtual void pauseTreeImmediately() override;
    virtual void pauseImmediately() override;

    virtual void unpauseTree() override;
    virtual void unpause() override;
    virtual void unpauseTreeImmediately() override;
    virtual void unpauseImmediately() override;

    virtual void reset() override;
    virtual void resetTree() override;

    virtual void executeFuncToLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) override;
    /**
     * ���c���[�V�[����n�t���[����ɃS�~���ֈړ� .
     * @param prm_offset_frames �S�~���ֈړ��^�C�~���O�c��t���[����(�f�t�H���g=1)
     */
    virtual void end(frame prm_offset_frames = 1) override;

    /**
     * ���c���[�𖖒[����J������B .
     * @param prm_num_cleaning �J���C���X�^���X��
     */
    virtual void clean(int prm_num_cleaning) override;

    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod() override;

    /**
     * ���V�[���̊ē��擾 .
     * @return	�ē�
     */
    virtual GgafDirector* getDirector();

    inline bool isActiveScene() {
         if (_can_live_flg && _is_active_flg) {
             return true;
         } else {
             return false;
         }
     }

    /**
     * �f�o�b�O�p�F�c���[�\����\�� .
     */
    virtual void dump();

    /**
     * �f�o�b�O�p�Fdump()����g�p����� .
     */
    virtual void dump(std::string prm_parent);
};

}
#endif /**GGAFSCENE_H_*/
