#ifndef GGAF_CORE_CHECKER_H_
#define GGAF_CORE_CHECKER_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/actor/Actor.h"
#include "jp/ggaf/core/util/lineartree/ITreeNodeElem.hpp"

#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * �`�F�b�N�N���X.
 * �����ؗv�f�ɂȂ�܂��B
 * @version 1.00
 * @since 2024/09/26
 * @author Masatoshi Tsuge
 */
class Checker : public Object, public ITreeNodeElem {

public:
    Actor* const _pActor;
    /** �g�� */
    Checker* _pNextChecker;
    /**
     * �X�e�[�^�X�Z�b�g���쐬 .
     * ���Z�b�g���\�b�h�����s���X�e�[�^�X���������s���܂��B
     * @param prm_pFunc_reset �X�e�[�^�X���Z�b�g���\�b�h
     */
    Checker(Actor* prm_pActor);

    /**
     * ���`�F�b�J�[�Ƒ��`�F�b�J�[�̂P�΂P�̓����蔻�菈�����s���B
     * @param prm_pOtherActor ���A�N�^�[
     */
    virtual void executeHitChk_MeAnd(Checker* prm_pOtherChecker) {
        if (prm_pOtherChecker == this) {
            return;
        } else {
            //�q�b�g�ł��镨�ǂ����̔���͎��O�ɂ���ł���悤�ɂ��鎖�B
            if (processHitChkLogic(prm_pOtherChecker)) { //���g�̃q�b�g�`�F�b�N
                _pActor->onHit(prm_pOtherChecker, prm_pOtherChecker->_pActor); //�����̃q�b�g���̐U�镑��
                prm_pOtherChecker->_pActor->onHit(this, _pActor); //����̃q�b�g���̐U�镑��
            }
        }
    }

    /**
     * ���A�N�^�[�Ɖ����̃A�N�^�[�ƏՓ˂������ǂ������肷�郍�W�b�N�B .
     * executeHitChk_MeAnd(Actor*) �����s���ꂽ�ꍇ�ɌĂяo����邱�ƂɂȂ�B<BR>
     * ���ʃN���X�œƎ��ɏՓ˔��胍�W�b�N����������B<BR>
     * ���̃��\�b�h�͉����Ăяo����邩�͌��܂��Ă��Ȃ��B�Ăяo���^�C�~���O�����ʃN���X�ˑ��B<BR>
     * �z��Ƃ��ẮAprocessJudgement() ���\�b�h�����������N���X���A���̒��Ŗ{���\�b�h���Ăяo�����̂Ƃ��Ă���B<BR>
     * �������̂悤�Ɏ��������ꍇ�A����A�N�^�[�� processJudgement() �ł�����̃A�N�^�[�Ƃ̏Փ˔�����s�����ƂɂȂ�΁A<BR>
     * �Փ˔��菈���d�����邱�ƂɂȂ�B�ǁ[������悢���l���邱�ƁB<BR>
     * @param	prm_pOtherChecker�@����`�F�b�J�[
     * @retval	true	�Փ˂��Ă����Ԃ���
     * @retval	false	�Փ˂��Ă��Ȃ���Ԃ���
     */
    virtual bool processHitChkLogic(Checker* prm_pOtherChecker) {
        return false;
    }

    ~Checker();

};

}
#endif /*GGAF_CORE_CHECKER_H_*/

