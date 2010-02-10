#ifndef MYLASERCHIP001_H_
#define MYLASERCHIP001_H_
namespace MyStg2nd {

class MyCurveLaserChip001 : public CurveLaserChip {

public:
    /** 0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int _lockon;
    MyDummyOption* _pOrg;
    velo _veloCurve;
    int _renge;

    MyCurveLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void processFinal();

    bool isOutOfGameSpace() override {
        if (isOffscreen() == 0) {
            return false;
        } else {
            return true;
        }
    }
    virtual ~MyCurveLaserChip001();

};

}
#endif /*MYLASERCHIP001_H_*/

