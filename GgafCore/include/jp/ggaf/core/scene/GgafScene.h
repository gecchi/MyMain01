#ifndef GGAFSCENE_H_
#define GGAFSCENE_H_

#define SCENE_PROG_NEW -1
#define SCENE_NOTHING_EVENT 0

namespace GgafCore {

/**
 * �V�[���N���X .
 * �{�v���O�����ł́w�V�[���i��ʁj�x�Ƃ́A�Ǘ���(GgafLoadActor)���Ǘ�����I�u�W�F�N�g�ł��B<BR>
 * �e�V�[���́A�K���P�̊Ǘ��҂������o�Ƃ��ĕێ����Ă��܂��B<BR>
 * �S�ẴV�[���N���X�́A�{�N���X�𒼐ځE�Ԑڌp�����Ȃ���΂Ȃ�܂���B<BR>
 * �܂��A�V�[�����m�̃|�C���^�ŁA�c���[�K�w�\�����̂鎖���ł��܂��B�i���̃c���[�\���̓N���X�̌p���Ƃ͊֌W����܂���j<BR>
 * �V�[���Ɏ�������Ă��郁�\�b�h�S�̂قƂ�ǂ́A�������g�Ǝ����z���̃V�[���i���c���[�V�[���j�S�Ăɉe������d�l�ɂȂ��Ă��܂��B<BR>
 * �Q�[�����I�u�W�F�N�g�w���ŕ\�����邽�߁A�l�X�ȁw�V�[���i��ʁj�x�Łw�A�N�^�[(�L����)�x���������􂷂�A�C���[�W�Ő݌v���Ă���܂��B<BR>
 * <B>�y�p��⑫�z</B>
 * <TABLE border='1'>
 * <TR>
 * <TD>�u�V�[���v</TD>
 * <TD>�V�[���N���X�̃C���X�^���X�i�I�u�W�F�N�g�j���ȗ����āA�P�ɃV�[���ƌĂԂ��Ƃɂ��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>���\�b�h�����s�����V�[���I�u�W�F�N�g���g���w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�T�u�V�[���v�u�T�u�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA�V�[����<B>����</B>�Ԃ牺����P�K�w���̃V�[���B���w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�V�[���z���v�u�z���v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA�V�[��<B>��</B>�Ԃ牺����S�ẴV�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�e�V�[���v�u�e�v</TD>
 * <TD>�V�[�����m�̃c���[�K�w�\����ɂ����āA���V�[��<B>��</B>���ڈ����͊ԐړI�ɂԂ牺�����Ă���V�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u���V�[���v�u���v</TD>
 * <TD>���V�[���ȊO�̃V�[�����w���Ă��܂��B</TD>
 * </TR><TR>
 * <TD>�u�c���[�v</TD>
 * <TD>�V�[�����m���c���[�K�w�\���ɂ���ĘA������Ă���1�̂܂Ƃ܂���w���܂��B</TD>
 * </TR><TR>
 * <TD>�u�������c���[�v</TD>
 * <TD>���V�[�����܂܂�Ă���c���[�\�������S�Ďw���܂��B<</TD>
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
 * <TD>�V�[���N���X�̃N���X�p���֌W��\���Ă��܂��B
 * �N���X�p���֌W�̕\���́u�X�[�p�[�v�u�T�u�v���́u�e�v�u�q�v�ƌ��킸��<B>�u��ʁv�u���ʁv</B>�œ��ꂷ�邱�Ƃɂ��܂��B</TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafScene : public GgafElement<GgafScene> {

    friend class GgafGod;
    friend class GgafWorld;
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
    DWORD _dwFrame_ProgressChange[100];

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
        return _dwFrame_ProgressChange[prm_progress];
    }

    /**
     * �i����ݒ� .
     * @param prm_progress �i��(1�`99)
     */
    virtual void setProgress(int prm_progress) {
        _progress_nextframe = prm_progress;
        _dwFrame_ProgressChange[prm_progress] = _dwFrame+1;
    }

    bool isChangeProgress(int prm_progress) {
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

    virtual void nextFrame();
    virtual void behave();
    virtual void judge();
    virtual void drawPrior();
    virtual void drawMain();
    virtual void drawTerminate();
    virtual void finally();

    virtual void happen(int prm_no);

    virtual void act();
    virtual void actAfter(DWORD prm_dwFrameOffset);
    virtual void actAlone();
    virtual void actImmediately();
    virtual void actImmediatelyAlone();

    virtual void refrain();
    virtual void refrainAfter(DWORD prm_dwFrameOffset);
    virtual void refrainAlone();
    virtual void refrainImmediately();
    virtual void refrainImmediatelyAlone();

    virtual void pause();
    virtual void pauseAlone();
    virtual void pauseImmediately();
    virtual void pauseImmediatelyAlone();

    virtual void unpause();
    virtual void unpauseAlone();
    virtual void unpauseImmediately();
    virtual void unpauseImmediatelyAlone();

    virtual void blind();
    virtual void blindAlone();
    virtual void blindImmediately();
    virtual void blindImmediatelyAlone();

    virtual void unblind();
    virtual void unblindAlone();
    virtual void unblindImmediately();
    virtual void unblindImmediatelyAlone();


    /**
     * ���c���[�V�[�������t���[���▽������B .
     * ��OverRide �ł���<BR>
     */
    virtual void farewell(DWORD prm_dwFrameOffset = 0);

    /**
     * ���c���[�V�[����▽������B .
     * ��OverRide �ł���<BR>
     */
    virtual void cleane(int prm_iNumCleanNode);

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
     * GgafActor#executeBumpChkRoundRobin�����s����B<BR>
     * @param	prm_actor_kind_name01	���肷��Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor��ʖ�
     * 		    prm_actor_kind_name02	���肳���Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor��ʖ�<BR>
     */
    //virtual void executeBumpChkHeadActors(std::string prm_actor_kind_name01, std::string prm_actor_kind_name02);


    /**
     * ���c���[�V�[���̃A�N�^�[�ɏՓ˔�������s �i�����ق��j.
     * ���c���[�V�[���S�Ăɑ΂��āA�e�V�[���ɏ�������Ǘ��҂̃T�u�A�N�^�[�ł��� GgafHeadActor �S�Ăɑ΂���<BR>
     * GgafActor#executeBumpChkRoundRobin�����s����B<BR>
     * @param	prm_actorkind01	���肷��Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor���
     * 		    prm_actorkind01	���肳���Ώۂ�GgafHeadActor�ɓo�^����Ă���Actor���<BR>
     */
    virtual void executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02);

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
