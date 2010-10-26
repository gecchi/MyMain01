#ifndef GGAFSCENE_H_
#define GGAFSCENE_H_

#define SCENE_PROG_NEW -1
#define SCENE_NOTHING_EVENT 0

namespace GgafCore {

/**
 * シーンクラス .
 * 本プログラムでの『シーン』とは、アプリ上での「場面」という概念を「ある纏まったもの」と考え、切り分けられたオブジェクトを言います。<BR>
 * 本クラスはそのまま new できません。直接・間接継承して実装する必要があります。<BR>
 * 機能として、シーンオブジェクト同士をポインタ接合し、ツリー階層構造を採る事ができます。（このツリー構造はクラスの継承と関係ありません。）<BR>
 * シーンに実装されているメソッド郡のほとんどは、自分自身と自分配下のシーン（自ツリーシーン）全てに影響する仕様になっています。<BR>
 * ゲーム（アプリ）というものは、<BR>
 * 「様々な『場面、つまりシーン(GgafScene)』で『キャラ、つまりアクター(GgafActor)』たちが活躍するものである。」<BR>
 * という概念の部分は共通化できるはずだと信じて設計を行いました。
 * アプリ全体を仮にアニメを再生しているものと考えた場合、シーンオブジェクトとは、<BR>
 * レイヤー（セル）のような物にあたります。<BR>
 * また、シーンクラスは管理者アクター(GgafLordActor)を管理するクラスでもあります。
 * 管理者アクターとはシーン毎のアクターの大親分のようなもので、GgafLordActor のコメントも参照して下さい。<BR>
 * 各シーンは、必ず１つの管理者アクター(GgafLordActor)をメンバとして保持しています。<BR>
 *
 * <B>【用語補足】</B>
 * <TABLE border='1'>
 * <TR>
 * <TD>「シーン」</TD>
 * <TD>シーンクラスのインスタンス（へのポインタ）を省略して、単にシーンと呼ぶことにします。</TD>
 * </TR><TR>
 * <TD>「自シーン」「自」</TD>
 * <TD>自分自身のインスタンス(this相当)。或いは、文脈の話題の中心となっているシーンが自シーンになる時もあります。</TD>
 * </TR><TR>
 * <TD>「サブシーン」「サブ」「子」</TD>
 * <TD>シーン同士のツリー階層構造上において、自シーンに<B>直に</B>ぶら下がる１階層下のシーン達を指しています。<BR>
 * シーンクラスを継承したクラスという意味では無いこととします。</TD>
 * </TR><TR>
 * <TD>「シーン配下」「配下」</TD>
 * <TD>シーン同士のツリー階層構造上において、自シーン<B>に</B>ぶら下がる全てのシーン達を指しています。サブシーンも当然含まれます。<BR>
 * シーンクラスを継承元クラスという意味では無いこととします。</TD>
 * </TR><TR>
 * <TD>「親シーン」「親」</TD>
 * <TD>シーン同士のツリー階層構造上において、自シーン<B>が</B>直接或いは間接的にぶら下がっているシーンを指しています。</TD>
 * </TR><TR>
 * <TD>「他シーン」「他」</TD>
 * <TD>自シーン以外のシーンを指しています。</TD>
 * </TR><TR>
 * <TD>「ツリー」</TD>
 * <TD>シーン同士がツリー階層構造によって連結されている1つのまとまりを表現する言葉。</TD>
 * </TR><TR>
 * <TD>「自所属ツリー」</TD>
 * <TD>自シーンが含まれている部分ツリー(或いはツリー全体)の階層構造を指します。</TD>
 * </TR><TR>
 * <TD>「自ツリー」</TD>
 * <TD>自シーンを頂点とする、自シーン＋自シーン配下のツリー階層構造を指します。</TD>
 * </TR><TR>
 * <TD>「自ツリーシーン」</TD>
 * <TD>自ツリーのシーン。つまり自シーン＋自シーン配下のシーン全てを指します。自シーンがツリーの頂点（最も親）に位置していることも意味しています</TD>
 * </TR><TR>
 * <TD>「シーンクラス」</TD>
 * <TD>GgafActorクラスを直接・間接継承しているクラス全般を指します。</TD>
 * </TR><TR>
 * <TD>「上位クラス」「下位クラス」</TD>
 * <TD>シーンクラスのクラスの継承関係を表しています。
 * クラス継承関係の表現は「スーパー」「サブ」又は「親」「子」は使わずに<B>「上位」「下位」</B>で統一することにします。<BR>
 * 「スーパー」「サブ」又は「親」「子」と言った場合はツリー階層構造のことを言っています。</TD>
 * </TR>
 * </TABLE>
 * <BR>
 * 本クラスは抽象クラスでそのまま new できません。<BR>
 * 全てのシーンクラスは、本クラスを直接・間接継承し少なくとも以下の仮想関数を実装しなければなりません。<BR>
 * <BR>
 * void initialize() ・・・初期処理 <BR>
 * void processBehavior() ・・・フレーム毎の振る舞い処理 <BR>
 * void processSettlementBehavior() ・・・フレーム毎の様々な判定処理の事前準備処理（全シーン振る舞い処理完了後の処理） <BR>
 * void processJudgement() ・・・フレーム毎の様々な判定処理の本処理 <BR>
 * void processPreDraw() ・・・フレーム毎の描画事前処理 <BR>
 * void processDraw() ・・・フレーム毎の描画本処理 <BR>
 * void processAfterDraw() ・・・フレーム毎の描画事後処理 <BR>
 * void processFinal() ・・・フレーム毎の終端処理 <BR>
 * void catchEvent(UINT32 prm_no, void* prm_pSource) ・・・その他のイベント時処理 <BR>
 * <BR>
 * @version 1.00
 * @since 2006/06/27
 * @author Masatoshi Tsuge
 */
class GgafScene : public GgafElement<GgafScene> {

