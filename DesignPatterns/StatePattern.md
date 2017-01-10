# State Pattern（状态模式）

## 总览

状态模式：对象状态改变时将改变其行为。

## UML

<img src='https://yuml.me/diagram/nofunky/class/[Context%7C%7C+Request()],[State%7C%7C+Handle()],[ConcreteStateA%7C%7C+Handle()],[ConcreteStateB%7C%7C+Handle()],[ConcreteStateC%7C%7C+Handle()],[Context]%3C%3E-%3E[State],[State]%5E-[ConcreteStateA],[State]%5E-[ConcreteStateB],[State]%5E-[ConcreteStateC]'>

- Context：维护一个 ConcreteState* 的实例，这个实例定义当前状态。
- State：定义一个接口以封装与 Context 的一个特定状态相关的行为。
- ConcreteState*：实现一个与 Context 的一个状态相关的行为。

## 用途

简化复杂的判断逻辑（if else or switch），将不同状态的行为分割开来。

## 场景

当一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为时，就可以考虑使用状态模式了。

## 代码

下面用PHP来实现一个考勤表单申请的逻辑。

<img src='http://g.gravizo.com/g?
 digraph G {
   表单申请 -> 主管处理 -> 考勤处理 -> 处理完毕;
 }
'/>

### 复杂的判断逻辑

```php
//表单申请
class Form
{
    const OPERATE_APPLY      = 1; //表单申请
    const OPERATE_MANAGER    = 2; //主管处理
    const OPERATE_ATTENDANCE = 3; //考勤处理
    const OPERATE_FINISH     = 0; //处理完毕

    protected $operateCode = self::OPERATE_APPLY; //操作码

    public function getOperateCode()
    {
        return $this->operateCode;
    }

    public function setOperateCode($code)
    {
        $this->operateCode = $code; 
    }

    /**
     * 获取当前流转状态
     * @return string
     */
    public function getState()
    {
        switch ($this->operateCode) {
            case self::OPERATE_APPLY:
                //申请逻辑
                return '表单申请';
            case self::OPERATE_MANAGER:
                //主管逻辑
                return '主管处理';
            case self::OPERATE_ATTENDANCE:
                //考勤逻辑
                return '考勤处理';
            default:
                //完毕逻辑
                return '处理完毕';
        }
    }   
}

class Client
{
    public static function main()
    {
        $form = new Form();
        $form->setOperateCode(Form::OPERATE_APPLY);
        echo $form->getState(),PHP_EOL;
        $form->setOperateCode(Form::OPERATE_MANAGER);
        echo $form->getState(),PHP_EOL;
        $form->setOperateCode(Form::OPERATE_ATTENDANCE);
        echo $form->getState(),PHP_EOL;
        $form->setOperateCode(Form::OPERATE_FINISH);
        echo $form->getState(),PHP_EOL;

    }
}

Client::main();
```

### 状态模式简化逻辑

```php
class Form
{
    const OPERATE_APPLY      = 1;
    const OPERATE_MANAGER    = 2;
    const OPERATE_ATTENDANCE = 3;
    const OPERATE_FINISH     = 0;

    protected $operateCode = OPERATE_APPLY;
    protected $state; //流转状态

    public function __construct()
    {
        $this->setState(new ApplyState());  
    }

    public function getOperateCode()
    {
        return $this->operateCode;
    }

    public function setOperateCode($code)
    {
        $this->operateCode = $code; 
    }

    public function setState(State $state)
    {
        $this->state = $state;
    }

    public function getState()
    {
        return $this->state->getState($this);
    }
}

abstract class State
{
    abstract public function getState(Form $form);
}

//申请状态
class ApplyState extends State
{
    public function getState(Form $form)
    {
        if ($form->getOperateCode() == Form::OPERATE_APPLY) {
            //申请逻辑 
            return '表单申请';
        } else {
            $form->setState(new ManagerState());            
            return $form->getState();
        }
    }    
}

//主管状态
class ManagerState extends State
{
    public function getState(Form $form)
    {
        if ($form->getOperateCode() == Form::OPERATE_MANAGER) {
            //主管逻辑
            return '主管处理';
        } else {
            $form->setState(new AttendenceState());
            return $form->getState();
        }
    }
}

//考勤状态
class AttendenceState extends State
{
    public function getState(Form $form)
    {
        if ($form->getOperateCode() == Form::OPERATE_ATTENDANCE) {
            //考勤逻辑
            return '考勤处理';    
        } else {
            $form->setState(new FinishState());
            return $form->getState();
        }
    }
}

//完毕状态
class FinishState extends State
{
    public function getState(Form $form)
    {
        //完毕逻辑
        return '处理完毕';
    }
}

class Client
{
    public static function main()
    {
        $form = new Form();
        $form->setOperateCode(Form::OPERATE_APPLY);
        echo $form->getState(),PHP_EOL;
        $form->setOperateCode(Form::OPERATE_MANAGER);
        echo $form->getState(),PHP_EOL;
        $form->setOperateCode(Form::OPERATE_ATTENDANCE);
        echo $form->getState(),PHP_EOL;
        $form->setOperateCode(Form::OPERATE_FINISH);
        echo $form->getState(),PHP_EOL;
    }
}

Client::main();
```
