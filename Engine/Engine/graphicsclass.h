////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, D3D11_FILL_MODE);
	void Shutdown();
	bool Frame();
	void ChangeBGColor(float , float , float , float );
<<<<<<< HEAD
	void ChangeBrightness(float brightness);
	void ChangeFillMode(D3D11_FILL_MODE fillMode);

public:
	float BackgroundColor[4];
	float changedBrightness;
	HWND m_hwnd;
	int m_screenwidth;
	int m_screenheight;
=======

public:
	float BackgroundColor[4];
>>>>>>> parent of 3d3856c (Change the color brightness)

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
};

#endif