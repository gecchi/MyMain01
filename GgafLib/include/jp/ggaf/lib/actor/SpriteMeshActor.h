#ifndef GGAF_LIB_SPRITEMESHACTOR_H_
#define GGAF_LIB_SPRITEMESHACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/ex/SpriteMeshActor.h"

namespace GgafLib {

/**
 * テクスチャアニメーション可能メッシュアクターの具象クラス.
 * GgafDx::SpriteMeshActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getPhase()</TD><TD>フェーズ管理</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocusVehicle()</TD><TD>移動車両。移動回転支援</TD><TD>GgafDx::LocusVehicle</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>テクスチャローテーション支援</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getWorldCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::WorldCollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2010/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshActor : public GgafDx::SpriteMeshActor {
public:
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pWorldCollisionChecker;
public:
    SpriteMeshActor(const char* prm_name, const char* prm_model);

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

    virtual GgafDx::CollisionChecker* createChecker() override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~SpriteMeshActor();
};

}
#endif /*GGAF_LIB_SPRITEMESHACTOR_H_*/
