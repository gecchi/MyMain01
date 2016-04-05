#ifndef GGAFLIB_MASSWALLACTOR_H_
#define GGAFLIB_MASSWALLACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

#define FACE_A_IDX 5
#define FACE_B_IDX 4
#define FACE_C_IDX 3
#define FACE_D_IDX 2
#define FACE_E_IDX 1
#define FACE_F_IDX 0

#define FACE_A_BIT 32  // 0b100000
#define FACE_B_BIT 16  // 0b010000
#define FACE_C_BIT 8   // 0b001000
#define FACE_D_BIT 4   // 0b000100
#define FACE_E_BIT 2   // 0b000010
#define FACE_F_BIT 1   // 0b000001

namespace GgafLib {

/**
 * �O�ǃV�[��(WallSectionScene)�̕ǃu���b�N���N���X .
 * �O�ǃV�[��(WallSectionScene)�̍\���v�f�̕ǃu���b�N�͖{�N���X���p������K�v������B
 * @version 1.00
 * @since 2016/03/08
 * @author Masatoshi Tsuge
 */
class MassWallActor : public GgafDxCore::GgafDxMassMeshActor {
    friend class GgafDxEffectManager;

protected:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
        float _21, _22, _23, _24;   // : TEXCOORD2  World�ϊ��s��A�Q�s��
        float _31, _32, _33, _34;   // : TEXCOORD3  World�ϊ��s��A�R�s��
        float _41, _42, _43, _44;   // : TEXCOORD4  World�ϊ��s��A�S�s��
        float _wall_draw_face, _pos_info;  // : TEXCOORD5 �ǃu���b�N�v���Y���ʒu���, �ǃu���b�N�\����
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstaceData(void* prm, GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);

public:
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _h_wall_dep;
    static D3DXHANDLE _h_wall_height;
    static D3DXHANDLE _h_wall_width;
    static D3DXHANDLE _h_ah_POS_PRISM_ZX;
    static D3DXHANDLE _h_fh_POS_PRISM_ZX;
    static D3DXHANDLE _h_ah_POS_PRISM_YZ;
    static D3DXHANDLE _h_fh_POS_PRISM_YZ;
    static D3DXHANDLE _h_ah_POS_PRISM_XY;
    static D3DXHANDLE _h_fh_POS_PRISM_XY;
    static D3DXHANDLE _h_reflectance;

    /** �v���Y���������ǉ��`��s�v�ʃe�[�u�� */
    static std::map<int, UINT> _delface;

    /** [r]�ǃu���b�N�v���Y���ʒu���(> 0�̏ꍇ�̓v���Y�����̓s���~�b�h�A0�̏ꍇ��BOX) */
    int _pos_info;
    /** [r]�ǃu���b�N�\���ʏ�� */
    int _wall_draw_face;
    /** [r]�ǃu���b�N�̒����iX���W�������j*/
    coord _wall_dep;
    /** [r]�ǃu���b�N�̍����iY���W�������j*/
    coord _wall_height;
    /** [r]�ǃu���b�N�̕��iZ���W�������j*/
    coord _wall_width;
//    /** [r]�ǃu���b�N�ړ��X�s�[�h(�l�͐��A�A���ړ�������X�����̕���) */
//    int _scroll_speed;
    GgafLib::CollisionChecker3D* _pColliChecker;
    /** [r]�O�ǃV�[�� */
    WallSectionScene* _pWallSectionScene;

public:
    MassWallActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);
    MassWallActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect,
                  const char* prm_technique,
                  GgafCore::GgafStatus* prm_pStat=nullptr);
//    MassWallActor(const char* prm_name,
//                  const char* prm_model_id,
//                  const char* prm_effect_id,
//                  const char* prm_technique,
//                  GgafCore::GgafStatus* prm_pStat,
//                  GgafDxCore::GgafDxChecker* prm_pChecker);

    void init();

    static bool initStatic(MassWallActor* prm_pMassWallActor);

    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processPreDraw() override;

    virtual void processDraw() override;

    virtual bool isOutOfSpacetime() const override;

    virtual int isOutOfView() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    /**
     * �ǃu���b�N��ݒ肷�� .
     * @param prm_pWallSectionScene WallSectionScene�I�u�W�F�N�g
     * @param prm_pos_info �v���Y���ʒu�ԍ��i�v���Y���^�u���b�N�̏ꍇ�̂݁j
     * @param prm_wall_draw_face �ǃu���b�N�\���ʏ��
     * @param prm_aColliBoxStretch �ǃu���b�N�����蔻����
     */
    virtual void config(WallSectionScene* prm_pWallSectionScene,
                        int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch);

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~MassWallActor();
};

}
#endif /*GGAFLIB_WALLPARTSACTOR_H_*/
