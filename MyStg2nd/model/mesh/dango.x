xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 245;
 -1.13740;1.58226;0.00000;,
 -0.70924;1.46182;-0.42816;,
 -1.13740;1.46182;-0.60550;,
 -0.53189;1.46182;0.00000;,
 -0.70924;1.46182;0.42816;,
 -1.13740;1.46182;0.60550;,
 -1.56555;1.46182;0.42816;,
 -1.74290;1.46182;0.00000;,
 -1.56555;1.46182;-0.42816;,
 -1.13740;1.46182;-0.60550;,
 -0.70924;1.46182;-0.42816;,
 -0.34627;1.11883;-0.79113;,
 -1.13740;1.11883;-1.11883;,
 -0.01858;1.11883;0.00000;,
 -0.34627;1.11883;0.79113;,
 -1.13740;1.11883;1.11883;,
 -1.92852;1.11883;0.79113;,
 -2.25623;1.11883;0.00000;,
 -1.92852;1.11883;-0.79113;,
 -1.13740;1.11883;-1.11883;,
 -0.10373;0.60550;-1.03366;,
 -1.13740;0.60550;-1.46182;,
 0.32441;0.60550;0.00000;,
 -0.10373;0.60550;1.03366;,
 -1.13740;0.60550;1.46182;,
 -2.17106;0.60550;1.03366;,
 -2.59920;0.60550;0.00000;,
 -2.17106;0.60550;-1.03366;,
 -1.13740;0.60550;-1.46182;,
 -0.01858;0.00000;-1.11883;,
 -1.13740;0.00000;-1.58226;,
 0.44486;0.00000;0.00000;,
 -0.01858;0.00000;1.11883;,
 -1.13740;0.00000;1.58226;,
 -2.25623;0.00000;1.11883;,
 -2.71965;0.00000;0.00000;,
 -2.25623;0.00000;-1.11883;,
 -1.13740;0.00000;-1.58226;,
 -0.10373;-0.60551;-1.03366;,
 -1.13740;-0.60551;-1.46182;,
 0.32441;-0.60551;-0.00000;,
 -0.10373;-0.60551;1.03366;,
 -1.13740;-0.60551;1.46182;,
 -2.17106;-0.60551;1.03366;,
 -2.59920;-0.60551;0.00000;,
 -2.17106;-0.60551;-1.03366;,
 -1.13740;-0.60551;-1.46182;,
 -0.34627;-1.11883;-0.79113;,
 -1.13740;-1.11883;-1.11883;,
 -0.01858;-1.11883;0.00000;,
 -0.34627;-1.11883;0.79113;,
 -1.13740;-1.11883;1.11883;,
 -1.92852;-1.11883;0.79113;,
 -2.25623;-1.11883;0.00000;,
 -1.92852;-1.11883;-0.79113;,
 -1.13740;-1.11883;-1.11883;,
 -0.70924;-1.46182;-0.42816;,
 -1.13740;-1.46182;-0.60550;,
 -0.53189;-1.46182;0.00000;,
 -0.70924;-1.46182;0.42816;,
 -1.13740;-1.46182;0.60550;,
 -1.56555;-1.46182;0.42816;,
 -1.74290;-1.46182;0.00000;,
 -1.56555;-1.46182;-0.42816;,
 -1.13740;-1.46182;-0.60550;,
 -1.13740;-1.58226;0.00000;,
 -1.13740;-1.58226;0.00000;,
 1.23599;1.58226;0.00000;,
 1.66415;1.46182;-0.42816;,
 1.23599;1.46182;-0.60550;,
 1.23599;1.58226;0.00000;,
 1.84149;1.46182;0.00000;,
 1.23599;1.58226;0.00000;,
 1.66415;1.46182;0.42816;,
 1.23599;1.58226;0.00000;,
 1.23599;1.46182;0.60550;,
 1.23599;1.58226;0.00000;,
 0.80783;1.46182;0.42816;,
 1.23599;1.58226;0.00000;,
 0.63048;1.46182;0.00000;,
 1.23599;1.58226;0.00000;,
 0.80783;1.46182;-0.42816;,
 1.23599;1.58226;0.00000;,
 1.23599;1.46182;-0.60550;,
 2.02712;1.11883;-0.79113;,
 1.23599;1.11883;-1.11883;,
 2.35482;1.11883;0.00000;,
 2.02712;1.11883;0.79113;,
 1.23599;1.11883;1.11883;,
 0.44486;1.11883;0.79113;,
 0.11716;1.11883;0.00000;,
 0.44486;1.11883;-0.79113;,
 1.23599;1.11883;-1.11883;,
 2.26965;0.60550;-1.03366;,
 1.23599;0.60550;-1.46182;,
 2.69780;0.60550;0.00000;,
 2.26965;0.60550;1.03366;,
 1.23599;0.60550;1.46182;,
 0.20233;0.60550;1.03366;,
 -0.22583;0.60550;0.00000;,
 0.20233;0.60550;-1.03366;,
 1.23599;0.60550;-1.46182;,
 2.35482;0.00000;-1.11883;,
 1.23599;0.00000;-1.58226;,
 2.81824;0.00000;0.00000;,
 2.35482;0.00000;1.11883;,
 1.23599;0.00000;1.58226;,
 0.11716;0.00000;1.11883;,
 -0.34627;0.00000;0.00000;,
 0.11716;0.00000;-1.11883;,
 1.23599;0.00000;-1.58226;,
 2.26965;-0.60551;-1.03366;,
 1.23599;-0.60551;-1.46182;,
 2.69780;-0.60551;-0.00000;,
 2.26965;-0.60551;1.03366;,
 1.23599;-0.60551;1.46182;,
 0.20233;-0.60551;1.03366;,
 -0.22583;-0.60551;0.00000;,
 0.20233;-0.60551;-1.03366;,
 1.23599;-0.60551;-1.46182;,
 2.02712;-1.11883;-0.79113;,
 1.23599;-1.11883;-1.11883;,
 2.35482;-1.11883;-0.00000;,
 2.02712;-1.11883;0.79113;,
 1.23599;-1.11883;1.11883;,
 0.44486;-1.11883;0.79113;,
 0.11716;-1.11883;-0.00000;,
 0.44486;-1.11883;-0.79113;,
 1.23599;-1.11883;-1.11883;,
 1.66415;-1.46182;-0.42816;,
 1.23599;-1.46182;-0.60550;,
 1.84149;-1.46182;-0.00000;,
 1.66415;-1.46182;0.42816;,
 1.23599;-1.46182;0.60550;,
 0.80783;-1.46182;0.42816;,
 0.63048;-1.46182;-0.00000;,
 0.80783;-1.46182;-0.42816;,
 1.23599;-1.46182;-0.60550;,
 1.23599;-1.58226;-0.00000;,
 1.23599;-1.58226;-0.00000;,
 1.23599;-1.58226;-0.00000;,
 1.23599;-1.58226;-0.00000;,
 1.23599;-1.58226;-0.00000;,
 1.23599;-1.58226;-0.00000;,
 1.23599;-1.58226;-0.00000;,
 1.23599;-1.58226;-0.00000;,
 -3.51078;1.58226;0.00000;,
 -3.08263;1.46182;-0.42816;,
 -3.51078;1.46182;-0.60550;,
 -3.51078;1.58226;0.00000;,
 -2.90528;1.46182;0.00000;,
 -3.51078;1.58226;0.00000;,
 -3.08263;1.46182;0.42816;,
 -3.51078;1.58226;0.00000;,
 -3.51078;1.46182;0.60550;,
 -3.51078;1.58226;0.00000;,
 -3.93894;1.46182;0.42816;,
 -3.51078;1.58226;0.00000;,
 -4.11628;1.46182;0.00000;,
 -3.51078;1.58226;0.00000;,
 -3.93894;1.46182;-0.42816;,
 -3.51078;1.58226;0.00000;,
 -3.51078;1.46182;-0.60550;,
 -2.71965;1.11883;-0.79113;,
 -3.51078;1.11883;-1.11883;,
 -2.39196;1.11883;0.00000;,
 -2.71965;1.11883;0.79113;,
 -3.51078;1.11883;1.11883;,
 -4.30191;1.11883;0.79113;,
 -4.62960;1.11883;0.00000;,
 -4.30191;1.11883;-0.79113;,
 -3.51078;1.11883;-1.11883;,
 -2.47713;0.60550;-1.03366;,
 -3.51078;0.60550;-1.46182;,
 -2.04897;0.60550;0.00000;,
 -2.47713;0.60550;1.03366;,
 -3.51078;0.60550;1.46182;,
 -4.54444;0.60550;1.03366;,
 -4.97260;0.60550;0.00000;,
 -4.54444;0.60550;-1.03366;,
 -3.51078;0.60550;-1.46182;,
 -2.39196;0.00000;-1.11883;,
 -3.51078;0.00000;-1.58226;,
 -1.92852;0.00000;0.00000;,
 -2.39196;0.00000;1.11883;,
 -3.51078;0.00000;1.58226;,
 -4.62960;0.00000;1.11883;,
 -5.09305;0.00000;0.00000;,
 -4.62960;0.00000;-1.11883;,
 -3.51078;0.00000;-1.58226;,
 -2.47713;-0.60551;-1.03366;,
 -3.51078;-0.60551;-1.46182;,
 -2.04897;-0.60551;0.00000;,
 -2.47713;-0.60551;1.03366;,
 -3.51078;-0.60551;1.46182;,
 -4.54444;-0.60551;1.03366;,
 -4.97260;-0.60551;0.00000;,
 -4.54444;-0.60551;-1.03366;,
 -3.51078;-0.60551;-1.46182;,
 -2.71965;-1.11883;-0.79113;,
 -3.51078;-1.11883;-1.11883;,
 -2.39196;-1.11883;0.00000;,
 -2.71965;-1.11883;0.79113;,
 -3.51078;-1.11883;1.11883;,
 -4.30191;-1.11883;0.79113;,
 -4.62960;-1.11883;0.00000;,
 -4.30191;-1.11883;-0.79113;,
 -3.51078;-1.11883;-1.11883;,
 -3.08263;-1.46182;-0.42816;,
 -3.51078;-1.46182;-0.60550;,
 -2.90528;-1.46182;0.00000;,
 -3.08263;-1.46182;0.42816;,
 -3.51078;-1.46182;0.60550;,
 -3.93894;-1.46182;0.42816;,
 -4.11628;-1.46182;0.00000;,
 -3.93894;-1.46182;-0.42816;,
 -3.51078;-1.46182;-0.60550;,
 -3.51078;-1.58226;0.00000;,
 -3.51078;-1.58226;0.00000;,
 -3.51078;-1.58226;0.00000;,
 -3.51078;-1.58226;0.00000;,
 -3.51078;-1.58226;0.00000;,
 -3.51078;-1.58226;0.00000;,
 -3.51078;-1.58226;0.00000;,
 -3.51078;-1.58226;0.00000;,
 -5.69815;0.07911;0.07911;,
 5.70256;0.07911;0.07911;,
 5.70256;0.07911;-0.07911;,
 -5.69815;0.07911;-0.07911;,
 -5.69815;0.07911;-0.07911;,
 5.70256;0.07911;-0.07911;,
 5.70256;-0.07911;-0.07911;,
 -5.69815;-0.07911;-0.07911;,
 -5.69815;-0.07911;-0.07911;,
 5.70256;-0.07911;-0.07911;,
 5.70256;-0.07911;0.07911;,
 -5.69815;-0.07911;0.07911;,
 -5.69815;-0.07911;0.07911;,
 5.70256;-0.07911;0.07911;,
 5.70256;0.07911;0.07911;,
 -5.69815;0.07911;0.07911;,
 5.70256;0.07911;0.07911;,
 5.70256;0.07911;-0.07911;,
 -5.69815;0.07911;0.07911;,
 -5.69815;0.07911;-0.07911;;
 
 198;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;9,10,11,12;,
 4;10,3,13,11;,
 4;3,4,14,13;,
 4;4,5,15,14;,
 4;5,6,16,15;,
 4;6,7,17,16;,
 4;7,8,18,17;,
 4;8,2,19,18;,
 4;12,11,20,21;,
 4;11,13,22,20;,
 4;13,14,23,22;,
 4;14,15,24,23;,
 4;15,16,25,24;,
 4;16,17,26,25;,
 4;17,18,27,26;,
 4;18,19,28,27;,
 4;21,20,29,30;,
 4;20,22,31,29;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;26,27,36,35;,
 4;27,28,37,36;,
 4;30,29,38,39;,
 4;29,31,40,38;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;35,36,45,44;,
 4;36,37,46,45;,
 4;39,38,47,48;,
 4;38,40,49,47;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;44,45,54,53;,
 4;45,46,55,54;,
 4;48,47,56,57;,
 4;47,49,58,56;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;53,54,63,62;,
 4;54,55,64,63;,
 3;57,56,65;,
 3;56,58,65;,
 3;58,59,66;,
 3;59,60,66;,
 3;60,61,66;,
 3;61,62,66;,
 3;62,63,66;,
 3;63,64,66;,
 3;67,68,69;,
 3;70,71,68;,
 3;72,73,71;,
 3;74,75,73;,
 3;76,77,75;,
 3;78,79,77;,
 3;80,81,79;,
 3;82,83,81;,
 4;69,68,84,85;,
 4;68,71,86,84;,
 4;71,73,87,86;,
 4;73,75,88,87;,
 4;75,77,89,88;,
 4;77,79,90,89;,
 4;79,81,91,90;,
 4;81,83,92,91;,
 4;85,84,93,94;,
 4;84,86,95,93;,
 4;86,87,96,95;,
 4;87,88,97,96;,
 4;88,89,98,97;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;91,92,101,100;,
 4;94,93,102,103;,
 4;93,95,104,102;,
 4;95,96,105,104;,
 4;96,97,106,105;,
 4;97,98,107,106;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;100,101,110,109;,
 4;103,102,111,112;,
 4;102,104,113,111;,
 4;104,105,114,113;,
 4;105,106,115,114;,
 4;106,107,116,115;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 4;112,111,120,121;,
 4;111,113,122,120;,
 4;113,114,123,122;,
 4;114,115,124,123;,
 4;115,116,125,124;,
 4;116,117,126,125;,
 4;117,118,127,126;,
 4;118,119,128,127;,
 4;121,120,129,130;,
 4;120,122,131,129;,
 4;122,123,132,131;,
 4;123,124,133,132;,
 4;124,125,134,133;,
 4;125,126,135,134;,
 4;126,127,136,135;,
 4;127,128,137,136;,
 3;130,129,138;,
 3;129,131,139;,
 3;131,132,140;,
 3;132,133,141;,
 3;133,134,142;,
 3;134,135,143;,
 3;135,136,144;,
 3;136,137,145;,
 3;146,147,148;,
 3;149,150,147;,
 3;151,152,150;,
 3;153,154,152;,
 3;155,156,154;,
 3;157,158,156;,
 3;159,160,158;,
 3;161,162,160;,
 4;148,147,163,164;,
 4;147,150,165,163;,
 4;150,152,166,165;,
 4;152,154,167,166;,
 4;154,156,168,167;,
 4;156,158,169,168;,
 4;158,160,170,169;,
 4;160,162,171,170;,
 4;164,163,172,173;,
 4;163,165,174,172;,
 4;165,166,175,174;,
 4;166,167,176,175;,
 4;167,168,177,176;,
 4;168,169,178,177;,
 4;169,170,179,178;,
 4;170,171,180,179;,
 4;173,172,181,182;,
 4;172,174,183,181;,
 4;174,175,184,183;,
 4;175,176,185,184;,
 4;176,177,186,185;,
 4;177,178,187,186;,
 4;178,179,188,187;,
 4;179,180,189,188;,
 4;182,181,190,191;,
 4;181,183,192,190;,
 4;183,184,193,192;,
 4;184,185,194,193;,
 4;185,186,195,194;,
 4;186,187,196,195;,
 4;187,188,197,196;,
 4;188,189,198,197;,
 4;191,190,199,200;,
 4;190,192,201,199;,
 4;192,193,202,201;,
 4;193,194,203,202;,
 4;194,195,204,203;,
 4;195,196,205,204;,
 4;196,197,206,205;,
 4;197,198,207,206;,
 4;200,199,208,209;,
 4;199,201,210,208;,
 4;201,202,211,210;,
 4;202,203,212,211;,
 4;203,204,213,212;,
 4;204,205,214,213;,
 4;205,206,215,214;,
 4;206,207,216,215;,
 3;209,208,217;,
 3;208,210,218;,
 3;210,211,219;,
 3;211,212,220;,
 3;212,213,221;,
 3;213,214,222;,
 3;214,215,223;,
 3;215,216,224;,
 4;225,226,227,228;,
 4;229,230,231,232;,
 4;233,234,235,236;,
 4;237,238,239,240;,
 4;241,238,231,242;,
 4;237,243,244,232;;
 
 MeshMaterialList {
  4;
  198;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.332800;0.684000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.633600;0.800000;0.323200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.684000;0.555200;0.138400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  179;
  -0.000001;1.000000;0.000000;,
  -0.000002;0.924734;-0.380613;,
  0.269131;0.924735;-0.269135;,
  0.380613;0.924734;0.000000;,
  0.269131;0.924735;0.269135;,
  -0.000002;0.924734;0.380613;,
  -0.269132;0.924734;0.269136;,
  -0.380612;0.924735;0.000000;,
  -0.269132;0.924734;-0.269136;,
  -0.000002;0.709228;-0.704979;,
  0.498494;0.709229;-0.498495;,
  0.704979;0.709228;0.000000;,
  0.498494;0.709229;0.498495;,
  -0.000002;0.709228;0.704979;,
  -0.498496;0.709227;0.498497;,
  -0.704980;0.709227;0.000000;,
  -0.498496;0.709227;-0.498497;,
  -0.000001;0.384551;-0.923104;,
  0.652734;0.384550;-0.652733;,
  0.923104;0.384549;0.000000;,
  0.652734;0.384550;0.652733;,
  -0.000001;0.384551;0.923104;,
  -0.652735;0.384550;0.652731;,
  -0.923105;0.384549;0.000000;,
  -0.652735;0.384550;-0.652731;,
  -0.000001;0.000002;-1.000000;,
  0.707108;0.000002;-0.707106;,
  1.000000;0.000002;0.000000;,
  0.707108;0.000002;0.707106;,
  -0.000001;0.000002;1.000000;,
  -0.707110;0.000002;0.707104;,
  -1.000000;0.000002;0.000000;,
  -0.707110;0.000002;-0.707104;,
  -0.000001;-0.384554;-0.923103;,
  0.652733;-0.384553;-0.652732;,
  0.923103;-0.384552;-0.000000;,
  0.652733;-0.384553;0.652732;,
  -0.000001;-0.384554;0.923103;,
  -0.652734;-0.384553;0.652730;,
  -0.923103;-0.384552;0.000000;,
  -0.652734;-0.384553;-0.652730;,
  -0.000002;-0.709232;-0.704975;,
  0.498492;-0.709233;-0.498492;,
  0.704976;-0.709232;-0.000000;,
  0.498492;-0.709233;0.498492;,
  -0.000002;-0.709232;0.704975;,
  -0.498493;-0.709230;0.498495;,
  -0.704977;-0.709230;0.000000;,
  -0.498493;-0.709230;-0.498495;,
  -0.000002;-0.924734;-0.380613;,
  0.269131;-0.924735;-0.269135;,
  0.380613;-0.924734;-0.000000;,
  0.269131;-0.924735;0.269135;,
  -0.000002;-0.924734;0.380613;,
  -0.269132;-0.924734;0.269136;,
  -0.380612;-0.924735;0.000000;,
  -0.269132;-0.924734;-0.269136;,
  -0.000001;-1.000000;0.000000;,
  0.000001;1.000000;-0.000000;,
  0.000000;0.924734;-0.380613;,
  0.269132;0.924736;-0.269131;,
  0.380613;0.924734;0.000000;,
  0.269132;0.924736;0.269131;,
  0.000000;0.924734;0.380613;,
  -0.269131;0.924735;0.269134;,
  -0.380613;0.924734;0.000000;,
  -0.269131;0.924735;-0.269134;,
  0.000000;0.709228;-0.704979;,
  0.498495;0.709229;-0.498495;,
  0.704980;0.709227;0.000000;,
  0.498495;0.709229;0.498495;,
  0.000000;0.709228;0.704979;,
  -0.498495;0.709227;0.498497;,
  -0.704981;0.709226;0.000000;,
  -0.498495;0.709227;-0.498497;,
  0.000000;0.384550;-0.923104;,
  0.652735;0.384548;-0.652733;,
  0.923106;0.384545;0.000000;,
  0.652735;0.384548;0.652733;,
  0.000000;0.384550;0.923104;,
  -0.652733;0.384550;0.652733;,
  -0.923104;0.384550;0.000000;,
  -0.652733;0.384550;-0.652733;,
  0.000000;0.000002;-1.000000;,
  0.707109;0.000002;-0.707105;,
  1.000000;0.000002;0.000000;,
  0.707109;0.000002;0.707105;,
  0.000000;0.000002;1.000000;,
  -0.707107;0.000002;0.707107;,
  -1.000000;0.000002;0.000000;,
  -0.707107;0.000002;-0.707107;,
  0.000000;-0.384553;-0.923103;,
  0.652734;-0.384551;-0.652732;,
  0.923105;-0.384549;-0.000000;,
  0.652734;-0.384551;0.652732;,
  0.000000;-0.384553;0.923103;,
  -0.652732;-0.384553;0.652732;,
  -0.923103;-0.384554;0.000000;,
  -0.652732;-0.384553;-0.652732;,
  0.000000;-0.709231;-0.704976;,
  0.498493;-0.709232;-0.498492;,
  0.704976;-0.709231;-0.000000;,
  0.498493;-0.709232;0.498492;,
  0.000000;-0.709231;0.704976;,
  -0.498493;-0.709231;0.498494;,
  -0.704978;-0.709229;0.000000;,
  -0.498493;-0.709231;-0.498494;,
  0.000000;-0.924734;-0.380613;,
  0.269132;-0.924736;-0.269131;,
  0.380613;-0.924734;-0.000000;,
  0.269132;-0.924736;0.269131;,
  0.000000;-0.924734;0.380613;,
  -0.269131;-0.924735;0.269134;,
  -0.380613;-0.924734;0.000000;,
  -0.269131;-0.924735;-0.269134;,
  0.000001;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.924734;-0.380615;,
  0.269132;0.924735;-0.269133;,
  0.269132;0.924735;0.269133;,
  0.000000;0.924734;0.380615;,
  -0.269132;0.924736;0.269132;,
  -0.380614;0.924734;0.000000;,
  -0.269132;0.924736;-0.269132;,
  0.000000;0.709226;-0.704981;,
  0.498495;0.709228;-0.498496;,
  0.704980;0.709227;0.000000;,
  0.498495;0.709228;0.498496;,
  0.000000;0.709226;0.704981;,
  -0.498496;0.709228;0.498495;,
  -0.704981;0.709226;0.000000;,
  -0.498496;0.709228;-0.498495;,
  -0.000000;0.384549;-0.923104;,
  0.652734;0.384549;-0.652733;,
  0.923104;0.384550;0.000000;,
  0.652734;0.384549;0.652733;,
  -0.000000;0.384549;0.923104;,
  -0.652733;0.384549;0.652734;,
  -0.923104;0.384550;0.000000;,
  -0.652733;0.384549;-0.652734;,
  -0.000000;0.000002;-1.000000;,
  0.707107;0.000002;-0.707107;,
  1.000000;0.000002;0.000000;,
  0.707107;0.000002;0.707107;,
  -0.000000;0.000002;1.000000;,
  -0.707106;0.000002;0.707108;,
  -1.000000;0.000002;0.000000;,
  -0.707106;0.000002;-0.707108;,
  -0.000000;-0.384552;-0.923103;,
  0.652733;-0.384552;-0.652732;,
  0.923103;-0.384553;-0.000000;,
  0.652733;-0.384552;0.652732;,
  -0.000000;-0.384552;0.923103;,
  -0.652732;-0.384552;0.652733;,
  -0.923103;-0.384554;0.000000;,
  -0.652732;-0.384552;-0.652733;,
  0.000000;-0.709230;-0.704977;,
  0.498493;-0.709231;-0.498493;,
  0.704976;-0.709231;-0.000000;,
  0.498493;-0.709231;0.498493;,
  0.000000;-0.709230;0.704977;,
  -0.498494;-0.709231;0.498493;,
  -0.704977;-0.709230;0.000000;,
  -0.498494;-0.709231;-0.498493;,
  0.000000;-0.924734;-0.380615;,
  0.269132;-0.924735;-0.269133;,
  0.380613;-0.924734;-0.000000;,
  0.269132;-0.924735;0.269133;,
  0.000000;-0.924734;0.380615;,
  -0.269132;-0.924736;0.269132;,
  -0.380614;-0.924734;0.000000;,
  -0.269132;-0.924736;-0.269132;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  198;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;58,60,59;,
  3;58,61,60;,
  3;58,62,61;,
  3;58,63,62;,
  3;58,64,63;,
  3;58,65,64;,
  3;58,66,65;,
  3;58,59,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,59,67,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,67,75,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,75,83,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,83,91,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,91,99,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,106,114,113;,
  4;106,99,107,114;,
  3;107,108,115;,
  3;108,109,115;,
  3;109,110,115;,
  3;110,111,115;,
  3;111,112,115;,
  3;112,113,115;,
  3;113,114,115;,
  3;114,107,115;,
  3;116,118,117;,
  3;116,3,118;,
  3;116,119,3;,
  3;116,120,119;,
  3;116,121,120;,
  3;116,122,121;,
  3;116,123,122;,
  3;116,117,123;,
  4;117,118,125,124;,
  4;118,3,126,125;,
  4;3,119,127,126;,
  4;119,120,128,127;,
  4;120,121,129,128;,
  4;121,122,130,129;,
  4;122,123,131,130;,
  4;123,117,124,131;,
  4;124,125,133,132;,
  4;125,126,134,133;,
  4;126,127,135,134;,
  4;127,128,136,135;,
  4;128,129,137,136;,
  4;129,130,138,137;,
  4;130,131,139,138;,
  4;131,124,132,139;,
  4;132,133,141,140;,
  4;133,134,142,141;,
  4;134,135,143,142;,
  4;135,136,144,143;,
  4;136,137,145,144;,
  4;137,138,146,145;,
  4;138,139,147,146;,
  4;139,132,140,147;,
  4;140,141,149,148;,
  4;141,142,150,149;,
  4;142,143,151,150;,
  4;143,144,152,151;,
  4;144,145,153,152;,
  4;145,146,154,153;,
  4;146,147,155,154;,
  4;147,140,148,155;,
  4;148,149,157,156;,
  4;149,150,158,157;,
  4;150,151,159,158;,
  4;151,152,160,159;,
  4;152,153,161,160;,
  4;153,154,162,161;,
  4;154,155,163,162;,
  4;155,148,156,163;,
  4;156,157,165,164;,
  4;157,158,166,165;,
  4;158,159,167,166;,
  4;159,160,168,167;,
  4;160,161,169,168;,
  4;161,162,170,169;,
  4;162,163,171,170;,
  4;163,156,164,171;,
  3;164,165,172;,
  3;165,166,172;,
  3;166,167,172;,
  3;167,168,172;,
  3;168,169,172;,
  3;169,170,172;,
  3;170,171,172;,
  3;171,164,172;,
  4;173,173,173,173;,
  4;174,174,174,174;,
  4;175,175,175,175;,
  4;176,176,176,176;,
  4;177,177,177,177;,
  4;178,178,178,178;;
 }
 MeshTextureCoords {
  245;
  0.750000;0.000000;
  1.188140;0.038060;
  1.000000;0.038060;
  0.250000;0.038060;
  0.311860;0.038060;
  0.500000;0.038060;
  0.688140;0.038060;
  0.750000;0.038060;
  0.811860;0.038060;
  0.000000;0.038060;
  0.188140;0.038060;
  0.188140;0.146450;
  0.000000;0.146450;
  0.250000;0.146450;
  0.311860;0.146450;
  0.500000;0.146450;
  0.688140;0.146450;
  0.750000;0.146450;
  0.811860;0.146450;
  1.000000;0.146450;
  0.188140;0.308660;
  0.000000;0.308660;
  0.250000;0.308660;
  0.311860;0.308660;
  0.500000;0.308660;
  0.688140;0.308660;
  0.750000;0.308660;
  0.811860;0.308660;
  1.000000;0.308660;
  0.188140;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.311860;0.500000;
  0.500000;0.500000;
  0.688140;0.500000;
  0.750000;0.500000;
  0.811860;0.500000;
  1.000000;0.500000;
  0.188140;0.691340;
  0.000000;0.691340;
  0.250000;0.691340;
  0.311860;0.691340;
  0.500000;0.691340;
  0.688140;0.691340;
  0.750000;0.691340;
  0.811860;0.691340;
  1.000000;0.691340;
  0.188140;0.853550;
  0.000000;0.853550;
  0.250000;0.853550;
  0.311860;0.853550;
  0.500000;0.853550;
  0.688140;0.853550;
  0.750000;0.853550;
  0.811860;0.853550;
  1.000000;0.853550;
  0.188140;0.961940;
  0.000000;0.961940;
  0.250000;0.961940;
  0.311860;0.961940;
  0.500000;0.961940;
  0.688140;0.961940;
  0.750000;0.961940;
  0.811860;0.961940;
  1.000000;0.961940;
  -0.250000;1.000000;
  0.750000;1.000000;
  0.062500;0.000000;
  0.125000;0.125000;
  0.000000;0.125000;
  0.187500;0.000000;
  0.250000;0.125000;
  0.312500;0.000000;
  0.375000;0.125000;
  0.437500;0.000000;
  0.500000;0.125000;
  0.562500;0.000000;
  0.625000;0.125000;
  0.687500;0.000000;
  0.750000;0.125000;
  0.812500;0.000000;
  0.875000;0.125000;
  0.937500;0.000000;
  1.000000;0.125000;
  0.125000;0.250000;
  0.000000;0.250000;
  0.250000;0.250000;
  0.375000;0.250000;
  0.500000;0.250000;
  0.625000;0.250000;
  0.750000;0.250000;
  0.875000;0.250000;
  1.000000;0.250000;
  0.125000;0.375000;
  0.000000;0.375000;
  0.250000;0.375000;
  0.375000;0.375000;
  0.500000;0.375000;
  0.625000;0.375000;
  0.750000;0.375000;
  0.875000;0.375000;
  1.000000;0.375000;
  0.125000;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.375000;0.500000;
  0.500000;0.500000;
  0.625000;0.500000;
  0.750000;0.500000;
  0.875000;0.500000;
  1.000000;0.500000;
  0.125000;0.625000;
  0.000000;0.625000;
  0.250000;0.625000;
  0.375000;0.625000;
  0.500000;0.625000;
  0.625000;0.625000;
  0.750000;0.625000;
  0.875000;0.625000;
  1.000000;0.625000;
  0.125000;0.750000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.375000;0.750000;
  0.500000;0.750000;
  0.625000;0.750000;
  0.750000;0.750000;
  0.875000;0.750000;
  1.000000;0.750000;
  0.125000;0.875000;
  0.000000;0.875000;
  0.250000;0.875000;
  0.375000;0.875000;
  0.500000;0.875000;
  0.625000;0.875000;
  0.750000;0.875000;
  0.875000;0.875000;
  1.000000;0.875000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.062500;0.000000;
  0.125000;0.125000;
  0.000000;0.125000;
  0.187500;0.000000;
  0.250000;0.125000;
  0.312500;0.000000;
  0.375000;0.125000;
  0.437500;0.000000;
  0.500000;0.125000;
  0.562500;0.000000;
  0.625000;0.125000;
  0.687500;0.000000;
  0.750000;0.125000;
  0.812500;0.000000;
  0.875000;0.125000;
  0.937500;0.000000;
  1.000000;0.125000;
  0.125000;0.250000;
  0.000000;0.250000;
  0.250000;0.250000;
  0.375000;0.250000;
  0.500000;0.250000;
  0.625000;0.250000;
  0.750000;0.250000;
  0.875000;0.250000;
  1.000000;0.250000;
  0.125000;0.375000;
  0.000000;0.375000;
  0.250000;0.375000;
  0.375000;0.375000;
  0.500000;0.375000;
  0.625000;0.375000;
  0.750000;0.375000;
  0.875000;0.375000;
  1.000000;0.375000;
  0.125000;0.500000;
  0.000000;0.500000;
  0.250000;0.500000;
  0.375000;0.500000;
  0.500000;0.500000;
  0.625000;0.500000;
  0.750000;0.500000;
  0.875000;0.500000;
  1.000000;0.500000;
  0.125000;0.625000;
  0.000000;0.625000;
  0.250000;0.625000;
  0.375000;0.625000;
  0.500000;0.625000;
  0.625000;0.625000;
  0.750000;0.625000;
  0.875000;0.625000;
  1.000000;0.625000;
  0.125000;0.750000;
  0.000000;0.750000;
  0.250000;0.750000;
  0.375000;0.750000;
  0.500000;0.750000;
  0.625000;0.750000;
  0.750000;0.750000;
  0.875000;0.750000;
  1.000000;0.750000;
  0.125000;0.875000;
  0.000000;0.875000;
  0.250000;0.875000;
  0.375000;0.875000;
  0.500000;0.875000;
  0.625000;0.875000;
  0.750000;0.875000;
  0.875000;0.875000;
  1.000000;0.875000;
  0.062500;1.000000;
  0.187500;1.000000;
  0.312500;1.000000;
  0.437500;1.000000;
  0.562500;1.000000;
  0.687500;1.000000;
  0.812500;1.000000;
  0.937500;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  1.000000;0.000000;
  1.000000;1.000000;
  0.000000;1.000000;
  0.000000;0.000000;
  0.000000;1.000000;
  1.000000;0.000000;
  1.000000;1.000000;;
 }
}
