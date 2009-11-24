#ifndef GGAFSCENE_H_
#define GGAFSCENE_H_

#define SCENE_PROG_NEW -1
#define SCENE_NOTHING_EVENT 0

namespace GgafCore {

/**
 * �V�[���N���X .
 * �{�v���O�����ł́w�V�[���x�Ƃ́A�A�v����ł́u��ʁv�Ƃ����T�O���u����Z�܂������́v�ƍl���A�؂蕪����ꂽ�I�u�W�F�N�g�������܂��B<BR>
 * �{�N���X�͂��̂܂� new �ł��܂���B���ځE�Ԑڌp�����Ď�������K�v������܂��B<BR>
 * �@�\�Ƃ��āA�V�[�����m�̃|�C���^�ڍ����A�c���[�K�w�\�����̂鎖���ł��܂��B�i���̃c���[�\���̓N���X�̌p���Ƃ͊֌W����܂���j<BR>
 * �V�[���Ɏ�������Ă��郁�\�b�h�S�̂قƂ�ǂ́A�������g�Ǝ����z���̃V�[���i���c���[�V�[���j�S�Ăɉe������d�l�ɂȂ��Ă��܂��B<BR>
 * �Q�[���i�A�v���j�Ƃ������̂́A<BR>
 * �u�l�X�ȁw�V�[���i��ʁj�x�Łw�A�N�^�[(�L����)�x���������􂷂���̂ł���B�v<BR>
 * �Ƃ��������͋��ʉ��ł���ƐM���Đ݌v���Ă���܂��B �A�v���S�̂����Ƀ��[�r�[���Đ����Ă�����̂ƍl�����ꍇ�A�V�[���I�u�W�F�N�g�Ƃ́A<BR>
 * ���C���[�i�����̃Z���j�̂悤�ȕ��ɂ�����Ƃ����l�����ł��B<BR>
 * �܂��A�V�[���N���X�͊Ǘ��҃A�N�^�[(GgafLoadActor)���Ǘ�����N���X�ł�����܂��B �Ǘ��҃A�N�^�[�Ƃ̓V�[�����̃A�N�^�[�̑�e���̂悤�Ȃ��́A<BR>
 * GgafLoadActor ���Q�Ƃ��ĉ������B<BR>
 * �e�V�[���́A�K���P�̊Ǘ��҂������o�Ƃ��ĕێ����Ă��܂��B<BR>
 *
 * <B>�y�p��⑫�z</B>
 * <TABLE border='1'>
 * <TR>
 * <TD>�u�V�[���v</TD>
 * <TD>�V�[���N���X�̃C���X�^���X�i�I�u�W�F�N�g�j���ȗ����āA�P�ɃV�[���ƌĂԂ��Ƃɂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>���\�b�h�����s�����V�[���I�u�W�F�N�g���g���w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�T�u�V�[���v�u�T�u�v�u�q�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA�V�[����<B>����</B>�Ԃ牺����P�K�w���̃V�[���B���w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�V�[���z���v�u�z���v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA�V�[��<B>��</B>�Ԃ牺����S�ẴV�[�����w���Ă��܂��B�T�u���܂܂�܂��B</TD>
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
 * <TD>���V�[�����܂܂�Ă���c���[���w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�v</TD>
 * <TD>���V�[���𒸓_�Ƃ���A���V�[���{���V�[���z���̃c���[�K�w�\���������w���܂��B</TD>
 * </TR><TR>
 * <TD>�u���c���[�V�[���v</TD>
 * <TD>���V�[���{���V�[���z���̃V�[���S�Ă��w���܂��B���V�[�������c���[�̒��_�i�ł��e�j�Ɉʒu���Ă��邱�Ƃ��Ӗ����Ă��܂�</TD>
 * </TR><TR>
 * <TD>�u�V�[���N���X�v</TD>
 * <TD>GgafActor�N���X�𒼐ځE�Ԑڌp�����Ă���N���X�S�ʂ��w���܂��B</TD>
 * </TR><TR>
 * <TD>�u��ʁv�u���ʁv</TD>
 * <TD>�V�[���N���X�̃N���X�̌p���֌W��\���Ă��܂��B
 * �N���X�p���֌W�̕\���́u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�ƌ��킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B<BR>
 * �u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�ƌ������ꍇ�̓c���[�K�w�\���̂��Ƃ������Ă��܂��B</TD>
 * </TR>
 * </TABLE>
 * <BR>
 * �{�N���X�͒��ۃN���X�ł��̂܂� new �ł��܂���B<BR>
 * �S�ẴV�[���N���X�́A�{�N���X�𒼐ځE�Ԑڌp�������Ȃ��Ƃ��ȉ��̉��z�֐����������Ȃ���΂Ȃ�܂���B<BR>
 * <BR>
 * void initialize() �E�E�E�������� <BR>
 * void processBehavior() �E�E�E�t���[�����̐U�镑������ <BR>
 * void processJudgement() �E�E�E�t���[�����̗l�X�Ȕ��菈���i�S�V�[���U�镑������������̏����j <BR>
 * void processPreDraw() �E�E�E�t���[�����̕`�掖�O���� <BR>
 * void processDraw() �E�E�E�t���[�����̕`��{���� <BR>
 * void processAfterDraw() �E�E�E�t���[�����̕`�掖�㏈�� <BR>
 * void processFinal() �E�E�E�t���[�����̏I�[���� <BR>
 * void processHappen(int prm_no) �E�E�E���̑��̃C�x���g������ <BR>
 * <BR>
 * @version 1.00
 * @since 2006/06/27
 * @author Masatoshi Tsuge
 */
class GgafScene : public GgafElement<GgafScene> {

