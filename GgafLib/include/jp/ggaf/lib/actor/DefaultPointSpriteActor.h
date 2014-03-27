#ifndef GGAFLIB_DEFAULTPOINTSPRITEACTOR_H_
#define GGAFLIB_DEFAULTPOINTSPRITEACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"

namespace GgafLib {

/**
 * スプライトアクターの具象クラス.
 * GgafDxCore::GgafDxPointSpriteActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>黒衣。移動回転支援</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>getSeTx()</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/02/25
 * @author Masatoshi Tsuge
 */
class DefaultPointSpriteActor : public GgafDxCore::GgafDxPointSpriteActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultPointSpriteActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultPointSpriteActor();

};

}
#endif /*GGAFLIB_DEFAULTPOINTSPRITEACTOR_H_*/
