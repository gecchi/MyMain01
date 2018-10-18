#ifndef GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_
#define GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * �X�v���C�g�A�N�^�[.
 * GgafDxGeometricActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * ������|��<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDxRegularPolygonSpriteActor : public GgafDxFigureActor {

public:
    /** [r]���f������ */
    GgafDxRegularPolygonSpriteModel* const _pRegularPolygonSpriteModel;
    /** [r]�G�t�F�N�g���� */
    GgafDxRegularPolygonSpriteEffect* const _pRegularPolygonSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* const _pUvFlipper;

    float _far_rate;
    /** �������`�悷�邩 */
    int _draw_fan_num;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    GgafDxRegularPolygonSpriteActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique,
                      GgafCore::GgafStatus* prm_pStat,
                      GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxRegularPolygonSpriteActor();

    /**
     * �����̍��W�ł������\�� .
     * @param prm_b
     */
    void drawAnyFar(bool prm_b) {
        if (prm_b) {
            _far_rate = 0.999f;
        } else {
            _far_rate = -1.0f;
        }
    }

    void setDrawFanNum(int prm_draw_fan_num) {
        _draw_fan_num = prm_draw_fan_num;
    }

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
};

}
#endif /*GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_*/
