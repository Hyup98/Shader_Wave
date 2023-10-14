#include "ExampleApp.h"

#include <directxtk/DDSTextureLoader.h> // 큐브맵 읽을 때 필요
#include <tuple>
#include <vector>

#include "GeometryGenerator.h"

namespace hlab {

using namespace std;
using namespace DirectX;

ExampleApp::ExampleApp() : AppBase() {}

bool ExampleApp::Initialize() {

    if (!AppBase::Initialize())
        return false;

    BuildFilters();

    return true;
}

void ExampleApp::Update(float dt) {

    using namespace DirectX;

    static float time = 0.0f;

    m_filters.back()->m_pixelConstData.iTime = time;
    m_filters.back()->UpdateConstantBuffers(m_device, m_context);

    time += dt;
}

void ExampleApp::Render() {

    // RS: Rasterizer stage
    // OM: Output-Merger stage
    // VS: Vertex Shader
    // PS: Pixel Shader
    // IA: Input-Assembler stage

    //SetViewport();

    //float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    //m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
    //m_context->ClearDepthStencilView(m_depthStencilView.Get(),
    //                                 D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
    //                                 1.0f, 0);
    //m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(),
    //                              m_depthStencilView.Get());
    //m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

    //if (m_drawAsWire) {
    //    m_context->RSSetState(m_wireRasterizerSate.Get());
    //} else {
    //    m_context->RSSetState(m_rasterizerSate.Get());
    //}

    //// 큐브매핑
    //m_cubeMapping.Render(m_context);

    //// 물체들
    //if (m_visibleMeshIndex == 0) {
    //    m_meshGroupSphere.Render(m_context);
    //} else {
    //    m_meshGroupCharacter.Render(m_context);
    //}

    // 후처리 필터
    for (auto &f : m_filters) {
        f->Render(m_context);
    }
}

void ExampleApp::BuildFilters() {

    static ComPtr<ID3D11Texture2D> texture;
    static ComPtr<ID3D11ShaderResourceView> textureResourceView;

    D3D11Utils::CreateTexture(m_device, "shadertoytexture0.jpg", texture,
                              textureResourceView);

    m_filters.clear();

    //auto shaderToy =
    //    make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Seascape",
    //                             m_screenWidth, m_screenHeight);

    auto shaderToy =
        make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Wave",
                                 m_screenWidth, m_screenHeight);

    shaderToy->SetShaderResources({textureResourceView});
    shaderToy->SetRenderTargets({m_renderTargetView});
    m_filters.push_back(shaderToy);
}

void ExampleApp::UpdateGUI() {
}

} // namespace hlab
