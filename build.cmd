: need to learn make files...
del Debug /Q
mkdir Debug
cl /nologo /EHsc /Fo:Debug\ json\parser\*.cpp json\types\*.cpp json\utils\*.cpp main.cpp /Fe:Debug\json.exe