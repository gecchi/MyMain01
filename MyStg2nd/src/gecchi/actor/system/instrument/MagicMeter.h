#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace MyStg2nd {

#define MMETER_MAX_LEVEL 8

#ifdef P_MYSHIP_SCENE
    #define P_MAGICMETER (P_MYSHIP_SCENE->_pMagicMeter)
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
    D3DXHANDLE _h_active_magic;
    /** MP */
    GgafLib::AmountGraph _mp;
    /** 残魔法効果持続時間表示 */
    MagicMeterStatus* _pMagicMeterStatus;
    /** エネルギーバー */
    EnagyBar* _pEnagyBar;
    /** 魔法リスト */
    GgafCore::GgafLinkedListRing<Magic> _ringMagics;

    /** メータ主カーソル */
    MagicMeterCursor001* _pMagicCursor;
    /** 各魔法のレベルカーソル(配列) */
    MagicMeterCursor002** _papLvCursor;
    /** 各魔法のレベルカーソルが指しているレベル(配列) */
    int* _paCursorLv;

    /** 魔法メーター１つの横幅(px) */
    float _width_px;
    /** 魔法メーター１つの高さ(px) */
    float _height_px;
    /** 魔法メーター１つの横幅 */
    coord _width;
    /** 魔法メーター１つの高さ */
    coord _height;


    MagicMeter(const char* prm_name);

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