    friend class GgafGod;
    friend class GgafUniverse;
    friend class GgafActor;
    friend class GgafHeadActor;
    friend class GgafLordActor;

protected:

    /** ���̃V�[���̊Ǘ��� */
    GgafLordActor* _pLordActor;

    static GgafHeadActor* _apHeadActor01[];
    static GgafHeadActor* _apHeadActor02[];

public:
    /** �i��� */
    int _progress;
    /** �P�t���[���O�i�� */
    int _progress_prev;
    /** ���t���[���ݒ肷��i��� */
    int _progress_nextframe;

    /** �i���C�x���g���t���[���X�g�b�N */
    DWORD _aFrame_ProgressChange[100];

    /**
     * ���݂̐i���擾 .
     * @return �i��(1�`99)
     */
    virtual int getProgress() {
        return _progress;
    }

    /**
     * �i�����N���������̃t���[���擾 .
     * @param prm_progress �i��(1�`99)
     * @return �����̒��߂̐i�����N�������Ƃ��̃t���[��
     */
    virtual DWORD getFrameAtProgress(int prm_progress) {
        return _aFrame_ProgressChange[prm_progress];
    }

    /**
     * �i����ݒ� .
     * @param prm_progress �i��(1�`99)
     */
    virtual void setProgress(int prm_progress) {
        _progress_nextframe = prm_progress;
        _aFrame_ProgressChange[prm_progress] = _lifeframe+1;
    }

