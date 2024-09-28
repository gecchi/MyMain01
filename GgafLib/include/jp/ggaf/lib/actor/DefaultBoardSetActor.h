#ifndef GGAF_LIB_DEFAULTBOARDSETACTOR_H_
#define GGAF_LIB_DEFAULTBOARDSETACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/BoardSetActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx::BoardSetActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getPhase()</TD><TD>フェーズ管理</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocusVehicle()</TD><TD>移動車両。移動回転支援</TD><TD>GgafDx::LocusVehicle</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * </TABLE>
 * <B>【注意】</B>拡大縮小支援(GgafDx::Scaler)は使用出来ません。
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class DefaultBoardSetActor : public GgafDx::BoardSetActor {
private:
    /**
     * 使用禁止 .
     * @return
     */
    GgafDx::Scaler* getScaler();

public:

    /** 衝突判定支援オブジェクト */
    ViewCollisionChecker* _pViewCollisionChecker;

    DefaultBoardSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

//    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
//        return false;
//    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;

    inline ViewCollisionChecker* getViewCollisionChecker() {
        return _pViewCollisionChecker;
    }

    virtual ~DefaultBoardSetActor();

};

}
#endif /*GGAF_LIB_DEFAULTBOARDSETACTOR_H_*/
