#pragma once

// Release関数を持ってるやつ
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

// ポインタの解放
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}