#include "GgafDx_World3DimEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// WallAAPrismActor�p�V�F�[�_�[
// �y�T�v�z
// �O�ǃv���Y���̕`����s���B
// ���_�o�b�t�@�ɁA�O�ǃv���Y����񂪁A10���J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� �`��ŁA�ő�
// 10�I�u�W�F�N�g�܂ŕ`��B��������_���B
// author : Masatoshi Tsuge
// date:2011/01/10
////////////////////////////////////////////////////////////////////////////////
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_wall_dep;    //�ǃu���b�N�̒����iX���W�������j
float g_wall_height; //�ǃu���b�N�̍����iY���W�������j
float g_wall_width;  //�ǃu���b�N�̕��iZ���W������)
int g_pos_info;

// ���C�g�̕���
float3 g_vecLightFrom_World;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j
float4 g_colLightDiffuse;

//���[���h�ϊ��s��
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
float4x4 g_matWorld016;
float4x4 g_matWorld017;
//float4x4 g_matWorld018;
//float4x4 g_matWorld019;
//float4x4 g_matWorld020;

#define POS_PRISM_xx_NN    1
#define POS_PRISM_xx_NP    2
#define POS_PRISM_xx_PN    4
#define POS_PRISM_xx_PP    8
#define POS_PRISM_XY_xx    16
#define POS_PRISM_YZ_xx    32
#define POS_PRISM_ZX_xx    64

