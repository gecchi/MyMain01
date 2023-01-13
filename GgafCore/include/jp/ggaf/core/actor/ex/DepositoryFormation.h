#ifndef GGAF_CORE_DEPOSITORYFORMATION_H_
#define GGAF_CORE_DEPOSITORYFORMATION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/Formation.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"

namespace GgafCore {

/**
 * �f�|�W�g���Ǘ��̃t�H�[���[�V�����Ǘ��[�N���X .
 * �ґ������o�[�͎g���񂷃t�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����A
 * setFormationMember(ActorDepository*) �ɂ��
 * �ґ������o�[�����̃f�|�W�g���I�u�W�F�N�g��o�^���Ă��������B
 * �܂��A�o�^�̃A�N�^�[���j�󂳂ꂽ�ꍇ�́A�ґ��S�Ŕ���̂��߂�
 * Actor::notifyDestroyedToFormation(); ���R�[�����Ă��������B
 * processFinal() �������ς݂ł��̂ŁA�I�[�o�[���C�h����ꍇ�͒��ӂ��ĉ������B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class DepositoryFormation : public Formation {

public:
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[�̃��X�g */
    RingLinkedList<Actor> _listFollower;
    bool _can_called_up;
    /** [r]�\�������o�[�̃X�g�b�J�[�inullptr�̏ꍇ�\�������o�[�͔z���A�N�^�[�̂͂��j */
    ActorDepository* _pDepo;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �t�H�[���[�V�����I�����̗P�\�t���[��
     * @return
     */
    DepositoryFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �ґ��\�������o�[���X�g�b�N���ꂽ�f�|�W�g����ݒ肷�� .
     * �����o�[������������ɂ́A��p���\�b�h calledUpMember() ���g�p����B
     * �����o�[�������I�����́Asayonara() ���g�p�B
     * @param prm_pDepo
     */
    void setFormationMember(ActorDepository* prm_pDepo);

    /**
     * �ґ������o�[���S�Ĕ񊈓��Ȃ�΁A�{�t�H�[���[�V�����I�u�W�F�N�g��� .
     * �\�������o�[���S�� sayonara() �ŁA�f�|�W�g���ɖ߂����ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g��������������悤�ɂ��邽�߂̎d�g�݂������B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * TreeFormation::processFinal();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processFinal() override;

    /**
     * �f�|�W�g������A�N�^�[��{�t�H�[���[�V���������o�[�Ƃ��Đݒ肵�擾����i���W����j .
     * setFormationMembersitory() �̎��O���s���K�v�B<BR>
     * �{���\�b�h���Ăяo���ƁA�f�|�W�g���ɊǗ����ꂽ�����o�[����� dispatch() ����܂��B(������ activate() �������)
     * �f�|�W�g���̃����o�[�����ׂĊ������ŁA�͊����Ă���ꍇ nullptr ���Ԃ�܂��B<BR>
     * �܂��A������ prm_formation_child_num �͍ő�ґ��\���v�����ŁA���̐��ȏ�̌Ăяo���ł� nullptr ���Ԃ�܂��B<BR>
     * ��x�ł� nullptr ���Ԃ����ƁA�����t���O _can_called_up �� false �ɂȂ�A�ȍ~�{�t�H�[���[�V�����I�u�W�F�N�g��
     * �����o�[�Ăяo���ł��Ȃ��悤�ɂȂ�܂��B�Ɠ�����(_can_called_up==false���󂯂�)processFinal() ���ł́A
     * �S�Ă̕ґ������o�[���񊈓����A�{�t�H�[���[�V�����I�u�W�F�N�g�������I�� sayonara(_offset_frames_end) �����s�����悤�ɂȂ�܂��B<BR>
     * �y�n�}���������P�z�����[�� calledUpMember �Ăяo���ŁA�f�|�W�g���X�g�b�N�͊��ɂ��A�����Ȃ�nullptr���Ԃ����ꍇ���A
     * _can_called_up = false �ɂȂ�܂��B����āA�{�t�H�[���[�V�����I�u�W�F�N�g�́A�����Ȃ� sayonara(_offset_frames_end) �����s����I������B
     * �Ƃ�������ɂȂ�܂��B�\�������o�[���m�ۂł��Ȃ������ꍇ���l�����ĉ������B<BR>
     * �y�n�}���������Q�zcalledUpMember() ���Ď擾���������o�[�� sayonara() (�����I�ɂ�inactive()) ���邱�Ƃɂ��A�ґ����痣�E�������ƂɂȂ�܂��B
     * �]���āAcalledUpMember() ���������o�[���Ainactive() ���āA�����ꎞ�ۗL���m�ۂ��邱�Ƃ́A���̏u�Ԃɕґ����痣�E�������Ɠ��ӂɂȂ�܂��̂ŁA
     * �ł��܂���B���̂悤�ɂ������ꍇ�� TreeFormation ���g����������܂���B<BR>
     * @param prm_formation_child_num �{�t�H�[���[�V�����̊Ǘ������v�����i���ґ��S�Ő��j�B�ȗ����͔z�������o�[���ƂȂ�B
     * @return �ґ��\���v���̃A�N�^�[�B
     *         �ő�ґ��\���v�������I�[�o�[���ČĂяo�����ꍇ�A������
     *         �f�|�W�g���ɍ\���v�����������Ȃ��ꍇ�� nullptr
     */
    Actor* calledUpMember(int prm_formation_child_num = INT_MAX);

    /**
     * �܂��A�ґ������m�ۂ��s�\���ŁAcalledUpMember() ������]�n�����邩�ǂ����B .
     * @return true�F�]�n����^false�F�]�n�Ȃ�
     */
    bool canCalledUp() const;

    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * DepositoryFormation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    /**
     * �f�|�W�g�����[�h�Ǘ��̕ґ��S�Ă� sayonara() �����s����B
     */
    virtual void sayonaraFollwer();

    /**
     * �ґ��ɏ��������A�N�^�[���S�Ă���Ȃ�(sayonara()���Ăяo���ꂽ)�����ꍇ�R�[���o�b�N����郁�\�b�h .
     * �K�v�ɉ����ĉ��ʂŃI�[�o�[���C�h���������ĉ������B
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~DepositoryFormation();
};

}
#endif /*GGAF_CORE_DEPOSITORYFORMATION_H_*/
