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
     * �g���Ȃ����邽�߂�private��override
     * @return
     */
    virtual int isOutOfView() {
        return 0;
    }
    /**
     * �g���Ȃ����邽�߂�private��override
     * @return
     */
    virtual bool isOutOfUniverse() {
        return false;
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

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw() override;

    virtual void locate(int x, int y) {
        _x = (float)x;
        _y = (float)y;
    }

    virtual void locate(int x, int y, int z) override {
        _x = (float)x;
        _y = (float)y;
        _z = (float)z;
    }

    virtual void locate(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual void locateWith(GgafDx9GeometricActor* prm_pActor) override {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }

    virtual ~GgafDx9BoardSetActor(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDSETACTORD_H_*/
