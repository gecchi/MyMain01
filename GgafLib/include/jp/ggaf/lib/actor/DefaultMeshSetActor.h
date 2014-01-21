#ifndef GGAFLIB_DEFAULTMESHSETACTOR_H_
#define GGAFLIB_DEFAULTMESHSETACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"

namespace GgafLib {

/**
 * メッシュアクターの具象クラス.
 * GgafDxCore::GgafDxMeshSetActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>参照変数</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>_pProg</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKroko</TD><TD>黒衣。移動回転支援</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>_pSeTx</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/06/16
 * @author Masatoshi Tsuge
 */
class DefaultMeshSetActor : public GgafDxCore::GgafDxMeshSetActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultMeshSetActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual ~DefaultMeshSetActor();
};

}
#endif /*GGAFLIB_DEFAULTMESHSETACTOR_H_*/
