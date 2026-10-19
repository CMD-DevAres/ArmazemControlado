gcc src/main.c src/armazem.c -o programa.exe

if ($LASTEXITCODE -eq 0) {
    .\programa.exe
}
