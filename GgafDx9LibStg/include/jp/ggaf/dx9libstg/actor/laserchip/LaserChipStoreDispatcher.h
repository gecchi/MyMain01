#ifndef LASERCHIPSTOREDISPATCHER_H_
#define LASERCHIPSTOREDISPATCHER_H_
namespace GgafDx9LibStg {

/**
 * （現在未使用。普通のStore でできたし。使用する場合は onReset() 等を実装する必要あり）
 * レーザーチップディスパッチャーのディスパッチャー。
 * つまりレーザーチップディスパッチャ使いまわし管理クラス 。
 * new した後 addSubLast メソッドで LaserChipインスタンスを好きな個数登録してください。<BR>
 * new から initialize()まで、又は随時変更が有効なパラメータ<BR>
 */
class LaserChipStoreDispatcher : public GgafCore::GgafActorStore {
    friend class LaserChip;
public:
    LaserChipStoreDispatcher(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * レーザーチップディパッチャーの借り入れを試みる .
     * ストック切れの場合は NULL が返る。必ずチェックすること。
     * 使い終われば sayonara() か、inactivate() を実行してください。自動的にストックに戻ります。
     * @return 借り入れしたレーザーチップディパッチャー。借り入れできない場合はNULL
     */
    virtual LaserChipStore* dispatch() override;

    /**
     * レーザーチップディパッチャーストックの追加 .
     * 好きなだけ追加して下さい。
     * 追加すればするほど玉切れがおきにくい
     * @param prm_pStore_LaserChip レーザーチップディパッチャー
     */
    void addSubLast(LaserChipStore* prm_pStore_LaserChip);

     virtual ~LaserChipStoreDispatcher();

};

}
#endif /*LASERCHIPSTOREDISPATCHER_H_*/
