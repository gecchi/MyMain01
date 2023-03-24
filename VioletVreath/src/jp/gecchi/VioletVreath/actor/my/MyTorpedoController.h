#ifndef MYTORPEDOCONTROLLER_H_
#define MYTORPEDOCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/actor/ex/DestructActor.h"

namespace VioletVreath {

/**
 * 魚雷コントローラー .
 * １オプションにつき１つの魚雷コントローラーを保持しています。
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyTorpedoController : public GgafCore::DestructActor {

public:
    /** [r]１オプション当たりの最大魚雷発射可能数 */
    static int max_torpedo_num_;
    /** [r]１オプション当たりの現在魚雷発射可能数 */
    static int torpedo_num_;

    /** [r]親アクターとなるオプション */
    GgafDx::GeometricActor* pOrg_;
    MyLockonController* pLockonCtrler_;
    /** [r]保持する魚雷配列（要素数は max_torpedo_num_ 個） */
    MyTorpedo** papTorpedo_;
    /** [r]保持する魚雷爆風デポジトリ */
    GgafCore::ActorDepository* pDepo_TorpedoBlast_;
    /** 同時発射魚雷数 */
    int firing_num_;
    /** 現在魚雷発射中かどうか true:いづれかの魚雷が活動中/false:全ての魚雷が非活動状態 */
    bool in_firing_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pOrg 親となるオプション
     * @return
     */
    MyTorpedoController(const char* prm_name, GgafDx::GeometricActor* prm_pOrg, MyLockonController* prm_pLockonCtrler);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    /**
     * 魚雷を一斉発射する。
     * 但し、いづれかの魚雷が活動中の場合は、何もしない。
     * 全ての魚雷が非活動状態で、本メソッドを実行すると魚雷を一斉発射する。
     */
    bool fire();

    virtual ~MyTorpedoController();


};

}
#endif /*MYTORPEDOCONTROLLER_H_*/

