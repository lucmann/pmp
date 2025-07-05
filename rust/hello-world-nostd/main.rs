#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_: &PanicInfo) -> ! {
    loop {} // Loop forever to halt the program
}

#[no_mangle]
#[cfg(target_arch = "x86_64")]
pub unsafe extern "C" fn _start() {
    let message = b"Hello, world!\n";
    let fd: usize = 1; // File descriptor for stdout
    let syscall_no: usize = 1; // Syscall number for write in Linux x86_64
    // Use inline asm macro to perform the syscall
    core::arch::asm!(
        "syscall",
        in("rax") syscall_no, // syscall number
        in("rdi") fd,         // file descriptor
        in("rsi") message.as_ptr(), // pointer to the message
        in("rdx") message.len(), // length of the message
        out("rcx") _, out("r11") _, // telling compiler these registers will
                                    // be clobbered by syscalls
    );

    // Exit the program with status code 0
    core::arch::asm!(
        "syscall",
        in("rax") 60, // syscall number for exit
        in("rdi") 0,  // exit status code
        out("rcx") _, out("r11") _, // telling compiler these registers will
                                    // be clobbered by syscalls
    );
}
