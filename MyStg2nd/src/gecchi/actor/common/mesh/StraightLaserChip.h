#ifndef STRAIGHTLASERCHIP_H_
#define STRAIGHTLASERCHIP_H_
namespace MyStg2nd {

class StraightLaserChip : public LaserChip {

public:

    int _X_onActive;
    int _Y_onActive;
    int _Z_onActive;

    GgafDx9Core::GgafDx9GeometricActor* _pSourceActor;


    StraightLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual void onActive();

    virtual void processJudgement();

    virtual ~StraightLaserChip();

};

}
#endif /*STRAIGHTLASERCHIP_H_*/

