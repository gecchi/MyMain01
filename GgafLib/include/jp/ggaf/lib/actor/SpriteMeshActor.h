#ifndef GGAFLIB_SPRITEMESHACTOR_H_
#define GGAFLIB_SPRITEMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshActor.h"

namespace GgafLib {

/**
 * テクスチャアニメーション可能メッシュアクターの具象クラス.
 * GgafDxCore::GgafDxSpriteMeshActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>参照変数</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>_pProg</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>黒衣A。移動回転支援</TD><TD>GgafDxCore::GgafDxKurokoA</TD></TR>
 * <TR><TD>_pKrokoB</TD><TD>黒衣B。移動支援</TD><TD>GgafDxCore::GgafDxKurokoB</TD></TR>
 * <TR><TD>_pAFader</TD><TD>フィードイン・アウト支援</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pUvFlipper</TD><TD>テクスチャローテーション支援</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>_pSeTx</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pScaler</TD><TD>拡大縮小支援</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2010/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshActor : public GgafDxCore::GgafDxSpriteMeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* const _pScaler;
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    SpriteMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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


    virtual ~SpriteMeshActor();
};

}
#endif /*GGAFLIB_SPRITEMESHACTOR_H_*/
