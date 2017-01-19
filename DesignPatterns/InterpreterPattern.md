# Interpreter Pattern（解释器模式）

`类行为型模式`

## 定义

给定一个语言，定义它的**文法**的一种标识，并定义一个**解释器**，这个<u>解释器使用该表式来解释语言中的句子</u>。

- 文法（Grammar）：程序语言的生成系统，用文法可以精确定义一个语言，并根据该文法构造出识别这个语言的自动机。


## UML

<img src='https://yuml.me/diagram/nofunky/class/[Client%7C%7C],[Context%7C%7C],[AbstractExpression%7C%7C+interpret],[AbstractExpression]%5E-[TerminalExpression%7C%7C+interpret],[AbstractExpression]%5E-[NonterminalExpression%7C%7C+interpret],[TerminalExpression]%3C%3E-%3E[AbstractExpression],[Client]-%3E[AbstractExpression],[Client]-%3E[Context]'>

- AbstractExpression（抽象解释器）：具体的解释任务由实现类完成
- TerminalExpression（终结符表达式）： 实现与文法中的元素相关联的解释操作。
- NonterminalExpression（非终结符表达式）：文法中的每条规则对应于一个非终结表达式。
- Context（环境角色）

## 代码

```php
<?php

//main.php
interface Expression
{
    public function interpreter(array $var);
}

class VarExpression implements Expression
{
    protected $key;

    public function __construct($key)
    {
        $this->key = $key;
    }

    public function interpreter(array $var)
    {
        return $var[$this->key];
    }
}

abstract class SymbolExpression implements Expression
{
    protected $left = null;
    protected $right = null;

    public function __construct(Expression $left, Expression $right)
    {
        $this->left = $left;
        $this->right = $right;
    }
}

class AddExpression extends SymbolExpression
{
    public function interpreter(array $var)
    {
        return $this->left->interpreter($var) + $this->right->interpreter($var);
    }
}

class SubExpression extends SymbolExpression
{
    public function interpreter(array $var)
    {
        return $this->left->interpreter($var) - $this->right->interpreter($var);
    }
}

class Calculator
{
    protected $expression = null;

    public function __construct($expr)
    {
        $expr = array_values(array_filter(str_split($expr, 1), function ($value) {
            return $value !== ' ';
        }));
        $stack = [];
        for ($i = 0; $i < count($expr); $i++) {
            $val = $expr[$i];
            switch ($val) {
                case '+':
                    $stack[] = new AddExpression(array_pop($stack), new VarExpression($expr[++$i]));
                    break;
                case '-':
                    $stack[] = new SubExpression(array_pop($stack), new VarExpression($expr[++$i]));
                    break;
                default:
                    $stack[] = new VarExpression($val);
            }
        }
        $this->expression = array_pop($stack);
    }

    public function result($var)
    {
        return $this->expression->interpreter($var);
    }
}

class Client
{
    public static function main()
    {
        $options = getopt('e:v:');
        $expr    = $options['e'];
        $var     = json_decode($options['v'], true);
        $calculator = new Calculator($expr);
        echo $calculator->result($var);
    }
}

Client::main();
```

```bash
$ php main.php -e 'a+b-c' -v '{"a":1,"b":2,"c":10}'
-7
```

[PHP实现逆波兰四则计算器（解释器模式）](http://blog.netsan.cn/2017/01/18/PHP%E5%AE%9E%E7%8E%B0%E9%80%86%E6%B3%A2%E5%85%B0%E5%9B%9B%E5%88%99%E8%AE%A1%E7%AE%97%E5%99%A8%EF%BC%88%E8%A7%A3%E9%87%8A%E5%99%A8%E6%A8%A1%E5%BC%8F%EF%BC%89/)

## 参考资料

- [解释器模式](http://www.cnblogs.com/cbf4life/archive/2009/12/17/1626125.html)
