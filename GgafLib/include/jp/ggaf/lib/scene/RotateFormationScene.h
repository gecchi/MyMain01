#ifndef GGAF_LIB_ROTATEFORMATIONSCENE_H_
#define GGAF_LIB_ROTATEFORMATIONSCENE_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"

namespace GgafLib {

/**
 * 早回し敵編隊テーブル管理シーン .
 * 早回し敵編隊とは具体的に、<BR>
 * ・編隊が消滅すれば、即刻次の編隊が出現。<BR>
 * ・編隊が消滅せずとも、一定時間で次の編隊が出現。<BR>
 * というようなテーブルのこと。<BR>
 * (斑鳩の敵出現テーブルのような感じで・・)<BR>
 * <b>＜使用方法＞</b><BR>
 * <pre><code>
 * ・あるSceneのprocessBehavior()等で次のコードを書いたとすると。
 *
 *     RotateFormationScene* ftbl = NEW RotateFormationScene("TableScene_9");
 *     appendChild(ftbl);               //子シーンとして登録
 *     ftbl->setMaxPerformFrame(280);  //編隊テーブル全体フレーム数設定
 *     ftbl->addFormation(((FormationAllas001a*)receiveActor(21047100)), 100);   //編隊a。次の 編隊b は 編隊a が全消滅した場合即出現。全消滅しなくとも、100フレーム後出現。
 *     ftbl->addFormation(((FormationAllas001b*)receiveActor(21057100)), 100);   //編隊b。次の 編隊c は 編隊b が全消滅した場合即出現。全消滅しなくとも、100フレーム後出現。
 *     ftbl->addFormation(((FormationAllas001c*)receiveActor(21067100)), 100);   //編隊c。次の 編隊d は 編隊c が全消滅した場合即出現。全消滅しなくとも、100フレーム後出現。
 *     ftbl->addFormation(((FormationAllas001d*)receiveActor(21077100)), 100);   //編隊d。次の 編隊e は 編隊d が全消滅した場合即出現。全消滅しなくとも、100フレーム後出現。
 *     ftbl->addFormation(((FormationAllas001e*)receiveActor(21087100)));        //編隊e。次の敵が無いため、フレーム数設定の意味は無くなる。
 *
 * ・これは下図のような事を意味する。
 *                                                             :
 *  親シーン   --------------------+---------------------------+---------------------------->
 *  親フレーム                     n                        n+280
 *                                                             :
 *  ＜何も撃破しない場合＞                                     :
 *   子シーン(RotateFormationScene)+---------+---------+-------+-+---
 *   子フレーム                    0        100       200   280: 300
 *                                                             :
 *                                 | a       | b       | c     : | d       ← 編隊d以降は出現しない。
 *                                  <--100--> <--100--> <--100--> <--100--->  編隊dの出現タイミングは300となり、
 *                                                             :              280までに間に合っていないため出現しない
 *  ＜編隊aだけを早期撃破(75フレームで撃破)した場合＞          :
 *   子シーン(RotateFormationScene)+------+---------+---------++---
 *   子フレーム                    0     75        175      275:280
 *                                                             :
 *                                 |a     | b       | c       |: d      ←編隊dは出現する。
 *                                  <-75-> <--100--> <--100--> <--100---> 編隊dの出現タイミングが275となり、
 *                                                             :          280までに間に合っているので出現する。
 *                                                             :          仮に編隊dが5フレーム以内で消滅された場合は、編隊eも出現可能。
 *  </code></pre>
 * 即刻次の編隊、という即効表示が必要な場合は、TreeFormation より、DepositoryFormationのほうが
 * 編隊準備が不要なので良い・・・。
 * @version 1.00
 * @since 2010/08/19
 * @author Masatoshi Tsuge
 */
class RotateFormationScene : public DefaultScene {

private:
    /**
     * 敵出現テーブル要素クラス .
     * 編隊アクター、最大待ちフレーム(_max_delay_offset) の情報を持ったコンテナ
     */
    class FormationTblElem {
    public:
        /** 編隊アクター */
        GgafCore::Formation* _pFormationActor;
        /** 編隊アクターが放置されたとしても、次の敵が出現するまでのフレーム数 */
        frame _max_delay_offset;

        /**
         * 要素コンストラクタ .
         * @param prm_pFormationActor 編隊アクター
         * @param prm_max_delay_offset 次の敵が出現するまでのフレーム数(省略時は0)
         * @return
         */
        FormationTblElem(GgafCore::Formation* prm_pFormationActor, frame prm_max_delay_offset = 0) {
            _pFormationActor = prm_pFormationActor;
            _max_delay_offset = prm_max_delay_offset;
        }
        virtual ~FormationTblElem() {
            //_pFormationActorはシーン所属となるため解放は不要
        }
    };

public:
    /** 早回し敵出現テーブル全体の許容フレーム */
    frame _max_perform_frame;
    /** テーブル内の現在の敵(アクター)が出現してからのフレーム数 */
    frame _frame_of_current_part_began;
    /** 敵出現テーブル(FormationTblElemオブジェクトの連結リスト) */
    GgafCore::RingLinkedList<FormationTblElem> _table;

public:
    /**
     * コンストラクタ .
     * @param prm_name シーン名
     * @return
     */
    RotateFormationScene(const char* prm_name);

    /**
     * 現テーブルに敵編隊要素追加 .
     * 要素追加時、敵編隊アクターは非活動状態(inactivateImmed())にさせられます。<BR>
     * 要素追加してから activate() は、しないでください。<BR>
     * @param prm_pFormationActor 敵編隊アクター
     * @param prm_max_delay_offset 次の敵出現までの、最大待ちフレーム数
     * @return
     */
    virtual void addFormation(GgafCore::Formation* prm_pFormationActor, frame prm_max_delay_offset = 0);

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

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual ~RotateFormationScene();
};

}
#endif /*GGAF_LIB_ROTATEFORMATIONSCENE_H_*/
