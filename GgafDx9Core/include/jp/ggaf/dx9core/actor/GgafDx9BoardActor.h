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
        _offscreenkind = 0;
        return _offscreenkind;
    }

    /**
     * �g���Ȃ����邽�߂�private��override
     * @return
     */
    bool isOutOfGameSpace() override {
        return false;
    }

    /** */
    float _sx;
    /** */
    float _sy;

public:
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9BoardModel* _pBoardModel;
    /** �G�t�F�N�g */
    GgafDx9BoardEffect* _pBoardEffect;
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9BoardActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique );

    virtual void processDraw() override;

    virtual void setGeometry(int x, int y) {
        _x = x;
        _y = y;
    }

    virtual void setGeometry(int x, int y, int z) override {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual void setGeometry(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) override {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }

    virtual ~GgafDx9BoardActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
