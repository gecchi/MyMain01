xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Material PDX08_-_Default {
 1.000000;1.000000;1.000000;0.540000;;
 16.320000;
 0.770588;1.048000;1.176431;;
 0.000000;0.000000;1.000000;;

 TextureFilename {
  "blue.tga";
 }
}

Frame Plane01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,14.988579,0.000000,24.627230,1.000000;;
 }

 Mesh  {
  20;
  -15.157995;0.000294;-24.049662;,
  -14.391360;0.000029;-24.627201;,
  -14.391360;0.000029;-24.627201;,
  -15.158039;-0.499676;-24.915735;,
  -15.150460;-0.499980;-24.915735;,
  -15.158043;0.500301;-24.915735;,
  -15.150458;0.500019;-24.915735;,
  -14.376286;0.000029;-24.627201;,
  -14.391360;0.000029;-24.627201;,
  -15.158039;0.500301;-24.915735;,
  -15.150585;0.000011;-24.049826;,
  -15.157995;0.000294;-24.049662;,
  -15.158039;-0.499676;-24.915735;,
  -14.376286;0.000029;-24.627201;,
  -15.150460;-0.499980;-24.915735;,
  -14.376286;0.000029;-24.627201;,
  -15.150458;0.500019;-24.915735;,
  -15.158043;0.500301;-24.915735;,
  -15.157995;0.000294;-24.049662;,
  -15.150585;0.000011;-24.049826;;
  12;
  3;7,12,1;,
  3;12,7,4;,
  3;2,10,0;,
  3;13,10,2;,
  3;14,5,6;,
  3;5,14,3;,
  3;5,15,6;,
  3;8,15,5;,
  3;9,10,16;,
  3;10,17,11;,
  3;18,4,19;,
  3;4,18,12;;

  MeshNormals  {
   13;
   0.613760;-0.789017;0.027393;,
   -0.039604;-0.982076;0.184279;,
   0.000000;0.500038;-0.866003;,
   -0.002233;-0.056428;-0.998404;,
   -0.000072;-1.000000;-0.000125;,
   -0.022088;-0.867777;0.496463;,
   -0.039288;-0.997890;-0.051692;,
   0.011398;0.308599;-0.951124;,
   0.033273;0.894334;0.446160;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.499612;0.866249;,
   0.032210;0.865541;0.499801;,
   0.022855;0.020709;0.999524;;
   12;
   3;0,1,2;,
   3;1,0,3;,
   3;4,5,6;,
   3;0,5,4;,
   3;3,7,8;,
   3;7,3,9;,
   3;7,0,8;,
   3;10,0,7;,
   3;11,5,8;,
   3;5,7,12;,
   3;12,3,5;,
   3;3,12,1;;
  }

  MeshMaterialList  {
   1;
   12;
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
   0;
   { PDX08_-_Default }
  }

  MeshTextureCoords  {
   20;
   0.000000;0.259850;,
   0.000000;0.971298;,
   0.000000;0.129925;,
   0.000000;0.945295;,
   1.000000;1.000000;,
   0.000000;0.910358;,
   1.000000;0.895648;,
   1.000000;0.979486;,
   0.000000;0.585715;,
   0.000000;0.259850;,
   1.000000;0.259850;,
   0.000000;0.259850;,
   0.000000;1.000000;,
   1.000000;0.129925;,
   0.500000;0.945295;,
   0.500000;0.711941;,
   1.000000;0.259850;,
   0.000000;0.259850;,
   0.000000;1.000000;,
   1.000000;1.000000;;
  }
 }
}