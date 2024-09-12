// SimpleMath.cpp
extern "C" {

__attribute__((visibility("default"))) 
__attribute__((used))
int Add(int a, int b) {
    return a + b;
}

__attribute__((visibility("default"))) 
__attribute__((used))
int Subtract(int a, int b) {
    return a - b;
}

__attribute__((visibility("default"))) 
__attribute__((used))
int Multiply(int a, int b) {
    return a * b;
}

__attribute__((visibility("default"))) 
__attribute__((used))
float Divide(int a, int b) {
    if (b == 0) return 0; // avoid division by zero
    return (float)a / b;
}
}
