@echo off
%~d0
cd %~dp0
set path=%path%;%cd%\bin\flex\
flex --wincompat -+ -o gen\ray.lex.cc lex\ray.L
copy /y .\bin\flex\FlexLexer.h .\gen\ >nul
copy /y .\src\token.h .\gen\ >nul
copy /y .\bin\flex\FlexLexer.h .\src\ >nul
set path=%path%;"F:\Program Files (x86)\LLVM\bin\"
cd gen
set src_path=%~dp0\src
set src_file=%src_path%\main.cc %src_path%\ast.cc
@echo on
clang++ ray.lex.cc %src_file% -static -o ray.exe -I.
@echo off
cd ..