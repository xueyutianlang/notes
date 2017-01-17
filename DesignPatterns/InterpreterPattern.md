# Interpreter Pattern（解释器模式）

## 概念

解释器模式(Interpreter Pattern) ：定义语言的文法，并且建立一个解释器来解释该语言中的句子，这里的 ”语言” 意思是使用规定格式和语法的代码，它是一种类行为型模式。

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

## 参考资料

- [解释器模式](http://www.cnblogs.com/cbf4life/archive/2009/12/17/1626125.html)
