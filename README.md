# C Template Libraries
Template container library for C.

## Usage
Build with `make`.
Copy files from `target/`.

## Demo
- [`testvector.c`](tests/testvector.c)
- [`teststack.c`](tests/teststack.c)
- [`testqueue.c`](tests/testqueue.c)

## Library
### Example usage
```c
typedef struct {
    int age;
    char *name;
} Person;

int main()
{
    // creating a vector of Persons
    Vector(Person) vcp = VectorFn(Person, from)(6, (Person[6]) {
        (Person) { 56, "Bob"   },
        (Person) { 21, "Nana"  },
        (Person) { 12, "Joe"   },
    });
    // your code
    vcp->free(&vcp);
}
```
### Containers
```
vector:      Resizable array
stack:       Array type stack
queue:       Array type queue
bstmap:      AVL BST based map
bstset:      AVL BST based set
hashmap    
hashset
linkedlist:  Doubly linked list
string
```

### Common functions
```
length:  Get total elements currently present in a container.
isempty: True if length of container is 0.
get:     Get an element from the container.
set:     Set an element in the container.
begin:   Get a pointer to the first element of a container.
end:     Get a pointer that doesn't belong to the container.
rbegin:  Get a pointer to the last element of a container.
next:    Update a pointer to point to the next element.
rnext:   Update a pointer to point to the previous element.
clone:   Clone an entire container.
free:    Shallow free the container from memory.
```

### Common macros
```
DECLARE: Declare the prototypes of a container functionality
         for some specific type.

DEFINE:  Define the functionality of a container for some
         specific type.

FOREACH: Iterates over every element of a container.
           i     -- Index
           key   -- Key (for maps only)
           value -- Pointer to value
```
