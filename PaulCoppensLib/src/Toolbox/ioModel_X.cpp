/////////////////////////////////////////////////////////
// IOModel_X.cpp
// load/save Frame descriptions
//
/////////////////////////////////////////////////////////

#include "ToolBox\IOModel_X.h"

#define TEXT_BUFFER 255
//add tsuge
#define FACE3 (0)
#define FACE4 (1)
//
#define MAX_TEMPLATES 15

struct XOF_TEMPLATEID {
    char* TxtID;
    uint16 TemplateID;
};

XOF_TEMPLATEID Templates[MAX_TEMPLATES] = { { "template", X_TEMPLATE },
        { "FrameTransformMatrix", X_FRAMETRANSFORMMATRIX }, { "Frame", X_FRAME },
        { "XSkinMeshHeader", X_SKINMESHHEADER }, { "MeshTextureCoords", X_MESHTEXTURECOORDS },
        { "MeshMaterialList", X_MESHMATERIALLIST }, { "MeshNormals", X_MESHNORMALS },
        { "Mesh", X_MESH }, { "Material", X_MATERIAL }, { "SkinWeights", X_SKINWEIGHTS },
        { "TextureFilename", X_TEXTUREFILENAME }, { "AnimationSet", X_ANIMATIONSET },
        { "AnimationKey", X_ANIMATIONKEY }, { "Animation", X_ANIMATION }, { "Header", X_HEADER } };

//////////////////////////////////////////////////////////
//
//       MAIN LOAD & SAVE FUNCTIONS
//
//////////////////////////////////////////////////////////

bool ToolBox::IO_Model_X::Load(std::string pFilename, Frm::Model3D* &pT) {
    active_load_filename = pFilename;
    XFileHeader XHeader;
    _LoadSkeletton = 0;

    _TRACE_("===> Processing file:" << pFilename << " ===>");

    fin.open(pFilename.c_str(), ios::in);

    if (fin.bad())
        return false;

    fin.read((char*) &XHeader, 16);

    //add tsuge ���{��G���[���b�Z�[�W�ǉ�

    if (XHeader.Magic != XOFFILE_FORMAT_MAGIC) {
        _TRACE_("Not a .X model file or Cant find "<<pFilename<<". Aborted...");
        throwGgafCriticalException("X�t�@�C��'"<<active_load_filename<<"'��������܂���"); //add tsuge
        return false;
    }

    if (XHeader.Major_Version != XOFFILE_FORMAT_VERSION03) {
        _TRACE_("Major version greater than 03. Aborted...");
        throwGgafCriticalException("�{�A�v���́AX�t�@�C���̃��W���[�o�[�W������3��z�肵�Ă��܂��B\n�������A'"<<active_load_filename<<"'�̃o�[�W������"<<XHeader.Major_Version<<"�ł����B"); //add tsuge
        return false;
    }

    if ((XHeader.Minor_Version != XOFFILE_FORMAT_VERSION03)
            && (XHeader.Minor_Version != XOFFILE_FORMAT_VERSION02)) {
        _TRACE_("Minor version greater than 03. Aborted...");
        throwGgafCriticalException("�{�A�v���́AX�t�@�C���̃}�C�i�[�[�W������ 2 or 3 ��z�肵�Ă��܂��B\n�������A'"<<active_load_filename<<"'�̃o�[�W������"<<XHeader.Minor_Version<<"�ł����B"); //add tsuge
        return false;
    }

    if (XHeader.Format != XOFFILE_FORMAT_TEXT) {
        throwGgafCriticalException("X�t�@�C���̃w�b�_�����񂪌�����܂���B\n�Ώۃt�@�C��='"<<active_load_filename<<"'"); //add tsuge
        _TRACE_("Not a text format. Aborted...");
        return false;
    }

    _Object = pT;

    while (!fin.eof()) {
        int16 blockid = ProcessBlock();
        //_TRACE_("blockid="<<blockid);
        switch (blockid) {
        case X_ERROR:
            throwGgafCriticalException("X�t�@�C���𐳂����ǂݍ��߂܂���ł����B\n�Ώۃt�@�C��='"<<active_load_filename<<"'"); //add tsuge
            _TRACE_("Stopped processing the file ...");
            return false;
        case X_COMMENT:
            break; //nothing to do
        case X_EBRACE:
            break; //end of a block ?!
        case X_FRAME:
            ProcessBone((Frm::Bone*) 0);
            break;
        case X_MESH:
            ProcessMesh();
            break;
        case X_ANIMATIONSET:
            ProcessAnimationSets();
            break;
        case X_OBRACE:
        default:
            AvoidTemplate();
            break;
        }
    }

    if (_LoadSkeletton != 0)
        MapMeshToBones(_LoadSkeletton);

    _TRACE_("<=== Processed file:" << pFilename << " OK <===");

    fin.close();
    return true;
}

bool ToolBox::IO_Model_X::Save(std::string pFilename, Frm::Model3D* &pT) {
    return false;
}

//////////////////////////////////////////////////////////
//
//       UTILITIES
//
//////////////////////////////////////////////////////////

