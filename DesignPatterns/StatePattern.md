# State Pattern（状态模式）

## 总览

状态模式：当一个对象的内在状态改变时允许改变其行为，这个对象看起来像是改变了其类。

## 用途

状态模式主要解决的是当控制一个对象状态转换的条件表达式过于复杂时的情况。把状态的判断逻辑转移到表示不同状态的一系列类当中，可以把复杂的判断逻辑简单化。

## 场景

当一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为时，就可以考虑使用状态模式了。

## UML

<img src='https://yuml.me/diagram/nofunky/class/[Context%7C%7C+Request()],[State%7C%7C+Handle()],[ConcreteStateA%7C%7C+Handle()],[ConcreteStateB%7C%7C+Handle()],[ConcreteStateC%7C%7C+Handle()],[Context]%3C%3E-%3E[State],[State]%5E-[ConcreteStateA],[State]%5E-[ConcreteStateB],[State]%5E-[ConcreteStateC]'>

## 优点

将与特定状态相关的行为局部化，并且将不同状态的行为分割开来。
