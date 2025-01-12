#ifndef GGAF_LIB_MASSWALLACTOR_H_
#define GGAF_LIB_MASSWALLACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MassMeshActor.h"

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
class MassWallActor : public GgafDx::MassMeshActor {
    friend class EffectManager;

protected:
    struct VERTEX_instancedata {
        float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
        float _21, _22, _23, _24;   // : TEXCOORD2  World�ϊ��s��A�Q�s��
        float _31, _32, _33, _34;   // : TEXCOORD3  World�ϊ��s��A�R�s��
        float _41, _42, _43, _44;   // : TEXCOORD4  World�ϊ��s��A�S�s��
        float r, g, b, a;           // : TEXCOORD5  �}�e���A���J���[
        float _wall_draw_face, _pos_info;  // : TEXCOORD6 �ǃu���b�N�v���Y���ʒu���, �ǃu���b�N�\����
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstanceData(void* prm, GgafDx::MassModel::VertexInstanceDataInfo* out_info);

public:
    /** �v���Y���������ǉ��`��s�v�ʃe�[�u�� */
    static std::map<int, UINT> _draw_face;

    /** [r]�ǃu���b�N���(0�̏ꍇ��BOX:0���傫���ꍇ�̓v���Y�����̓s���~�b�h) */
    pos_t _pos_info;
    /** [r]�ǃu���b�N�\���ʏ�� */
    int _wall_draw_face;
    /** [r]�ǃu���b�N�̒����iX���W�������j*/
    coord _wall_dep;
    /** [r]�ǃu���b�N�̍����iY���W�������j*/
    coord _wall_height;
    /** [r]�ǃu���b�N�̕��iZ���W�������j*/
    coord _wall_width;
//    /** [r]�ǃu���b�N�ړ��X�s�[�h(�l�͐��A�A���ړ�������X�����̕���) */
//    int _feature_p1;
    WorldCollisionChecker* _pWorldCollisionChecker;
    /** [r]�O�ǃV�[�� */
    WallSectionScene* _pWallSectionScene;

public:
    MassWallActor(const char* prm_name, const char* prm_model);
    MassWallActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect,
                  const char* prm_technique);
//    MassWallActor(const char* prm_name,
//                  const char* prm_model,
//                  const char* prm_effect_id,
//                  const char* prm_technique);
//                  GgafDx::CollisionChecker* prm_pColliChecker);

    void init();

    static bool initStatic(MassWallActor* prm_pMassWallActor);

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

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual void drawHitArea() override;

    /**
     * �ǃu���b�N��ݒ肷�� .
     * @param prm_pWallSectionScene WallSectionScene�I�u�W�F�N�g
     * @param prm_pos_info 0:BOX/1�`:�v���Y��or�s���~�b�h�ʒu�ԍ�(POS_***)
     * @param prm_wall_draw_face �ǃu���b�N�\���ʏ��
     * @param prm_aColliBoxStretch �ǃu���b�N�����蔻����
     */
    virtual void config(WallSectionScene* prm_pWallSectionScene,
                        pos_t prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch);

    virtual GgafDx::CollisionChecker* createChecker(kind_t prm_kind = 0) override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    /**
     * ���f���������P�������Ēǉ�����B .
     * ���߂Ė{���\�b�h�����s����ƁA�������X�g�ɕێ�����A���̃��f���������L���ɂȂ�܂��B
     * �Q��ڈȍ~�̎��s�́A�����������f��������������X�g�̖����ɒǉ����܂��B�i�L���ɂȂ�܂���j
     * @param prm_model ���f����`��
     */
    virtual void addModel(const char* prm_model) override;

    virtual ~MassWallActor();
};

}
#endif /*GGAF_LIB_WALLPARTSACTOR_H_*/
