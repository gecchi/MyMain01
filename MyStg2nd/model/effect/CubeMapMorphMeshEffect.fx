#include "GgafEffectConst.fx"
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MorphMeshModel�p�V�F�[�_�[
// author : Masatoshi Tsuge
// date:2009/05/12
////////////////////////////////////////////////////////////////////////////////
/** �J������World�ʒu */
//float3 pos_camera;

//�G���[���o��̂łƂ肠�����錾
/** �X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
float g_specular;
/** �X�y�L�����[�̋��x */
float g_specular_power;
/** �J�����i���_�j�̈ʒu�x�N�g�� */
float3 g_posCam;



float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��
int g_morph_target_num;  //���b�V���p�^�[����(���[�t�^�[�Q�b�g���j�A���ݖ��g�p
float g_weight1; //���[�t�^�[�Q�b�g�P�̏d��
float g_weight2; //���[�t�^�[�Q�b�g�Q�̏d��
float g_weight3; //���[�t�^�[�Q�b�g�R�̏d��
float g_weight4; //���[�t�^�[�Q�b�g�S�̏d��
float g_weight5; //���[�t�^�[�Q�b�g�T�̏d��
float g_weight6; //���[�t�^�[�Q�b�g�U�̏d��
//float g_weight7; //���[�t�^�[�Q�b�g�V�̏d��

float3 g_vecLightDirection; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
//struct OUT_VS
//{
//    float4 pos    : POSITION;
//	float2 uv     : TEXCOORD0;
//	float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
//};

struct OUT_VS {
    float4 pos   : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;
    float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
    float3 cam    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
    //float3 viewVecW: TEXCOORD1;  	// ���[���h��Ԃł̎����x�N�g��
};

///////////////////////////////////////////////////////////////////////////

//���[�t�^�[�Q�b�g�Ȃ�
OUT_VS GgafDx9VS_CubeMapMorphMesh0(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0       // ���f���̒��_��UV

) {
    OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
    float4 posWorld = mul(prm_pos0, g_matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv0;  //���̂܂�
    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.normal = normalize(mul(prm_normal0, g_matWorld));     
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
    //�u���_���J�������_�v�����x�N�g��                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.col.a = g_colMaterialDiffuse.a;
    //���t�H�O
    if (out_vs.pos.z > (g_zf*0.9)*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
        out_vs.col.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
    } 
    //�}�X�^�[��
    out_vs.col.a *= g_alpha_master;
	return out_vs;







//    //���_�v�Z
//    out_vs.pos = mul(prm_pos0, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//    out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(prm_normal0, g_matWorld));
//
////	//���_�v�Z
////	out_vs.pos = mul( mul(mul( prm_pos0, g_matWorld ), g_matView ), g_matProj);//
////    //�@���v�Z
////    out_vs.normal = normalize(mul(prm_normal0, g_matWorld)); 	//�@���� World �ϊ����Đ��K��
////	//UV�͂��̂܂�
////	out_vs.uv = prm_uv0;
//    return out_vs;
}

//���[�t�^�[�Q�b�g�P��
OUT_VS GgafDx9VS_CubeMapMorphMesh1(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1         // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��

) {
//    OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 pos = prm_pos0;
    float3 normal = prm_normal0;
    if (g_weight1 != 0 ) {
        pos += ((prm_pos1 - prm_pos0) * g_weight1);
        normal = lerp(normal, prm_normal1, g_weight1);
    }
    return GgafDx9VS_CubeMapMorphMesh0(pos, normal,prm_uv0);

//    //���_�v�Z
//    out_vs.pos = mul(pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//    out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(normal, g_matWorld));
//
////	//���_�o�͐ݒ�
////	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
////	//�@���o�͐ݒ�
////	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
////	//UV�͂��̂܂�
////	out_vs.uv = prm_uv0;
//
//    return out_vs;
}


//���[�t�^�[�Q�b�g�Q��
OUT_VS GgafDx9VS_CubeMapMorphMesh2(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
      float3 prm_normal2 : NORMAL2         // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 pos = prm_pos0;
    float3 normal = prm_normal0;
    if (g_weight1 != 0 ) {
        pos += ((prm_pos1 - prm_pos0) * g_weight1);
        normal = lerp(normal, prm_normal1, g_weight1);
    }
    if (g_weight2 != 0 ) {
        pos += ((prm_pos2 - prm_pos0) * g_weight2);
        normal = lerp(normal, prm_normal2, g_weight2);
    }
    return GgafDx9VS_CubeMapMorphMesh0(pos, normal,prm_uv0);

//    //���_�v�Z
//    out_vs.pos = mul(pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//    out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(normal, g_matWorld));
//
//
////	//���_�o�͐ݒ�
////	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
////	//�@���o�͐ݒ�
////	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
////	//UV�͂��̂܂�
////	out_vs.uv = prm_uv0;
//
//    return out_vs;
}

//���[�t�^�[�Q�b�g�R��
OUT_VS GgafDx9VS_CubeMapMorphMesh3(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
      float3 prm_normal2 : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
      float4 prm_pos3    : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
      float3 prm_normal3 : NORMAL3         // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 pos = prm_pos0;
    float3 normal = prm_normal0;
    if (g_weight1 != 0 ) {
        pos += ((prm_pos1 - prm_pos0) * g_weight1);
        normal = lerp(normal, prm_normal1, g_weight1);
    }
    if (g_weight2 != 0 ) {
        pos += ((prm_pos2 - prm_pos0) * g_weight2);
        normal = lerp(normal, prm_normal2, g_weight2);
    }
    if (g_weight3 != 0 ) {
        pos += ((prm_pos3 - prm_pos0) * g_weight3);
        normal = lerp(normal, prm_normal3, g_weight3);
    }
    return GgafDx9VS_CubeMapMorphMesh0(pos, normal,prm_uv0);

//    //���_�v�Z
//    out_vs.pos = mul(pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//    out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(normal, g_matWorld));
//
////	//���_�o�͐ݒ�
////	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
////	//�@���o�͐ݒ�
////	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
////	//UV�͂��̂܂�
////	out_vs.uv = prm_uv0;
//
//    return out_vs;
}

//���[�t�^�[�Q�b�g�S��
OUT_VS GgafDx9VS_CubeMapMorphMesh4(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
      float3 prm_normal2 : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
      float4 prm_pos3    : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
      float3 prm_normal3 : NORMAL3,        // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
      float4 prm_pos4    : POSITION4,      // ���f���̃��[�t�^�[�Q�b�g4���_
      float3 prm_normal4 : NORMAL4         // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 pos = prm_pos0;
    float3 normal = prm_normal0;
    if (g_weight1 != 0 ) {
        pos += ((prm_pos1 - prm_pos0) * g_weight1);
        normal = lerp(normal, prm_normal1, g_weight1);
    }
    if (g_weight2 != 0 ) {
        pos += ((prm_pos2 - prm_pos0) * g_weight2);
        normal = lerp(normal, prm_normal2, g_weight2);
    }
    if (g_weight3 != 0 ) {
        pos += ((prm_pos3 - prm_pos0) * g_weight3);
        normal = lerp(normal, prm_normal3, g_weight3);
    }
    if (g_weight4 != 0 ) {
        pos += ((prm_pos4 - prm_pos0) * g_weight4);
        normal = lerp(normal, prm_normal4, g_weight4);
    }
    return GgafDx9VS_CubeMapMorphMesh0(pos, normal,prm_uv0);

//    //���_�v�Z
//    out_vs.pos = mul(pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//    out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(normal, g_matWorld));
//
////
////	//���_�o�͐ݒ�
////	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
////	//�@���o�͐ݒ�
////	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
////	//UV�͂��̂܂�
////	out_vs.uv = prm_uv0;
//
//    return out_vs;
}

//���[�t�^�[�Q�b�g�T��
OUT_VS GgafDx9VS_CubeMapMorphMesh5(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
      float3 prm_normal2 : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
      float4 prm_pos3    : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
      float3 prm_normal3 : NORMAL3,        // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
      float4 prm_pos4    : POSITION4,      // ���f���̃��[�t�^�[�Q�b�g4���_
      float3 prm_normal4 : NORMAL4,        // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
      float4 prm_pos5    : POSITION5,      // ���f���̃��[�t�^�[�Q�b�g5���_
      float3 prm_normal5 : NORMAL5         // ���f���̃��[�t�^�[�Q�b�g5���_�̖@��
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 pos = prm_pos0;
    float3 normal = prm_normal0;
    if (g_weight1 != 0 ) {
        pos += ((prm_pos1 - prm_pos0) * g_weight1);
        normal = lerp(normal, prm_normal1, g_weight1);
    }
    if (g_weight2 != 0 ) {
        pos += ((prm_pos2 - prm_pos0) * g_weight2);
        normal = lerp(normal, prm_normal2, g_weight2);
    }
    if (g_weight3 != 0 ) {
        pos += ((prm_pos3 - prm_pos0) * g_weight3);
        normal = lerp(normal, prm_normal3, g_weight3);
    }
    if (g_weight4 != 0 ) {
        pos += ((prm_pos4 - prm_pos0) * g_weight4);
        normal = lerp(normal, prm_normal4, g_weight4);
    }
    if (g_weight5 != 0 ) {
        pos += ((prm_pos5 - prm_pos0) * g_weight5);
        normal = lerp(normal, prm_normal5, g_weight5);
    }
    return GgafDx9VS_CubeMapMorphMesh0(pos, normal,prm_uv0);

//    //���_�v�Z
//    out_vs.pos = mul(pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//    out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(normal, g_matWorld));
//
//
//
////	//���_�o�͐ݒ�
////	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
////	//�@���o�͐ݒ�
////	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
////	//UV�͂��̂܂�
////	out_vs.uv = prm_uv0;
//
//    return out_vs;
}

//���[�t�^�[�Q�b�g�U��
OUT_VS GgafDx9VS_CubeMapMorphMesh6(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
      float3 prm_normal2 : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
      float4 prm_pos3    : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
      float3 prm_normal3 : NORMAL3,        // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
      float4 prm_pos4    : POSITION4,      // ���f���̃��[�t�^�[�Q�b�g4���_
      float3 prm_normal4 : NORMAL4,        // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
      float4 prm_pos5    : POSITION5,      // ���f���̃��[�t�^�[�Q�b�g5���_
      float3 prm_normal5 : NORMAL5,        // ���f���̃��[�t�^�[�Q�b�g5���_�̖@��
      float4 prm_pos6    : POSITION6,      // ���f���̃��[�t�^�[�Q�b�g6���_
      float3 prm_normal6 : NORMAL6         // ���f���̃��[�t�^�[�Q�b�g6���_�̖@��

) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 pos = prm_pos0;
    float3 normal = prm_normal0;
    if (g_weight1 != 0 ) {
        pos += ((prm_pos1 - prm_pos0) * g_weight1);
        normal = lerp(normal, prm_normal1, g_weight1);
    }
    if (g_weight2 != 0 ) {
        pos += ((prm_pos2 - prm_pos0) * g_weight2);
        normal = lerp(normal, prm_normal2, g_weight2);
    }
    if (g_weight3 != 0 ) {
        pos += ((prm_pos3 - prm_pos0) * g_weight3);
        normal = lerp(normal, prm_normal3, g_weight3);
    }
    if (g_weight4 != 0 ) {
        pos += ((prm_pos4 - prm_pos0) * g_weight4);
        normal = lerp(normal, prm_normal4, g_weight4);
    }
    if (g_weight5 != 0 ) {
        pos += ((prm_pos5 - prm_pos0) * g_weight5);
        normal = lerp(normal, prm_normal5, g_weight5);
    }
    if (g_weight6 != 0 ) {
        pos += ((prm_pos6 - prm_pos0) * g_weight6);
        normal = lerp(normal, prm_normal6, g_weight6);
    }
    return GgafDx9VS_CubeMapMorphMesh0(pos, normal,prm_uv0);

//    //���_�v�Z
//    out_vs.pos = mul(pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//    out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(normal, g_matWorld));
//
//
////	//���_�o�͐ݒ�
////	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
////	//�@���o�͐ݒ�
////	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
////	//UV�͂��̂܂�
////	out_vs.uv = prm_uv0;
//
//    return out_vs;
}

////���[�t�^�[�Q�b�g�V��
//OUT_VS GgafDx9VS_CubeMapMorphMesh7(
//      float4 prm_pos0    : POSITION0,      // ���f���̒��_
//      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
//      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
//      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
//      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
//      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
//      float3 prm_normal2 : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
//      float4 prm_pos3    : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
//      float3 prm_normal3 : NORMAL3,        // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
//      float4 prm_pos4    : POSITION4,      // ���f���̃��[�t�^�[�Q�b�g4���_
//      float3 prm_normal4 : NORMAL4,        // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
//      float4 prm_pos5    : POSITION5,      // ���f���̃��[�t�^�[�Q�b�g5���_
//      float3 prm_normal5 : NORMAL5,        // ���f���̃��[�t�^�[�Q�b�g5���_�̖@��
//      float4 prm_pos6    : POSITION6,      // ���f���̃��[�t�^�[�Q�b�g6���_
//      float3 prm_normal6 : NORMAL6,        // ���f���̃��[�t�^�[�Q�b�g6���_�̖@��
//      float4 prm_pos7    : POSITION7,      // ���f���̃��[�t�^�[�Q�b�g7���_
//      float3 prm_normal7 : NORMAL7         // ���f���̃��[�t�^�[�Q�b�g7���_�̖@��
//) {
//	OUT_VS out_vs = (OUT_VS)0;
//
//	//���_���@���u�����h
//	float4 pos = prm_pos0;
//	float3 normal = prm_normal0;
//	if (g_weight1 != 0 ) {
//		pos += ((prm_pos1 - prm_pos0) * g_weight1);
//		normal = lerp(normal, prm_normal1, g_weight1);
//	}
//	if (g_weight2 != 0 ) {
//		pos += ((prm_pos2 - prm_pos0) * g_weight2);
//		normal = lerp(normal, prm_normal2, g_weight2);
//	}
//	if (g_weight3 != 0 ) {
//		pos += ((prm_pos3 - prm_pos0) * g_weight3);
//		normal = lerp(normal, prm_normal3, g_weight3);
//	}
//	if (g_weight4 != 0 ) {
//		pos += ((prm_pos4 - prm_pos0) * g_weight4);
//		normal = lerp(normal, prm_normal4, g_weight4);
//	}
//	if (g_weight5 != 0 ) {
//		pos += ((prm_pos5 - prm_pos0) * g_weight5);
//		normal = lerp(normal, prm_normal5, g_weight5);
//	}
//	if (g_weight6 != 0 ) {
//		pos += ((prm_pos6 - prm_pos0) * g_weight6);
//		normal = lerp(normal, prm_normal6, g_weight6);
//	}
//	if (g_weight7 != 0 ) {
//		pos += ((prm_pos7 - prm_pos0) * g_weight7);
//		normal = lerp(normal, prm_normal7, g_weight7);
//	}
//	//���_�o�͐ݒ�
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
//	//�@���o�͐ݒ�
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
//	//UV�͂��̂܂�
//	out_vs.uv = prm_uv0;
//
//	return out_vs;
//}

//float4 GgafDx9PS_CubeMapMorphMesh(
//     float3 prm_normal: TEXCOORD0,
//     float3 prm_viewVecW: TEXCOORD1
//) : COLOR  {


float4 GgafDx9PS_CubeMapMorphMesh(       
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);
    float4 out_color = tex_color * prm_col; 
	float3 vReflect = reflect( -prm_cam, prm_normal );
	float4 cube_tex_color = texCUBE(CubeMapTextureSampler, vReflect);
    //Blinker���l��
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	} 
	return out_color + (cube_tex_color*0.5) + s;
	
//    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
//    float power = max(dot(prm_normal, -g_vecLightDirection ), 0);
//
//    float3 vReflect = reflect( -prm_cam, prm_normal );
//    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
//
//    //���C�g�����A���C�g�F�A�}�e���A���F�A�e�N�X�`���F���l�������F�쐬�B
//    float4 out_color = g_colLightDiffuse * g_colMaterialDiffuse * tex_color * power;
//    //Ambient�F�����Z�B�}�e���A����Ambien���ːF�́A�}�e���A����Diffuse���ːF�Ɠ����F�Ƃ���B
//    out_color =  (g_colLightAmbient * g_colMaterialDiffuse * tex_color) + out_color;
//    if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
//        out_color.rgb *= g_tex_blink_power;
//    }
//    //���v�Z�A���͖@������у��C�g�����Ɉˑ����Ȃ����Ƃ���̂ŕʌv�Z�B�Œ�̓��C�g���F���l�����邪�A�{�V�F�[�_�[�̓��C�g���͖����B
//    out_color.a = g_colMaterialDiffuse.a * tex_color.a * g_alpha_master;
//
//    return out_color * float4(2.0, 2.0, 2.0, 1.0); //�S�̓I�ɖ��邭����;
}

