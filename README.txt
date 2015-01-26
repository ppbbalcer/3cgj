What Shall We Do Now - Revenge of the GM
README file

This is PRE ALPHA RELEASE.

To run game double click onto executable (Windows) or build it yourself (Linux).

You can also make your own levels by creating new files in the
Resources/levels folder.

This game is released under THREE CLAUSE BSD LICENSE


Copyright (c) 2015, Pawłowski Sławomir, Kaminski Maciej, Naruszewicz Maciej, Balcer Piotr
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

RELEASE NOTES:

Following problems are known:

- when character is moving quickly and shoting in the same time,
  fireballs may appear in character's previous location. This is
  rare graphical glitch, that does not affect gameplay or stable
  operation of product

- when working directory DOESN'T contain resources directory,
  execution fails.

- in Windows 8 the screen might get scaled unproportionally, in
  such case disabling display scaling on high DPI settings should
  help (right click on the executable file "Revenge of the GM.exe",
  Compatibility -> Disable display scaling on high DPI settings

- Game wasn't designed to run on dual monitor setups and may crash on
  such.
