# Interpreter Pattern（解释器模式）

`类行为型模式`

## 定义

给定一个语言，定义它的**文法**的一种标识，并定义一个**解释器**，这个解释器使用该表式来解释语言中的句子。

文法（Grammar）：程序语言的生成系统，用文法可以精确定义一个语言，并根据该文法构造出识别这个语言的自动机。

## 动机

如果一种特定类型的问题发生频率足够高，那么就值得将该问题的各个实例表述为一个简单语言的句子，然后构建一个解释器解释这些句子来解决问题。

## 场景

当有一个语言需要解释执行，可以讲语言中的句子表示为一个抽象语法树（Abstract Syntax Tree, AST），可使用解释器模式。

## UML

<img src='https://yuml.me/diagram/nofunky/class/[Client%7C%7C],[Context%7C%7C],[AbstractExpression%7C%7C+interpret],[AbstractExpression]%5E-[TerminalExpression%7C%7C+interpret],[AbstractExpression]%5E-[NonterminalExpression%7C%7C+interpret],[NonTerminalExpression]%3C%3E-%3E[AbstractExpression],[Client]-%3E[AbstractExpression],[Client]-%3E[Context]'>

- AbstractExpression（抽象表达式）
    - 声明一个抽象的解释操作，这个接口为抽象语法树中所有的节点所共享。
- TerminalExpression（终结符表达式）
    - 实现与文法中的终结符相关联的解释操作。
    - 一个句子中的每个终结符需要该类的一个实例。
- NonterminalExpression（非终结符表达式）
    - 文法中的每条规则对应于一个非终结符表达式实例。
- Context（环境角色）
    - 包含解释器之外的全局信息。
- Client（客户）
    - 构建标识该文法定义的语言中一个特定的句子的抽象语法树。
    - 调用解释操作。

## 优缺点

- 易于改变和扩展文法
- 易于实现文法
- 复杂的文法难以维护
- 增加了新的解释表达式的方式

## 代码

### 实验一、实现布尔表达式操作求值

```php
/**
 * 思路：根据表达式类型分割成
 *     终结符表达式：[常量表达式]
 *     非终结符表达式：[变量表达式、与表达式、或表达式、非表达式]
 */
abstract class BooleanExp
{
    abstract public function evaluate(Context $context);//取值
    abstract public function replace($name, BooleanExp $exp);//表达式替换，注意递归
}
//常量表达式
class ConstantExp extends BooleanExp
{
    protected $constant;
    public function __construct($constant)
    {
        $this->constant = $constant;
    }
    public function evaluate(Context $context)
    {
        return $this->constant;
    }
    public function replace($name, BooleanExp $exp)
    {
        return $this;
    }
}
//变量表达式
class VariableExp extends BooleanExp
{
    protected $name;
    public function __construct($name)
    {
        $this->name = $name;
    }
    public function evaluate(Context $context)
    {
        return $context->get($this->name);
    }
    public function replace($name, BooleanExp $exp)
    {
        return $name === $this->name ? clone $exp : new self($this->name);//name相同，克隆本身，否则重新构造变量表达式
    }
}
//与表达式
class AndExp extends BooleanExp
{
    protected $left  = null;
    protected $right = null;
    public function __construct(BooleanExp $left,BooleanExp $right)
    {
        $this->left  = $left;
        $this->right = $right;
    }
    public function evaluate(Context $context)
    {
        return $this->left->evaluate($context) && $this->right->evaluate($context);
    }
    public function replace($name, BooleanExp $exp)
    {
        return new self($this->left->replace($name, $exp), $this->right->replace($name, $exp));
    }
    public function __clone()
    {
        return new self(clone $this->left, clone $this->right);
    }
}
//或表达式
class OrExp extends BooleanExp
{
    protected $left  = null;
    protected $right = null;
    public function __construct(BooleanExp $left, BooleanExp $right)
    {
        $this->left  = $left;
        $this->right = $right;
    }
    public function evaluate(Context $context)
    {
        return $this->left->evaluate($context) || $this->right->evaluate($context);
    }
    public function replace($name, BooleanExp $exp)
    {
        return new self($this->left->replace($name, $exp), $this->right->replace($name, $exp));
    }
    public function __clone()
    {
        return new self(clone $this->left, clone $this->right);
    }
}
//非表达式
class NotExp extends BooleanExp
{
    protected $exp = null;
    public function __construct(BooleanExp $exp)
    {
        $this->exp = $exp;
    }
    public function evaluate(Context $context)
    {
        return !$this->exp->evaluate($context);
    }
    public function replace($name, BooleanExp $exp)
    {
        return new self($this->exp->replace($name, $exp));
    }
    public function __clone()
    {
        return new self(clone $this->exp);
    }
}

class Context
{
    protected $params;
    public function __construct($params)
    {
        $this->params = $params;
    }
    public function get($name)
    {
        return $this->params[$name];
    }
    public function set($name, $value)
    {
        $this->params[$name] = $value;
    }
}

class Client
{
    public static function main()
    {
        //(true and x) or (y and (not x))
        $context = new Context([
            'x' => false,
            'y' => true,
            'z' => true
        ]);
        $x       = new VariableExp('x');
        $y       = new VariableExp('y');
        $expression = new OrExp(
            new AndExp(new ConstantExp(true), $x),
            new AndExp($y, new NotExp($x))
        );
        var_dump($expression->evaluate($context));//bool(true)
        //replace -> y = not z
        $replace = $expression->replace('y', new NotExp(new VariableExp('z')));
        $result  = $replace->evaluate($context);
        var_dump($result);//bool(false)
    }
}
Client::main();
```

### 实验二、四则运算器
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
- [行为型模式—解释器模式](http://www.cnblogs.com/5iedu/p/5595153.html)
- [Let’s Build A Simple Interpreter. Part 7.](https://ruslanspivak.com/lsbasi-part7/)
