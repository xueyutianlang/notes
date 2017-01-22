# Command Pattern（命令模式）

`行为型模式`

## 定义

> 命令模式把一个请求或操作封装到一个对象中。命令模式允许系统使用不同的请求客户端参数化，对请求排队或者请求记录日志，可以提供命令的撤销和恢复功能。——《Java与模式》

## UML

- Command：抽象命令类
- ConcreteCommand：具体命令类
- Invoker：调用者
- Receiver：接受者
- Client：客户类

## 代码

```php
<?php
#main.php
interface Command
{
    public function execute();
}

class ConcreteCommand implements Command
{
    protected $receiver = null;

    public function __construct(Receiver $receiver)
    {
        $this->receiver = $receiver;
    }

    public function execute()
    {
        echo __METHOD__,PHP_EOL;
        $this->receiver->action();
    }
}

class Receiver
{
    public function action()
    {
        echo __METHOD__,PHP_EOL;
    }
}

class Invoker
{
    protected $command = null;

    public function __construct(Command $command)
    {
        $this->command = $command;
    }

    public function call()
    {
        echo __METHOD__,PHP_EOL;
        $this->command->execute();
    }
}

class Client
{
    public static function main()
    {
        $invoker = new Invoker(new ConcreteCommand(new Receiver()));
        $invoker->call();
    }
}

Client::main();
```
