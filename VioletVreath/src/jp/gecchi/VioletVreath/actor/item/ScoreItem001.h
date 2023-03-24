#ifndef SCOREITEM001_H_
#define SCOREITEM001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/ScoreItem.h"

namespace VioletVreath {

/**
 * ScoreâÒïúÉAÉCÉeÉÄè¨ .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class ScoreItem001 : public ScoreItem {

public:
    ScoreItem001(const char* prm_name);

    void initialize() override;

    virtual ~ScoreItem001();
};

}
#endif /*SCOREITEM001_H_*/

