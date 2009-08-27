#ifndef MYLASERCHIP001_H_
#define MYLASERCHIP001_H_
namespace MyStg2nd {

class MyLaserChip001 : public CurveLaserChip {

public:

    MyLaserChip001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize();

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~MyLaserChip001();

};

}
#endif /*MYLASERCHIP001_H_*/

