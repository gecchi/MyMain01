#include "VvvWorld.h"

#include <Shlwapi.h>
#include <algorithm>
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/MorphMeshActor.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"
#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultRegularPolygonSpriteActor.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "VvvCaretaker.h"
#include "actor/CamWorker/VvvCamWorker.h"
#include "actor/VvvCursor.h"
#include "actor/VvvGrid.h"
#include "actor/VvvCamera.h"
#include "actor/Font01.h"
#include "actor/VvvMousePointer.h"
#include "jp/ggaf/lib/util/Direction26Util.h"


using namespace GgafLib;
using namespace VVViewer;
using namespace std;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pCamWorker_ = NEW VvvCamWorker("VvvCamWorker", pCARETAKER->getSpacetime()->getCamera());
    bringSceneMediator()->appendGroupChild(pCamWorker_);
    pCursor_ = NEW VvvCursor("Cursor");
    bringSceneMediator()->appendGroupChild(pCursor_);
    pGrid_ = NEW VvvGrid("GRID");
    bringSceneMediator()->appendGroupChild(pGrid_);
    vb_ = NEW VirtualButton();
    pFont01_info_ =  NEW Font01("Font01");
    bringSceneMediator()->appendGroupChild(pFont01_info_);
    pFont01_help_ =  NEW Font01("Font01");
    bringSceneMediator()->appendGroupChild(pFont01_help_);
    view_help_ = true;
    view_info_ = true;
    pVvvMousePointer_= nullptr;
}

