# Архиватор

В проекте реализован архиватор
посредством [алгоритма Хаффмана](https://en.wikipedia.org/wiki/Huffman_coding).

Программа-архиватор имеет следующий интерфейс командной строки:

* `Archiver -c archive_name file1 [file2 ...]` - заархивировать файлы `fil1, file2, ...` и сохранить результат в
  файл `archive_name`.
* `Archiver -d archive_name` - разархивировать файлы из архива `archive_name` и положить в текущую директорию. Имена
  файлов должны сохраняться при архивации и разархивации.
* `Archiver -h` - вывести справку по использованию программы.