int16 ToolBox::IO_Model_X::ProcessBlock(void) {
    std::string Text;
    char Token;
    if (token_next == 0) {
        Token = fin.peek();
    } else {
        Token = token_next;
        token_next = 0;
    }
    //_TRACE_("Token='"<<Token<<"'");
    switch (Token) {
    case '\n':
    case ' ':
    case '\t':
        fin.get();
        return X_COMMENT; //spaces are identified as comments
    case '{':
        return X_OBRACE;
    case '}':
        fin.get();
        return X_EBRACE; //We arrived at the end of the block
    case '/':
        fin.get();
        if (fin.peek() != '/') {
            return X_ERROR;
        } //we processed a block name starting with slash ?!
    case '#':
        fin.ignore(TEXT_BUFFER, '\n');
        return X_COMMENT;
    default:

        fin >> Text;
        size_t len = Text.size();
        //_TRACE_("1Text="<<Text<<" len="<<len);
        if (len > 0) {
            char c = Text[len-1];
            if (c == '{') { //�ŏI����
                // �u���b�N��؂蕶���̓z���C�g�X�y�[�X�̑���'{'����؂�ƌ��Ȃ������i���^�Z�R�AX�t�@�C���p�j
                // "Header {" �ł� "Header{" �ł�����OK�Ƃ��邽�߁B
                Text = string(Text, 0, len-1);
                token_next = c;
            }
        }
        //_TRACE_("2Text="<<Text);
        return BlockID(Text);
    };
}

int16 ToolBox::IO_Model_X::BlockID(std::string &pText) {
    long Pos;

    if (fin.eof())
        return X_COMMENT;

    if (pText.empty()) {
        _TRACE_("Error, no block read !");
        throwGgafCriticalException("X�t�@�C���̓ǂݍ��݃u���b�N������܂���B\n�Ώۃt�@�C��='"<<active_load_filename<<"'"); //add tsuge
        //return X_ERROR;
    }

    for (int i = 0; i < MAX_TEMPLATES; i++) {
        Pos = pText.find(Templates[i].TxtID);
        if (Pos > -1) {
            fin.get(); //eats the whitespace after the block name.
            return Templates[i].TemplateID;
        }
    }
    _TRACE_("Unknown Block:" << pText);
    _TRACE_("X�t�@�C���ɑz�肵�Ȃ��s���ȃu���b�N������܂��B��������܂��B�Ώۃt�@�C��='"<<active_load_filename<<"'\n�Y���f�[�^='"<<pText<<"'"); //add tsuge
    return X_UNKNOWN;
}

void ToolBox::IO_Model_X::AvoidTemplate(void) {
    char Token;
    //Token = fin.peek();
    //_TRACE_("AvoidTemplate Token="<<Token);
    //fin.ignore(TEXT_BUFFER, '{');

    if (token_next == 0) {
        fin.ignore(TEXT_BUFFER, '{');
        token_next = 0;
    } else {
        if (token_next == '{') {
            token_next = 0;
        } else {
            fin.ignore(TEXT_BUFFER, '{');
            token_next = 0;
        }
    }

    while (!fin.eof()) {
        Token = fin.peek();
        if (Token == '{')
            AvoidTemplate();
        if (Token == '}') {
            fin.get();
            return;
        }
        fin.get();
    }
}

void ToolBox::IO_Model_X::Find(uchar pChar) {
    if (token_next == 0) {
        fin.ignore(TEXT_BUFFER, pChar);
    } else {
        if (token_next == pChar) {
            token_next = 0;
            return;
        } else {
            fin.ignore(TEXT_BUFFER, pChar);
            token_next = 0;
        }
    }
}

char* ToolBox::IO_Model_X::SetUID(char pType) {
    //This is a quick hack to derive a Unique ID for blocks with
    //no identifier names like in the tiny_4anim.x example.

    _X_UID.Integer = GetTickCount(); //This function return a 4 byte wide number
    _X_UID.Text[4] = pType; //We set the 5th byte with a significant character
    _X_UID.Text[5] = '\0'; //add tsuge �f�o�b�O�\���p�̂���

    //If any of the first 4 bytes are under 32 we add 32
    //We want to avoid the occurrence of the char '\0' within
    //the first 4 bytes since this would truncate the text returned.

//tsuge add begin �\���\������
    _X_UID.Text[0] %= 92;
    _X_UID.Text[1] %= 92;
    _X_UID.Text[2] %= 92;
    _X_UID.Text[3] %= 92;
    while (_X_UID.Text[0] < 32)
        _X_UID.Text[0] += 32;
    while (_X_UID.Text[1] < 32)
        _X_UID.Text[1] += 32;
    while (_X_UID.Text[2] < 32)
        _X_UID.Text[2] += 32;
    while (_X_UID.Text[3] < 32)
        _X_UID.Text[3] += 32;

//tsuge add end

//tsuge del begin
      //TODO:
//    if (_X_UID.Text[0] < 32)
//        _X_UID.Text[0] += 32;
//    if (_X_UID.Text[1] < 32)
//        _X_UID.Text[1] += 32;
//    if (_X_UID.Text[2] < 32)
//        _X_UID.Text[2] += 32;
//    if (_X_UID.Text[3] < 32)
//        _X_UID.Text[3] += 32;
//tsuge del end

    return _X_UID.Text;
}

//////////////////////////////////////////////////////////
//
//       TRANSFORM MATRIX
//
//////////////////////////////////////////////////////////

void ToolBox::IO_Model_X::ProcessFrameTransformMatrix(Frm::Bone* &pB) {
    char Text[TEXT_BUFFER];

    Find('{');
    for (int i = 0; i < 15; i++) {
        fin.getline(Text, TEXT_BUFFER, ',');
        pB->_MatrixPos[i] = TextToNum(Text);
    }
    fin.getline(Text, TEXT_BUFFER, ';');
    pB->_MatrixPos[15] = TextToNum(Text);
    //   pB->_TransMatrix = pB->_MatrixPos;
    Find('}');
}