void VvvWorld::initialize() {
    pVvvMousePointer_ = desireActor(VvvMousePointer);
//    pVvvMousePointer_->setDefaultKind(KIND_2DFIX_MOUSE_POINTER);
    bringSceneMediator()->appendGroupChild(pVvvMousePointer_);

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
             "[R]+[CursorKey]:Z or Y Axial rotation model.\n"
             "[R]+[PgUp/PgDown]:X Axial rotation model.\n"
             "[S]+[PgUp/PgDown]:Scale inc or dec.\n"
             "[S]+[X]+[CursorKey]:X or Y Axial Scale inc or dec.\n"
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
             "[1]-[6]+[CursorKey]:Morph to taget No model, weight inc or dec.\n"
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
            if (pA->_zwriteenable) {
                pA->setZWriteEnable(false); //自身のZバッファを書き込みしない
            } else {
                pA->setZWriteEnable(true);  //自身のZバッファを書き込みする
            }
        }
    } else if (GgafDx::Input::isPushedDownKey(DIK_B)) {
        GgafDx::FigureActor* pA = listActorInfo_.getCurrent()->pActor_;
        if (pA->instanceOf(Obj_GgafDx_MeshActor)) {
            //ハーフランバード切替
            GgafDx::MeshActor* pMeshActor = dynamic_cast<GgafDx::MeshActor*>(pA);
            if (pMeshActor->_lambert_flg > 0) {
                pMeshActor->_lambert_flg = -1.0f;
            } else {
                pMeshActor->_lambert_flg = 1.0f;
            }
        }
    }

    if (listActorInfo_.length() > 0) {
        GgafDx::FigureActor* pActor =  listActorInfo_.getCurrent()->pActor_;
        int d = 1;
        if (GgafDx::Input::isPressedKey(DIK_SPACE) || GgafDx::Input::isPressedKey(DIK_LCONTROL) || GgafDx::Input::isPressedKey(DIK_RCONTROL)) {
            d = 10;
        } else {
            d = 1;
        }
        if (GgafDx::Input::isPressedKey(DIK_A)) {
            //α増減
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                pActor->addAlpha(0.01*d);
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                pActor->addAlpha(-0.01*d);
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                pActor->addAlpha(0.01*d);
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                pActor->addAlpha(-0.01*d);
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pActor->addAlpha(1.00); //αリセット
            }
            if (pActor->getAlpha() < 0.00) {
                pActor->setAlpha(0.00);
            }
            if (pActor->getAlpha() > 1.00) {
                pActor->setAlpha(1.00);
            }
        } else if (GgafDx::Input::isPressedKey(DIK_P)) {
            //スペキュラー
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                pActor->getModel()->_specular += 0.05*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                pActor->getModel()->_specular -= 0.05*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                pActor->getModel()->_specular_power += 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                pActor->getModel()->_specular_power -= 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pActor->getModel()->_specular = 0.00f;
                pActor->getModel()->_specular_power = 0.00f;
            }
        } else if (GgafDx::Input::isPressedKey(DIK_P)) {
            //スペキュラー
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                pActor->getModel()->_specular += 0.05*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                pActor->getModel()->_specular -= 0.05*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                pActor->getModel()->_specular_power += 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                pActor->getModel()->_specular_power -= 0.01*d;
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pActor->getModel()->_specular = 0.00f;
                pActor->getModel()->_specular_power = 0.00f;
            }
        } else if (GgafDx::Input::isPressedKey(DIK_S)) {
            if (GgafDx::Input::isPressedKey(DIK_X)) {
                //各軸拡大縮小
                if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                    pActor->addScaleX(d*10);
                }
                if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                    pActor->addScaleX(-d*10);
                }
                if (GgafDx::Input::isPressedKey(DIK_UP)) {
                    pActor->addScaleY(d*10);
                }
                if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                    pActor->addScaleY(-d*10);
                }
                if (GgafDx::Input::isPressedKey(DIK_PGUP)) {
                    pActor->addScaleZ(d*10);
                }
                if (GgafDx::Input::isPressedKey(DIK_PGDN)) {
                    pActor->addScaleZ(-d*10);
                }
            } else {
                //全軸拡大縮小
                if (GgafDx::Input::isPressedKey(DIK_UP)) {
                    pActor->addScale(d*10);
                }
                if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                    pActor->addScale(-d*10);
                }
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pActor->setScaleR(1.0);
            }
            //当たり判定更新
            dxcoord bound = pActor->getModel()->_bounding_sphere_radius * pActor->_rate_of_bounding_sphere_radius;
            GgafLib::WorldCollisionChecker* pChecker = listActorInfo_.getCurrent()->pCollisionChecker_;
            pChecker->setColliSphere(0, DX_C(bound));
        } else if (GgafDx::Input::isPressedKey(DIK_R)) {
            //軸回転
            if (GgafDx::Input::isPressedKey(DIK_PGUP)) {
                pActor->addRxFaceAng(D_ANG(d));
            }
            if (GgafDx::Input::isPressedKey(DIK_PGDN)) {
                pActor->addRxFaceAng(-D_ANG(d));
            }
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                pActor->addRyFaceAng(D_ANG(d));
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                pActor->addRyFaceAng(-D_ANG(d));
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                pActor->addRzFaceAng(D_ANG(d));
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                pActor->addRzFaceAng(-D_ANG(d));
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pActor->setFaceAngZero();
            }
        } else if (GgafDx::Input::isPressedKey(DIK_C)) {
            //環境マップテクスチャ映りこみ率
            if (pActor->instanceOf(Obj_GgafDx_CubeMapMeshActor)) {
                CubeMapMeshActor* pCubeMapActor = (CubeMapMeshActor*)pActor;
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
            if (pActor->instanceOf(Obj_GgafDx_CubeMapMorphMeshActor)) {
                CubeMapMorphMeshActor* pCubeMapActor = (CubeMapMorphMeshActor*)pActor;
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
        } else if (GgafDx::Input::isPressedKey(DIK_1) ||
                   GgafDx::Input::isPressedKey(DIK_2) ||
                   GgafDx::Input::isPressedKey(DIK_3) ||
                   GgafDx::Input::isPressedKey(DIK_4) ||
                   GgafDx::Input::isPressedKey(DIK_5) ||
                   GgafDx::Input::isPressedKey(DIK_6) ||
                   GgafDx::Input::isPressedKey(DIK_7)   )
        {
            if(pActor->instanceOf(Obj_GgafDx_MorphMeshActor) ) {
                GgafDx::MorphMeshActor* pMorphMeshActor = dynamic_cast<GgafDx::MorphMeshActor*>(pActor);
                if (pMorphMeshActor) {
                    for (int i = 1; i <= pMorphMeshActor->_morph_target_num; i++) {
                        if (GgafDx::Input::isPressedKey(DIK_1 + (i-1))) {
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
            float r = pActor->_paMaterial[0].Ambient.r;
            float g = pActor->_paMaterial[0].Ambient.g;
            float b = pActor->_paMaterial[0].Ambient.b;
            //マテリアル赤色
            if (GgafDx::Input::isPressedKey(DIK_RIGHT) || GgafDx::Input::isPressedKey(DIK_UP)) {
                if (GgafDx::Input::isPressedKey(DIK_J)) {
                    pActor->setMaterialRed(r+(0.01*d));
                }
                if (GgafDx::Input::isPressedKey(DIK_K)) {
                    pActor->setMaterialGreen(g+(0.01*d));
                }
                if (GgafDx::Input::isPressedKey(DIK_L)) {
                    pActor->setMaterialBlue(b+(0.01*d));
                }
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT) || GgafDx::Input::isPressedKey(DIK_DOWN)) {
                if (GgafDx::Input::isPressedKey(DIK_J)) {
                    pActor->setMaterialRed(r-(0.01*d));
                }
                if (GgafDx::Input::isPressedKey(DIK_K)) {
                    pActor->setMaterialGreen(g-(0.01*d));
                }
                if (GgafDx::Input::isPressedKey(DIK_L)) {
                    pActor->setMaterialBlue(b-(0.01*d));
                }
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pActor->resetMaterialColor();
            }

        } else {

            //平行移動
            if (GgafDx::Input::isPressedKey(DIK_PGUP)) {
                pActor->_z += PX_C(d); //奥
            }
            if (GgafDx::Input::isPressedKey(DIK_PGDN)) {
                pActor->_z -= PX_C(d); //手前
            }
            if (GgafDx::Input::isPressedKey(DIK_RIGHT)) {
                pActor->_x += PX_C(d); //右
            }
            if (GgafDx::Input::isPressedKey(DIK_LEFT)) {
                pActor->_x -= PX_C(d); //左
            }
            if (GgafDx::Input::isPressedKey(DIK_UP)) {
                pActor->_y += PX_C(d); //上
            }
            if (GgafDx::Input::isPressedKey(DIK_DOWN)) {
                pActor->_y -= PX_C(d); //下
            }
            if (GgafDx::Input::isPressedKey(DIK_ESCAPE)) {
                pActor->_x = 0;
                pActor->_y = 0;
                pActor->_z = 0;
            }
        }
    }



    if (VvvCaretaker::is_wm_dropfiles_) {
        string dropfile_dir = UTIL::getFileDirName(VvvCaretaker::dropfiles_) + "/";
        string file_name = UTIL::getFileBaseName(VvvCaretaker::dropfiles_);
        string model = UTIL::getFileBaseNameWithoutExt(VvvCaretaker::dropfiles_);
        string ext = UTIL::getFileExt(VvvCaretaker::dropfiles_);
        _TRACE_("dropfile_dir="<<dropfile_dir);
        _TRACE_("model="<<model);
        _TRACE_("ext="<<ext);

        //プロパティ一時退避
        string vvv_dir_model_system = CONFIG::DIR_MODEL[0];
        string vvv_dir_model_user = CONFIG::DIR_MODEL[1];
        string vvv_dir_model_current = CONFIG::DIR_MODEL[2];
        string vvv_dir_texture_system = CONFIG::DIR_MESH[0];
        string vvv_dir_texture_user = CONFIG::DIR_MESH[1];
        string vvv_dir_texture_current = CONFIG::DIR_MESH[2];
        string dir_texture_system = CONFIG::DIR_TEXTURE[0];
        string dir_texture_user = CONFIG::DIR_TEXTURE[1];
        string dir_texture_current = CONFIG::DIR_TEXTURE[2];
        //プロパティ書き換え
        CONFIG::DIR_MODEL[0]      = vvv_dir_model_system; //vvv_dir_model_system はシステムスキンディレクトリ
        CONFIG::DIR_MODEL[1]      = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_MODEL + "/";
        CONFIG::DIR_MODEL[2]      = dropfile_dir;
        CONFIG::DIR_MESH[0]      = vvv_dir_texture_user; //vvv_dir_texture_user はシステムスキンディレクトリ
        CONFIG::DIR_MESH[1]      = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_MESH + "/";
        CONFIG::DIR_MESH[2]      = dropfile_dir;
        CONFIG::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはシステムスキンディレクトリ
        CONFIG::DIR_TEXTURE[1]      = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
        CONFIG::DIR_TEXTURE[2]      = dropfile_dir;
        transform(ext.begin(), ext.end(), ext.begin(), static_cast<int (*)(int)>(toupper));
        {
            GgafDx::FigureActor* pActor = nullptr;
            GgafLib::WorldCollisionChecker* pChecker = nullptr;
            std::string modelfile = "";
            if (ext == "MESHX") {
                GgafDx::ModelManager* pModelManager = pCARETAKER->_pModelManager;
                GgafDx::ModelManager::MeshXFileFmt xdata;
                std::string model_def_filepath = std::string(VvvCaretaker::dropfiles_);
                pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
                if (xdata.XFileNum >= 2) {
                    GgafLib::DefaultMorphMeshActor* pDefaultMorphMeshActor =
                            desireActor(GgafLib::DefaultMorphMeshActor, "actor", model.c_str());
                    pActor = pDefaultMorphMeshActor;
                    pChecker = pDefaultMorphMeshActor->getWorldCollisionChecker();
                } else {
    //            if (model.find("WORLDBOUND") == string::npos) {
    //                pActor = desireActor(GgafLib::WorldBoundActor, "actor", filename);
    //            } else {
                    GgafLib::DefaultMeshActor* pDefaultMeshActor =
                            desireActor(GgafLib::DefaultMeshActor, "actor", model.c_str());
                    pActor = pDefaultMeshActor;
                    pChecker = pDefaultMeshActor->getWorldCollisionChecker();
    //            }
    //                DefaultMeshActor* pDefaultMeshActor = (DefaultMeshActor*)pActor;
    //                pDefaultMeshActor->setBumpMapTexture("normal.bmp");


                }
            } else if (ext == "SPRX") {
                GgafLib::DefaultSpriteActor* pDefaultSpriteActor =
                        desireActor(GgafLib::DefaultSpriteActor, "actor", model.c_str());
                pActor = pDefaultSpriteActor;
                pChecker = pDefaultSpriteActor->getWorldCollisionChecker();
            } else if (ext == "PSPRX") {
                GgafLib::DefaultPointSpriteActor* pDefaultPointSpriteActor =
                        desireActor(GgafLib::DefaultPointSpriteActor, "actor", model.c_str());
                pActor = pDefaultPointSpriteActor;
                pChecker = pDefaultPointSpriteActor->getWorldCollisionChecker();
            } else if (ext == "FSPRX") {
                GgafLib::DefaultFramedSpriteActor* pDefaultFramedSpriteActor =
                        desireActor(GgafLib::DefaultFramedSpriteActor, "actor", model.c_str());
                pActor = pDefaultFramedSpriteActor;
                pChecker = pDefaultFramedSpriteActor->getWorldCollisionChecker();
            } else if (ext == "RSPRX") {
                GgafLib::DefaultRegularPolygonSpriteActor* pDefaultRegularPolygonSpriteActor =
                        desireActor(GgafLib::DefaultRegularPolygonSpriteActor, "actor", model.c_str());
                pActor = pDefaultRegularPolygonSpriteActor;
                pChecker = pDefaultRegularPolygonSpriteActor->getWorldCollisionChecker();
            } else if (ext == "X") {
                //DefaultMeshActor のみ x ファイル直接でも大丈夫
                GgafLib::DefaultMeshActor* pDefaultMeshActor =
                        desireActor(GgafLib::DefaultMeshActor, "actor", model.c_str());
                pActor = pDefaultMeshActor;
                pChecker = pDefaultMeshActor->getWorldCollisionChecker();
            }
            //アクター表示
            if (pActor) {
                dxcoord bound = pActor->getModel()->_bounding_sphere_radius * pActor->_rate_of_bounding_sphere_radius;
                pChecker->createCollisionArea(1);
                pChecker->setColliSphere(0, DX_C(bound));
                pActor->setHitAble(true);

                bringSceneMediator()->appendGroupChild(KIND_ACTOR, pActor);
                ActorInfo* pActorInfo = NEW ActorInfo(pActor, pChecker, string(VvvCaretaker::dropfiles_));
                listActorInfo_.addLast(pActorInfo);
                listActorInfo_.createIndex();
                listActorInfo_.last(); //カレントをlastへ
                VvvCamera* pCam = pCARETAKER->getSpacetime()->getCamera();

                GgafDx::GeometricActor* p = pCam->getCameraViewPoint();
                pActor->setPositionAt(p);
            }


        }


        if (!(file_name.find("cubemap") == std::string::npos &&
              file_name.find("CubeMap") == std::string::npos &&
              file_name.find("Cubemap") == std::string::npos)
        ) {
            GgafDx::FigureActor* pNewActor = nullptr;
            GgafLib::WorldCollisionChecker* pNewChecker = nullptr;
            GgafDx::FigureActor* pCurrentActor = listActorInfo_.getCurrent()->pActor_;
            if (pCurrentActor->instanceOf(Obj_GgafDx_MeshActor)) {
                string was_dropfile_dir = UTIL::getFileDirName(listActorInfo_.getCurrent()->modelfile_.c_str()) + "/";
                CONFIG::DIR_MESH[2] = was_dropfile_dir;
                CONFIG::DIR_TEXTURE[0]    = dir_texture_user; //dir_texture_userはシステムスキンディレクトリ
                CONFIG::DIR_TEXTURE[1]    = was_dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                CONFIG::DIR_TEXTURE[2]    = was_dropfile_dir;
                string was_model = UTIL::getFileBaseNameWithoutExt(listActorInfo_.getCurrent()->modelfile_.c_str());
                GgafLib::CubeMapMeshActor* pCubeMapMeshActor =
                        desireActor(GgafLib::CubeMapMeshActor, "actor", was_model.c_str());
                CONFIG::DIR_TEXTURE[0]    = dir_texture_user; //dir_texture_userはシステムスキンディレクトリ
                CONFIG::DIR_TEXTURE[1]    = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                CONFIG::DIR_TEXTURE[2]    = dropfile_dir;
                pCubeMapMeshActor->setCubeMap(file_name.c_str(), 0.5);
                pNewActor = pCubeMapMeshActor;
                pNewChecker = pCubeMapMeshActor->getWorldCollisionChecker();

            } else if (pCurrentActor->instanceOf(Obj_GgafDx_MorphMeshActor)) {
                string was_dropfile_dir = UTIL::getFileDirName(listActorInfo_.getCurrent()->modelfile_.c_str()) + "/";
                CONFIG::DIR_MESH[2] = was_dropfile_dir;
                CONFIG::DIR_TEXTURE[0]    = dir_texture_user; //dir_texture_userはシステムスキンディレクトリ
                CONFIG::DIR_TEXTURE[1]    = was_dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                CONFIG::DIR_TEXTURE[2]    = was_dropfile_dir;
                GgafLib::CubeMapMorphMeshActor*  pCubeMapMorphMeshActor =
                        desireActor(GgafLib::CubeMapMorphMeshActor, "actor", pCurrentActor->getModel()->getName());
                CONFIG::DIR_TEXTURE[0]    = dir_texture_user; //dir_texture_userはシステムスキンディレクトリ
                CONFIG::DIR_TEXTURE[1]    = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                CONFIG::DIR_TEXTURE[2]    = dropfile_dir;
                pCubeMapMorphMeshActor->setCubeMap(file_name.c_str(), 0.5);
                pNewActor = pCubeMapMorphMeshActor;
                pNewChecker = pCubeMapMorphMeshActor->getWorldCollisionChecker();
            }
            if (pNewActor) {
                pNewActor->setPositionAt(pCurrentActor);
                pNewActor->setFaceAngAs(pCurrentActor);
                pNewActor->setScaleAt(pCurrentActor);
                bringSceneMediator()->appendGroupChild(KIND_ACTOR, pNewActor);

                dxcoord new_bound = pNewActor->getModel()->_bounding_sphere_radius * pNewActor->_rate_of_bounding_sphere_radius;
                pNewChecker->createCollisionArea(1);
                pNewChecker->setColliSphere(0, DX_C(new_bound));
                pNewActor->setHitAble(true);

                ActorInfo* pActorInfoNew = NEW ActorInfo(pNewActor, pNewChecker, listActorInfo_.getCurrent()->modelfile_);
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
            CONFIG::DIR_TEXTURE[0] = dir_texture_user; //dir_texture_userはシステムスキンディレクトリ
            CONFIG::DIR_TEXTURE[1] = dropfile_dir + "/../" + CONFIG::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
            CONFIG::DIR_TEXTURE[2] = dropfile_dir;
            if (pCurrentActor->instanceOf(Obj_GgafDx_MeshActor)) {
                ((GgafDx::MeshActor*)pCurrentActor)->effectBumpMapping(file_name.c_str());
            }
        }


        //プロパティ復帰
        CONFIG::DIR_MESH[0]   = vvv_dir_texture_system;
        CONFIG::DIR_MESH[1]   = vvv_dir_texture_user;
        CONFIG::DIR_MESH[2]   = vvv_dir_texture_current;
        CONFIG::DIR_MODEL[0] = vvv_dir_model_system;
        CONFIG::DIR_MODEL[1] = vvv_dir_model_user;
        CONFIG::DIR_MODEL[2] = vvv_dir_model_current;
        CONFIG::DIR_TEXTURE[0]      = dir_texture_system;
        CONFIG::DIR_TEXTURE[1]      = dir_texture_user;
        CONFIG::DIR_TEXTURE[2]      = dir_texture_current;
        VvvCaretaker::is_wm_dropfiles_ = false;
    }

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
            oss << "["<<listActorInfo_.getCurrentIndex()<<"] = \""<<listActorInfo_.getCurrent()->modelfile_<<"\"\n"
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

            pFont01_info_->update(oss.str().c_str());
        } else {
            pFont01_info_->update("empty");
        }


    } else {
    }
}

VvvWorld::~VvvWorld() {
}
