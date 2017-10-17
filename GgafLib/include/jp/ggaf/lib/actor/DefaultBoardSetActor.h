#ifndef GGAFLIB_DEFAULTBOARDSETACTOR_H_
#define GGAFLIB_DEFAULTBOARDSETACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardSetActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDxCore::GgafDxBoardSetActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>黒衣。移動回転支援</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * </TABLE>
 * <B>【注意】</B>拡大縮小支援(GgafDxCore::GgafDxScaler)は使用出来ません。
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class DefaultBoardSetActor : public GgafDxCore::GgafDxBoardSetActor {
private:
    /**
     * 使用禁止 .
     * @return
     */
    GgafDxCore::GgafDxScaler* getScaler();

public:
    DefaultBoardSetActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultBoardSetActor();

};

}
#endif /*GGAFLIB_DEFAULTBOARDSETACTOR_H_*/
