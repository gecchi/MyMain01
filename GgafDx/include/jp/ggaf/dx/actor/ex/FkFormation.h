#ifndef GGAF_DX_FKFORMATION_H_
#define GGAF_DX_FKFORMATION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/actor/ex/Formation.h"

namespace GgafDx {

/**
 * �z���c���[�Ǘ��̃t�H�[���[�V�����Ǘ��N���X .
 * �ґ������o�[�͎g���̂Ẵt�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����AappendFormationMember(GgafCore::Actor*) �ɂ��
 * �ґ������o�[��ǉ����Ă����Ă��������B
 * processFinal()�������ς݂ł��̂ŁA�I�[�o�[���C�h����ꍇ�͒��ӂ��ĉ������B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class FkFormation : public GgafCore::Formation {
private:
    /**
     * �g�p�s�� .
     * @param prm_pChild
     */
    virtual void appendChild(GgafCore::Actor* prm_pChild) override {
        throwCriticalException("�g�p�s�ł��B");
    }

    /** [r]calledUpMember()�p�̃J�[�\�� */
    GgafCore::Actor* _pIte;

    bool _can_called_up;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    FkFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �q��������Ζ{�I�u�W�F�N�g����Ƃ������� .
     * �\�������o�[���S�� sayonara() �����ꍇ�A�{�t�H�[���[�V�����I�u�W�F�N�g��������������
     * �悤�ɂ��邽�߂Ɏ����ς݂ł��B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * FkFormation::processFinal();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processFinal() override;

    /**
     * FK�̃x�[�X��ݒ� .
     * ��������
     * �����B�ړ�����p�_�~�[�Ȃǂ�z��B
     * ���������A�N�^�[�ł��ǂ��B���̏ꍇ�{�t�H�[���[�V�����I�u�W�F�N�g�̎�ʂ��P���邽�߁A
     * �Q�ڈȍ~�͒ǉ�������ʂł���K�v������B
     * �x�[�X��FK�̒ǉ�����A�N�^�[�̎�ʂ́A������appendGroupChildAsFk���g�p���A�c�������܂��Ă���̂ŁA
     * �����Œǉ�����x�[�X�Ɠ�����ʂł��邩�ǂ������C�ɂ���K�v���Ȃ��B
     * @param prm_pFkBase
     */
    virtual void registerFormationFkBase(GeometricActor* prm_pFkBase);

    virtual GeometricActor* getFkBase() {
        return (GeometricActor*)(getChildFirst());
    }

    /**
     * �ґ��̃����o�[��o�^�B�p�����t�H���[�h�L�l�}�e�B�N�X�Őݒ肷��B
     * �ґ����\�����邽�߂ɁA�{���\�b�h�����s���A�����o�[��\�ߔz���A�N�^�[�ɐݒ肷��K�v������B<BR>
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�appendFormationMember ����K�v������B<BR>
     * �\�������o�[������������ɂ́AcalledUpMember() ���g�p�B<BR>
     * �\�������o�[�������I�����́Asayonara() ���g�p�B����ΏۂɂȂ�B<BR>
     * �ґ������o�[�͎g���̂Ăł���B<BR>
     * �����I�ɂ́A���� prm_fkbase_index �Ԗڂ̎q�A�N�^�[���x�[�X�Ƃ��A���̃x�[�X�A�N�^�[�� appendGroupChildAsFk �ɂ��
     * prm_pMember��z���ɓo�^���܂��B<BR>
     * <BR>
     * �����̕ґ������o�[�A�N�^�[�́A���̂Q�̃��\�b�h�̎g�p���\�ƂȂ�܂��B <BR>
     * _x,_y,_z,_rx,_ry,_rz �����[�J���ithis����̑��΁j�ɐ؂�ւ���E�E�EchangeGeoLocal()<BR>
     * _x,_y,_z,_rx,_ry,_rz ��΍��W�ɐ؂�ւ���                    �E�E�EchangeGeoFinal()<BR>
     * �y���Ӂz<BR>
     * �ړ��ԗ�(getLocoVehicle()) �́A���[�J�����W�n�ł̂ݎg�p�\�ƂȂ�܂��B<BR>
     * �]���A�N�^�[processBehavior() �̏����𔲂���O�ɂ́AchangeGeoFinal() �Ő�΍��W�ɖ߂��Ă����K�v������܂��B<BR>
     * @param prm_pMember �]��������A�N�^�[
     * @param prm_x_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����X���W�ʒu
     * @param prm_y_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Y���W�ʒu
     * @param prm_z_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Z���W�ʒu
     * @param prm_rx_init_local �]���A�N�^�[�̃��[�J��(this)��]�����X����]�l
     * @param prm_ry_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Y����]�l
     * @param prm_rz_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Z����]�l
     */
    virtual void appendFormationMember(GeometricActor* prm_pMember,
                                       int prm_x_init_local,
                                       int prm_y_init_local,
                                       int prm_z_init_local,
                                       int prm_rx_init_local,
                                       int prm_ry_init_local,
                                       int prm_rz_init_local);

    /**
     * �o�^�����ґ��̃����o�[�����ԂɎ擾���܂�.
     * appendChild(GgafCore::Actor*) �ɂ��A�o�^�����ґ������o�[�����ԂɎ��o���܂��B
     * �S�ĕґ������o�[���擾���Ă��܂����ꍇ�Anullptr ��Ԃ��܂��B
     * @param prm_formation_child_num �{�t�H�[���[�V�����̊Ǘ������v�����i���ґ��S�Ő��j�B�ȗ����͔z�������o�[���ƂȂ�B
     * @return �������̕ґ��o�^�����o�[�B���� nullptr�A�������̕ґ��o�^�����o�[�͂��������B
     */
    GeometricActor* calledUpMember(int prm_formation_child_num = INT_MAX);

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
     * FkFormation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    /**
     * �ґ��ɏ��������A�N�^�[���S�Ă���Ȃ�(sayonara()���Ăяo���ꂽ)�����ꍇ�R�[���o�b�N����郁�\�b�h .
     * �K�v�ɉ����ĉ��ʂŃI�[�o�[���C�h���������ĉ������B
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~FkFormation();
};

}
#endif /*GGAF_DX_FKFORMATION_H_*/
