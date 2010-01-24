#ifndef REFRACTIONLASERCHIP_H_
#define REFRACTIONLASERCHIP_H_
namespace MyStg2nd {

/**
 * ���܃��[�U�[�p�|�����C���̃`�b�v .
 * ���܃��[�U�[�ƕ\�����Ă��邪�A
 * ���m�ɂ͔��ˍ��W�Œ�A�ړ������͐擪�`�b�v�����߂�A�����o���`���[�U�[�Ƃ����ׂ����B
 * �Ƃ���Ă�������[�U�[�ƌ����ׂ����A����Ȋ����B
 * @version 1.00
 * @since 2010/01/19
 * @author Masatoshi Tsuge
 */
class RefractionLaserChip : public LaserChip {
    friend class LaserChipDispatcher;

private:
    DWORD _frame_refraction_enter;
    DWORD _frame_refraction_outer;
    bool _isRefracting;
    int _cnt_refraction;
public:
    /** �擱�`�b�v�i�{���̐擪�`�b�v�j�t���O */
    bool _is_leader; //�{���̐擪�`�b�v�Ƃ́A���[�U�[�ړ����ɂ�����Ĕ�������ɂ킩�擪�`�b�v�ł͖����Ƃ����Ӗ��B;
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

    int _num_refraction;
    DWORD _frame_refraction_interval;
    DWORD _frame_standstill;


    RefractionLaserChip(const char* prm_name, const char* prm_model);

    void setParam(int prm_num_refraction, DWORD prm_frame_refraction_interval, DWORD prm_frame_standstill) {
        _num_refraction = prm_num_refraction;
        _frame_refraction_interval = _frame_refraction_interval;
        _frame_standstill = prm_frame_standstill;
    }

    virtual void initialize() override;

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior() override;

    /**
     * ���܃��[�U�[�̐擪�`�b�v�̓������������� .
     * �{���̐擪�`�b�v�̏ꍇ�͂������R�[���o�b�N����邪�A
     * �ɂ킩�擪�`�b�v�i������ċ}�ɐ擪�ɂȂ����`�b�v�j�̏ꍇ���R�[���o�b�N����܂��B
     */
    virtual void processOnRefraction(int prm_num_refraction)=0;

    /**
     * ���[�U�[�`�b�v���蓙���� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processJudgement() ���\�b�h���Ăяo���Ă��������B
     * ���͖{���\�b�h�ŁAGgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld) ���Ăяo���Ă���A
     * ���̃^�C�~���O�Ń��[���h�ϊ��s�񂪊m�肵�܂��̂ŁA�I�[�o�[���C�h�̍ۂ͍Ō�� RefractionLaserChip::processJudgement(); ��
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


    //virtual void initializeRefraction(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_Target);

    virtual ~RefractionLaserChip();

};

}
#endif /*HOMINGLASERCHIP_H_*/

