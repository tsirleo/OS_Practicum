# ДЗ №8

## Задание 1

Доделать задачу с семинара (немного расширена)

Реализовать игру в «ping-pomg» для 3 процессов (кому мало, можно для произвольного **N >= 2** ‚ **N** задавать в командной строке).

Главный процесс порождает двух (N-1) потомков по любой схеме (2 сына или сын-внук) и начинает передачу данных. Начальное и конечное целые числа переданы в командной строке. Принимающий
увеличивает число на 1 и передает дальше, и так по кругу до тех пор, пока число не превысит заданный максимум.

Каждый процесс выводит на экран текущее число и свой **pid**.

Необходимо предоставить две реализации программы:
1. Обмен данными через каналы (каждая пара процессов связана отдельным каналом).

2. Обмен данными через один канал. Синхронизация обращений к каналу должна быть организована с помощью сигналов.

Обратите внимание на завершение работы, лишних чисел выводиться не должно.

## Задание 2

Протестировать работу сигналов в используемой Вами системе. Написать тестовые программы, которые позволяют ответить на эти вопросы, и дать комментарий по поводу результатов — что у вас получилось.

1. Сбрасывается ли обработка сигнала на значение по умолчанию после вызова обработчика, если нет явной переустановки?

2. Блокируется ли на время работы обработчика
   * тот же сигнал, что в данный момент обрабатывается,
   * другие сигналы?
3. При посылке сигнала всей своей группе получает ли этот сигнал тот процесс, который его отправляет?

4. Возобновляет ли работу функция **wait()**, если во время ожидания пришел сигнал, или она завершается с ошибкой?