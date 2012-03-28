#ifndef GGAFDXBOARDACTORD_H_
#define GGAFDXBOARDACTORD_H_
namespace GgafDxCore {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[ .
 * GgafDxTransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �e�N�X�`���̂P�s�N�Z�������̂܂܂P�h�b�g�ŕ\�����������Ɏg�p�B<BR>
 * 2D�[���X�v���C�g�I�ȋ@�\��z�肵���A�N�^�[�B<BR>
 * ��]�@�\�Ȃ��A�g��@�\����B<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDxBoardActor : public GgafDxDrawableActor {
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
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDxBoardModel* _pBoardModel;
    /** [r]�G�t�F�N�g */
    GgafDxBoardEffect* _pBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* _pUvFlipper;
    /** [r]��(px) */
    pixcoord _width_px;
    /** [r]����(px) */
    pixcoord _height_px;
    GgafDxAlign _align;
    GgafDxValign _valign;

    /**
     *
     * @param prm_name
     * @param prm_model_id
     * @param prm_effect_id
     * @param prm_technique
     */
    GgafDxBoardActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique );

    virtual void processDraw() override;

    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardActor(); //�f�X�g���N�^

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_TOP);

    virtual void locatedBy(GgafDxGeometricActor* prm_pActor) override {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
    }
    virtual void locatedBy(GgafDxGeoElem* prm_pGeoElem) override;
};

}
#endif /*GGAFDXBOARDACTORD_H_*/
