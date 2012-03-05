#ifndef MAGICMETERSTATUS_H_
#define MAGICMETERSTATUS_H_
namespace VioletVreath {

/**
 * 残魔法効果持続時間表示 .
 * @version 1.00
 * @since 2011/11/16
 * @author Masatoshi Tsuge
 */
class MagicMeterStatus : public GgafLib::StringBoardActor {

public:
    MagicMeter* pMagicMeter_;
    char aBuf_[30];
    MagicMeterStatus(const char* prm_name, MagicMeter* prm_pMagicMeter);
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processDraw() override;
    virtual ~MagicMeterStatus();

};

}
#endif /*MAGICMETERSTATUS_H_*/
