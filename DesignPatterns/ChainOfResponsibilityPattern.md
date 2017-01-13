# Chain Of Reponsibility Pattern（责任链模式）

## 总览

> 责任链模式：对象由每一个对象对其下家的引用而连接起来形成一条链。请求在这个链上传递，直到链上的某一个对象决定处理此请求。发出请求的客户端并不知道链上的哪一个对象最终处理这个请求，这使得系统可以在不影响客户端的情况下动态地重新组织和分配责任。

责任链模式属于**行为模式**。

## UML

<img src="https://yuml.me/diagram/nofunky/class/[Handler%7Csuccessor:%20Handler%7C+setSuccessor():%20void;+handleRequest():%20void;],[ConcreteHandlerA%7C%7C+handleRequest():%20void],[ConcreteHandlerB%7C%7C+handleRequest():%20void],[Client%7C%7C],[Handler]%5E-[ConcreteHandlerA],[Handler]%5E-[ConcreteHandlerB],[Handler]%3C%3E-%3E[Handler],[Client]-.-%3E[Handler]">

- Handler：定义职责接口，通常在内部定义处理请求的方法，可以在这里实现后继链
- ConcreteHandler：实际职责类，实现在它的职责范围内的请求处理，如果不处理，就继续转发请求给后继者
- Client：客户端，组装职责链，向链上的具体对象提交请求

## 用途

使得多个**请求处理者**都有机会处理请求，避免**请求发送者**和**请求处理者**间的耦合关系。多个**请求处理者**形成一条链，并沿着这条链传递请求，直到对象处理它为止。

客户端发出一个请求，链上的对象都有机会来处理这一请求，而客户端不需要知道谁是具体的处理对象。这样就实现了请求者和接受者之间的解耦，并且在客户端可以实现动态的组合职责链。

每个请求都不拦截，而是一步步的往下传，每一步都会处理请求对象，就可以变形成处理请求功能链。

## 场景

- 有多个对象可以处理同一个请求，具体哪个对象处理该请求由运行时刻自动确定
- 在不明确指定接收者的情况下，向多个对象中的一个提交一个请求
- 可动态指定一组对象处理请求

## 实例

- Java Web 中的过滤器链
- Struts2 中的拦截器栈

## 代码

```php
# main.php

//职责接口
abstract class Handler
{
    protected $successor = null;//后继职责对象

    //设置后继职责对象
    public function setSuccessor(Handler $handler)
    {
        $this->successor = $handler;
    }

    //抽象父类统一请求处理方法
    //可以在方法中传值 作为判断条件 也可以不传值利用其它外部条件
    abstract public function handleRequest($count);
}

// 具体职责对象
class ConcreteHandlerA extends Handler
{
    public function handleRequest($count)
    {
        if ($count < 1000) {
            //自己职责范围
            echo __CALSS__," Handle",PHP_EOL;
        } else {
            echo __CLASS__," Post",PHP_EOL;
            //非自己，请求下发
            $this->successor->handleRequest($count);
        }
    }
}

// 具体职责对象
class ConcreteHandlerB extends Handler
{
    public function handleRequest($count)
    {
        //一定能处理，不再下发
        echo __CLASS__," Handle", PHP_EOL;
    }
}

//负责组装职责链，并发起请求
class Client
{
    public static function main()
    {
        //构造职责对象
        $handlerA = new ConcreteHandlerA();
        $handlerB = new ConcreteHandlerB();
        //组装职责链
        $handlerA->setSuccessor($handlerB);
        //发起请求
        $handlerA->handleRequest(2000);
    }
}

Client::main();
```

```bash
$ php main.php
ConcreteHandlerA Post
ConcreteHandlerB Handle
```

时序图：

<img src="http://www.gravizo.com/g?@startuml;participant%20%22%20%E5%AE%A2%E6%88%B7%E7%AB%AF%22%20as%20C;participant%20%22%E8%81%8C%E8%B4%A3%E5%AF%B9%E8%B1%A1A%22%20as%20A;participant%20%22%E8%81%8C%E8%B4%A3%E5%AF%B9%E8%B1%A1B%22%20as%20B;C%20-%3E%20A:%20%E5%8F%91%E5%87%BA%E8%AF%B7%E6%B1%82;activate%20A;A%20-%3E%20B:%20%E4%B8%8B%E5%8F%91%E8%AF%B7%E6%B1%82;activate%20B;note%20over%20B:%20%E5%A4%84%E7%90%86%E5%93%8D%E5%BA%94;B%20--%3E%20A:%20%E5%9B%9E%E5%BA%94%E8%AF%B7%E6%B1%82;A%20--%3E%20C;@enduml;">

## 优点

- 请求者和接受者松散耦合：请求者不需要知道接受者，也不需要知道如何处理。每个职责对象只负责自己的职责范围，其他的交给后继者。各个组件间完全解耦。
- 动态组合职责：职责链模式会把功能分散到单独的职责对象中，然后在使用时动态的组合形成链，从而可以灵活的分配职责对象，也可以灵活的添加改变对象职责。

## 缺点

- 产生很多细粒度的对象：因为功能处理都分散到了单独的职责对象中，每个对象功能单一，要把整个流程处理完，需要很多的职责对象，会产生大量的细粒度职责对象。
- 不一定能处理：每个职责对象都只负责自己的部分，这样就可以出现某个请求，即使把整个链走完，都没有职责对象处理它。这就需要提供默认处理，并且注意构造链的有效性


## 参考

- [责任链模式](http://www.runoob.com/design-pattern/chain-of-responsibility-pattern.html)
- [设计模式-职责链/责任链模式(Chain of Responsibility)分析理解和在Android的应用](http://blog.csdn.net/card361401376/article/details/51552568)
