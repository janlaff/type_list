# type_list
C++ compile-time type tuple with several algorithms to imitate std::tuple behaviour

## Examples

### Adding types
```
using my_empty_list = type_list<>;
using my_list = my_empty_list::add<double, int>; // -> type_list<double, int>
```
or just
```
using my_list = type_list<double, int>;
```

### Get size
```
using my_list = type_list<int, float>;

// my_list::size -> 2
```

### Removing the first occurrence of a type
```
using my_list = type_list<double, float, double, char>;
using result = my_list::remove<float>; // -> type_list<double, double, char>
```

### Remove all occurrences of one or more types
```
using my_list = type_list<double, float, double, char>;
using result = my_list::remove_all<double, char>; // -> type_list<float>
```

### Get type at index
```
using my_list = type_list<int, float, char>;
using elem1 = my_list::get<1>; // float
```

### Concat lists
```
using my_list = type_list<char, float>;
using my_list2 = type_list<int, std::string>;

using result = my_list::concat<my_list2>; // -> type_list<char, float, int, std::string>
```

Pretty easy, isn't it??
