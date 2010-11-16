#ifndef GGAFACTOR_H_
#define GGAFACTOR_H_

#define LORDACTOR  1
#define GROUPACTOR  2
#define MAINACTOR  3

#define STAT_DEFAULT_ACTOR_KIND 0


namespace GgafCore {


/**
 * �A�N�^�[�̊��N���X .
 * �{�v���O�����Ō����w�A�N�^�[�x�Ƃ́A��ɃL�����N�^�[��\������B<BR>
 * �e�V�[��(GgafScene)�ɏ������A���􂷂�C���[�W�B<BR>
 * GgafElement �ɓ����蔻�����������d�g�݂��������N���X�ɂȂ��Ă���B<BR>
 * �{�N���X�͒��ۃN���X�ł��̂܂� new �͂ł��Ȃ��B<BR>
 * �S�ẴA�N�^�[�N���X�́A�{�N���X���p�������Ȃ��Ƃ��ȉ��̏������z�֐�����������K�v������B<BR>
 * <BR>
 * ���P�x�����Ăяo����鏃�����z�֐���<BR>
 * void initialize() �E�E�E�������� <BR>
 * ���ʏ�A���t���[���Ăяo����鏃�����z�֐���<BR>
 * void processBehavior() �E�E�E�t���[�����̐U�镑�������i���W�ړ����j <BR>
 * void processJudgement() �E�E�E�t���[�����̗l�X�Ȕ��菈���i�S�A�N�^�[�U�镑��������̏����j <BR>
 * void processPreDraw() �E�E�E�t���[�����̕`�掖�O���� <BR>
 * void processDraw() �E�E�E�t���[�����̕`��{���� <BR>
 * void processAfterDraw() �E�E�E�t���[�����̕`�掖�㏈�� <BR>
 * void processFinal() �E�E�E�t���[�����̏I�[���� <BR>
 * �����t���[���Ăяo�����킯�ł͂Ȃ��������z�֐���<BR>
 * void onCatchEvent(UINT32 prm_no, void* prm_pSource) �E�E�E���̑��̃C�x���g���̏��� <BR>
 * bool processHitChkLogic(GgafActor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N <BR>
 * void onHit(GgafActor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N��true�̏ꍇ�̏��� <BR>
 * <BR>
 * ���e���v���[�g�N���X�� GgafNode �ƁAGgafElement �̐������Q�Ƃ̂��ƁB<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafActor : public GgafElement<GgafActor> {

    friend class GgafGod;
    friend class GgafMainActor;
    friend class GgafLordActor;
    friend class GgafGroupActor;
    friend class GgafDummyActor;
    friend class GgafScene;
    friend class GgafUniverse;

private:

    /** ���݂̏����V�[�� */
    GgafScene* _pScene_Platform;

    /** ���[�v�p */
    GgafActor* _pActor_tmp;
    /** �W���ؓo�^���s�����ǂ����̃t���O */
    bool _use_octree;

