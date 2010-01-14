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
 * void processHappen(int prm_no) �E�E�E���̑��̃C�x���g���̏��� <BR>
 * bool processBumpChkLogic(GgafActor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N <BR>
 * void processOnHit(GgafActor* prm_pOtherActor) �E�E�E�Փ˔��胍�W�b�N��true�̏ꍇ�̏��� <BR>
 * <BR>
 * ���e���v���[�g�N���X�� GgafNode �ƁAGgafElement �̐������Q�Ƃ̂��ƁB<BR>
 * @version 1.00
 * @since 2007/11/20
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
    GgafActor* _pActor_tmp1;
    GgafActor* _pActor_tmp2;
    GgafActor* _pActor_tmp3;
    GgafActor* _pActor_tmp4;

    bool _use_octree;
    /**
     * �����V�[����ݒ肷��B .
     */
    void setScenePlatform(GgafScene* prm_pScene_Platform);

//    /**
//     * �y���A�N�^�[ �� ���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[�z�̏Փ˔��菈�������s���� .
//     * �{���\�b�h�� executeBumpChk2_WeAnd(GgafActor*)����Ăяo������p���\�b�h�B�ėp���͂Ȃ��B<BR>
//     * ���s����Ǝ��A�N�^�[��processHitLogic()���Ăяo���A���̌��ʂ�true�̏ꍇ(�Փ˂����ꍇ)�͎��g��processOnHit()�ƁA
//     * ����̃A�N�^�[��processOnHit()���Ăяo���B<BR>
//     * �߂�l�� bool �̓q�b�g����or���ĂȂ����Ӗ����镨�ł͂Ȃ��̂ŖY���ȁB<BR>
//     * @param	prm_pOtherActor	�Փ˔��肷�鎩�c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[
//     * @retval	true	�p�����[�^�����A�N�^�[
//     * @retval	false	�p�����[�^�����A�N�^�[�ȊO
//     */
//    bool executeBumpChk2_MeAnd(GgafActor* prm_pOtherActor);
//
//    /**
//     * �y���c���[�A�N�^�[ �� ���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[�z���ďՓ˔��菈��(executeBumpChk_MeAnd)�����s���� .
//     * executeBumpChk_RoundRobin2() ����Ăяo�����B<BR>
//     * executeBumpChk_WeAnd(GgafActor*)�Ɗ�{�I�ɓ����g�ݍ��킹�A���S���Y���ł��邪�A<BR>
//     * �K������Ă��鎩�A�N�^�[���m�����蔻��̃`�F�b�N���s���悤�ɂȂ��Ă��܂������_�ŗ��E���A<BR>
//     * ����ȏ�ċA���[�v���s��Ȃ��悤���Ă���B�c��̑g�ݍ��킹�͌㑱�̃��[�v�ŕ����B�i�n�Y�ł���j<BR>
//     * ���E���Ă����v�ȗ��R�́A���A�N�^�[�z�����m�̑�������ł��邽�߁A�P�����F�i�^�X�L�j�̑g�ݍ��킹�ōs����<BR>
//     *  Actor�@ �� Actor�A �@�@�i���͏Փ˔��肷��Ƃ����Ӗ��j<BR>
//     *  Actor�A �� Actor�@<BR>
//     * �̂悤�ɁA�Փ˔��菈�����d�����Ă��܂����߁A���������邽�ߓr���Ń��[�v���E����̂ł���B<BR>
//     * executeBumpChk_RoundRobin2() ��p���\�b�h�Ƃ����Ă��ǂ��B�ėp���͖����B<BR>
//     * �߂�l�� bool �̓q�b�g����or���ĂȂ����Ӗ����镨�ł͂Ȃ��̂ŖY���ȁB<BR>
//     * @param	prm_pOtherActor	�Փ˔��肷�鎩�c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[
//     * @retval	true	�ċA�����ł��؂�
//     * @retval	false	�ċA�������s
//     */
//    bool executeBumpChk2_WeAnd(GgafActor* prm_pOtherActor);

public:
    /** �A�N�^�[�̊K�� */
    int _actor_class; //1:GgafLoadActor 2:GgafGroupActor 3:GgafMainActor 0:���̑�


    /** �A�N�^�[�J�n�V�X�e������ */
    DWORD _start_system_time;

    /** �A�N�^�[�Փ˔���L���t���O */
    bool _can_bump_flg;

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

//    /**
//     * �I�[�o�[���C�h
//     */
//    virtual void addSubLast(GgafActor* prm_pSub) {
//        GgafElement<GgafActor>::addSubLast(prm_pSub);
//        if(prm_pSub->_was_initialize_flg == false) {
//            prm_pSub->initialize();
//            prm_pSub->_was_initialize_flg = true;
//        }
//    }

    /**
     * ���A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * @param	prm_can_bump_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     */
    void setBumpable(bool prm_can_bump_flg);

    /**
     * ���c���[�A�N�^�[�̏Փ˔���L����ݒ肷��B .
     * @param	prm_can_bump_flg  �Փ˔���L��(true:�Փ˔���L��^false:�Փ˔��薳��)
     */
    void setBumpableTree(bool prm_can_bump_flg);

    /**
     * �Փ˂ł��邩�ǂ���
     * @return	bool true:�Փ˂ł���^false:�Փ˂ł��Ȃ�
     */
    //bool canBump();
    inline bool canBump() {
        if (isActive() && _can_bump_flg) {
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

    inline void executeBumpChk_MeAnd(GgafActor* prm_pOtherActor) {
        if (prm_pOtherActor == this) {
            return;
        } else {
            if (_can_bump_flg &&
                prm_pOtherActor->_can_bump_flg &&
                _can_live_flg &&
                prm_pOtherActor->_can_live_flg &&
                _is_active_flg &&
                prm_pOtherActor->_is_active_flg)
            {
                if (processBumpChkLogic(prm_pOtherActor)) { //���g�̃q�b�g�`�F�b�N
                    processOnHit(prm_pOtherActor); //�����̃q�b�g���̐U�镑��
                    prm_pOtherActor->processOnHit(this); //����̃q�b�g���̐U�镑��
                }
            }
        }
    }

//    inline void executeBumpChk_WeAnd(GgafActor* prm_pOtherActor) {
//        executeBumpChk_MeAnd(prm_pOtherActor);
//        if (_pSubFirst != NULL) {
//            _pActor_tmp3 = _pSubFirst;
//            while (true) {
//                _pActor_tmp3->executeBumpChk_WeAnd(prm_pOtherActor);
//                if (_pActor_tmp3->_is_last_flg) {
//                    break;
//                } else {
//                    _pActor_tmp3 = _pActor_tmp3->_pNext;
//                }
//            }
//        }
//    }
//
//    inline void executeBumpChk_RoundRobin(GgafActor* prm_pOtherActor) {
//        executeBumpChk_WeAnd(prm_pOtherActor);
//        if (prm_pOtherActor->_pSubFirst != NULL) {
//            GgafActor* _pActor_tmpZ = prm_pOtherActor->_pSubFirst;
//            while (true) {
//                executeBumpChk_RoundRobin(_pActor_tmpZ);
//                if (_pActor_tmpZ->_is_last_flg) {
//                    break;
//                } else {
//                    _pActor_tmpZ = _pActor_tmpZ->_pNext;
//                }
//            }
//        }
//    }
//
//    inline bool executeBumpChk2_MeAnd(GgafActor* prm_pOtherActor) {
//        if (prm_pOtherActor == this) {
//            return true;
//        } else {
//            if (_can_bump_flg && prm_pOtherActor->_can_bump_flg && _can_live_flg && prm_pOtherActor->_can_live_flg && _is_active_flg
//                    && prm_pOtherActor->_is_active_flg) {
//                if (processBumpChkLogic(prm_pOtherActor)) { //���g�̃q�b�g�`�F�b�N
//                    processOnHit(prm_pOtherActor); //�����̃q�b�g���̐U�镑��
//                    prm_pOtherActor->processOnHit(this); //����̃q�b�g���̐U�镑��
//                }
//            }
//            return false;
//        }
//    }
//
//    inline bool executeBumpChk2_WeAnd(GgafActor* prm_pOtherActor) {
//        bool ret1 = executeBumpChk2_MeAnd(prm_pOtherActor);
//        bool ret2;
//        if (ret1) {
//            return true;
//        } else {
//            if (_pSubFirst != NULL) {
//                _pActor_tmp4 = _pSubFirst;
//                while (true) {
//                    ret2 = _pActor_tmp4->executeBumpChk2_WeAnd(prm_pOtherActor);
//                    if (ret2) {
//                        return true;
//                    } else {
//                        if (_pActor_tmp4->_is_last_flg) {
//                            break;
//                        } else {
//                            _pActor_tmp4 = _pActor_tmp4->_pNext;
//                        }
//                    }
//                }
//            }
//            return false;
//        }
//    }
//
//    inline void executeBumpChk_RoundRobin2(GgafActor* prm_pOtherActor) {
//        executeBumpChk2_WeAnd(prm_pOtherActor);
//        if (prm_pOtherActor->_pSubFirst != NULL) {
//            GgafActor* pActor_tmpZ2 = prm_pOtherActor->_pSubFirst;
//            while (true) {
//                executeBumpChk_RoundRobin2(pActor_tmpZ2);
//                if (pActor_tmpZ2->_is_last_flg) {
//                    break;
//                } else {
//                    pActor_tmpZ2 = pActor_tmpZ2->_pNext;
//                }
//            }
//        }
//    }

//
//    /**
//     * �y���A�N�^�[ �� ���A�N�^�[�z�̏Փ˔��菈�������s���� .
//     * ���g��processHitLogic()�̌��ʁA�Փ˂����ꍇ(true)�͎��g��processOnHit()�ƁA����A�N�^�[��processOnHit()�����s����� <BR>
//     * �A���A�����ɁA���g�̃|�C���^��n���Ă͂����Ȃ��B<BR>
//     * @param	prm_pOtherActor	����̑��A�N�^�[
//     */
//    void executeBumpChk_MeAnd(GgafActor* prm_pOtherActor);
//
//    /**
//     * �y���c���[�A�N�^�[ �� ���A�N�^�[�z�̏Փ˔��菈�������s���� .
//     * �����I�ɂ́A���c���[�A�N�^�[ �S�Ăɂ��āAexecuteBumpChk_MeAnd(GgafActor*) ���������s�B<BR>
//     * �A���A�����ɁA���c���[�A�N�^�[�����̃A�N�^�[�̃|�C���^��n���Ă͂����Ȃ��B<BR>
//     * @param	prm_pOtherActor	����̑��A�N�^�[
//     */
//    void executeBumpChk_WeAnd(GgafActor* prm_pOtherActor);
//
//    /**
//     * �y���c���[�A�N�^�[ �� ���c���[�A�N�^�[�z�̑�������ŏՓ˔�������s���� .
//     * �����I�ɂ́A�����ł��� ���c���[�A�N�^�[ �̑S�Ăɂ��āAexecuteBumpChk_WeAnd(GgafActor*) ���������s���Ă��邾���B<BR>
//     * �A���A���c���[�ɂ����c���[�ɂ������ɏ������Ă���A�N�^�[�������Ă͂����Ȃ��B<BR>
//     * @param	prm_pOtherActor	����̑��c���[�A�N�^�[
//     */
//    void executeBumpChk_RoundRobin(GgafActor* prm_pOtherActor);
//
//    /**
//     * �y���c���[�A�N�^�[ �� ���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[�𒸓_�Ƃ���c���[�A�N�^�[�z�̑�������ŏՓ˔�������s����B.
//     * �����I�ɂ́A�����̃A�N�^�[ �̑S�Ăɂ��āAexecuteBumpChk2_WeAnd(GgafActor*) ���������s���Ă��邾���B<BR>
//     * �A�����A�N�^�[���m�̏d���g�ݍ��킹�𖳎�����B <BR>
//     * @param	prm_pOtherActor	���c���[�A�N�^�[�̂ǂꂩ1�̃A�N�^�[
//     */
//    void executeBumpChk_RoundRobin2(GgafActor* prm_pOtherActor);
//
    /**
     * ���A�N�^�[�Ɖ����̃A�N�^�[�ƏՓ˂������ǂ������肷��B .
     * executeBumpChk_MeAnd(GgafActor*) �����s���ꂽ�ꍇ�ɌĂяo����邱�ƂɂȂ�B<BR>
     * ���ʃN���X�ŏՓ˔��胍�W�b�N����������B<BR>
     * ���̃��\�b�h�͉����Ăяo����邩�͌��܂��Ă��Ȃ��B�Ăяo���^�C�~���O�����ʃN���X�Ŏ�������B<BR>
     * �z��Ƃ��ẮAprocessJudgement() ���\�b�h�����������N���X���A���̒��Ŗ{���\�b�h���Ăяo�����̂Ƃ��Ă���B<BR>
     * �������̂悤�Ɏ��������ꍇ�A����A�N�^�[�� processJudgement() �ł�����̃A�N�^�[�Ƃ̏Փ˔�����s�����ƂɂȂ�΁A<BR>
     * �Փ˔��菈���d�����邱�ƂɂȂ�B���̓_�𗯈ӂ��A�ǁ[������悢���l���邱�ƁB<BR>
     * @param	prm_pOtherActor	����A�N�^�[
     * @retval	true	�Փ˂��Ă����Ԃ���
     * @retval	false	�Փ˂��Ă��Ȃ���Ԃ���
     */
    virtual bool processBumpChkLogic(GgafActor* prm_pOtherActor) {
        return false;
    }

    /**
     * �A�N�^�[�ƏՓ˂������̏��� .
     * processBumpChkLogic(GgafActor*) �� true �̏ꍇ�ɌĂяo����邱�ƂɂȂ�܂��B<BR>
     * �Փ˔���̌��ʁA�Փ˂����ꍇ�̏��������ʃN���X�������Ă��������B<BR>
     * @param	prm_pOtherActor	�Փ˂��Ă��鑊��̃A�N�^�[�i�P�j
     */
    virtual void processOnHit(GgafActor* prm_pOtherActor) {}

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
