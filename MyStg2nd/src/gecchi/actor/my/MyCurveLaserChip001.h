#ifndef MYLASERCHIP001_H_
#define MYLASERCHIP001_H_
namespace MyStg2nd {

class MyCurveLaserChip001 : public GgafDx9LibStg::CurveLaserChip {

public:
    /** 0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int _lockon;
    MyOption* _pOrg;
    velo _veloCurve;
    int _renge;
    float _maxAcceRange;

    int _new_target_X;
    int _new_target_Y;
    int _new_target_Z;
    bool _isLockOn;
    int _default_stamina;

    MyCurveLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void processFinal();

//    bool isOutOfGameSpace() override {
//        if (isOffscreen() == 0) {
//            return false;
//        } else {
//            return true;
//        }
//    }

    virtual ~MyCurveLaserChip001();

};

}
#endif /*MYLASERCHIP001_H_*/

