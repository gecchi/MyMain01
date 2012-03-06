#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace VioletVreath {

#define MMETER_MAX_LEVEL 8

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

public:
    D3DXHANDLE h_active_magic_;
    /** MP */
    GgafLib::AmountGraph mp_;
    /** �c���@���ʎ������ԕ\�� */
    MagicMeterStatus* pMagicMeterStatus_;
    /** �G�l���M�[�o�[ */
    EnagyBar* pEnagyBar_;
    /** ���@���X�g */
    GgafCore::GgafLinkedListRing<Magic> ringMagics_;

    /** ���[�^��J�[�\�� */
    MagicMeterCursor001* pMagicCursor_;
    /** �e���@�̃��x���J�[�\��(�z��) */
    MagicMeterCursor002** papLvCursor_;
    /** �e���@�̃��x���J�[�\�����w���Ă��郌�x��(�z��) */
    int* paCursorLv_;

    /** ���@���[�^�[�P�̉���(px) */
    float width_px_;
    /** ���@���[�^�[�P�̍���(px) */
    float height_px_;
    /** ���@���[�^�[�P�̉��� */
    coord width_;
    /** ���@���[�^�[�P�̍��� */
    coord height_;

    stringstream st_[10];

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

    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/

