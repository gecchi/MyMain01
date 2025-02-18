#include "VvvWorld.h"

#include <Shlwapi.h>
#include <algorithm>
#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"
#include "jp/ggaf/dx/model/SkinAniMeshModel.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dx/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dx/util/XFile/Toolbox/IOModel_X.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"
#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultSkinAniMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultBoneAniMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultRegularPolygonSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
#include "VvvCaretaker.h"
#include "actor/CamWorker/VvvCamWorker.h"
#include "actor/VvvCursor.h"
#include "actor/VvvGrid.h"
#include "actor/VvvGrid2.h"
#include "actor/VvvCamera.h"
#include "actor/Font01.h"
#include "actor/VvvMousePointer.h"
#include "jp/ggaf/lib/util/Direction26Util.h"

using namespace GgafLib;
using namespace VVViewer;
using namespace std;

template<class T>
class VvvActor : public T {
public:
    GgafLib::DefaultBoardActor* pHitActor_;
    VvvWorld* pWorld_;
public:
    VvvActor(const char* prm_name, const char* prm_model)
        : T(prm_name, prm_model) {
        pHitActor_ = nullptr;
        pWorld_ =  (VvvWorld*)(pCARETAKER->getSpacetime()->pWorld_);
    }

    virtual void initialize() override {
        pHitActor_ = desireActor(GgafLib::DefaultBoardActor, "HitArea", "HitBoard");
        pHitActor_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        ViewCollisionChecker* pChecker = pHitActor_->getViewCollisionChecker();
        pChecker->addCollisionArea(1);
        pChecker->setColliAABox(0, 0.5);
        pHitActor_->setHitAble(true);
        pHitActor_->setCheckerKind(KIND_ACTOR);
        T::appendChild(pHitActor_);
    }

    virtual void processBehavior() override {
        pHitActor_->setPositionByWorldCoord(T::_x, T::_y, T::_z);
    }

    virtual ~VvvActor() {
    }
};


VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pCamWorker_ = NEW VvvCamWorker("VvvCamWorker", pCARETAKER->getSpacetime()->getCamera());
    getSceneChief()->appendChild(pCamWorker_);
    pCursor_ = NEW VvvCursor("Cursor");
    getSceneChief()->appendChild(pCursor_);
    pGrid_ = NEW VvvGrid("GRID");
    getSceneChief()->appendChild(pGrid_);
//    pGrid_ = NEW VvvGrid2("GRID2");
//    getSceneChief()->appendChild(pGrid_);
    vb_ = NEW VirtualButton();
    pFont01_info_ =  NEW Font01("Font01");
    getSceneChief()->appendChild(pFont01_info_);
    pFont01_help_ =  NEW Font01("Font01");
    getSceneChief()->appendChild(pFont01_help_);
    view_help_ = true;
    view_info_ = true;
    pVvvMousePointer_= nullptr;

    _w_r =  1.0 * CONFIG::GAME_BUFFER_WIDTH / CONFIG::RENDER_TARGET_BUFFER_WIDTH;
    _h_r =  1.0 * CONFIG::GAME_BUFFER_HEIGHT / CONFIG::RENDER_TARGET_BUFFER_HEIGHT;

//    _primary_buffer_source_left = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[SCREEN01].LEFT*_w_r;
//    _primary_buffer_source_top = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[SCREEN01].TOP*_h_r;
//    _primary_buffer_source_width = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[SCREEN01].WIDTH*_w_r;
//    _primary_buffer_source_height = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[SCREEN01].HEIGHT*_h_r;

    mapNumDik_[0] = DIK_0;
    mapNumDik_[1] = DIK_1;
    mapNumDik_[2] = DIK_2;
    mapNumDik_[3] = DIK_3;
    mapNumDik_[4] = DIK_4;
    mapNumDik_[5] = DIK_5;
    mapNumDik_[6] = DIK_6;
    mapNumDik_[7] = DIK_7;
    mapNumDik_[8] = DIK_8;
    mapNumDik_[9] = DIK_9;
}

void VvvWorld::initialize() {
    pVvvMousePointer_ = desireActor(VvvMousePointer);
//    pVvvMousePointer_->setCheckerKind(KIND_2DFIX_MOUSE_POINTER);
    pVvvMousePointer_->setCheckerKind(KIND_POINTER);
    getSceneChief()->appendChild(pVvvMousePointer_);

     pFont01_help_->setAlign(ALIGN_LEFT, VALIGN_TOP);
     pFont01_help_->setMaterialColor(1.0,0.5,0.2);
     pFont01_help_->update(PX_C(0), PX_C(0),
             "[F1]:Move to the initial position the camera.\n"
             "[F2]:Target to next model, and directed camera.\n"
             "[F3]:Target to next model.\n"
             "[F4]:Directed camera toward active model.\n"
             "[DELETE]:Remove active model.\n"
             "[CursorKey]:Move model up/right/down/left.\n"
             "[PgUp/PgDown]: Move model near/far. (Z axis)\n"
             "[ESC]:Move to (0, 0, 0).\n"
             "[R]+[UP/DOWN]:Rz (Z Axis) rotation model.\n"
             "[R]+[RIGHT/LEFT]:Ry (Y Axis) rotation model.\n"
             "[R]+[PgUp/PgDown]:Rx (X Axis) rotation model.\n"
             "[S]+[UP/DOWN]:Scale inc or dec.\n"
             "[S]+[X]+[UP/DOWN]:X Axial Scale inc or dec.\n"
             "[S]+[X]+[RIGHT/LEFT]:Y Axial Scale inc or dec.\n"
             "[S]+[X]+[PgUp/PgDown]:Z Axial Scale inc or dec.\n"
             "[W]:Toggle effect Wireframe on/off.\n"
             "[G]:Toggle display grid on/off.\n"
             "[O]:Toggle effect \"DestBlend = One/InvSrcAlpha\".\n"
             "[Z]:Toggle effect \"Zwriteenable = True/False\".\n"
             "[B]:Toggle effect Half-Lambert/Lambert.\n"
             "[N]:Toggle effect culling enable/disablet.\n"
             "[M]:Toggle effect \"ZBlendOp = Add/Maxe\".\n"
             "[A]+[CursorKey]:Effect AlphaBlend inc or dec.\n"
             "[P]+[RIGHT/LEFT]:Effect SpecularRange inc or dec.\n"
             "[P]+[UP/DOWN]:Effect SpecularPower inc or dec.\n"
             "[J/K/L]+[CursorKey]:Material red/green/blue Color inc or dec.\n"
             "[C]+[CursorKey]:Cube mapping reflectance inc or dec.\n"
             "[0]-[9]:Perfom animation set 0~9.\n"
             "[1]-[9]+[CursorKey]:Morph to taget number(1~9) model, weight inc or dec.\n"
             "...+[SPACE or Ctrl]:Accretion inc or dec.\n"
             "...+[ESC]:Reset init.\n"
             "[I]:Toggle display active model properties infomation.\n"
             "[H]:Toggle display this help."
             );

     pFont01_info_->setAlign(ALIGN_LEFT, VALIGN_BOTTOM);
     pFont01_info_->update(0, PX_C(CONFIG::GAME_BUFFER_HEIGHT), "");
}

void VvvWorld::processBehavior() {
    vb_->update(); //入力状況更新


    //全体的な操作
    manipulateWorld();

    //アクティブなアクターに対する操作
    if (listActorInfo_.length() > 0) {
        GgafDx::FigureActor* pActor =  listActorInfo_.getCurrent()->pActor_;
        manipulateActiveActor(pActor);
    }

    //全部のアクターに対する定常的な処理
    if (listActorInfo_.length() > 0) {
        GgafCore::RingLinkedList<ActorInfo>::Elem* pElem = listActorInfo_.getElemFirst();
        int n = listActorInfo_.length();
        for (int i = 0; i < n; i++) {
            ActorInfo* pActorInfo = pElem->getValue();
            GgafDx::FigureActor* pActor = pActorInfo->pActor_;
            behaveActor(pActor);
            pElem = pElem->_pNext;
        }
    }

    //ドラッグアンドドロップ時
    if (VvvCaretaker::is_wm_dropfiles_) {
        processDragAndDrop();
    }

    //ヘルプ関連
    if (GgafDx::Input::isPushedDownKey(DIK_H)) {
        view_help_ = view_help_ ? false : true;
        if (view_help_) {
            pFont01_help_->activate();
        } else {
            pFont01_help_->inactivate();
        }
    }
    if (GgafDx::Input::isPushedDownKey(DIK_I)) {
        view_info_ = view_info_ ? false : true;
        if (view_info_) {
            pFont01_info_->activate();
        } else {
            pFont01_info_->inactivate();
        }
    }
    if (view_info_) {
        if (listActorInfo_.length() > 0) {
            GgafDx::FigureActor* p = listActorInfo_.getCurrent()->pActor_;
            float r = p->_paMaterial[0].Ambient.r;
            float g = p->_paMaterial[0].Ambient.g;
            float b = p->_paMaterial[0].Ambient.b;
            std::ostringstream oss;
            oss << "["<<listActorInfo_.getCurrentIndex()<<"] = \""<<listActorInfo_.getCurrent()->dropfile_<<"\"\n"
                   "Class : "<<p->_class_name<<"\n"
                   "(_x, _y, _z) = ("<<(p->_x)<<", "<<(p->_y)<<", "<<(p->_z)<<")\n"
                   "_rx, _ry, _rz = "<<(p->_rx)<<", "<<(p->_ry)<<", "<<(p->_rz)<<"\n"
                   "_sx, _sy, _sz = "<<(p->_sx)<<", "<<(p->_sy)<<", "<<(p->_sz)<<"\n"
                   "_bounding_sphere_radius = "<<(p->getModel()->_bounding_sphere_radius)<<" * "<<(p->_rate_of_bounding_sphere_radius)<<" = "<<
                            (p->getModel()->_bounding_sphere_radius * p->_rate_of_bounding_sphere_radius)<<" (="<<DX_C(p->getModel()->_bounding_sphere_radius * p->_rate_of_bounding_sphere_radius)<<" coord)"<<"\n"
                   "red/green/blue = "<<r<<"/"<<g<<"/"<<b<<"\n"
                   "_alpha = "<< (p->getAlpha())<<"\n";
            if (p->instanceOf(Obj_GgafDx_CubeMapMorphMeshActor)) {
                CubeMapMorphMeshActor* p2 = (CubeMapMorphMeshActor*)p;
                oss << "_reflectance = "<< (p2->_reflectance)<<"\n";
                oss << "_cubemap_tex = \""<<(p2->_cubemap_tex)<<"\"\n";
            }
            oss << "renge,power = "<<(p->getModel()->_specular)<<", "<<(p->getModel()->_specular_power)<<"";

            if (p->instanceOf(Obj_GgafDx_SkinAniMeshActor)) {
                GgafDx::SkinAniMeshActor* p3 = (GgafDx::SkinAniMeshActor*)p;
                oss << "AnimationSetNum = "<< (p3->getPuppeteer()->getPerformanceNum())<<"\n";
            }

            if (p->instanceOf(Obj_GgafDx_BoneAniMeshActor)) {
                GgafDx::BoneAniMeshActor* p3 = (GgafDx::BoneAniMeshActor*)p;
                oss << "AnimationSetNum = "<< (p3->getPuppeteer()->getPerformanceNum())<<"\n";
            }
            pFont01_info_->update(oss.str().c_str());
        } else {
            pFont01_info_->update("empty");
        }

    } else {
    }
    VvvCaretaker* pCaretaker = (VvvCaretaker*)askCaretaker();

#ifdef MY_DEBUG
    if (getActiveFrame() % CONFIG::FPS == 0) {
        sprintf(aBufDebug_, "%07uF, %05u/%05uACT, %04u/%04uDRAW, %06u(%06u->%06uOTC,%03uDUP)CHK3D(%05uACT), %02uCHK2D(%02uACT), %03.1fFPS(SLOW%d), V%03d",
                                    pCaretaker->_frame_of_Caretaker,
                                    GgafCore::Caretaker::_num_active_actors,
                                    GgafCore::Actor::_num_actors,
                                    GgafCore::Caretaker::_num_draw,
                                    GgafCore::Caretaker::_num_draw_actors,
                                    WorldCollisionChecker::_num_check,
                                    WorldCollisionChecker::_num_otoku_check,
                                    WorldCollisionChecker::_num_otoku_check_actors,
                                    WorldCollisionChecker::_num_zannen_check,
                                    WorldCollisionChecker::_num_check_actors,
                                    ViewCollisionChecker::_num_check,
                                    ViewCollisionChecker::_num_check_actors,
                                    pCaretaker->_fps,
                                    pCaretaker->_slowdown_mode,
                                    (GgafDx::Sound::getAppMasterVolume())
                                    );
        _TRACE_("***** "<<aBufDebug_);
    }
#endif
}


void VvvWorld::manipulateWorld() {
    if (GgafDx::Input::isPushedDownKey(DIK_F1)) {
        //カメラを初期位置へ
        VvvCamera* const pCam = pCARETAKER->getSpacetime()->getCamera();
        pCamWorker_->slideMvCamTo(0,0,DX_C(pCam->getZOrigin()),60);
        pCamWorker_->slideMvVpTo(0,0,0,60);
        pCamWorker_->slideMvUpVecTo(0, PX_C(1), 0, 60);
    } else if (GgafDx::Input::isPushedDownKey(DIK_F2)) {
        //ターゲット変更＋カメラ向く
        if (listActorInfo_.length() > 0) {
            if (pCursor_->_pPhase->getCurrent() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
            } else {
                pCursor_->moveTo(listActorInfo_.next()->pActor_);
            }
            listActorInfo_.getCurrent()->pActor_->effectFlush(30);
            GgafDx::FigureActor* pT = listActorInfo_.getCurrent()->pActor_;
            pCamWorker_->slideMvVpTo(pT->_x, pT->_y, pT->_z, 60);
        }
    } else if (GgafDx::Input::isPushedDownKey(DIK_F3)) {
       //ターゲット変更のみ
       if (listActorInfo_.length() > 0) {
           if (pCursor_->_pPhase->getCurrent() == VvvCursor::CUR_SINK) {
               pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
           } else {
               pCursor_->moveTo(listActorInfo_.next()->pActor_);
           }
           listActorInfo_.getCurrent()->pActor_->effectFlush(30);
       }
    } else if (GgafDx::Input::isPushedDownKey(DIK_F4)) {
        //現ターゲットへカメラ向く
        if (listActorInfo_.length() > 0) {
            if (pCursor_->_pPhase->getCurrent() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
            }
            listActorInfo_.getCurrent()->pActor_->effectFlush(30);
            GgafDx::FigureActor* pT = listActorInfo_.getCurrent()->pActor_;
            pCamWorker_->slideMvVpTo(pT->_x, pT->_y, pT->_z, 60);
        }
     } else if (GgafDx::Input::isPushedDownKey(DIK_DELETE)) {
        //選択を削除
        if (listActorInfo_.length() > 0) {
            listActorInfo_.remove();
        }
        if (listActorInfo_.length() > 0) {
            pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
        }
    } else if (GgafDx::Input::isPushedDownKey(DIK_W)) {
        //ワイヤフレーム表示切替
        if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
        } else {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
        }
        pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, pCARETAKER->_d3dfillmode);
    } else if (GgafDx::Input::isPushedDownKey(DIK_G)) {
        //グリッド表示非表示
        if (pGrid_->isActive()) {
            pGrid_->inactivate();
        } else {
            pGrid_->activate();
        }
    } else if (GgafDx::Input::isPushedDownKey(DIK_O)) {
        //加算合成有り無し
        if (listActorInfo_.length() > 0) {
            GgafDx::FigureActor* pA = listActorInfo_.getCurrent()->pActor_;
            if (pA->_is_temp_technique) {
                pA->effectDefault();
            } else {
                pA->effectBlendOne();
            }
        }
    } else if (GgafDx::Input::isPushedDownKey(DIK_M)) {
       //加算合成有り演算Max
       if (listActorInfo_.length() > 0) {
           GgafDx::FigureActor* pA = listActorInfo_.getCurrent()->pActor_;
           if (pA->instanceOf(Obj_GgafDx_MeshActor)) {
               if (pA->_is_temp_technique) {
                   pA->effectDefault();
               } else {
                   pA->changeEffectTechniqueMoment("DestBlendOneMax", MAX_FRAME);
               }
           }
       }
    } else if (GgafDx::Input::isPushedDownKey(DIK_N)) {
        //カリングの有無
        if (listActorInfo_.length() > 0) {
            GgafDx::FigureActor* pA = listActorInfo_.getCurrent()->pActor_;
            if (pA->_cull_enable) {
                pA->setCullingDraw(false);
            } else {
                pA->setCullingDraw(true);
            }
        }
     } else if (GgafDx::Input::isPushedDownKey(DIK_Z)) {
        //自身のZバッファを書き込みする無し
        if (listActorInfo_.length() > 0) {
            GgafDx::FigureActor* pA = listActorInfo_.getCurrent()->pActor_;
            if (pA->_zbuffer_write_enable) {
                pA->setZBufferWriteEnable(false); //自身のZバッファを書き込みしない
            } else {
                pA->setZBufferWriteEnable(true);  //自身のZバッファを書き込みする
            }
        }
    } else if (GgafDx::Input::isPushedDownKey(DIK_B)) {
        GgafDx::FigureActor* pA = listActorInfo_.getCurrent()->pActor_;
        if (pA->instanceOf(Obj_GgafDx_MeshActor)) {
            //ハーフランバード切替
            GgafDx::MeshActor* pMeshActor = dynamic_cast<GgafDx::MeshActor*>(pA);
            if (pMeshActor->_lambert_flg > 0) {
                pMeshActor->_lambert_flg = -1.0f;  //-1.0:Lambert
            } else {
                pMeshActor->_lambert_flg = 1.0f;   //1.0:Half Lambert
            }
        }
    }

}

void VvvWorld:: manipulateActiveActor(GgafDx::FigureActor* prm_pActiveActor) {
    int d = 1;
    if (GgafDx::Input::isPressedKey(DIK_SPACE) || GgafDx::Input::isPressedKey(DIK_LCONTROL) || GgafDx::Input::isPressedKey(DIK_RCONTROL)) {
        d = 10;
    } else {
        d = 1;
    }
    if (GgafDx::Input::isPressedKey(DIK_A)) {
        //α増減
        if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
            prm_pActiveActor->addAlpha(0.01*d);
        }
        if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
            prm_pActiveActor->addAlpha(-0.01*d);
        }
        if (GgafDx::Input::isPressedKey(DIK_UP)) {
            prm_pActiveActor->addAlpha(0.01*d);
        }
        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
            prm_pActiveActor->addAlpha(-0.01*d);
        }
        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
            prm_pActiveActor->addAlpha(1.00); //αリセット
        }
        if (prm_pActiveActor->getAlpha() < 0.00) {
            prm_pActiveActor->setAlpha(0.00);
        }
        if (prm_pActiveActor->getAlpha() > 1.00) {
            prm_pActiveActor->setAlpha(1.00);
        }
    } else if (GgafDx::Input::isPressedKey(DIK_P)) {
        //スペキュラー
        if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
            prm_pActiveActor->getModel()->_specular += 0.05*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
            prm_pActiveActor->getModel()->_specular -= 0.05*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_UP)) {
            prm_pActiveActor->getModel()->_specular_power += 0.01*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
            prm_pActiveActor->getModel()->_specular_power -= 0.01*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
            prm_pActiveActor->getModel()->_specular = 0.00f;
            prm_pActiveActor->getModel()->_specular_power = 0.00f;
        }
    } else if (GgafDx::Input::isPressedKey(DIK_P)) {
        //スペキュラー
        if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
            prm_pActiveActor->getModel()->_specular += 0.05*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
            prm_pActiveActor->getModel()->_specular -= 0.05*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_UP)) {
            prm_pActiveActor->getModel()->_specular_power += 0.01*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
            prm_pActiveActor->getModel()->_specular_power -= 0.01*d;
        }
        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
            prm_pActiveActor->getModel()->_specular = 0.00f;
            prm_pActiveActor->getModel()->_specular_power = 0.00f;
        }
    } else if (GgafDx::Input::isPressedKey(DIK_S)) {
        if (GgafDx::Input::isPressedKey(DIK_X)) {
            //各軸拡大縮小
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                prm_pActiveActor->addScaleX(d*10);
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                prm_pActiveActor->addScaleX(-d*10);
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                prm_pActiveActor->addScaleY(d*10);
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                prm_pActiveActor->addScaleY(-d*10);
            }
            if (GgafDx::Input::isPressedKey(DIK_PGUP)) {
                prm_pActiveActor->addScaleZ(d*10);
            }
            if (GgafDx::Input::isPressedKey(DIK_PGDN)) {
                prm_pActiveActor->addScaleZ(-d*10);
            }
        } else {
            //全軸拡大縮小
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                prm_pActiveActor->addScale(d*10);
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                prm_pActiveActor->addScale(-d*10);
            }
        }
        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
            prm_pActiveActor->setScaleR(1.0);
        }
        //当たり判定更新
        dxcoord bound = prm_pActiveActor->getModel()->_bounding_sphere_radius * prm_pActiveActor->_rate_of_bounding_sphere_radius;
        GgafLib::WorldCollisionChecker* pChecker = listActorInfo_.getCurrent()->pCollisionChecker_;
        pChecker->setColliSphere(0, DX_C(bound));
    } else if (GgafDx::Input::isPressedKey(DIK_R)) {
        //軸回転
        if (GgafDx::Input::isPressedKey(DIK_PGUP)) {
            prm_pActiveActor->addRxFaceAng(D_ANG(d));
        }
        if (GgafDx::Input::isPressedKey(DIK_PGDN)) {
            prm_pActiveActor->addRxFaceAng(-D_ANG(d));
        }
        if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
            prm_pActiveActor->addRyFaceAng(D_ANG(d));
        }
        if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
            prm_pActiveActor->addRyFaceAng(-D_ANG(d));
        }
        if (GgafDx::Input::isPressedKey(DIK_UP)) {
            prm_pActiveActor->addRzFaceAng(D_ANG(d));
        }
        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
            prm_pActiveActor->addRzFaceAng(-D_ANG(d));
        }
        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
            prm_pActiveActor->setFaceAngZero();
        }
    } else if (GgafDx::Input::isPressedKey(DIK_C)) {
        //環境マップテクスチャ映りこみ率
        if (prm_pActiveActor->instanceOf(Obj_GgafDx_CubeMapMeshActor)) {
            CubeMapMeshActor* pCubeMapActor = (CubeMapMeshActor*)prm_pActiveActor;
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                pCubeMapActor->_reflectance += 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                pCubeMapActor->_reflectance -= 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                pCubeMapActor->_reflectance += 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                pCubeMapActor->_reflectance -= 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pCubeMapActor->_reflectance = 0.00;
            }
            if (pCubeMapActor->_reflectance < 0.0) {
                pCubeMapActor->_reflectance = 0.0;
            }
        }
        if (prm_pActiveActor->instanceOf(Obj_GgafDx_CubeMapMorphMeshActor)) {
            CubeMapMorphMeshActor* pCubeMapActor = (CubeMapMorphMeshActor*)prm_pActiveActor;
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                pCubeMapActor->_reflectance += 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                pCubeMapActor->_reflectance -= 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                pCubeMapActor->_reflectance += 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                pCubeMapActor->_reflectance -= 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pCubeMapActor->_reflectance = 0.00;
            }
            if (pCubeMapActor->_reflectance < 0.0) {
                pCubeMapActor->_reflectance = 0.0;
            }
            if (pCubeMapActor->_reflectance > 1.0) {
                pCubeMapActor->_reflectance = 1.0;
            }
        }
    } else if (GgafDx::Input::isPressedKey(DIK_0) ||
               GgafDx::Input::isPressedKey(DIK_1) ||
               GgafDx::Input::isPressedKey(DIK_2) ||
               GgafDx::Input::isPressedKey(DIK_3) ||
               GgafDx::Input::isPressedKey(DIK_4) ||
               GgafDx::Input::isPressedKey(DIK_5) ||
               GgafDx::Input::isPressedKey(DIK_6) ||
               GgafDx::Input::isPressedKey(DIK_7) ||
               GgafDx::Input::isPressedKey(DIK_8) ||
               GgafDx::Input::isPressedKey(DIK_9) )
    {
        if(prm_pActiveActor->instanceOf(Obj_GgafDx_SkinAniMeshActor) ) {
            GgafDx::SkinAniMeshActor* pSkinAniMeshActor = dynamic_cast<GgafDx::SkinAniMeshActor*>(prm_pActiveActor);
            if (pSkinAniMeshActor) {
                GgafDx::Puppeteer* pPuppeteer = pSkinAniMeshActor->getPuppeteer();
                int performance_num = pPuppeteer->getPerformanceNum();
                int dik = GgafDx::Input::getFirstPressedKey();
                for (int i = 0; i <= 9; i++) {
                    if (GgafDx::Input::isPushedDownKey(mapNumDik_[i])) {
                        if (i < performance_num) {
                            if (GgafDx::Input::isPressedKey(DIK_LSHIFT) || GgafDx::Input::isPressedKey(DIK_RSHIFT)) {
                                pPuppeteer->shiftTo(i, SEC_F(2));
                            } else if (GgafDx::Input::isPressedKey(DIK_SPACE)) {
                                pPuppeteer->playPartly(i, 1.0);
                            } else {
                                pPuppeteer->play(i);
                            }
                            break;
                        } else {
                            pPuppeteer->stop();
                            break;
                        }
                    }
                }
            }

        } else if(prm_pActiveActor->instanceOf(Obj_GgafDx_BoneAniMeshActor) ) {
            GgafDx::BoneAniMeshActor* pBoneAniMeshActor = dynamic_cast<GgafDx::BoneAniMeshActor*>(prm_pActiveActor);
            if (pBoneAniMeshActor) {
                GgafDx::Puppeteer* pPuppeteer = pBoneAniMeshActor->getPuppeteer();
                int performance_num = pPuppeteer->getPerformanceNum();
                int dik = GgafDx::Input::getFirstPressedKey();
                for (int i = 0; i <= 9; i++) {
                    if (GgafDx::Input::isPushedDownKey(mapNumDik_[i])) {
                        if (i < performance_num) {
                            if (GgafDx::Input::isPressedKey(DIK_LSHIFT) || GgafDx::Input::isPressedKey(DIK_RSHIFT)) {
                                pPuppeteer->shiftTo(i, SEC_F(2));
                            } else if (GgafDx::Input::isPressedKey(DIK_SPACE)) {
                                pPuppeteer->playPartly(i, 1.0);
                            } else {
                                pPuppeteer->play(i);
                            }
                            break;
                        } else {
                            pPuppeteer->stop();
                            break;
                        }
                    }
                }
            }

        } else if(prm_pActiveActor->instanceOf(Obj_GgafDx_MorphMeshActor) ) {
            GgafDx::MorphMeshActor* pMorphMeshActor = dynamic_cast<GgafDx::MorphMeshActor*>(prm_pActiveActor);
            if (pMorphMeshActor) {
                for (int i = 1; i <= pMorphMeshActor->_morph_target_num; i++) {
                    if (GgafDx::Input::isPressedKey(mapNumDik_[i])) {
                        if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                            pMorphMeshActor->addMorphWeight(i, 0.01*d);
                            if (pMorphMeshActor->getMorphWeight(i) > 1.0) {
                                pMorphMeshActor->setMorphWeight(i, 1.0);
                            }
                        }
                        if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                            pMorphMeshActor->addMorphWeight(i, -0.01*d);
                            if (pMorphMeshActor->getMorphWeight(i) < 0) {
                                pMorphMeshActor->setMorphWeight(i, 0);
                            }
                        }
                        if (GgafDx::Input::isPressedKey(DIK_UP)) {
                            pMorphMeshActor->addMorphWeight(i, 0.01*d);
                            if (pMorphMeshActor->getMorphWeight(i) > 1.0) {
                                pMorphMeshActor->setMorphWeight(i, 1.0);
                            }
                        }
                        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                            pMorphMeshActor->addMorphWeight(i, -0.01*d);
                            if (pMorphMeshActor->getMorphWeight(i) < 0) {
                                pMorphMeshActor->setMorphWeight(i, 0);
                            }
                        }
                        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                            pMorphMeshActor->setMorphWeight(i, 0);
                        }

                    } else {
                        //何もしない
                    }
                }
            }
        }
    } else if (GgafDx::Input::isPressedKey(DIK_J) ||
               GgafDx::Input::isPressedKey(DIK_K) ||
               GgafDx::Input::isPressedKey(DIK_L)   )
    {
        float r = prm_pActiveActor->_paMaterial[0].Ambient.r;
        float g = prm_pActiveActor->_paMaterial[0].Ambient.g;
        float b = prm_pActiveActor->_paMaterial[0].Ambient.b;
        //マテリアル赤色
        if (GgafDx::Input::isPressedKey(DIK_RIGHT) || GgafDx::Input::isPressedKey(DIK_UP)) {
            if (GgafDx::Input::isPressedKey(DIK_J)) {
                prm_pActiveActor->setMaterialRed(r+(0.01*d));
            }
            if (GgafDx::Input::isPressedKey(DIK_K)) {
                prm_pActiveActor->setMaterialGreen(g+(0.01*d));
            }
            if (GgafDx::Input::isPressedKey(DIK_L)) {
                prm_pActiveActor->setMaterialBlue(b+(0.01*d));
            }
        }
        if (GgafDx::Input::isPressedKey(DIK_LEFT) || GgafDx::Input::isPressedKey(DIK_DOWN)) {
            if (GgafDx::Input::isPressedKey(DIK_J)) {
                prm_pActiveActor->setMaterialRed(r-(0.01*d));
            }
            if (GgafDx::Input::isPressedKey(DIK_K)) {
                prm_pActiveActor->setMaterialGreen(g-(0.01*d));
            }
            if (GgafDx::Input::isPressedKey(DIK_L)) {
                prm_pActiveActor->setMaterialBlue(b-(0.01*d));
            }
        }
        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
            prm_pActiveActor->resetMaterialColor();
        }

    } else {

        //平行移動
        if (GgafDx::Input::isPressedKey(DIK_PGUP)) {
            prm_pActiveActor->_z += PX_C(d); //奥
        }
        if (GgafDx::Input::isPressedKey(DIK_PGDN)) {
            prm_pActiveActor->_z -= PX_C(d); //手前
        }
        if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
            prm_pActiveActor->_x += PX_C(d); //右
        }
        if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
            prm_pActiveActor->_x -= PX_C(d); //左
        }
        if (GgafDx::Input::isPressedKey(DIK_UP)) {
            prm_pActiveActor->_y += PX_C(d); //上
        }
        if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
            prm_pActiveActor->_y -= PX_C(d); //下
        }
        if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
            prm_pActiveActor->_x = 0;
            prm_pActiveActor->_y = 0;
            prm_pActiveActor->_z = 0;
        }
    }
}
void VvvWorld::behaveActor(GgafDx::FigureActor* prm_pActor) {

    if (prm_pActor->instanceOf(Obj_GgafDx_SkinAniMeshActor)) {
        GgafDx::SkinAniMeshActor* pSkinAniMeshActor = (GgafDx::SkinAniMeshActor*)prm_pActor;
        pSkinAniMeshActor->getPuppeteer()->behave();
    }
    if (prm_pActor->instanceOf(Obj_GgafDx_BoneAniMeshActor)) {
        GgafDx::BoneAniMeshActor* pBoneAniMeshActor = (GgafDx::BoneAniMeshActor*)prm_pActor;
        pBoneAniMeshActor->getPuppeteer()->behave();
    }
}

void VvvWorld::processDragAndDrop() {
    string dropfile_dir = UTIL::getFileDirName(VvvCaretaker::dropfiles_) + "/";
    string file_name_ext = std::string(UTIL::getFileBaseName(VvvCaretaker::dropfiles_));
    string file_name = std::string(UTIL::getFileBaseNameWithoutExt(VvvCaretaker::dropfiles_));
    string ext = std::string(UTIL::getFileExt(VvvCaretaker::dropfiles_));
    _TRACE_("dropfiles_="<<VvvCaretaker::dropfiles_);
    _TRACE_("dropfile_dir="<<dropfile_dir);
    _TRACE_("file_name_ext="<<file_name_ext);
    _TRACE_("file_name="<<file_name);
    _TRACE_("ext="<<ext);
    transform(ext.begin(), ext.end(), ext.begin(), static_cast<int (*)(int)>(toupper));

    //プロパティ一時退避
    string vvv_dir_model_system = CONFIG::DIR_MODEL[0];
    string vvv_dir_model_user = CONFIG::DIR_MODEL[1];
    string vvv_dir_model_current = CONFIG::DIR_MODEL[2];
    string vvv_dir_mesh_system = CONFIG::DIR_MESH[0];
    string vvv_dir_mesh_user = CONFIG::DIR_MESH[1];
    string vvv_dir_mesh_current = CONFIG::DIR_MESH[2];
    string vvv_dir_pointsprite_system = CONFIG::DIR_POINT_SPRITE3D[0];
    string vvv_dir_pointsprite_user = CONFIG::DIR_POINT_SPRITE3D[1];
    string vvv_dir_pointsprite_current = CONFIG::DIR_POINT_SPRITE3D[2];
    string vvv_dir_sprite_system = CONFIG::DIR_SPRITE[0];
    string vvv_dir_sprite_user = CONFIG::DIR_SPRITE[1];
    string vvv_dir_sprite_current = CONFIG::DIR_SPRITE[2];
    string vvv_dir_texture_system = CONFIG::DIR_TEXTURE[0];
    string vvv_dir_texture_user = CONFIG::DIR_TEXTURE[1];
    string vvv_dir_texture_current = CONFIG::DIR_TEXTURE[2];

    if (ext == "MODELX" || ext == "X" || ext == "SPRX" || ext == "PSPRX" || ext == "FSPRX" || ext == "RSPRX") {
        //プロパティ書き換え
        CONFIG::DIR_MODEL[0]      = vvv_dir_model_system; //vvv_dir_model_system はシステムスキンディレクトリ
        CONFIG::DIR_MODEL[1]      = dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODEL + "/";
        CONFIG::DIR_MODEL[2]      = dropfile_dir;
        CONFIG::DIR_MESH[0]      = vvv_dir_mesh_system; //vvv_dir_mesh_system はシステムスキンディレクトリ
        CONFIG::DIR_MESH[1]      = dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH + "/";
        CONFIG::DIR_MESH[2]      = dropfile_dir;
        CONFIG::DIR_POINT_SPRITE3D[0]      = vvv_dir_pointsprite_system; //vvv_dir_pointsprite_system はシステムスキンディレクトリ
        CONFIG::DIR_POINT_SPRITE3D[1]      = dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D + "/";
        CONFIG::DIR_POINT_SPRITE3D[2]      = dropfile_dir;
        CONFIG::DIR_SPRITE[0]      = vvv_dir_sprite_system; //vvv_dir_mesh_system はシステムスキンディレクトリ
        CONFIG::DIR_SPRITE[1]      = dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE + "/";
        CONFIG::DIR_SPRITE[2]      = dropfile_dir;
        CONFIG::DIR_TEXTURE[0]      = dropfile_dir; //ここは dropfile_dir vvv_dir_texture_system
        CONFIG::DIR_TEXTURE[1]      = dropfile_dir + "/../../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
        CONFIG::DIR_TEXTURE[2]      = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
    } else {
        string was_dropfile_dir = UTIL::getFileDirName(listActorInfo_.getCurrent()->dropfile_.c_str()) + "/";
        CONFIG::DIR_MODEL[0]      = vvv_dir_model_system; //vvv_dir_model_system はシステムスキンディレクトリ
        CONFIG::DIR_MODEL[1]      = was_dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODEL + "/";
        CONFIG::DIR_MODEL[2]      = was_dropfile_dir;
        CONFIG::DIR_MESH[0]      = vvv_dir_mesh_system; //vvv_dir_mesh_system はシステムスキンディレクトリ
        CONFIG::DIR_MESH[1]      = was_dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH + "/";
        CONFIG::DIR_MESH[2]      = was_dropfile_dir;
        CONFIG::DIR_POINT_SPRITE3D[0]      = vvv_dir_pointsprite_system; //vvv_dir_pointsprite_system はシステムスキンディレクトリ
        CONFIG::DIR_POINT_SPRITE3D[1]      = was_dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D + "/";
        CONFIG::DIR_POINT_SPRITE3D[2]      = was_dropfile_dir;
        CONFIG::DIR_SPRITE[0]      = vvv_dir_sprite_system; //vvv_dir_mesh_system はシステムスキンディレクトリ
        CONFIG::DIR_SPRITE[1]      = was_dropfile_dir + CONFIG::DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE + "/";
        CONFIG::DIR_SPRITE[2]      = was_dropfile_dir;

        CONFIG::DIR_TEXTURE[0]      = was_dropfile_dir;//ここは was_dropfile_dir vvv_dir_texture_system
        CONFIG::DIR_TEXTURE[1]      = was_dropfile_dir + "/../../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
        CONFIG::DIR_TEXTURE[2]      = was_dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
    }

    {
        GgafDx::FigureActor* pActor = nullptr;
        GgafLib::WorldCollisionChecker* pChecker = nullptr;
        GgafDx::ModelManager::ModelXFileFmt xdata;

        string model_file_name_ext = "";
        string model_file_name = "";
        string model_ext = "";

        if (ext == "MODELX") {
            GgafDx::ModelManager* pModelManager = pCARETAKER->_pModelManager;
            std::string model_def_filepath = std::string(VvvCaretaker::dropfiles_);
            pModelManager->obtainMetaModelInfo(&xdata, model_def_filepath);

        } else {
            xdata.XFileNum = 1;
            xdata.XFileNames = NEW std::string[1];
            xdata.XFileNames[0] = file_name_ext;
        }
        model_file_name_ext = std::string(xdata.XFileNames[0]);
        model_file_name = std::string(UTIL::getFileBaseNameWithoutExt(model_file_name_ext.c_str()));
        model_ext = std::string(UTIL::getFileExt(model_file_name_ext.c_str()));
        transform(model_ext.begin(), model_ext.end(), model_ext.begin(), static_cast<int (*)(int)>(toupper));
        _TRACE_("→ model_file_name_ext="<<model_file_name_ext);
        _TRACE_("→ model_file_name="<<model_file_name);
        _TRACE_("→ model_ext="<<model_ext);

        if (model_ext == "X") {
            std::string xfilepath = VvvWorld::getMeshXFilePath(model_file_name_ext, dropfile_dir);
            std::ifstream ifs(xfilepath.c_str());
            if (ifs.fail()) {
                throwCriticalException("["<<xfilepath<<"] が開けません");
            }
            _TRACE_("xfilepath="<<xfilepath);
            std::string buf;
            bool isSkinWeights = false;
            bool isAnimationSet = false;
            int nFrameTransformMatrix = 0;
            std::string data;
            while (isSkinWeights == false && !ifs.eof()) {
                ifs >> data;
                if (data == "SkinWeights") {
                    isSkinWeights = true;
                }
                if (data == "AnimationKey") {
                    isAnimationSet = true;
                }
                if (data == "FrameTransformMatrix") {
                    nFrameTransformMatrix++;
                }
            }
            ifs.close();

            if (isSkinWeights) {
                GgafLib::DefaultSkinAniMeshActor* pDefaultSkinAniMeshActor =
                        desireActor(VvvActor<GgafLib::DefaultSkinAniMeshActor>, "actor", file_name.c_str());
                pActor = pDefaultSkinAniMeshActor;
                pChecker = pDefaultSkinAniMeshActor->getWorldCollisionChecker();
            } else if (isAnimationSet) {
                GgafLib::DefaultBoneAniMeshActor* pDefaultBoneAniMeshActor =
                        desireActor(VvvActor<GgafLib::DefaultBoneAniMeshActor>, "actor", file_name.c_str());
                pActor = pDefaultBoneAniMeshActor;
                pChecker = pDefaultBoneAniMeshActor->getWorldCollisionChecker();

            } else {
                if (xdata.XFileNum >= 2) {
                    GgafLib::DefaultMorphMeshActor* pDefaultMorphMeshActor =
                            desireActor(VvvActor<GgafLib::DefaultMorphMeshActor>, "actor", file_name.c_str());
                    pActor = pDefaultMorphMeshActor;
                    pChecker = pDefaultMorphMeshActor->getWorldCollisionChecker();
                } else {
                    GgafLib::DefaultMeshActor* pDefaultMeshActor = NEW VvvActor<GgafLib::DefaultMeshActor>("actor", file_name.c_str());
                    pActor = pDefaultMeshActor;
                    pChecker = pDefaultMeshActor->getWorldCollisionChecker();
                }
            }
        } else if (model_ext == "SPRX") {
            GgafLib::DefaultSpriteActor* pDefaultSpriteActor =
                    desireActor(VvvActor<GgafLib::DefaultSpriteActor>, "actor", file_name.c_str());
            pActor = pDefaultSpriteActor;
            pChecker = pDefaultSpriteActor->getWorldCollisionChecker();
        } else if (model_ext == "PSPRX") {
            GgafLib::DefaultPointSpriteActor* pDefaultPointSpriteActor =
                    desireActor(VvvActor<GgafLib::DefaultPointSpriteActor>, "actor", file_name.c_str());
            pActor = pDefaultPointSpriteActor;
            pChecker = pDefaultPointSpriteActor->getWorldCollisionChecker();
        } else if (model_ext == "FSPRX") {
            GgafLib::DefaultFramedSpriteActor* pDefaultFramedSpriteActor =
                    desireActor(VvvActor<GgafLib::DefaultFramedSpriteActor>, "actor", file_name.c_str());
            pActor = pDefaultFramedSpriteActor;
            pChecker = pDefaultFramedSpriteActor->getWorldCollisionChecker();
        } else if (model_ext == "RSPRX") {
            GgafLib::DefaultRegularPolygonSpriteActor* pDefaultRegularPolygonSpriteActor =
                    desireActor(VvvActor<GgafLib::DefaultRegularPolygonSpriteActor>, "actor", file_name.c_str());
            pActor = pDefaultRegularPolygonSpriteActor;
            pChecker = pDefaultRegularPolygonSpriteActor->getWorldCollisionChecker();
        }
//        else if (model_ext == "X") {
//            std::string xfilepath = std::string(VvvCaretaker::dropfiles_);
//            GgafLib::DefaultMeshActor* pDefaultMeshActor = NEW VvvActor<GgafLib::DefaultMeshActor>("actor", file_name.c_str());
//            pActor = pDefaultMeshActor;
//            pChecker = pDefaultMeshActor->getWorldCollisionChecker();
//        }

        //アクター表示
        if (pActor) {
            //当たり判定設定
            dxcoord bound = pActor->getModel()->_bounding_sphere_radius * pActor->_rate_of_bounding_sphere_radius;
            pChecker->addCollisionArea(1);
            pChecker->setColliSphere(0, DX_C(bound));
            pActor->setHitAble(true);
            pActor->setCheckerKind(KIND_ACTOR);
            getSceneChief()->appendChild(pActor);
            ActorInfo* pActorInfo = NEW ActorInfo(pActor, pChecker, string(VvvCaretaker::dropfiles_), ext == "MODELX" ? true : false);
            listActorInfo_.addLast(pActorInfo);
            listActorInfo_.createIndex();
            listActorInfo_.last(); //カレントをlastへ
            VvvCamera* pCam = pCARETAKER->getSpacetime()->getCamera();
            GgafDx::GeometricActor* pCameraViewPoint = pCam->getCameraViewPoint();
            pActor->setPositionAt(pCameraViewPoint);
        }


    }


    if (!(file_name.find("cubemap") == std::string::npos &&
          file_name.find("CubeMap") == std::string::npos &&
          file_name.find("Cubemap") == std::string::npos)
    ) {
        _TRACE_("Cubemap テクスチャがきた。すげ替えます");
        GgafDx::FigureActor* pNewActor = nullptr;
        GgafLib::WorldCollisionChecker* pNewChecker = nullptr;
        GgafDx::FigureActor* pCurrentActor = listActorInfo_.getCurrent()->pActor_;
        if (pCurrentActor->instanceOf(Obj_GgafDx_MeshActor)) {
            _TRACE_("MeshActor → CubeMapMeshActor にすげ替える作戦実行");
            string was_dropfile_dir = UTIL::getFileDirName(listActorInfo_.getCurrent()->dropfile_.c_str()) + "/";
            _TRACE_("was_dropfile_dir="<<was_dropfile_dir);
            CONFIG::DIR_TEXTURE[0]    = was_dropfile_dir;
            CONFIG::DIR_TEXTURE[1]    = was_dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            CONFIG::DIR_TEXTURE[2]    = was_dropfile_dir + "/../../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            string was_model = UTIL::getFileBaseNameWithoutExt(listActorInfo_.getCurrent()->dropfile_.c_str());
            _TRACE_("was_model="<<was_model);
            GgafLib::CubeMapMeshActor* pCubeMapMeshActor =
                    desireActor(VvvActor<GgafLib::CubeMapMeshActor>, "actor", was_model.c_str());
            CONFIG::DIR_TEXTURE[0]    = dropfile_dir;
            CONFIG::DIR_TEXTURE[1]    = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            CONFIG::DIR_TEXTURE[2]    = dropfile_dir + "/../../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            pCubeMapMeshActor->setCubeMap(file_name_ext.c_str(), 0.5);
            pNewActor = pCubeMapMeshActor;
            pNewChecker = pCubeMapMeshActor->getWorldCollisionChecker();

        } else if (pCurrentActor->instanceOf(Obj_GgafDx_MorphMeshActor)) {
            _TRACE_("MorphMeshActor → CubeMapMorphMeshActor にすげ替える作戦実行");
            string was_dropfile_dir = UTIL::getFileDirName(listActorInfo_.getCurrent()->dropfile_.c_str()) + "/";
            _TRACE_("was_dropfile_dir="<<was_dropfile_dir);
            CONFIG::DIR_TEXTURE[0]    = was_dropfile_dir;
            CONFIG::DIR_TEXTURE[1]    = was_dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            CONFIG::DIR_TEXTURE[2]    = was_dropfile_dir + "/../../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            string was_model = UTIL::getFileBaseNameWithoutExt(listActorInfo_.getCurrent()->dropfile_.c_str());
            _TRACE_("was_model="<<was_model);
            GgafLib::CubeMapMorphMeshActor*  pCubeMapMorphMeshActor =
                    desireActor(VvvActor<GgafLib::CubeMapMorphMeshActor>, "actor", was_model.c_str());
            CONFIG::DIR_TEXTURE[0]    = dropfile_dir;
            CONFIG::DIR_TEXTURE[1]    = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            CONFIG::DIR_TEXTURE[2]    = dropfile_dir + "/../../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
            pCubeMapMorphMeshActor->setCubeMap(file_name_ext.c_str(), 0.5);
            pNewActor = pCubeMapMorphMeshActor;
            pNewChecker = pCubeMapMorphMeshActor->getWorldCollisionChecker();
        }
        if (pNewActor) {
            pNewActor->setPositionAt(pCurrentActor);
            pNewActor->setFaceAngAs(pCurrentActor);
            pNewActor->setScaleAt(pCurrentActor);
            pNewActor->setCheckerKind(KIND_ACTOR);
            getSceneChief()->appendChild(pNewActor);

            dxcoord new_bound = pNewActor->getModel()->_bounding_sphere_radius * pNewActor->_rate_of_bounding_sphere_radius;
            pNewChecker->addCollisionArea(1);
            pNewChecker->setColliSphere(0, DX_C(new_bound));
            pNewActor->setHitAble(true);

            ActorInfo* pActorInfoNew = NEW ActorInfo(pNewActor, pNewChecker, listActorInfo_.getCurrent()->dropfile_, listActorInfo_.getCurrent()->is_model_x_);
            listActorInfo_.replace(pActorInfoNew);
        }
    } else if (!(file_name.find("Nmap") == std::string::npos &&
        file_name.find("NMap") == std::string::npos &&
        file_name.find("nmap") == std::string::npos &&
        file_name.find("normalmap") == std::string::npos &&
        file_name.find("NormalMap") == std::string::npos &&
        file_name.find("Normalmap") == std::string::npos)
    ) {
        GgafDx::FigureActor* pCurrentActor = listActorInfo_.getCurrent()->pActor_;
        CONFIG::DIR_TEXTURE[0] = dropfile_dir;
        CONFIG::DIR_TEXTURE[1] = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
        CONFIG::DIR_TEXTURE[2] = dropfile_dir + "/../../" + CONFIG::DIRNAME_RESOURCE_SKINXXX_TEXTURE + "/";
        if (pCurrentActor->instanceOf(Obj_GgafDx_MeshActor)) {
            ((GgafDx::MeshActor*)pCurrentActor)->effectBumpMapping(file_name_ext.c_str());
        }
    }


    //プロパティ復帰
    CONFIG::DIR_MODEL[0] = vvv_dir_model_system;
    CONFIG::DIR_MODEL[1] = vvv_dir_model_user;
    CONFIG::DIR_MODEL[2] = vvv_dir_model_current;
    CONFIG::DIR_MESH[0]   = vvv_dir_mesh_system;
    CONFIG::DIR_MESH[1]   = vvv_dir_mesh_user;
    CONFIG::DIR_MESH[2]   = vvv_dir_mesh_current;
    CONFIG::DIR_POINT_SPRITE3D[0]   = vvv_dir_pointsprite_system;
    CONFIG::DIR_POINT_SPRITE3D[1]   = vvv_dir_pointsprite_user;
    CONFIG::DIR_POINT_SPRITE3D[2]   = vvv_dir_pointsprite_current;
    CONFIG::DIR_SPRITE[0]   = vvv_dir_sprite_system;
    CONFIG::DIR_SPRITE[1]   = vvv_dir_sprite_user;
    CONFIG::DIR_SPRITE[2]   = vvv_dir_sprite_current;
    CONFIG::DIR_TEXTURE[0]      = vvv_dir_texture_system;
    CONFIG::DIR_TEXTURE[1]      = vvv_dir_texture_user;
    CONFIG::DIR_TEXTURE[2]      = vvv_dir_texture_current;

    VvvCaretaker::is_wm_dropfiles_ = false;
}

