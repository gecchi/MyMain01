#ifndef WORLDBOUNDACTOR_H_
#define WORLDBOUNDACTOR_H_
namespace GgafDx9LibStg {

/**
 * 世界境界.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundActor : public GgafDx9Core::GgafDx9SpriteMeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    UINT32 _frame_offset;

    WorldBoundActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

   virtual void processSettlementBehavior() override;
//
//    virtual void processPreDraw() override;

    virtual void processHappen(int prm_no) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    int isOffscreen() override {
        //画面外判定無し
        return 0;
    }

    bool isOutOfGameSpace() override {;
        //ゲーム座標範囲外判定無し
        return false;
    }
    virtual ~WorldBoundActor();
};

}
#endif /*WORLDBOUNDACTOR_H_*/
