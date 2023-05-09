#ifndef MAGICMETER_H_
#define MAGICMETER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassBoardActor.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"

namespace VioletVreath {

#ifdef pMYSHIP
    #define pMAGICMETER (pMYSHIP->pMagicMeter_)
#else
    #error pMAGICMETER isnt define
#endif


typedef GgafCore::RingLinkedList<Magic> MagicList;

/**
 * ���@���[�^�[ .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultMassBoardActor {
protected:
    VERTEX_instancedata* paInstancedata_MM_;
    int max_draw_num_;
public:
    TractorMagic* pTractorMagic_;
    SpeedMagic*   pSpeedMagic_;
    LockonMagic*  pLockonMagic_;
    TorpedoMagic* pTorpedoMagic_;
    ShotMagic*    pShotMagic_;
    LaserMagic*   pLaserMagic_;
    BunshinMagic* pBunshinMagic_;
    VreathMagic*  pVreathMagic_;
    SmileMagic*   pSmileMagic_;

//    /** ���@��MP */
//    GgafLib::Quantity* pMP_MyShip_;
//    /** ���@��Vreath */
//    GgafLib::Quantity* pVreath_MyShip_;
//    /** Vreath�̃_���[�W���\���p */
//    GgafLib::Quantity damage_disp_vreath;

    /** �c���@���ʎ������ԕ\�� */
    MagicMeterStatus* pMagicMeterStatus_;
    /** �G�l���[�o�[ */
    MpBar* pMpBar_;
    /** �R�X�g�\���o�[ */
    CostDispBar* pMpCostDispBar_;
    /** �����X�[�o�[ */
    VreathBar* pVreathBar_;
    /** �R�X�g�\���o�[ */
    CostDispBar* pVreathCostDispBar_;
    /** �_���[�W�\���o�[ */
    DamageDispBar* pDamageDispBar_;

    /** ���@���X�g */
    MagicList lstMagic_;

    /** ���[�^��J�[�\�� */
    MagicMeterCursor001* pMainCur_;
    /** �e���@(�z��)�̃��x���̃J�[�\��(��������ړ�) */
    MagicLvCursor001** papLvTgtMvCur_;
    /** �e���@(�z��)�̌����x�������\���p�J�[�\�� */
    MagicLvCursor002** papLvNowCur_;
    /** �e���@(�z��)�̉r�������x�������\���p�J�[�\�� */
    MagicLvCursor003** papLvCastingCur_;

    /** [r]���݂̊e���@(�z��)�̃��[���A�b�v�\�����(0.0:���Ă��� �` 1.0:�J���Ă���) */
    float* r_roll_;
    /** [r/w]�e���@(�z��)�̃��[���A�b�v�̑��� */
    float* r_roll_velo_;

    float alpha_velo_;

    /** ���@���[�^�[�P�̉���(px) */
    const float width_px_;
    /** ���@���[�^�[�P�̍���(px) */
    const float height_px_;
    /** ���@���[�^�[�P�̉��� */
    const coord width_;
    /** ���@���[�^�[�P�̍��� */
    const coord height_;

    std::stringstream st_[10];

    /** [r]�r�������ʉ������Ǘ� */
    GgafDx::SeTransmitterForActor* pSeXmtr4Cast_;
    /** [r]���������ʉ������Ǘ� */
    GgafDx::SeTransmitterForActor* pSeXmtr4Invoke_;
    /** �\�������̎c�莞�Ԃ�ݒ� */
    frame fraeme_of_notice_remaind_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ���ʖ�
     * @param prm_pMP_MyShip MP�l�ϐ��̃A�h���X
     * @param prm_pVreath_MyShip Vreath�l�ϐ��̃A�h���X
     */
    MagicMeter(const char* prm_name, int* prm_pMP_MyShip, int* prm_pVreath_MyShip);

    void saveStatus(int prm_saveno);

    void loadStatus(int prm_saveno);

    void save(std::stringstream& sts);

    void loadProperties(std::stringstream& sts);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void onInactive() override;

    void processDraw() override;

    void rollOpen(int prm_meter_index);

    void rollClose(int prm_meter_index);


    void setMeterAlpha(float a);
    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/

