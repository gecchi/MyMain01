#ifndef MYSTRAIGHTLASERCHIP001_H_
#define MYSTRAIGHTLASERCHIP001_H_
namespace MyStg2nd {

class MyStraightLaserChip001 : public StraightLaserChip {

public:

    MyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