//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS VS_WallAAPrism(
      float4 prm_posModel_Local    : POSITION,      // ���f���̒��_
      float  prm_object_index  : PSIZE , // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���j
      float3 prm_vecNormal_Local : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
    OUT_VS out_vs = (OUT_VS)0;
    //���[���h�ϊ��s������蓖�Ă�
    const int index = (int)prm_object_index;
    float4x4 matWorld;
    if (index == 0) {
        matWorld = g_matWorld001;
    } else if (index == 1) {
        matWorld = g_matWorld002;
    } else if (index == 2) {
        matWorld = g_matWorld003;
    } else if (index == 3) {
        matWorld = g_matWorld004;
    } else if (index == 4) {
        matWorld = g_matWorld005;
    } else if (index == 5) {
        matWorld = g_matWorld006;
    } else if (index == 6) {
        matWorld = g_matWorld007;
    } else if (index == 7) {
        matWorld = g_matWorld008;
    } else if (index == 8) {
        matWorld = g_matWorld009;
    } else if (index == 9) {
        matWorld = g_matWorld010;
//	} else if (index == 10) {
//		matWorld = g_matWorld011;
//	} else if (index == 11) {
//		matWorld = g_matWorld012;
//	} else if (index == 12) {
//		matWorld = g_matWorld013;
//	} else if (index == 13) {
//		matWorld = g_matWorld014;
//	} else if (index == 14) {
//		matWorld = g_matWorld015;
//	} else if (index == 15) {
//		matWorld = g_matWorld016;
//	} else if (index == 16) {
//		matWorld = g_matWorld017;
//	} else if (index == 17) {
//		matWorld = g_matWorld018;
//	} else if (index == 18) {
//		matWorld = g_matWorld019;
    } else {
        matWorld = g_matWorld011;
    }
    //�`��ʔԍ���񂪁A���[���h�ϊ��s���matWorld._14 �ɖ��ߍ��܂�Ă���
    int draw_face = matWorld._14;
    int pos_info = matWorld._24;
    //���̍s��l�ɖ߂��Ă���
    matWorld._14 = 0;
    matWorld._24 = 0; //���̍s��l�ɖ߂��Ă���

    //UV�ɂ��ǂ̖ʂ̒��_�����f���A
    //�`��s�v�Ȗʂ̒��_�̏ꍇ�͉��Ƃ�����i�W�I���g���V�F�[�_�[�g�������G�j

    //draw_face�͕Ǖ����Ƀr�b�g�������Ă���
    //&b 00abcdef
    //
    //���}��BOX�̓W�J������Ԃ̐}
    //
    //                   ^y
    //              z��  |
    //                 \ |
    //                  c|
    // ----���@��--- a b d f ---- -> x
    //                   |e
    //                   | \
    //                   |  \
    //  u v
    // (0,0)      0.25                     ��u
    //       +------+------+------+------+
    //       |      |        Z+          |
    //       |      |       ��c          |
    //  0.25 +  X+  +--------------------+
    //       | ��f  |        Y-          |
    //       |      |       ��d          |
    //   0.5 +------+--------------------+
    //       |      |        Y+          |
    //       |      |       ��a          |
    //  0.75 +  X-  +--------------------+
    //       | ��b  |        Z-          |
    //       |      |       ��e          |
    //       +------+------+------+------+
    //    ��                                (1,1)
    //    v

    //                          00abcdef
      if (draw_face >= 32) {  //&b00100000
        draw_face -= 32;
    } else {
        //���(��a)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.5  < prm_uv.y && prm_uv.y < 0.75 )
        {
            return out_vs;
        }
    }

    //                          00abcdef
      if (draw_face >= 16) {  //&b00010000
        draw_face -= 16;
    } else {
        //����(��b)���`��s�v�̏ꍇ
        if (                   prm_uv.x < 0.25 &&
            0.5  < prm_uv.y                       )
        {
            return out_vs;
        }
    }
    //                          00abcdef
      if (draw_face >= 8) {   //&b00001000
        draw_face -= 8;
    } else {
        //������(��c)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
                               prm_uv.y < 0.25 )
        {
            return out_vs;
        }
    }
    //                          00abcdef
       if (draw_face >= 4) {   //&b00000100
        draw_face -= 4;
    } else {
        //���(��d)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.25 < prm_uv.y && prm_uv.y < 0.5 )
        {
            return out_vs;
        }
    }
    //                          00abcdef
      if (draw_face >= 2) {   //&b00000010
        draw_face -= 2;
    } else {
        //�E����(��e)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.75 < prm_uv.y                    )
        {
            return out_vs;
        }
    }
    //                          00abcdef
      if (draw_face >= 1) {   //&b00000001
       // draw_face -= 1;
    } else {
        //����������(��f)���`��s�v�̏ꍇ
        if (                    prm_uv.x < 0.25 &&
                                prm_uv.y < 0.5    )
        {
            return out_vs;
        }
    }

    //BOX�̂P�ʂ𖳗������ăv���Y���^�ɕό`������
    float ah,fh;
    if (pos_info >= POS_PRISM_ZX_xx) {
        //�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
        // ZX �� XZ���ʂƌ���
        pos_info -= POS_PRISM_ZX_xx;
        ah = g_wall_width / g_wall_dep / 2.0; //�X�� z/x �i�X�� x/z �ł͂Ȃ��āj
        //ah = g_wall_height / g_wall_dep / 2.0; //�X�� y/x
        fh = g_wall_dep/2.0;
        if (pos_info == POS_PRISM_xx_PP) {
            prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+fh)/g_wall_dep))       - ((prm_posModel_Local.x-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_PN) {
            prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) + ((prm_posModel_Local.x+fh)*ah);
        } else if (pos_info == POS_PRISM_xx_NP) {
            prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+fh)/g_wall_dep))       + ((prm_posModel_Local.x-fh)*ah);
        } else { //if (pos_info == POS_PRISM_xx_NN) {
            prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) - ((prm_posModel_Local.x+fh)*ah);
        }
    } else if (pos_info >= POS_PRISM_YZ_xx) {
        //�{Z -Z �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
        pos_info -= POS_PRISM_YZ_xx;
        ah = g_wall_height / g_wall_width / 2.0; //�X�� y/z
        fh = g_wall_width/2.0;                   //�X����
        if (pos_info == POS_PRISM_xx_PP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+fh)/g_wall_width))       - ((prm_posModel_Local.z-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_PN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+fh)/g_wall_width))) + ((prm_posModel_Local.z+fh)*ah);
        } else if (pos_info == POS_PRISM_xx_NP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+fh)/g_wall_width))       + ((prm_posModel_Local.z-fh)*ah);
        } else { //if (pos_info == POS_PRISM_xx_NN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+fh)/g_wall_width))) - ((prm_posModel_Local.z+fh)*ah);
        }
    } else { //if (pos_info >= POS_PRISM_XY_xx) {
        //�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
        pos_info -= POS_PRISM_XY_xx;
        ah = g_wall_height / g_wall_dep / 2.0; //�X�� y/x
        fh = g_wall_dep/2.0;                   //�X����
        if (pos_info == POS_PRISM_xx_PP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))       - ((prm_posModel_Local.x-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_PN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))       + ((prm_posModel_Local.x-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_NP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) + ((prm_posModel_Local.x+fh)*ah);
        } else { //if (pos_info == POS_PRISM_xx_NN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) - ((prm_posModel_Local.x+fh)*ah);
        }
    }
    //����
    //(prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))   �E�E�E ��[���L���b�Ƃ܂Ƃ߂�v�Z
    //+ ((prm_posModel_Local.x-fh)*ah);                      �E�E�E ��[�𐅕��ɂ���v�Z

    //World*View*�ˉe�ϊ�
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);

    //UV�͂��̂܂�
    out_vs.uv = prm_uv;

    //���_�J���[�v�Z

    //�@���� World �ϊ����Đ��K��
    float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));
    vecNormal_World.x+=0.5; //�l0.5�͕ǖʂɂ����������𓖂Ă邽��
                   //���C�g�x�N�g���� XYZ=0.819232,-0.573462,0
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
    float refl_power = dot(vecNormal_World, float3(-0.819232,0.573462,0));
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g���� ���l�������J���[�쐬�B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power));// * �}�e���A���F����colMaterialDiffuse;

    //���t�H�O
    //out_vs.color.a = colMaterialDiffuse.a;
//    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
//        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
//    }

    if (out_vs.posModel_Proj.z > out_vs.posModel_Proj.w) {
        out_vs.posModel_Proj.z = out_vs.posModel_Proj.w; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
    }
    //���@����O�̓�
    if ( out_vs.posModel_Proj.z < g_distance_AlphaTarget) {
        out_vs.color.a = (out_vs.posModel_Proj.z + 1.0)  / (g_distance_AlphaTarget*2);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
    return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 PS_WallAAPrism(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    if (prm_color.a == 0) {
        discard;
    }
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color;

    //Blinker���l��
    colOut = getBlinkColor(colOut, colTex);
    //�}�X�^�[��
    colOut.a *= g_alpha_master;
    return colOut;
}


float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique WallAAPrismTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_WallAAPrism();
        PixelShader  = compile PS_VERSION PS_WallAAPrism();
    }
}

technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //���Z����
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_WallAAPrism();
        PixelShader  = compile PS_VERSION PS_WallAAPrism();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_WallAAPrism();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