//////////////////////////////////////////////////////////
//
//       BONE WITHIN SKELETTON
//
//////////////////////////////////////////////////////////

void ToolBox::IO_Model_X::ProcessBone(Frm::Bone* pBone) {
    Frm::Bone* cBone;
    int16 Token;
    char Data[TEXT_BUFFER];

    cBone = NEW Frm::Bone();


    //mod tsuge Token = fin.peek();
    if (token_next == 0) {
        Token = fin.peek();
    } else {
        Token = token_next;
        token_next = 0;
    }
    //if (Token != '{')
    if (Token != '{' && Token != ' ')  //modify by gecchi 2009/3/5
        fin >> cBone->_Name;
    else
        cBone->_Name = SetUID('B');

    if (pBone == 0) {
        _TRACE_("Skeletton 1st bone:" << cBone->_Name);
        _LoadSkeletton = cBone;
        _Object->_Skeletton = _LoadSkeletton;

        //add tsuge begin
        //��҂̃o�O���Ǝv����B
        //_LoadSkeletton���㏑������Ă����悤�Ȏd�g�݂ɂȂ��Ă��܂��Ă���̂��C���B
        //�Ƃ肠���� list�ɑޔ�����B�E�E�E�C���O�̓������[���[�N�ɂȂ��Ă����B
        _Object->_toplevel_Skelettons.push_back(cBone);
        //add tsuge end

    } else {
        _TRACE_("\t" << pBone->_Name << "->" << cBone->_Name);
        pBone->_Bones.push_back(cBone);
    }
    Find('{');
    Token = X_OBRACE;
    while (Token != X_EBRACE) {
        Token = ProcessBlock();
        switch (Token) {
        case X_HEADER: //add tsuge
            break;
        case X_COMMENT:
            break; //used for spaces and other kind of comments
        case X_EBRACE:
            return; //this is the end, my only friend ...
        case X_OBRACE:
            fin.getline(Data, TEXT_BUFFER, '}');
            cBone->_MeshName = Data;
            break;
        case X_FRAME:
            ProcessBone(cBone);
            break;
        case X_FRAMETRANSFORMMATRIX:
            ProcessFrameTransformMatrix(cBone);
            break;
        case X_MESH:
            ProcessMesh();
            cBone->_MeshName = _LoadMesh->_Name;
            break;
        default:
            AvoidTemplate();
            break;
        }
    }
}

//////////////////////////////////////////////////////////
//
//       MESH
//
//////////////////////////////////////////////////////////

