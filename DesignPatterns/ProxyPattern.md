# Proxy Pattern（代理模式）

## 总览

- [1. 用途](#1)
- [2. 场景](#2)
    - [2.1 远程代理](#2.1)
    - [2.2 虚拟代理](#2.2)
    - [2.3 保护代理](#2.3)
    - [2.4 智能代理](#2.4)
- [3. UML](#3)
- [4. 组成](#4)
- [5. 代码](#5)
- [6. 参考资料](#6)

<h2 id="1">1. 用途</h2>

- 提供对象代理来控制访问。
- 使用额外的中间层来支持分布式控制和智能访问。
- 增加包装和委派来保护真实的成员。

<h2 id="2">2. 场景</h2>

<h3 id="2.1">2.1 远程代理（Remote Proxy）</h3>

用于访问远程对象，隐藏事实（分布在不同的地址空间）。

<h3 id="2.2">2.2 虚拟代理（Virtual Proxy）</h3>

通过 lazily loading 按需加载。

<h3 id="2.3">2.3 保护代理（Protection Proxy）</h3>

基于访问规则对属性和方法进行权限控制。

<h3 id="2.4">2.4 智能代理（Smart Proxy）</h3>

当调用方法时添加额外的行为，适用于切面编程。


<h2 id="3">3. UML</h2>

![Proxy Pattern UML](images/400px-Proxy_pattern_diagram.svg.png)

<h2 id="4">4. 组成</h2>

**抽象角色**（Subject）：通过接口或抽象类声明真实角色实现的业务方法。

**代理角色**（Proxy）：实现抽象角色，是真实角色的代理，通过真实角色的业务逻辑方法来实现抽象方法，并可以附加自己的操作。

**真实角色**（RealSubject）：实现抽象角色，定义真实角色所要实现的业务逻辑，供代理角色调用。

<h2 id="5">5. 代码</h2>

```php
<?php
/**
 * Proxy design pattern (lazy loading)
 * 
 * @author Enrico Zimuel (enrico@zimuel.it) 
 * @see    https://github.com/ezimuel/PHP-design-patterns/blob/master/Proxy.php
 */
interface ImageInterface
{
    public function display();
}
class Image implements ImageInterface
{
    protected $filename;
    public function  __construct($filename) {
        $this->filename = $filename;
        $this->loadFromDisk();
    }
    protected function loadFromDisk() {
        echo "Loading {$this->filename}\n";
    }
    public function display() {
        echo "Display {$this->filename}\n";
    }
}
class ProxyImage implements ImageInterface
{
    protected $id;
    protected $image;
    public function  __construct($filename) {
        $this->filename = $filename;
    }
    public function display() {
        if (null === $this->image) {
            $this->image = new Image($this->filename);
        }
        return $this->image->display();
    }
}
// Usage example
$filename = 'test.png';
$image1 = new Image($filename); // loading necessary
echo $image1->display(); // loading unnecessary
$image2 = new ProxyImage($filename); // loading unnecessary
echo $image2->display(); // loading necessary
echo $image2->display(); // loading unnecessary
```

<h2 id="6">6. 参考资料</h2>

- [Wikipedia Proxy Pattern](https://en.wikipedia.org/wiki/Proxy_pattern)
- [SourceMaking Proxy Pattern](https://sourcemaking.com/design_patterns/proxy)
- [RESTful Remote Object Proxies with ProxyManager](https://www.sitepoint.com/restful-remote-object-proxies-with-proxymanager/)

