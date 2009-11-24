#ifndef GGAFSCENE_H_
#define GGAFSCENE_H_

#define SCENE_PROG_NEW -1
#define SCENE_NOTHING_EVENT 0

namespace GgafCore {

/**
 * シーンクラス .
 * 本プログラムでの『シーン』とは、アプリ上での「場面」という概念を「ある纏まったもの」と考え、切り分けられたオブジェクトを言います。<BR>
 * 本クラスはそのまま new できません。直接・間接継承して実装する必要があります。<BR>
 * 機能として、シーン同士のポインタ接合し、ツリー階層構造を採る事ができます。（このツリー構造はクラスの継承とは関係ありません）<BR>
 * シーンに実装されているメソッド郡のほとんどは、自分自身と自分配下のシーン（自ツリーシーン）全てに影響する仕様になっています。<BR>
 * ゲーム（アプリ）というものは、<BR>
 * 「様々な『シーン（場面）』で『アクター(キャラ)』たちが活躍するものである。」<BR>
 * という部分は共通化できると信じて設計してあります。 アプリ全体を仮にムービーが再生しているものと考えた場合、シーンオブジェクトとは、<BR>
 * レイヤー（透明のセル）のような物にあたるという考え方です。<BR>
 * また、シーンクラスは管理者アクター(GgafLoadActor)を管理するクラスでもあります。 管理者アクターとはシーン毎のアクターの大親分のようなもの、<BR>
 * GgafLoadActor も参照して下さい。<BR>
 * 各シーンは、必ず１つの管理者をメンバとして保持しています。<BR>
 *
 * <B>【用語補足】</B>
 * <TABLE border='1'>
 * <TR>
 * <TD>「シーン」</TD>
 * <TD>シーンクラスのインスタンス（オブジェクト）を省略して、単にシーンと呼ぶことにします。</TD>
 * </TR><TR>
 * <TD>「自シーン」「自」</TD>
 * <TD>メソッドが実行されるシーンオブジェクト自身を指しています。</TD>
 * </TR><TR>
 * <TD>「サブシーン」「サブ」「子」</TD>
 * <TD>シーン同士のツリー階層構造上において、シーンに<B>直に</B>ぶら下がる１階層下のシーン達を指しています。</TD>
 * </TR><TR>
 * <TD>「シーン配下」「配下」</TD>
 * <TD>シーン同士のツリー階層構造上において、シーン<B>に</B>ぶら下がる全てのシーンを指しています。サブも含まれます。</TD>
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
 * <TD>自シーンが含まれているツリーを指します。</TD>
 * </TR><TR>
 * <TD>「自ツリー」</TD>
 * <TD>自シーンを頂点とする、自シーン＋自シーン配下のツリー階層構造部分を指します。</TD>
 * </TR><TR>
 * <TD>「自ツリーシーン」</TD>
 * <TD>自シーン＋自シーン配下のシーン全てを指します。自シーンが自ツリーの頂点（最も親）に位置していることも意味しています</TD>
 * </TR><TR>
 * <TD>「シーンクラス」</TD>
 * <TD>GgafActorクラスを直接・間接継承しているクラス全般を指します。</TD>
 * </TR><TR>
 * <TD>「上位」「下位」</TD>
 * <TD>シーンクラスのクラスの継承関係を表しています。
 * クラス継承関係の表現は「スーパー」「サブ」又は「親」「子」と言わずに<B>「上位」「下位」</B>で統一することにします。<BR>
 * 「スーパー」「サブ」又は「親」「子」と言った場合はツリー階層構造のことを言っています。</TD>
 * </TR>
 * </TABLE>
 * <BR>
 * 本クラスは抽象クラスでそのまま new できません。<BR>
 * 全てのシーンクラスは、本クラスを直接・間接継承し少なくとも以下の仮想関数を実装しなければなりません。<BR>
 * <BR>
 * void initialize() ・・・初期処理 <BR>
 * void processBehavior() ・・・フレーム毎の振る舞い処理 <BR>
 * void processJudgement() ・・・フレーム毎の様々な判定処理（全シーン振る舞い処理完了後の処理） <BR>
 * void processPreDraw() ・・・フレーム毎の描画事前処理 <BR>
 * void processDraw() ・・・フレーム毎の描画本処理 <BR>
 * void processAfterDraw() ・・・フレーム毎の描画事後処理 <BR>
 * void processFinal() ・・・フレーム毎の終端処理 <BR>
 * void processHappen(int prm_no) ・・・その他のイベント時処理 <BR>
 * <BR>
 * @version 1.00
 * @since 2006/06/27
 * @author Masatoshi Tsuge
 */
class GgafScene : public GgafElement<GgafScene> {

    friend class GgafGod;
    friend class GgafUniverse;
    friend class GgafActor;
    friend class GgafHeadActor;
    friend class GgafLordActor;

protected:

    /** このシーンの管理者 */
    GgafLordActor* _pLordActor;

