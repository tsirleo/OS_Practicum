# Зачетная работа

В командной строке передаются имена исполняемых файлов с аргументами. Эти группы разделены строкой "+". Количество заданных имен не более 3. В конце командной строки возможно задание пары **-o _имя_файла_** для перенаправления вывода в указанный файл.

Требуется запустить указанные программы на параллельную обработку в виде конвейера и при необходимости перенаправить вывод в заданный файл.

Пример вызова:
```shell
> ./prog ls -l -a + sort -r + cat -o file
> ./prog ls -l -a + sort -r
> ./prog ls -o file
> ./prog ls -l
```
