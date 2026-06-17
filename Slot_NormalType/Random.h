#pragma once
#include <Windows.h>
#include <bcrypt.h>
#include <cstdint>

#pragma comment(lib, "bcrypt.lib")

//Xoroshiro128++アルゴリズムを実装したクラス
struct Xoroshiro128PP {
	uint64_t s[2];  //状態を保持する配列(64bit×2)

	//64bitの値を左回転する関数
	static inline uint64_t rotl(const uint64_t x, int k) {
		return (x << k) | (x >> (64 - k));
	}

	//乱数生成（64bit）
	uint64_t next() {
		//状態をコピー
		const uint64_t s0 = s[0];
		uint64_t s1 = s[1];

		//s0とs1を足してから17ビット左回転し、さらにs0を加算して返す
		const uint64_t result = rotl(s0 + s1, 17) + s0;

		//s1をs0とXOR演算する
		s1 ^= s0;

		//s0を49ビット左回転し、s1とXOR演算し、さらにs1を21ビット左シフトした値とXOR演算してs[0]に代入
		s[0] = rotl(s0, 49) ^ s1 ^ (s1 << 21);
		//s1を28ビット左回転してs[1]に代入
		s[1] = rotl(s1, 28);

		//生成された乱数を返す
		return result;
	}

	//シード設定
	void seed(uint64_t a, uint64_t b) {
		//全ゼロは禁止
		//変化しない状態を避けるため
		if (a == 0 && b == 0) b = 1;
		s[0] = a;
		s[1] = b;
	}

	//16bitの乱数を取得する関数
	[[nodiscard]]uint16_t GetRandom16()
	{
		return next() & 0xFFFF;
	}
};


//ハード乱数の64bit乱数を返す
uint64_t GetHardwareRandom64()
{
	uint64_t v;

	BCryptGenRandom(
		nullptr,                        //プロバイダーのハンドル
		reinterpret_cast<PUCHAR>(&v),   //バッファの先頭アドレス
		sizeof(v),                      //バッファのサイズ
		BCRYPT_USE_SYSTEM_PREFERRED_RNG //動作を変更するフラグ(これとハンドルnullptrで既定の乱数生成器を使用)
	);
	return v;
}
