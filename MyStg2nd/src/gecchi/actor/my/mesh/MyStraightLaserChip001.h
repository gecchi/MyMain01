#ifndef MYSTRAIGHTLASERCHIP001_H_
#define MYSTRAIGHTLASERCHIP001_H_
namespace MyStg2nd {

class MyStraightLaserChip001 : public StraightLaserChip {

public:

    MyStraightLaserChip001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    void onActive();

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~MyStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

