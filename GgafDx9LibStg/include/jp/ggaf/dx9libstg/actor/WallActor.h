#ifndef WALLACTOR_H_
#define WALLACTOR_H_


#define FACE_A_IDX 5
#define FACE_B_IDX 4
#define FACE_C_IDX 3
#define FACE_D_IDX 2
#define FACE_E_IDX 1
#define FACE_F_IDX 0


namespace GgafDx9LibStg {

/**
 * �O�ǃV�[��(WalledSectionScene)�̕ǃu���b�N���N���X .
 * �O�ǃV�[��(WalledSectionScene)�̍\���v�f�̕ǃu���b�N�͖{�N���X���p������K�v������B
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WallActor : public GgafDx9Core::GgafDx9MeshSetActor {
    friend class GgafDx9EffectManager;

private:
    /** [r]�ǃu���b�N�\���ʏ�� */
    int _wall_draw_face;
    /** [r]�ǃu���b�N�̒����iX���W�������j*/
    int _wall_dep;
    /** [r]�ǃu���b�N�̍����iY���W�������j*/
    int _wall_height;
    /** [r]�ǃu���b�N�̕��iZ���W�������j*/
    int _wall_width;
//    /** [r]�ǃu���b�N�ړ��X�s�[�h(�l�͐��A�A���ړ�������X�����̕���) */
//    int _scrool_speed;

public:
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;
    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    /** [r]�O�ǃV�[�� */
    WalledSectionScene* _pWalledSectionScene;
    D3DXHANDLE _h_distance_AlphaTarget;

    WallActor(const char* prm_name, const char* prm_model);


    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor);

    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processDraw() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual bool isOutOfUniverse() override;

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
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
    virtual void config(WalledSectionScene* prm_pWalledSectionScene, int prm_wall_draw_face, int* prm_aColliBoxStretch);


    virtual ~WallActor();
};

}
#endif /*WALLACTOR_H_*/
