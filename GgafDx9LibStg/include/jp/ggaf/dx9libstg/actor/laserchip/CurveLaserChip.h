#ifndef CURVELASERCHIP_H_
#define CURVELASERCHIP_H_
namespace GgafDx9LibStg {

/**
 * �J�[�u���[�U�[�p�|�����C���̃`�b�v .
 * �J�[�u���[�U�[�Ȃǂƕ\�����Ă��邪�A���m�ɂ�<BR>
 * �E���ˍ��W�C��<BR>
 * �E�ړ������A���x���Ɏ��͌Œ�<BR>
 * �E�������A�אڂ���`�b�v�ƃ`�b�v�������荇���A�`�b�v�Ԃɓ����蔻�肪����<BR>
 * �Ƃ����ׂ����A���T���̎��̃z�[�X����o�鐅�������[�U�[�ƌ����ׂ����A����Ȋ����B<BR>
 * @version 1.00
 * @since 2009/08/27
 * @author Masatoshi Tsuge
 */
class CurveLaserChip : public LaserChip {
    friend class LaserChipDispatcher;
public:
    int _tmpX, _tmpY, _tmpZ;
    CurveLaserChip(const char* prm_name, const char* prm_model);

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
     * ���̃^�C�~���O�Ń��[���h�ϊ��s�񂪊m�肵�܂��̂ŁA�I�[�o�[���C�h�̍ۂ͍Ō�� CurveLaserChip::processJudgement(); ��
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

    virtual ~CurveLaserChip();

};

}
#endif /*CURVELASERCHIP_H_*/

