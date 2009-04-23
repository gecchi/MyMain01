#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace MyStg2nd {

class LaserChip : public GgafDx9Core::GgafDx9MeshActor {

private:
    D3DXHANDLE _hKind, _hX, _hY, _hZ, _hMatWorld_front;

public:
    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
	LaserChip* _pChip_behind;
    /** 自身のWORLD変換行列 */
    D3DXMATRIX _matWorld;
    /** 一つ前方のWORLD変換行列 */
    D3DXMATRIX _matWorld_front;
    /** 自身を管理してるローテーションアクター */
    LaserChipRotationActor* _pRotation;

    GgafDx9LibStg::StgChecker* _pChecker;


    LaserChip(const char* prm_name, const char* prm_model, LaserChipRotationActor* prm_pRotation);

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

    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

