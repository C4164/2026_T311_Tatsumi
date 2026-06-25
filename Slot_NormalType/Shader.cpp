#include "Shader.h"
#include <d3dcompiler.h>

ID3DBlob* Shader::LoadVS(const std::string& path)
{
    return Load(path);
}

ID3DBlob* Shader::LoadPS(const std::string& path)
{
    return Load(path);
}

ID3DBlob* Shader::Load(const std::string& path)
{
    //ÉLÉÉÉbÉVÉÖÇ…Ç†ÇÈÇ©Ç«Ç§Ç©
    auto it = cache.find(path);
    if (it != cache.end())
    {
        return it->second.Get();
    }

    //ì«Ç›çûÇ›
    Microsoft::WRL::ComPtr<ID3DBlob> blob;
    HRESULT hr = D3DReadFileToBlob(std::wstring(path.begin(), path.end()).c_str(), &blob);

    if (FAILED(hr))
    {
        OutputDebugStringA(("Shader Load Failed: " + path + "\n").c_str());
        return nullptr;
    }

    cache[path] = blob;
    return blob.Get();
}