std::string VvvWorld::getMeshXFilePath(std::string prm_xfile, std::string prm_model_def_dir) {
    std::string xfile_path = prm_model_def_dir + "/" + prm_xfile;
    UTIL::strReplace(xfile_path, "//", "/");
    if (prm_model_def_dir != "" && PathFileExists(xfile_path.c_str()) ) {
        _TRACE_("VvvWorld::getMeshXFilePath() xfile_path="<<xfile_path);
        return xfile_path; //カレントに存在すればそれを優先
    }

    std::string xfile_path2 = CONFIG::DIR_MESH[2] + "/" + prm_xfile;
    UTIL::strReplace(xfile_path2, "//", "/");
    if (PathFileExists(xfile_path2.c_str()) ) {
        _TRACE_("VvvWorld::getMeshXFilePath() xfile_path2="<<xfile_path2);
        return xfile_path2; //直下に存在すればそれを優先
    }

    std::string xfile_path1 = CONFIG::DIR_MESH[1] + "/" + prm_xfile;
    UTIL::strReplace(xfile_path1, "//", "/");
    _TRACE_("VvvWorld::getMeshXFilePath() xfile_path1="<<xfile_path1);
    if (PathFileExists(xfile_path1.c_str()) ) {
        return xfile_path1; //ユーザースキンに存在すればそれを優先
    }

    std::string xfile_path0 = CONFIG::DIR_MESH[0] + "/" + prm_xfile;
    UTIL::strReplace(xfile_path0, "//", "/");
    _TRACE_("VvvWorld::getMeshXFilePath() xfile_path0="<<xfile_path0);
    if (PathFileExists(xfile_path0.c_str()) ) {
        return xfile_path0;
    }
    throwCriticalException("Model::getMeshXFilePath() Xファイルが以下から見つかりません。prm_xfile="<<prm_xfile<<"\n"<<
            "xfile_path="<<xfile_path<<"\n"
            "xfile_path2="<<xfile_path2<<"\n"
            "xfile_path1="<<xfile_path1<<"\n"
            "xfile_path0="<<xfile_path0<<"\n"
            );
}

VvvWorld::~VvvWorld() {
}
