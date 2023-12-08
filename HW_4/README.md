# ДЗ №4
В командной строке передаются два имени файлов.

Если оба имени указывают на один и тот же файл (помним, что один файл может иметь несколько имен), выдать диагностику и ничего делать, иначе первый файл — исходный, во второй записать результат обработки.

**Обработка файла:**

Файл исходный — не текстовый, бинарный. В файле содержатся 32-битные целые знаковые числа. Переставить в исходном файле числа так, чтобы в начале файла располагались
отрицательные числа, а в конце — неотрицательные. Порядок чисел среди чисел одного знака произвольный. Файл в память целиком не считывать. Можно одновременно считывать не более
10 чисел файла. Временный файл создавать нельзя.

Использовать функции низкоуровневой работы с файлами.

В файл-результат записать текстовую версию обработанного файла — числа в текстовом виде через пробел. Для этого удобней использовать функции высокого уровня.

Для тестирования написать программу создания исходного файла. Учесть, что файл может быть пустым, может содержать только числа одного знака.