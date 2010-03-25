#ifndef GGAFDX9BOARDACTORD_H_
#define GGAFDX9BOARDACTORD_H_
namespace GgafDx9Core {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[.
 * GgafDx9TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�B<BR>
 * �P���\���i��]�g�喳���j�̂��ߍ����B�X�R�A�\����A�w�i���Ɏg�p���悤�B<BR>
 * �Q�c�Q�[�������Ȃ�A�I�u�W�F�N�g�͂��̃N���X��{�ł�����B<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardActor : public GgafDx9DrawableActor {
private:
    /**
     * �g���Ȃ����邽�߂�private��override
     * @return
     */
    int isOffscreen() override {
        return 0;
    }

    /**
     * �g���Ȃ����邽�߂�private��override
     * @return
     */
    bool isOutOfGameSpace() override {
        return false;
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
    virtual void setGeometry(float x, float y) {
        _x = x;
        _y = y;
    }

    /**
     * �A�N�^�[�̕ϊ��ςݍ��W(����̓_)��ݒ� .
     * @param x
     * @param y
     * @param z �[�x
     */
    virtual void setGeometry(int x, int y, int z) override {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * �A�N�^�[�̕ϊ��ςݍ��W(����̓_)��ݒ� .
     * @param x
     * @param y
     * @param z �[�x
     */
    virtual void setGeometry(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * �A�N�^�[�̕ϊ��ςݍ��W���R�s�[���Đݒ� .
     * @param prm_pActor
     */
    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) override {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }

    virtual ~GgafDx9BoardActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
