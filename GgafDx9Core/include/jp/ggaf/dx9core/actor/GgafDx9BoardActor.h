#ifndef GGAFDX9BOARDACTORD_H_
#define GGAFDX9BOARDACTORD_H_
namespace GgafDx9Core {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[ .
 * GgafDx9TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�B<BR>
 * �P���\���i��]�g�喳���j�̂��ߍ����B<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardActor : public GgafDx9DrawableActor {
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
    void locateAs(GgafDx9GeoElem* prm_pGgafDx9GeoElem) override {
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void rotateWith(GgafDx9GeometricActor* prm_pActor) override {
    }

public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9BoardModel* _pBoardModel;
    /** [r]�G�t�F�N�g */
    GgafDx9BoardEffect* _pBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFlipper* _pUvFlipper;
    /** [r/w]�ϊ��ςݍ��WX���g�嗦(1.0�œ��{) */
    float _sx;
    /** [r/w]�ϊ��ςݍ��WY���g�嗦(1.0�œ��{) */
    float _sy;

    GgafDx9BoardActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique );

    virtual void processDraw() override;

    /**
     * �A�N�^�[�̕ϊ��ςݍ��W(����̓_)��ݒ� .
     * z �͕ω��Ȃ�
     * @param x
     * @param y
     */
    virtual void locate(float x, float y) {
        _x = x;
        _y = y;
    }

    /**
     * �A�N�^�[�̕ϊ��ςݍ��W(����̓_)��ݒ� .
     * @param x
     * @param y
     * @param z �[�x
     */
    virtual void locate(int x, int y, int z) override {
        _x = (float)x;
        _y = (float)y;
        _z = (float)z;
    }

    /**
     * �A�N�^�[�̕ϊ��ςݍ��W(����̓_)��ݒ� .
     * @param x
     * @param y
     * @param z �[�x
     */
    virtual void locate(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * �A�N�^�[�̕ϊ��ςݍ��W���R�s�[���Đݒ� .
     * @param prm_pActor
     */
    virtual void locateAs(GgafDx9GeometricActor* prm_pActor) override {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }

    /**
     * �X�P�[�����X�P�[���l�Őݒ肵�܂��B
     * @param S �X�P�[���l(1.0 �� 1.0�{)
     */
    virtual void setScale(int S) override {
        _sx = S;
        _sy = S;
        setBoundingSphereRadiusRate((1.0*S)/1000);
    }

    /**
     * �X�P�[����{���Őݒ肵�܂��B
     * 1.0 �� 1.0�{�B
     * �y���ӁzsetScale �Ɠ���
     * @param prm_rate �{��
     */
    virtual void setScaleRate(float prm_rate) override {
        _sx = prm_rate;
        _sy = prm_rate;
        setBoundingSphereRadiusRate(prm_rate);
    }

    virtual void processSettlementBehavior() {
    }

    virtual ~GgafDx9BoardActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
