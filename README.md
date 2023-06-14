# SIRE: Simple Immediate Renderer
A single header library that makes immediate mode style rendering fun.

## Compatibility
- DirectX9
- DirectX10
- DirectX11

## Example
Usage example, drawing a triangle.
 ```C++
int main(int argc, char* argv[]) {
  // Init device first
  // ... 
  
  Sire::Init(Sire::SIRE_RENDERER_DX11, pSwapChain); // <- pass dxgi swapchain as argument
  
  while (...) {
    /// Clear render target view.
    
    Sire::SetProjectionMode(Sire::SIRE_PROJ_ORTHOGRAPHIC);
    Sire::SetTexture(nullptr, nullptr);
    
    Sire::Begin(Sire::SIRE_TRIANGLE);    
    Sire::SetVertex2f(0.0f, 0.5f);
    Sire::SetVertex2f(0.45f, -0.5f);
    Sire::SetVertex2f(-0.45f, -0.5f);
    Sire::End();
        
    /// Present.
  }
  
  Sire::Shutdown();
  
  // Shutdown device after
  // ...
}
 
 ```
