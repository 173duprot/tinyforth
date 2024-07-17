// This is where you write your platform's IO

int write(int fd, const void *buf, unsigned int count) {
    int ret;
    asm volatile (
        "syscall" : "=a" (ret) : "a" (1), "D" (fd), "S" (buf), "d" (count) : "rcx", "r11", "memory"
    );
    return ret;
}

int read(int fd, void *buf, unsigned int count) {
    int ret;
    asm volatile (
        "syscall" : "=a" (ret) : "a" (0), "D" (fd), "S" (buf), "d" (count) : "rcx", "r11", "memory"
    );
    return ret;
}

int puts(const char *s) {
    while (*s) {
        if (write(1, s++, 1) != 1) return -1;
    }
    return write(1, "\n", 1) != 1 ? -1 : 0;
}

char* gets(char *buf) {
    char *ptr = buf;
    while (read(0, ptr, 1) > 0 && *ptr != '\n' && *ptr != '\0') ptr++;
    *ptr = '\0';
    return buf;
}
