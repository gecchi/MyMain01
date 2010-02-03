#ifndef MYLASERCHIP001_H_
#define MYLASERCHIP001_H_
namespace MyStg2nd {

class MyCurveLaserChip001 : public CurveLaserChip {

public:
    bool _is_lockon;
    MyDummyOption* _pOrg;
    velo _veloCurve;
    int _slow_renge;

    int _cnt_rev;

    MyCurveLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

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

