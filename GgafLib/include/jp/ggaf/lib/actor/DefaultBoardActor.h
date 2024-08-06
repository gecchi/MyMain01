#ifndef GGAF_LIB_DEFAULTBOARDACTOR_H_
#define GGAF_LIB_DEFAULTBOARDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/BoardActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDx::BoardActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getPhase()</TD><TD>フェーズ管理</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocusVehicle()</TD><TD>移動車両。移動支援(※正面方角回転機能はZ軸回転のみ有効)</TD><TD>GgafDx::LocusVehicle</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/03/11
 * @author Masatoshi Tsuge
 */
class DefaultBoardActor : public GgafDx::BoardActor {

public:
    /** 衝突判定支援オブジェクト */
    ViewCollisionChecker* _pColliCollisionChecker;

    DefaultBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline ViewCollisionChecker* getViewCollisionChecker() {
        return _pColliCollisionChecker;
    }

    virtual ~DefaultBoardActor();

};

}
#endif /*GGAF_LIB_DEFAULTBOARDACTOR_H_*/
