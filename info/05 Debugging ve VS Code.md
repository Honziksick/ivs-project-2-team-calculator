Debugging ve VS Code
--------------------

__Debugging ve VS Code__ není nic příjemného, pokud člověk využívá WSL v systému Windows. VS Code totiž vyžaduje speciální soubor `.json`, které dokáží debugging pěkně ztížit, ale pokud člověk pochopí o co se jedná, dokáží udělat život jednodušším. Vrhněme se tedy do tajů debugging `.c/.cpp` programů ve VS Code.

_V mnou připravených souborech máte více konfigurací. Ty uvedené v tomto souboru jsou pouze ilustrační._

## Prerekvizity aneb mé prostředí, kde to funguje
- mít spustitelný soubor (program/binárku) obsahující funkci `main()`
  - tedy pokud potřebujeme debuggovat knihovnu, tak si nejdřív musíme vytvořit program, který danou knihovnu využívá a následně debuggovat tento program, který volá funkce z naší knihovny (v debuggeru __Step into__)
- spouštět VS Code přes WSL pomocí příkazu `code <file_name>`
  - toto si jednoduše ověříte tak, že se vám v levém dolním rohu zobrazuje text `WSL: Ubuntu`
- v rámci VS Code je nutné otevřít si složku s projektem/repozitářem
  - debugging našeho projektu je nakonfigurován tak, že VS Code očekává že je otevřena kořenová složka repozitáře (aneb ta obsahující složku `.git`)
- náš projekt dále očekává, že je Makefile umístěn v adresáři `src/`
- poslední nutností je mít ve VS Code nainstalováno rozšíření `C/C++`

## Jak na to?
1) ve složce `.vscode` je nutné vytvořit konfigurační soubory `launch.json`, `tasks.json` a `c_cpp_properties.json`
    - `launch.json`
      - tento soubor obsahuje konfigurace pro spuštění debuggeru
    - `tasks.json`
      - tento soubor obsahuje terminálové příkazy pro spuštění příkazu `make <command>`
    - `c_cpp_properties.json`
      - tento soubor je konfiguračním souborem vašeho C++ obsahující například informace o typu operačního systému nebo kompilátor, který je používán ke stavbě projektu.

<br>

2) vytvoříme soubor `.vscode/c_cpp_properties.json`
    - tento soubor není ničím zajímavý a je možné, že se vám dokonce již vygeneroval automaticky, pokud používáte rozšíření `C/C++`
    - pokud využíváte WSL, tak je silně pravděpodobné, že váš soubor bude vypadat stejně, pokud programujete jiným způsobem, může se lišit

```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```
<br>

3) vytvoříme soubor `tasks.json`
    - do tohoto souboru můžete přidávat jednotlivé příkazy projektového Makefile, pokud byste chtěli provádět stavbu programu přímo ve VS Code
    - `label` je pojmenování daného tasku, kterým je pak určen debugging task v souboru `launch.json`
    - Dejte si pozor na mezery v cestě k pracovnímu adresáři - doporučuju dávat `${workspaceFolder}/src` do uvozovek `\"${workspaceFolder}/src\"`

```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build-test-debug",
            "type": "shell",
            "command": "make -C \"${workspaceFolder}/src\" build-test-debug",
            "group": "build",
            "presentation": {
                "reveal": "always"
            },
            "problemMatcher": []
        }
    ]
}
```
<br>

4) vytvoříme soubor `launch.json`
    - v tomto souboru si definujete debugging úkoly - tedy jakým způsobem se budou programy pro debugging spouštět a jak se budou zobrazovat ve VS Code záložce __Spustit a ladit__
    - `name` určuje název daného úkolu pro debugging
    - `program` je relativní cestou od pracovního adresáře až k přeloženému programu
    - `args` je argumenty/parametry, které můžeme při spuštění programu předat
      - např. `-h`, `"<", "${workspaceFolder}/src/tests/input.txt"`
    - `preLaunchTask` je vyhledává task s daným label v souboru `tasks.json`, resp. provede před spuštěním debuggingu příkaz `make`, který se používá ke stavbě programu, který chceme debuggovat

```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) core tests for debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/src/build/tests/cat_calc_core_test_debug",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "miDebuggerPath": "/usr/bin/gdb",
            "preLaunchTask": "build-test-debug",
        }
    ]
}
```
<br>

5) spustíme debugging v VS Code záložce __Spustit a ladit__
    - rozklikněte tuto záložku
    - v její horní části si z menu vyberte debugging task, který budete chtít spustit
    - klikněte na zelený trojúhelníček a spusťte debugger

<br>

---

*Datum poslední úpravy: 15. 4. 2024, 11:20*