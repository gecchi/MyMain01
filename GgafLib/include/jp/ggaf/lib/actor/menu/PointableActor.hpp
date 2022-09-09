#ifndef GGAF_LIB_POINTABLEACTOR_H_
#define GGAF_LIB_POINTABLEACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/core/util/LinkedListRing.hpp"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"
#include "jp/ggaf/lib/actor/menu/PointableActor.hpp"
#include "jp/ggaf/lib/actor/FontBoardActor.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"


namespace GgafLib {

/**
 * マウスでポイント可能なアクター .
 * @tparam T 母体のメニュー板となるアクターの型
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class PointableActor : public T {

protected:
    /**
     * コンストラクタ .
     * 【注意】生成直後非活動状態をデフォルトとしています。<BR>
     * 具体的には T::inactivateImmed(); をコールしています。
     * @param prm_name
     * @param prm_model モデル識別名
     */
    PointableActor(const char* prm_name, const char* prm_model);


    /**
     * 状態フラグ更新を追加のためオーバーライド .
     * 内部で T::nextFrame(); もコールしています。
     */
    virtual void nextFrame() override;


    /**
     * メニューの振る舞い .
     * カーソルの移動及び、メニューアイテムとカーソルをメニューの母体座標に追従させる
     * 処理が実装済みです。<BR>
     * メニューの振る舞いを追加する場合は、オーバーライドして、
     * 処理中に上位 processBehavior() を呼び出すのを忘れないように。<BR>
     */
    virtual void processBehavior() override;

    virtual ~PointableActor();
};


template<class T>
PointableActor<T>::PointableActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model) {
    T::_class_name = "PointableActor";
}

template<class T>
void PointableActor<T>::nextFrame() {
    T::nextFrame();
}

template<class T>
void PointableActor<T>::processBehavior() {

}


template<class T>
PointableActor<T>::~PointableActor() {
}

}
#endif /*GGAF_LIB_MENUACTOR_H_*/
