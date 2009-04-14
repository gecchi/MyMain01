#ifndef MYLASERCHIP_H_
#define MYLASERCHIP_H_
namespace MyStg2nd {

class MyLaserChip : public GgafDx9Core::GgafDx9MeshActor {
public:
    D3DXHANDLE _hX, _hY, _hZ;
    int _prevX, _prevY, _prevZ;
    MyLaserChip* _pChip_front;
	MyLaserChip* _pChip_behind;
    DWORD _lifeframe_prev;

    MyLaserChipRotationActor* _pRotation;


    GgafDx9LibStg::StgChecker* _pChecker;

    /** 対象アクター */
    GgafDx9UntransformedActor* _pActor_Radical;

    MyLaserChip(const char* prm_name, MyLaserChipRotationActor* prm_pRotation);

    /**
     * ＜OverRide です＞
     */
    void initialize();

    /**
     * ＜OverRide です＞
     */
    void processBehavior();

    /**
     * ＜OverRide です＞
     */
    void processJudgement();

    void processDrawPrior() {
        GgafDx9Core::GgafDx9MeshActor::processDrawPrior();
    }

    void processDrawTerminate();

    /**
     * ＜OverRide です＞
     */
    void processDrawMain();

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    /**
     * ＜OverRide です＞
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
        _pActor_Radical = prm_pActor;
    }

    MyLaserChip* getNext() {
        return (MyLaserChip*)_pNext;
    }

    MyLaserChip* getPrev() {
        return (MyLaserChip*)_pPrev;
    }

    bool isOffScreen();

    virtual ~MyLaserChip();

};

}
#endif /*MYLASERCHIP_H_*/

