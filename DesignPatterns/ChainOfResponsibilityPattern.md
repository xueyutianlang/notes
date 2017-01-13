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

使得多个<u>请求处理者</u>都有机会处理请求，避免<u>请求发送者</u>和<u>请求处理者</u>间的耦合关系。多个<u>请求处理者</u>形成一条链，并沿着这条链传递请求，直到对象处理它为止。

## 场景

- Java Web 中的过滤器链
- Struts2 中的拦截器栈

## 参考

- [责任链模式](http://www.runoob.com/design-pattern/chain-of-responsibility-pattern.html)
