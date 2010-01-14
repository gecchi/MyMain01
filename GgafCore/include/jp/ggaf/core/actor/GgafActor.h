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
 * void processHappen(int prm_no) ・・・その他のイベント時の処理 <BR>
 * bool processBumpChkLogic(GgafActor* prm_pOtherActor) ・・・衝突判定ロジック <BR>
 * void processOnHit(GgafActor* prm_pOtherActor) ・・・衝突判定ロジックがtrueの場合の処理 <BR>
 * <BR>
 * 基底テンプレートクラスの GgafNode と、GgafElement の説明も参照のこと。<BR>
 * @version 1.00
 * @since 2007/11/20
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
    GgafActor* _pActor_tmp1;
    GgafActor* _pActor_tmp2;
    GgafActor* _pActor_tmp3;
    GgafActor* _pActor_tmp4;

    bool _use_octree;
    /**
     * 所属シーンを設定する。 .
     */
    void setScenePlatform(GgafScene* prm_pScene_Platform);

//    /**
//     * 【自アクター 対 自ツリーアクターのどれか1つのアクター】の衝突判定処理を実行する .
//     * 本メソッドは executeBumpChk2_WeAnd(GgafActor*)から呼び出される専用メソッド。汎用性はない。<BR>
//     * 実行すると自アクターのprocessHitLogic()を呼び出し、その結果がtrueの場合(衝突した場合)は自身のprocessOnHit()と、
//     * 相手のアクターのprocessOnHit()を呼び出す。<BR>
//     * 戻り値の bool はヒットしたorしてないを意味する物ではないので忘れるな。<BR>
//     * @param	prm_pOtherActor	衝突判定する自ツリーアクターのどれか1つのアクター
//     * @retval	true	パラメータが自アクター
//     * @retval	false	パラメータが自アクター以外
//     */
//    bool executeBumpChk2_MeAnd(GgafActor* prm_pOtherActor);
//
//    /**
//     * 【自ツリーアクター 対 自ツリーアクターのどれか1つのアクター】ついて衝突判定処理(executeBumpChk_MeAnd)を実行する .
//     * executeBumpChk_RoundRobin2() から呼び出される。<BR>
//     * executeBumpChk_WeAnd(GgafActor*)と基本的に同じ組み合わせアルゴリズムであるが、<BR>
//     * 必ずやってくる自アクター同士当たり判定のチェックを行うようになってしまった時点で離脱し、<BR>
//     * それ以上再帰ループを行わないようしている。残りの組み合わせは後続のループで補われる。（ハズである）<BR>
//     * 離脱しても大丈夫な理由は、自アクター配下同士の総当たりであるため、単純に襷（タスキ）の組み合わせで行うと<BR>
//     *  Actor① → Actor② 　　（矢印は衝突判定するという意味）<BR>
//     *  Actor② → Actor①<BR>
//     * のように、衝突判定処理が重複してしまうため、これを避けるため途中でループ離脱するのである。<BR>
//     * executeBumpChk_RoundRobin2() 専用メソッドといっても良い。汎用性は無い。<BR>
//     * 戻り値の bool はヒットしたorしてないを意味する物ではないので忘れるな。<BR>
//     * @param	prm_pOtherActor	衝突判定する自ツリーアクターのどれか1つのアクター
//     * @retval	true	再帰処理打ち切り
//     * @retval	false	再帰処理続行
//     */
//    bool executeBumpChk2_WeAnd(GgafActor* prm_pOtherActor);

public:
    /** アクターの階級 */
    int _actor_class; //1:GgafLoadActor 2:GgafGroupActor 3:GgafMainActor 0:その他


    /** アクター開始システム時刻 */
    DWORD _start_system_time;

    /** アクター衝突判定有無フラグ */
    bool _can_bump_flg;

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

