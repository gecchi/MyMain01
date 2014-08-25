#ifndef HOSHIBOSHITITLE_H_
#define HOSHIBOSHITITLE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"


namespace VioletVreath {

/**
 * 星々ポイントスプライトタイトル用 .
 * @version 1.00
 * @since 2012/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshiTitle : public HoshiBoshi {

public:
    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    HoshiBoshiTitle(const char* prm_name);

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void fadein();

    virtual ~HoshiBoshiTitle();
};

}

#endif /*HOSHIBOSHITITLE_H_*/