    /**
     * �����V�[����ݒ肷��B .
     */
    void setScenePlatform(GgafScene* prm_pScene_Platform);

public:
    /** [r]�����f�B�X�p�b�`���[(NULL�͖�����) */
    GgafActorDispatcher* _pDependenceDispcher;
    /** [r]�A�N�^�[�J�n�V�X�e������ */
    UINT32 _start_system_time;
    /** [r]�A�N�^�[�Փ˔���L���t���O */
    bool _can_hit_flg;
    /** [r]���R�X�e�[�^�X */
    GgafStatus* _pStatus;

    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[�̖��O
     */
    GgafActor(const char* prm_name);

    /**
     * �f�X�g���N�^ .
     * ���c���[�A�N�^�[�̉�����s���܂��B
     */
    virtual ~GgafActor();

    /**
     * ���A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * @param	prm_can_hit_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     */
    void setHitAble(bool prm_can_hit_flg);

    /**
     * ���c���[�A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * @param	prm_can_hit_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     */
    void setHitAbleTree(bool prm_can_hit_flg);

    /**
     * ���ݏՓ˂ł���󋵂��ǂ������� .
     * ���ӁF�Փ˔\�͂����邩�ǂ����ł͖����B
     * @return	bool true:�Փˉ\�󋵁^false:�Փ˕s�\��
     */
    inline bool canHit() {
        if (isActive() && _can_hit_flg) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �������Ă���V�[�����擾�B .
     * @return	GgafScene*	�������Ă���V�[��
     */
    virtual GgafScene* getPlatformScene();

    /**
     * ���A�N�^�[�Ƒ��A�N�^�[�̂P�΂P�̓����蔻�菈�����s���B
     * @param prm_pOtherActor ���A�N�^�[
     */
    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
        if (prm_pOtherActor == this) {
            return;
        } else {
            if (canHit() && prm_pOtherActor->canHit() &&
                _can_live_flg && prm_pOtherActor->_can_live_flg ) {
                if (processHitChkLogic(prm_pOtherActor)) { //���g�̃q�b�g�`�F�b�N
                    onHit(prm_pOtherActor); //�����̃q�b�g���̐U�镑��
                    prm_pOtherActor->onHit(this); //����̃q�b�g���̐U�镑��
                }
            }
        }
    }


    /**
     * ���A�N�^�[�Ɖ����̃A�N�^�[�ƏՓ˂������ǂ������肷�郍�W�b�N�B .
     * executeHitChk_MeAnd(GgafActor*) �����s���ꂽ�ꍇ�ɌĂяo����邱�ƂɂȂ�B<BR>
     * ���ʃN���X�œƎ��ɏՓ˔��胍�W�b�N����������B<BR>
     * ���̃��\�b�h�͉����Ăяo����邩�͌��܂��Ă��Ȃ��B�Ăяo���^�C�~���O�����ʃN���X�ˑ��B<BR>
     * �z��Ƃ��ẮAprocessJudgement() ���\�b�h�����������N���X���A���̒��Ŗ{���\�b�h���Ăяo�����̂Ƃ��Ă���B<BR>
     * �������̂悤�Ɏ��������ꍇ�A����A�N�^�[�� processJudgement() �ł�����̃A�N�^�[�Ƃ̏Փ˔�����s�����ƂɂȂ�΁A<BR>
     * �Փ˔��菈���d�����邱�ƂɂȂ�B�ǁ[������悢���l���邱�ƁB<BR>
     * @param	prm_pOtherActor	����A�N�^�[
     * @retval	true	�Փ˂��Ă����Ԃ���
     * @retval	false	�Փ˂��Ă��Ȃ���Ԃ���
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) {
        return false;
    }

    /**
     * �A�N�^�[�ƏՓ˂������̏��� .
     * processHitChkLogic(GgafActor*) �� true �̏ꍇ�ɌĂяo����邱�ƂɂȂ�܂��B<BR>
     * �Փ˔���̌��ʁA�Փ˂����ꍇ�̏��������ʃN���X�������Ă��������B<BR>
     * @param	prm_pOtherActor	�Փ˂��Ă��鑊��̃A�N�^�[�i�P�j
     */
    virtual void onHit(GgafActor* prm_pOtherActor) {}

    /**
     * Dispcher�ɏ������Ă���ꍇ�A�����Ԃ��B
     * �������̏ꍇNULL
     * @return ����Dispcher
     */
    GgafActorDispatcher* getDependenceDispcher() {
        return _pDependenceDispcher;
    }

    /**
     * ����Ȃ炵�܂� .
     * Dispcher�ɏ������Ă���ꍇ�� inactiveAfter(prm_frame_offset) <BR>
     * Dispcher�ɏ������Ă��Ȃ��ꍇ�� end(prm_frame_offset) <BR>
     * ���A���s����܂��B
     * �A�N�^�[���V�[�����痣�E���������ꍇ�͂��̃��\�b�h�����s���邱�ƁB
     * @param prm_frame_offset �P�\�t���[��(1�`)
     */
    virtual void sayonara(frame prm_frame_offset = 1);



    /**
     * �f�o�b�O�p�F�c���[�\����\��<BR>
     */
    virtual void dump();

    /**
     * �f�o�b�O�p�Fdump()����g�p�����<BR>
     */
    virtual void dump(std::string prm_parent);

};

}
#endif /**GGAFACTOR_H_*/
