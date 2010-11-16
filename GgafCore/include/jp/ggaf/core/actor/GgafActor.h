#ifndef GGAFACTOR_H_
#define GGAFACTOR_H_

#define LORDACTOR  1
#define GROUPACTOR  2
#define MAINACTOR  3

#define STAT_DEFAULT_ACTOR_KIND 0


namespace GgafCore {


/**
 * アクターの基底クラス .
 * 本プログラムで言う『アクター』とは、主にキャラクターを表現する。<BR>
 * 各シーン(GgafScene)に所属し、活躍するイメージ。<BR>
 * GgafElement に当たり判定を実現する仕組みを加えたクラスになっている。<BR>
 * 本クラスは抽象クラスでそのまま new はできない。<BR>
 * 全てのアクタークラスは、本クラスを継承し少なくとも以下の純粋仮想関数を実装する必要がある。<BR>
 * <BR>
 * ＜１度だけ呼び出される純粋仮想関数＞<BR>
 * void initialize() ・・・初期処理 <BR>
 * ＜通常、毎フレーム呼び出される純粋仮想関数＞<BR>
 * void processBehavior() ・・・フレーム毎の振る舞い処理（座標移動等） <BR>
 * void processJudgement() ・・・フレーム毎の様々な判定処理（全アクター振る舞い処理後の処理） <BR>
 * void processPreDraw() ・・・フレーム毎の描画事前処理 <BR>
 * void processDraw() ・・・フレーム毎の描画本処理 <BR>
 * void processAfterDraw() ・・・フレーム毎の描画事後処理 <BR>
 * void processFinal() ・・・フレーム毎の終端処理 <BR>
 * ＜毎フレーム呼び出されるわけではない純粋仮想関数＞<BR>
 * void onCatchEvent(UINT32 prm_no, void* prm_pSource) ・・・その他のイベント時の処理 <BR>
 * bool processHitChkLogic(GgafActor* prm_pOtherActor) ・・・衝突判定ロジック <BR>
 * void onHit(GgafActor* prm_pOtherActor) ・・・衝突判定ロジックがtrueの場合の処理 <BR>
 * <BR>
 * 基底テンプレートクラスの GgafNode と、GgafElement の説明も参照のこと。<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafActor : public GgafElement<GgafActor> {

    friend class GgafGod;
    friend class GgafMainActor;
    friend class GgafLordActor;
    friend class GgafGroupActor;
    friend class GgafDummyActor;
    friend class GgafScene;
    friend class GgafUniverse;

private:

    /** 現在の所属シーン */
    GgafScene* _pScene_Platform;

    /** ループ用 */
    GgafActor* _pActor_tmp;
    /** ８分木登録を行うかどうかのフラグ */
    bool _use_octree;

    /**
     * 所属シーンを設定する。 .
     */
    void setScenePlatform(GgafScene* prm_pScene_Platform);

public:
    /** [r]所属ディスパッチャー(NULLは未所属) */
    GgafActorDispatcher* _pDependenceDispcher;
    /** [r]アクター開始システム時刻 */
    UINT32 _start_system_time;
    /** [r]アクター衝突判定有無フラグ */
    bool _can_hit_flg;
    /** [r]自由ステータス */
    GgafStatus* _pStatus;

    /**
     * コンストラクタ .
     * @param prm_name アクターの名前
     */
    GgafActor(const char* prm_name);

    /**
     * デストラクタ .
     * 自ツリーアクターの解放を行います。
     */
    virtual ~GgafActor();

    /**
     * 自アクターの衝突判定有無を設定する。 .
     * @param	prm_can_hit_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     */
    void setHitAble(bool prm_can_hit_flg);

    /**
     * 自ツリーアクターの衝突判定有無を設定する。 .
     * @param	prm_can_hit_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     */
    void setHitAbleTree(bool prm_can_hit_flg);

    /**
     * 現在衝突できる状況かどうか判定 .
     * 注意：衝突能力があるかどうかでは無い。
     * @return	bool true:衝突可能状況／false:衝突不可能状況
     */
    inline bool canHit() {
        if (isActive() && _can_hit_flg) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * 所属しているシーンを取得。 .
     * @return	GgafScene*	所属しているシーン
     */
    virtual GgafScene* getPlatformScene();

    /**
     * 自アクターと他アクターの１対１の当たり判定処理を行う。
     * @param prm_pOtherActor 他アクター
     */
    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
        if (prm_pOtherActor == this) {
            return;
        } else {
            if (canHit() && prm_pOtherActor->canHit() &&
                _can_live_flg && prm_pOtherActor->_can_live_flg ) {
                if (processHitChkLogic(prm_pOtherActor)) { //自身のヒットチェック
                    onHit(prm_pOtherActor); //自分のヒット時の振る舞い
                    prm_pOtherActor->onHit(this); //相手のヒット時の振る舞い
                }
            }
        }
    }


    /**
     * 自アクターと何かのアクターと衝突したかどうか判定するロジック。 .
     * executeHitChk_MeAnd(GgafActor*) が実行された場合に呼び出されることになる。<BR>
     * 下位クラスで独自に衝突判定ロジックを実装する。<BR>
     * このメソッドは何時呼び出されるかは決まっていない。呼び出しタイミングも下位クラス依存。<BR>
     * 想定としては、processJudgement() メソッドを実装したクラスが、その中で本メソッドを呼び出すものとしている。<BR>
     * もしそのように実装した場合、相手アクターも processJudgement() でこちらのアクターとの衝突判定を行うことになれば、<BR>
     * 衝突判定処理重複することになる。どーしたらよいか考えること。<BR>
     * @param	prm_pOtherActor	相手アクター
     * @retval	true	衝突しているを返す事
     * @retval	false	衝突していないを返す事
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) {
        return false;
    }

    /**
     * アクターと衝突した時の処理 .
     * processHitChkLogic(GgafActor*) が true の場合に呼び出されることになります。<BR>
     * 衝突判定の結果、衝突した場合の処理を下位クラス実装してください。<BR>
     * @param	prm_pOtherActor	衝突している相手のアクター（１つ）
     */
    virtual void onHit(GgafActor* prm_pOtherActor) {}

    /**
     * Dispcherに所属している場合、それを返す。
     * 未所属の場合NULL
     * @return 所属Dispcher
     */
    GgafActorDispatcher* getDependenceDispcher() {
        return _pDependenceDispcher;
    }

    /**
     * さよならします .
     * Dispcherに所属している場合は inactiveAfter(prm_frame_offset) <BR>
     * Dispcherに所属していない場合は end(prm_frame_offset) <BR>
     * が、実行されます。
     * アクターをシーンから離脱させたい場合はこのメソッドを実行すること。
     * @param prm_frame_offset 猶予フレーム(1～)
     */
    virtual void sayonara(frame prm_frame_offset = 1);



    /**
     * デバッグ用：ツリー構造を表示<BR>
     */
    virtual void dump();

    /**
     * デバッグ用：dump()から使用される<BR>
     */
    virtual void dump(std::string prm_parent);

};

}
#endif /**GGAFACTOR_H_*/
