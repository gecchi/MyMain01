#ifndef STAGEPARTCONTROLLER_H_
#define STAGEPARTCONTROLLER_H_
namespace VioletVreath {

/**
 * ステージコントローラー基底 .
 * @version 1.00
 * @since 2011/10/21
 * @author Masatoshi Tsuge
 */
class StagePartController : public GgafLib::DefaultScene {

public:

    StagePartController(const char* prm_name);

    virtual ~StagePartController();
};

}
#endif /*STAGEPARTCONTROLLER_H_*/
