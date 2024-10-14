#ifndef GGAF_LIB_DEFAULTMASSMORPHMESHACTOR_H_
#define GGAF_LIB_DEFAULTMASSMORPHMESHACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassMorphMeshActor.h"

namespace GgafLib {

/**
 * モーフメッシュアクターの具象クラス.
 * GgafDx::MassMorphMeshActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getPhase()</TD><TD>フェーズ管理</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocusVehicle()</TD><TD>移動車両。移動回転支援</TD><TD>GgafDx::LocusVehicle</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getMorpher()</TD><TD>モーフィング支援</TD><TD>GgafDx::Morpher</TD></TR>
 * <TR><TD>getWorldCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::WorldCollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class DefaultMassMorphMeshActor : public GgafDx::MassMorphMeshActor {

    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float r, g, b, a;           // : TEXCOORD5  マテリアルカラー
        //_14 : モーフターゲット1の重みの値が埋め込まれる。シェーダー内で取り出し後0に上書き。
        //_24 : モーフターゲット2の重みの値が埋め込まれる。シェーダー内で取り出し後0に上書き。
        //_34 : モーフターゲット3の重みの値が埋め込まれる。シェーダー内で取り出し後0に上書き。
        //_44 : モーフターゲット4の重みの値が埋め込まれる。シェーダー内で取り出し後1に上書き。
    };

    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pWorldCollisionChecker;

public:
    DefaultMassMorphMeshActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~DefaultMassMorphMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTMASSMORPHMESHACTOR_H_*/
