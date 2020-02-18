# ansictrl

A simple header-only library providing wrappers for ansi escape sequences.

## How to use

### Setup

1. clone this repository

2. include the header
    ```cpp
    #include "ansictrl.h"
    ```

3. (optional) use namespace
    ```cpp
    using namespace ansi;
    ```
    You may even use `ansi::term`, but beware that this contains typenames such as color, direction, etc.
    Using `ansi::term` is *not* recommended.

### Functions

All functionality is wrapped in free functions in the `ansi::term` namespace.
The following examples assume `using namespace ansi::term;` and thus omit the `ansi::term::` prefix to all types and names.

* `set_color(color foreground, color background)`
    Sets the foreground and background color (type `term::color`). If you only want to set one of them, set the other one to `term::color::DontChange`.
    To reset the color all attributes have to be reset with `clear_attributes()`.

* `set_cursor_pos(u32 line, u32 column)`
    Sets the cursor's position to the line and column specified.

* `move_cursor(dir direction, u32 amount)`
    Moves the cursor's position by amount, in the specified direction (type `term::dir`).

* Attributes
    Apart from the color the following attributes can be enabled:
    * `bold_on()`
    * `blink_on()`
    * `underscore_on()`
    * `reverse_on()`
    * `concealed_on()`
    These can be disabled by clearing all attributes with `clear_attributes()`.

* Misc. functions
    These are documented better in ANSI documentation than I could do here:
    * `clear_line()`
    * `clear_screen()`
    * `enable_line_wrapping()`
    * `disable_line_wrapping()`
    * `save_cursor_pos()`
    * `restore_cursor_pos()`


