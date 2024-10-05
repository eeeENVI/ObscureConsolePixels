# Why-won't-you-cease-to-exist- ObscurePixels Project by eeeENVI
aive no 1dea wot 50 eva m8
I'll end this project with some simple 3d support and after FULL HD 1920x1080 characters will run in 60 fps with console font setsize=1, right now its around ~20-30 
it uses CSI functionality builded in consoles, to make it work you need to add key to registry:

HKEY_CURRENT_USER\Console\VirtualTerminalLevel type: RED_DWORD value: 1

ncurses worst nightmare, pure c++ only standard libraries no externals or windows.h or other stuff like that  _._

IMPLEMENTED:
alpha blending ( linear color interpolation )

TO DO:
Matrix calculations support
fast simple primitives ( lines,traingles,elipses)
jpg,png support

antialiasing
supersampling

improve drawing & memory managament
delete redundancy