void ToolBox::IO_Model_X::ProcessMesh(void) {
    std::string Text;
    int16 Token;
    char Data[TEXT_BUFFER];

    _LoadMesh = NEW Frm::Mesh;
    if (!_Object->_Meshes.empty()) {
        Frm::Mesh* LastMesh = _Object->_Meshes.back();
        _LoadMesh->_FirstVertex = LastMesh->_FirstVertex + LastMesh->_nVertices;
        if (65535 < ((int)LastMesh->_FirstVertex + (int)LastMesh->_nVertices)) {
            throwGgafCriticalException("X�t�@�C��'"<<active_load_filename<<"'�ǂݍ��ݒ��A_FirstVertex �� 65535�𒴂�����������܂���B\n���_���������̂ŉ��Ƃ����Ă��������B");
        }
        _LoadMesh->_FirstFace = LastMesh->_FirstFace + LastMesh->_nFaces;
        if (65535 < ((int)LastMesh->_FirstFace + (int)LastMesh->_nFaces)) {
            throwGgafCriticalException("X�t�@�C��'"<<active_load_filename<<"'�ǂݍ��ݒ��A_FirstFace �� 65535�𒴂�����������܂���B\n���_�C���f�b�N�X�i�ʁj���������̂ŉ��Ƃ����Ă��������B");
        }
        _LoadMesh->_FirstTextureCoord = LastMesh->_FirstTextureCoord
                + LastMesh->_nTextureCoords;
        if (65535 < ((int)LastMesh->_FirstTextureCoord + (int)LastMesh->_nTextureCoords)) {
            throwGgafCriticalException("X�t�@�C��'"<<active_load_filename<<"'�ǂݍ��ݒ��A_FirstTextureCoord �� 65535�𒴂�����������܂���B\n�e�N�X�`��UV���W���������̂ŉ��Ƃ����Ă��������B");
        }
        _LoadMesh->_FirstMaterial = LastMesh->_FirstMaterial
                + LastMesh->_nMaterials;
        if (65535 < ((int)LastMesh->_FirstMaterial + (int)LastMesh->_nMaterials)) {
            throwGgafCriticalException("X�t�@�C��'"<<active_load_filename<<"'�ǂݍ��ݒ��A_FirstMaterial �� 65535�𒴂�����������܂���B\n�}�e���A�����������̂ŉ��Ƃ����Ă��������B");
        }
        if (_LoadMesh->_FirstTextureCoord < _LoadMesh->_FirstVertex)
            _LoadMesh->_FirstTextureCoord = _LoadMesh->_FirstVertex;
        _LoadMesh->_FirstNormal = LastMesh->_FirstNormal + LastMesh->_nNormals;
        if (65535 < ((int)LastMesh->_FirstNormal + (int)LastMesh->_nNormals)) {
            throwGgafCriticalException("X�t�@�C��'"<<active_load_filename<<"'�ǂݍ��ݒ��A_FirstNormal �� 65535�𒴂�����������܂���B\n�@�����������̂ŉ��Ƃ����Ă��������B");
        }
        if (_LoadMesh->_FirstNormal < _LoadMesh->_FirstVertex)
            _LoadMesh->_FirstNormal = _LoadMesh->_FirstVertex;
        _TRACE_("Starting Vertex index:" << _LoadMesh->_FirstVertex);
        _TRACE_("Starting Face index:" << _LoadMesh->_FirstFace);
        _TRACE_("Starting TextureCoord index:" << _LoadMesh->_FirstTextureCoord);
        _TRACE_("Starting Normal index:" << _LoadMesh->_FirstNormal);
        _TRACE_("Starting Material index:" << _LoadMesh->_FirstMaterial);
    }

    Token = fin.peek();
    //if (Token != '{')
    if (Token != '{' && Token != ' ')  //modify by gecchi 2009/3/5
        fin >> _LoadMesh->_Name;
    else
        _LoadMesh->_Name = SetUID('M');

    Find('{');
    _TRACE_("Mesh:�u" << _LoadMesh->_Name<<"�v");

    fin.getline(Data, TEXT_BUFFER, ';');
    _LoadMesh->_nVertices = (uint16) TextToNum(Data);
    _TRACE_("Number of vertices:" << _LoadMesh->_nVertices);
    _LoadMesh->_Vertices = NEW Frm::Vertex[_LoadMesh->_nVertices];
    //   _LoadMesh->_SkinnedVertices = NEW Frm::Vertex[_LoadMesh->_nVertices];
    for (int i = 0; i < _LoadMesh->_nVertices; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_Vertices[i].data[0] = TextToNum(Data);
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_Vertices[i].data[1] = TextToNum(Data);
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_Vertices[i].data[2] = TextToNum(Data);
        fin.get();//eats either the comma or the semicolon at the end of each vertex description
    }

//delete tsuge
//
//    fin.getline(Data, TEXT_BUFFER, ';');
//    _LoadMesh->_nFaces = (uint16) TextToNum(Data);
//    _TRACE_("Number of Faces:" << _LoadMesh->_nFaces);
//    _LoadMesh->_Faces = NEW Frm::Face[_LoadMesh->_nFaces];
//    for (int i = 0; i < _LoadMesh->_nFaces; i++) {
//        Find(';');
//        fin.getline(Data, TEXT_BUFFER, ',');
//        _LoadMesh->_Faces[i].data[0] = (uint16) TextToNum(Data);
//        fin.getline(Data, TEXT_BUFFER, ',');
//        _LoadMesh->_Faces[i].data[1] = (uint16) TextToNum(Data);
//        fin.getline(Data, TEXT_BUFFER, ';');
//        _LoadMesh->_Faces[i].data[2] = (uint16) TextToNum(Data);
//        fin.get(); //eats either the comma or the semicolon at the end of each face description
//        //_TRACE_("Face:" << i, ":" << _LoadMesh->_Faces[i].data[0],_LoadMesh->_Faces[i].data[1],_LoadMesh->_Faces[i].data[2]);
//    }

//add tsuge
//4���_�C���f�b�N�X�ɂ��Face�w��ɑΉ�
//4;0,1,2,3;
//�̏ꍇ�́A0,1,2 �� 0,2,3 �ɕ���
    fin.getline(Data, TEXT_BUFFER, ';');
    _LoadMesh->_nFaces = (uint16) TextToNum(Data);
    _TRACE_("Before Number of Faces:" << _LoadMesh->_nFaces);
    _LoadMesh->_Faces = NEW Frm::Face[(_LoadMesh->_nFaces)*2];
    int face_vtx_num;
    int nFaces = _LoadMesh->_nFaces;
    int n = 0;
    for (int i = 0; i < nFaces; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        face_vtx_num = (int) TextToNum(Data);
        if (face_vtx_num == 3) {
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_Faces[n].data[0] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_Faces[n].data[1] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ';');
            _LoadMesh->_Faces[n].data[2] = (uint16) TextToNum(Data);
            fin.get(); //eats either the comma or the semicolon at the end of each face description
            _LoadMesh->_Faces[n].data[3] = FACE3;
        } else if (face_vtx_num == 4) {
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_Faces[n].data[0] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_Faces[n].data[1] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_Faces[n].data[2] = (uint16) TextToNum(Data);
            _LoadMesh->_Faces[n].data[3] = FACE4;

            _LoadMesh->_Faces[n+1].data[0] = _LoadMesh->_Faces[n].data[0];
            _LoadMesh->_Faces[n+1].data[1] = _LoadMesh->_Faces[n].data[2];
            fin.getline(Data, TEXT_BUFFER, ';');
            _LoadMesh->_Faces[n+1].data[2] = (uint16) TextToNum(Data);
            fin.get();
            _LoadMesh->_Faces[n+1].data[3] = FACE3;
            n++;
            _LoadMesh->_nFaces = _LoadMesh->_nFaces + 1;
        } else {
            _TRACE_("�������� face_vtx_num = "<<face_vtx_num);
        }
        n++;
    }

    _TRACE_("After Number of Faces:" << _LoadMesh->_nFaces);

    Token = X_COMMENT;
    while (Token != X_EBRACE) {
        Token = ProcessBlock();
        switch (Token) {
        case X_COMMENT:
            break; //used for spaces and other kind of comments
        case X_EBRACE:
            _Object->_Meshes.push_back(_LoadMesh);
            return; //this is the end, my only friend ...
        case X_MESHNORMALS:
            ProcessMeshNormals();
            break;
        case X_MESHTEXTURECOORDS:
            ProcessMeshTextureCoords();
            break;
        case X_MESHMATERIALLIST:
            ProcessMeshMaterials();
            break;
        case X_SKINMESHHEADER:
            AvoidTemplate();
            break;
        case X_SKINWEIGHTS:
            ProcessSkinWeights();
            break;
        default:
            AvoidTemplate();
            break;
        }
    }
    _Object->_Meshes.push_back(_LoadMesh);
}

//////////////////////////////////////////////////////////
//
//       TEXTURE COORDS
//
//////////////////////////////////////////////////////////

void ToolBox::IO_Model_X::ProcessMeshTextureCoords(void) {
    char Data[TEXT_BUFFER];

    Find('{');

    fin.getline(Data, TEXT_BUFFER, ';');
    _LoadMesh->_nTextureCoords = (uint16) TextToNum(Data);
    _TRACE_("Number of Texture Coords:" << _LoadMesh->_nTextureCoords);
    _LoadMesh->_TextureCoords = NEW Frm::TCoord[_LoadMesh->_nTextureCoords];
    for (int i = 0; i < _LoadMesh->_nTextureCoords; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_TextureCoords[i].data[0] = TextToNum(Data);
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_TextureCoords[i].data[1] = TextToNum(Data);
        fin.get();//eats the comma or the semicolon at the end
    }
    Find('}');
}

//////////////////////////////////////////////////////////
//
//       MESH NORMAL VECTORS
//
//////////////////////////////////////////////////////////

void ToolBox::IO_Model_X::ProcessMeshNormals(void) {
    char Data[TEXT_BUFFER];

    Find('{');

//delete tsuge
//    fin.getline(Data, TEXT_BUFFER, ';');
//    _LoadMesh->_nNormals = (uint16) TextToNum(Data);
//    _TRACE_("Number of normals :" << _LoadMesh->_nNormals);
//    _LoadMesh->_Normals = NEW Frm::vector<float>[_LoadMesh->_nNormals];
//    for (int i = 0; i < _LoadMesh->_nNormals; i++) {
//        fin.getline(Data, TEXT_BUFFER, ';');
//        _LoadMesh->_Normals[i].x = TextToNum(Data);
//        fin.getline(Data, TEXT_BUFFER, ';');
//        _LoadMesh->_Normals[i].y = TextToNum(Data);
//        fin.getline(Data, TEXT_BUFFER, ';');
//        _LoadMesh->_Normals[i].z = TextToNum(Data);
//        fin.get();//eats the comma or the semicolon at the end
//    }
//
//    Find(';'); //add gecchi 2009/03/01 face����ǂݔ�΂����߂ɒǉ��B���炭��҂̃o�O�B
//
//    _LoadMesh->_FaceNormals = NEW Frm::Face[_LoadMesh->_nFaces];
//    for (int i = 0; i < _LoadMesh->_nFaces; i++) {
//        Find(';');
//        fin.getline(Data, TEXT_BUFFER, ',');
//        _LoadMesh->_FaceNormals[i].data[0] = (uint16) TextToNum(Data);
//        fin.getline(Data, TEXT_BUFFER, ',');
//        _LoadMesh->_FaceNormals[i].data[1] = (uint16) TextToNum(Data);
//        fin.getline(Data, TEXT_BUFFER, ';');
//        _LoadMesh->_FaceNormals[i].data[2] = (uint16) TextToNum(Data);
//        fin.get(); //eats either the comma or the semicolon at the end of each face description
//        //      _TRACE_("Face Normal indexes:" << i, ":" << _LoadMesh->_FaceNormals[i].data[0],_LoadMesh->_FaceNormals[i].data[1],_LoadMesh->_FaceNormals[i].data[2]);
//    }

    //add tsuge
    //4���_�ɂ��@���C���f�b�N�X�ɑΉ�
    fin.getline(Data, TEXT_BUFFER, ';');
    _LoadMesh->_nNormals = (uint16) TextToNum(Data);
    _TRACE_("Number of normals :" << _LoadMesh->_nNormals);
    _LoadMesh->_Normals = NEW Frm::vector<float>[_LoadMesh->_nNormals];
    for (int i = 0; i < _LoadMesh->_nNormals; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_Normals[i].x = TextToNum(Data);
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_Normals[i].y = TextToNum(Data);
        fin.getline(Data, TEXT_BUFFER, ';');
        _LoadMesh->_Normals[i].z = TextToNum(Data);
        fin.get();//eats the comma or the semicolon at the end
    }

    fin.getline(Data, TEXT_BUFFER, ';');
    _LoadMesh->_nFaceNormals = TextToNum(Data);
    _TRACE_("Before Number of normals index :" << _LoadMesh->_nFaceNormals);
    _LoadMesh->_FaceNormals = NEW Frm::Face[_LoadMesh->_nFaces]; //NEW Frm::Face[_LoadMesh->_nFaceNormals] �ƊԈႦ�Ă͂��Ȃ��B
    int face_vtx_num;
    int n = 0;
    for (int i = 0; i < _LoadMesh->_nFaceNormals; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        face_vtx_num = (int) TextToNum(Data);
        if (face_vtx_num == 3) {
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_FaceNormals[n].data[0] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_FaceNormals[n].data[1] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ';');
            _LoadMesh->_FaceNormals[n].data[2] = (uint16) TextToNum(Data);
            fin.get(); //eats either the comma or the semicolon at the end of each face description
        } else if (face_vtx_num == 4) {
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_FaceNormals[n].data[0] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_FaceNormals[n].data[1] = (uint16) TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            _LoadMesh->_FaceNormals[n].data[2] = (uint16) TextToNum(Data);
            _LoadMesh->_FaceNormals[n+1].data[0] = _LoadMesh->_FaceNormals[n].data[0];
            _LoadMesh->_FaceNormals[n+1].data[1] = _LoadMesh->_FaceNormals[n].data[2];
            fin.getline(Data, TEXT_BUFFER, ';');
            _LoadMesh->_FaceNormals[n+1].data[2] = (uint16) TextToNum(Data);
            fin.get(); //eats either the comma or the semicolon at the end of each face description
            n++;
        } else {
            _TRACE_("�������� face_vtx_num = "<<face_vtx_num);
        }
        n++;
    }
    _LoadMesh->_nFaceNormals = n;
    _TRACE_("After Number of normals index :" << n);




    Find('}');
}

