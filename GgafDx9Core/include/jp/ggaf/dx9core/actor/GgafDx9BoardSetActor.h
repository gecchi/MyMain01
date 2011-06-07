#ifndef GGAFDX9BOARDSETACTORD_H_
#define GGAFDX9BOARDSETACTORD_H_
namespace GgafDx9Core {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[.
 * GgafDx9TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ����A����ɑ�ʕ\�����ɓ��ꃂ�f���͈ꊇ�`����s���悤�ɍœK���������A�N�^�[�B<BR>
 * �P���\���i��]�g�喳���j�̂��ߍ����B�X�R�A�\����A�w�i���Ɏg�p���悤�B<BR>
 * �Q�c�Q�[�������Ȃ�A�L�����N�^�I�u�W�F�N�g�͂��̃N���X��{�ł�����B<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardSetActor : public GgafDx9DrawableActor {
private:
    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    int isOutOfView() override {
        return 0;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    bool isOutOfUniverse() override {
        return false;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    GgafCore::GgafGroupActor* addSubBone(actorkind prm_kind,
                                         GgafDx9GeometricActor* prm_pGeoActor,
                                         int prm_X_init_local,
                                         int prm_Y_init_local,
                                         int prm_Z_init_local,
                                         int prm_RX_init_local,
                                         int prm_RZ_init_local,
                                         int prm_RY_init_local) override {
        return NULL;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    GgafCore::GgafGroupActor* addSubBone(GgafDx9GeometricActor* prm_pGeoActor,
                                         int prm_X_init_local,
                                         int prm_Y_init_local,
                                         int prm_Z_init_local,
                                         int prm_RX_init_local,
                                         int prm_RZ_init_local,
                                         int prm_RY_init_local) override {
        return NULL;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void changeGeoLocal() override {
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void changeGeoFinal() override {
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void rotateWith(GgafDx9GeometricActor* prm_pActor) override {
    }

public:
    int _draw_set_num;
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9BoardSetModel* _pBoardSetModel;
    /** �G�t�F�N�g */
    GgafDx9BoardSetEffect* _pBoardSetEffect;
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9BoardSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDx9BoardSetActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDSETACTORD_H_*/
