#include <cst/unx/File.h>

namespace cst {
namespace unx {

File Stdin(STDIN_FILENO, ":stdin:");
File Stdout(STDOUT_FILENO, ":stdout:");
File Stderr(STDERR_FILENO, ":stderr:");

}
}
