#ifndef GGAFCORE_GGAFTREEFORMATION_H_
#define GGAFCORE_GGAFTREEFORMATION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/GgafFormation.h"

namespace GgafCore {

/**
 * �z���c���[�Ǘ��̃t�H�[���[�V�����Ǘ��N���X .
 * �ґ������o�[�͎g���̂Ẵt�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����AaddFormationMember(GgafActor*) �ɂ��
 * �ґ������o�[��ǉ����Ă����Ă��������B
 * �܂��A�o�^�̃A�N�^�[���j�󂳂ꂽ�ꍇ�́A�ґ��S�Ŕ���̂��߂�
 * GgafActor::notifyDestroyedToFormation(); ���R�[�����Ă��������B
 * processFinal()�������ς݂ł��̂ŁA�I�[�o�[���C�h����ꍇ�͒��ӂ��ĉ������B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafTreeFormation : public GgafFormation {
private:
    /**
     * �g�p�s�� .
     * @param prm_pSub
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
        throwGgafCriticalException("�͎g�p�s�ł��B");
    }

    /** [r]callUpMember()�p�̃J�[�\�� */
    GgafCore::GgafActor* _pIte;
    bool _can_call_up;
    bool _is_addmember_experienced;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �T�u��������Ζ{�I�u�W�F�N�g����Ƃ������� .
     * �\�������o�[���S�� sayonara() �����ꍇ�A�{�t�H�[���[�V�����I�u�W�F�N�g��������������
     * �悤�ɂ��邽�߂Ɏ����ς݂ł��B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * GgafTreeFormation::processFinal();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processFinal() override;

    /**
     * �ґ��̃����o�[��o�^���܂�.
     * �ґ����\�����邽�߂ɁA�{���\�b�h�����s���A�����o�[��\�ߔz���A�N�^�[�ɐݒ肷��K�v������B<BR>
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addFormationMember ����K�v������B<BR>
     * �����Ŏ����� inactivateImmed() �����s����A�ŏ��͑ҋ@��ԂƂȂ�B<BR>
     * �\�������o�[������������ɂ́AcallUpMember() ���g�p�B<BR>
     * �\�������o�[�������I�����́Asayonara() ���g�p�B����ΏۂɂȂ�B<BR>
     * �ґ������o�[�͎g���̂Ăł���B<BR>
     * @param prm_pSub �ґ��̃����o�[�̃A�N�^�[
     */
    virtual void addFormationMember(GgafCore::GgafActor* prm_pSub);

    /**
     * �o�^�����ґ��̃����o�[�����ԂɎ擾���܂�.
     * addFormationMember(GgafCore::GgafActor*) �ɂ��A�o�^�����ґ������o�[�����ԂɎ��o���܂��B
     * �S�ĕґ������o�[���擾���Ă��܂����ꍇ�Anullptr ��Ԃ��܂��B
     * @return �������̕ґ��o�^�����o�[�B���� nullptr�A�������̕ґ��o�^�����o�[�͂��������B
     */
    GgafActor* callUpMember();

    /**
     * callUpMember() �\�ȏꍇ true
     * @return true:�������̕ґ��o�^�����o�[����������/false:�������݂��Ȃ��B
     */
    inline bool canCallUp() {
        return _can_call_up;
    }

    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafTreeFormation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    /**
     * �ґ��ɏ��������A�N�^�[���S�Ă���Ȃ�(sayonara()���Ăяo���ꂽ)�����ꍇ�R�[���o�b�N����郁�\�b�h .
     * �K�v�ɉ����ĉ��ʂŃI�[�o�[���C�h���������ĉ������B
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~GgafTreeFormation();
};

}
#endif /*GGAFCORE_GGAFTREEFORMATION_H_*/
