#ifndef MYOPTIONTORPEDOCONTROLLER_H_
#define MYOPTIONTORPEDOCONTROLLER_H_
namespace VioletVreath {

/**
 * 魚雷コントローラー .
 * １オプションにつき１つの魚雷コントローラーを保持しています。
 * 魚雷の発射数は、１オプションの最大ロックオン可能数(MyOption::max_lockon_num_)と一致します。
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyOptionTorpedoController : public GgafCore::GgafDummyActor {

public:
    /** [r]親アクターとなるオプション */
    MyOption* pMyOption_;
    /** [r]保持する魚雷配列（要素数は MyOption::max_lockon_num_ 個） */
    MyTorpedo** papMyTorpedo_;
    /** [r]保持する魚雷爆風デポジトリ */
    GgafCore::GgafActorDepository* pDepo_TorpedoBlast_;
    /** 同時発射魚雷数 */
    int firing_num_;
    /** 現在魚雷発射中かどうか true:いづれかの魚雷が活動中/false:全ての魚雷が非活動状態 */
    bool in_firing_;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pMyOption 親となるオプション
     * @return
     */
    MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption);

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
    void fire();

    virtual ~MyOptionTorpedoController();


};

}
#endif /*MYOPTIONTORPEDOCONTROLLER_H_*/

