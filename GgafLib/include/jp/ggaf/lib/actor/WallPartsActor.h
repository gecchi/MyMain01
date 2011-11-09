#ifndef WALLPARTSACTOR_H_
#define WALLPARTSACTOR_H_


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
 * �O�ǃV�[��(WalledSectionScene)�̕ǃu���b�N���N���X .
 * �O�ǃV�[��(WalledSectionScene)�̍\���v�f�̕ǃu���b�N�͖{�N���X���p������K�v������B
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WallPartsActor : public GgafDxCore::GgafDxMeshSetActor {
    friend class GgafDxEffectManager;

public:
    /** [r]�ǃu���b�N�v���Y���ʒu���(> 0�̏ꍇ�̓v���Y���A0�̏ꍇ��BOX) */
    int _pos_prism;
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


    GgafDxCore::GgafDxScaler* _pScaler;
    GgafLib::CollisionChecker* _pCollisionChecker;

    /** [r]�O�ǃV�[�� */
    WalledSectionScene* _pWalledSectionScene;


    WallPartsActor(const char* prm_name,
              const char* prm_model_id,
              const char* prm_effect_id,
              const char* prm_technique,
              GgafCore::GgafStatus* prm_pStat
              );


    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor);

    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processDraw() = 0;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processPreDraw() override;

    virtual bool isOutOfUniverse() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    /**
     * �ǃu���b�N��ݒ肷��
     * @param prm_wall_draw_face �ǃu���b�N�\���ʏ��
     * @param prm_aColliBoxStretch �ǃu���b�N�����蔻����
     */
    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch);


    virtual ~WallPartsActor();
};

}
#endif /*WALLPARTSACTOR_H_*/