    bool onChangeProgressAt(int prm_progress) {
        if (_progress != _progress_prev) {
            if (prm_progress == _progress) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    /**
     * �i�����ω����������ׂ� .
     * @return 0 ���� �i��(0=�ω����Ă��Ȃ�/0�ȊO=�ω����������V�����i��)
     */
    int getProgressOnChange() {
        if (_progress != _progress_prev) {
            return _progress;
        } else {
            return 0; // = false
        }
    }

    /**
     * �R���X�g���N�^ .
     * �����F prm_name �V�[����<BR>
     */
    GgafScene(const char* prm_name);

    /**
     * �f�X�g���N�^ .
     * ���V�[���̊Ǘ��҂̃c���[�A�N�^�[�̉�����s���Ă���B<BR>
     * ���c���[�V�[���̉�����s���܂�<BR>
     */
    virtual ~GgafScene();

    /**
     * �I�[�o�[���C�h
     */
    virtual void addSubLast(GgafScene* prm_pScene) {
        GgafElement<GgafScene>::addSubLast(prm_pScene);
        if(prm_pScene->_was_initialize_flg == false) {
            prm_pScene->initialize();
            prm_pScene->_was_initialize_flg = true;
        }
    }

    virtual void nextFrame();
    virtual void behave();
    virtual void preJudge();
    virtual void judge();
    virtual void preDraw();
    virtual void draw();
    virtual void afterDraw();
    virtual void finally();

    virtual void happen(int prm_no);

    virtual void activateTree();
    virtual void activateAfter(DWORD prm_frame_offset);
    virtual void activate();
    virtual void activateTreeImmediately();
    virtual void activateImmediately();

    virtual void inactivateTree();
    virtual void inactivateAfter(DWORD prm_frame_offset);
    virtual void inactivate();
    virtual void inactivateTreeImmediately();
    virtual void inactivateImmediately();

    virtual void pauseTree();
    virtual void pause();
    virtual void pauseTreeImmediately();
    virtual void pauseImmediately();

    virtual void unpauseTree();
    virtual void unpause();
    virtual void unpauseTreeImmediately();
    virtual void unpauseImmediately();

    /**
     * ���c���[�V�[�������t���[���▽������B .
     * ��OverRide �ł���<BR>
     */
    virtual void adios(DWORD prm_frame_offset = 0);

    /**
     * ���c���[�V�[����▽������B .
     * ��OverRide �ł���<BR>
     */
    virtual void cleane(int prm_num_cleaning);

    /**
     * �_�ɉy�� .
     * @return	�Ă΂�ďo�Ă����_
     */
    virtual GgafGod* askGod();

    /**
     * ���V�[���̊Ǘ��҂��擾 .
     * @return	�Ǘ���
     */
    virtual GgafLordActor* getLordActor();

    /**
     * ���c���[�V�[���̃A�N�^�[�ɏՓ˔�������s (�x�����B�������getName()��std::string��r�Ȃ̂ł��x���B���̃��\�b�h���g�������ǂ����[).
     * ���c���[�V�[���S�Ăɑ΂��āA�e�V�[���ɏ�������Ǘ��҂̃T�u�A�N�^�[�ł��� GgafHeadActor �S�Ăɑ΂���<BR>
     * GgafActor#executeBumpChk_RoundRobin�����s����B<BR>
     * @param	prm_actor_kind_name01	���肷��Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor��ʖ�
     * 		    prm_actor_kind_name02	���肳���Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor��ʖ�<BR>
     */
    //virtual void executeBumpChkHeadActors(std::string prm_actor_kind_name01, std::string prm_actor_kind_name02);


    /**
     * ���c���[�V�[���̃A�N�^�[�ɏՓ˔�������s �i�����ق��j.
     * ���c���[�V�[���S�Ăɑ΂��āA�e�V�[���ɏ�������Ǘ��҂̃T�u�A�N�^�[�ł��� GgafHeadActor �S�Ăɑ΂���<BR>
     * GgafActor#executeBumpChk_RoundRobin�����s����B<BR>
     * @param	prm_actorkind01	���肷��Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor���
     * 		    prm_actorkind01	���肳���Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor���<BR>
     */
    //virtual void executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02);
    /**
     * �o�߃t���[������B .
     * ���O�� delay(n) ���s���i���ʂ�true/false�Ɋւ�炸�j�̃t���[��������̌o�߃t���[�����ɒB���������肷��B<BR>
     * ���ӁF����q�Ŏg�p�����ꍇ�͂��܂������܂���B<BR>
     * @param	prm_dwFrame_delay	�o�߃t���[����
     * @return	bool	true:�o�߃t���[�����ɒB����/false:�B���Ă��Ȃ�
     */
    //	virtual bool delayed(_delay);

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
