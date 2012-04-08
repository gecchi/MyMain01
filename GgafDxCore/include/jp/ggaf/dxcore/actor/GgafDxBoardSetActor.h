#ifndef GGAFDXBOARDSETACTORD_H_
#define GGAFDXBOARDSETACTORD_H_
namespace GgafDxCore {

/**
 * ���W�ϊ��ς݂̃X�v���C�g�A�N�^�[(��ʕ\�����p) .
 * GgafDxTransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * GgafDxBoardActor�ɁA���ꃂ�f���͈ꊇ�`����s���悤�ɍœK���������A�N�^�[�B<BR>
 * ��]�@�\�Ȃ��A�g��@�\�Ȃ��B<BR>
 * �P���\���̂��ߍ����B�����\����A�w�i���Ɏg�p�������B<BR>
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
    GgafCore::GgafGroupHead* addSubFk(actorkind prm_kind,
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
    GgafCore::GgafGroupHead* addSubFk(GgafDxGeometricActor* prm_pGeoActor,
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
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDxBoardSetModel* _pBoardSetModel;
    /** [r]�G�t�F�N�g */
    GgafDxBoardSetEffect* _pBoardSetEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
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

    virtual void locatedBy(GgafDxGeometricActor* prm_pActor) override {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
    }

    virtual void locatedBy(GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_TOP);
};

}
#endif /*GGAFDXBOARDSETACTORD_H_*/