//    /**
//     * オーバーライド
//     */
//    virtual void addSubLast(GgafActor* prm_pSub) {
//        GgafElement<GgafActor>::addSubLast(prm_pSub);
//        if(prm_pSub->_was_initialize_flg == false) {
//            prm_pSub->initialize();
//            prm_pSub->_was_initialize_flg = true;
//        }
//    }

    /**
     * 自アクターの衝突判定有無を設定する。 .
     * @param	prm_can_bump_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     */
    void setBumpable(bool prm_can_bump_flg);

    /**
     * 自ツリーアクターの衝突判定有無を設定する。 .
     * @param	prm_can_bump_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     */
    void setBumpableTree(bool prm_can_bump_flg);

    /**
     * 衝突できるかどうか
     * @return	bool true:衝突できる／false:衝突できない
     */
    //bool canBump();
    inline bool canBump() {
        if (isActive() && _can_bump_flg) {
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

    inline void executeBumpChk_MeAnd(GgafActor* prm_pOtherActor) {
        if (prm_pOtherActor == this) {
            return;
        } else {
            if (_can_bump_flg &&
                prm_pOtherActor->_can_bump_flg &&
                _can_live_flg &&
                prm_pOtherActor->_can_live_flg &&
                _is_active_flg &&
                prm_pOtherActor->_is_active_flg)
            {
                if (processBumpChkLogic(prm_pOtherActor)) { //自身のヒットチェック
                    processOnHit(prm_pOtherActor); //自分のヒット時の振る舞い
                    prm_pOtherActor->processOnHit(this); //相手のヒット時の振る舞い
                }
            }
        }
    }

//    inline void executeBumpChk_WeAnd(GgafActor* prm_pOtherActor) {
//        executeBumpChk_MeAnd(prm_pOtherActor);
//        if (_pSubFirst != NULL) {
//            _pActor_tmp3 = _pSubFirst;
//            while (true) {
//                _pActor_tmp3->executeBumpChk_WeAnd(prm_pOtherActor);
//                if (_pActor_tmp3->_is_last_flg) {
//                    break;
//                } else {
//                    _pActor_tmp3 = _pActor_tmp3->_pNext;
//                }
//            }
//        }
//    }
//
//    inline void executeBumpChk_RoundRobin(GgafActor* prm_pOtherActor) {
//        executeBumpChk_WeAnd(prm_pOtherActor);
//        if (prm_pOtherActor->_pSubFirst != NULL) {
//            GgafActor* _pActor_tmpZ = prm_pOtherActor->_pSubFirst;
//            while (true) {
//                executeBumpChk_RoundRobin(_pActor_tmpZ);
//                if (_pActor_tmpZ->_is_last_flg) {
//                    break;
//                } else {
//                    _pActor_tmpZ = _pActor_tmpZ->_pNext;
//                }
//            }
//        }
//    }
//
//    inline bool executeBumpChk2_MeAnd(GgafActor* prm_pOtherActor) {
//        if (prm_pOtherActor == this) {
//            return true;
//        } else {
//            if (_can_bump_flg && prm_pOtherActor->_can_bump_flg && _can_live_flg && prm_pOtherActor->_can_live_flg && _is_active_flg
//                    && prm_pOtherActor->_is_active_flg) {
//                if (processBumpChkLogic(prm_pOtherActor)) { //自身のヒットチェック
//                    processOnHit(prm_pOtherActor); //自分のヒット時の振る舞い
//                    prm_pOtherActor->processOnHit(this); //相手のヒット時の振る舞い
//                }
//            }
//            return false;
//        }
//    }
//
//    inline bool executeBumpChk2_WeAnd(GgafActor* prm_pOtherActor) {
//        bool ret1 = executeBumpChk2_MeAnd(prm_pOtherActor);
//        bool ret2;
//        if (ret1) {
//            return true;
//        } else {
//            if (_pSubFirst != NULL) {
//                _pActor_tmp4 = _pSubFirst;
//                while (true) {
//                    ret2 = _pActor_tmp4->executeBumpChk2_WeAnd(prm_pOtherActor);
//                    if (ret2) {
//                        return true;
//                    } else {
//                        if (_pActor_tmp4->_is_last_flg) {
//                            break;
//                        } else {
//                            _pActor_tmp4 = _pActor_tmp4->_pNext;
//                        }
//                    }
//                }
//            }
//            return false;
//        }
//    }
//
//    inline void executeBumpChk_RoundRobin2(GgafActor* prm_pOtherActor) {
//        executeBumpChk2_WeAnd(prm_pOtherActor);
//        if (prm_pOtherActor->_pSubFirst != NULL) {
//            GgafActor* pActor_tmpZ2 = prm_pOtherActor->_pSubFirst;
//            while (true) {
//                executeBumpChk_RoundRobin2(pActor_tmpZ2);
//                if (pActor_tmpZ2->_is_last_flg) {
//                    break;
//                } else {
//                    pActor_tmpZ2 = pActor_tmpZ2->_pNext;
//                }
//            }
//        }
//    }

//
//    /**
//     * 【自アクター 対 他アクター】の衝突判定処理を実行する .
//     * 自身のprocessHitLogic()の結果、衝突した場合(true)は自身のprocessOnHit()と、相手アクターのprocessOnHit()が実行される <BR>
//     * 但し、引数に、自身のポインタを渡してはいけない。<BR>
//     * @param	prm_pOtherActor	相手の他アクター
//     */
//    void executeBumpChk_MeAnd(GgafActor* prm_pOtherActor);
//
//    /**
//     * 【自ツリーアクター 対 他アクター】の衝突判定処理を実行する .
//     * 内部的には、自ツリーアクター 全てについて、executeBumpChk_MeAnd(GgafActor*) を順次実行。<BR>
//     * 但し、引数に、自ツリーアクター所属のアクターのポインタを渡してはいけない。<BR>
//     * @param	prm_pOtherActor	相手の他アクター
//     */
//    void executeBumpChk_WeAnd(GgafActor* prm_pOtherActor);
//
//    /**
//     * 【自ツリーアクター 対 他ツリーアクター】の総当たりで衝突判定を実行する .
//     * 内部的には、引数である 他ツリーアクター の全てについて、executeBumpChk_WeAnd(GgafActor*) を順次実行しているだけ。<BR>
//     * 但し、自ツリーにも他ツリーにも同時に所属しているアクターがあってはいけない。<BR>
//     * @param	prm_pOtherActor	相手の他ツリーアクター
//     */
//    void executeBumpChk_RoundRobin(GgafActor* prm_pOtherActor);
//
//    /**
//     * 【自ツリーアクター 対 自ツリーアクターのどれか1つのアクターを頂点とするツリーアクター】の総当たりで衝突判定を実行する。.
//     * 内部的には、引数のアクター の全てについて、executeBumpChk2_WeAnd(GgafActor*) を順次実行しているだけ。<BR>
//     * 但し自アクター同士の重複組み合わせを無視する。 <BR>
//     * @param	prm_pOtherActor	自ツリーアクターのどれか1つのアクター
//     */
//    void executeBumpChk_RoundRobin2(GgafActor* prm_pOtherActor);
//
    /**
     * 自アクターと何かのアクターと衝突したかどうか判定する。 .
     * executeBumpChk_MeAnd(GgafActor*) が実行された場合に呼び出されることになる。<BR>
     * 下位クラスで衝突判定ロジックを実装する。<BR>
     * このメソッドは何時呼び出されるかは決まっていない。呼び出しタイミングも下位クラスで実装する。<BR>
     * 想定としては、processJudgement() メソッドを実装したクラスが、その中で本メソッドを呼び出すものとしている。<BR>
     * もしそのように実装した場合、相手アクターも processJudgement() でこちらのアクターとの衝突判定を行うことになれば、<BR>
     * 衝突判定処理重複することになる。この点を留意し、どーしたらよいか考えること。<BR>
     * @param	prm_pOtherActor	相手アクター
     * @retval	true	衝突しているを返す事
     * @retval	false	衝突していないを返す事
     */
    virtual bool processBumpChkLogic(GgafActor* prm_pOtherActor) {
        return false;
    }

    /**
     * アクターと衝突した時の処理 .
     * processBumpChkLogic(GgafActor*) が true の場合に呼び出されることになります。<BR>
     * 衝突判定の結果、衝突した場合の処理を下位クラス実装してください。<BR>
     * @param	prm_pOtherActor	衝突している相手のアクター（１つ）
     */
    virtual void processOnHit(GgafActor* prm_pOtherActor) {}

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
