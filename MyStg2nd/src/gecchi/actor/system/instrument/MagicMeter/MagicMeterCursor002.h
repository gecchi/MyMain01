#ifndef MAGICMETERCURSOR002_H_
#define MAGICMETERCURSOR002_H_


namespace MyStg2nd {

/**
 * メーター副カーソル .
 * @version 1.00
 * @since 2011/12/12
 * @author Masatoshi Tsuge
 */
class MagicMeterCursor002 : public GgafLib::DefaultBoardActor {

public:
    /** 対象魔法 */
    Magic* _pMagic;
    /** 対象魔法メーター */
    MagicMeter* _pMagicMeter;

    int _magic_index;

    coord _tmp_Y;

    MagicMeterCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    void processPreDraw() override;

    void processAfterDraw() override;



    void moveToLv(int prm_lv);

    void blink();


    virtual ~MagicMeterCursor002();
};

}
#endif /*MAGICMETERCURSOR002_H_*/

