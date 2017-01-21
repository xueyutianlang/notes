# Singleton Pattern（单例模式）

## 代码

```php
class Singleton
{
    protected static $instance = null;
    
    public static function getInstance()
    {
        if (null === self::$instance) {
            self::$instance = new self();
        }
        return self::$instance;
    }
}
```
