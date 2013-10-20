#ifndef FORMATIONDELHEID001_H_
#define FORMATIONDELHEID001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�f���n�C�h�p�t�H�[���[�V����001�O���[�v .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid001 : public FormationDelheid {

public:
    /** [r]�ݒu���W�ƌ��� */
    GgafDxCore::GgafDxGeoElem geoLocate_;
    /** [r]�X�v���C�����I�u�W�F�N�g�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;

    FormationDelheid001(const char* prm_name);

    /**
     * �ݒu���W�ƌ������Z�b�g .
     * @param X
     * @param Y
     * @param Z
     * @param RZ
     * @param RY
     */
    void position(coord X, coord Y, coord Z,
                        angle RZ, angle RY) {
        geoLocate_.X = X;
        geoLocate_.Y = Y;
        geoLocate_.Z = Z;
        geoLocate_.RZ = RZ;
        geoLocate_.RY = RY;
    }

    /**
     * �ґ������o�[�Ƃ��ď��W���ꂽ�u�ԂɌĂяo�����R�[���o�b�N�����A�ݒu���W�ƌ������Z�b�g�B
     * @param pEnemyDelheid ���W���ꂽ�ґ������o�[
     */
    void onCallUpDelheid(EnemyDelheid* pEnemyDelheid) override;

    /**
     * �X�v���C�����I�u�W�F�N�g���擾 .
     * @return �X�v���C�����I�u�W�F�N�g
     */
    GgafLib::SplineManufacture* getSplManuf() override;

    /**
     * �U�镑������ .
     */
    virtual void processBehavior() override;

    virtual ~FormationDelheid001();
};

}
#endif /*FORMATIONDELHEID001_H_*/
