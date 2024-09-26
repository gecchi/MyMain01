#ifndef GGAF_CORE_ACTOR_H_
#define GGAF_CORE_ACTOR_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Element.hpp"
#include "jp/ggaf/core/util/Status.h"

#define STAT_DEFAULT_ACTOR_KIND 0

namespace GgafCore {

/**
 * アクター（演者）の基底クラス .
 * 本プログラムでの『アクター』とは、主にキャラクターを表現する。<BR>
 * 各シーン(Scene)に所属し、活躍するイメージ。<BR>
 * Element に当たり判定を実現する仕組みを加えたクラスになっている。<BR>
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
 * void onCatchEvent(eventval prm_event_val, void* prm_pSource) ・・・その他のイベント時の処理 <BR>
 * void onHit(const Actor* prm_pOtherActor) ・・・衝突判定ロジックがtrueの場合の処理 <BR>
 * <BR>
 * 基底テンプレートクラスの Node と、Element の説明も参照のこと。<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class Actor : public Element<Actor> {

    friend class Caretaker;
    friend class MainActor;
    friend class SceneChief;
    friend class DestructActor;
    friend class Scene;
    friend class Spacetime;
    friend class GarbageBox;

public:
#ifdef MY_DEBUG
    static unsigned int _num_actors;
#endif
    /** [r]所属デポジトリ(nullptrは未所属) */
    ActorDepository* _pDependenceDepository;
    /** [r]所属フォーメーション(nullptrは未所属) */
    Formation* _pFormation;

    /** [r]アクター衝突判定有無フラグ */
    bool _can_hit_flg;
    /** [r]true:視界外でもヒットチェックを行う/false:視界外はヒットチェックを行なわない */
    bool _enable_out_of_view_hit_flg;
    /** [r/w]自由ステータス */
    Status* _pStatus;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクターの名前
     */
    Actor(const char* prm_name);

    /**
     * デストラクタ .
     * 自ツリーアクターの解放を行います。
     */
    virtual ~Actor();

    /**
     * 自アクターの衝突判定有無を設定する。 .
     * @param prm_can_hit_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     * @param prm_enable_out_of_view_hit_flg  衝突判定有りの場合、視野外衝突判定の有無を設定(true:画面外衝突判定有り／false:画面外衝突判定無し)
     */
    void setHitAble(bool prm_can_hit_flg, bool prm_enable_out_of_view_hit_flg) {
        _can_hit_flg = prm_can_hit_flg;
        _enable_out_of_view_hit_flg = prm_enable_out_of_view_hit_flg;
    }
    /**
     * 自アクターの衝突判定有無を設定する。 .
     * 視野外衝突判定の有無は変化しない。
     * @param prm_can_hit_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     */
    void setHitAble(bool prm_can_hit_flg) {
        _can_hit_flg = prm_can_hit_flg;
    }

    /**
     * 視野外衝突判定の有無を設定 .
     * 衝突判定有無は変化しない。
     * @param prm_enable_out_of_view_hit_flg (true:画面外衝突判定有り／false:画面外衝突判定無し)
     */
    void enableOutOfViewHit(bool prm_enable_out_of_view_hit_flg) {
        _enable_out_of_view_hit_flg = prm_enable_out_of_view_hit_flg;
    }
    /**
     * 自ツリーアクターの衝突判定有無を設定する。 .
     * @param prm_can_hit_flg  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     * @param prm_enable_out_of_view_hit_flg  衝突判定有りの場合、視野外衝突判定の有無を設定(true:画面外衝突判定有り／false:画面外衝突判定無し)
     */
    void setHitAbleTree(bool prm_can_hit_flg, bool prm_enable_out_of_view_hit_flg);
    void setHitAbleTree(bool prm_can_hit_flg);
    /**
     * 現在衝突できる状況かどうか判定 .
     * 注意：衝突能力があるかどうかでは無い。
     * @return	bool true:衝突可能状況／false:衝突不可能状況
     */
    inline bool canHit() const {
        if (_can_live_flg && _is_active_flg && _can_hit_flg) {
            return true;
        } else {
            return false;
        }
    }


