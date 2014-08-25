#ifndef FORMATIONTHAGORAS_H_
#define FORMATIONTHAGORAS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�^�S���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras : public GgafLib::TreeFormation {

public:
    const char** xpm_;
    XpmHeader* pXpmHd_;
    int num_Thagoras_;

    int cnt_call_up_row_;
    frame call_up_interval_;

    /** [r]�o�����W(�V�[�����ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;

    GgafDxCore::GgafDxScaler* pScaler_;
    GgafLib::DefaultGeometricActor* pActor4Sc_;

public:
    FormationThagoras(const char* prm_name, const char** prm_xpm);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) = 0;

    /**
     * �o�����W��ݒ�B
     * @param X
     * @param Y
     * @param Z
     */
    void position(coord x, coord y, coord z) {
        entry_pos_.x = x;
        entry_pos_.y = y;
        entry_pos_.z = z;
    }

    virtual ~FormationThagoras();
};

}
#endif /*FORMATIONTHAGORAS_H_*/
