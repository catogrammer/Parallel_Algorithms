# Lecture 1

**Типы ядра**
​	* Мнолитное ядро
​		User $<-> | <->​$ Kernel
​	* Разделенное ядро [микроядро]
​		All services in user area
**Режимы**
​	* Обычный
​	* защищенный

# cmd

sh(shell), bash, dash, zsh
csh(C shell)
ash(Algorithm shell)
​
'|' - conveyor

Внешняя (date pwd, cd, ls)
Внутренняя(echo)

Get enviroment variable
~ echo '$'PWD

Add path enviroment variable
~ export PATH= /home/you_path/ :PATH

Print working directory
~ pwd

Print process
~ ps -ef

Search smth
~ grep

Delete process
~ kill number_you_pocess

Trinslate proces in font mode

~ cat/etc/blablalba > ./nahuy.txt
~ cat/etc/blablalba 1> ./nahuy.txt		    // 1 - поток вывода
​								// 2 - поток ошибок
​								// 0 - поток ввода
$ cat/etc/blablalba >> ./nahuy.txt //дописывает

# Lecture 2

**Процесс**
​	- стек
​	- ...


**Поток**
​	- процесс
​	- IP

	void exit() - упраление сразу передается ядру (ресурсы не освобождаются)
	void Exit() - вызов дополнительных функций, до передачи управления ядру (освобождение ресурсов)

**PID** - number of 16 bit - settings of kernel

~ man getpid

	int main(){
	    pid_t pid, ppid, uid;
	    pid = getpid();
	    ......
	}

**Make process**
- fork - for system process (make two equals process) return 0 for parrant process
- exec
- wait / waitpid[id_process] (ending douther process) return -1 for douther process

exec - замещение текущего адресного пространства другим

## Lab 1
	Кажое дерево одна программа.
	1 каждый процес должен вывести свои характеристики
	2 каждый процесс должен дожидаться своих дочерних

* Переменные окружения
* сигналы (~ kill -l)
* Каналы
  - Именнованные
  - Неименованные

# Lecture 3

**XSI PSI - System 5**
