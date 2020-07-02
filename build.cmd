: need to learn make files...
del Debug /Q
mkdir Debug
cl /nologo /EHsc /Fo:Debug\ json\parser\parse.cpp json\parser\Parser.cpp json\parser\Tokenizer.cpp json\types\Array.cpp json\types\Number.cpp json\types\Object.cpp json\types\String.cpp json\utils\escapeQuotes.cpp json\utils\unescapeQuotes.cpp json\utils\fromTokenTypeToString.cpp main.cpp /Fe:Debug\json.exe