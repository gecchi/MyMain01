#ifndef IFORMATIONABLE_H_
#define IFORMATIONABLE_H_

namespace GgafLib {
/**
 * フォーメーションアクターインターフェイス .
 * FormationActor が管理するフォーメーション要素のアクターは、
 * 本クラスを継承剃る必要があります。
 * 詳細は FormationActor の解説参照へ。
 * @version 1.00
 * @since 2011/10/02
 * @author Masatoshi Tsuge
 */
class IFormationAble {
public:
    /** 現在自身が管理下におかれている、フォーメーション */
    GgafLib::FormationActor* _pFormation;

    /**
     * コンストラクタ .
     * フォーメーション処理を行ないたいアクターは、
     * 次のように感じで多重継承してください。
     * <pre><code>
     * ＜例＞
     *
     * class SampleActor :
     *   public GgafLib::DefaultMeshSetActor, public GgafLib::IFormationAble {
     *
     *     SampleActor(const char* prm_name);
     * }
     *
     * SampleActor::SampleActor(const char* prm_name) :
     *   DefaultMeshSetActor(prm_name, "SampleActor", STATUS(SampleActor)), IFormationAble() {
     *
     *     _class_name = "EnemyEunomia";
     * }
     * </pre></code>
     */
    IFormationAble();

    /**
     * 自身が破壊された場合に通知するメソッド .
     * フォーメーション（編隊）の編隊全滅ボーナスなどの全滅判定を行うために、<BR>
     * 自身が編隊全滅に有効な消滅（画面外等では無く、破壊されたとかボム等）のタイミングで、<BR>
     * 本メソッドを実行し、破壊による消滅を通知して下さい。<BR>
     * 通知を行うことにより、管理されている FormationActor オブジェクトから、編隊全滅時に、
     *
     * FormationActor::onDestroyedFormation()
     *
     * のコールバックが行われます。
     * 編隊ボーナス、アイテム出現等は FormationActor::onDestroyedFormation() 実装で行って下さい。
     * <pre><code>
     * ＜例＞
     * void SampleActor::onHit(GgafActor* prm_pOtherActor) {
     *    //自身の耐久力チェック
     *    if (MyStgUtil::calcSampleStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
     *        //Hitの相手のチェック
     *        if (pOther->getKind() & KIND_MY) {
     *            //Hitの相手は自機関連（自機、自機ユニット、自機発射弾)
     *            informDestroyedFollower(); //編隊全滅判定に有効な破壊を通知する
     *        }
     *    }
     * }
     * </pre></code>
     */
    void informDestroyedFollower();

    virtual ~IFormationAble();
};

}
#endif /*IFORMATIONABLE_H_*/
