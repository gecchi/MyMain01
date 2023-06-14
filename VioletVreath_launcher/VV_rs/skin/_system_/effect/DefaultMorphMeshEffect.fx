#include "GgafDx_World3DimEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::MorphMeshModel�p�V�F�[�_�[
// author : Masatoshi Tsuge
// date:2009/05/12
////////////////////////////////////////////////////////////////////////////////


/** �X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
float g_specular;
/** �X�y�L�����[�̋��x */
float g_specular_power;
/** �J�����i���_�j�̈ʒu�x�N�g�� */
float3 g_posCam_World;


float4x4 g_matWorld;  //World�ϊ��s��
int g_morph_target_num;  //���b�V���p�^�[����(���[�t�^�[�Q�b�g���j�A���ݖ��g�p
float g_weight1; //���[�t�^�[�Q�b�g�P�̏d��
float g_weight2; //���[�t�^�[�Q�b�g�Q�̏d��
float g_weight3; //���[�t�^�[�Q�b�g�R�̏d��
float g_weight4; //���[�t�^�[�Q�b�g�S�̏d��
float g_weight5; //���[�t�^�[�Q�b�g�T�̏d��
float g_weight6; //���[�t�^�[�Q�b�g�U�̏d��
//float g_weight7; //���[�t�^�[�Q�b�g�V�̏d��

float3 g_vecLightFrom_World; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float g_tex_blink_power;
float g_tex_blink_threshold;

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj   : POSITION;
    float2 uv              : TEXCOORD0;
    float4 color           : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   // ���[���h�ϊ������@��
    float3 vecEye_World    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
};


///////////////////////////////////////////////////////////////////////////

//���[�t�^�[�Q�b�g�Ȃ�
OUT_VS VS_DefaultMorphMesh0(
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0   // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;
    //���_�v�Z
    const float4 posModel_World = mul(prm_posPrimary_Local, g_matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv0;  //���̂܂�

    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormalPrimary_Local, g_matWorld));
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
    float refl_power = dot(out_vs.vecNormal_World, -g_vecLightFrom_World);
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse;
    //�u���_���J�������_�v�����x�N�g��
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = g_colMaterialDiffuse.a;
    //�������̕\�����@�B
    if (g_fog_starts_far_rate < 0.0) {
        //���̏ꍇ�A�ǂ�ȉ����ł��\������
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*0.999; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    }

    return out_vs;
}

//���[�t�^�[�Q�b�g�P��
OUT_VS VS_DefaultMorphMesh1(
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1     // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
) {
//	OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , g_weight1);
    }

    return VS_DefaultMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}


//���[�t�^�[�Q�b�g�Q��
OUT_VS VS_DefaultMorphMesh2(
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2     // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
) {
//	OUT_VS out_vs = (OUT_VS)0;

    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , g_weight2);
    }
    return VS_DefaultMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�R��
OUT_VS VS_DefaultMorphMesh3(
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2,    // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
    float4 prm_posMorphTarget3_Local  : POSITION3,  // ���f���̃��[�t�^�[�Q�b�g3���_
    float3 prm_vecNormal3_Local       : NORMAL3     // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , g_weight3);
    }

    return VS_DefaultMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�S��
OUT_VS VS_DefaultMorphMesh4(
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2,    // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
    float4 prm_posMorphTarget3_Local  : POSITION3,  // ���f���̃��[�t�^�[�Q�b�g3���_
    float3 prm_vecNormal3_Local       : NORMAL3,    // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
    float4 prm_posMorphTarget4_Local  : POSITION4,  // ���f���̃��[�t�^�[�Q�b�g4���_
    float3 prm_vecNormal4_Local    : NORMAL4     // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget4_Local, g_weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal4_Local     , g_weight4);
    }
    return VS_DefaultMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�T��
