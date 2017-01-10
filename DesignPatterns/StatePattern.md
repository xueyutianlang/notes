# State Pattern（状态模式）

## 总览

状态模式：对象状态改变时将改变其行为。

## UML

<img src="https://yuml.me/diagram/nofunky/class/[Context||+request()],[State||+handle()],[ConcreteStateA||+handle()],[ConcreteStateB||+handle()],[ConcreteStateC||+handle()],[Context]<>->[State],[State]^-[ConcreteStateA],[State]^-[ConcreteStateB],[State]^-[ConcreteStateC]">

- Context：维护一个 ConcreteState* 的实例，这个实例定义当前状态。
- State：定义一个接口以封装与 Context 的一个特定状态相关的行为。
- ConcreteState*：实现一个与 Context 的一个状态相关的行为。

## 用途

简化复杂的判断逻辑（if else or switch），将不同状态的行为分割开来。

<img src='https://yuml.me/diagram/nofunky/class/[Context%7C%7C+Request()],[State%7C%7C+Handle()],[ConcreteStateA%7C%7C+Handle()],[ConcreteStateB%7C%7C+Handle()],[ConcreteStateC%7C%7C+Handle()],[Context]%3C%3E-%3E[State],[State]%5E-[ConcreteStateA],[State]%5E-[ConcreteStateB],[State]%5E-[ConcreteStateC]'>

## 场景

当一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为时，就可以考虑使用状态模式了。
