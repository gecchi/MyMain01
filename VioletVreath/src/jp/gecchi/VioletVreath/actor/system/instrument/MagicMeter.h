#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace VioletVreath {

#define MMETER_MAX_LEVEL 9

#ifdef P_MYSHIP_SCENE
    #define P_MAGICMETER (P_MYSHIP_SCENE->pMagicMeter_)
#else
    #error P_MYSHIP_SCENE isnt define
#endif


/**
 * ���@���[�^�[ .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultBoardSetActor {
    enum {
        SE_CURSOR_MOVE_METER = 0   ,
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
    D3DXHANDLE h_active_magic_;
    /** MP */
    GgafLib::AmountGraph mp_;

    /** COST */
    GgafLib::AmountGraph cost_disp_;

    /** �c���@���ʎ������ԕ\�� */
    MagicMeterStatus* pMagicMeterStatus_;
    /** �G�l���M�[�o�[ */
    EnergyBar* pEnergyBar_;
    /** �R�X�g�\���o�[ */
    CostDispBar* pCostDispBar_;
    /** ���@���X�g */
    GgafCore::GgafLinkedListRing<Magic> ringMagics_;

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

    /** ���@���[�^�[�P�̉���(px) */
    float width_px_;
    /** ���@���[�^�[�P�̍���(px) */
    float height_px_;
    /** ���@���[�^�[�P�̉��� */
    coord width_;
    /** ���@���[�^�[�P�̍��� */
    coord height_;

    std::stringstream st_[10];

public:
    MagicMeter(const char* prm_name);

    void saveStatus(int prm_saveno);

    void loadStatus(int prm_saveno);

    void save(std::stringstream& sts);

    void load(std::stringstream& sts);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void processDraw() override;

    void rollOpen(int prm_meter_index);

    void rollClose(int prm_meter_index);

    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/

