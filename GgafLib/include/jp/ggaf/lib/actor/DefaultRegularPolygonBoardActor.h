#ifndef GGAF_LIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#define GGAF_LIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/RegularPolygonBoardActor.h"

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
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class DefaultRegularPolygonBoardActor : public GgafDx::RegularPolygonBoardActor {

public:
    DefaultRegularPolygonBoardActor(const char* prm_name, const char* prm_model);

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

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual ~DefaultRegularPolygonBoardActor();

};

}
#endif /*GGAF_LIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_*/
