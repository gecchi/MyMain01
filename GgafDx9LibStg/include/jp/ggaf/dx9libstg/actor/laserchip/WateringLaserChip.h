#ifndef CURVELASERCHIP_H_
#define CURVELASERCHIP_H_
namespace GgafDx9LibStg {

/**
 * ���T�����[�U�[�p�|�����C���̃`�b�v .
 * ���T�����[�U�[�Ȃǂƕ\�����Ă��邪�A���m�ɂ�<BR>
 * �E���ˍ��W�C�Ӂi���ˌ����W���ړ��\�j<BR>
 * �E�e�`�b�v�̈ړ������A���x���ɌŒ�<BR>
 * �E�������A�אڂ���`�b�v�ƃ`�b�v�������荇���A�`�b�v�Ԃɓ����蔻�肪����<BR>
 * �Ƃ����ׂ����A�O���f�B�E�X�u�̃f�B���N�V�������[�U�[(TYPE2)�ƌ����ׂ����A����Ȋ����B<BR>
 * @version 1.00
 * @since 2009/08/27
 * @author Masatoshi Tsuge
 */
class WateringLaserChip : public LaserChip {
    friend class LaserChipDispatcher;
public:
    int _tmpX, _tmpY, _tmpZ;
    WateringLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize() override;

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior() override;


    virtual void processSettlementBehavior() override;

    /**
     * ���[�U�[�`�b�v���蓙���� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processJudgement() ���\�b�h���Ăяo���Ă��������B
     * ���͖{���\�b�h�ŁAGgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld) ���Ăяo���Ă���A
     * ���̃^�C�~���O�Ń��[���h�ϊ��s�񂪊m�肵�܂��̂ŁA�I�[�o�[���C�h�̍ۂ͍Ō�� WateringLaserChip::processJudgement(); ��
     * �����ق����ǂ��ł��傤�B
     */
    virtual void processJudgement() override;

    /**
     * ���[�U�[�`�b�v�o�������� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void onActive() override;

    /**
     * ���[�U�[�`�b�v���������� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� onInactive() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void onInactive() override;

    virtual ~WateringLaserChip();

};

}
#endif /*CURVELASERCHIP_H_*/

