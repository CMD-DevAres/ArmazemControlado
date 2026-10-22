gcc -Wall -Wextra -g3 src/main.c src/armazem.c -o src/output/main.exe

if ($LASTEXITCODE -eq 0) {
    .\src\output\main.exe
}
