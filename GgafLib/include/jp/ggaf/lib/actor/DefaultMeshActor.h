#ifndef DEFAULTMESHACTOR_H_
#define DEFAULTMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace GgafLib {

/**
 * メッシュアクターの具象クラス .
 * GgafDxCore::GgafDxMeshActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>参照変数</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>_pProg</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>黒衣A。移動回転支援</TD><TD>GgafDxCore::GgafDxKurokoA</TD></TR>
 * <TR><TD>_pKrokoB</TD><TD>黒衣B。移動支援</TD><TD>GgafDxCore::GgafDxKurokoB</TD></TR>
 * <TR><TD>_pAFader</TD><TD>フィードイン・アウト支援</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pScaler</TD><TD>拡大縮小支援</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pSeTx</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/02/19
 * @author Masatoshi Tsuge
 */
class DefaultMeshActor : public GgafDxCore::GgafDxMeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_model モデル定義
     * @param prm_pStat 定義済みのステータスを渡す。種別(STAT_DEFAULT_ACTOR_KIND)は衝突判定で使用される。
     */
    DefaultMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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


    virtual ~DefaultMeshActor();
};

}
#endif /*DEFAULTMESHACTOR_H_*/
