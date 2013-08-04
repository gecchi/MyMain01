#ifndef MAGICMETER_H_
#define MAGICMETER_H_
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"

namespace VioletVreath {

#ifdef P_MYSHIP
    #define P_MAGICMETER (P_MYSHIP->pMagicMeter_)
#else
    #error P_MAGICMETER isnt define
#endif


typedef GgafCore::GgafLinkedListRing<Magic> MagicList;

/**
 * ���@���[�^�[ .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultBoardSetActor {
    enum {
        SE_CURSOR_MOVE_METER       ,
        SE_CURSOR_MOVE_LEVEL       ,
        SE_CURSOR_MOVE_LEVEL_CANCEL,
        SE_CURSOR_BAD_MOVE         ,
        SE_EXECUTE_LEVELUP_MAGIC   ,
        SE_EXECUTE_LEVELDOWN_MAGIC ,
        SE_EXECUTE_CANCEL_LEVELUP_MAGIC   ,
        SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC ,
        SE_CANT_INVOKE_MAGIC       ,
        SE_BAD_OPERATION   ,
    };
public:
    TractorMagic* pTractorMagic_;
    SpeedMagic*   pSpeedMagic_;
    LockonMagic*  pLockonMagic_;
    TorpedoMagic* pTorpedoMagic_;
    LaserMagic*   pLaserMagic_;
    OptionMagic*  pOptionMagic_;
    VreathMagic*  pVreathMagic_;
    SmileMagic*   pSmileMagic_;

    /** ���@��MP */
    GgafLib::AmountGraph* pMP_MyShip_;
    /** MP��COST���\���p */
    GgafLib::AmountGraph cost_disp_mp_;
    /** ���@��Vreath */
    GgafLib::AmountGraph* pVreath_MyShip_;
    /** Vreath��COST���\���p */
    GgafLib::AmountGraph cost_disp_vreath;
    /** Vreath�̃_���[�W���\���p */
    GgafLib::AmountGraph damage_disp_vreath;

    /** �c���@���ʎ������ԕ\�� */
    MagicMeterStatus* pMagicMeterStatus_;
    /** �G�l���M�[�o�[ */
    EnergyBar* pEnergyBar_;
    /** �R�X�g�\���o�[ */
    CostDispBar* pCostDispBar_;
    /** �����X�M�[�o�[ */
    VreathBar* pVreathBar_;
    /** �R�X�g�\���o�[ */
    CostDispBar* pCostDispBar2_;
    /** �_���[�W�\���o�[ */
    DamageDispBar* pDamageDispBar_;

    /** ���@���X�g */
    MagicList lstMagic_;

    /** ���[�^��J�[�\�� */
    MagicMeterCursor001* pMagicCursor_;
    /** �e���@(�z��)�̃��x���̃J�[�\�� */
    MagicLvCursor001** papLvTargetCursor_;
    /** �e���@(�z��)�̌����x�������\���p�J�[�\�� */
    MagicLvCursor002** papLvHilightCursor_;
    /** �e���@(�z��)�̉r�������x�������\���p�J�[�\�� */
    MagicLvCursor003** papLvCastingMarkCursor_;

    /** [r]���݂̊e���@(�z��)�̃��[���A�b�v�\�����(0.0:���Ă��� �` 1.0:�J���Ă���) */
    float* paFloat_rr_;
    /** [r/w]�e���@(�z��)�̃��[���A�b�v�̑��� */
    float* paFloat_velo_rr_;

    float alpha_velo_;

    /** ���@���[�^�[�P�̉���(px) */
    float width_px_;
    /** ���@���[�^�[�P�̍���(px) */
    float height_px_;
    /** ���@���[�^�[�P�̉��� */
    coord width_;
    /** ���@���[�^�[�P�̍��� */
    coord height_;

    std::stringstream st_[10];

    /** [r]�r�������ʉ������Ǘ��I�u�W�F�N�g2 */
    GgafDxCore::GgafDxSeTransmitterForActor* pSeTx4Cast_;
    GgafDxCore::GgafDxSeTransmitterForActor* pSeTx4Invoke_;
public:
    MagicMeter(const char* prm_name, GgafLib::AmountGraph* prm_pMP_MyShip, GgafLib::AmountGraph* prm_pVreath_MyShip);

    void saveStatus(int prm_saveno);

    void loadStatus(int prm_saveno);

    void save(std::stringstream& sts);

    void load(std::stringstream& sts);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void processDraw() override;

    void rollOpen(int prm_meter_index);

    void rollClose(int prm_meter_index);


    void setMeterAlpha(float a);
    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/

