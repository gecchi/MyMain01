#ifndef FORMATIONADELHEID001_H_
#define FORMATIONADELHEID001_H_

namespace VioletVreath {

/**
 * �G�@�A�[�f���n�C�h�p�t�H�[���[�V����001�O���[�v .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationAdelheid001 : public FormationAdelheid {

public:
    /** [r]�ݒu���W�ƌ��� */
    GgafDxCore::GgafDxGeoElem geoLocate_;
    /** [r]�X�v���C�����I�u�W�F�N�g�����ւ̐ڑ� */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;

    FormationAdelheid001(const char* prm_name);

    /**
     * �ݒu���W�ƌ������Z�b�g .
     * @param X
     * @param Y
     * @param Z
     * @param RZ
     * @param RY
     */
    void locate(coord X, coord Y, coord Z,
                        angle RZ, angle RY) {
        geoLocate_._X = X;
        geoLocate_._Y = Y;
        geoLocate_._Z = Z;
        geoLocate_._RZ = RZ;
        geoLocate_._RY = RY;
    }

    /**
     * �ґ������o�[�Ƃ��ď��W���ꂽ�u�ԂɌĂяo�����R�[���o�b�N�����A�ݒu���W�ƌ������Z�b�g�B
     * @param pEnemyAdelheid ���W���ꂽ�ґ������o�[
     */
    void onCallUpAdelheid(EnemyAdelheid* pEnemyAdelheid) override;

    /**
     * �X�v���C�����I�u�W�F�N�g���擾 .
     * @return �X�v���C�����I�u�W�F�N�g
     */
    GgafLib::SplineManufacture* getSplManuf() override;

    /**
     * �U�镑������ .
     */
    virtual void processBehavior() override;

    virtual ~FormationAdelheid001();
};

}
#endif /*FORMATIONADELHEID001_H_*/
