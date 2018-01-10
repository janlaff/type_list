# type_list
C++ compile-time type tuple with several algorithms to imitate std::tuple behaviour

## Examples

```
using my_empty_list = type_list<>;
using my_list = my_empty_list::add<double, int>; // -> type_list<double, int>
```
