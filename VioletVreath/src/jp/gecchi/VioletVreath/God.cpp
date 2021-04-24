#include "God.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

VirtualButton* God::pVbtn_PLAY_ = nullptr;
VirtualButton* God::pVbtn_UI_ = nullptr;
VirtualButton* God::pVbtn_active_ = nullptr;
VirtualButton* God::pVbtn_active_next_frame_ = nullptr;
bool God::g_should_reboot_ = false;

God::God() :
      DefaultGod() {

    pDepoManager_ = NEW DepositoryManager("DepositoryManager");
    pXpmManager_ = NEW XpmManager("XpmManager");
    God::pVbtn_PLAY_ = NEW VirtualButton(FILE_INPUT_PLAY_REPLAY);
    God::pVbtn_UI_   = NEW VirtualButton(FILE_INPUT_UI_REPLAY);
#ifdef MY_DEBUG
    pVbtn_PLAY_->_pRpy->setRealtimeOutputFile(FILE_REALTIME_OUTPUT_PLAY_REPLAY);
    pVbtn_UI_->_pRpy->setRealtimeOutputFile(FILE_REALTIME_OUTPUT_UI_REPLAY);
    _TRACE_("デバッグリアルタイムリプレイ記録モード○");
#endif
    God::pVbtn_active_ = God::pVbtn_UI_;
    God::pVbtn_active_next_frame_ = God::pVbtn_UI_;

    if (pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("プレイリプレイ情報○、UIリプレイ情報○");
        _TRACE_("→リプレイ再生モードです。");
    } else if (!pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("プレイリプレイ情報×、UIリプレイ情報○");
        _TRACE_("→UIのみ再生モードです。っていうか意味あるのん？");
    } else if (pVbtn_PLAY_->_is_replaying && !pVbtn_UI_->_is_replaying) {
        _TRACE_("プレイリプレイ情報○、UIリプレイ情報×");
        _TRACE_("→リプレイ再生モードです。但し、プレイリプレイから PAUSE情報を切り取ります。");
        //プレイリプレイあり、かつUIリプレイ無しの場合のみ、プレイリプレイのPAUSE情報を除去する
        VBReplayRecorder* pRepPlay = pVbtn_PLAY_->_pRpy;
        VBReplayRecorder::VBRecordNote* pRecNote = pRepPlay->_pFirstVBNote;
        vb_sta vb_pause_not_mask = ~((vb_sta)VB_PAUSE);
        while (pRecNote) {
            pRecNote->_state = (pRecNote->_state & vb_pause_not_mask);
            pRecNote = pRecNote->_pNext;
        }
    } else {
        _TRACE_("プレイリプレイ情報×、UIリプレイ情報×");
        _TRACE_("リプレイ登録モードです。");
    }

    //ランキング情報読み込み
    G_RANKING_TABLE.init();
    initVB();
}

HRESULT God::initDevice() {
    MyStgUtil::init();  //ユーティリティ準備
    return DefaultGod::initDevice();
}

