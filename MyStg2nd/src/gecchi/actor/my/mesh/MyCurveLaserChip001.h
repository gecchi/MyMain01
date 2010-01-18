#ifndef MYLASERCHIP001_H_
#define MYLASERCHIP001_H_
namespace MyStg2nd {

class MyCurveLaserChip001 : public CurveLaserChip {

public:


    MyCurveLaserChip001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    void onActive() override;

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~MyCurveLaserChip001();

};

}
#endif /*MYLASERCHIP001_H_*/