//////////////////////////////////////////////////////////
//
//       MATERIALS USED IN MESH
//
//////////////////////////////////////////////////////////

void ToolBox::IO_Model_X::ProcessMeshMaterials(void) {
    std::string Text;
    int16 Token;
    char Data[TEXT_BUFFER];

    Find('{');

// delete tsuge
//    fin.getline(Data, TEXT_BUFFER, ';');
//    _LoadMesh->_nMaterials = (uint16) TextToNum(Data);
//    _TRACE_("Number of Materials:" << (uint16)TextToNum(Data));
//
//    fin.getline(Data, TEXT_BUFFER, ';');
//    _LoadMesh->_FaceMaterials = NEW uint16[(uint16) TextToNum(Data)];
//    for (int i = 0; i < _LoadMesh->_nFaces - 1; i++) {
//        fin.getline(Data, TEXT_BUFFER, ',');
//        _LoadMesh->_FaceMaterials[i] = (uint16) TextToNum(Data);
//    }
//    fin.getline(Data, TEXT_BUFFER, ';');
//    _LoadMesh->_FaceMaterials[_LoadMesh->_nFaces - 1]
//            = (uint16) TextToNum(Data);
//    fin.get(); //eats the last semicolon

//add tsuge
//4���_�C���f�b�N�X��Face�w��Ή��ɂ��A�}�e���A���O���[�v���X�g�̂����␳
    fin.getline(Data, TEXT_BUFFER, ';');
    _LoadMesh->_nMaterials = (uint16) TextToNum(Data);


    fin.getline(Data, TEXT_BUFFER, ';');
    _LoadMesh->_FaceMaterials = NEW uint16[((uint16)TextToNum(Data))*2];
    _TRACE_("Before Number of Materials:" << (uint16)TextToNum(Data));

    int file_nFaceMaterials = (uint16) TextToNum(Data);
    int n = 0;
    for (int i = 0; i < file_nFaceMaterials - 1; i++) {
        fin.getline(Data, TEXT_BUFFER, ',');
        if (_LoadMesh->_Faces[n].data[3] == FACE3) {
            _LoadMesh->_FaceMaterials[n] = (uint16) TextToNum(Data);
        } else if (_LoadMesh->_Faces[n].data[3] == FACE4) {
            _LoadMesh->_FaceMaterials[n] = (uint16) TextToNum(Data);
            _LoadMesh->_FaceMaterials[n+1] = (uint16) TextToNum(Data);
            n++;
        }
        n++;
    }
    fin.getline(Data, TEXT_BUFFER, ';');
    if (_LoadMesh->_Faces[n].data[3] == FACE3) {
        _LoadMesh->_FaceMaterials[n] = (uint16) TextToNum(Data);

    } else if (_LoadMesh->_Faces[n].data[3] == FACE4) {
        _LoadMesh->_FaceMaterials[n] = (uint16) TextToNum(Data);
        _LoadMesh->_FaceMaterials[n+1] = (uint16) TextToNum(Data);
        n++;
    }
    n++;
    fin.get(); //eats the last semicolon

    _TRACE_("After Number of Materials:" << n);


    Token = X_COMMENT;
    while (Token != X_EBRACE) {
        Token = ProcessBlock();
        switch (Token) {
        case X_COMMENT:
            break; //used for spaces and other kind of comments
        case X_EBRACE:
            return; //this is the end, my only friend ...
        case X_MATERIAL:
            ProcessMaterial();
            break;
        default:
            AvoidTemplate();
            break;
        }
    }
}

//////////////////////////////////////////////////////////
//
//       MATERIAL DESCRIPTION
//
//////////////////////////////////////////////////////////

void ToolBox::IO_Model_X::ProcessMaterial(void) {
    std::string Text;
    int16 Token;
    char Data[TEXT_BUFFER];

    //Frm::Material* NewMaterial = NEW Frm::Material;
    Frm::Material* NewMaterial = NEW Frm::Material(); //alter tsuge

    Find('{');
    for (int i = 0; i < 4; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        NewMaterial->_FaceColor.data[i] = TextToNum(Data);
    }
    fin.get(); //eats the last semicolon
    fin.getline(Data, TEXT_BUFFER, ';');
    NewMaterial->_power = TextToNum(Data);

    for (int i = 0; i < 3; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        NewMaterial->_SpecularColor.data[i] = TextToNum(Data);
    }
    fin.get();//eats the last semicolon

    for (int i = 0; i < 3; i++) {
        fin.getline(Data, TEXT_BUFFER, ';');
        NewMaterial->_EmissiveColor.data[i] = TextToNum(Data);
    }
    fin.get();//eats the last semicolon

    Token = X_COMMENT;

    bool exist_tex = false;//add tsuge

    while (Token != '}') {
        Token = ProcessBlock();
        switch (Token) {
        case X_COMMENT:
            break; //used for spaces and other kind of comments
        case X_EBRACE:
            _LoadMesh->_Materials.push_back(NewMaterial);
            return; //this is the end, my only friend ...
        case X_TEXTUREFILENAME:
            Find('{');
            Find('"');
            fin.getline(Data, TEXT_BUFFER, '"');
            NewMaterial->_TextureName = Data;
            _TRACE_("_TextureName="<<NewMaterial->_TextureName);
            exist_tex = true; //add tsuge
            Find('}');
            break;
        default:
            AvoidTemplate();
            break;
        }
    }
    //add tsuge begin
    if (!exist_tex) {
        NewMaterial->_TextureName = "";
    }
    //add tsuge end
    _LoadMesh->_Materials.push_back(NewMaterial);
}

