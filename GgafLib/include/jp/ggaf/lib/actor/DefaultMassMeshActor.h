#ifndef GGAFLIB_DEFAULTMASSMESHACTOR_H_
#define GGAFLIB_DEFAULTMASSMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

namespace GgafLib {

/**
 * メッシュアクターの具象クラス.
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class DefaultMassMeshActor : public GgafDxCore::GgafDxMassMeshActor {

private:
    class VERTEX_instancedata {
    public:
        float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
        float _21, _22, _23, _24;   // : TEXCOORD2  World変換行列、２行目
        float _31, _32, _33, _34;   // : TEXCOORD3  World変換行列、３行目
        float _41, _42, _43, _44;   // : TEXCOORD4  World変換行列、４行目
        float r, g, b, a;           // : TEXCOORD5  マテリアルカラー
    };
    static VERTEX_instancedata _aInstancedata[GGAFDXMASS_MAX_INSTACE];
    static void createVertexInstaceData(GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

    DefaultMassMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultMassMeshActor();
};

}
#endif /*GGAFLIB_DEFAULTMASSMESHACTOR_H_*/
