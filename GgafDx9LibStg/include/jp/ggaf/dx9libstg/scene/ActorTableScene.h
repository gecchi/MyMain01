#ifndef ACTORTABLESCENE_H_
#define ACTORTABLESCENE_H_
namespace GgafDx9LibStg {

/**
 * 早回し敵出現テーブル管理シーン .
 * 早回し敵出現とは具体的に、<BR>
 * ・敵（や編隊）が消滅すれば、即刻次の敵（や編隊）が出現。<BR>
 * ・敵が消滅せずとも、一定時間で次の敵が出現。<BR>
 * というようなテーブルのこと。<BR>
 * (斑鳩の敵出現テーブルのような感じで・・)<BR>
 * <b>＜使用方法＞</b><BR>
 * <pre><code>
 * ・あるSceneのprocessBehavior()等で次のコードを書いたとする。
 *
 *     ActorTableScene* ta = NEW ActorTableScene("TableScene_9");
 *     ta->setMaxPerformFrame(290);  //全体フレーム数設定
 *     addSubLast(ta);               //子シーンとして登録
 *     ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21047100)), 100);   //編隊a。全消滅しなくとも、次の編隊bは100フレーム後出現
 *     ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21057100)), 100);   //編隊b。全消滅しなくとも、次の編隊cは100フレーム後出現
 *     ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21067100)), 100);   //編隊c。全消滅しなくとも、次の編隊dは100フレーム後出現
 *     ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21077100)), 100);   //編隊d。全消滅しなくとも、次の編隊eは100フレーム後出現
 *     ta->addToTable(((FormationPallas001e*)obtainActorFromFactory(21087100)));        //編隊e。次の敵が無いため、フレーム数設定の意味は無くなる。
 *
 * ・これは下図のような事を意味する。
 *
 *  親シーン   --------------------+----------------------------+---------------------------->
 *  親フレーム                     n                            n+290
 *
 *  ＜何もしない場合＞
 *    子シーン(ActorTableScene)    +---------+---------+--------+
 *    子フレーム                   0         100       200      290
 *
 *                                 | a       | b       | c       |   d  ←  編隊d以降は出現しない。
 *                                 <--100---><--100---><--100---><--100--->      編隊dの出現タイミングは300となり、290までに間に合っていないため出現しない
 *
 *  ＜編隊aだけを早期撃破(80フレーム)された場合＞
 *    子シーン(ActorTableScene)    +------+---------+---------+-+
 *    子フレーム                   0      80        180     280 290
 *
 *                                 |a     | b       | c       | d  ←  編隊dは出現する。
 *                                 <--80-><--100---><--100---><--100--->   編隊dの出現タイミングが280となり、290までに間に合っているので出現する。
 *                                                                         仮に編隊dが10フレーム以内で消滅された場合は、編隊eも出現可能。
 *  </code></pre>
 * @version 1.00
 * @since 2010/08/19
 * @author Masatoshi Tsuge
 */
class ActorTableScene : public GgafDx9Core::GgafDx9Scene {

private:
    /**
     * 敵出現テーブル要素クラス .
     * 編隊アクター、最大待ちフレーム(_max_delay_offset) の情報を持ったコンテナ
     */
    class TblElem {
    public:
        /** 編隊アクター */
        GgafDx9Core::GgafDx9FormationActor* _pFormationActor;
        /** 編隊アクターが放置されたとしても、次の敵が出現するまでのフレーム数 */
        frame _max_delay_offset;

        /**
         * 要素コンストラクタ .
         * @param prm_pFormationActor 編隊アクター
         * @param prm_max_delay_offset 次の敵が出現するまでのフレーム数(省略時は0)
         * @return
         */
        TblElem(GgafDx9Core::GgafDx9FormationActor* prm_pFormationActor, frame prm_max_delay_offset = 0) {
            _pFormationActor = prm_pFormationActor;
            _max_delay_offset = prm_max_delay_offset;
        }
        virtual ~TblElem() {
            //_pActorはシーン所属となるため解放は不要
        }
    };

public:
    /** 早回し敵出現テーブル全体の許容フレーム */
    frame _max_perform_frame;
    /** テーブル内の現在の敵(アクター)が出現してからのフレーム数 */
    frame _frame_of_current_part_began;
    /** 敵出現テーブル(TblElemオブジェクトの連結リスト) */
    GgafCore::GgafLinkedListRing<TblElem> _table;

    /**
     * コンストラクタ .
     * @param prm_name シーン名
     * @return
     */
    ActorTableScene(const char* prm_name);

    /**
     * 現テーブルに敵編隊要素追加 .
     * 要素追加時、敵編隊アクターは非活動状態(inactivateImmediately())にさせられます。<BR>
     * 要素追加してから activate() は、しないでください。<BR>
     * @param prm_pFormationActor 敵編隊アクター
     * @param prm_max_delay_offset 次の敵出現までの、最大待ちフレーム数
     * @return
     */
    virtual GgafCore::GgafGroupHead* addToTable(GgafDx9Core::GgafDx9FormationActor* prm_pFormationActor, frame prm_max_delay_offset = 0);

    /**
     * 早回し敵出現テーブル全体の許容フレームを設定する。
     * 設定を行わない場合、0xffffffff が設定されている。
     * @param prm_max_perform_frame
     */
    virtual void setMaxPerformFrame(frame prm_max_perform_frame) {
        _max_perform_frame = prm_max_perform_frame;
    }

    virtual void initialize() override {
    }

    virtual void onActive() override;

    /**
     * テーブルにしたがって、敵(アクター)をactivate()していきます。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual void processDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual ~ActorTableScene();
};

}
#endif /*ACTORTABLESCENE_H_*/
