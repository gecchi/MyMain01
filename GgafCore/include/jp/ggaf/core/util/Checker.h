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
    /** �`�F�b�N�Ώ� */
    Actor* const _pActor;
    /** �g���`�F�b�N�Anullptr �łȂ���΃`�F�b�N����� */
    Checker* _pNextExChecker;
public:
    /**
     * �`�F�b�J�[���� .
     * @param prm_pActor �`�F�b�N�Ώ�
     */
    Checker(Actor* prm_pActor, kind_t prm_kind = 0);

    /**
     * ���`�F�b�J�[�Ƒ��`�F�b�J�[�̂P�΂P�̓����蔻�菈�����s���B
     * @param prm_pOppHitChecker ���`�F�b�J�[
     */
    virtual void executeHitChk_MeAnd(Checker* prm_pOppHitChecker) {
        if (prm_pOppHitChecker == this) {
            return;
        } else {
            //�q�b�g�ł��镨�ǂ����̔���͎��O�ɂ���ł���悤�ɂ��鎖�B
            if (processHitChkLogic(prm_pOppHitChecker)) { //���g�̃q�b�g�`�F�b�N
                _pActor->onHit(this, prm_pOppHitChecker); //�����̃q�b�g���̐U�镑��
                prm_pOppHitChecker->_pActor->onHit(prm_pOppHitChecker, this); //����̃q�b�g���̐U�镑��
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
     * @param	prm_pOppHitChecker�@����`�F�b�J�[
     * @retval	true	�Փ˂��Ă����Ԃ���
     * @retval	false	�Փ˂��Ă��Ȃ���Ԃ���
     */
    virtual bool processHitChkLogic(Checker* prm_pOppHitChecker) {
        return false;
    }


    /**
     * �f�t�H���g�`�F�b�J�[�� _pNextExChecker �Ɋg���`�F�b�J�[��ǉ�
     * @return �g���`�F�b�J�[
     */
    virtual Checker* addExChecker(kind_t prm_kind = 0);

    ~Checker();

};

}
#endif /*GGAF_CORE_CHECKER_H_*/

