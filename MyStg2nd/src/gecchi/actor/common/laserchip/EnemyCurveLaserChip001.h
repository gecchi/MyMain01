#ifndef ENEMYCURVELASERCHIP001_H_
#define ENEMYCURVELASERCHIP001_H_
namespace MyStg2nd {

class EnemyCurveLaserChip001 : public GgafDx9LibStg::CurveLaserChip {

public:
    /** 0:�񃍃b�N�I���i�͂��߂���j 1:���b�N�I�� 2:�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j */
    int _lockon;
    MyOption* _pOrg;
    velo _veloCurve;
    int _renge;
    float _maxAcceRange;


    EnemyCurveLaserChip001(const char* prm_name);

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

    virtual ~EnemyCurveLaserChip001();

};

}
#endif /*ENEMYCURVELASERCHIP001_H_*/

