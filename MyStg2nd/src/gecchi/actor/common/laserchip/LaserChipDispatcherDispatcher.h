#ifndef LASERCHIPDISPATCHERDISPATCHER_H_
#define LASERCHIPDISPATCHERDISPATCHER_H_
namespace MyStg2nd {

/**
 * （現在未使用。普通のDispatcher でできたし）
 * レーザーチップディパッチャー使いまわし管理クラス .
 * new した後 addSubLast メソッドで LaserChipインスタンスを好きな個数登録してください。<BR>
 * new から initialize()まで、又は随時変更が有効なパラメータ<BR>
 */
class LaserChipDispatcherDispatcher : public GgafCore::GgafActorDispatcher {
    friend class LaserChip;
public:
    LaserChipDispatcherDispatcher(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * レーザーチップディパッチャーの借り入れを試みる .
     * ストック切れの場合は NULL が返る。必ずチェックすること。
     * 使い終われば sayonara() か、inactivate() を実行してください。自動的にストックに戻ります。
     * @return 借り入れしたレーザーチップディパッチャー。借り入れできない場合はNULL
     */
    virtual LaserChipDispatcher* employ() override;

    /**
     * レーザーチップディパッチャーストックの追加 .
     * 好きなだけ追加して下さい。
     * 追加すればするほど玉切れがおきにくい
     * @param prm_pDispatcher_LaserChip レーザーチップディパッチャー
     */
    void addSubLast(LaserChipDispatcher* prm_pDispatcher_LaserChip);

     virtual ~LaserChipDispatcherDispatcher();

};

}
#endif /*LASERCHIPDISPATCHERDISPATCHER_H_*/
