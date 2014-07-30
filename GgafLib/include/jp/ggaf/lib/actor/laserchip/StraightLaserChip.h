#ifndef GGAFLIB_STRAIGHTLASERCHIP_H_
#define GGAFLIB_STRAIGHTLASERCHIP_H_
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * �X�g���[�g���[�U�[�p�|�����C���̃`�b�v .
 * �X�g���[�g���[�U�[�Ȃǂƕ\�����Ă��邪�A���m�ɂ�<BR>
 * �E���ˍ��W�C�ӁA���ˌ����W���ړ�����ƁA����ɂƂ��Ȃ��ĕ��s�ړ�����i���Ƃ��\�j<BR>
 * �E���˕����C�ӁA���ˌ������̊p�x���ω�����ƁA����ɂƂ��Ȃ��Ĕ��ˌ��𒆐S�ɉ�]�ړ�����i���Ƃ��\�j<BR>
 * �E�ړ����@�͊�{�����Œ��i<BR>
 * �E�A���S�`�b�v���ˌ��I�u�W�F�N�g���W�ƌ����̍��������Z�B�������Ƃ�B<BR>
 * �ƌ����ׂ����A�O���f�B�E�X�������C���_�[�\�ȃ��[�U�[�ƌ����ׂ����A����Ȋ����B<BR>
 * �����o�[�� _velo_mv �ňړ����܂��Bdispatch() ������A���W�ƕ����y�� _velo_mv ��ݒ肵�ĉ������B<BR>
 * ���ˌ��ƘA�����ē������ꍇ�� setSource() ��ݒ肵�ĉ������B���̏ꍇ�A���W�ƕ����͎����ݒ肳��܂��B
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class StraightLaserChip : public LaserChip {
    friend class LaserChipDepository;

private:
    int _tmp_source_x;
    int _tmp_source_y;
    int _tmp_source_z;
    angle _tmp_source_rx;
    angle _tmp_source_ry;
    angle _tmp_source_rz;

public:
    /** ���[�U�[�̈ʒu�𓯊����邽�߂́AX���W�ϐ��ꏊ */
    int* _pSource_x;
    /** ���[�U�[�̈ʒu�𓯊����邽�߂́AY���W�ϐ��ꏊ */
    int* _pSource_y;
    /** ���[�U�[�̈ʒu�𓯊����邽�߂́AZ���W�ϐ��ꏊ */
    int* _pSource_z;
    /** ���[�U�[�̌��������̂𓯊����邽�߂́AX����]�A���O���l�ϐ��ꏊ */
    angle* _pSource_rx;
    /** ���[�U�[�̌��������̂𓯊����邽�߂́AY����]�A���O���l�ϐ��ꏊ */
    angle* _pSource_ry;
    /** ���[�U�[�̌��������̂𓯊����邽�߂́AZ����]�A���O���l�ϐ��ꏊ */
    angle* _pSource_rz;

    /** [r/w]�ړ����x */
    velo _velo_mv;

    GgafDxGeometricActor* _pSourceActor;

public:
    StraightLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processSettlementBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    /**
     * ���ˌ��̈ړ��Ɖ�]�ɂ��āA�������Ƃ锭�˃A�N�^�[��ݒ� .
     * @param prm_pGeoActor ���ˌ��A�N�^�[
     */
    void setSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_x = &prm_pGeoActor->_x;
        _pSource_y = &prm_pGeoActor->_y;
        _pSource_z = &prm_pGeoActor->_z;
        _pSource_rx = &prm_pGeoActor->_rx;
        _pSource_ry = &prm_pGeoActor->_ry;
        _pSource_rz = &prm_pGeoActor->_rz;
        _pSourceActor = prm_pGeoActor;
    }

    /**
     * ���ˌ��̈ړ��݂̂ɂ��āA�������Ƃ锭�˃A�N�^�[��ݒ� .
     * �ǂ����������ĂĂ����������ɔ��ˁB
     * @param prm_pGeoActor ���ˌ��A�N�^�[
     */
    void setPositionSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_x = &prm_pGeoActor->_x;
        _pSource_y = &prm_pGeoActor->_y;
        _pSource_z = &prm_pGeoActor->_z;
        _pSourceActor = prm_pGeoActor;
    }

    /**
     * ���ˌ��̉�]�݂̂ɂ��āA�������Ƃ锭�˃A�N�^�[��ݒ� .
     * �����{�������˂ȂǂɎg�p���邩�ȁE�E�E�B
     * @param prm_pGeoActor ���ˌ��A�N�^�[
     */
    void setAngleSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_rx = &prm_pGeoActor->_rx;
        _pSource_ry = &prm_pGeoActor->_ry;
        _pSource_rz = &prm_pGeoActor->_rz;
        _pSourceActor = prm_pGeoActor;
    }

    void setMvVelo(coord prm_velo);

    virtual ~StraightLaserChip();
};

}
#endif /*GGAFLIB_STRAIGHTLASERCHIP_H_*/

