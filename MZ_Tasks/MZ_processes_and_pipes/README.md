# Проверочная работа "Процессы.Каналы."

В командной строке передается имя файла.

Процесс-отец создает "сына". Сын считывает со стандартного ввода число **x** и строку (длина не больше 80), записывает строку в файл и передает отцу число и строку.

Отец заменяет в середине строки **x** символов на **'*'**, результат выводит в тот же файл после строки записанной сыном. Если **x** больше длины строки, просто выводит строку из **x** символов **'*'**. Работа продолжается до получения сыном строки **"exit"**.

Синхронизировать работу с файлом с помощью аппарата каналов.

Если работа с файлом осуществляется с использованием функций высокого уровня, после каждого вызова рекомендуется сбрасывать буфер с помощью вызова функции **fflush()**.

Завершение процессов также должно быть аккуратным — с закрытием файла.