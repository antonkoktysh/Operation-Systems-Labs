
4.2. Написать программы для консольного процесса Administrator и консольных процессов Reader и Writer. Для моделирования передачи сообщений ввести специальные события (c автоматическим сбросом), которые обозначают сообщение “A” , сообщение “B”,  и конец сеанса для процессов Reader и Writer. 
Одновременно принимать и отправлять сообщения могут только 3 активных процесса Writer (использовать семафор) и 1 активный процесс Reader (использовать мьютекс), передача остальных сообщений от других процессов должна временно блокироваться (находиться в режиме ожидания).

Процесс Administrator:
	1. Инициализация объектов синхронизации.
	2. Запрашивает у пользователя количество процессов Reader и Writer, которые он должен запустить.
	3. Запрашивает у пользователя кол-во отправленных сообщений для процесса Writer и кол-во принятых сообщений для процесса Reader(общее количество отправленных и принятых сообщений должно совпадать).
	4. Запускает заданное количество процессов Reader и Writer. Одновременно принимать и отправлять сообщения могут только три процесса Writer(использовать семафор),  и один процесс Reader(использовать мьютекс), передача остальных сообщений от других процессов должна блокироваться(находиться в режиме ожидания).
	5. Принимает от каждого процесса Reader и Writer сообщение о завершении  сеанса и выводит его на консоль в одной строке. 
	6. Завершает свою работу.

Процесс Writer:
	1. Синхронизировать работу процессов Writer с помощью семафора.
	2. Передачу сообщений реализовать с помощью событий.
	3. Запрашивает с консоли сообщения, и передает их (по одному) процессу Reader.
	4. Передает сообщение о завершении  сеанса процессу Administrator.
	5. Завершает свою работу.

Процесс Reader:
	1. Синхронизировать работу процессов Reader с помощью мьютекса.
	2. Передачу сообщений реализовать с помощью событий.
	3. Принимает сообщения от  процесса Writer.
	4. Выводит на консоль сообщение.
	5. Передает сообщение о завершении  сеанса процессу Administrator.
