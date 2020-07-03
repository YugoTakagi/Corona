# Corona

Corona is **motorSistem for 下腿人工関節シミュレータ**.



- Client as 通信を持ちかけるライブラリ

- Server as 通信を待っているライブラリ



## How to use Client

Client はRaspberry Piで実行するプログラム.



 ==※ Serverを実行してから==

```bash
#実行方法
$ pwd
	xxxxxx/Client/build/
$ cmake ..
$ cmake --build .
$ ./main (port num) #Serverが待っているport
```

もし, `$ ld: No such file or directory ` がでたら, cmakeが悪さをしているので, 

```bash
$ pwd
	xxxxxx/Client/build/
$ rm -rf *
xxxxxxxxxx [yn]? #yを入力してEnter
```

で, buildフォルダの中身を全部消してから, もう一度実行方法を行う😌





## How to use Server

Server はMacで実行するプログラム.



```bash
#実行方法
$ pwd
	xxxxxx/Server/build/
$ cmake ..
$ cmake --build .
$ ./main
```

