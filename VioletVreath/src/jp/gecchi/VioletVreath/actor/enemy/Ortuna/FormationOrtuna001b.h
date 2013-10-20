#ifndef FORMATIONORTUNA001B_H_
#define FORMATIONORTUNA001B_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/FormationOrtuna001.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �I���g�D�i�p�t�H�[���[�V��������001-b .
 * @version 1.00
 * @since 2013/08/05
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001b : public FormationOrtuna001 {

public:
    /** �t�H�[���[�V������_���W */
    GgafDxCore::GgafDxGeoElem pos_;

public:
    FormationOrtuna001b(const char* prm_name);

    /**
     * ��_���W�Z�b�g�B
     * onCallUpOrtuna() �̏��񎞈����s�����
     * @param X
     * @param Y
     * @param Z
     */
    void position(coord X, coord Y, coord Z) {
        pos_.X = X;
        pos_.Y = Y;
        pos_.Z = Z;
    }

    virtual void onCallUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) override;

    virtual ~FormationOrtuna001b();
};

}
#endif /*FORMATIONORTUNA001B_H_*/
