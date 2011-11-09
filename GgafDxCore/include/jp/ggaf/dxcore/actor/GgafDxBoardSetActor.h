#ifndef GGAFDXBOARDSETACTORD_H_
#define GGAFDXBOARDSETACTORD_H_
namespace GgafDxCore {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[.
 * GgafDxTransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ����A����ɑ�ʕ\�����ɓ��ꃂ�f���͈ꊇ�`����s���悤�ɍœK���������A�N�^�[�B<BR>
 * �P���\���i��]�g�喳���j�̂��ߍ����B�X�R�A�\����A�w�i���Ɏg�p���悤�B<BR>
 * �Q�c�Q�[�������Ȃ�A�L�����N�^�I�u�W�F�N�g�͂��̃N���X��{�ł�����B<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDxBoardSetActor : public GgafDxDrawableActor {
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
    GgafCore::GgafGroupHead* addSubBone(actorkind prm_kind,
                                         GgafDxGeometricActor* prm_pGeoActor,
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
    GgafCore::GgafGroupHead* addSubBone(GgafDxGeometricActor* prm_pGeoActor,
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
    void rotateWith(GgafDxGeometricActor* prm_pActor) override {
    }

public:
    int _draw_set_num;
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDxBoardSetModel* _pBoardSetModel;
    /** �G�t�F�N�g */
    GgafDxBoardSetEffect* _pBoardSetEffect;
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* _pUvFlipper;
    /** [r]��(px) */
    pixcoord _width_px;
    /** [r]����(px) */
    pixcoord _height_px;
    GgafDxAlign _align;
    GgafDxValign _valign;

    GgafDxBoardSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardSetActor(); //�f�X�g���N�^

    virtual void locateAs(GgafDxGeometricActor* prm_pActor) override {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
    }

    virtual void locateAs(GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_TOP);
};

}
#endif /*GGAFDXBOARDSETACTORD_H_*/