    static GgafHeadActor* _apHeadActor01[];
    static GgafHeadActor* _apHeadActor02[];

public:
    /** 進捗具合 */
    int _progress;
    /** １フレーム前進捗 */
    int _progress_prev;
    /** 次フレーム設定する進捗具合 */
    int _progress_nextframe;

    /** 進捗イベント時フレームストック */
    DWORD _aFrame_ProgressChange[100];

    /**
     * 現在の進捗取得 .
     * @return 進捗(1～99)
     */
    virtual int getProgress() {
        return _progress;
    }

    /**
     * 進捗が起こった時のフレーム取得 .
     * @param prm_progress 進捗(1～99)
     * @return 引数の直近の進捗が起こったときのフレーム
     */
    virtual DWORD getFrameAtProgress(int prm_progress) {
        return _aFrame_ProgressChange[prm_progress];
    }

    /**
     * 進捗を設定 .
     * @param prm_progress 進捗(1～99)
     */
    virtual void setProgress(int prm_progress) {
        _progress_nextframe = prm_progress;
        _aFrame_ProgressChange[prm_progress] = _lifeframe+1;
    }

    bool onChangeProgressAt(int prm_progress) {
        if (_progress != _progress_prev) {
            if (prm_progress == _progress) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    /**
     * 進捗が変化したか調べる .
     * @return 0 又は 進捗(0=変化していない/0以外=変化があった新しい進捗)
     */
    int getProgressOnChange() {
        if (_progress != _progress_prev) {
            return _progress;
        } else {
            return 0; // = false
        }
    }

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

    /**
     * オーバーライド
     */
    virtual void addSubLast(GgafScene* prm_pScene) {
        GgafElement<GgafScene>::addSubLast(prm_pScene);
        if(prm_pScene->_was_initialize_flg == false) {
            prm_pScene->initialize();
            prm_pScene->_was_initialize_flg = true;
        }
    }

    virtual void nextFrame();
    virtual void behave();
    virtual void preJudge();
    virtual void judge();
    virtual void preDraw();
    virtual void draw();
    virtual void afterDraw();
    virtual void finally();

    virtual void happen(int prm_no);

    virtual void activateTree();
    virtual void activateAfter(DWORD prm_frame_offset);
    virtual void activate();
    virtual void activateTreeImmediately();
    virtual void activateImmediately();

    virtual void inactivateTree();
    virtual void inactivateAfter(DWORD prm_frame_offset);
    virtual void inactivate();
    virtual void inactivateTreeImmediately();
    virtual void inactivateImmediately();

    virtual void pauseTree();
    virtual void pause();
    virtual void pauseTreeImmediately();
    virtual void pauseImmediately();

    virtual void unpauseTree();
    virtual void unpause();
    virtual void unpauseTreeImmediately();
    virtual void unpauseImmediately();

    /**
     * 自ツリーシーンを次フレーム絶命させる。 .
     * ＜OverRide です＞<BR>
     */
    virtual void adios(DWORD prm_frame_offset = 0);

    /**
     * 自ツリーシーンを絶命させる。 .
     * ＜OverRide です＞<BR>
     */
    virtual void cleane(int prm_num_cleaning);

    /**
     * 神に謁見 .
     * @return	呼ばれて出てきた神
     */
    virtual GgafGod* askGod();

    /**
     * 自シーンの管理者を取得 .
     * @return	管理者
     */
    virtual GgafLordActor* getLordActor();

    /**
     * 自ツリーシーンのアクターに衝突判定を実行 (遅い方。こちらはgetName()のstd::string比較なのでやや遅い。次のメソッドを使う方が良いだー).
     * 自ツリーシーン全てに対して、各シーンに所属する管理者のサブアクターである GgafHeadActor 全てに対して<BR>
     * GgafActor#executeBumpChk_RoundRobinを実行する。<BR>
     * @param	prm_actor_kind_name01	判定する対象のGgafHeadActorに登録されているActor種別名
     * 		    prm_actor_kind_name02	判定される対象のGgafHeadActorに登録されているActor種別名<BR>
     */
    //virtual void executeBumpChkHeadActors(std::string prm_actor_kind_name01, std::string prm_actor_kind_name02);


    /**
     * 自ツリーシーンのアクターに衝突判定を実行 （速いほう）.
     * 自ツリーシーン全てに対して、各シーンに所属する管理者のサブアクターである GgafHeadActor 全てに対して<BR>
     * GgafActor#executeBumpChk_RoundRobinを実行する。<BR>
     * @param	prm_actorkind01	判定する対象のGgafHeadActorに登録されているActor種別
     * 		    prm_actorkind01	判定される対象のGgafHeadActorに登録されているActor種別<BR>
     */
    //virtual void executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02);
    /**
     * 経過フレーム判定。 .
     * 直前の delay(n) 実行時（結果がtrue/falseに関わらず）のフレーム数からの経過フレーム数に達したか判定する。<BR>
     * 注意：入れ子で使用した場合はうまく動きません。<BR>
     * @param	prm_dwFrame_delay	経過フレーム数
     * @return	bool	true:経過フレーム数に達した/false:達していない
     */
    //	virtual bool delayed(_delay);

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
