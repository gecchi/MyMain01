#ifndef GGAFDEPOSITORYFORMATION_H_
#define GGAFDEPOSITORYFORMATION_H_
#include "jp/ggaf/core/actor/ex/GgafFormation.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"

namespace GgafCore {

/**
 * �f�|�W�g���Ǘ��̃t�H�[���[�V�����Ǘ��[�N���X .
 * �ґ������o�[�͎g���񂷃t�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����A
 * setFormationMember(GgafActorDepository*) �ɂ��
 * �ґ������o�[�����̃f�|�W�g���I�u�W�F�N�g��o�^���Ă��������B
 * processFinal() �������ς݂ł��̂ŁA�I�[�o�[���C�h����ꍇ�͒��ӂ��ĉ������B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDepositoryFormation : public GgafFormation {

public:
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[�̃��X�g */
    GgafCore::GgafLinkedListRing<GgafActor> _listFollower;
    /** [r]����ȏ� callUpMember() �s�̏ꍇ true */
    bool _can_call_up;
    /** [r]�S�Ŏ� true (GgafActor::notifyDestroyedToFormation() ���ݒ�) */
    bool _was_all_destroyed;
    /** [r]�\�������o�[�̃X�g�b�J�[�inullptr�̏ꍇ�\�������o�[�͔z���A�N�^�[�̂͂��j */
    GgafCore::GgafActorDepository* _pDepo;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �t�H�[���[�V�����I�����̗P�\�t���[��
     * @return
     */
    GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �ґ��\�������o�[���X�g�b�N���ꂽ�f�|�W�g����ݒ肷�� .
     * �����o�[������������ɂ́A��p���\�b�h callUpMember() ���g�p����B
     * �����o�[�������I�����́Asayonara() ���g�p�B
     * @param prm_pDepo
     */
    void setFormationMember(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * �ґ������o�[���S�Ĕ񊈓��Ȃ�΁A�{�t�H�[���[�V�����I�u�W�F�N�g��� .
     * �\�������o�[���S�� sayonara() �ŁA�f�|�W�g���ɖ߂����ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g��������������悤�ɂ��邽�߂̎d�g�݂������B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * GgafTreeFormation::processFinal();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processFinal() override;

    /**
     * �f�|�W�g������A�N�^�[��{�t�H�[���[�V���������o�[�Ƃ��Đݒ肵�擾����i���W����j .
     * setFormationMembersitory() �̎��O���s���K�v�B<BR>
     * �{���\�b�h���Ăяo���ƁA�f�|�W�g���ɊǗ����ꂽ�����o�[����� dispatch() ����܂��B(������ activate() �������)
     * �f�|�W�g���̃����o�[�����ׂĊ������ŁA�͊����Ă���ꍇ nullptr ���Ԃ�܂��B<BR>
     * �܂��A������ prm_formation_sub_num �͍ő�ґ��\���v�����ŁA���̐��ȏ�̌Ăяo���ł� nullptr ���Ԃ�܂��B<BR>
     * ��x�ł� nullptr ���Ԃ����ƁA�����t���O _can_call_up �� false �ɂȂ�A�ȍ~�{�t�H�[���[�V�����I�u�W�F�N�g��
     * �����o�[�Ăяo���ł��Ȃ��悤�ɂȂ�܂��B�Ɠ�����(_can_call_up==false���󂯂�)processFinal() ���ł́A
     * �S�Ă̕ґ������o�[���񊈓����A�{�t�H�[���[�V�����I�u�W�F�N�g�������I�� sayonara(_offset_frames_end) �����s�����悤�ɂȂ�܂��B<BR>
     * �y�n�}���������P�z�����[�� callUpMember �Ăяo���ŁA�f�|�W�g���X�g�b�N�͊��ɂ��A�����Ȃ�nullptr���Ԃ����ꍇ���A
     * _can_call_up = false �ɂȂ�܂��B����āA�{�t�H�[���[�V�����I�u�W�F�N�g�́A�����Ȃ� sayonara(_offset_frames_end) �����s����I������B
     * �Ƃ�������ɂȂ�܂��B�\�������o�[���m�ۂł��Ȃ������ꍇ���l�����ĉ������B<BR>
     * �y�n�}���������Q�zcallUpMember() ���Ď擾���������o�[�� sayonara() (�����I�ɂ�inactive()) ���邱�Ƃɂ��A�ґ����痣�E�������ƂɂȂ�܂��B
     * �]���āAcallUpMember() ���������o�[���Ainactive() ���āA�����ꎞ�ۗL���m�ۂ��邱�Ƃ́A���̏u�Ԃɕґ����痣�E�������Ɠ��ӂɂȂ�܂��̂ŁA
     * �ł��܂���B���̂悤�ɂ������ꍇ�� GgafTreeFormation ���g����������܂���B<BR>
     * @param prm_formation_sub_num �{�t�H�[���[�V�����̍ő�ґ��\���v����
     * @return �ґ��\���v���̃A�N�^�[�B
     *         �ő�ґ��\���v�������I�[�o�[���ČĂяo�����ꍇ�A������
     *         �f�|�W�g���ɍ\���v�����������Ȃ��ꍇ�� nullptr
     */
    GgafActor* callUpMember(int prm_formation_sub_num = INT_MAX);

    /**
     * �܂��A�ґ������m�ۂ��s�\���ŁAcallUpMember() ������]�n�����邩�ǂ����B .
     * @return true�F�]�n����^false�F�]�n�Ȃ�
     */
    bool canCallUp();

    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafDepositoryFormation::onEnd() ���Ăяo���ĉ������B
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

    virtual ~GgafDepositoryFormation();
};

}
#endif /*GGAFDEPOSITORYFORMATION_H_*/
