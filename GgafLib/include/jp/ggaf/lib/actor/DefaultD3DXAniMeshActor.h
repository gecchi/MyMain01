#ifndef GGAFLIB_DEFAULTD3DXANIMESHACTOR_H_
#define GGAFLIB_DEFAULTD3DXANIMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"

namespace GgafLib {

/**
 * フレームアニメーションメッシュアクターの具象クラス .
 * GgafDxCore::GgafDxD3DXAniMeshActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>黒衣。移動回転支援</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>_pPuppeteer</TD><TD>フレームアニメーション支援</TD><TD>GgafDxCore::GgafDxPuppeteer</TD></TR>
 * <TR><TD>getSeTx()</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class DefaultD3DXAniMeshActor : public GgafDxCore::GgafDxD3DXAniMeshActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultD3DXAniMeshActor();
};

}
#endif /*GGAFLIB_DEFAULTD3DXANIMESHACTOR_H_*/
