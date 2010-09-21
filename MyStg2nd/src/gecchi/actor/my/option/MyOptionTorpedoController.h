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
    /** 親となるオプション */
    MyOption* _pMyOption;
    MyTorpedo** _papMyTorpedo;

    //GgafDx9LibStg::LaserChipDispatcher** _papMyTorpedoTailChipDispatcher;
    //MyTorpedoTail** _papMyTorpedoTailChip_Head;

    //bool* _pa_all_employed_MyTorpedoTailChip;
    //int _length_MyTorpedoTailChip;
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

