# SOLID

- [1. Single Responsibility Principle（单一职责原则）](#SRP)
- [2. Open/Closed Principle（开闭原则）](#OCP)
- [3. Liskov Substitution Principle（里氏替换原则）](#LSP)
- [4. Interface Segregation Principle（接口隔离原则）](#ISP)
- [5. Dependency Inversion Priciple（依赖倒置原则）](#DIP)

> SOLID：single responsibility, open-closed, Liskov substitution, interface segregation and dependency inversion.

<table>
    <tr><th>Initial</th><th>Stands for</th><th>Concept</th></tr>
    <tr><td>S</td><td>SRP</td><td>Single Responsibility Priciple（单一职责）</td></tr>
    <tr><td>O</td><td>OCP</td><td>Open/Closed Principle（开闭）</td></tr>
    <tr><td>L</td><td>LSP</td><td>Liskov Substitution Principle（里氏替换）</td></tr>
    <tr><td>I</td><td>ISP</td><td>Interface Segregation Principle（接口隔离）</td></tr>
    <tr><td>D</td><td>DIP</td><td>Dependency Inversion Principle（依赖倒置）</td></tr>
</table>

<h2 id="SRP">1. <a href="https://en.wikipedia.org/wiki/Single_responsibility_principle">Single Responsibility Principle</a>（单一职责原则）</h2>

> A class should have only one reason to change. -- [Robert C. Martin](https://en.wikipedia.org/wiki/Robert_Cecil_Martin)

一个类应该只有一个发生变化的原因。

<h2 id="OCP">2. <a href="https://en.wikipedia.org/wiki/Open/closed_principle">Open/Closed Principle</a>（开闭原则）</h2>

> software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification.

- open for extension：对扩展是开放的。
- closed for modification：对修改时关闭的。

<h2 id="LSP">3. <a href="https://en.wikipedia.org/wiki/Liskov_substitution_principle">Liskov Substitution Principle</a>（里氏替换原则）</h2>

> objects in a program should be replaceable with instances of their subtypes without altering the correctness of that program.

任何基类可以出现的地方，子类一定可以出现。

<h2 id="ISP">4. <a href="https://en.wikipedia.org/wiki/Interface_segregation_principle">Interface Segregation Principle</a>（接口隔离原则）</h2>

> many client-specific interfaces are better than one general-purpose interface.

多个特定的接口比一个通用的接口要好。

<h2 id="DIP">5. <a href="https://en.wikipedia.org/wiki/Dependency_inversion_principle">Dependency Inversion Priciple</a>（依赖倒置原则）</h2>

> High-level modules should not depend on low-level modules. Both should depend on abstractions.
> Abstractions should not depend on details. Details should depend on abstractions.

- 高层次的模块不应该依赖低层次的模块，他们应该依赖于抽象。
- 抽象不应该依赖于具体实现，具体实现应该依赖于抽象。
