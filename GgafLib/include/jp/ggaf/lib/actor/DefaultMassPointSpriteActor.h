#ifndef GGAF_LIB_DEFAULTMASSPOINTSPRITEACTOR_H_
#define GGAF_LIB_DEFAULTMASSPOINTSPRITEACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassPointSpriteActor.h"

namespace GgafLib {

/**
 * TODO: �g���܂���A���ˑ�������.
 */
class DefaultMassPointSpriteActor : public GgafDx::MassPointSpriteActor {

private:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
        float _21, _22, _23, _24;   // : TEXCOORD2  World�ϊ��s��A�Q�s��
        float _31, _32, _33, _34;   // : TEXCOORD3  World�ϊ��s��A�R�s��
        float _41, _42, _43, _44;   // : TEXCOORD4  World�ϊ��s��A�S�s��
        float r, g, b, a;           // : TEXCOORD5  �}�e���A���J���[
        float pattno_uvflip_now;    // : TEXCOORD6

    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker* _pColliChecker;

    DefaultMassPointSpriteActor(const char* prm_name, const char* prm_model);

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

    virtual ~DefaultMassPointSpriteActor();
};

}
#endif /*GGAF_LIB_DEFAULTMASSMESHACTOR_H_*/
