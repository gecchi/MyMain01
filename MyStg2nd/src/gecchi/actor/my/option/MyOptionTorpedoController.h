#ifndef MYOPTIONTORPEDOCONTROLLER_H_
#define MYOPTIONTORPEDOCONTROLLER_H_
namespace MyStg2nd {


/**
 * 魚雷コントローラー .
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyOptionTorpedoController : public GgafCore::GgafDummyActor {

public:

   // GgafDx9LibStg::HomingLaserChip*** _papaHomingLaserChip;

    GgafDx9LibStg::LaserChipDispatcher** _papLaserChipDispatcher;
    MyTorpedoChip** _papMyTorpedoChip_Head;
    MyOption* _pMyOption;
    bool* _pa_all_employed;
    int _length_TorpedoChip;
    //bool _ready_to_fire;
    int _firing_num;
    bool _in_firing;

    MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void releaseAllLockon();

    void lockon(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget);

    virtual ~MyOptionTorpedoController();

    void fire();

};

}
#endif /*MYOPTIONTORPEDOCONTROLLER_H_*/

