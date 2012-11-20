#ifndef STRAIGHTLASERCHIP_H_
#define STRAIGHTLASERCHIP_H_
namespace GgafLib {

/**
 * �X�g���[�g���[�U�[�p�|�����C���̃`�b�v .
 * �X�g���[�g���[�U�[�Ȃǂƕ\�����Ă��邪�A���m�ɂ�<BR>
 * �E���ˍ��W�C�ӁA���ˌ����W���ړ�����ƁA����ɂƂ��Ȃ��ĕ��s�ړ�����i���Ƃ��\�j<BR>
 * �E���˕����C�ӁA���ˌ������̊p�x���ω�����ƁA����ɂƂ��Ȃ��Ĕ��ˌ��𒆐S�ɉ�]�ړ�����i���Ƃ��\�j<BR>
 * �E�ړ����@�͊�{�����Œ��i<BR>
 * �E�A���S�`�b�v���ˌ��I�u�W�F�N�g���W�ƌ����̍��������Z�B�������Ƃ�B<BR>
 * �ƌ����ׂ����A�O���f�B�E�X�������C���_�[�\�ȃ��[�U�[�ƌ����ׂ����A����Ȋ����B<BR>
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class StraightLaserChip : public LaserChip {
    friend class LaserChipDepository;

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

    GgafDxGeometricActor* _pSourceActor;

    StraightLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    /**
     * ���s�ړ��Ɖ�]�ړ��̓������Ƃ锭�˃A�N�^�[��ݒ� .
     * @param prm_pGeoActor ���ˌ��A�N�^�[
     */
    void setSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pKurokoA->_vX;
        _pSource_vY = &prm_pGeoActor->_pKurokoA->_vY;
        _pSource_vZ = &prm_pGeoActor->_pKurokoA->_vZ;
        _pSourceActor = prm_pGeoActor;
    }


    /**
     * ���s�ړ��̂ݓ������Ƃ锭�˃A�N�^�[��ݒ� .
     * @param prm_pGeoActor
     */
    void setPositionSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
        _pSourceActor = prm_pGeoActor;
    }

    /**
     * ��]�ړ��̂ݓ������Ƃ锭�˃A�N�^�[��ݒ� .
     * @param prm_pGeoActor
     */
    void setAngleSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pKurokoA->_vX;
        _pSource_vY = &prm_pGeoActor->_pKurokoA->_vY;
        _pSource_vZ = &prm_pGeoActor->_pKurokoA->_vZ;
        _pSourceActor = prm_pGeoActor;
    }

    virtual ~StraightLaserChip();
};

}
#endif /*STRAIGHTLASERCHIP_H_*/

