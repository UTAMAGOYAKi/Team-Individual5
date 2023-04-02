
#include "AEEngine.h"

AEGfxVertexList* createmesh() {
	// Pointer to Mesh
	AEGfxVertexList* pMesh = 0;

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles that makes up a square
	// Color parameters represent colours as ARGB in hexadecimal
	// (e.g. 0xFFFF0000 is red, 0xFF00FF00 is green)
	// UV coordinates to read from loaded textures
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);

	// Saving the mesh (list of triangles) in pMesh
	pMesh = AEGfxMeshEnd();
}

void freemesh(AEGfxVertexList* pMesh) {
	// Pointer to Mesh
	AEGfxMeshFree(pMesh);
}