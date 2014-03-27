#ifndef GGAFLIB_CUBEMAPMORPHMESHACTOR_H_
#define GGAFLIB_CUBEMAPMORPHMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMorphMeshActor.h"

namespace GgafLib {

/**
 * 環境マップモーフメッシュアクターの具象クラス .
 * GgafDxCore::GgafDxMorphMeshActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>黒衣。移動回転支援</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>getSeTx()</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>getMorpher()</TD><TD>モーフィング支援</TD><TD>GgafDxCore::GgafDxMorpher</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshActor : public GgafDxCore::GgafDxCubeMapMorphMeshActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    CubeMapMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~CubeMapMorphMeshActor();
};

}
#endif /*GGAFLIB_CUBEMAPMORPHMESHACTOR_H_*/
