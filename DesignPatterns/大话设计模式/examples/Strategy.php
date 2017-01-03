<?php

abstract class Strategy
{
    abstract public function exec();
}

class ConcreteStrategyA extends Strategy
{
    public function exec()
    {
        return "exec ConcreteStrategyA\n";
    }
}

class ConcreteStrategyB extends Strategy
{
    public function exec()
    {
        return "exec ConcreteStrategyB\n";
    }
}

class Context
{
    private $strategy = null;

    public function __construct(Strategy $strategy)
    {
        $this->strategy = $strategy;
    }

    public function exec()
    {
        return $this->strategy->exec(); 
    }
}

$context = new Context(new ConcreteStrategyA());
echo $context->exec();
$context = new Context(new ConcreteStrategyB());
echo $context->exec();
