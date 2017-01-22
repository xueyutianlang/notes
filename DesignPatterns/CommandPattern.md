# Command Pattern（命令模式）

`行为型模式`

## 定义

> 命令模式把一个请求或操作封装到一个对象中。命令模式允许系统使用不同的请求客户端参数化，对请求排队或者请求记录日志，可以提供命令的撤销和恢复功能。——《Java与模式》

## 意图

把发出命令的责任和执行命令的责任分隔开，委派给不同的对象。

## 优点

- 使新的命令很容易地被加入到系统里。
- 允许接收请求的一方决定是否要否决请求。
- 能较容易地设计一个命令队列。
- 可以很容易地实现对请求的 Undo 和 Redo。
- 较容易地讲命令计入日志。

## UML

<img src="https://yuml.me/diagram/nofunky/class/[Client%7C%7C],[Invoker%7C%7C+action():void],[ConcreteCommand%7C%7C+execute():void],[Receiver%7C%7C+action():void],[Client]-.-%3E[Invoker],[Invoker]%3C%3E-%3E[%3C%3CCommand%3E%3E],[Client]-.-%3E[Receiver],[%3C%3CCommand%3E%3E]%5E-.-[ConcreteCommand],[ConcreteCommand]-receiver%20%3E[Receiver]">

- Client（客户角色）：创建一个具体命令对象并确定其接收者。
- Command（命令角色）：声明一个具体命令类的抽象接口。
- ConcreteCommand（具体命令角色）：定义一个接收者和行为之间的弱耦合，实现 execute() 方法，负责调用接收者的响应操作。execute() 方法通常叫做执行方法。
- Invoker（请求者角色）：负责调用命令对象执行，先相关的方法叫做行动方法。
- Receiver（接收者角色）：负责具体实施和执行一个请求。实施和执行请求的方法叫做行动方法。


## 代码

```php
<?php
/**
 * main.php
 * @author netsan
 */
//请求者角色
class Invoker
{
    protected $command = null;
    public function __construct(Command $command)
    {
        $this->command = $command;
    }
    //调用命令对象执行请求[行动方法]
    public function action()
    {
        echo __METHOD__,PHP_EOL;
        $this->command->execute();
    }
}
//命令角色（接口）
interface Command
{
    //负责调用接收者相应操作[执行方法]
    public function execute();
}
//具体命令对象
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
//接收者角色
class Receiver
{
    //具体实施和执行一个请求[行动方法]
    public function action()
    {
        echo __METHOD__,PHP_EOL;
    }
}
//客户角色
class Client
{
    public static function main()
    {
        $receiver = new Receiver();
        $command  = new ConcreteCommand($receiver);
        $invoker  = new Invoker($command);
        $invoker->action();
    }
}
Client::main();
```

```bash
$ php main.php
Invoker::action
ConcreteCommand::execute
Receiver::action
```
