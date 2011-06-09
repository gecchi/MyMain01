#ifndef MYOPTIONCURVELASERCHIP001_H_
#define MYOPTIONCURVELASERCHIP001_H_
namespace MyStg2nd {

/**
 * �I�v�V�������[�U�[�̃`�b�v .
 * WateringLaserChip �� ���b�N�I���@�\��ǉ��B
 * (WateringLaserChip���番������)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyOptionWateringLaserChip001 : public GgafDx9LibStg::WateringLaserChip {

public:
    /** 0:�񃍃b�N�I���i�͂��߂���j 1:���b�N�I�� 2:�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j */
    int _lockon;
    MyOption* _pOrg;
    velo _veloCurve;
    int _renge;
    float _maxAcceRange;

    int _new_target_X;
    int _new_target_Y;
    int _new_target_Z;
    bool _isLockon;
    int _default_stamina;


    jerk _jerkVx;
    jerk _jerkVy;
    jerk _jerkVz;

    MyOptionWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

//    void processFinal();

//    bool isOutOfUniverse() override {
//        if (isOutOfView() == 0) {
//            return false;
//        } else {
//            return true;
//        }
//    }

    virtual ~MyOptionWateringLaserChip001();

};

}
#endif /*MYLASERCHIP001_H_*/

