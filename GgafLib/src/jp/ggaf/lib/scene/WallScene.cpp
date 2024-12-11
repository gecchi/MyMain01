#include "jp/ggaf/lib/scene/WallScene.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/scene/WallSectionScene.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

using namespace GgafLib;

WallScene::WallScene(const char* prm_name, GgafCore::SceneChief* prm_pSceneChief) : DefaultScene(prm_name, prm_pSceneChief) {
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
        GgafCore::ActorDepository* prm_pDepo_wall) {
    _TRACE_(FUNC_NAME<<" ["<<getName()<<"] build...");
    setFeatureFunction(WallScene::scrollX); //X軸方向スクロール関数

    _pDepo_wall = prm_pDepo_wall;
    if (_pDepo_wall->getSceneChief()) {
        //既に所属しているならばOK
    } else {
        getSceneChief()->appendChild(_pDepo_wall); //仮所属 initialize() で本所属
    }
    for (int i = 0; i < prm_section_num; i++) {
        appendChild(prm_papSection[i]); //配下シーンに所属
        prm_papSection[i]->config(_pDepo_wall,
                                  prm_wall_start_x,
                                  prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivate();
        _ringHoldSection.addLast(prm_papSection[i], false);
    }
    _ringHoldSection.createIndex();
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
            int len = pSection->_paWallNum[pSection->_area_len-1];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_Fを潰す 0b111110
            }
        }
        //中間、最後、各セクションの最前ブロック面の全BOXのFACE_B描画を潰す
        for (int i = 1; i < prm_section_num; i++) {
            WallSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallNum[0];
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
        throwCriticalException("WallScene["<<getName()<<"] オブジェクトが未完成です。buildWallScene()を実行し構築してください。");
    }
    //buildWallScene が継承クラスのコンストラクタで実行された場合、getSceneChief() は世界シーンを返すため
    //壁デポジトリの所属シーンは世界シーン所属になっている可能性がある。、
    //スクロール制御を行うためにも、壁デポジトリ は this の配下に置く必要があるため、以下の様に
    //配下シーンに再設定する。
    getSceneChief()->appendChild(_pDepo_wall->extract());
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
                pSection->inactivateDelay(360);
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

void WallScene::scrollX(GgafCore::Object* pThat, void* p1, void* p2, void* p3) {
    if (pThat->instanceOf(Obj_GgafDx_GeometricActor)) {
        GgafDx::GeometricActor* pActor = (GgafDx::GeometricActor*)pThat;
//        //ここだめ_was_paused_flg
//        if (pActor->getSceneChief()->getPlatformScene()->_was_paused_flg == false) {
//            pActor->_x -= (*((coord*)p1));
//        }
        pActor->_x -= (*((coord*)p1));
    }
}

WallScene::~WallScene() {
}
