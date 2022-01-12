#ifndef GGAF_LIB_DEFAULTMASSSPRITEACTOR_H_
#define GGAF_LIB_DEFAULTMASSSPRITEACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassSpriteActor.h"

namespace GgafLib {

/**
 * スプライトセットアクターの具象クラス.
 * GgafDx::MassSpriteActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::Progress</TD></TR>
 * <TR><TD>getVecDriver()</TD><TD>力車。移動回転支援</TD><TD>GgafDx::VecDriver</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>効果音発生管理</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>衝突判定支援</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class DefaultMassSpriteActor : public GgafDx::MassSpriteActor {

private:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float offset_u, offset_v;   // : TEXCOORD5  テクスチャオフセット
        float r, g, b, a;           // : TEXCOORD6  マテリアルカラー
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);
public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pColliChecker;

    DefaultMassSpriteActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultMassSpriteActor();

};

}
#endif /*GGAF_LIB_DEFAULTMASSSPRITEACTOR_H_*/
