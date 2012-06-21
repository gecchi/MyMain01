#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;
using namespace std;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pCamWorker_ = NEW VvvCamWorker("VvvCamWorker");
    getDirector()->addSubGroup(pCamWorker_);
    pCursor_ = NEW VvvCursor("Cursor_");
    getDirector()->addSubGroup(pCursor_);

    vb_ = NEW VirtualButton();
}

void VvvWorld::initialize() {
}

void VvvWorld::processBehavior() {
    vb_->update(); //���͏󋵍X�V

    if (GgafDxInput::isPushedDownKey(DIK_F1)) {
        VvvCamera* pCam = P_CAM;
        pCamWorker_->move_target_X_CAM_ = 0;
        pCamWorker_->move_target_Y_CAM_ = 0;
        pCamWorker_->move_target_Z_CAM_ = DX_C(pCam->_cameraZ_org);
        pCamWorker_->move_target_X_VP_ =  0;
        pCamWorker_->move_target_Y_VP_ =  0;
        pCamWorker_->move_target_Z_VP_ =  0;
        pCamWorker_->move_target_XY_CAM_UP_ = D90ANG;
    } else if (GgafDxInput::isPushedDownKey(DIK_F2)) {
        if (_listActorInfo.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(_listActorInfo.getCurrent()->pActor_);
            } else {
                pCursor_->moveTo(_listActorInfo.next()->pActor_);
            }
            _listActorInfo.getCurrent()->pActor_->effectFlush(30);
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_RETURN)) {
        if (_listActorInfo.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(_listActorInfo.getCurrent()->pActor_);
            } else {
                pCursor_->moveTo(_listActorInfo.next()->pActor_);
            }
            _listActorInfo.getCurrent()->pActor_->effectFlush(30);
        }
        GgafDxDrawableActor* pT = _listActorInfo.getCurrent()->pActor_;
        pCamWorker_->move_target_X_VP_ =  pT->_X;
        pCamWorker_->move_target_Y_VP_ =  pT->_Y;
        pCamWorker_->move_target_Z_VP_ =  pT->_Z;
        pCamWorker_->move_target_XY_CAM_UP_ = D90ANG;
    } else if (GgafDxInput::isPushedDownKey(DIK_DELETE)) {
        if (_listActorInfo.length() > 0) {
            _listActorInfo.getCurrent()->pActor_->end();
            _listActorInfo.remove();
        }
        if (_listActorInfo.length() > 0) {
            pCursor_->moveTo(_listActorInfo.getCurrent()->pActor_);
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_W)) {
        //���C���t���[���\���ؑ�
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
    }

    if (_listActorInfo.length() > 0) {
        GgafDxDrawableActor* pActor =  _listActorInfo.getCurrent()->pActor_;
        int d = 1;
        if (GgafDxInput::isBeingPressedKey(DIK_SPACE) || GgafDxInput::isBeingPressedKey(DIK_LCONTROL) || GgafDxInput::isBeingPressedKey(DIK_RCONTROL)) {
            d = 10;
        } else {
            d = 1;
        }

        if (GgafDxInput::isBeingPressedKey(DIK_A)) {
            //��
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                if (pActor->getAlpha() > 1.00) {
                    pActor->setAlpha(1.00);
                } else {
                    pActor->addAlpha(0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                if (pActor->getAlpha() < 0.00) {
                    pActor->setAlpha(0.00);
                } else {
                    pActor->addAlpha(-0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                if (pActor->getAlpha() > 1.00) {
                    pActor->setAlpha(1.00);
                } else {
                    pActor->addAlpha(0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                if (pActor->getAlpha() < 0.00) {
                    pActor->setAlpha(0.00);
                } else {
                    pActor->addAlpha(-0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->addAlpha(1.00);
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_P)) {
            //�X�y�L�����[
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_pModel->_specular += 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_pModel->_specular -= 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_pModel->_specular_power += 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_pModel->_specular_power -= 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_pModel->_specular = 0.00f;
                pActor->_pModel->_specular_power = 0.00f;
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_S)) {
            //�g��k��
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->addScale(d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->addScale(-d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->addScale(d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->addScale(-d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->setScaleR(1.0);
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_R)) {
            //����]
            if (GgafDxInput::isBeingPressedKey(DIK_PGUP)) {
                pActor->_RX = UTIL::simplifyAng(pActor->_RX + D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                pActor->_RX = UTIL::simplifyAng(pActor->_RX - D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_RZ = UTIL::simplifyAng(pActor->_RZ + D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_RZ = UTIL::simplifyAng(pActor->_RZ - D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_RY = UTIL::simplifyAng(pActor->_RY + D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_RY = UTIL::simplifyAng(pActor->_RY - D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_RX = 0;
                pActor->_RY = 0;
                pActor->_RZ = 0;
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_C)) {

        } else {
            //���s�ړ�
            if (GgafDxInput::isBeingPressedKey(DIK_PGUP)) {
                pActor->_Z += PX_C(d); //��
            }
            if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                pActor->_Z -= PX_C(d); //��O
            }
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_X += PX_C(d); //�E
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_X -= PX_C(d); //��
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_Y += PX_C(d); //��
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_Y -= PX_C(d); //��
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_X = 0;
                pActor->_Y = 0;
                pActor->_Z = 0;
            }
        }

        if ( Obj_GgafDxCubeMapMorphMeshActor & pActor->_obj_class) {
            CubeMapMorphMeshActor* pMorphMeshActor = dynamic_cast<CubeMapMorphMeshActor*>(pActor);
            if (pMorphMeshActor) {
                for (int i = 1; i <= pMorphMeshActor->_pMorphMeshModel->_morph_target_num; i++) {
                    if (GgafDxInput::isBeingPressedKey(DIK_1 + (i-1))) {
                        pMorphMeshActor->_pMorpher->addWeight(i, 0.01);
                    } else {
                        pMorphMeshActor->_pMorpher->addWeight(i, -0.01);
                    }
                }
                pMorphMeshActor->_pMorpher->behave();
            }
        }
    }

    if (VvvGod::is_wm_dropfiles_) {
        string dropfile_dir = UTIL::getFileDirName(VvvGod::dropfiles_) + "/";
        string file_name = UTIL::getFileBaseName(VvvGod::dropfiles_);
        string model_id = UTIL::getFileBaseNameWithoutExt(VvvGod::dropfiles_);
        string model_type = UTIL::getFileExt(VvvGod::dropfiles_);
        _TRACE_("dropfile_dir="<<dropfile_dir);
        _TRACE_("model_id="<<model_id);
        _TRACE_("model_type="<<model_type);

        //�v���p�e�B�ꎞ�ޔ�
        string dir_mesh_model0 = GGAF_PROPERTY(DIR_MESH_MODEL[0]);
        string dir_mesh_model1 = GGAF_PROPERTY(DIR_MESH_MODEL[1]);
        string dir_sprite_model0 = GGAF_PROPERTY(DIR_SPRITE_MODEL[0]);
        string dir_sprite_model1 = GGAF_PROPERTY(DIR_SPRITE_MODEL[1]);
        string dir_texture0 = GGAF_PROPERTY(DIR_TEXTURE[0]);
        string dir_texture1 = GGAF_PROPERTY(DIR_TEXTURE[1]);
        //�v���p�e�B��������
        GGAF_PROPERTY(DIR_MESH_MODEL[0])   = dropfile_dir;
        GGAF_PROPERTY(DIR_MESH_MODEL[1])   = dropfile_dir;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[0]) = dropfile_dir;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[1]) = dropfile_dir;
        GGAF_PROPERTY(DIR_TEXTURE[0])      = dropfile_dir;
        GGAF_PROPERTY(DIR_TEXTURE[1])      = dropfile_dir + "/../" + GGAF_PROPERTY(DIRNAME_RESOURCE_SKIN_XXX_TEXTURE) + "/";
        transform(model_type.begin(), model_type.end(), model_type.begin(), static_cast<int (*)(int)>(toupper));

        GgafDxDrawableActor* pActor = NULL;
        std::string modelfile = "";
        if (model_type == "X") {
            if (model_id.length() > 2 && model_id.substr(model_id.length()-2) == "_0") {
                //model_id = "donatu_0"
                string model_part = model_id.substr(0,model_id.length()-2);
                //model_part = "donatu"
                int targetnum = 0;
                while (true) {
                    string model_filenm = model_part + "_" + ITOS(targetnum+1) + ".x";
                    //model_filenm = "donatu_1.x"
                    string model_path = dropfile_dir + "/" + model_filenm;
                    if (PathFileExists(model_path.c_str())) {
                        targetnum++;
                    } else {
                        break;
                    }
                }
                pActor = createInFactory2(GgafLib::CubeMapMorphMeshActor, "actor",
                                          string(ITOS(targetnum) + "/" +model_part).c_str());
                //���[�t
            } else {

//            if (model_id.find("WORLDBOUND") == string::npos) {
//                pActor = createInFactory2(GgafLib::WorldBoundActor, "actor", filename);
//            } else {
                pActor = createInFactory2(GgafLib::CubeMapMeshActor, "actor", model_id.c_str());
//            }
            }
        } else if (model_type == "SPRX") {
            pActor = createInFactory2(GgafLib::DefaultSpriteActor, "actor", model_id.c_str());
        } else if (model_type == "PSPRX") {
            pActor = createInFactory2(GgafLib::DefaultPointSpriteActor, "actor", model_id.c_str());
        } else if (model_type == "DDS") {
            if (_listActorInfo.getCurrent()) {
                GgafDxDrawableActor* pCurrentActor = _listActorInfo.getCurrent()->pActor_;
//                if ( Obj_GgafDxMeshActor & pCurrentActor->_obj_class) {
//                    CubeMapMeshActor* pNewActor = createInFactory2(GgafLib::CubeMapMeshActor, "actor",
//                                                                   pCurrentActor->_pModel->_model_name);
//                    pNewActor->locateWith(pCurrentActor);
//                    pNewActor->rotateWith(pCurrentActor);
//                    pNewActor->scaleWith(pCurrentActor);
//                    _listActorInfo.getCurrent()->pActor_->end();
//                    _listActorInfo.getCurrent()->pActor_= pNewActor;
//                    pNewActor->effectFlush(30);
//                } else if ( Obj_GgafDxMorphMeshActor & pCurrentActor->_obj_class) {
//                    CubeMapMorphMeshActor* pNewActor = createInFactory2(GgafLib::CubeMapMorphMeshActor, "actor",
//                                                                        pCurrentActor->_pModel->_model_name);
//                    pNewActor->locateWith(pCurrentActor);
//                    pNewActor->rotateWith(pCurrentActor);
//                    pNewActor->scaleWith(pCurrentActor);
//                    _listActorInfo.getCurrent()->pActor_->end();
//                    _listActorInfo.getCurrent()->pActor_= pNewActor;
//                    pNewActor->effectFlush(30);
//                }


                if (Obj_GgafDxCubeMapMeshActor & pCurrentActor->_obj_class) {
                    GgafDxCubeMapMeshActor* pCubeMapActor = (GgafDxCubeMapMeshActor*)pCurrentActor;
                    pCubeMapActor->setCubeMap(file_name.c_str(), 0.5);
                } else if( Obj_GgafDxCubeMapMorphMeshActor & pCurrentActor->_obj_class) {
                    GgafDxCubeMapMorphMeshActor* pCubeMapMorphActor = (GgafDxCubeMapMorphMeshActor*)pCurrentActor;
                    pCubeMapMorphActor->setCubeMap(file_name.c_str(), 0.5);
                }
            }
        } else {

        }
        if (pActor) {
            getDirector()->addSubGroup(pActor);
            ActorInfo* pActorInfo = NEW ActorInfo(pActor, string(VvvGod::dropfiles_));
            _listActorInfo.addLast(pActorInfo);
            _listActorInfo.last(); //�J�����g��last��
            VvvCamera* pCam = P_CAM;

            GgafDxGeometricActor* p = pCam->getViewPoint();
            pActor->locateWith(p);
        }

        //�v���p�e�B���A
        GGAF_PROPERTY(DIR_MESH_MODEL[0])   = dir_mesh_model0;
        GGAF_PROPERTY(DIR_MESH_MODEL[1])   = dir_mesh_model1;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[0]) = dir_sprite_model0;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[1]) = dir_sprite_model1;
        GGAF_PROPERTY(DIR_TEXTURE[0])      = dir_texture0;
        GGAF_PROPERTY(DIR_TEXTURE[1])      = dir_texture1;

        VvvGod::is_wm_dropfiles_ = false;
    }
}

VvvWorld::~VvvWorld() {
}