//////////////////////////////////////////////////////////
//
//       SKIN WEIGHTS
//
//////////////////////////////////////////////////////////
void ToolBox::IO_Model_X::ProcessSkinWeights(void) {
    Frm::Bone* cBone;
    std::string temp;
    char Data[TEXT_BUFFER];

    Find('{');
    Find('"');
    fin.getline(Data, TEXT_BUFFER, '"');
    temp = Data;
    cBone = _LoadSkeletton->IsName(temp);
    //   cBone->_Mesh = _LoadMesh;
    _TRACE_("Skinning bone:" << cBone->_Name);
    Find(';');

    fin.getline(Data, TEXT_BUFFER, ';');
    cBone->_nVertices = (uint16) TextToNum(Data);
    cBone->_Vertices = NEW uint16[(cBone->_nVertices)];
    for (int i = 0; i < cBone->_nVertices - 1; i++) {
        fin.getline(Data, TEXT_BUFFER, ',');
        cBone->_Vertices[i] = (uint16) TextToNum(Data);
        _TRACE_("Vertex:" << atoi(Data));
    }
    fin.getline(Data, TEXT_BUFFER, ';');
    cBone->_Vertices[cBone->_nVertices - 1] = (uint16) TextToNum(Data);
    _TRACE_("Vertex:" << atoi(Data));

    cBone->_Weights = NEW float[cBone->_nVertices];
    for (int i = 0; i < cBone->_nVertices - 1; i++) {
        fin.getline(Data, TEXT_BUFFER, ',');
        cBone->_Weights[i] = TextToNum(Data);
        _TRACE_("Weight:" << atof(Data));
    }
    fin.getline(Data, TEXT_BUFFER, ';');
    cBone->_Weights[cBone->_nVertices - 1] = TextToNum(Data);
    _TRACE_("Weight:" << atof(Data));

    for (int i = 0; i < 15; i++) {
        fin.getline(Data, TEXT_BUFFER, ',');
        cBone->_SkinOffset[i] = TextToNum(Data);
    }
    fin.getline(Data, TEXT_BUFFER, ';');
    cBone->_SkinOffset[15] = TextToNum(Data);
    Find('}');
}

/*************************************************
 NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW- NEW*/

//////////////////////////////////////////////////////////
//
//       ANIMATION SET
//
//////////////////////////////////////////////////////////
void ToolBox::IO_Model_X::ProcessAnimationSets(void) {
    //   std::string Text;
    int16 Token;
    //   char Data[TEXT_BUFFER];

    _MaxKey = 0;
    _LoadAnimationSet = NEW Frm::AnimationSet;

    Token = fin.peek();
    //if (Token != '{')
    if (Token != '{' && Token != ' ')  //modify by gecchi 2009/3/5
        fin >> _LoadAnimationSet->_Name;
    else
        _LoadAnimationSet->_Name = SetUID('A');

    Find('{');
    _TRACE_("Animation Set:" << _LoadAnimationSet->_Name);

    Token = X_COMMENT;
    while (Token != X_EBRACE) {
        Token = ProcessBlock();
        switch (Token) {
        case X_COMMENT:
            break; //used for spaces and other kind of comments
        case X_EBRACE:
            _LoadAnimationSet->_MaxKey = _MaxKey;
            _TRACE_("MaxKey:" << _MaxKey)
            ;
            _Object->_AnimationSets.push_back(_LoadAnimationSet);
            return; //this is the end, my only friend ...
        case X_ANIMATION:
            ProcessAnimations(_LoadAnimationSet);
            break;
        default:
            AvoidTemplate();
            break;
        }
    }
    _LoadAnimationSet->_MaxKey = _MaxKey;
    _TRACE_("MaxKey:" << _MaxKey);
    _Object->_AnimationSets.push_back(_LoadAnimationSet);
}

//////////////////////////////////////////////////////////
//
//       ANIMATION
//
//////////////////////////////////////////////////////////
void ToolBox::IO_Model_X::ProcessAnimations(Frm::AnimationSet* &pAS) {
    int16 Token;
    char Data[TEXT_BUFFER];
    Frm::Animation* TempAnimation = NEW Frm::Animation;

    Find('{');

    Token = X_COMMENT;
    while (Token != X_EBRACE) {
        Token = ProcessBlock();
        switch (Token) {
        case X_COMMENT:
            break; //used for spaces and other kind of comments
        case X_EBRACE:
            pAS->_Animations.push_back(TempAnimation);
            return; //this is the end, my only friend ...
        case X_OBRACE:
            Find('{');
            fin.getline(Data, TEXT_BUFFER, '}');
            Remove(' ', Data);
            TempAnimation->_BoneName = Data;
            _TRACE_("Animated Bone:" << TempAnimation->_BoneName)
            ;
            break;
        case X_ANIMATIONKEY:
            ProcessAnimationKeys(TempAnimation);
            break;
        default:
            AvoidTemplate();
            break;
        }
    }
    pAS->_Animations.push_back(TempAnimation);
}

