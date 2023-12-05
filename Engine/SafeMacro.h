#pragma once

// ReleaseŠÖ”‚ðŽ‚Á‚Ä‚é‚â‚Â
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

// ƒ|ƒCƒ“ƒ^‚Ì‰ð•ú
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}