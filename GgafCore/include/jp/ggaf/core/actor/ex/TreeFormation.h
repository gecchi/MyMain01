#ifndef GGAF_CORE_TREEFORMATION_H_
#define GGAF_CORE_TREEFORMATION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/Formation.h"

namespace GgafCore {

/**
 * �z���c���[�Ǘ��̃t�H�[���[�V�����Ǘ��N���X .
 * �ґ������o�[�͎g���̂Ẵt�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����AappendFormationMember(Actor*) �ɂ��
 * �ґ������o�[��ǉ����Ă����Ă��������B
 * �܂��A�o�^�̃A�N�^�[���j�󂳂ꂽ�ꍇ�́A�ґ��S�Ŕ���̂��߂�
 * Actor::notifyDestroyedToFormation(); ���R�[�����Ă��������B
 * processFinal()�������ς݂ł��̂ŁA�I�[�o�[���C�h����ꍇ�͒��ӂ��ĉ������B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class TreeFormation : public Formation {
private:
    /**
     * �g�p�s�� .
     * @param prm_pChild
     */
    virtual void appendChild(Actor* prm_pChild) override {
        throwCriticalException("�g�p�s�ł��B");
    }

    /** [r]calledUpMember()�p�̃J�[�\�� */
    Actor* _pIte;
    bool _can_called_up;
    bool _is_append_member_experienced;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    TreeFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �q��������Ζ{�I�u�W�F�N�g����Ƃ������� .
     * �\�������o�[���S�� sayonara() �����ꍇ�A�{�t�H�[���[�V�����I�u�W�F�N�g��������������
     * �悤�ɂ��邽�߂Ɏ����ς݂ł��B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * TreeFormation::processFinal();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processFinal() override;

    /**
     * �ґ��̃����o�[��o�^���܂�.
     * �ґ����\�����邽�߂ɁA�{���\�b�h�����s���A�����o�[��\�ߔz���A�N�^�[�ɐݒ肷��K�v������B<BR>
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�appendFormationMember ����K�v������B<BR>
     * �����Ŏ����� inactivateImmed() �����s����A�ŏ��͑ҋ@��ԂƂȂ�B<BR>
     * �\�������o�[������������ɂ́AcalledUpMember() ���g�p�B<BR>
     * �\�������o�[�������I�����́Asayonara() ���g�p�B����ΏۂɂȂ�B<BR>
     * �ґ������o�[�͎g���̂Ăł���B<BR>
     * @param prm_pChild �ґ��̃����o�[�̃A�N�^�[
     */
    virtual void appendFormationMember(Actor* prm_pChild);

    /**
     * �o�^�����ґ��̃����o�[�����ԂɃA�N�e�B�u�ɂ��Ď擾���܂�.
     * appendFormationMember(Actor*) �ɂ��A�o�^�����ґ������o�[�����ԂɎ��o���܂��B
     * �S�ĕґ������o�[���擾���Ă��܂����ꍇ�Anullptr ��Ԃ��܂��B
     * @param prm_formation_child_num �{�t�H�[���[�V�����̊Ǘ������v�����i���ґ��S�Ő��j�B�ȗ����͔z�������o�[���ƂȂ�B
     * @return �������̕ґ��o�^�����o�[�B���� nullptr�A�������̕ґ��o�^�����o�[�͂��������B
     */
    Actor* calledUpMember(int prm_formation_child_num = INT_MAX);

    /**
     * calledUpMember() �\�ȏꍇ true
     * @return true:�������̕ґ��o�^�����o�[����������/false:�������݂��Ȃ��B
     */
    inline bool canCalledUp() {
        return _can_called_up;
    }

    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * TreeFormation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    /**
     * �ґ��ɏ��������A�N�^�[���S�Ă���Ȃ�(sayonara()���Ăяo���ꂽ)�����ꍇ�R�[���o�b�N����郁�\�b�h .
     * �K�v�ɉ����ĉ��ʂŃI�[�o�[���C�h���������ĉ������B
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~TreeFormation();
};

}
#endif /*GGAF_CORE_TREEFORMATION_H_*/
