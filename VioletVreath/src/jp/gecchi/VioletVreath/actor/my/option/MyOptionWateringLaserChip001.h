#ifndef MYOPTIONCURVELASERCHIP001_H_
#define MYOPTIONCURVELASERCHIP001_H_
namespace VioletVreath {

/**
 * �I�v�V�������[�U�[�̃`�b�v .
 * WateringLaserChip �� ���b�N�I���@�\��ǉ��B
 * (WateringLaserChip���番������)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyOptionWateringLaserChip001 : public GgafLib::WateringLaserChip {
    /** �ϋv�͏����ݒ�l */
    int _default_stamina;
    /** �����x�͈�( _max_velo_renge / _r_max_acce ) */
    float _max_acce_renge;
    /** �`�b�v�̓������v�Z */
    void moveChip(int vTx, int vTy, int vTz);

public:
    /** [r]���b�N�I�����Ă���ꍇ true */
    bool _isLockon;
    /** [r]0:�񃍃b�N�I���i�͂��߂���j 1:���b�N�I�� 2:�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j */
    int _lockon;
    /** [r]���[�U�[���ˌ� */
    MyOption* _pOrg;
    /** [r/w]���x�͈́i���̒l��傫������ƁA�ō����x�������Ȃ�B�j */
    int _max_velo_renge;
    /** [r/w]���x�ɑ΂�������x�̊����i���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�j */
    int _r_max_acce;

    MyOptionWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOptionWateringLaserChip001();

};

}
#endif /*MYOPTIONCURVELASERCHIP001_H_*/

