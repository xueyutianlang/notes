# Chain Of Reponsibility Pattern（责任链模式）

## 总览

责任链模式：对象由每一个对象对其下家的引用而连接起来形成**一条链**。请求在这个链上传递，直到链上的某一个对象决定处理此请求。发出请求的客户端并不知道链上的哪一个对象最终处理这个请求，这使得系统可以在不影响客户端的情况下动态地重新组织和分配责任。

责任链模式是对象的**行为模式**。

## UML

<img src="https://yuml.me/diagram/nofunky/class/[Handler%7Csuccessor:%20Handler%7C+setSuccessor():%20void;+handle():%20void;],[ConcreteHandlerA%7C%7C+handle():%20void],[ConcreteHandlerB%7C%7C+handle():%20void],[Client%7C%7C],[Handler]%5E-[ConcreteHandlerA],[Handler]%5E-[ConcreteHandlerB],[Handler]%3C%3E-%3E[Handler],[Client]-.-%3E[Handler]">
