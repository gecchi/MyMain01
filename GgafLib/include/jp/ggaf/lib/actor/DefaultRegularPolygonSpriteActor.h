#ifndef GGAF_LIB_DEFAULTREGULARPOLYGONSPRITEACTOR_H_
#define GGAF_LIB_DEFAULTREGULARPOLYGONSPRITEACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/RegularPolygonSpriteActor.h"

namespace GgafLib {

/**
 * 正多角形スプライトアクターの具象クラス.
 * GgafDx::RegularPolygonSpriteActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::Progress</TD></TR>
 * <TR><TD>callRikisha()</TD><TD>力車。移動回転支援</TD><TD>GgafDx::Rikisha</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class DefaultRegularPolygonSpriteActor : public GgafDx::RegularPolygonSpriteActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pColliChecker;

public:
    DefaultRegularPolygonSpriteActor(const char* prm_name, const char* prm_model_id);

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

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultRegularPolygonSpriteActor();

};

}
#endif /*GGAF_LIB_DEFAULTREGULARPOLYGONSPRITEACTOR_H_*/
