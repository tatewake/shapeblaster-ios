# ShapeBlaster for iOS

By Terence J. Grant - tjgrant [at] tatewake [dot] com

## License

**The BSD 2-Clause License**

Copyright (c) 2013, Terence J. Grant

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## Notes

ShapeBlaster for iOS is a port of ShapeBlaster for XNA / C# by Michael Hoffman.

The primary language used in this port is C++, and the primary API is OpenGL ES 2.0. There's also a light mix of some custom classes (called the **Utility library**) I've written to act as an impromptu game framework.

  * **Debug mode runs slower than Release mode!** To enable release mode:
    * Choose **Edit Scheme** from the **Product** menu.
    * Select **Run ShapeBlaster** from the left pane in the window that appears.
    * In the right pane, make sure **Info** is the selected tab.
    * In the right pane, select **release** in the **Build Configuration** setting.
    * Hit the **OK** button
    * **Build** and **Run**. You'll definitely notice speed improvements.
  * **Bloom Post-processing** is possible, though I was not able to get it running at a decent framerate, so it's been omitted.
  * **Warping Grid** uses 600 points rather than the original's 1600 as it's spring / physics and drawing calculations are very expensive.
  * **The iOS simulator** runs slower than actual hardware; you'll see best performance on actual hardware.
  * **72 DPI** is the correct resolution for textures on iOS / Mac. Other DPIs can give unexpected performance. Since XNA uses 96 DPI, the images from the original project had to be resampled.

