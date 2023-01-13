#ifndef GGAF_CORE_DEPOSITORYFORMATION_H_
#define GGAF_CORE_DEPOSITORYFORMATION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/Formation.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"

namespace GgafCore {

/**
 * デポジトリ管理のフォーメーション管理ークラス .
 * 編隊メンバーは使い回すフォーメーション。
 * 使用する場合は、本クラスを継承し、
 * setFormationMember(ActorDepository*) により
 * 編隊メンバー所属のデポジトリオブジェクトを登録してください。
 * また、登録のアクターが破壊された場合は、編隊全滅判定のために
 * Actor::notifyDestroyedToFormation(); をコールしてください。
 * processFinal() を実装済みですので、オーバーライドする場合は注意して下さい。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class DepositoryFormation : public Formation {

public:
    /** [r]編隊要素として管理されているアクターのリスト */
    RingLinkedList<Actor> _listFollower;
    bool _can_called_up;
    /** [r]構成メンバーのストッカー（nullptrの場合構成メンバーは配下アクターのはず） */
    ActorDepository* _pDepo;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end フォーメーション終了時の猶予フレーム
     * @return
     */
    DepositoryFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * 編隊構成メンバーがストックされたデポジトリを設定する .
     * メンバーを活動させるには、専用メソッド calledUpMember() を使用する。
     * メンバーを活動終了時は、sayonara() を使用。
     * @param prm_pDepo
     */
    void setFormationMember(ActorDepository* prm_pDepo);

    /**
     * 編隊メンバーが全て非活動ならば、本フォーメーションオブジェクト解放 .
     * 構成メンバーが全て sayonara() で、デポジトリに戻った場合、
     * 本フォーメーションオブジェクトが自動解放されるようにするための仕組みを実装。
     * 下位で processFinal() の処理が必要な場合は、
     * オーバーライドして、その処理中での何処かで
     * <code>
     * TreeFormation::processFinal();
     * </code>
     * を呼び出してください、
     */
    virtual void processFinal() override;

    /**
     * デポジトリからアクターを本フォーメーションメンバーとして設定し取得する（招集する） .
     * setFormationMembersitory() の事前実行が必要。<BR>
     * 本メソッドを呼び出すと、デポジトリに管理されたメンバーが一つ dispatch() されます。(同時に activate() もされる)
     * デポジトリのメンバーがすべて活動中で、枯渇している場合 nullptr が返ります。<BR>
     * また、引数の prm_formation_child_num は最大編隊構成要員数で、この数以上の呼び出しでも nullptr が返ります。<BR>
     * 一度でも nullptr が返されると、内部フラグ _can_called_up が false になり、以降本フォーメーションオブジェクトは
     * メンバー呼び出しできないようになります。と同時に(_can_called_up==falseを受けて)processFinal() 内では、
     * 全ての編隊メンバーが非活動時、本フォーメーションオブジェクトが自動的に sayonara(_offset_frames_end) が実行されるようになります。<BR>
     * 【ハマったメモ１】初っ端に calledUpMember 呼び出しで、デポジトリストック枯渇により、いきなりnullptrが返った場合も、
     * _can_called_up = false になります。よって、本フォーメーションオブジェクトは、いきなり sayonara(_offset_frames_end) が実行され終了する。
     * という動作になります。構成メンバーが確保できなかった場合も考慮して下さい。<BR>
     * 【ハマったメモ２】calledUpMember() して取得したメンバーは sayonara() (内部的にはinactive()) することにより、編隊から離脱したことになります。
     * 従って、calledUpMember() したメンバーを、inactive() して、内部一時保有し確保することは、その瞬間に編隊から離脱したこと同意になりますので、
     * できません。そのようにしたい場合は TreeFormation を使うしかありません。<BR>
     * @param prm_formation_child_num 本フォーメーションの管理される要員数（＝編隊全滅数）。省略時は配下メンバー数となる。
     * @return 編隊構成要員のアクター。
     *         最大編隊構成要員数をオーバーして呼び出した場合、或いは
     *         デポジトリに構成要員がもういない場合は nullptr
     */
    Actor* calledUpMember(int prm_formation_child_num = INT_MAX);

    /**
     * まだ、編隊隊員確保が不十分で、calledUpMember() をする余地があるかどうか。 .
     * @return true：余地あり／false：余地なし
     */
    bool canCalledUp() const;

    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * DepositoryFormation::onEnd() を呼び出して下さい。
     */
    virtual void onEnd() override;

    /**
     * デポジトリモード管理の編隊全てに sayonara() を実行する。
     */
    virtual void sayonaraFollwer();

    /**
     * 編隊に所属したアクターが全てさよなら(sayonara()が呼び出された)した場合コールバックされるメソッド .
     * 必要に応じて下位でオーバーライドし実装して下さい。
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~DepositoryFormation();
};

}
#endif /*GGAF_CORE_DEPOSITORYFORMATION_H_*/
