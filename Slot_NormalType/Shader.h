#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include <unordered_map>

class Shader 
{
public:
    //シングルトン
    static Shader& Instance()
    {
        static Shader instance;
        return instance;
    }

    ID3DBlob* LoadVS(const std::string& path);
    ID3DBlob* LoadPS(const std::string& path);

private:
    Shader() = default;

    //共通読み込み関数
    ID3DBlob* Load(const std::string& path);

    //キャッシュ
    std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> cache;
};