//////////////////////////////////////////////////////////
//
//       ANIMATION KEY
//
//////////////////////////////////////////////////////////
void ToolBox::IO_Model_X::ProcessAnimationKeys(Frm::Animation* &pA) {
    int Type, Size;
    char Data[TEXT_BUFFER];
    Frm::RotateKey* TempRot;
    Frm::ScaleKey* TempScale;
    Frm::PositionKey* TempPos;
    Frm::MatrixKey* TempMatrix;

    Find('{');
    fin.getline(Data, TEXT_BUFFER, ';');
    Type = (uint16) atoi(Data);
    fin.getline(Data, TEXT_BUFFER, ';');
    Size = (uint16) atoi(Data);

    switch (Type) {
    case 0:
        MYTRACE(Size, "Rotation Keys");
        pA->_Rotations.reserve(Size);
        while (Size--) {
            TempRot = NEW Frm::RotateKey;
            fin.getline(Data, TEXT_BUFFER, ';');
            TempRot->Time = (uint16) TextToNum(Data);
            if (TempRot->Time > _MaxKey)
                _MaxKey = TempRot->Time;
            Find(';');
            fin.getline(Data, TEXT_BUFFER, ',');
            TempRot->Rotation[0] = TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            TempRot->Rotation[1] = TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            TempRot->Rotation[2] = TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ';');
            TempRot->Rotation[3] = TextToNum(Data);
            Find(';');
            fin.get();
            pA->_Rotations.push_back(TempRot);
        }
        break;
    case 1:
        MYTRACE(Size, "Scaling Keys");
        pA->_Scalings.reserve(Size);
        while (Size--) {
            TempScale = NEW Frm::ScaleKey;
            fin.getline(Data, TEXT_BUFFER, ';');
            TempScale->Time = (uint16) TextToNum(Data);
            if (TempScale->Time > _MaxKey)
                _MaxKey = TempScale->Time;
            Find(';');
            fin.getline(Data, TEXT_BUFFER, ',');
            TempScale->Scale.x = TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            TempScale->Scale.y = TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ';');
            TempScale->Scale.z = TextToNum(Data);
            Find(';');
            fin.get();
            pA->_Scalings.push_back(TempScale);
        }
        break;
    case 2:
        MYTRACE(Size, "Position Keys");
        pA->_Translations.reserve(Size);
        while (Size--) {
            TempPos = NEW Frm::PositionKey;
            fin.getline(Data, TEXT_BUFFER, ';');
            TempPos->Time = (uint16) TextToNum(Data);
            if (TempPos->Time > _MaxKey)
                _MaxKey = TempPos->Time;
            Find(';');
            fin.getline(Data, TEXT_BUFFER, ',');
            TempPos->Translation[0] = TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ',');
            TempPos->Translation[1] = TextToNum(Data);
            fin.getline(Data, TEXT_BUFFER, ';');
            TempPos->Translation[2] = TextToNum(Data);
            Find(';');
            fin.get();
            pA->_Translations.push_back(TempPos);
        }
        break;
    case 4:
        MYTRACE(Size, "Matrix Keys");
        pA->_Matrices.reserve(Size);
        while (Size--) {
            TempMatrix = NEW Frm::MatrixKey;
            fin.getline(Data, TEXT_BUFFER, ';');
            TempMatrix->Time = (uint16) TextToNum(Data);
            if (TempMatrix->Time > _MaxKey)
                _MaxKey = TempMatrix->Time;
            Find(';');
            for (int i = 0; i < 15; i++) {
                fin.getline(Data, TEXT_BUFFER, ',');
                TempMatrix->Matrix[i] = TextToNum(Data);
            }
            fin.getline(Data, TEXT_BUFFER, ';');
            TempMatrix->Matrix[15] = TextToNum(Data);
            Find(';');
            fin.get();
            pA->_Matrices.push_back(TempMatrix);
        }
        break;
    default:
        _TRACE_("Unknown Type" << Type << " ...");
        throwGgafCriticalException("X�t�@�C���ɑz�肵�Ȃ��s���� ANIMATION KEY �̃^�C�v������܂��B\n�Ώۃt�@�C��='"<<active_load_filename<<"'\n�Y���f�[�^='"<<Type<<"'"); //add tsuge
        break;
    }

    Find('}');
}

/***END*******************************************/

//////////////////////////////////////////////////////////
//
//       MAP MESH TO BONES
//
//////////////////////////////////////////////////////////
void ToolBox::IO_Model_X::MapMeshToBones(Frm::Bone* &pBone) {
    if (pBone->_MeshName.empty())
        pBone->_MeshName = _LoadMesh->_Name;

    _TRACE_("Bone" << pBone->_Name << "is linked to mesh" << pBone->_MeshName);

    if (!pBone->_Bones.empty())
        for (std::list<Frm::Bone*>::iterator i = pBone->_Bones.begin(); i
                != pBone->_Bones.end(); i++) {
            if ((*i)->_MeshName.empty()) {
                (*i)->_MeshName = pBone->_MeshName;
            }
            MapMeshToBones(*i);
        }
}

