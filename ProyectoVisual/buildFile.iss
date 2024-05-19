
[Setup]
AppName=Flonk!
AppVersion=0.9
WizardStyle=modern
DefaultDirName={autopf}\"Flonk a frog adventure"
DefaultGroupName=My Program
UninstallDisplayIcon={app}\MyProg.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "\bin\FrogDebug.exe"; DestDir: "{app}"; DestName: "flonk.exe"
;recursos, estaría bien no incluir los archivos de prueba
Source: "\Frog\resources\config\*"; DestDir: "{app}\resources\config\"
Source: "\Frog\resources\fonts\*"; DestDir: "{app}\resources\fonts\"
Source: "\Frog\resources\Buttons\*"; DestDir: "{app}\resources\Buttons\"
Source: "\Frog\resources\maps\*"; DestDir: "{app}\resources\maps\"
Source: "\Frog\resources\Menus\*"; DestDir: "{app}\resources\Menus\"
Source: "\Frog\resources\Sound\*"; DestDir: "{app}\resources\Sound\"
Source: "\Frog\resources\Sprites\*"; DestDir: "{app}\resources\Sprites\"
;librerias
Source: "\SDL2\lib\*"; DestDir: "{app}\SDL2\"
Source: "\SDL2_image\lib\*"; DestDir: "{app}\SDL2_image\lib\"
Source: "\SDL2_mixer-2.0.2\lib\*"; DestDir: "{app}\SDL2_mixer-2.0.2\lib\"
Source: "\SDL2_ttf-2.0.14\lib\*"; DestDir: "{app}\SDL2_ttf-2.0.14\lib\"
Source: "\tmxlite\lib\*"; DestDir: "{app}\tmxlite\lib\"


[Icons]
Name: "{group}\Flonk"; Filename: "{app}\flonk.exe"