OUT_VS VS_DefaultMorphMesh5(
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2,    // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
    float4 prm_posMorphTarget3_Local  : POSITION3,  // ���f���̃��[�t�^�[�Q�b�g3���_
    float3 prm_vecNormal3_Local       : NORMAL3,    // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
    float4 prm_posMorphTarget4_Local  : POSITION4,  // ���f���̃��[�t�^�[�Q�b�g4���_
    float3 prm_vecNormal4_Local    : NORMAL4,    // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
    float4 prm_posMorphTarget5_Local  : POSITION5,  // ���f���̃��[�t�^�[�Q�b�g5���_
    float3 prm_vecNormal5_Local       : NORMAL5     // ���f���̃��[�t�^�[�Q�b�g5���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget4_Local, g_weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal4_Local     , g_weight4);
    }
    if (g_weight5 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget5_Local, g_weight5);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal5_Local     , g_weight5);
    }
    return VS_DefaultMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}

//���[�t�^�[�Q�b�g�U��
OUT_VS VS_DefaultMorphMesh6(
    float4 prm_posPrimary_Local       : POSITION0,  // ���f���̒��_
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // ���f���̒��_�̖@��
    float2 prm_uv0                    : TEXCOORD0,  // ���f���̒��_��UV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // ���f���̃��[�t�^�[�Q�b�g1���_
    float3 prm_vecNormal1_Local       : NORMAL1,    // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
    float4 prm_posMorphTarget2_Local  : POSITION2,  // ���f���̃��[�t�^�[�Q�b�g2���_
    float3 prm_vecNormal2_Local       : NORMAL2,    // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
    float4 prm_posMorphTarget3_Local  : POSITION3,  // ���f���̃��[�t�^�[�Q�b�g3���_
    float3 prm_vecNormal3_Local       : NORMAL3,    // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
    float4 prm_posMorphTarget4_Local  : POSITION4,  // ���f���̃��[�t�^�[�Q�b�g4���_
    float3 prm_vecNormal4_Local    : NORMAL4,    // ���f���̃��[�t�^�[�Q�b�g4���_�̖@��
    float4 prm_posMorphTarget5_Local  : POSITION5,  // ���f���̃��[�t�^�[�Q�b�g5���_
    float3 prm_vecNormal5_Local       : NORMAL5,    // ���f���̃��[�t�^�[�Q�b�g5���_�̖@��
    float4 prm_posMorphTarget6_Local  : POSITION6,  // ���f���̃��[�t�^�[�Q�b�g6���_
    float3 prm_vecNormal6_Local       : NORMAL6     // ���f���̃��[�t�^�[�Q�b�g6���_�̖@��
) {
    //���_���@���u�����h
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, g_weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, g_weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, g_weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget4_Local, g_weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal4_Local     , g_weight4);
    }
    if (g_weight5 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget5_Local, g_weight5);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal5_Local     , g_weight5);
    }
    if (g_weight6 != 0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget6_Local, g_weight6);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal6_Local     , g_weight6);
    }
    return VS_DefaultMorphMesh0(posModel_Local, vecNormal_Local, prm_uv0);
}


float4 PS_DefaultMorphMesh(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 colOut = (colTex2D * prm_color) + s;
    //Blinker���l��
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }
    colOut.a = prm_color.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    const float4 colTex2D  = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex2D * prm_color * FLUSH_COLOR;
    colOut *= g_alpha_master;
    return 	colOut;
}

technique DefaultMorphMeshTechnique
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh0();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh1();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh2();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh3();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh4();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh5();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh6();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }
}


technique DestBlendOne
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh0();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh1();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh2();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh3();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh4();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh5();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh6();
        PixelShader  = compile PS_VERSION PS_DefaultMorphMesh();
    }

//	//���[�t�^�[�Q�b�g�V��
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //���Z����
//		VertexShader = compile VS_VERSION VS_DefaultMorphMesh7();
//		PixelShader  = compile PS_VERSION PS_DestBlendOne();
//	}

}

technique Flush
{
    //���[�t�^�[�Q�b�g����
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh0();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�P��
    pass P1 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh1();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�Q��
    pass P2 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh2();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�R��
    pass P3 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh3();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�S��
    pass P4 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh4();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�T��
    pass P5 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh5();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //���[�t�^�[�Q�b�g�U��
    pass P6 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMorphMesh6();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

//	//���[�t�^�[�Q�b�g�V��
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //���Z����
//		VertexShader = compile VS_VERSION VS_DefaultMorphMesh7();
//		PixelShader  = compile PS_VERSION PS_Flush();
//	}

}