//float4 PS_DestBlendOne(
//     float3 prm_normal: TEXCOORD0,
//	 float3 prm_viewVecW: TEXCOORD1
//) : COLOR  {
// 	float3 vReflect = reflect( prm_viewVecW, prm_normal );
//    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
//	tex_color.a = tex_color.a * g_alpha_master;
//	return 	tex_color;
//}

float4 PS_Flush(
     float3 prm_normal: TEXCOORD0,
     float3 prm_viewVecW: TEXCOORD1
) : COLOR  {
     float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect) * float4(7.0, 7.0, 7.0, 1.0);
    tex_color.a = tex_color.a * g_alpha_master;
    return 	tex_color;
}

technique CubeMapMorphMeshTechnique
{
    //�u���b�V���W���V�F�[�_�[�v
    //���b�V����`�悷��
    //�y�l�������v�f�z
    //--- VS ---
    //�E���_�� World�AView�A�ˉe �ϊ�
    //�E�@���� World�ϊ�
    //--- PS ---
    //�EDiffuse���C�g�F(���F�͖���)
    //�EAmbient���C�g�F(���F�͖���)
    //�E���s�����C�g����
    //�E�������C�g
    //�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
    //�E�I�u�W�F�N�g�̃e�N�X�`��
    //�E�I�u�W�F�N�g�̃}�e���A�����������iDiffuse���˃��ƃe�N�X�`�����̏�Z�j
    //�y�g�p�����z
    //�E�e�N�X�`�������݂�s0���W�X�^�Ƀo�C���h����Ă��邱�ƁB
    //�y�ݒ�p�����[�^�z
    // float g_weight1�`9       :   �d��1�`9(�K�v�ȃ^�[�Q�b�g������)
    // float4x4 g_matWorld		:	World�ϊ��s��
    // float4x4 g_matView		:	View�ϊ��s��
    // float4x4 g_matProj		:	�ˉe�ϊ��s��
    // float3 g_vecLightDirection	:	���C�g�̕���
    // float4 g_colLightAmbient	:	Ambien���C�g�F�i���ːF�j
    // float4 g_colLightDiffuse	:	Diffuse���C�g�F�i���ːF�j
    // float4 g_colMaterialDiffuse	:	�}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
    // s0���W�X�^				:	2D�e�N�X�`��

    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh0();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh1();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh2();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh3();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh4();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh5();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh6();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

//	//���[�t�^�[�Q�b�g�V��
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = InvSrcAlpha;
//		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh7();
//		PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
//	}
}


technique DestBlendOne
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh0();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh1();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh2();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh3();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh4();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh5();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh6();
        PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
    }

//	//���[�t�^�[�Q�b�g�V��
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //���Z����
//		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh7();
//		PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMorphMesh();
//	}

}

technique Flush
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh0();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh1();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh2();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh3();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh4();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh5();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh6();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

//	//���[�t�^�[�Q�b�g�V��
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //���Z����
//		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMorphMesh7();
//		PixelShader  = compile PS_VERSION PS_Flush();
//	}

}
