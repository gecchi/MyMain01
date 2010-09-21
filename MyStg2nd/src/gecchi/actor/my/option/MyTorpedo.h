#ifndef MYTORPEDO_H_
#define MYTORPEDO_H_

#define MyTorpedo_IN_FIRE 1
#define MyTorpedo_RELEASE 2
namespace MyStg2nd {



/**
 * ‹›—‹ .
 * @version 1.00
 * @since 2010/07/26
 * @author Masatoshi Tsuge
 */
class MyTorpedo : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    MyOptionTorpedoController* _pMyOptionTorpedoController;
//    MyTorpedoTail* _pMyTorpedoTailChip_Head;
    int _length_TailEffect;

    int _begin_X,_begin_Y,_begin_Z;

    GgafDx9LibStg::LaserChipDispatcher* _pTailEffectDispatcher;

    GgafDx9Core::GgafDx9GeometricActor* _pTarget;
    MyTorpedo(const char* prm_name, MyOptionTorpedoController* prm_pMyOptionTorpedoController);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyTorpedo();
};

}
#endif /*MYTORPEDO*/

