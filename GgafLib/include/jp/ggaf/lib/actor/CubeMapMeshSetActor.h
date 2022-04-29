#ifndef GGAF_LIB_CUBEMAPMESHSETACTOR_H_
#define GGAF_LIB_CUBEMAPMESHSETACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/ex/CubeMapMeshSetActor.h"

namespace GgafLib {

/**
 * 環境マップメッシュセットアクター の具象クラス .
 * GgafDx::CubeMapMeshSetActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getPhase()</TD><TD>進捗管理</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getVecVehicle()</TD><TD>力車。移動回転支援</TD><TD>GgafDx::VecVehicle</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetActor : public GgafDx::CubeMapMeshSetActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pColliChecker;

public:
    CubeMapMeshSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~CubeMapMeshSetActor();
};

}
#endif /*GGAF_LIB_CUBEMAPMESHSETACTOR_H_*/
