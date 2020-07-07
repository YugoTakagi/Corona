# Corona

Corona is **motorSistem for 下腿人工関節シミュレータ**.



- Client as 通信を持ちかけるライブラリ
- Server as 通信を待っているライブラリ
- TsvToCsv as OpenSimから目標値を取り出すライブラリ





## How to use Client

Client はRaspberry Piで実行するプログラム.



 ==**※ Serverを実行してから**==

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



### > sub directory muscle

muscle は**筋をイメージしたオブジェクト**. muscle class の為のヘッダーファイルが増えたので sub directory纏めた.

muscle は目標値( 筋張力[N] )に追従するように, motorを制御する. 



### >sub directory tcpClient

tcpClient は, **TCP/IP通信のクライアントをイメージしたオブジェクト**. 





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



### >sub directory tcpServer

tcpServer は, **TCP/IP通信のサーバをイメージしたオブジェクト**. 

