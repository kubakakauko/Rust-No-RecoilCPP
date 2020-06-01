#include "Menu.h"
#include "Recoil.h"
#include <list>

// Data
static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

 int Menu::MenuImGui()
{
     // Create application window
     WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
     ::RegisterClassEx(&wc);
     HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX11 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

     if(!CreateDeviceD3D(hwnd))
     {
         CleanupDeviceD3D();
         ::UnregisterClass(wc.lpszClassName, wc.hInstance);
         return 1;
     }
     ::ShowWindow(hwnd, SW_SHOWDEFAULT);
     ::UpdateWindow(hwnd);

     //Setup ImGui context
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO& io = ImGui::GetIO(); (void)io;


     // Setup Dear ImGui style
     ImGui::StyleColorsDark();

     // Setup Platform/Renderer bindings
     ImGui_ImplWin32_Init(hwnd);
     ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

     //Some states
     bool show_demo_window = false;
     ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
     //
     // Main loop
     MSG msg;
     ZeroMemory(&msg, sizeof(msg));
     while(msg.message != WM_QUIT)
     {
         Recoil::calculations();

         // Poll and handle messages (inputs, window resize, etc.)
         // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
         // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
         // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
         // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
         if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
         {
             ::TranslateMessage(&msg);
             ::DispatchMessage(&msg);

             continue;
             
         }
         
         // Start the Dear ImGui frame
         ImGui_ImplDX11_NewFrame();
         ImGui_ImplWin32_NewFrame();
         ImGui::NewFrame();

         // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
          if (show_demo_window)
             ImGui::ShowDemoWindow(&show_demo_window);

         // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
         {
             static float f = 0.0f;
             static int counter = 0;
             const char* weapons[] = { "None","Assault-Rifle", "LR300" ,"Thompson", "Custom-SMG", "M249", "MP5", "Semi-Auto-Rifle", "M39", "M92", "Semi-Auto-Pistol","Python","Revolver","Nail-Gun" };
             const char* attachments[] = {"None", "Muzzle-Boost", "Muzzle-Brake", "Silencer"};
             const char* scopes[] = {"None", "Holosight", "Home-Made", "8x", "16x"};

             ImGui::Begin("Combo-X",0);                                  // Create a window called "Hello, world!" and append into it.

             ImGui::Checkbox("Activated ", &Recoil::scriptActive);


             ImGui::Text("Selected Weapon: "); ImGui::SameLine(); ImGui::Text(("{}", Recoil::weaponName(Recoil::selectedWeapon)).c_str());
             ImGui::Text("Selected Scope: "); ImGui::SameLine(); ImGui::Text(("{}", Recoil::scopeName(Recoil::selectedScope)).c_str());
             ImGui::Text("Selected Attachment: "); ImGui::SameLine(); ImGui::Text(("{}", Recoil::attachmentName(Recoil::selectedAttachment)).c_str());

             if(ImGui::CollapsingHeader("Weapons"))
             {
                 ImGui::ListBox("Weapon", &Recoil::selectedWeapon, weapons, IM_ARRAYSIZE(weapons), 14);

             }

             if(ImGui::CollapsingHeader("Scopes"))
             {
                 ImGui::ListBox("Scope", &Recoil::selectedScope, scopes, IM_ARRAYSIZE(scopes), 5);

             }

             if(ImGui::CollapsingHeader("Attachments"))
             {
                 ImGui::ListBox("Attachment", &Recoil::selectedAttachment, attachments, IM_ARRAYSIZE(attachments), 4);
             }
             //
             //ImGui::Separator();
             //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
             //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
             
             ImGui::End();
         }

         // Rendering
         ImGui::Render();
         g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
         g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
         ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

         g_pSwapChain->Present(1, 0); // Present with vsync
         //g_pSwapChain->Present(0, 0); // Present without vsync
     }

     // Cleanup
     ImGui_ImplDX11_Shutdown();
     ImGui_ImplWin32_Shutdown();
     ImGui::DestroyContext();

     CleanupDeviceD3D();
     ::DestroyWindow(hwnd);
     ::UnregisterClass(wc.lpszClassName, wc.hInstance);
     return 0;
}


 // Helper functions

 bool CreateDeviceD3D(HWND hWnd)
 {
     // Setup swap chain
     DXGI_SWAP_CHAIN_DESC sd;
     ZeroMemory(&sd, sizeof(sd));
     sd.BufferCount = 2;
     sd.BufferDesc.Width = 0;
     sd.BufferDesc.Height = 0;
     sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
     sd.BufferDesc.RefreshRate.Numerator = 60;
     sd.BufferDesc.RefreshRate.Denominator = 1;
     sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
     sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
     sd.OutputWindow = hWnd;
     sd.SampleDesc.Count = 1;
     sd.SampleDesc.Quality = 0;
     sd.Windowed = TRUE;
     sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

     UINT createDeviceFlags = 0;
     //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
     D3D_FEATURE_LEVEL featureLevel;
     const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
     if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
         return false;

     CreateRenderTarget();
     return true;
 }

 void CleanupDeviceD3D()
 {
     CleanupRenderTarget();
     if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
     if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
     if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
 }

 void CreateRenderTarget()
 {
     ID3D11Texture2D* pBackBuffer;
     g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
     g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
     pBackBuffer->Release();
 }

 void CleanupRenderTarget()
 {
     if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
 }

 // Forward declare message handler from imgui_impl_win32.cpp
 extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

 // Win32 message handler
 LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
 {
     if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
         return true;

     switch (msg)
     {
     case WM_SIZE:
         if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
         {
             CleanupRenderTarget();
             g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
             CreateRenderTarget();
         }
         return 0;
     case WM_SYSCOMMAND:
         if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
             return 0;
         break;
     case WM_DESTROY:
         ::PostQuitMessage(0);
         return 0;
     }
     return ::DefWindowProc(hWnd, msg, wParam, lParam);
 }
