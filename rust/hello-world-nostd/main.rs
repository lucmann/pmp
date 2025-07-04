#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_: &PanicInfo) -> ! {
    loop {} // Loop forever to halt the program
}

#[no_mangle]
pub extern "C" fn _start() {
    let message = b"Hello, world!\n";
    let fd: usize = 1; // File descriptor for stdout
    let syscall_no: usize = 1; // Syscall number for write in Linux
    unsafe {
        // Use inline asm macro to perform the syscall
        core::arch::asm!(
            "syscall",
            in("rax") syscall_no, // syscall number
            in("rdi") fd,         // file descriptor
            in("rsi") message.as_ptr(), // pointer to the message
            in("rdx") message.len(), // length of the message
            out("rcx") _, out("r11") _,
        );
    }

    loop {} // Loop forever to avoid segfault since _start() is expected
            // to never return in a no_std environment
}
