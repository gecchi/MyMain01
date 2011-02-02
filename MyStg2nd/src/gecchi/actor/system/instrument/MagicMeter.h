#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace MyStg2nd {

#define MMETER_MAX_LEVEL_Y 9

/**
 * 魔法メーター .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafDx9LibStg::DefaultBoardSetActor {

public:
    D3DXHANDLE _h_active_magic;

    GgafCore::GgafLinkedListRing<Magic> _ringMagics;

    int _pos_pattern_no[MMETER_MAX_LEVEL_Y][8];
    int* _paLevelCursor;
    float _width;
    float _height;
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

