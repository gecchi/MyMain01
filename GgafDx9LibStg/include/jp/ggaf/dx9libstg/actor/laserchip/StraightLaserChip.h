#ifndef STRAIGHTLASERCHIP_H_
#define STRAIGHTLASERCHIP_H_
namespace GgafDx9LibStg {

/**
 * �X�g���[�g���[�U�[�p�|�����C���̃`�b�v .
 * �X�g���[�g���[�U�[�Ȃǂƕ\�����Ă��邪�A���m�ɂ�<BR>
 * �E���ˍ��W�C�Ӂi���ˌ����W���ړ��\�j<BR>
 * �E�ړ����@�͊�{�����Œ��i<BR>
 * �E�A���S�`�b�v���ˌ��I�u�W�F�N�g���W�ƌ����̍��������Z�B�������Ƃ�B<BR>
 * �ƌ����ׂ����A�O���f�B�E�X�������C���_�[�\�ȃ��[�U�[�ƌ����ׂ����A����Ȋ����B<BR>
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class StraightLaserChip : public LaserChip {
    friend class LaserChipStore;

public:
    /** ���[�U�[�̈ʒu�𓯊����邽�߂́AX���W�ϐ��ꏊ */
    int* _pSource_X;
    /** ���[�U�[�̈ʒu�𓯊����邽�߂́AY���W�ϐ��ꏊ */
    int* _pSource_Y;
    /** ���[�U�[�̈ʒu�𓯊����邽�߂́AZ���W�ϐ��ꏊ */
    int* _pSource_Z;
    /** ���[�U�[�̌��������̂𓯊����邽�߂́AX����]�A���O���l�ϐ��ꏊ */
    angle* _pSource_RX;
    /** ���[�U�[�̌��������̂𓯊����邽�߂́AY����]�A���O���l�ϐ��ꏊ */
    angle* _pSource_RY;
    /** ���[�U�[�̌��������̂𓯊����邽�߂́AZ����]�A���O���l�ϐ��ꏊ */
    angle* _pSource_RZ;
    /** ���[�U�[�̈ړ������𓯊����邽�߂́A�P�ʕ����x�N�g��X�����ϐ��ꏊ */
    float* _pSource_vX;
    /** ���[�U�[�̈ړ������𓯊����邽�߂́A�P�ʕ����x�N�g��Y�����ϐ��ꏊ */
    float* _pSource_vY;
    /** ���[�U�[�̈ړ������𓯊����邽�߂́A�P�ʕ����x�N�g��Z�����ϐ��ꏊ */
    float* _pSource_vZ;
    /** �ړ����x */
    int _veloMv;

    GgafDx9GeometricActor* _pSourceActor;

    StraightLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void onActive() override;

    virtual void onInactive() override;

    void setPositionSource(GgafDx9Core::GgafDx9GeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
        _pSourceActor = prm_pGeoActor;
    }

    void setAngleSource(GgafDx9Core::GgafDx9GeometricActor* prm_pGeoActor) {
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pMvNavigator->_vX;
        _pSource_vY = &prm_pGeoActor->_pMvNavigator->_vY;
        _pSource_vZ = &prm_pGeoActor->_pMvNavigator->_vZ;
        _pSourceActor = prm_pGeoActor;
    }

    void setSource(GgafDx9Core::GgafDx9GeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pMvNavigator->_vX;
        _pSource_vY = &prm_pGeoActor->_pMvNavigator->_vY;
        _pSource_vZ = &prm_pGeoActor->_pMvNavigator->_vZ;
        _pSourceActor = prm_pGeoActor;
    }

    virtual ~StraightLaserChip();

};

}
#endif /*STRAIGHTLASERCHIP_H_*/

