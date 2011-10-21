#ifndef STAGEPARTCONTROLLER_H_
#define STAGEPARTCONTROLLER_H_

namespace MyStg2nd {

class StagePartController : public GgafLib::DefaultScene {

public:

    StagePartController(const char* prm_name);

//ここで挫折。方針変更
//    /**
//     * スロー
//     * @param prm_pScene
//     */
//    virtual void addSubLast(GgafScene* prm_pScene) override;

    virtual ~StagePartController();
};

}
#endif /*STAGEPARTCONTROLLER_H_*/
