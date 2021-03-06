////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;

	BackgroundColor[0] = 0.0f; //기본 뒷배경 color값 검정으로 초기화.
	BackgroundColor[1] = 0.0f;
	BackgroundColor[2] = 0.0f;
	BackgroundColor[3] = 1.0f;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, D3D11_FILL_MODE fillMode)
{
	bool result;

	m_hwnd = hwnd;
	m_screenwidth = screenWidth;
	m_screenheight = screenHeight;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR, fillMode);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
<<<<<<< HEAD
		return false; 
=======
		return false;
>>>>>>> parent of 3d3856c (Change the color brightness)
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;

	rotation += (float)D3DX_PI * 0.01f;
	if (rotation > 360.0f)
		rotation -= 360.0f;

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::ChangeBGColor(float red, float green, float blue, float alpha)
{
	BackgroundColor[0] = red;
	BackgroundColor[1] = green;
	BackgroundColor[2] = blue;
	BackgroundColor[3] = alpha;

	return;
}

<<<<<<< HEAD
void GraphicsClass::ChangeBrightness(float brightness)
{
	changedBrightness = brightness;

	return;
}

void GraphicsClass::ChangeFillMode(D3D11_FILL_MODE fillMode)
{
	Initialize(m_screenwidth, m_screenheight, m_hwnd, fillMode);
	return;
}

bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;	
	D3DXMATRIX transformMatrix;
	D3DXMATRIX scaleMatrix;
	D3DXMATRIX* m_worldMatrix;

=======
bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	//D3DXMATRIX triangleMatrix, squareMatrix, hexagonMatrix;
>>>>>>> parent of 3d3856c (Change the color brightness)
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(BackgroundColor[0], BackgroundColor[1], BackgroundColor[2], BackgroundColor[3] );

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_worldMatrix = new D3DXMATRIX[3]; //도형 수만큼 매트릭스 생성해주기.
	if (!m_worldMatrix)
	{
		return false;
	}

	for (int i = 0; i < 3; i++)
	{
		m_worldMatrix[i] = worldMatrix;
	}
	D3DXMatrixRotationX(&m_worldMatrix[0], rotation);
	D3DXMatrixTranslation(&transformMatrix, -2, 0, 0);
	D3DXMatrixScaling(&scaleMatrix, 1, 1, 1);
	m_worldMatrix[0] *= transformMatrix * scaleMatrix;

	D3DXMatrixRotationY(&m_worldMatrix[1], rotation);
	D3DXMatrixTranslation(&transformMatrix, 0, 0, 0);
	D3DXMatrixScaling(&scaleMatrix, 1, 1, 1);
	m_worldMatrix[1] *= transformMatrix * scaleMatrix;

	D3DXMatrixRotationZ(&m_worldMatrix[2], rotation);
	D3DXMatrixTranslation(&transformMatrix, 2, 0, 0);
	D3DXMatrixScaling(&scaleMatrix, 1, 1, 1);
	m_worldMatrix[2] *= transformMatrix * scaleMatrix;

	for (int i = 0; i < 3; i++)
	{
		worldMatrix = m_worldMatrix[i];
		m_Model[i].Render(m_D3D->GetDeviceContext());

		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(),
			worldMatrix, viewMatrix, projectionMatrix, changedBrightness);
	}

	//m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
<<<<<<< HEAD
	
=======
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), 
		worldMatrix, viewMatrix, projectionMatrix);
>>>>>>> parent of 3d3856c (Change the color brightness)
	if(!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}