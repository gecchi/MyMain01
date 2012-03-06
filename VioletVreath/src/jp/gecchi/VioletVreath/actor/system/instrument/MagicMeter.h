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
 * 魔法メーター .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultBoardSetActor {

public:
    D3DXHANDLE h_active_magic_;
    /** MP */
    GgafLib::AmountGraph mp_;
    /** 残魔法効果持続時間表示 */
    MagicMeterStatus* pMagicMeterStatus_;
    /** エネルギーバー */
    EnagyBar* pEnagyBar_;
    /** 魔法リスト */
    GgafCore::GgafLinkedListRing<Magic> ringMagics_;

    /** メータ主カーソル */
    MagicMeterCursor001* pMagicCursor_;
    /** 各魔法のレベルカーソル(配列) */
    MagicMeterCursor002** papLvCursor_;
    /** 各魔法のレベルカーソルが指しているレベル(配列) */
    int* paCursorLv_;

    /** 魔法メーター１つの横幅(px) */
    float width_px_;
    /** 魔法メーター１つの高さ(px) */
    float height_px_;
    /** 魔法メーター１つの横幅 */
    coord width_;
    /** 魔法メーター１つの高さ */
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

