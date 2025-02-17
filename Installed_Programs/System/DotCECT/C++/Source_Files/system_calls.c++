// Define system call numbers
#define SYS_PRINT 1

// Function prototypes
void sys_print();
void syscall_handler(int syscall_number);

// System call table declaration
void* syscall_table[] = {
    nullptr,         // 0 is reserved
    (void*)sys_print // 1 - SYS_PRINT
};

// System call handler function
void syscall_handler(int syscall_number) {
    if (syscall_number >= 0 && syscall_number < sizeof(syscall_table) / sizeof(syscall_table[0])) {
        void (*handler)() = (void (*)())syscall_table[syscall_number];
        if (handler) {
            handler();
        } else {
            // Handle unimplemented system call
            // Add your custom error handling code here
        }
    } else {
        // Handle invalid system call number
        // Add your custom error handling code here
    }
}

// Example system call implementation
void sys_print() {
    // Implement your custom kernel-space printing function here
    // For example, writing to a console or a log file
}