    /**
     * アクターと衝突した時の処理 .
     * _pChecker->processHitChkLogic(Checker*) が true の場合に呼び出されることになります。<BR>
     * 衝突判定の結果、衝突した場合の処理を下位クラス実装してください。<BR>
     * @param	prm_pOtherActor	衝突している相手のアクター（１つ）
     */
    virtual void onHit(const Actor* prm_pOtherActor) {}

    /**
     * Depositoryに所属している場合、それを返す。
     * 未所属の場合nullptr
     * @return 所属Depository
     */
    ActorDepository* getDependenceDepository() const {
        return _pDependenceDepository;
    }

    /**
     * 破壊されたことを通知 .
     * 自身が編隊全滅判定に有効な破壊のされ方などで、破壊されて消滅した事を、所属のフォーメーションに通知するメソッド .
     * 自身がフォーメーションに所属している(_pFormation != nullptr)場合、
     * フォーメーションの編隊全滅判定を行うために、自身が編隊全滅に有効な消滅、つまり
     * 画面外、自滅、では無く、自機に破壊された場合、本メソッドを実行して、管理フォーメーションに通知して下さい。<BR>
     * 通知を行うことにより、管理されている Formation オブジェクトから、
     * 編隊全滅時に、
     *
     * Formation::onDestroyAll()
     *
     * のコールバックが行われます。
     * 編隊ボーナス、アイテム出現等の処理を GgafDx::FormationActor::onDestroyAll() の
     * オーバーライドで行って下さい。
     * <code><pre>
     * ＜例＞
     * void SampleActor::onHit(const Actor* prm_pOtherActor) {
     *    //自身の耐久力チェック
     *    if (MyStgUtil::calcSampleStatus(_pStatus, _kind, pOther->_pStatus, pOther->_kind) <= 0) {
     *        //Hitの相手のチェック
     *        if (pOther->kind & KIND_MY) {
     *            //Hitの相手は自機関連（自機、自機ユニット、自機発射弾)
     *            notifyDestroyed(); //編隊全滅判定に有効な破壊を通知する
     *        }
     *    }
     * }
     *
     * </pre></code>
     * 自身がフォーメーションに所属していない(_pFormation == nullptr)場合、本メソッドは何も起こりません。
     */
    virtual void notifyDestroyed();

    /**
     * 自身がの所属のフォーメーションを返す .
     * @return フォーメーション。或いは、所属してない場合はnullptr
     */
    inline virtual Formation* getFormation() const {
        return _pFormation;
    }
    /**
     * さよならします .
     * Depository に所属している場合は inactiveAfter(prm_offset_frames) <BR>
     * Depository に所属していない場合は end(prm_offset_frames) <BR>
     * が、実行されます。
     * アクターをシーンから離脱させたい場合はこのメソッドを実行すること。
     * @param prm_offset_frames 猶予フレーム(1～)
     */
    virtual void sayonara(frame prm_offset_frames = 1);

    /**
     * オブジェクトが何のクラス由来かを調べる。
     * _obj_class メンバ変数に Obj_xxxx マクロ定数が設定されていることが前提。
     * @param prm_Obj_xxxx 調べるクラスのマクロ定数
     * @return
     */
    virtual bool instanceOf(uint64_t prm_Obj_xxxx) const override {
        if ((Obj_SceneBit & prm_Obj_xxxx) == Obj_SceneBit) {
            //シーンを示すビットが立っていたら
            return false;
        } else {
            return Element<Actor>::instanceOf(prm_Obj_xxxx);
        }
    }

    inline Status* getStatus() const {
        return _pStatus;
    }

    /**
     * アクターのデフォルトの種別を取得 .
     * @return アクターのデフォルトの種別
     */
    inline kind_t getDefaultKind() const {
        return (kind_t)getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND);
    }

    /**
     * アクターのデフォルトの種別を設定 .
     * @param prm_kind アクターのデフォルトの種別
     */
    inline void setDefaultKind(kind_t prm_kind) const {
        return getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_kind);
    }

    virtual void appendChild(Actor* prm_pActor) override;

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
#endif /*GGAF_CORE_ACTOR_H_*/
