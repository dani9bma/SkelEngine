#pragma once

#include "platform\directx\graphics\DXWindow.h"
#include "platform\directx\graphics\context.h"
#include "platform\directx\graphics\DXShader.h"
#include "platform\directx\graphics\DXIndexBuffer.h"
#include "platform\directx\graphics\DXVertexBuffer.h"
#include "platform\directx\graphics\DXCamera.h"
#include "platform\directx\graphics\DXTexture.h"

#include <DirectXMath.h>

#include "imgui/imgui.h"


extern bool ImGui_ImplDX11_Init(void* hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
extern void ImGui_ImplDX11_Shutdown();
extern void ImGui_ImplDX11_NewFrame();
extern void ImGui_ImplDX11_RenderDrawData(ImDrawData* draw_data);
extern void ImGui_ImplDX11_InvalidateDeviceObjects();
extern bool ImGui_ImplDX11_CreateDeviceObjects();

using namespace DirectX;

struct Vertex    //Overloaded Vertex Structure
{
	Vertex() {}
	Vertex(float x, float y, float z, float u, float v)
		: pos(x, y, z), texCoord(u, v) 
	{}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

using namespace Skel;

class DXScene
{
public:
	DXScene()
	{
		//Create the vertex buffer
		Vertex v[] =
		{
			// Front Face
			Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
			Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
			Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

			// Back Face
			Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
			Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
			Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
			Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

			// Top Face
			Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
			Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
			Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

			// Bottom Face
			Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
			Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
			Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),

			// Left Face
			Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
			Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
			Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
			Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

			// Right Face
			Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
			Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
			Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
			Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
		};

		DWORD indices[] = {
			// Front Face
			0,  1,  2,
			0,  2,  3,

			// Back Face
			4,  5,  6,
			4,  6,  7,

			// Top Face
			8,  9, 10,
			8, 10, 11,

			// Bottom Face
			12, 13, 14,
			12, 14, 15,

			// Left Face
			16, 17, 18,
			16, 18, 19,

			// Right Face
			20, 21, 22,
			20, 22, 23
		};

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DXWindow* window = new DXWindow(1280, 720, "Skel Engine");
		Context* context = new Context(window);
		DXShader* shader = new DXShader(context);
		shader->setShaders(L"src/platform/directx/shaders/basicVert.hlsl", L"src/platform/directx/shaders/basicPixel.hlsl");
		DXIndexBuffer* indexBuffer = new DXIndexBuffer(indices, sizeof(DWORD) * 12 * 3, context);
		DXVertexBuffer* vertexBuffer = new DXVertexBuffer(v, sizeof(Vertex) * 24, sizeof(Vertex), context);
		shader->setInputLayout(layout);
		DXCamera* camera = new DXCamera(context, window);
		DXTexture* texture = new DXTexture(context, L"src/textures/ice.jpg");


		// Setup ImGui binding
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->AddFontFromFileTTF("C:/Users/dinho/Desktop/Roboto-Regular.ttf", 18.0f);
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		ImGui_ImplDX11_Init(window->getHandle(), context->getDevice(), context->getDeviceContext());

		// Setup style
		ImGui::StyleColorsDark();

		bool show_another_window = true;

		while (!window->closed())
		{
			window->update();

			ImGui_ImplDX11_NewFrame();


			if (show_another_window)
			{
				ImGui::Begin("Debug", &show_another_window);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

			//Render
			context->update();

			camera->update();
			texture->update();
			context->getDeviceContext()->DrawIndexed(36, 0, 0);

			context->draw();
		}
		
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();

	}

};