#ifndef GGAFLIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#define GGAFLIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxRegularPolygonBoardActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDxCore::GgafDxBoardActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>黒衣。移動支援(※正面方角回転機能はZ軸回転のみ有効)</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class DefaultRegularPolygonBoardActor : public GgafDxCore::GgafDxRegularPolygonBoardActor {

public:
    DefaultRegularPolygonBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultRegularPolygonBoardActor();

};

}
#endif /*GGAFLIB_DEFAULTREGULARPOLYGONBOARDACTOR_H_*/
