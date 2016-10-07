#include "jp/ggaf/lib/scene/WallSectionScene.h"

#include <fstream>
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/scene/WallScene.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WallSectionScene::WallSectionScene(const char* prm_name, const char* prm_data_filename,  WallScene* prm_pWallScene) : DefaultScene(prm_name) {
//ruby tool/script/make_stage_data.rb > scene/stage_data.txt

    _TRACE_(FUNC_NAME<<" "<<prm_data_filename<<" begin");
    _class_name = "WallSectionScene";
    _pActor_infront_alpha_target = nullptr;
    _pWallScene = prm_pWallScene;
    _area_len = 0;
    _area_height = 0;
    _area_width= 0;
    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    _loop_num = 1;
    _cnt_loop = 0;
    _frame_of_launch_next = 0;
    _cnt_area_len = 0;
    _is_loop_end = false;
    std::string data_filename = PROPERTY::DIR_WALL + std::string(prm_data_filename);
    std::ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException(prm_data_filename<<" が開けません");
    }
    ifs >> _loop_num;

    ifs >> _area_len >>
           _area_height >>
           _area_width;
    if (ifs.fail()) {
        throwGgafCriticalException(prm_data_filename<<" フォーマットエラーその１");
    }
    int r_data;
    _paWallInfoLen = NEW int[_area_len];
    for (int i = 0; i < _area_len; i++) {
        ifs >> r_data;
        _paWallInfoLen[i] = r_data;
        if (ifs.fail()) {
            throwGgafCriticalException(prm_data_filename<<" フォーマットエラーその２ i="<<i<<" _area_len="<<_area_len);
        }
    }

    _papaWallInfo = NEW WallInfo*[_area_len];
    for (int i = 0; i < _area_len; i++) {
        _TRACE_("WallSectionScene read..."<<i);
        _papaWallInfo[i] = NEW WallInfo[_paWallInfoLen[i]];
        for (int j = 0; j < _paWallInfoLen[i]; j++) {
            ifs >> _papaWallInfo[i][j]._pos_info >>
                   _papaWallInfo[i][j]._y >>
                   _papaWallInfo[i][j]._z >>
                   _papaWallInfo[i][j]._wall_draw_face >>
                   _papaWallInfo[i][j]._aColliBoxStretch[0] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[1] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[2] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[3] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[4] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[5];
            if (ifs.fail()) {
                throwGgafCriticalException(prm_data_filename<<" フォーマットエラーその３ i="<<i<<"/j="<<j<<"/_area_len="<<_area_len<<"/_paWallInfoLen[i]="<<_paWallInfoLen[i]);
            }
        }
    }
    ifs.close();
    _pWallLast = nullptr;;
    _wall_start_x = 0;
    _pDepo_wall = nullptr;
    _TRACE_(FUNC_NAME<<" "<<prm_data_filename<<" done");
}

void WallSectionScene::config(
        GgafActorDepository* prm_pDepo_wall,
        coord prm_wall_start_x,
        coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height) {
    _pDepo_wall = prm_pDepo_wall;
    _wall_dep = prm_wall_dep;
    _wall_width = prm_wall_width;
    _wall_height = prm_wall_height;
    _wall_start_x = prm_wall_start_x + (_wall_dep/2);
}

void WallSectionScene::initialize() {
    if (_pDepo_wall == nullptr) {
        throwGgafCriticalException("GgafActorDepository* _pDepo_wall をセットして下さい。");
    }
}

void WallSectionScene::onActive() {
    _frame_of_launch_next = (frame)(_wall_dep /_pWallScene->getScrollSpeed());
    _cnt_area_len = 0;
    _cnt_loop = 0;
    _is_loop_end = false;
}

void WallSectionScene::processBehavior() {
    const velo parent_scroll_speed =_pWallScene->getScrollSpeed();
    if (!_is_loop_end && parent_scroll_speed != 0) {

        if (_pWallLast == nullptr || (_wall_start_x - _pWallLast->_x) >= _wall_dep) {
            //_pWallLast は、本セクションシーン内での最終表示壁AABB。
            //初めての時はnullptr

            if (_cnt_area_len >= _area_len && _cnt_loop+1 >= _loop_num) {
                //終了
                _is_loop_end = true;
                return;
            } else {
                if (_cnt_area_len >= _area_len) {
                    _cnt_area_len = 0;
                    _cnt_loop++;
                }
            }
            MassWallActor* pWall = nullptr;
            const int len = _paWallInfoLen[_cnt_area_len];
            const int harf_area_height = _area_height/2;
            const int harf_area_width = _area_width/2;
            for (int n = 0; n < len; n++) {
                WallInfo* const pWallInfo = &(_papaWallInfo[_cnt_area_len][n]);
                pWall = (MassWallActor*)_pDepo_wall->dispatchForce();
                //pWallInfo->_pos_info == 0 ならばBOX
                if (pWall->isActiveInTheTree()) {
                    //無理やり横取りした
                    pWall->inactivateImmed();
                    pWall->onInactive();
                }

                pWall->config(this, pWallInfo->_pos_info,
                                         pWallInfo->_wall_draw_face,
                                         pWallInfo->_aColliBoxStretch);
                pWall->setPosition( _pWallLast==nullptr ? _wall_start_x : _pWallLast->_x + _wall_dep,
                                    (-harf_area_height + pWallInfo->_y) * _wall_height,
                                    (-harf_area_width  + pWallInfo->_z) * _wall_width   );
                pWall->activateImmed();
                pWall->onActive();
                pWall->_frame_of_behaving_since_onActive = 1; //リセット
            }
            _pWallLast = pWall;
            _frame_of_launch_next = (frame)(_wall_dep / parent_scroll_speed);

            onBlockLaunch(_cnt_loop, _cnt_area_len, _pWallLast==nullptr ? _wall_start_x : _pWallLast->_x + _wall_dep); //コールバック
            _cnt_area_len++;

        }
    } else {
        //終了
    }
}

MassWallActor* WallSectionScene::getLastWallParts() const {
    return _pWallLast;
}

WallSectionScene::~WallSectionScene() {
    for (int i = 0; i < _area_len; i++) {
        GGAF_DELETEARR(_papaWallInfo[i]);
    }
    GGAF_DELETEARR(_papaWallInfo);
    GGAF_DELETEARR(_paWallInfoLen);
}