void God::initVB() {
    //仮想ボタンを本ゲーム用に上書きして再定義
    God::pVbtn_PLAY_->remap(VB_BUTTON1   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT1      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT1      ]);
    God::pVbtn_PLAY_->remap(VB_BUTTON2   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT2      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT2      ]);
    God::pVbtn_PLAY_->remap(VB_BUTTON3   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_OPTION     ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_OPTION     ]);
    God::pVbtn_PLAY_->remap(VB_BUTTON4   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW       ]);
    God::pVbtn_PLAY_->remap(VB_BUTTON5   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_TURBO      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_TURBO      ]);
    God::pVbtn_PLAY_->remap(VB_BUTTON6   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_POWERUP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_POWERUP    ]);
    God::pVbtn_PLAY_->remap(VB_BUTTON7   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON7    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON7    ]);
    God::pVbtn_PLAY_->remap(VB_BUTTON8   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON8    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON8    ]);
    God::pVbtn_PLAY_->remap(VB_PAUSE     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_PAUSE      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_PAUSE      ]);
    God::pVbtn_PLAY_->remap(VB_UP        , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UP         ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UP         ]);
    God::pVbtn_PLAY_->remap(VB_DOWN      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_DOWN       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_DOWN       ]);
    God::pVbtn_PLAY_->remap(VB_LEFT      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_LEFT       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_LEFT       ]);
    God::pVbtn_PLAY_->remap(VB_RIGHT     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_RIGHT      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_RIGHT      ]);
    God::pVbtn_PLAY_->remap(VB_S1_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_UP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_UP    ]);
    God::pVbtn_PLAY_->remap(VB_S1_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_DOWN  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_DOWN  ]);
    God::pVbtn_PLAY_->remap(VB_S1_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_LEFT  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_LEFT  ]);
    God::pVbtn_PLAY_->remap(VB_S1_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_RIGHT ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_RIGHT ]);
    God::pVbtn_PLAY_->remap(VB_UI_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_UP      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_UP      ]);
    God::pVbtn_PLAY_->remap(VB_UI_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DOWN    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_DOWN    ]);
    God::pVbtn_PLAY_->remap(VB_UI_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_LEFT    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_LEFT    ]);
    God::pVbtn_PLAY_->remap(VB_UI_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_RIGHT   ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_RIGHT   ]);
    God::pVbtn_PLAY_->remap(VB_UI_EXECUTE, VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_EXECUTE ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_EXECUTE ]);
    God::pVbtn_PLAY_->remap(VB_UI_CANCEL , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_CANCEL  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_CANCEL  ]);
    God::pVbtn_PLAY_->remapK(VB_UI_DEBUG  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DEBUG   ]  );

    God::pVbtn_UI_->remap(VB_BUTTON1   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT1      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT1      ]);
    God::pVbtn_UI_->remap(VB_BUTTON2   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT2      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT2      ]);
    God::pVbtn_UI_->remap(VB_BUTTON3   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_OPTION     ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_OPTION     ]);
    God::pVbtn_UI_->remap(VB_BUTTON4   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW       ]);
    God::pVbtn_UI_->remap(VB_BUTTON5   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_TURBO      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_TURBO      ]);
    God::pVbtn_UI_->remap(VB_BUTTON6   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_POWERUP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_POWERUP    ]);
    God::pVbtn_UI_->remap(VB_BUTTON7   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON7    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON7    ]);
    God::pVbtn_UI_->remap(VB_BUTTON8   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON8    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON8    ]);
    God::pVbtn_UI_->remap(VB_PAUSE     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_PAUSE      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_PAUSE      ]);
    God::pVbtn_UI_->remap(VB_UP        , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UP         ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UP         ]);
    God::pVbtn_UI_->remap(VB_DOWN      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_DOWN       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_DOWN       ]);
    God::pVbtn_UI_->remap(VB_LEFT      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_LEFT       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_LEFT       ]);
    God::pVbtn_UI_->remap(VB_RIGHT     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_RIGHT      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_RIGHT      ]);
    God::pVbtn_UI_->remap(VB_S1_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_UP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_UP    ]);
    God::pVbtn_UI_->remap(VB_S1_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_DOWN  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_DOWN  ]);
    God::pVbtn_UI_->remap(VB_S1_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_LEFT  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_LEFT  ]);
    God::pVbtn_UI_->remap(VB_S1_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_RIGHT ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_RIGHT ]);
    God::pVbtn_UI_->remap(VB_UI_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_UP      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_UP      ]);
    God::pVbtn_UI_->remap(VB_UI_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DOWN    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_DOWN    ]);
    God::pVbtn_UI_->remap(VB_UI_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_LEFT    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_LEFT    ]);
    God::pVbtn_UI_->remap(VB_UI_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_RIGHT   ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_RIGHT   ]);
    God::pVbtn_UI_->remap(VB_UI_EXECUTE, VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_EXECUTE ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_EXECUTE ]);
    God::pVbtn_UI_->remap(VB_UI_CANCEL , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_CANCEL  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_CANCEL  ]);
    God::pVbtn_UI_->remapK(VB_UI_DEBUG  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DEBUG   ] );

}

GgafCore::Spacetime* God::createSpacetime() {
    Camera* pCamera = NEW Camera("CAMERA");
    Spacetime* pSpacetime = NEW Spacetime("MYSPACETIME", pCamera);
    return (GgafCore::Spacetime*)pSpacetime;
}

void God::clean() {
    if (!_was_cleaned) {
        if (VB_PLAY->_is_replaying) {
#ifdef MY_DEBUG
            VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_REPADD.rep");
#endif
        } else {
            VB_PLAY->_pRpy->outputFile(FILE_OUTPUT_PLAY_REPLAY);
        }
        if (VB_UI->_is_replaying) {
#ifdef MY_DEBUG
            VB_PLAY->_pRpy->outputFile("VB_UI_LAST_REPADD.rep");
#endif
        } else {
            VB_UI->_pRpy->outputFile(FILE_OUTPUT_UI_REPLAY);
        }
        _TRACE_(FUNC_NAME<<" begin");
        DefaultGod::clean();
        GGAF_DELETE(pVbtn_PLAY_);
        GGAF_DELETE(pVbtn_UI_);
        GGAF_DELETE(pDepoManager_);
        GGAF_DELETE(pXpmManager_);
        _TRACE_(FUNC_NAME<<" end");
    }
}

void God::reboot() {
    God::g_should_reboot_ = true; //再起動フラグセット
    ::PostQuitMessage(0); //終了！
}

void God::oops() {
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Oops.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Oops.rep");
    DefaultGod::oops(); //上位の「しまった！」へ
}

EffectManager* God::createEffectManager() {
    EffectManager* p = NEW EffectManager("EffectManager");
    return p;
}
CurveSourceManagerEx* God::createCurveSourceManager() {
    CurveSourceManagerEx* p = NEW CurveSourceManagerEx("CurveSourceManagerEx");
    return p;
}
CurveManufactureManagerEx* God::createCurveManufactureManager() {
    CurveManufactureManagerEx* p = NEW CurveManufactureManagerEx("CurveManufactureManagerEx");
    return p;
}

God::~God() {
    if (getSpacetime()) {
        World* pWorld = getSpacetime()->getWorld();
        if (pWorld) {
            pWorld->throwEventLowerTree(EVENT_GOD_WILL_DEMISE); //全シーンに通知
        }
    }
    clean();
    _was_cleaned = true;
}

