#ifndef MYOPTIONTORPEDOCONTROLLER_H_
#define MYOPTIONTORPEDOCONTROLLER_H_
namespace MyStg2nd {

/**
 * 魚雷コントローラー .
 * １オプションにつき１つの魚雷コントローラーを保持しています。
 * 魚雷の発射数は、１オプションの最大ロックオン可能数(MyOption::_max_lockon_num)と一致します。
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyOptionTorpedoController : public GgafCore::GgafDummyActor {

public:
    /** [r]親アクターとなるオプション */
    MyOption* _pMyOption;
    /** [r]保持する魚雷配列（要素数は MyOption::_max_lockon_num 個） */
    MyTorpedo** _papMyTorpedo;
    /** [r]保持する魚雷爆風デポジトリ */
    GgafCore::GgafActorDepository* _pDepo_TorpedoBlast;
    /** 同時発射魚雷数 */
    int _firing_num;
    /** 現在魚雷発射中かどうか true:いづれかの魚雷が活動中/false:全ての魚雷が非活動状態 */
    bool _in_firing;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_pMyOption 親となるオプション
     * @return
     */
    MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

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

