#ifndef CURVELASERCHIP_H_
#define CURVELASERCHIP_H_
namespace MyStg2nd {

class CurveLaserChip : public LaserChip {
    friend class CurveLaserChipDispatcher;
public:
    CurveLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void onActive();

    virtual void onInactive();

    virtual ~CurveLaserChip();

};

}
#endif /*CURVELASERCHIP_H_*/

