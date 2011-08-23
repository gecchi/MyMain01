#ifndef LASERCHIPDEPOSITORYSTORE_H_
#define LASERCHIPDEPOSITORYSTORE_H_
namespace GgafDx9LibStg {

/**
 * （現在未使用。普通のDepository でできたし。使用する場合は onReset() 等を実装する必要あり）
 * レーザーチップデポジトリのデポジトリ。
 * つまりレーザーチップディスパッチャ使いまわし管理クラス 。
 * new した後 addSubLast メソッドで LaserChipインスタンスを好きな個数登録してください。<BR>
 * new から initialize()まで、又は随時変更が有効なパラメータ<BR>
 */
class LaserChipDepositoryStore : public GgafCore::GgafActorDepository {
    friend class LaserChip;
public:
    LaserChipDepositoryStore(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * レーザーチップディパッチャーの借り入れを試みる .
     * ストック切れの場合は NULL が返る。必ずチェックすること。
     * 使い終われば sayonara() か、inactivate() を実行してください。自動的にストックに戻ります。
     * @return 借り入れしたレーザーチップディパッチャー。借り入れできない場合はNULL
     */
    virtual LaserChipDepository* dispatch() override;

    /**
     * レーザーチップディパッチャーストックの追加 .
     * 好きなだけ追加して下さい。
     * 追加すればするほど玉切れがおきにくい
     * @param prm_pDepo_LaserChip レーザーチップディパッチャー
     */
    void addSubLast(LaserChipDepository* prm_pDepo_LaserChip);

     virtual ~LaserChipDepositoryStore();

};

}
#endif /*LASERCHIPDEPOSITORYSTORE_H_*/