    friend class GgafGod;
    friend class GgafUniverse;
    friend class GgafActor;
    friend class GgafGroupActor;
    friend class GgafLordActor;

protected:

    /** このシーンの管理者 */
    GgafLordActor* _pLordActor;

public:

    /**
     * コンストラクタ .
     * 引数： prm_name シーン名<BR>
     */
    GgafScene(const char* prm_name);

    /**
     * デストラクタ .
     * 自シーンの管理者のツリーアクターの解放を行ってから。<BR>
     * 自ツリーシーンの解放を行います<BR>
     */
    virtual ~GgafScene();

    virtual void addSubLast(GgafScene* prm_pScene) override {
        GgafElement<GgafScene>::addSubLast(prm_pScene);
//        if(prm_pScene->_was_initialize_flg == false) {
//            prm_pScene->initialize();
//            prm_pScene->_was_initialize_flg = true;
//        }
    }

    virtual void nextFrame() override;
    virtual void behave() override;
    virtual void settleBehavior() override;
    virtual void judge() override;
    virtual void preDraw() override;
    virtual void draw() override;
    virtual void afterDraw() override;
    virtual void doFinally() override;
    virtual void throwDownEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual void activateTree() override;
    virtual void activateDelay(frame prm_frame_offset = 1) override;
    virtual void activate() override;
    virtual void activateTreeImmediately() override;
    virtual void activateImmediately() override;
    virtual void inactivateTree() override;
    virtual void inactivateDelay(frame prm_frame_offset = 1) override;
    virtual void inactivate() override;
    virtual void inactivateTreeImmediately() override;
    virtual void inactivateImmediately() override;

    virtual void pauseTree() override;
    virtual void pause() override;
    virtual void pauseTreeImmediately() override;
    virtual void pauseImmediately() override;

    virtual void unpauseTree() override;
    virtual void unpause() override;
    virtual void unpauseTreeImmediately() override;
    virtual void unpauseImmediately() override;
    virtual void execDownFunction(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) override;
    /**
     * 自ツリーシーンをnフレーム後にゴミ箱へ移動 .
     * @param prm_frame_offset ゴミ箱へ移動タイミング残りフレーム数(デフォルト=1)
     */
    virtual void end(frame prm_frame_offset = 1) override;

    /**
     * 自ツリーを末端から開放する。 .
     * @param prm_num_cleaning 開放インスタンス数
     */
    virtual void clean(int prm_num_cleaning) override;

    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    virtual GgafGod* askGod() override;

    /**
     * 自シーンの管理者を取得 .
     * @return	管理者
     */
    virtual GgafLordActor* getLordActor();

    /**
     * デバッグ用：ツリー構造を表示 .
     */
    virtual void dump();

    /**
     * デバッグ用：dump()から使用される .
     */
    virtual void dump(std::string prm_parent);
};

}
#endif /**GGAFSCENE_H_*/
