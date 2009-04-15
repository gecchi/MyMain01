#ifndef MYLASERCHIP_H_
#define MYLASERCHIP_H_
namespace MyStg2nd {

class MyLaserChip : public GgafDx9Core::GgafDx9MeshActor {

private:
    D3DXHANDLE _hX, _hY, _hZ, _hMatWorld_front;

public:
    /** 一つ前方のレーザーチップ */
    MyLaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
	MyLaserChip* _pChip_behind;
    /** 自身のWORLD変換行列 */
    D3DXMATRIX _matWorld;
    /** 一つ前方のWORLD変換行列 */
    D3DXMATRIX _matWorld_front;
    /** 自身を管理してるローテーションアクター */
    MyLaserChipRotationActor* _pRotation;
    /** 発射元アクター */
    GgafDx9UntransformedActor* _pActor_Radical;


    GgafDx9LibStg::StgChecker* _pChecker;


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

    bool isOffScreen();

    /**
     * 出現時コールバック実装
     */
    void onActive();

    /**
     * 消失時コールバック実装
     */
    void onInactive();

    virtual ~MyLaserChip();

};

}
#endif /*MYLASERCHIP_H_*/

