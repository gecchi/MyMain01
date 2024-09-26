#ifndef GGAF_DX_BOARDACTORD_H_
#define GGAF_DX_BOARDACTORD_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D�\���p�|���A�N�^�[ .
 * �|���S���Ƀe�N�X�`����\��t�����A�N�^�[�B<BR>
 * �e�N�X�`���̂P�s�N�Z�������̂܂܂P�h�b�g�ŕ\�����������Ɏg�p�B<BR>
 * �\���ɓ������Ă���A�[�x�ő傫�����ς��܂���B<BR>
 * �����蔻��I�u�W�F�N�g�͕ێ����܂���B<BR>
 * ���W�n�͍��オ (0,0) �� �E���Ɍ������� X���W�AY���W��������d�l�B<BR>
 * ��]�@�\(Z����]�̂�)�A�g��k���@�\�@�\����B<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class BoardActor : public FigureActor, public IAlignAbleActor {

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void appendChildAsFk(GeometricActor* prm_pGeoActor,
                          int prm_x_init_local,
                          int prm_y_init_local,
                          int prm_z_init_local,
                          int prm_rx_init_local,
                          int prm_ry_init_local,
                          int prm_rz_init_local) override {
        throwCriticalException("�g�p�s�ł��B");
    }

public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    BoardModel* _pBoardModel;
    /** [r]�G�t�F�N�g */
    BoardEffect* const _pBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".sprx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @return
     */
    BoardActor(const char* prm_name,
               const char* prm_model,
               const char* prm_effect_id,
               const char* prm_technique,
               CollisionChecker* prm_pChecker = nullptr);

    virtual void processDraw() override;
    virtual void setPositionAt(const GeometricActor* prm_pActor) override;
    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;
    virtual void setScale(scale s) override;
    virtual void setScale(scale sx, scale sy) override;
    virtual void setScale(scale sx, scale sy, scale sz) override;
    virtual void setScaleR(float prm_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override;
    virtual void addScaleX(scale dsx) override {
        _sx += dsx;
    }
    virtual void addScaleY(scale dsy) override {
        _sy += dsy;
    }
    virtual void addScaleZ(scale dsz) override {
        _sz += dsz;
    }

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfSpacetime() const override {
        return false;
    }

    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~BoardActor();
};

}
#endif /*GGAF_DX_BOARDACTORD_H_*/
