#ifndef MYLASERCHIP001_H_
#define MYLASERCHIP001_H_
namespace MyStg2nd {

class MyCurveLaserChip001 : public CurveLaserChip {

public:


    MyCurveLaserChip001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~MyCurveLaserChip001();

};

}
#endif /*MYLASERCHIP001_H_*/

