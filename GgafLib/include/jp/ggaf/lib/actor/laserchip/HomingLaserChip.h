#ifndef HOMINGLASERCHIP_H_
#define HOMINGLASERCHIP_H_
namespace GgafLib {

/**
 * �z�[�~���O���[�U�[�p�|�����C���̃`�b�v .
 * �z�[�~���O���[�U�[�ȂǂƂƕ\�����Ă��邪�A���m�ɂ� <BR>
 * �E���ˍ��W�ʒu�Œ�i���ˌ����W���ړ��s�j<BR>
 * �E�ړ������A���x�͐擪�`�b�v���݂̂����߁A�c��`�b�v�͒P�ɒǏ]����<BR>
 * �ƌ����ׂ����A���C�t�H�[�X�̃��b�N�I�����[�U�[�ƌ����ׂ����A����Ȋ����B<BR>
 * @version 1.00
 * @since 2009/11/04
 * @author Masatoshi Tsuge
 */
class HomingLaserChip : public LaserChip {
    friend class LaserChipDepository;

public:
    /** �擱�`�b�v�i�{���̐擪�`�b�v�j�t���O */
    bool _is_leader; //�{���̐擪�`�b�v�Ƃ́A���[�U�[�ړ����ɂ�����Ĕ�������ɂ킩�擪�`�b�v�ł͖����Ƃ����Ӗ��B
    int _begining_X;
    int _begining_Y;
    int _begining_Z;
    angle _begining_RX;
    angle _begining_RY;
    angle _begining_RZ;
    int _prev_X;
    int _prev_Y;
    int _prev_Z;
    angle _prev_RX;
    angle _prev_RY;
    angle _prev_RZ;

    HomingLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void initialize() override;


    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior() override;

    virtual void processSettlementBehavior() override;

    /**
     * �z�[�~���O���[�U�[�̐擪�`�b�v�̓������������� .
     * �{���̐擪�`�b�v�̏ꍇ�͂������R�[���o�b�N����邪�A
     * �ɂ킩�擪�`�b�v�i������ċ}�ɐ擪�ɂȂ����`�b�v�j�̏ꍇ���R�[���o�b�N����܂��B
     */
    virtual void processBehaviorHeadChip() = 0;

    /**
     * ���[�U�[�`�b�v���蓙���� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processJudgement() ���\�b�h���Ăяo���Ă��������B
     * ���͖{���\�b�h�ŁAGgafDxGeometricActor::updateWorldMatrix_Mv(this, _matWorld) ���Ăяo���Ă���A
     * ���̃^�C�~���O�Ń��[���h�ϊ��s�񂪊m�肵�܂��̂ŁA�I�[�o�[���C�h�̍ۂ͍Ō�� HomingLaserChip::processJudgement(); ��
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


    //virtual void initializeHoming(GgafDxCore::GgafDxGeometricActor* prm_pActor_Target);

    virtual ~HomingLaserChip();

};

}
#endif /*HOMINGLASERCHIP_H_*/
