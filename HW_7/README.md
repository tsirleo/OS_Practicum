# ДЗ №7

В командной строке передается имя файла. Процесс-отец создает «сына», затем открывает файл, и далее происходит работа в цикле до конца файла:

1. «Отец» передает «сыну» очередную строку файла.

2. «Сын» читает переданную ему строку, реверсирует ее, оставляя на месте **'\n'**, если он есть, и возвращает измененную строку «отцу».

3. Тот читает ее и выводит в файл.

В результате должен быть изменен исходный файл (все строки записаны задом наперед).