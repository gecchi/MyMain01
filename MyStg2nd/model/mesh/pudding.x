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
 18;
 -2.70832;2.53905;0.00000;,
 0.00000;2.53905;0.00000;,
 -1.91507;2.53905;-1.91507;,
 -3.59075;-2.53905;-3.59075;,
 -5.07810;-2.53905;0.00000;,
 0.00000;-2.53905;-0.00000;,
 0.00000;2.53905;-2.70832;,
 0.00000;-2.53905;-5.07810;,
 1.91507;2.53905;-1.91507;,
 3.59075;-2.53905;-3.59075;,
 2.70832;2.53905;0.00000;,
 5.07810;-2.53905;-0.00000;,
 1.91507;2.53905;1.91507;,
 3.59075;-2.53905;3.59075;,
 0.00000;2.53905;2.70832;,
 0.00000;-2.53905;5.07810;,
 -1.91507;2.53905;1.91507;,
 -3.59075;-2.53905;3.59075;;
 
 24;
 3;0,1,2;,
 4;0,2,3,4;,
 3;4,3,5;,
 3;2,1,6;,
 4;2,6,7,3;,
 3;3,7,5;,
 3;6,1,8;,
 4;6,8,9,7;,
 3;7,9,5;,
 3;8,1,10;,
 4;8,10,11,9;,
 3;9,11,5;,
 3;10,1,12;,
 4;10,12,13,11;,
 3;11,13,5;,
 3;12,1,14;,
 4;12,14,15,13;,
 3;13,15,5;,
 3;14,1,16;,
 4;14,16,17,15;,
 3;15,17,5;,
 3;16,1,0;,
 4;16,0,4,17;,
 3;17,4,5;;
 
 MeshMaterialList {
  2;
  24;
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1;;
  Material {
   0.247000;0.129000;0.004000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;0.502000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  0.000000;-1.000000;-0.000000;,
  -0.906184;0.422884;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.640769;0.422884;-0.640769;,
  0.000000;0.422884;-0.906184;,
  0.640769;0.422884;-0.640769;,
  0.906184;0.422884;0.000000;,
  0.640769;0.422884;0.640769;,
  0.000000;0.422884;0.906184;,
  -0.640769;0.422884;0.640769;;
  24;
  3;2,2,2;,
  4;1,3,3,1;,
  3;0,0,0;,
  3;2,2,2;,
  4;3,4,4,3;,
  3;0,0,0;,
  3;2,2,2;,
  4;4,5,5,4;,
  3;0,0,0;,
  3;2,2,2;,
  4;5,6,6,5;,
  3;0,0,0;,
  3;2,2,2;,
  4;6,7,7,6;,
  3;0,0,0;,
  3;2,2,2;,
  4;7,8,8,7;,
  3;0,0,0;,
  3;2,2,2;,
  4;8,9,9,8;,
  3;0,0,0;,
  3;2,2,2;,
  4;9,1,1,9;,
  3;0,0,0;;
 }
 MeshTextureCoords {
  18;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;;
 }
}
