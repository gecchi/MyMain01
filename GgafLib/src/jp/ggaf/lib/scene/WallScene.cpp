#include "jp/ggaf/lib/scene/WallScene.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallScene::WallScene(const char* prm_name) : DefaultScene(prm_name) {
    _obj_class |= Obj_WallScene;
    _class_name = "WallScene";
    _pDepo_wall = nullptr;
    _pLastSectionScene = nullptr;
    _is_all_active_section_scenes = false;
    _is_finished = false;
}

void WallScene::buildWallScene(
        coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height,
        coord prm_wall_start_x,
        WallSectionScene** prm_papSection, int prm_section_num,
        GgafActorDepository* prm_pDepo_wall) {
    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] build...");
    setScrollingFunction(WallScene::scrollX); //X軸方向スクロール関数

    _pDepo_wall = prm_pDepo_wall;
    if (_pDepo_wall->getMySceneMediator()) {
        //既に所属しているならばOK
    } else {
        bringSceneMediator()->addSubGroup(_pDepo_wall); //仮所属 initialize() で本所属
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]); //配下シーンに所属
        prm_papSection[i]->config(_pDepo_wall,
                                  prm_wall_start_x,
                                  prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivate();
        _ringHoldSection.addLast(prm_papSection[i], false);
    }
    // 0b 00abcdef
    //
    //    c
    // a b d f
    //      e
    //
    //    FACE_A_BIT = 0b100000
    //    FACE_B_BIT = 0b010000
    //    FACE_C_BIT = 0b001000
    //    FACE_D_BIT = 0b000100
    //    FACE_E_BIT = 0b000010
    //    FACE_F_BIT = 0b000001
    //    A          = 0b111110 = 62
    //    A          = 0b101111 = 47

    //セクションつなぎ目のBOX描画の処理
    if (prm_section_num >= 2) {
        //最初、中間、各セクションの最末尾ブロック面の全BOXのFACE_F描画を潰す
        for (int i = 0; i < prm_section_num-1; i++) {
            WallSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallInfoLen[pSection->_area_len-1];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_Fを潰す 0b111110
            }
        }
        //中間、最後、各セクションの最前ブロック面の全BOXのFACE_B描画を潰す
        for (int i = 1; i < prm_section_num; i++) {
            WallSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallInfoLen[0];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[0][j]._wall_draw_face &= 47; //FACE_Bを潰す 0b111110
            }
        }
    }
    _ringHoldSection.first();
    _is_all_active_section_scenes = false;
    _pLastSectionScene = prm_papSection[prm_section_num-1];
    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] done");
}

void WallScene::initialize() {
    if (_pDepo_wall == nullptr) {
        throwGgafCriticalException("WallScene["<<getName()<<"] オブジェクトが未完成です。buildWallScene()を実行し構築してください。");
    }
    //buildWallScene が継承クラスのコンストラクタで実行された場合、bringSceneMediator() は世界シーンを返すため
    //壁デポジトリの所属シーンは世界シーン所属になっている可能性がある。、
    //スクロール制御を行うためにも、壁デポジトリ は this の配下に置く必要があるため、以下の様に
    //配下シーンに再設定する。
    bringSceneMediator()->addSubGroup(_pDepo_wall->extract());
}

void WallScene::onActive() {
    WallSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
    pCurrentSection->activate();
}

void WallScene::processBehavior() {

    if (!_is_finished) {
        if (!_is_all_active_section_scenes) {

            const WallSectionScene* const pCurrentSection = _ringHoldSection.getCurrent();
            if (!pCurrentSection->isLast()) {
                if (pCurrentSection->_is_loop_end) {
                    WallSectionScene* const pNewSection = _ringHoldSection.next();
                    pNewSection->activate();
                    pNewSection->_pWallLast = pCurrentSection->getLastWallParts();
                    _ringLoopEndSection.addLast(pCurrentSection, false);
                }
            } else {
                if (pCurrentSection->_is_loop_end) {
                    _ringLoopEndSection.addLast(pCurrentSection, false);
                    _is_all_active_section_scenes = true;
                }
            }
        }

        //_ringLoopEndSectionチェック
        //MassWallActor::_pWallSectionScene が不正ポインタにならないための考慮である。
        for (int i = 0; i < _ringLoopEndSection.length(); i++) { //_ringLoopEndSection.length()をローカル変数に置き換えてはいけません
            WallSectionScene* const pSection =_ringLoopEndSection.next();
            const MassWallActor* const pWallLast = pSection->_pWallLast;
            if (pWallLast->_pWallSectionScene != pSection || !pWallLast->isActive() ) {
                //＜メモ＞
                //pSection->_pWallLast->_pWallSectionScene != pSection は、
                //pSection->_pWallLast つまり最終壁の紐付くセクションはが自分でない、
                //つまり、他のセクションシーンに dispatchForce() されたからOK、と考えた。
                //また、!pSection->_pWallLast->isActive() は
                //他のセクションシーンに dispatchForce() されずに、活動範囲外に消えたからOK、と考えた。
                _TRACE_(FUNC_NAME<<" ["<<getName()<<"] シーンのセクション["<<pSection->getName()<<"]inactivate!!");
                pSection->inactivateDelay(60*60);
                _ringLoopEndSection.remove();
                if (pSection == _pLastSectionScene) {
                    //最終セクションならば一度コールバックを行い、処理を任せる。
                    //（以前はここでsayonara()をしていた）
                    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] 最終セクションシーンだったためonFinishedAllSection() コールバック");
                    _is_finished = true;
                    onFinishedAllSection(); //コールバック
                }
            }
        }
    } else {
    }
}

void WallScene::processFinal() {
}

void WallScene::scrollX(GgafObject* pThat, void* p1, void* p2, void* p3) {
    if (pThat->instanceOf(Obj_GgafDxGeometricActor)) {
        GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
        if (!pActor->_was_paused_flg) {
            // _is_active_flg と、_can_live_flg は、GgafElement<T>::executeFuncLowerTree()でチェック済み
            pActor->_x -= (*((coord*)p1));
        }
    }
}

WallScene::~WallScene() {
}
