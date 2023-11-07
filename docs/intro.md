# Что это? 
[tasm-makeconfig](https://github.com/zafod42/tasm-makeconfig) Это программа, которая генерирует
файлы конфигурации для DOSBOX. Которые в свою очередь выполняют такие задачи как:
    - Сборка
    - Запуск
        Программ на ассемблере TASM с использованием пакета TASM 4.1
# Этапы
## Сборка
    Генерирование файла конфигурации для сборка осуществляет функция `write_builder_config`
        Inputs:
        - std::ofstream& file -- ссылка на файл записи конфигурациооного файла 
        - const std::string path -- путь по которому будет лежать конфигурационный файл
        - const std::string tasmPath -- путь по которому лежат binutils TASM
        - const std::string sourcePath -- путь по которому лежит исходный код
        - const std::string outputPath -- путь по которому будет лежать собранный файл
        - const std::string filename -- имя исходного файла

    Имя файла filename обрезается до точки - то есть остаётся только имя без расширения
    Данная фукнция генерирует конфигурациооный файл следующего вида:
    ```
    [autoexec]
    @echo off
    mount c: <tasmPath> 
    mount d: <sourcePath>
    mount f: <outputPath>
    path=z:\;c:\
    f:
    tasm d:\<filename>.asm > f:\build.log
    tlink <filename>.obj > f:\link.log
    cls
    exit
    ```
## Запуск
    Генерирование файла конфигурации для запуска осуществляет функция `write_runner_config`
        Inputs:
        - std::ofstream& file -- ссылка на файл записи конфигурациооного файла 
        - const std::string path -- путь по которому будет лежать конфигурационный файл
        - const std::string binaryPath -- путь по которому лежит запускаемый файл
        - const std::string filename -- имя исходного файла

    Важно! Для этой функции filename не обрезается. При вызове необходимо указывать полное имя файла.
    Функция генерирует файл похожего вида:
        ```
    [autoexec]
    @echo off
    mount d: <binaryPath> 
    path=z:\;c:\
    d:
    cls
    d:\<filename> 
    exit
    ```
## Порядок вызова программы
Usage: 
normal usage:
        tasm-makeconfig <output path> <binary path> <binary name>
                output path     - path/to/dir where config will be created
                binary path     - path/to/dir where binary is located
                binary name     - name of binary file

--build option:
        tasm-makeconfig --build <output path> <tasm path> <source path> <source name>
                output path     - path/to/dir where config will be created
                tasm path       - path/to/dir where tasm binutils is located
                source path     - path/to/dir where asm source file is located
                binary output path      - path/to/dir where binary will be created
                source name     - name of asm source file

