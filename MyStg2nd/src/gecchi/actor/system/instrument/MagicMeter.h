#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace MyStg2nd {

#define MMETER_MAX_LEVEL 8

/**
 * 魔法メーター .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultBoardSetActor {

public:
    D3DXHANDLE _h_active_magic;

    GgafCore::GgafLinkedListRing<Magic> _ringMagics;
    /** 各魔法のアクティブカーソル位置 */
    int* _paLevelCursor;

    /** 魔法メーター１つの横幅(px) */
    float _width_px;
    /** 魔法メーター１つの高さ(px) */
    float _height_px;
    MagicMeter(const char* prm_name);

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

