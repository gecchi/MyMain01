#ifndef GGAFACTOR_H_
#define GGAFACTOR_H_

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
 * void onCatchEvent(hashval prm_no, void* prm_pSource) ・・・その他のイベント時の処理 <BR>
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
    friend class GgafDirector;
    friend class GgafGroupHead;
    friend class GgafDummyActor;
    friend class GgafScene;
    friend class GgafUniverse;

private:
    /** 現在の所属シーン */
    GgafScene* _pScene_Platform;

    /**
     * 所属シーンを設定する。 .
     */
    void setPlatformScene(GgafScene* prm_pScene_Platform);

public:
    /** [r]所属デポジトリ(NULLは未所属) */
    GgafActorDepository* _pDependenceDepository;
    /** [r]所属フォーメーション(NULLは未所属) */
    GgafFormation* _pFormation;

    /** [r]アクター開始システム時刻 */
    UINT32 _start_system_time;
    /** [r]アクター衝突判定有無フラグ */
    bool _can_hit_flg;
    /** [r]true:視界外でもヒットチェックを行う/false:視界外はヒットチェックを行なわない */
    bool _can_hit_out_of_view;
    /** [r]自由ステータス */
    GgafStatus* _pStatus;

    /**
     * コンストラクタ .
     * @param prm_name アクターの名前
     */
    GgafActor(const char* prm_name, GgafStatus* prm_pStat);

    /**
     * デストラクタ .
     * 自ツリーアクターの解放を行います。
     */
    virtual ~GgafActor();

    /**
     * 自アクターの衝突判定有無を設定する。 .
     * @param prm_can_hit_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     * @param prm_can_hit_out_of_view_flg  衝突判定有りの場合、視野外衝突判定の有無を設定(true:画面外衝突判定有り／false:画面外衝突判定無し)
     */
    void setHitAble(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg = true);

    /**
     * 自ツリーアクターの衝突判定有無を設定する。 .
     * @param prm_can_hit_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     * @param prm_can_hit_out_of_view_flg  衝突判定有りの場合、視野外衝突判定の有無を設定(true:画面外衝突判定有り／false:画面外衝突判定無し)
     */
    void setHitAbleTree(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg = true);

    /**
     * 現在衝突できる状況かどうか判定 .
     * 注意：衝突能力があるかどうかでは無い。
     * @return	bool true:衝突可能状況／false:衝突不可能状況
     */
    inline bool canHit() {
        if (_can_live_flg && _is_active_flg && _can_hit_flg) {
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
            //ヒットできる物どうかの判定は事前にすんでいるようにする事。
            if (processHitChkLogic(prm_pOtherActor)) { //自身のヒットチェック
                onHit(prm_pOtherActor); //自分のヒット時の振る舞い
                prm_pOtherActor->onHit(this); //相手のヒット時の振る舞い
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
     * Depositoryに所属している場合、それを返す。
     * 未所属の場合NULL
     * @return 所属Depository
     */
    GgafActorDepository* getDependenceDepository() {
        return _pDependenceDepository;
    }

    /**
     * 自身が破壊された事を所属のフォーメーション(GgafDxFormationActor)に通知するメソッド .
     * 自身がフォーメーションに所属(_pFormation != NULL)している場合、
     * フォーメーションの編隊全滅判定を行うために、自身が編隊全滅に有効な消滅
     * （画面外、自滅等では無く、自機に破壊された場合）であることを通知する必要があります。<BR>
     * 破壊されたタイミングで本メソッドを実行すると、管理フォーメーションに通知しされます。<BR>
     * 通知を行うことにより、管理されている Formation オブジェクトから、
     * 編隊全滅時に、
     *
     * Formation::onDestroyedAll()
     *
     * のコールバックが行われます。
     * 編隊ボーナス、アイテム出現等の処理を GgafDxFormationActor::onDestroyedAll() の
     * オーバーライドで行って下さい。
     * <pre><code>
     * ＜例＞
     * void SampleActor::onHit(GgafActor* prm_pOtherActor) {
     *    //自身の耐久力チェック
     *    if (MyStgUtil::calcSampleStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
     *        //Hitの相手のチェック
     *        if (pOther->getKind() & KIND_MY) {
     *            //Hitの相手は自機関連（自機、自機ユニット、自機発射弾)
     *            notifyFormationAboutDestroyed(); //編隊全滅判定に有効な破壊を通知する
     *        }
     *    }
     * }
     * </pre></code>
     */
    virtual void notifyFormationAboutDestroyed();

    /**
     * さよならします .
     * Depository に所属している場合は inactiveAfter(prm_offset_frames) <BR>
     * Depository に所属していない場合は end(prm_offset_frames) <BR>
     * が、実行されます。
     * アクターをシーンから離脱させたい場合はこのメソッドを実行すること。
     * @param prm_offset_frames 猶予フレーム(1〜)
     */
    virtual void sayonara(frame prm_offset_frames = 1);

    /**
     * ツリー構造から切り離す .
     * @return
     */
    virtual GgafActor* extract() override;


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
