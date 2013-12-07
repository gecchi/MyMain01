#ifndef GGAFDXCORE_GGAFDXFKFORMATION_H_
#define GGAFDXCORE_GGAFDXFKFORMATION_H_
#include "jp/ggaf/core/actor/ex/GgafFormation.h"

namespace GgafDxCore {

/**
 * �z���c���[�Ǘ��̃t�H�[���[�V�����Ǘ��N���X .
 * �ґ������o�[�͎g���̂Ẵt�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����AaddFormationMember(GgafActor*) �ɂ��
 * �ґ������o�[��ǉ����Ă����Ă��������B
 * processFinal()�������ς݂ł��̂ŁA�I�[�o�[���C�h����ꍇ�͒��ӂ��ĉ������B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDxFkFormation : public GgafCore::GgafFormation {
private:
    /**
     * �g�p�s�� .
     * @param prm_pSub
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
        throwGgafCriticalException("GgafDxFkFormation::addSubLast �͎g�p�s�ł��B");
    }

    /** [r]callUpMember()�p�̃J�[�\�� */
    GgafCore::GgafActor* _pIte;
    bool _can_call_up;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafDxFkFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �T�u��������Ζ{�I�u�W�F�N�g����Ƃ������� .
     * �\�������o�[���S�� sayonara() �����ꍇ�A�{�t�H�[���[�V�����I�u�W�F�N�g��������������
     * �悤�ɂ��邽�߂Ɏ����ς݂ł��B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * GgafDxFkFormation::processFinal();
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
     * �x�[�X��FK�̒ǉ�����A�N�^�[�̎�ʂ́A������addSubGroupAsFk���g�p���A�c�������܂��Ă���̂ŁA
     * �����Œǉ�����x�[�X�Ɠ�����ʂł��邩�ǂ������C�ɂ���K�v���Ȃ��B
     * @param prm_pFkBase
     */
    virtual void registerFormationFkBase(GgafDxGeometricActor* prm_pFkBase);

    virtual GgafDxGeometricActor* getFkBase() {
        return (GgafDxGeometricActor*)(getSubFirst());
    }

    /**
     * �ґ��̃����o�[��o�^�B�p�����t�H���[�h�L�l�}�e�B�N�X�Őݒ肷��B
     * �ґ����\�����邽�߂ɁA�{���\�b�h�����s���A�����o�[��\�ߔz���A�N�^�[�ɐݒ肷��K�v������B<BR>
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addFormationMember ����K�v������B<BR>
     * �\�������o�[������������ɂ́AcallUpMember() ���g�p�B<BR>
     * �\�������o�[�������I�����́Asayonara() ���g�p�B����ΏۂɂȂ�B<BR>
     * �ґ������o�[�͎g���̂Ăł���B<BR>
     * �����I�ɂ́A���� prm_fkbase_index �Ԗڂ̃T�u�A�N�^�[���x�[�X�Ƃ��A���̃x�[�X�A�N�^�[�� addSubGroupAsFk �ɂ��
     * prm_pMember��z���ɓo�^���܂��B<BR>
     * <BR>
     * �����̕ґ������o�[�A�N�^�[�́A���̂Q�̃��\�b�h�̎g�p���\�ƂȂ�܂��B <BR>
     * _x,_y,_z,_rx,_ry,_rz �����[�J���ithis����̑��΁j�ɐ؂�ւ���E�E�EchangeGeoLocal()<BR>
     * _x,_y,_z,_rx,_ry,_rz ��΍��W�ɐ؂�ւ���                    �E�E�EchangeGeoFinal()<BR>
     * �y���Ӂz<BR>
     * ����(_pKuroko) �́A���[�J�����W�n�ł̂ݎg�p�\�ƂȂ�܂��B<BR>
     * �]���A�N�^�[processBehavior() �̏����𔲂���O�ɂ́AchangeGeoFinal() �Ő�΍��W�ɖ߂��Ă����K�v������܂��B<BR>
     * @param prm_pMember �]��������A�N�^�[
     * @param prm_x_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����X���W�ʒu
     * @param prm_y_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Y���W�ʒu
     * @param prm_z_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Z���W�ʒu
     * @param prm_rx_init_local �]���A�N�^�[�̃��[�J��(this)��]�����X����]�l
     * @param prm_ry_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Y����]�l
     * @param prm_rz_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Z����]�l
     */
    virtual void addFormationMember(GgafDxGeometricActor* prm_pMember,
                                    int prm_x_init_local,
                                    int prm_y_init_local,
                                    int prm_z_init_local,
                                    int prm_rx_init_local,
                                    int prm_ry_init_local,
                                    int prm_rz_init_local);

    /**
     * �o�^�����ґ��̃����o�[�����ԂɎ擾���܂�.
     * addSubLast(GgafCore::GgafActor*) �ɂ��A�o�^�����ґ������o�[�����ԂɎ��o���܂��B
     * �S�ĕґ������o�[���擾���Ă��܂����ꍇ�Anullptr ��Ԃ��܂��B
     * @return �������̕ґ��o�^�����o�[�B���� nullptr�A�������̕ґ��o�^�����o�[�͂��������B
     */
    GgafDxGeometricActor* callUpMember();

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
     * GgafDxFkFormation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    /**
     * �ґ��ɏ��������A�N�^�[���S�Ă���Ȃ�(sayonara()���Ăяo���ꂽ)�����ꍇ�R�[���o�b�N����郁�\�b�h .
     * �K�v�ɉ����ĉ��ʂŃI�[�o�[���C�h���������ĉ������B
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~GgafDxFkFormation();
};

}
#endif /*GGAFDXCORE_GGAFDXFKFORMATION_H_*/
