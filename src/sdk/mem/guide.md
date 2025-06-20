# How to find Signatures and Offsets

**Functions**
- SplashTextRenderer::render
  - Search for "splashes"
  - Jump to xref once
  - Get the function "_loadSplashes"
  - Jump to xref once more
  - Completed.
- MinecraftGame::update
  - Search for "---MainThread---"
  - Jump to xref twice until you reach a function
  - Completed.
- mce::TextureGroup::getTexture
  - Search for "{}absorption_heart_half"
  - Function at the end with 6 paramaters is getTexture
  - Completed.
- mce::TextureGroup::uploadTexture
  - Go to getTexture in the same class
  - Find three paramater function
  - Completed.