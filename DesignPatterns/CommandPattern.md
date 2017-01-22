# Command Pattern（命令模式）

`行为型模式`

## 意图

命令模式可以对发送者和接收者完全解耦，发送者与接收者之间**没有直接引用关系**，发送请求的对象只需要知道如何发送请求，而不必知道如何完成请求。

## 定义

将一个请求封装为一个对象，从而使我们可用不同的请求对客户进行参数化。

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
